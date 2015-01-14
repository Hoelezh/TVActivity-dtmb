package com.alitech.dvb;

import java.io.Serializable;


public class DvbTpNode implements Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = 2L;
	private int sat_id;
	private int freq;
	private int symbol;
	private int pol;
	
	private int tp_id;
	private String tp_name;
	
	public DvbTpNode() {
		this.tp_id = 0;
		this.tp_name = "snew";
	}

	public DvbTpNode(int id, String name, String number, int parent_id, int freq, int symbol, int pol) {
		//super(id, name, number);
		this.tp_id = id;
		this.tp_name = name;
		this.sat_id = parent_id;
		this.freq = freq;
		this.symbol = symbol;
		this.pol = pol;
	}
	
	public DvbTpNode(int parent_id) {
		// TODO Auto-generated constructor stub
		this.tp_id = 0;
		this.sat_id = parent_id;

		this.tp_name = "tpnew";

		this.freq = 0;
		this.symbol = 0;
		this.pol = 0;
	}

	public int getId() {
		return this.tp_id;
	}
	
	public int getParentId() {
		return this.sat_id;
	}
	
	public String getName() {
		return this.tp_name;
	}
	
	public void setId(int id) {
		this.tp_id = id;
	}
	
	public void setName(String name) {
		this.tp_name = name;
	}

	public int getFreq() {
		return this.freq;
	}
	
	public void setFreq(int freq) {
		this.freq = freq;
	}
	
	public int getSymbol() {
		return this.symbol;
	}
	
	public void setSymbol(int symbol) {
		this.symbol = symbol;
	}
	
	public int getPol() {
		return this.pol;
	}
	
	public void setPol(int pol) {
		this.pol = pol;
	}
}
