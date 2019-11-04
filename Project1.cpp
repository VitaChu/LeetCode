//*/  非叶子节点的cost的计算 
min_DP_val = 1000000000;
			min_DP_via_cost = 1000000000;
			global_x = x;
			global_y = y;
			max_DP_k = z;
			if (path_map[x][y].val == 1)	// not a pin
				min_DP_k = z;
			else	// pin
				min_DP_k = 0;
			for(i = 0; i < 4; ++i)
				min_DP_idx[i] = -1;
			rec_count(0, 0, count_idx);
			
			
			
void rec_count(int level, int val, int *count_idx) {
	int k, temp_x, temp_y, temp_val, temp_via_cost;
	int temp_idx[4];
	int min_k, max_k, temp_min_k, temp_max_k;
	
	if (level < 4) {
		if (val <= min_DP_val) {
			for(k = 0; k < level; ++k)
				temp_idx[k] = count_idx[k];
			if (path_map[global_x][global_y].edge[level] == 1) {
				temp_x = global_x + plane_dir[level][0];
				temp_y = global_y + plane_dir[level][1];
				for(k = 0; k < global_max_layer; ++k)	// use global_max_layer to substitue max_zz
					if (klat_map[temp_x][temp_y][k].val >= 0) {
						temp_idx[level] = k;
						rec_count(level + 1, val + klat_map[temp_x][temp_y][k].val, temp_idx);
					}
			}
			else {
				temp_idx[level] = -1;
				rec_count(level + 1, val, temp_idx);
			}
		}
	}
	
	else {	// level == 4
		min_k = min_DP_k;
		max_k = max_DP_k;
		for(k = temp_via_cost = 0; k < 4; ++k)
			if (count_idx[k] != -1) {
				if (count_idx[k] < min_k)
					min_k = count_idx[k];
				if (count_idx[k] > max_k)
					max_k = count_idx[k];
				temp_via_cost += klat_map[global_x+plane_dir[k][0]][global_y+plane_dir[k][1]][count_idx[k]].via_cost;
			}
		temp_via_cost += ((max_k - min_k) * via_cost);
		#ifdef VIA_DENSITY
		for(k = min_k, temp_val = val; k < max_k; ++k)
			if (viadensity_map[global_x][global_y][k].cur >= viadensity_map[global_x][global_y][k].max)
				++temp_val;
		#else
		temp_val = temp_via_cost;
		#endif
		if (temp_val < min_DP_val) {
			min_DP_val = temp_val;
			min_DP_via_cost = temp_via_cost;
			for(k = 0; k < 4; ++k)
				min_DP_idx[k] = count_idx[k];
		}
		else if (temp_val == min_DP_val) {
		#ifdef VIA_DENSITY
			if (temp_via_cost < min_DP_via_cost) {
				min_DP_via_cost = temp_via_cost;
				for(k = 0; k < 4; ++k)
					min_DP_idx[k] = count_idx[k];
			}
			else if (temp_via_cost == min_DP_via_cost) {
				temp_min_k = min_DP_k;
				temp_max_k = max_DP_k;
				for(k = 0; k < 4; ++k)
					if (min_DP_idx[k] != -1) {
						if (min_DP_idx[k] < temp_min_k)
							temp_min_k = min_DP_idx[k];
						if (min_DP_idx[k] > temp_max_k)
							temp_max_k = min_DP_idx[k];
					}
				if (max_k > temp_max_k || min_k > temp_min_k)
					for(k = 0; k < 4; ++k)
						min_DP_idx[k] = count_idx[k];
			}
			#else
			temp_min_k = min_DP_k;
			temp_max_k = max_DP_k;
			for(k = 0; k < 4; ++k)
				if (min_DP_idx[k] != -1) {
					if (min_DP_idx[k] < temp_min_k)
						temp_min_k = min_DP_idx[k];
					if (min_DP_idx[k] > temp_max_k)
						temp_max_k = min_DP_idx[k];
				}
			if (max_k > temp_max_k || min_k > temp_min_k)
				for(k = 0; k < 4; ++k)
					min_DP_idx[k] = count_idx[k];
			#endif
		}
	}
}

