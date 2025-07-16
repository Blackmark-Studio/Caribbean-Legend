// Арчибальд Колхаун
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "¿Hay algo que necesites?";
			link.l1 = "No, nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "portroyal":
			dialog.text = "¡Ja, Monsieur de Maure!  ¡Bienvenido a Port Royal!  ¿Todavía me recuerdas?";
			link.l1 = "Hmm...Eres Calhoun, ¿no es así? ¿Henry Calhoun?";
			link.l1.go = "portroyal_1";
		break;
		
		case "portroyal_1":
			dialog.text = "Casi... Archibald Calhoun.";
			link.l1 = "Ah, perdóname, monsieur. Sí, me acuerdo. Nos encontramos en Cabo Catoche, en la bahía. Tu capitán estaba contigo también, William Paterson. Reconocí su escuadrón.";
			link.l1.go = "portroyal_2";
		break;
		
		case "portroyal_2":
			dialog.text = "¡Absolutamente correcto! Por favor, perdone a mi capitán. Siempre es grosero con las personas que no conoce. Lo has hecho excelente, asaltando el fuerte de Diego de Montoya, sobre el cual casualmente hemos afilado nuestras garras...";
			link.l1 = "Es por el bien de la justicia, debo añadir, que sin los preparativos preliminares mostrados por tu capitán, dudo mucho que hubiera podido siquiera acercarme a la entrada, mientras estaba bajo el fuego de los cañones españoles. ¿Encontró tu comandante lo que buscaba?";
			link.l1.go = "portroyal_3";
		break;
		
		case "portroyal_3":
			dialog.text = "Sí. Buscó profundamente en las casamatas bajo el fuerte, y encontró algún tipo de archivo. Estaba indescriptiblemente contento. Por cierto, si no te importa que pregunte, ¿qué te impulsó a atacar ese fuerte en la jungla?";
			link.l1 = "Después de ser derrotado por mí en Saint-Pierre, Don Diego comenzó a tramar un plan, y terminó organizando un ataque abierto a Cuba. Luego rompió el combate y escapó a las colinas hacia el continente. Bueno, decidí deshacerme de ese perro cobarde de una vez por todas, para que nunca más mancillara a los franceses.";
			link.l1.go = "portroyal_4";
		break;
		
		case "portroyal_4":
			dialog.text = "Sí, he oído bastantes cuentos legendarios sobre las heroicidades del Capitán Charles de Maure. Ahora lo he visto con mis propios ojos...";
			link.l1 = "Sí, también escuché algunas cosas sobre el valor de William Paterson. Tienes suerte de tener un capitán como él.";
			link.l1.go = "portroyal_5";
		break;
		
		case "portroyal_5":
			dialog.text = "Qué suerte la mía, es cierto. Aunque se ha convertido en un hombre tan importante estos días, un hombre de la alta sociedad, audiencias, bailes, desfiles y fiestas privadas... No se le puede sacar del palacio del gobernador cada vez que llegamos a Port Royal. De hecho, está allí de nuevo ahora mismo.\nCapitán Charles de Maure, ¿puedes hacerle un favor a un borracho escocés? ¡Únete a mi compañía y charlemos! Estoy harto de ver siempre las mismas caras, y pareces ser una buena persona para charlar. Ven a mi casa, relajémonos y tomemos un barril de excelente whisky. ¡Yo invito!";
			link.l1 = "Hm... Tentador, pero...";
			link.l1.go = "portroyal_6";
		break;
		
		case "portroyal_6":
			dialog.text = "¡Oh, detente, Capitán, tú también necesitas descansar de vez en cuando! Por cierto, tengo unos finos entremeses, directamente de la tienda del comerciante. Estoy alquilando una habitación justo encima de la tienda. Cuando sientas ganas de comer algo o beber un trago, simplemente ve por las escaleras y listo, ¡ja-ja! Conveniente, ¿no es así? ¡Vamos, vamos!";
			link.l1 = "¡Me has convencido!";
			link.l1.go = "portroyal_7";
		break;
		
		case "portroyal_7":
			dialog.text = "Estupendo. ¡Sígueme!";
			link.l1 = "...";
			link.l1.go = "portroyal_8";
		break;
		
		case "portroyal_8":
			DialogExit();
			NextDiag.CurrentNode = "portroyal_9";
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6_back", "PortRoyal_store", "goto", "goto2", "GuardOT_ArchyIntoStore", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "portroyal_9":
			LAi_SetSitType(Pchar);
			dialog.text = "¿Ves qué agradable está aquí? Agradable y frío... ¡Aquí hay unos barriles de whisky! ¡Fondo blanco, Capitán!";
			link.l1 = "¡Pues, brindemos por nuestro afortunado encuentro, y una agradable amistad!";
			link.l1.go = "portroyal_10";
		break;
		
		case "portroyal_10":
			dialog.text = "¡Encantado!... ¡Ah! Has llegado al Caribe recientemente, ¿verdad, Monsieur de Maure?";
			link.l1 = "Relativamente hace poco... o no tan poco. Realmente no sé cómo decirlo. Siento que he vivido aquí la mitad de mi vida.";
			link.l1.go = "portroyal_11";
		break;
		
		case "portroyal_11":
			dialog.text = "Oh, conozco ese sentimiento... Aunque yo mismo llevo aquí mucho tiempo. Y cuando desembarqué en esa maldita isla de la que William me salvó... Oh, sentí como si hubiera dicho adiós a la mitad de mi vida en ese lugar.";
			link.l1 = "¡Interesante! ¿Qué isla era esa?";
			link.l1.go = "portroyal_12";
		break;
		
		case "portroyal_12":
			dialog.text = "Willy es un viejo amigo mío, nos conocimos cuando aún respiraba el aire puro de Escocia... Buenos tiempos. Fui lo bastante tonto como para tener una disputa con unos malditos papistas, y el mismo Inquisidor, así que organizó un ataque contra mí. En aquel entonces era comerciante, tenía mi propio filibote.\nEh, ese maldito día mi barco fue atacado por los españoles, vestidos de piratas. Luchamos valientemente, pero ¡lograron acorralarnos como ratas! Incluso entonces, el viejo Calhoun no perdió la cabeza y saltó por la borda con un barril de agua y unas cuantas tablas.\nUsé la oscuridad y nadé lejos de mi barco, sin ser visto por los soldados. Las posibilidades de supervivencia no eran muy buenas, pero quedarse en el barco significaba no tener ninguna oportunidad. Dos días después, llegué a la costa de alguna isla desierta.\nHabía estado viviendo en el Caribe por un tiempo para entonces, y sin embargo, ¡nunca había oído hablar de ella hasta ese momento! Es pequeña y completamente deshabitada... y pasé dos años allí, que parecieron una eternidad. Aún no sé cómo logré mantener mi mente intacta.";
			link.l1 = "¿Viviste dos años en una isla deshabitada?";
			link.l1.go = "portroyal_13";
		break;
		
		case "portroyal_13":
			dialog.text = "¡Claro que sí, maldito lugar! Menos mal que había agua fresca. Me alimenté de cangrejos, percebes, peces y aves. Por eso la llamé Isla Cangrejo. No tenía ninguna arma, ¡así que dominé el arpón, la lanza y la flecha como un salvaje! ¡Oh-hoo! Bebe, bebe, capitán. No me importa mojar mi silbato también...";
			link.l1 = "Sí... No te envidio.";
			link.l1.go = "portroyal_14";
		break;
		
		case "portroyal_14":
			dialog.text = "¡Ahí lo tienes! Eso es exactamente lo que dije cuando puse el pie en la playa de ese gran trozo de arena: 'Viejo Archy, tu situación no es envidiable, ¡pero tampoco es desesperada!' ¿Y sabes qué me mantuvo con vida, capitán?";
			link.l1 = "¿Un barco pasando cerca de la isla?";
			link.l1.go = "portroyal_15";
		break;
		
		case "portroyal_15":
			dialog.text = "¡No! ¡El trabajo me salvó! ¡Trabajo, fe y un deseo de vivir! Exploré toda la isla, cada rincón de ella y fui recompensado con un cofre, lleno de herramientas de carpintero, accesorios de escritura y otras cositas. ¿Sabes qué me dije en ese momento? ¡Sirve más, capitán, sólo sirve!\nDije: Archie, debes trabajar para mantener tu mente en su lugar, y Dios te ha dado todo para empezar a hacerlo. ¿Ves ahora? Comencé a construir una casa cerca de una bahía y ¿sabes qué? ¡Me salvó de pensamientos oscuros y me dio una razón para vivir!";
			link.l1 = "Eres una inspiración viviente, Sr. Calhoun. No todos los hombres serían capaces de hacer mucho, si es que algo, en una situación como esa...";
			link.l1.go = "portroyal_16";
		break;
		
		case "portroyal_16":
			dialog.text = "¡Sí, el viejo Calhaun nació en Escocia por una razón! ¡Cierto! Somos los hijos de las montañas: fuertes, valientes y duros, mucho mejores que esos pesos pluma del pantano. Sirve más... Bien, ¿de qué estaba hablando? ¡Sí! Trabajé duro y construí una casa decente para mí. También comencé un diario para escribir diariamente sobre mis desgracias. Me llevé el diario cuando Willy me salvó.\nAhora lo guardo en esta mesa aquí y lo releo en una cama cálida y suave cada vez que nos quedamos en Port Royal.\nEscribí todo en él, todo lo que me sucedió antes y después de llegar allí. Es una de las razones por las que aún conservo mi cordura.";
			link.l1 = "¿Así que resulta que el Sr. Paterson te recogió de la isla? ¿Pero cómo pudo haberla encontrado? Dijiste...";
			link.l1.go = "portroyal_17";
		break;
		
		case "portroyal_17":
			dialog.text = "Sí, sí, la isla no está marcada en ningún mapa. ¡Pero Willy, es el viejo Willy! ¡Puede hacer cualquier cosa! Y encontró esa maldita isla y me salvó, y por eso estaré agradecido hasta el fin de mis días. Sí...";
			link.l1 = "¿Te gusta servir al señor Paterson? ¿Te gustaría ir de nuevo con tus propios recursos?";
			link.l1.go = "portroyal_18";
		break;
		
		case "portroyal_18":
			dialog.text = "Estoy harto de ser independiente. Willy es joven y exitoso, y también soy su amigo desde hace mucho tiempo. ¿Qué más necesito? No, estaré con Willy hasta el fin de mis días, o al menos hasta que me eche la próxima vez que me emborrache, ¡ja-ja! Hablando de emborracharse, ¡sírveme otra!";
			link.l1 = "Agh... (bebiendo) Dime, Sr. Calhoun. Escuché que, eh, solías ser un cazador de tesoros. ¿Es cierto o es solo un disparate?";
			link.l1.go = "portroyal_19";
		break;
		
		case "portroyal_19":
			dialog.text = "¿Quién te dijo eso? Bueno, no tiene sentido tratar de ocultarlo. Solía ser uno. Aunque no salió bien, precisamente esa búsqueda de tesoros me llevó a los malditos jesuitas y a la isla. Los santos padres torturaron a un hombre hasta la muerte por mi culpa, y yo mismo... oh, dejemos el pasado en el pasado.\nHe pagado suficiente por mis pecados y espero no repetirlos en el futuro. No, Willy no permitirá que eso suceda, ¡estoy seguro!";
			link.l1 = "Escucha, Archibald. ¿Alguna vez has oído hablar de un hombre llamado Miguel Dichoso?";
			link.l1.go = "portroyal_20";
		break;
		
		case "portroyal_20":
			dialog.text = "Jamás he oído ese nombre antes. ¿Quién es él?";
			link.l1 = "Oh, nadie interesante... solo un hombre que gusta de buscar aventuras y tesoros. Pero como no has oído hablar de él, no hablaremos de él.";
			link.l1.go = "portroyal_21";
		break;
		
		case "portroyal_21":
			dialog.text = "¡Sí, mejor no lo hagamos! ¡Hablemos de la vieja Europa en su lugar! Recuerdo hace veinte años en Escocia...";
			link.l1 = "...";
			link.l1.go = "portroyal_22";
		break;
		
		case "portroyal_22":
			DialogExit();
			AddDialogExitQuest("GuardOT_MCOutFromArchyRoom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
