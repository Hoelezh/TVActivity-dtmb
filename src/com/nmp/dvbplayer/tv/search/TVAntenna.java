package com.nmp.dvbplayer.tv.search;

import java.util.ArrayList;

import com.alitech.dvb.DVBSatellite;
import com.alitech.dvb.DVBSatelliteNode;
import com.alitech.dvb.DvbSystem;
import com.alitech.dvb.DvbTpNode;
import com.nmp.dvbplayer.R;

import android.app.Activity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.widget.LinearLayout;
import android.widget.TextView;

public class TVAntenna extends Activity {
	
	final static int TUNER_ID = 0;
	final static int SATELLITE_ID = 1;
	final static int LNB_ID = 2;
	final static int TRANSPONDER_ID = 3;
	final static int DISEQC1_0_ID = 4;
	final static int DISEQC1_1_ID = 5;
	final static int S22K_ID = 6;
	final static int POLARITY_ID = 7;
	
	//LNB params start
	final static int lnb_freqs_list[] = {
		5150,	/*	0  */
		5750,	/*	1  */
		5950,	/*	2  */
		9750,	/*	3  */
		10000,	/*	4  */
		10050,	/*	5  */
		10450,	/*	6  */
		10550,	/*	7  */
		10600,	/*	8  */
		10700,	/*	9  */
		10750,	/*	10  */
		11250,	/*	11  */
		11300,	/*	12  */
		10200	/*	13 */
	};
	
	final static int LNB_FRE_5150 = 0;
	final static int LNB_FRE_5750 = 1;
	final static int LNB_FRE_5950 = 2;
	final static int LNB_FRE_9750 = 3;
	final static int LNB_FRE_10000 = 4;
	final static int LNB_FRE_10050 = 5;
	final static int LNB_FRE_10450 = 6;
	final static int LNB_FRE_10550 = 7;
	final static int LNB_FRE_10600 = 8;
	final static int LNB_FRE_10700 = 9;
	final static int LNB_FRE_10750 = 10;
	final static int LNB_FRE_11250 = 11;
	final static int LNB_FRE_11300 = 12;
	final static int LNB_FRE_10200 = 13;
	private static final DvbTpNode[] NULL = null;
	
	final int lnb_standard_freqs[] = {
		LNB_FRE_5150,
		LNB_FRE_5750,
		LNB_FRE_5950,
		LNB_FRE_9750,
		LNB_FRE_10000,
		LNB_FRE_10050,
		LNB_FRE_10450,
		LNB_FRE_10550,
		LNB_FRE_10600,
		LNB_FRE_10700,
		LNB_FRE_10750,
		LNB_FRE_11250,
		LNB_FRE_11300,
		LNB_FRE_10200,
	};

	final int lnb_user_freqs[][] = {
		{LNB_FRE_5150,	LNB_FRE_5750},
		{LNB_FRE_5750,	LNB_FRE_5150},
	};

	final int lnb_universal_freqs[][] = {
		{LNB_FRE_9750,	LNB_FRE_10550},
		{LNB_FRE_9750,	LNB_FRE_10600},
		{LNB_FRE_9750,	LNB_FRE_10700},
		{LNB_FRE_9750,	LNB_FRE_10750},	
	};

	final int lnb_unicable_freqs[][] = {
		{LNB_FRE_9750,	LNB_FRE_10600},
		{LNB_FRE_10200, LNB_FRE_10200},
	};
	
	final int LNB_CTRL_STD = 0;	/* standard non dual-LNB	*/
	final int LNB_CTRL_POL = 1;	/* dual LNB controlled by polar	*/
	final int LNB_CTRL_22K = 2;	/* dual LNB controlled by 22k	*/
	final int LNB_CTRL_UNICABLE = 3;	/* dual LNB controlled from unicable */
	final int LNB_CTRL_RESERVED = 4;	/* reserved control method	*/
	
	//LNB params end
	
	String [] DiSEqC10 = {
			"Disable",
			"Port1",
			"Port2",
			"Port3",
			"Port4",
	};
	
	String [] DiSEqC11 = {
			"Disable",
			"1Cascade M1:Port1",
			"1Cascade M1:Port2",
			"1Cascade M1:Port3",
			"1Cascade M1:Port4",
			"1Cascade M2:Port1",
			"1Cascade M2:Port2",
			"1Cascade M2:Port3",
			"1Cascade M2:Port4",
			"1Cascade M3:Port1",
			"1Cascade M3:Port2",
			"1Cascade M3:Port3",
			"1Cascade M3:Port4",
			"2Cascade: Port1",
			"2Cascade: Port2",
			"2Cascade: Port3",
			"2Cascade: Port4",
			"2Cascade: Port5",
			"2Cascade: Port6",
			"2Cascade: Port7",
			"2Cascade: Port8",
			"2Cascade: Port9",
			"2Cascade: Port10",
			"2Cascade: Port11",
			"2Cascade: Port12",
			"2Cascade: Port13",
			"2Cascade: Port14",
			"2Cascade: Port15",
			"2Cascade: Port16",
	};
	
    final int DISEQC11_TYPE_DISABLE = 0; /* disable(not set)*/
    final int DISEQC11_TYPE_1CASCADE = 1; /* 1 Cascade */
    final int DISEQC11_TYPE_2CASCADE = 2; /* 2 Cascade */
	
	private int item_count = 8;
	private int FocusID = 0;
	
	private int select_sat_id;
	private int select_tp_id;
	private int select_lnb_id;
	private int select_DiSEqC10_id;
	private int select_DiSEqC11_id;
	private int select_K22_id;
	private int select_pol_id;
	
	private boolean is_k22_gray;
	
	private int sat_count;
	private int tp_count;
	private int lnb_count;
	
	private boolean is_edit = false;
	
	private DVBSatelliteNode[] sat_nodes;
	private ArrayList<DVBSatelliteNode> mSatLists;
	private DvbTpNode[] tp_nodes;
	
	private DVBSatelliteNode sat_show;
	private DvbTpNode tp_show;
	
	private ArrayList<View> mItemLists;
	private int[] mItemName = {
			R.string.tv_antenna_tuner,
			R.string.tv_antenna_satellite,
			R.string.tv_antenna_lnb,
			R.string.tv_antenna_freq,
			R.string.tv_antenna_dis1,
			R.string.tv_antenna_dis2,
			R.string.tv_antenna_22K,
			R.string.tv_tp_polarity,
	};
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		setContentView(R.layout.tv_satellite_list);
		
		LinearLayout lLayout = (LinearLayout)this.findViewById(R.id.tv_satellite_header);
		lLayout.setVisibility(View.GONE);
		TextView txtTextView = (TextView)this.findViewById(R.id.tv_satellite_help);
		txtTextView.setVisibility(View.GONE);
		
		lLayout = (LinearLayout)this.findViewById(R.id.tv_satellite_items);
		LayoutParams params = lLayout.getLayoutParams();
		params.height = 600;
		lLayout.setLayoutParams(params);
		
		this.mItemLists = new ArrayList<View>();
		for (int i = 0; i < item_count; ++i ) {
			View.inflate(this, R.layout.tv_search_list_item, lLayout);
		}
		
		for (int i = 0; i < item_count; ++i) {
			this.mItemLists.add(lLayout.getChildAt(i));
		}	
	
		for (int i = 0; i < item_count; ++i) {
			View view = lLayout.getChildAt(i);
			view.findViewById(R.id.val_picker).setVisibility(View.GONE);
			view.findViewById(R.id.value_field).setVisibility(View.VISIBLE);
		}
		
		TextView txtTitle = (TextView)this.findViewById(R.id.tv_satellite_title);
		txtTitle.setText(R.string.tv_antenna_set);
		
		FocusID = 0;
		is_edit = false;
		
		select_sat_id = 0;
		select_tp_id = 0;
		select_lnb_id = 0;
		
		sat_count = 0;
		tp_count = 0;
		
		is_k22_gray = false;
		
		lnb_count = lnb_standard_freqs.length + lnb_user_freqs.length + lnb_universal_freqs.length + lnb_unicable_freqs.length; 
	}
	
	@Override
	protected void onStart() {
		super.onStart();
		
		for(int i = 0; i < item_count; ++i) {
			TextView txtTextView = getTitleText(i);
			txtTextView.setText(mItemName[i]);
			updateView(i);
		}
		
		TextView text = getValueText(TUNER_ID);
		text.setText("LNB1(Fixed)");
		
		initNodeList();
		
	}
	
	private void initNodeList() {
		this.sat_nodes = DVBSatellite.loadSatelliteNodes();
		if(this.sat_nodes == null || this.sat_nodes.length == 0) {
			return;
		}
		DVBSatelliteNode sNode;
		this.mSatLists = new ArrayList<DVBSatelliteNode>();
		for (int i = 0; i < this.sat_nodes.length; i++) {
			sNode = this.sat_nodes[i];
			
			if(sNode.isselect()) {
				mSatLists.add(sNode);
			}
		}
		
		sat_count = this.mSatLists.size();
		if(sat_count == 0 && this.sat_nodes.length > 0) {
			sNode = this.sat_nodes[0];
			mSatLists.add(sNode);
			sat_count = this.mSatLists.size();
			sNode.setselect(true);
			sNode.settuner1(true);
			DVBSatellite.updateSatellite(sNode);
		}
		
		if(sat_count > 0) {
			sat_show = this.mSatLists.get(select_sat_id);
			this.tp_nodes = DVBSatellite.loadTpNodes(sat_show.getId());
			if(this.tp_nodes == NULL)
				tp_count = 0;
			else
			tp_count = this.tp_nodes.length;
			this.initLNB();
			this.initDiseqc();
			this.initK22();
			this.initpol();
			
			updateSat(0);
			updateTp(0);
		}
		
	}
	
	private TextView getTitleText(int index) {
		int rid = R.id.tv_satellite_items;
		LinearLayout lLayout = (LinearLayout)this.findViewById(rid);

		View view = lLayout.getChildAt(index);
		
		TextView value_view = null;
		if (view == null) {
			return null;
		}

		value_view = (TextView) view.findViewById(R.id.text_field);

		return value_view;
	}
	
	private TextView getValueText(int index) {
		int rid = R.id.tv_satellite_items;
		LinearLayout lLayout = (LinearLayout)this.findViewById(rid);

		View view = lLayout.getChildAt(index);
		
		TextView value_view = null;
		if (view == null) {
			return null;
		}

		value_view = (TextView) view.findViewById(R.id.value_field);

		return value_view;
	}
	
	private void updateView(int index) {
		int rid = R.id.tv_satellite_items;
		LinearLayout lLayout = (LinearLayout)this.findViewById(rid);
		View view = lLayout.getChildAt(index);

		if(index == FocusID) {
			view.setBackgroundResource(R.drawable.tv_search_list_focus);
		}
		else {
			view.setBackgroundResource(0);
		}
			
	}
	
	private void updateSat(int diff) {
		select_sat_id = select_sat_id+diff;
		if( select_sat_id < 0) {
			select_sat_id = this.sat_count -1;
		}
		else if(select_sat_id == this.sat_count) {
			select_sat_id = 0;
		}
		
		this.sat_show = this.mSatLists.get(select_sat_id);
		
		TextView text = getValueText(SATELLITE_ID);
		text.setText("("+String.valueOf(select_sat_id+1)+"/"+String.valueOf(sat_count)+")"+
				this.sat_show.getName());
		
		this.tp_nodes = DVBSatellite.loadTpNodes(sat_show.getId());
		if(this.tp_nodes == NULL)
			tp_count = 0;
		else
		tp_count = this.tp_nodes.length;
		
		select_tp_id = 0;
		this.updateTp(0);
		this.initDiseqc();
		this.initLNB();
		this.initK22();
		this.initpol();
		
		
	}
	
	private void updateTp(int diff) {
		select_tp_id = select_tp_id+diff;
		if( select_tp_id < 0) {
			select_tp_id = this.tp_count -1;
		}
		else if(select_tp_id == this.tp_count) {
			select_tp_id = 0;
		}
		
		TextView text = getValueText(TRANSPONDER_ID);
		if(this.tp_nodes == null || this.tp_count == 0) {
			text.setText(" ");
		}
		else {
		this.tp_show = this.tp_nodes[select_tp_id];
		
			if(this.tp_show.getPol()==0)
		text.setText("("+String.valueOf(select_tp_id+1)+"/"+String.valueOf(tp_count)+")"+
					this.tp_show.getFreq()+" H "+this.tp_show.getSymbol());
			else
				text.setText("("+String.valueOf(select_tp_id+1)+"/"+String.valueOf(tp_count)+")"+
				this.tp_show.getFreq()+" V "+this.tp_show.getSymbol());
			DvbSystem.LockFreq(this.tp_nodes[select_tp_id].getParentId(),this.tp_nodes[select_tp_id].getId());
		}
		
		
	}
	
	private void initLNB() {
		int lnb_type, lnb_low;
		int lnb_high;
		
		boolean flag = false;
		
		lnb_type = this.sat_show.getlnb_type();
		lnb_low = this.sat_show.getlnb_low();
		lnb_high = this.sat_show.getlnb_high();
		
		if(lnb_low == 0 || lnb_high == 0) {
			lnb_type = LNB_CTRL_STD;
			select_lnb_id = 0;
			flag = true;
		}
		else {
			if(lnb_type == LNB_CTRL_STD ) {
				for(int i = 0; i < lnb_standard_freqs.length; i++) {
					if(lnb_freqs_list[lnb_standard_freqs[i]] == lnb_low) {
						flag = true;
						select_lnb_id = i;
						break;
					}
				}
			}
			else if(lnb_type == LNB_CTRL_POL) {
				for(int i = 0; i < lnb_user_freqs.length; i++) {
					if(lnb_freqs_list[lnb_user_freqs[i][0]] == lnb_low && lnb_freqs_list[lnb_user_freqs[i][1]] == lnb_high) {
						flag = true;
						select_lnb_id = lnb_standard_freqs.length + i;
						break;
					}
				}
			}
			else if(lnb_type == LNB_CTRL_22K) {
				for(int i = 0; i < lnb_universal_freqs.length; i++) {
					if(lnb_freqs_list[lnb_universal_freqs[i][0]] == lnb_low && lnb_freqs_list[lnb_universal_freqs[i][1]] == lnb_high) {
						flag = true;
						select_lnb_id = lnb_standard_freqs.length + lnb_user_freqs.length + i;
						break;
					}
				}
			}
			else if(lnb_type == LNB_CTRL_UNICABLE) {
				for(int i = 0; i < lnb_unicable_freqs.length; i++) {
					if(lnb_freqs_list[lnb_unicable_freqs[i][0]] == lnb_low && lnb_freqs_list[lnb_unicable_freqs[i][1]] == lnb_high) {
						flag = true;
						select_lnb_id = lnb_standard_freqs.length + lnb_user_freqs.length + lnb_universal_freqs.length + i;
						break;
					}
				}
			}
		}
		
		if(flag == false) {
			lnb_type = LNB_CTRL_STD;
			select_lnb_id = 0;
		}
		updateLNB(0);
	}
	
	private void updateLNB(int diff) {
		
		select_lnb_id = select_lnb_id+diff;
		if( select_lnb_id < 0) {
			select_lnb_id = this.lnb_count -1;
		}
		else if(select_lnb_id == this.lnb_count) {
			select_lnb_id = 0;
		}
		
		int lnb_type, lnb_low, index;
		int lnb_high;
		
		if( select_lnb_id < lnb_standard_freqs.length) {
			lnb_type = LNB_CTRL_STD;
			is_k22_gray = false;
			lnb_low = lnb_high = lnb_freqs_list[lnb_standard_freqs[select_lnb_id]];
		}
		else if( select_lnb_id < lnb_standard_freqs.length + lnb_user_freqs.length) {
			index = select_lnb_id - lnb_standard_freqs.length;
			lnb_type = LNB_CTRL_POL;
			is_k22_gray = false;
			lnb_low = lnb_freqs_list[lnb_user_freqs[index][0]];
			lnb_high = lnb_freqs_list[lnb_user_freqs[index][1]];
		}
		else if(select_lnb_id < lnb_standard_freqs.length + lnb_user_freqs.length
				+ lnb_universal_freqs.length) {
			index = select_lnb_id - lnb_standard_freqs.length - lnb_user_freqs.length;
			lnb_type = LNB_CTRL_22K;
			is_k22_gray = true;
			lnb_low = lnb_freqs_list[lnb_universal_freqs[index][0]];
			lnb_high = lnb_freqs_list[lnb_universal_freqs[index][1]];
		}
		else if(select_lnb_id < this.lnb_count) {
			index = select_lnb_id - lnb_standard_freqs.length - lnb_user_freqs.length
					-lnb_universal_freqs.length;
			lnb_type = LNB_CTRL_UNICABLE;
			is_k22_gray = true;
			lnb_low = lnb_freqs_list[lnb_unicable_freqs[index][0]];
			lnb_high = lnb_freqs_list[lnb_unicable_freqs[index][1]];
		}
		else {
			select_lnb_id = 0;
			lnb_type = LNB_CTRL_STD;
			is_k22_gray = false;
			lnb_low = lnb_high = lnb_freqs_list[lnb_standard_freqs[select_lnb_id]];
		}
		
		this.sat_show.setlnb_type(lnb_type);
		this.sat_show.setlnb_freq(lnb_low, lnb_high);
		
		TextView text = getValueText(LNB_ID);
		if(lnb_type == LNB_CTRL_STD) {
			text.setText(String.valueOf(lnb_low));
		}
		else if(lnb_type == LNB_CTRL_POL) {
			text.setText(String.valueOf(lnb_low) + " - " + String.valueOf(lnb_high));
		}
		else if(lnb_type == LNB_CTRL_22K) {
			text.setText("Universal(" + String.valueOf(lnb_low) + " - " + String.valueOf(lnb_high)+")");
		}
		else if(lnb_type == LNB_CTRL_UNICABLE) {
			text.setText("Unicable(" + String.valueOf(lnb_low) + " - " + String.valueOf(lnb_high)+")");
		}
		updateK22(0);
		//DVBSatellite.updateSatellite(this.sat_show);
		
	}
	
	private void initDiseqc() {
		
		if(this.sat_show.getDiSEqCtype() == 0) 
			select_DiSEqC10_id = 0;
		else
			select_DiSEqC10_id = this.sat_show.getDiSEqCport() + 1;
		
		if(this.sat_show.getDiSEqC11type() == DISEQC11_TYPE_DISABLE) {
			select_DiSEqC11_id = 0;
		}
		else if(this.sat_show.getDiSEqC11type() == DISEQC11_TYPE_1CASCADE) {
	        int diseqc11_mode = this.sat_show.getDiSEqC11port() & 0x0C;
	        if(diseqc11_mode == 0x0C)
	        	select_DiSEqC11_id = 1 + (this.sat_show.getDiSEqC11port() & 3);
	        else
	        	select_DiSEqC11_id = 1 + this.sat_show.getDiSEqC11port();
		}
		else if(this.sat_show.getDiSEqC11type() == DISEQC11_TYPE_2CASCADE) {
			select_DiSEqC11_id = this.sat_show.getDiSEqC11port() + 13;
		}
		
		this.updateDiseqc(0);
		this.updateDiseqc11(0);
	}
	
	private void updateDiseqc(int diff) {
		select_DiSEqC10_id = select_DiSEqC10_id+diff;
		
		if(select_DiSEqC10_id < 0){
			select_DiSEqC10_id = DiSEqC10.length;
		}
		else if(select_DiSEqC10_id == DiSEqC10.length) {
			select_DiSEqC10_id = 0;
		}
		
		if(select_DiSEqC10_id == 0) {
			this.sat_show.setDiSEqC(0, 0);
		}
		else {
			this.sat_show.setDiSEqC(2, select_DiSEqC10_id);
		}
		
		TextView text = getValueText(DISEQC1_0_ID);
		
		text.setText(DiSEqC10[select_DiSEqC10_id]);
		
		DVBSatellite.updateSatellite(this.sat_show);
	}
	
	private void updateDiseqc11(int diff) {
		select_DiSEqC11_id = select_DiSEqC11_id + diff;
		
		if(select_DiSEqC11_id < 0){
			select_DiSEqC11_id = DiSEqC11.length;
		}
		else if(select_DiSEqC11_id == DiSEqC11.length) {
			select_DiSEqC11_id = 0;
		}
		
		if(select_DiSEqC11_id == 0){
			this.sat_show.setDiSEqC11(DISEQC11_TYPE_DISABLE, 0);
	    }
	    else if(select_DiSEqC11_id <=4){
	    	this.sat_show.setDiSEqC11(DISEQC11_TYPE_1CASCADE, select_DiSEqC11_id - 1);
	    }
	    else if(select_DiSEqC11_id <=8){
	    	this.sat_show.setDiSEqC11(DISEQC11_TYPE_1CASCADE, (0x04|(select_DiSEqC11_id - 5)));
	    }
	    else if(select_DiSEqC11_id <=12){
	    	this.sat_show.setDiSEqC11(DISEQC11_TYPE_1CASCADE, (0x08|(select_DiSEqC11_id - 9)));
	    }
	    else{
	    	this.sat_show.setDiSEqC11(DISEQC11_TYPE_2CASCADE, select_DiSEqC11_id - 13);
	    }
		
		TextView text = getValueText(DISEQC1_1_ID);
		
		text.setText(DiSEqC11[select_DiSEqC11_id]);
		
		DVBSatellite.updateSatellite(this.sat_show);
		
	}
	
	private void initK22() {
		select_K22_id = this.sat_show.getK22();
		if(select_lnb_id > lnb_standard_freqs.length + lnb_user_freqs.length)
			is_k22_gray = true;
		else
			is_k22_gray = false;
		updateK22(0);
	}
	
	private void updateK22(int diff) {
		if(is_k22_gray == false) {
			select_K22_id = select_K22_id + diff;
			if(select_K22_id < 0) {
				select_K22_id = 1;
			}
			else if(select_K22_id >= 2) {
				select_K22_id = 0;
			}			
		}
		else {
			select_K22_id = 2;
		}
		
		
		
		TextView text = getValueText(S22K_ID);
		
		if(select_K22_id == 0) {
			text.setText(R.string.tv_open);
		}
		else if(select_K22_id == 1) {
			text.setText(R.string.tv_off);
		}
		else if(select_K22_id == 2) {
			text.setText(R.string.tv_auto);
		}
		
		if(select_K22_id == 2) {
			this.sat_show.setK22(0);
		}
		else {
			this.sat_show.setK22(select_K22_id);
		}
		
		DVBSatellite.updateSatellite(this.sat_show);
	}
	
	private void initpol() {
		if(this.sat_show.getlnbpower() == 0) {
			select_pol_id = 3;
		}
		else {
			select_pol_id = this.sat_show.getpol();
			if(select_pol_id >= 2)
				select_pol_id = 2;
		}
		
		updatepol(0);
	}
	
	private void updatepol(int diff) {
		select_pol_id = select_pol_id + diff;
		
		if(select_pol_id < 0) {
			select_pol_id = 2;
		}
		else if(select_pol_id >= 3) {
			select_pol_id = 0;
		}
		
		
		TextView text = getValueText(POLARITY_ID);
		
		if(select_pol_id == 0) {
			text.setText(R.string.tv_auto);
		}
		else if(select_pol_id == 1) {
			text.setText("H");
		}
		else if(select_pol_id == 2) {
			text.setText("V");
		}
		else if(select_pol_id == 3) {
			text.setText(R.string.tv_off);
		}
		
		if(select_pol_id == 3) {
			this.sat_show.setlnbpower(0);
			this.sat_show.setpol(0);
		}
		else {
			this.sat_show.setlnbpower(1);
			this.sat_show.setpol(select_pol_id);
		}
		
		DVBSatellite.updateSatellite(this.sat_show);
		if(this.tp_nodes != null) {
			DvbSystem.LockFreq(this.tp_nodes[select_tp_id].getParentId(), this.tp_nodes[select_tp_id].getId());
		}
	}
	
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		
		boolean keyHandled = false;
		
		if(KeyEvent.KEYCODE_DPAD_UP == keyCode ||
				KeyEvent.KEYCODE_DPAD_DOWN == keyCode ) {
			onPressUpDown(keyCode, event);
			return true;
		}
		else if(KeyEvent.KEYCODE_DPAD_LEFT == keyCode ||
				KeyEvent.KEYCODE_DPAD_RIGHT == keyCode) {
			onPressLeftRight(keyCode, event);
			return true;
		}
		
		keyHandled = super.onKeyDown(keyCode, event);
		
		return keyHandled;
	}
	
	private void onPressUpDown(int keyCode, KeyEvent event) {
		if(is_edit == false) {
			if(KeyEvent.KEYCODE_DPAD_UP == keyCode) {
				changefucos(-1);
			}
			else if(KeyEvent.KEYCODE_DPAD_DOWN == keyCode) {
				changefucos(1);
			}
			for(int i = 0; i < item_count; i++) {
				updateView(i);
			}
		}
		else {
			
		}
	}
	
	private void onPressLeftRight(int keyCode, KeyEvent event) {
		int diff = 0;
		if(KeyEvent.KEYCODE_DPAD_LEFT == keyCode) {
			diff = -1;
		}
		else if(KeyEvent.KEYCODE_DPAD_RIGHT == keyCode) {
			diff = 1;
		}
		
		if(is_edit) {
			
		}
		else {
			if(FocusID == SATELLITE_ID) {
				this.updateSat(diff);
			}
			else if(FocusID == TRANSPONDER_ID) {
				this.updateTp(diff);
			}
			else if(FocusID == LNB_ID) {
				if(this.sat_show != null ) {
					this.updateLNB(diff);
				}
			}
			else if(FocusID == DISEQC1_0_ID) {
				if(this.sat_show != null ) {
					this.updateDiseqc(diff);
				}
			}
			else if(FocusID == DISEQC1_1_ID) {
				if(this.sat_show != null ) {
					this.updateDiseqc11(diff);
				}
			}
			else if(FocusID == S22K_ID) {
				if(this.sat_show != null ) {
					this.updateK22(diff);
				}
			}
			else if(FocusID == POLARITY_ID) {
				if(this.sat_show != null ) {
					this.updatepol(diff);
				}
			}
		}
	}
	
	private void changefucos(int diff) {
		FocusID = FocusID + diff;
		if(FocusID < 0) {
			FocusID = item_count - 1;
		}
		else if(FocusID == item_count) {
			FocusID = 0;
		}
		if(is_k22_gray == true && FocusID == S22K_ID) {
			FocusID = FocusID +diff;
		}
		
	}
	
}
