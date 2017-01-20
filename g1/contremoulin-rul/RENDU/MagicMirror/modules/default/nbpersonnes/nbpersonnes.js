/* global Module */

/* Magic Mirror
 * Module: HelloWorld
 *
 * By Michael Teeuw http://michaelteeuw.nl
 * MIT Licensed.
 */

Module.register("nbpersonnes",{

	// Default module config.
	defaults: {
		text : " : ",
		file : "nbpers.txt",
		fadeSpeed : 500,
		updateInterval : 1000,
	},

	// Define start sequence.
	start: function() {
		Log.info("Starting module: " + this.name);

		// Schedule update timer.
		var self = this;
		setInterval(function() {
			self.updateDom(self.config.fadeSpeed);
		}, this.config.updateInterval);
	},

	// Define required scripts.
	getStyles: function() {
		return ["font-awesome.css"];
	},

	icon: function(){
		var wrapper = document.createElement("div");
		var x = document.createElement("I");
		x.setAttribute('class', 'fa fa-male');
		x.setAttribute('aria-hidden', 'true');
		wrapper.appendChild(x);
		return x;
	},

	fichier: function(file_path){
		if(window.XMLHttpRequest) obj = new XMLHttpRequest(); //Pour Firefox, Opera,...

    		else if(window.ActiveXObject) obj = new ActiveXObject("Microsoft.XMLHTTP"); //Pour Internet Explorer 

    		else return(false);

		if (obj.overrideMimeType) obj.overrideMimeType("text/xml"); //Évite un bug de Safari

   
    		obj.open("GET", file_path, false);
    		obj.send(null);
   
    		if(obj.readyState == 4) return(obj.responseText);
    		else return(false);
	},

	file_path: function(filename){
		return this.data.path + filename;
	},

	value: function(){
		var path = this.file_path(this.config.file);
		var value = this.fichier(path);
		return value;
	},

	//Generate text with current number of persons
	print: function() {
		var text = this.config.text;
		var nbpers = this.value();
		var print = text + nbpers;
		return print;
	},

	// Override dom generator.
	getDom: function() {
		var wrapper = document.createElement("div");
		var icon = this.icon();
		var text = document.createElement("div");
		text.className = "thin bright";
		text.innerHTML = this.print();
		var clear = document.createElement("div");
		text.setAttribute('style', 'clear: both');
		wrapper.appendChild(icon);
		wrapper.appendChild(text);
		wrapper.appendChild(clear);
		return wrapper;
	}
});
