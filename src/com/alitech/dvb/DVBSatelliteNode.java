package com.alitech.dvb;


import java.io.Serializable;



public class DVBSatelliteNode implements Serializable {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private int sat_id;
	private String sat_name;
	
	private int sat_orbit;
	private boolean select_flag;
	private boolean tuner1_valid;
	private boolean tuner2_valid;
	
	private int lnb_type;
	private int lnb_low;
	private int lnb_high;
	
	private int DiSEqC_type;
	private int DiSEqC_port;
	
	private int DiSEqC11_type;
	private int DiSEqC11_port;
	
	private int lnb_power;
	private int pol;
	private int k22;
	
	
	private DvbTpNode[] children_nodes;
	
	public DVBSatelliteNode() {
		this.sat_id = 0;
		this.sat_name = "snew";
		this.sat_orbit = 0;
		this.select_flag = false;
		this.tuner1_valid = true;
		this.tuner2_valid = false;
		this. lnb_type = 0;
		this.lnb_low=5150;
		this. lnb_high=5150;
		this.DiSEqC_type=0;
		this.DiSEqC_port=0;
		this.DiSEqC11_type=0;
		this.DiSEqC11_port=0;
		this.lnb_power=1;
		this. pol=0;
		this.k22=0;
		this.children_nodes = null;
	}
	
	public DVBSatelliteNode(int satId, String name, String number, int orbit, boolean is_select, boolean tuner1_valid, boolean tuner2_valid,
			int lnb_type, int lnb_low, int lnb_high, int DiSEqC_type, int DiSEqC_port, int DiSEqC11_type, int DiSEqC11_port, int lnb_power, int pol, int k22)
	{		
		this.sat_id = satId;
		this.sat_name = name;
		
		this.sat_orbit = orbit;
		this.select_flag = is_select;
		this.tuner1_valid = tuner1_valid;
		this.tuner2_valid = tuner2_valid;
		
		this.children_nodes = null;

		this.lnb_type = lnb_type;
		this.lnb_low = lnb_low;
		this.lnb_high = lnb_high;
		
		this.DiSEqC_type = DiSEqC_type;
		this.DiSEqC_port = DiSEqC_port;
		
		this.DiSEqC11_type = DiSEqC11_type;
		this.DiSEqC11_port = DiSEqC11_port;
		
		this.lnb_power = lnb_power;
		this.pol = pol;
		this.k22 = k22;
	}
	
	
	public int getId() {
		return this.sat_id;
	}
	
	public String getName() {
		return this.sat_name;
	}
	
	public void setId(int id) {
		this.sat_id = id;
	}
	
	public void setName(String name) {
		this.sat_name = name;
	}
	
	
	public void setselect(boolean flag) {
		this.select_flag = flag;
	}
	
	public boolean isselect() {
		return this.select_flag;
	}
	
	public void settuner1(boolean flag) {
		this.tuner1_valid = flag;
	}
	
	public boolean istuner1valid() {
		return this.tuner1_valid;
	}
	
	public void settuner2(boolean flag) {
		this.tuner2_valid = flag;
	}
	
	public boolean istuner2valid() {
		return this.tuner2_valid;
	}
	
	public void setorbit(int value) {
		this.sat_orbit = value;
	}
	
	public int getorbit() {
		return this.sat_orbit;
	}
	
	public int initChildren() {
		this.children_nodes = DVBSatellite.loadTpNodes(this.getId());
		if(this.children_nodes == null)
			return 0;
		else
			return this.children_nodes.length;
	}
	
	public DvbTpNode[] getChildrenNodes() {
		//if(this.children_nodes == null)
		this.initChildren();
		return this.children_nodes;
	}
	
	public void setlnb_type(int type) {
		lnb_type = type;
	}
	
	public int getlnb_type() {
		return lnb_type;
	}
	
	public void setlnb_freq(int low, int high) {
		lnb_low = low;
		lnb_high = high;
	}
	
	public int getlnb_low() {
		return lnb_low;
	}
	
	public int getlnb_high() {
		return lnb_high;
	}
	
	public void setDiSEqC(int type, int port) {
		DiSEqC_type = type;
		DiSEqC_port = port;
	}
	
	public void setDiSEqC11(int type, int port) {
		DiSEqC11_type = type;
		DiSEqC11_port = port;
	}
	
	public int getDiSEqCtype() {
		return DiSEqC_type;
	}
	
	public int getDiSEqCport() {
		return DiSEqC_port;
	}
	
	public int getDiSEqC11type() {
		return DiSEqC11_type;
	}
	
	public int getDiSEqC11port() {
		return DiSEqC11_port;
	}
	
	public void setK22(int value) {
		k22 = value;
	}
	
	public int getK22() {
		return k22;
	}
	
	public void setpol(int value) {
		pol = value;
	}
	
	public int getpol() {
		return pol;
	}
	
	public void setlnbpower(int value) {
		lnb_power = value;
	}
	
	public int getlnbpower() {
		return lnb_power;
	}
}
