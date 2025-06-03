int questShips[50];
int questShipsNum = 0;

extern void InitGunExt(string id,			
				string sAttr,       
				string sBullet,     
				string sGunPowder,  
				float  DmgMin_NC,   
				float  DmgMax_NC,   
				float  DmgMin_C,    
				float  DmgMax_C,    
				float  EnergyP_NC,  
				float  EnergyP_C,   
				bool   Stun_NC,     
				bool   Stun_C,      
				bool   MultiDamage, 
				int    MisFire,     
				bool   SelfDamage,  
				bool   Explosion,   
				float  Accuracy,    
				int    ChargeSpeed, 
				bool   isDefault );

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp, attr, companion;
	ref chref;
	int iTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string node = Dialog.CurrentNode;
	if(HasSubStr(node, "joruba_p3_ship_")) {
		iTemp = findsubstr(node, "joruba_p3_ship_", 0);
	 	companion = strcut(node, iTemp + strlen("joruba_p3_ship_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p3";
	}
	
	if(HasSubStr(node, "joruba_p4_off_")) {
		iTemp = findsubstr(node, "joruba_p4_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_p4_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p4_off";
	}

	if(HasSubStr(node, "joruba_o6_off_")) {
		iTemp = findsubstr(node, "joruba_o6_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_o6_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_o6_off";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "No se supone que debas ver esto.";
			link.l1 = "Hora de presentar un informe de error.";
			link.l1.go = "exit";
		break;
		
        case "native":
			dialog.text = "¡Uy! Ta'kahi, joven. No quiero ser grosero, pero ¿cómo entraste aquí? Le recomendé encarecidamente a Madame que cerrara el establecimiento durante mi estadía.";
			link.l1 = "Vaya, en verdad. ¿Cómo te dejaron entrar? ¿Por qué este burdel no ha sido ya quemado por gente temerosa de Dios?";
			link.l1.go = "native_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Panama");
		break;
		
        case "native_1":
			dialog.text = "Doblones de oro abren todos los caminos y hacen más felices a los blancos. ¿No lo sabrías?";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text+" Puedo percibir el casi desgastado aroma de Versalles, donde te dejaron entrar con tal chirrido.";
			}
			link.l1 = "No me hables así, cara roja. Es cierto que soy nuevo aquí, aunque no sé cómo te enteraste. Podría dispararte justo donde estás y conseguir a cualquier chica para la noche para compensar el inconveniente.";
			link.l1.go = "native_var1";
			link.l2 = "No sé quién te dijo esas tonterías, pero hablas bastante fluido, te lo concedo. Es la primera vez que veo a un nativo tan educado.";
			if (HasSubStr(pchar.model, "Sharle")) {
				link.l2 = link.l2+"¡Versalles, mis cojones!";
			}
			link.l2.go = "native_var2";
		break;
		
        case "native_var1":
			dialog.text = "No, Capitán, no sabes nada. Estoy perfectamente seguro aquí... por ahora. Sin embargo, ya que nos hemos familiarizado tan rápido, intentemos de nuevo. ¿Bebida?";
			link.l1 = "Puedo hacer eso, definitivamente has despertado mi interés.";
			link.l1.go = "native_play";
		break;
		
        case "native_var2":
			dialog.text = "¡Bravo! Veo que ya nos tuteamos e intercambiamos pullas. Ahora sugiero que brindemos por la paz y hablemos de negocios.";
			link.l1 = "Puedo hacer eso, definitivamente has despertado mi interés.";
			link.l1.go = "native_play";
		break;
		
        case "native_play":
			dialog.text = "¡Considerando el propósito del lugar, tu comentario, Capitán, me preocupa bastante! He estado atrapado aquí casi un mes. He intentado todo lo que se me ocurre, y estoy listo para trepar por la pared de aburrimiento e inutilidad.";
			link.l1 = "Entonces vete. Visita una iglesia por variar... a la que no te dejarán entrar.";
			link.l1.go = "native_play_1";
		break;
		
        case "native_play_1":
			dialog.text = "No es tan simple, ya que estoy obligado a pasar otras veinticuatro horas en este burdel, según mi... contrato.";
			link.l1 = "Suena horrible, por supuesto, pero no conseguirás simpatía de mi parte. ¡Un alquiler exclusivo de burdel por un mes es un sueño hecho realidad!";
			link.l1.go = "native_play_2";
		break;
		
        case "native_play_2":
			dialog.text = "Teme tus deseos, Capitán. No sé cómo llegaste aquí, porque se suponía que iba a pasar este mes solo. Solo con la india y el vino, pero solo pude aguantar con el vino hasta el tercer día o algo así. Y hoy fue el día en que me harté de eso también.";
			link.l1 = "¿Y qué quieres que haga? ¿Compartir un montón de chicas y vino contigo?";
			link.l1.go = "native_play_3";
		break;
		
        case "native_play_3":
			dialog.text = "Tal vez, ¡pero sugiero que apostemos primero! ¡Mil de plata por carta! Por cierto, mi nombre es Agueybana.";
			link.l1 = "Mía es "+GetFullName(pchar)+". Claro, juguemos.";
			link.l1.go = "native_accept";
			link.l2 = "El mío es "+GetFullName(pchar)+". ¿Mil pesos? No está mal. Lo pensaré, pero no prometo nada.";
			link.l2.go = "native_decline";
		break;
		
        case "native_play_again":
			dialog.text = "¿Has cambiado de opinión, capitán? ¿Vamos?";
			link.l1 = "Claro, ¿por qué demonios no?";
			link.l1.go = "native_accept";
			link.l2 = "Aún no.";
			link.l2.go = "native_decline";
		break;
		
        case "native_decline":
			DialogExit();
			
			NextDiag.CurrentNode = "native_play_again";
		break;
		
        case "native_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1");
		break;
		
        case "native_cards_loss":
			dialog.text = "Gracias por el juego, capitán. Pensé que me haría sentir mejor, pero no fue así. Por favor, déjame en paz - de alguna manera me las arreglaré solo otro día. ¡Maldito sea ese bastardo!";
			link.l1 = "¿Eso es todo? Admito que mi decepción es mayor que la amargura de perder un montón de dinero.";
			link.l1.go = "native_cards_loss_1";
		break;
		
        case "native_cards_loss_1":
			dialog.text = "Tú ni siquiera deberías estar aquí, capitán. Pero si anhelas descubrir de qué se trataba todo esto... busca un templo antiguo en el continente. Y trae mucho tuunich kaane'. Aquí, toma uno.";
			link.l1 = "¿Una piedra de serpiente? Una piedra con un agujero definitivamente encaja en el lugar. Gracias, Agueybana";
			link.l1.go = "native_cards_loss_2";
		break;
		
        case "native_cards_loss_2":
			dialog.text = "Adiós, capitán.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game1LossGoAway");
		break;
		
        case "native_cards_win":
			dialog.text = "¡Uy! ¡Gracias, capitán! Una pena lo del dinero, pero al menos he vuelto a saborear la vida.";
			link.l1 = "Sí, es la primera vez que veo a alguien emocionarse tanto por una ruta como esta. ¿De dónde sacaste todo ese dinero, por cierto?";
			link.l1.go = "native_cards_win_1";
		break;
		
        case "native_cards_win_1":
			dialog.text = "¡Una pregunta grosera que nunca le harías a tu igual, capitán! Pero la noche aún es joven, y me queda una buena cantidad de monedas. ¿Qué tal una revancha?";
			link.l1 = "¿Por qué demonios no? ¡Hagamos otro!";
			link.l1.go = "native_cards_win_2";
		break;
		
        case "native_cards_win_2":
			dialog.text = "Sugiero que esta vez juguemos a los dados y subamos un poco las apuestas. También tengo una historia que contarte, así que por favor alquila una habitación arriba para ambos. ¡Demasiados oídos aquí! Te agradecería que fueras a Madame y pagaras la habitación. Mi crédito, desafortunadamente, no se aplica a ti.";
			link.l1 = "¿Alquilar una habitación? ¿Para dos? ¿Aquí? ¡Que te jodan, Agueybana! ¡Me largo de aquí!";
			link.l1.go = "native_cards_rematch_decline";
			link.l2 = "Oh, qué demonios. Esta historia terminará o como una buena anécdota o como un baño de sangre muy caro. Mi espada se queda conmigo, así que nada de bromas, ¡ja-ja! Espera aquí, lo resolveré.";
			link.l2.go = "native_cards_rematch_accept";
		break;
		
        case "native_cards_rematch_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinNoRematch");
		break;
		
        case "native_cards_rematch_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinRematch");
		break;
		
        case "native_dice":
			dialog.text = "¿Entonces?";
			link.l1 = "Espero sinceramente que me hayas llamado aquí solo para beber y apostar.";
			link.l1.go = "native_dice_1";
		break;
		
        case "native_dice_1":
			dialog.text = "No te preocupes, capitán, ¡no me interesan esas tonterías! Aunque, si hubieras aparecido aquí el primer día... ¡ja ja! ¿Empezamos?";
			link.l1 = "¡La fortuna favorece a los valientes!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game2");
		break;
		
        case "native_dice_win":
			dialog.text = "¡Uy! ¡Eso se siente bien! Felicitaciones por tu victoria, Capitán.";
			link.l1 = "No te excedas. ¿Es hora de que me ilumines sobre qué demonios está pasando aquí?";
			link.l1.go = "native_dice_story";
			link.l2 = "Eres raro, Agueybana. Ahora, si no salgo de este lugar de inmediato, mi reputación como noble y como hombre se verá irremediablemente dañada. Dame mi plata y separemos nuestros caminos.";
			link.l2.go = "native_dice_win_not_story";
		break;
		
        case "native_dice_loss":
			dialog.text = "Qué lástima, esperaba terminar el día de otra manera...";
			link.l1 = "Es la primera vez que veo a un hombre tan molesto por ganar este juego plebeyo. ¿Puedes al menos iluminarme ahora sobre qué diablos está pasando aquí?!";
			link.l1.go = "native_dice_story";
			link.l2 = "¡Que te jodan, Agueybana! ¡Ya tuve suficiente de esto!";
			link.l2.go = "native_dice_loss_not_story";
		break;
		
        case "native_dice_story":
			dialog.text = "Todo lo que pueda, capitán. No estoy seguro de que me esté permitido, pero aun así, has alegrado mis últimos días... En este burdel, quiero decir.";
			link.l1 = "¿Y de qué se trataba esto?";
			link.l1.go = "native_dice_story_1";
		break;
		
        case "native_dice_story_1":
			dialog.text = "Olvídalo... ¡Escucha aquí, hombre blanco! Soy el gran jefe del pueblo taíno, Agueybana. ¡A veces sueño que nací cien años antes y expulsé a los invasores españoles de mis islas! Pero en cambio vendí a tres mil de mis tribus para las minas por diez doblones cada uno.";
			link.l1 = "Una biografía digna. Tengo un repentino impulso de pegarte un tiro, Agueybana, y dejarte pudrirte en este hediondo agujero con olor a vino agrio.";
			link.l1.go = "native_dice_story_2";
		break;
		
        case "native_dice_story_2":
			dialog.text = "Lo que sea, capitán. Todo lo que siempre quise fue ser como usted.";
			link.l1 = "¿Como yo?";
			link.l1.go = "native_dice_story_3";
		break;
		
        case "native_dice_story_3":
			dialog.text = "He visto tus barcos, maravillas del ingenio humano, y he deseado tener uno para mí. He visto a tus mujeres en corsés apretados, y he soñado con quitarle uno a una mía. He observado incluso a los peores de tus comandantes ejercer un poder más allá de los sueños de cualquiera de nuestros líderes. He oído historias sobre Europa y las enormes casas de piedra donde la gente vive en lugar de sobrevivir. ¡Y lo he tenido todo! Además, ¡incluso he estado en Europa y todo eso en el último año!";
			link.l1 = "Has bebido demasiado vino, jefe. Los únicos boletos a Europa para ti serían cadenas, para deleite del Vaticano y los artistas callejeros. Lo que dices es simplemente imposible en el mundo en que vivimos.";
			link.l1.go = "native_dice_story_4";
		break;
		
        case "native_dice_story_4":
			dialog.text = "Este es el mundo en el que vivimos, capitán. Ya me han explicado que nuestro mundo es erróneo, imaginario, y que todo es posible.";
			link.l1 = "¿Y quién fue el listillo que te dijo eso? ¡Aparentemente, no solo te dejan entrar a burdeles, sino también a manicomios!";
			link.l1.go = "native_dice_story_5";
		break;
		
        case "native_dice_story_5":
			dialog.text = "Ahora llegamos al punto de mi historia. Sabes cómo funcionan las cosas aquí, ¿verdad? Los españoles e ingleses pagan por nuestros prisioneros de guerra con armas, herramientas y pólvora. Yo pagué por mis compañeros de tribu con tu dinero. ¿Por qué crees que es así?";
			link.l1 = "Siento que estás a punto de iluminarme.";
			link.l1.go = "native_dice_story_6";
		break;
		
        case "native_dice_story_6":
			dialog.text = "Solo los dioses pueden cumplir nuestros deseos más profundos y vergonzosos. Si no puedes vivir la vida que deseas, entonces pídeles que interfieran con el destino. Solo ellos pueden cumplir nuestros deseos más profundos y vergonzosos. Este es el camino. Pero aquí está el problema: casi todos nuestros dioses ya están muertos, y aunque no lo estuvieran, nunca estuvieron interesados en el oro de todos modos. Afortunadamente, la naturaleza aborrece el vacío, y un nuevo dios ha aparecido en una de las viejas pirámides. A él no le importa si eres de aquí o de la vieja europa, villano o héroe, solo paga y obtendrás lo que pediste. Todas las tribus lo saben, y algunos de los tuyos también. He pagado el precio en oro y he vivido como uno de ustedes. Mañana será un año.";
			link.l1 = "¿Qué dios? ¿A Europa y de regreso en un año? ¿Y el punto culminante de tu viaje fue algún burdel de mala muerte en el Caribe? Oh, qué demonios. Suena como el cuento de un borracho, y lo compraré como tal. Vamos a tomar un trago y continuar con tu historia.";
			link.l1.go = "native_dice_story_7";
		break;
		
        case "native_dice_story_7":
			dialog.text = "Todo lo que te he dicho es la verdad. No hay nada más que contar.";
			link.l1 = "No has vivido en nuestro mundo lo suficiente, Agueybana. Cada fábula inspirada en el alcohol, especialmente una contada borracho en un burdel, debe terminar con una moraleja. Definitivamente deberíamos filosofar antes de terminar nuestro salón adecuadamente.";
			link.l1.go = "native_dice_story_8";
		break;
		
        case "native_dice_story_8":
			dialog.text = "¿Cómo suelen terminar?";
			link.l1 = "¿No lo sabes? ¡Depende del género del participante, por supuesto! Pelea a puñetazos con los hombres, lleva a las mujeres a la cama. Aunque a veces la moda dicta lo contrario. Entonces, ¿cuál es la moraleja de tu fábula? ¿El dinero no compra la felicidad? ¡Aburrido!";
			link.l1.go = "native_dice_story_9";
		break;
		
        case "native_dice_story_9":
			dialog.text = "Esa no es la moraleja de mi fábula, como tú lo dices. Pero ya que lo mencionaste, siento la necesidad de decir que no estoy de acuerdo con tu punto. Al contrario, creo que el dinero compra la felicidad y mejora a las personas.";
			link.l1 = "¡Tonterías! Pareces estar contradiciéndote ahora. Acumulaste una fortuna considerable a través del comercio de tu propia gente. ¿Recuerdas la cantidad total de la que te beneficiaste? ¿Casi treinta mil monedas de oro? Tómate un momento para reflexionar, pero me queda claro que el dinero no te compró la felicidad. Aunque sí te compró esta bonita suite.";
			link.l1.go = "native_dice_story_10";
		break;
		
        case "native_dice_story_10":
			dialog.text = "Está bien, ajustaré mi punto inicial: el dinero mejora la vida y a las personas.";
			link.l1 = "Eso es mejor, pero ¿qué te hace pensar que hace a la gente mejor? ¿Así que ahora eres un modelo de virtud? ¿Y qué hay de aquellos que no tienen mucho dinero? ¿Vamos a etiquetarlos como malas personas?";
			link.l1.go = "native_dice_story_11";
		break;
		
        case "native_dice_story_11":
			dialog.text = "Sabes, capitán, realmente aprecio esta conversación. Permíteme ajustar de nuevo: el dinero mejora la vida y a las personas, pero solo a aquellos que ya poseen una chispa de virtud.";
			link.l1 = "¡Oíd, oíd! Entonces, ¿no hay chispa para ti, eh?";
			link.l1.go = "native_dice_story_12";
		break;
		
        case "native_dice_story_12":
			dialog.text = "No. Yo era el jefe de mi gente y, a diferencia del dinero, el poder definitivamente corrompe a los hombres. ¿Sabes qué, capitán? Te miro ahora y me doy cuenta de que enfrentarás el mismo dilema algún día.";
			link.l1 = "¿Tu ídolo también te ha bendecido con el don de la videncia? Entonces deberías ir a Santiago, he oíd"+GetSexPhrase("o","a")+" que allí tienen un interés especial por los médiums y adivinos.";
			link.l1.go = "native_dice_story_13";
		break;
		
        case "native_dice_story_13":
			dialog.text = "Terminemos nuestro... ejem, salón sin peleas ni camas, por favor. No logré sacar una moraleja de mi historia, así que me gustaría proponer un brindis en su lugar.";
			link.l1 = "Estás completamente perdido, jefe. Pero en una cosa tienes razón. ¡Mejor bebamos!";
			link.l1.go = "native_dice_story_14";
		break;
		
        case "native_dice_story_14":
			dialog.text = "Que lo que queremos siempre coincida con lo que necesitamos. Gracias, Capitán, es un final apropiado para... nuestra velada. Si deseas probar la veracidad de mi fábula algún día, ve al continente y encuentra un templo antiguo allí. Lleva contigo ciento trece tuunich kaane'. Me quedan noventa y nueve - llévalos y ¡adiós!";
			link.l1 = "¿Un montón de piedras con agujeros? Encaja bien con el lugar. Gracias por la velada, Agueybana. ¿Nos vemos de nuevo?";
			link.l1.go = "native_dice_story_15";
		break;
		
        case "native_dice_story_15":
			dialog.text = "No, no lo harás. Adiós, capitán.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_BuyAmulets");
		break;
		
        case "native_dice_win_not_story":
			dialog.text = "Entiendo, capitán. Para bien o para mal, te daré una pista sobre el tesoro. Después de todo, has iluminado mis últimos días... En este burdel, quiero decir. Busca un templo antiguo en la gran tierra y trae una pila de tuunich kaane'. Aquí, toma uno.";
			link.l1 = "¿Una piedra de víbora? Qué encantador, y una piedra con un agujero definitivamente encaja con el lugar. ¡Ya tuve suficiente de tu trato!";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_loss_not_story":
			dialog.text = "Entiendo que estás enfadado, capitán. Para bien o para mal, te daré una pista sobre el tesoro. Después de todo, has alegrado mis últimos días... En este burdel, quiero decir. Busca un antiguo templo en la gran tierra y trae un montón de tuunich kaane'. Aquí, toma uno.";
			link.l1 = "¿Una piedra de víbora? Qué encantador y una piedra con un agujero definitivamente encaja con el lugar. ¡He tenido suficiente de tu trato!";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_not_story":
			dialog.text = "Adiós, capitán.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotBuyAmulets");
		break;
		
		case "joruba":
			dialog.text = "¿Otro más? ¡Por la puta madre, estoy tan harto de todos vosotros!";
			link.l1 = "¡A-a-ah! ¡Fuera!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_1";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_1":
			dialog.text = "¿Eh? Sí, correcto. ¡Inclínate ante mí, mortal! ¡Contempla el poder de mi pirámide!";
			link.l1 = "(grito desesperado)";
			link.l1.go = "joruba_2";
			link.l2 = "(mata al monstruo)";
			link.l2.go = "joruba_3";
		break;
		
		case "joruba_2":
			dialog.text = "Así es. Bienvenido a mi humilde factoría, capitán.";
			link.l1 = "¿Q-qué eres tú?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_3":
			DialogExit();
			
			NextDiag.CurrentNode = "joruba_3_next";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_3_next":
			dialog.text = "Te felicito por tu persistencia. ¿Cuál es tu próximo movimiento, capitán? ¿Qué opinas de hacer un poco de comercio?";
			link.l1 = "¿Q-qué eres tú?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_4":
			dialog.text = "No importa lo que soy, lo que importa es la función que desempeño. En este momento, estoy realizando acuerdos comerciales con los habitantes de este agujero de ratas para beneficio mutuo.";
			link.l1 = "¿El agujero de ratas? ¿Te refieres a este templo?";
			link.l1.go = "joruba_6";
			
			AddDialogExitQuestFunction("ChickenGod_JorubaToNormal");
		break;
		
		case "joruba_6":
			dialog.text = "¡Tu primera y última advertencia, capitán! Sin embargo, esta pirámide es, de hecho, algo estrecha, obviamente la he superado.";
			link.l1 = "Has dicho algo sobre el comercio. ¿De qué tipo de comercio estás hablando?";
			if (CheckAttribute(pchar, "questTemp.ChickenGod.SawJoruba")) {
				link.l1.go = "joruba_7A";
			} else {
				link.l1.go = "joruba_7";
			}
		break;
		
		case "joruba_7":
			dialog.text = "Doy lo que la gente más necesita.";
			link.l1 = "¿Concedes deseos? ¿Como un genio de un cuento de hadas? ¡Santo cielo, ¿qué está pasando aquí?!";
			link.l1.go = "joruba_7_1";
		break;
		
		case "joruba_7_1":
			dialog.text = "¡No seas absurdo! Solo ayudo a la gente a conseguir lo que vinieron a buscar a este mundo de la manera más rápida y placentera.";
			link.l1 = "¿Eres un chamán o algo así?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_7A":
			dialog.text = "Bueno, conociste a Agueybana, eso debería darte algunas ideas.";
			link.l1 = "¿Ese pobre, perdido y borracho indio fue obra tuya?";
			link.l1.go = "joruba_7A_1";
		break;
		
		case "joruba_7A_1":
			dialog.text = "No fui yo quien vendió a su tribu por un par de miles de libras de oro, no fui yo quien le vertió barriles de licor por la garganta, y ciertamente no le obligué a recoger todas las enfermedades, conocidas y desconocidas, de cientos de prostitutas. Me pidió que lo convirtiera en un aristócrata blanco, así que lo hice. Como su destino me lo ordenó.";
			link.l1 = "¿Concedes deseos? ¿Como un genio de un cuento de hadas? ¡Santo Dios, ¿qué está pasando aquí?!";
			link.l1.go = "joruba_7A_2";
		break;
		
		case "joruba_7A_2":
			dialog.text = "¡No seas absurdo! Solo ayudo a la gente a obtener para qué vinieron a este mundo de la manera más rápida y placentera. Agueybana se suponía que debía salvar a su gente del yugo de los invasores europeos, pero en cambio babeó demasiado por el corsé de la hija del comandante y decidió empeñar el suyo propio.\nDesde entonces, el único significado que le quedaba en su vida era darse cuenta de la profundidad de su error y empezar de nuevo pronto. Un año en Europa, cirrosis y el tiempo que pasaron ustedes dos en un burdel debieron de ayudar. Pero debo admitir, tuvo unas grandes vacaciones, ¡ja ja!";
			link.l1 = "¿Cirrho qué? ¿Eres un chamán o algo así?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_8":
			dialog.text = "O algo así. Sin embargo, te gustará mi oferta. Y, para variar, estaré genuinamente feliz de ayudar.";
			link.l1 = "Correcto. ¿Cuánto?";
			link.l1.go = "joruba_9A";
			link.l2 = "¿Por qué? ¿Soy especial?";
			link.l2.go = "joruba_9B";
		break;
		
		case "joruba_9A":
			dialog.text = "No está tan mal, capitán. O eres listo o eres tan tonto como un burro, pero tus probabilidades acaban de mejorar un poco. El precio no será un problema.";
			link.l1 = "¿Necesitas matar a alguien? No hago eso.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_9B":
			dialog.text = "Porque tu propósito en esta vida es hacer agujeros en un buen amigo mío, ¡ja ja!";
			link.l1 = "¿Necesitas matar a alguien? Yo no hago eso.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_10":
			dialog.text = "Primero, tú lo haces. Segundo, llevaremos a cabo cuatro transacciones importantes y otras cuatro más pequeñas. Cada una te hará mucho más fuerte y aumentará tus posibilidades en este mundo cruel y extraño. Si completas cada trato, te garantizo que un día podrás salir y luchar contra los dioses en igualdad de condiciones, por no hablar de los mortales comunes.";
			link.l1 = "Suena divertido. Cuéntamelo.";
			link.l1.go = "joruba_11";
		break;
		
		case "joruba_11":
			dialog.text = "¡Buena elección! Por lo general, mis discursos llevan a que la gente sea llevada a Blueweld con un presunto ataque al corazón, pero te estás manteniendo bastante bien. Aquí tienes la lista de tareas: pequeños recados de índole comercial que espero que hagas. Sin plazos, jeje.";
			link.l1 = "Curioso. Leeré la lista más tarde. ¿Algo más?";
			link.l1.go = "joruba_12";
		break;
		
		case "joruba_12":
			dialog.text = "Sí, la primera transacción importante. Dos mil doblones es el precio.";
			link.l1 = "Quizás acepte... ¡Pero eso es mucho dinero! ¿Por qué necesitas tanto? ¿Puedo pagar en pesos?";
			link.l1.go = "joruba_13";
			link.l2 = "¿Estás loco? ¡Puedo comprar una fragata con ese dinero!";
			link.l2.go = "joruba_insult";
		break;
		
		case "joruba_13":
			dialog.text = "La pirámide necesita reparaciones - la mampostería a veces cae sobre las cabezas de los clientes y eso es malo para el negocio. Mis hombres la reparan todos los días, pero nuestra organización necesita una inyección urgente de dinero desde fuera para solucionar la situación de una vez por todas. En cuanto a los pesos, no me atraen mucho, ya que su tasa de cambio es bastante volátil.";
			link.l1 = "Estás siendo injusto con los honestos pesos... Espera un momento, ¿no estás solo aquí?";
			link.l1.go = "joruba_14";
		break;
		
		case "joruba_14":
			dialog.text = "No, soy la fachada de una organización seria. Entonces, ¿estás dentro?";
			link.l1 = "Lo pensaré, pero primero, me gustaría saber qué estoy obteniendo por tan fuerte suma.";
			link.l1.go = "joruba_15";
		break;
		
		case "joruba_15":
			dialog.text = "¿Por qué arruinar la sorpresa? Además, solo trata ese dinero como un impuesto. Tu adquisición más valiosa será desbloquear los próximos tratos. Las recompensas serán divinas. Únicas también, tenlo en cuenta, ¡ya que no las encontrarás en ningún otro lugar!";
			link.l1 = "Está bien. ¿Cómo te llamas otra vez?";
			link.l1.go = "joruba_16";
		break;
		
		case "joruba_16":
			dialog.text = "Aruba la Magnífica. Una última cosa, "+pchar.name+", la entrada a la pirámide está permitida solo una vez al día. No retrases a otros clientes y no me molestes por nada.";
			link.l1 = "No veo a la fila formarse... Adiós, su majestad.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			AddDialogExitQuestFunction("ChickenGod_GiveFirstTask");
		break;
		
		case "joruba_wait":
			dialog.text = "Ahoy, capitán. ¿Qué tienes para mí?";
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1.Completed") && PCharDublonsTotal() >= 2000) {
				link.p1 = "Aquí están tus doblones. ¡Ya es bastante difícil cargar con ese maldito metal... pero es aún más difícil desprenderse de él!";
				link.p1.go = "joruba_p1";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2.Completed") && GetCharacterItem(pchar, "cannabis7") >= 15) {
				link.p2 = "Cumplí mi parte del trato. Aquí está tu hierba, Aruba.";
				link.p2.go = "joruba_p2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3.Completed") && ChickenGod_FindQuestShips()) {
				for (i = 0; i < questShipsNum; i++) {
					sTemp = "p3_" + (i + 1);
				
					chref = GetCharacter(questShips[i]);
					sld = GetRealShip(sti(chref.ship.type));
					link.(sTemp) = "¡Aruba, a la vista! ¡" + GetStrSmallRegister(XI_ConvertString(sld.BaseName)) + " '" + chref.Ship.Name + "' es todo tuyo!";
					link.(sTemp).go = "joruba_p3_ship_" + questShips[i];
					if (FindCompanionShips(SHIP_PINK) && sti(pchar.questTemp.ChickenGod.Tasks.Schyot) <= 1 && startHeroType != 4)
					{
						link.(sTemp) = "¡Aruba, a la vista! ¡El Pink '" + chref.Ship.Name + "' es todo tuyo!";
						link.(sTemp).go = "joruba_p3_PinkOtkaz";
					}
					/*if (FindCompanionShips(SHIP_GALEON_SM))
					{
						link.(sTemp) = "¡Ahoy Aruba! ¡El galeón '" + chref.Ship.Name + "' es todo tuyo!";
						link.(sTemp).go = "joruba_p3_HolyMercy";
					}*/
				}
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.p3 = "Estoy dispuesto a hacer un sacrificio.";
				link.p3.go = "joruba_p4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Lady") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Completed")) {
				link.o2 = "Le traigo una novia y problemas con las autoridades españolas, señor. La dama está paseando fuera, bien protegida por mis hombres. No os la entregaré hasta que me convenzáis de la nobleza de vuestras intenciones.";
				link.o2.go = "joruba_o2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3.Completed") && GetCharacterFreeItem(pchar, "cirass4") >= 1) {
				link.o3 = "Aquí está tu armadura, Aruba. Asegúrate de que mi recompensa te compense.";
				link.o3.go = "joruba_o3";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4.Completed") && GetPrisonerQty() >= 30) {
				link.o4 = "Tengo los prisioneros que pediste.";
				link.o4.go = "joruba_o4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5.Completed") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.p2 = "Te traje tu basura. Toma, ciento trece piedras, como me pediste.";
				link.p2.go = "joruba_o5";
			}
			
			bOk = (PCharDublonsTotal() >= 25000) || (ChickenGod_HaveOfficers());
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.Completed") && bOk) {
				link.p3 = "Estoy dispuesto a hacer un sacrificio.";
				link.p3.go = "joruba_o6";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.respec = "(Redistribuir características del personaje)";
				link.respec.go = "joruba_respec";
			}
			
			link.exit = "Solo estoy de paso.";
			link.exit.go = "joruba_wait_1";
			
			NextDiag.TempNode = "joruba_wait";
		break;
		
		case "joruba_wait_1":
			dialog.text = "La próxima vez entonces.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "joruba_p1":
			dialog.text = "No está mal, le daré buen uso a ese oro. Aquí tienes, una pequeña chuchería que perteneció a un muy virtuoso jefe taíno. Ayuda a llevar montones de oro. Ciertamente le ayudó a él, je-je...";
			link.l1 = "Gracias y espero no arrepentirme. ¿Cuál es el siguiente trato?";
			link.l1.go = "joruba_p1_1";
			link.l2 = "Espera un minuto. ¿Te di un montón de oro y recibí un trozo de arcilla a cambio? ¡Pues, necesito un reembolso!";
			link.l2.go = "joruba_insult";
			
			RemoveDublonsFromPCharTotal(2000);
			pchar.questTemp.ChickenGod.Gold = 2000;
			
			pchar.questTemp.ChickenGod.Tasks.p1.Completed = true;
			GiveItem2Character(pchar, "talisman13");
			//Log_info("You received Taino Figurine");
			PlaySound("interface\important_item.wav");
		break;
		
		case "joruba_p1_1":
			dialog.text = "¿Eh? Aye, el próximo trato. Este oro debería ser suficiente por ahora, así que es hora de considerar más mercancías espirituales. Tengo que encontrarme una cura.";
			link.l1 = "¿Por qué, estás enfermo?";
			link.l1.go = "joruba_p1_2";
		break;
		
		case "joruba_p1_2":
			dialog.text = "Mi alma lo es. Verás, los sacerdotes evitan mi humilde pirámide desde aquel incidente con la Inquisición, así que tenemos que depender de métodos más tradicionales. Necesito, bueno, mi factoría necesita quince plantas de magarosa para seguir operativa.";
			if (!ChickenGod_TalkedToAmelia()) {
				link.l1 = "¿Es eso una hierba?";
			} else {
				link.l1 = "Yo sé qué es, je-je.";
			}
			link.l1.go = "joruba_p1_3";
		break;
		
		case "joruba_p1_3":
			dialog.text = "Seré honesto - es una hierba rara de gran valor. ¿Piensa cuidadosamente si realmente va a pasar años recolectándola por todo el archipiélago?";
			link.l1 = "Sin promesas, pero te deseo buena salud y espero que mi recompensa por la hierba valga la pena.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveSecondTask");
		break;
		
		case "joruba_p2":
			dialog.text = "¡Muy bien, oficialmente declaro que este es mi día libre! Un trato como este vale un verdadero tesoro. ¡Mira!\n¡Este machete estuvo una vez así de cerca de aplastar la cabeza de ese imbécil de Kanek! Por lo tanto, es muy querido para mí y humildemente te pido que lo cuides bien. Es viejo, pero está extremadamente bien forjado, ya no hacen acero como este.";
			link.l1 = "¿Kanek? ¿Quién es ese?";
			link.l1.go = "joruba_p2_1";
			
			TakeNItems(pchar, "cannabis7", -15);
			pchar.questTemp.ChickenGod.Tasks.p2.Completed = true;
			if (pchar.rank >= 21)
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 80.0;
			}
			else
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 60.0;
			}
			GiveItem2Character(pchar, "machete2");
			//Log_info("You received Machete Conquistador");
			PlaySound("interface\important_item.wav");
			SetAlchemyRecipeKnown("bullet_double");
			SetAlchemyRecipeKnown("grapeshot_double");
			ChickenGod_InitAmmo();
		break;
		
		case "joruba_p2_1":
			dialog.text = "Oh, vosotros dos os encontraréis. Ahora, espero que no seas uno de esos pomposos imbéciles que desprecian el trabajo manual. Si es así, estás jodido, porque la segunda parte de la recompensa son los planos de la munición de doble carga.";
			if (pchar.HeroParam.HeroType == "HeroType_4") {
				link.l1 = "Oh, me encantan esos. Pero, ¿qué tienen de único? Una carga doble de pólvora no es novedad, por lo tanto concluyo que obviamente no has dejado tu pirámide desde los tiempos de ese machete de museo.";
			} else {
				link.l1 = "¿Eso es todo? Oye...";
			}
			link.l1.go = "joruba_p2_2";
		break;
		
		case "joruba_p2_2":
			dialog.text = "¡No seas un listillo y escucha! Cualquier idiota puede poner dos montones de pólvora en un barril y arriesgarse a quedarse ciego, con quemaduras en la cara o con la nariz rota. Te ofrezco un truco mágico: revisa la calidad de la pólvora con cuidado, muélela a la consistencia adecuada, ponle una bala o perdigones, y adereza con un doblón picado. ¡El estallido hará trizas hasta una coraza!";
			link.l1 = "¿Disparando dinero, eh? Tan típico de ti.";
			link.l1.go = "joruba_p2_3";
		break;
		
		case "joruba_p2_3":
			dialog.text = "¡Eres insufrible! Está bien, agarra un mortero de mano, y una docena de granadas para él también. Si eres tan malditamente listo, conseguirás los planos de las granadas por tu cuenta en poco tiempo.";
			link.l1 = "Muchas gracias, mi señor. ¿Qué sigue?";
			link.l1.go = "joruba_p2_4";
			
			//Log_info("You received Hand mortar");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "mortairgun");
			TakeNItems(pchar, "grenade", 10);
		break;
		
		case "joruba_p2_4":
			dialog.text = "No te va a encantar. Necesito un barco... no, necesito el barco. Como puedes imaginar, con una historia detrás de él.";
			link.l1 = "¿Por qué? Ni siquiera eres capitán.";
			link.l1.go = "joruba_p2_5";
		break;
		
		case "joruba_p2_5":
			dialog.text = "¡No es asunto tuyo! Más te vale concentrarte en tu recompensa, porque puedo exigir que limpies esta pirámide de arriba a abajo por esto, ¡y aún me deberías!";
			link.l1 = "Definitivamente no eres un capitán, de lo contrario sabrías que un barco necesita un muelle o una bahía para atracar. ¡¿Cómo diablos esperas que meta un barco en tu pirámide?!";
			link.l1.go = "joruba_p2_6";
		break;
		
		case "joruba_p2_6":
			dialog.text = "¿Has notado un lago gigante detrás de mi pirámide por casualidad? Así es. Solo atraca con la nave correcta en el escuadrón cercano y mis hombres se encargarán del resto. Ahora lárgate de aquí, estás deteniendo la fila.";
			link.l1 = "Por supuesto. ¡Adiós!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveThirdTask");
		break;
		
		case "joruba_p3":
			sld = GetCharacter(sti(companion));
			pchar.questTemp.ChickenGod.Tasks.p3.ship = sld.ship.type;
			RemoveCharacterCompanion(pchar, sld);
			AddPassenger(pchar, sld, false);
						
			npchar.ship.type = pchar.questTemp.ChickenGod.Tasks.p3.ship;
			SetCharacterShipLocation(npchar, "Temple");
						
			sld = GetRealShip(sti(pchar.questTemp.ChickenGod.Tasks.p3.ship));
					
			dialog.text = "¡Genial! ¡Lo tengo!";
			link.l1 = "¡Deja de hacerte el listo y dame mi recompensa!";
			link.l1.go = "joruba_p3_1";
			switch (sti(sld.BaseType)) {
				case SHIP_MAYFANG:
					dialog.text = "¿Qué hay de los otros dos? ¿No pudiste guardarlos para ti mismo? Je-je.";
				break;
				
				case SHIP_MIRAGE:
					dialog.text = "¿Qué hay de los otros dos? ¿No pudiste guardarlos para ti mismo? Je-je.";
				break;
				
				case SHIP_VALCIRIA:
					dialog.text = "¿Qué pasa con los otros dos? ¿No pudiste guardarlos para ti? Je-je.";
				break;
				
				case SHIP_FRIGATE_L:
					dialog.text = "Maldición, me impresiona que no quisieras quedártela para ti. ¡Ahora eso es lo que yo llamo un barco con historia! Maldita sea, William... Realmente deseaba que volvieras a casa y fundaras un gran banco como siempre soñaste.";
				break;
				
				case SHIP_CORVETTE_QUEST:
					sTemp = "privateer";
					if (isMainCharacterPatented()) {
						sTemp = GetStrSmallRegister(GetAddress_FormTitle(sti(Items[sti(pchar.EquipedPatentId)].Nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur)));
					}
					
					dialog.text = "¡Mira esto! ¡Eres una desgracia para tu comisión, "+sTemp+"!";
				break;
				
				case SHIP_POLACRE_QUEST:
					dialog.text = "¿Charlie Prince decidió deshacerse de las pruebas incriminatorias en mi antigua pirámide? ¡Lo apruebo!";
				break;
				
				case SHIP_ECLIATON:
					dialog.text = "Buena suerte explicando a tus superiores la pérdida del buque insignia, Almirante. Oh, perdóneme, general-gobernador.";
				break;
				
				case SHIP_CURSED_FDM:
					dialog.text = "¿Eres un tonto supersticioso o simplemente un tonto? ¡Ella vale una fortuna! No estoy seguro de que sea un intercambio justo, pero lo que sea.";
				break;
				
				case SHIP_FDM:
					dialog.text = "¿Eres un tonto supersticioso o solo un tonto? ¡Ella vale una fortuna! No estoy seguro de que sea un intercambio justo, pero lo que sea.";
				break;
				
				case SHIP_RENOVATED_FDM:
					dialog.text = "¿Eres un necio supersticioso o simplemente un necio? ¡Ella vale una fortuna! No estoy seguro de que sea un intercambio justo, pero bueno.";
				break;
				
				case SHIP_ELCASADOR:
					dialog.text = "¡Buena decisión! Me encantan los castellanos, ¿sabes? Tal vez se la devuelva cuando termine.";
				break;
				
				case SHIP_HIMERA:
					dialog.text = "En verdad, careces de corazón, Capitán. Este barco apesta a traición. Me la llevaré.";
				break;
				
				case SHIP_PINK:
					if (startHeroType == 4)
					{
						dialog.text = "Ay, este barco puede tener una historia... pero ¿no fue demasiado fácil de obtener? Ah, está bien. Tu caso es especial, querida, así que lo aceptaré. Al menos trae algunos recuerdos de mi juventud.";
						Achievment_Set("ach_CL_127");
					}
					else 
					{
						dialog.text = "¡Aye, este barco puede tener una historia... pero, ¿no fue demasiado fácil de conseguir? Oh, qué demonios. Está bien, Capitán, dejaré pasar esta, ya que hiciste un gran trabajo con esas tareas de mi lista. Lo tomaré. Al menos me trae algunos recuerdos de mi juventud.";
					}
				break;
				
				case SHIP_GALEON_SM:
					dialog.text = "¿Y has visto al sacerdote? Bueno, lo conocerás. Y será mejor que te abastezcas de cargas de pistola de doble disparo. Si eso no ayuda, intenta con una estaca de madera.";
				break;
				
				case SHIP_LADYBETH:
					dialog.text = "¿Y has visto al cura? Bueno, lo conocerás. Y será mejor que te abastezcas de balas para pistolas de doble cañón. Si eso no ayuda, prueba con una estaca de madera.";
				break;
			}
		break;
		
		/*case "joruba_p3_HolyMercy":
			dialog.text = "¿Y has visto al sacerdote?";
			link.l1 = "¿Qué sacerdote?";
			link.l1.go = "joruba_p3_HolyMercy_2";
		break;
		
		case "joruba_p3_HolyMercy_2":
			dialog.text = "Bueno, lo conocerás. Y será mejor que te abastezcas de cargas de pistola de doble tiro. Si eso no ayuda, prueba con una estaca de madera.";
			link.l1 = "...";
			link.l1.go = "joruba_p3_1";
		break;*/
		
		case "joruba_p3_PinkOtkaz":
			dialog.text = "¡Aye, este barco puede tener una historia... pero, ¿no fue demasiado fácil de obtener? ¡De ninguna manera! Todavía tienes un montón de trabajo sin terminar de la lista. Una vez que hayas hecho eso, discutiremos este sacrificio nuevamente.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "joruba_p3_1":
			dialog.text = "Te bendigo, "+GetFullName(pchar)+". Que el mar te sea favorable. Ahora, hablemos de la próxima transacción...";
			link.l1 = "¿Espera, qué? ¡Ni siquiera los idiotas de pueblo caen en tales tonterías en nuestra era de la razón! ¡No puse ni un centavo en tu caja de caridad, te di un buque de guerra en toda regla!";
			link.l1.go = "joruba_insult";
			link.l2 = "Espera un segundo. ¿Qué significa exactamente tu bendición para mí?";
			link.l2.go = "joruba_p3_2";
			
			pchar.questTemp.ChickenGod.Tasks.p3.Completed = true;
		break;
		
		case "joruba_p3_2":
			dialog.text = "¡Cualquier barco que comandéis será bendecido con un casco más fuerte, mientras que vuestros enemigos sufrirán lo contrario! Además, el tiempo en el mar pasará más lento para vos. Y si eso no es suficiente para que pongáis de rodillas a este agujero maldito, ¡mejor id con vuestro padre y exigid un reembolso!";
			link.l1 = "Si no funciona, ¡juro que volveré aquí esta noche y quemaré tu pirámide! ¡Cuéntame sobre el próximo trato!";
			link.l1.go = "joruba_p3_3";
			notification("+10% defensa del casco", "None");
			notification("+10% de daño al casco de los barcos enemigos", "None");
			notification("+5% de velocidad en el Mapa Global", "None");
			PlaySound("Interface\new_level.wav");
		break;
		
		case "joruba_p3_3":
			dialog.text = "¿Desarrollando un gusto por ello, eh capitán? Desafortunadamente para ti, yo también. ¿Por qué crees que elegí esta pirámide para mi oficina?";
			link.l1 = "¿Probablemente porque la caza de brujas sigue siendo algo?";
			link.l1.go = "joruba_p3_4";
		break;
		
		case "joruba_p3_4":
			dialog.text = "Heh-heh, no, no exactamente. Hago mis negocios aquí porque los mejores tratos requieren sangre. Esta pirámide requiere sangre. Yo requiero sangre. Así ha sido, así será.";
			link.l1 = "Ni siquiera lo pienses, monstruo. ¡No entregaré víctimas para que las mates!";
			link.l1.go = "joruba_p3_5";
		break;
		
		case "joruba_p3_5":
			dialog.text = "¿Y cuántos has matado, eh? Espera, incluso te diré el número exacto: tú personalmente mataste "+(Statistic_AddValue(pchar,"Soldado_s",0)+Statistic_AddValue(pchar,"Ciudadano_s",0)+Statistic_AddValue(pchar,"Guerrero_s",0)+Statistic_AddValue(pchar,"Solder_g",0)+Statistic_AddValue(pchar,"Ciudadano_g",0)+Statistic_AddValue(pchar,"Guerrero_g",0))+" ¡gente! ¡Pusisteis una montaña de cadáveres en el altar de vuestra ambición y lujuria por la riqueza! ";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text+"¡La deuda de tu hermano ya ha matado a más personas que una guerra europea promedio! ";
			}
			dialog.text = dialog.text+"No empieces a moralizar aquí conmigo, especialmente porque no voy a juzgarte. El éxito de algunos siempre se pagará con las tragedias de otros, y los dioses, oh, dioses, estarán observando y cobrando su parte.";
			link.l1 = "No puedo darte una respuesta ahora mismo... Necesito salir de aquí.";
			link.l1.go = "joruba_p3_6";
		break;
		
		case "joruba_p3_6":
			dialog.text = "¿Una necesidad urgente de despejar tu mente? Muy bien, pero primero, escúchame. Te daré poder y control total sobre tu cuerpo y mente, si me traes a un hombre de gran valor. No un extra, no un ratón gris sin rostro de las calles o una rata de las sentinas apestosas. Tráeme un hombre que te siga y juegue un papel importante en tu tragicomedia.";
			link.l1 = "¿Uno de mis oficiales? ¡No puedes caer más bajo, Aruba! Si esto se llega a saber...";
			link.l1.go = "joruba_p3_7";
		break;
		
		case "joruba_p3_7":
			dialog.text = "Me ocuparé del secreto como siempre lo hago. Y antes de que empieces a quejarte otra vez, te haré saber que hay otra manera.";
			link.l1 = "¿Qué se supone que significa eso? ¿Así no tengo que arrastrar a mi propia gente al altar?";
			link.l1.go = "joruba_p3_8";
		break;
		
		case "joruba_p3_8":
			dialog.text = "No, pero no te gustará la alternativa. Si no quieres pagar con sangre, puedes pagar con oro. Tres mil doblones y una conciencia tranquila. El dinero puede hacer eso y más, ¡me encanta!";
			link.l1 = "Adiós, Aruba. Ya no quiero hablar contigo.";
			link.l1.go = "joruba_p3_9";
		break;
		
		case "joruba_p3_9":
			dialog.text = "Sabes dónde encontrarme.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveFourthTask");
		break;
		
		case "joruba_p4":
			dialog.text = "Vamos a hacer esto rápido antes de que aparezca la Inquisición Española. ¿Sangre u oro?";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Oro es. Aquí tienes tus tres mil, aunque no puedo imaginar cómo es posible que puedas gastar una cantidad tan enorme en este desierto. ";
				link.l1.go = "joruba_p4_1";
			}
			if (ChickenGod_HaveOfficers()) 
			{
				link.l2 = "Sangre.";
				link.l2.go = "joruba_p4_other";
			}
			link.l3 = "No importa.";
			link.l3.go = "exit";
		break;
		
		case "joruba_p4_1":
			dialog.text = "...";
			link.l1 = "¿Has terminado? Hablemos de mi recompensa.";
			link.l1.go = "joruba_p4_reward_1";
			RemoveDublonsFromPCharTotal(3000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 3000;
		break;
		
		case "joruba_p4_other":
			dialog.text = "Que así sea. Di el nombre.";
			
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Irons");
		break;
		
		case "joruba_p4_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Claude Durand no es un oficial, sino un mercenario despiadado, así que elige otra víctima.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "Acepto tu tributo. No tienes que mirar.";
			link.l1 = "No, no lo hago. Volveré por mi recompensa en una hora.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_p4_reward";
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
		break;
		
		case "joruba_o6_money":
			dialog.text = "Buena elección. Odio limpiar el altar de toda esa sangre, así que el oro es preferible. Aquí, toma esta poción, un obsequio de un buen amigo mío.";
			link.l1 = "El sabor no está nada mal...";
			link.l1.go = "exit";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			RemoveDublonsFromPCharTotal(25000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 25000;
			
			if (sti(pchar.questTemp.ChickenGod.Gold) >= 30000) {
				Achievment_Set("ach_CL_87");
			}
			
			notification("+3 P.I.R.A.T.E.S. point", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_p4_reward":
			dialog.text = "";
			link.l1 = "¿Has terminado? Hablemos de mi recompensa.";
			link.l1.go = "joruba_p4_reward_1";
		break;
		
		case "joruba_p4_reward_1":
			dialog.text = "Habla conmigo cuando quieras cambiar tu destino.";
			link.l1 = "¿Pero qué significa exactamente para mí?";
			link.l1.go = "joruba_p4_reward_2";
		break;
		
		case "joruba_p4_reward_2":
			dialog.text = "¡Poder sobre ti mismo! Inténtalo a veces y te encantará. Mientras tanto, déjame contarte sobre la próxima transacción. La más importante.";
			link.l1 = "¡Ya no estoy seguro de que valga la pena!";
			link.l1.go = "joruba_p4_reward_3";
			link.l2 = "Vamos, suéltalo ya.";
			link.l2.go = "joruba_p4_reward_3";
		break;
		
		case "joruba_p4_reward_3":
			dialog.text = "Tienes la oportunidad no solo de cambiar tu destino, sino de estar junto a los genios y dioses de nuestro tiempo. Sí, puedes cambiar tu cuerpo y mente tanto como desees ahora, pero nunca saltarás por encima de tu cabeza, porque una persona común no puede ser buena en todo. Lo que estoy sugiriendo es que rompas esos límites.";
			link.l1 = "¿Qué me va a costar? ¿Más sangre? ¿Oro?";
			link.l1.go = "joruba_p4_reward_4";
		break;
		
		case "joruba_p4_reward_4":
			dialog.text = "Ay. O me traes veinticinco mil doblones o uno de tus compañeros. Una vez que terminemos, no habrá más transacciones.";
			link.l1 = "Lo pensaré.";
			link.l1.go = "joruba_p4_reward_5";
		break;
		
		case "joruba_p4_reward_5":
			dialog.text = "Sabes dónde encontrarme. Y no dudes en visitarme en cualquier momento que desees cambiar tu destino.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			
			pchar.questTemp.ChickenGod.Tasks.p4.Completed = true;
			AddDialogExitQuestFunction("ChickenGod_GiveFifthTask");
		break;
		
		case "joruba_respec":
			dialog.text = "Como desees.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ChickenGod_Respec");
		break;
		
		case "joruba_o2":
			dialog.text = "En primer lugar, esa es mi esposa, no una novia. En segundo lugar, tienes un problema con los castellanos, no conmigo. Y finalmente, ya la he llevado y despedido a tus hombres. Y en cuanto a intenciones honorables... Mírame, ¿acaso no soy un modelo de un caballero decente? Tlazolteotl, bendícelo para que él también pueda conocer un día a una mujer de verdad. O a un hombre.";
			link.l1 = "¡Que te den, Aruba!";
			link.l1.go = "exit";
			
			notification("+ 10 HP, + 10 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(10.0);
			pchar.questTemp.ChickenGod.Tasks.o2.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			sld = CharacterFromID(pchar.questTemp.ChickenGod.Tasks.o2.Lady);
			RemovePassenger(pchar, sld);
			ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto1");
			LAi_SetCitizenTypeNoGroup(sld);
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o3":
			dialog.text = "No está mal, gracias. Francamente, realmente no lo necesito, pero tal vez lo use en algún salón o lo que sea. En el nombre de Ishtar te bendigo. Ahora ve y peca.";
			link.l1 = "Qué sensación tan extraña...";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o3.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			TakeItemFromCharacter(pchar, "cirass4");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o4":
			dialog.text = "Me los llevaré. ¿Qué? Necesito hombres muertos en mi tripulación como tú, excepto que a diferencia de ti, no puedo ir por las tabernas reclutando. Ahora, Bast, bendiga al héroe por sus futuros esfuerzos.";
			link.l1 = "Qué sensación tan extraña...";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o4.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
			
			AddDialogExitQuestFunction("ChickenGod_RemovePrisoners");
		break;
		
		case "joruba_o5":
			dialog.text = "Sí, tendremos que dispersarlos de nuevo, porque la gente los pierde todo el tiempo, y necesitamos clientes. Freya, protege a este gran recolector de piedras.";
			link.l1 = "Qué sensación tan extraña...";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o5.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6":
			dialog.text = "Hagámoslo rápido antes de que aparezca la Inquisición Española. ¿Sangre u oro?";
			
			if (PCharDublonsTotal() >= 25000)
			{
				link.money = "Aquí está tu oro, bastardo codicioso.";
				link.money.go = "joruba_o6_money";
			}
			
			if (ChickenGod_HaveOfficers())
			{
				link.blood = "Blood.";
				link.blood.go = "joruba_o6_blood";
			}
			link.l3 = "No importa.";
			link.l3.go = "exit";
		break;
		
		case "joruba_o6_blood":
			dialog.text = "Di el nombre.";
			
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Irons");
			
			if (!CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Helena");
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Mary");
			}
		break;
		
		case "joruba_o6_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Mary" || pchar.questTemp.ChickenGod.Sacrifice == "Helena") {
				pchar.questTemp.ChickenGod.Tasks.o6.gf = true;
				sTemp = "future wife";
				sld = CharacterFromID(pchar.questTemp.ChickenGod.Sacrifice);
				if (sld.lastname == pchar.lastname) {
					sTemp = "current wife";
				}
				
				dialog.text = "Eso es bastante tentador, pero haré una excepción solo esta vez - no aceptaré tu sacrificio. No revelaré esto a tu "+sTemp+", aunque probablemente debería. Recuerda que no eres nada sin ella. Ahora, piérdete y no me molestes hoy.";
				link.l1 = "";
				link.l1.go = "exit";
				
				AddDialogExitQuestFunction("ChickenGod_KickedFromTemple");
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Claude Durand no es un oficial, sino un mercenario despiadado, así que elige otra víctima.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "Así sea. Aquí, toma esta poción - un obsequio de un buen amigo mío.";
			link.l1 = "El sabor no está nada mal...";
			link.l1.go = "joruba_o6_reward";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			notification("+3 P.I.R.A.T.E.S. points", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6_reward":
			dialog.text = "Hasta la próxima, capitán.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.OnExitKick = true;
		break;
		
		case "joruba_final":
			dialog.text = "¡Ahoy-hoy! ¡Finalmente, todo ha terminado!";
			link.l1 = "¿Eh?";
			link.l1.go = "joruba_final_1";
		break;
		
		case "joruba_final_1":
			dialog.text = "Estamos acabados aquí, Capitán. Los tratos están cerrados, todos están satisfechos, y no hay lugar para reembolsos. Nuestra oficina está cerrando y reubicándose.";
			link.l1 = "Espera un momento, Aruba. Te he dado mucho oro, pagado con sangre, traído mujeres y prisioneros a este antro infernal. Puedo manejar eventos sobrenaturales que aparentemente ocurren en el Caribe. Pero nuestras 'transacciones' contigo desafían toda lógica. Por favor, explica.";
			link.l1.go = "joruba_final_2";
		break;
		
		case "joruba_final_2":
			dialog.text = "¿Sabes una cosa? Estoy harto de este mundo y quiero salir de él. Todos los días, la misma rutina: una antigua pirámide con el techo derruido, esas repugnantes palmeras idénticas y un sinfín de capitanes, cada uno con sus propias ideas ingeniosas. Sí, proporciono a la gente lo que desea; es mi vocación, y me enorgullezco de ello. Pero, por los dioses, ¡cómo os detesto a todos!";
			link.l1 = "¿Alguien te está reteniendo aquí? ¡La salida está justo ahí, genio!";
			link.l1.go = "joruba_final_3";
		break;
		
		case "joruba_final_3":
			dialog.text = "Eres absolutamente correcto, nadie me retiene aquí. Ya no. Y todo es gracias a ti, mi amigo.";
			link.l1 = "Eso es un cambio de opinión repentino. Esperaba una historia, pero lo único que he oído hasta ahora son las diatribas sin sentido de un vil pequeño dios en una polvorienta pirámide.";
			link.l1.go = "joruba_final_4";
		break;
		
		case "joruba_final_4":
			dialog.text = "Bueno, todos necesitan desahogarse de vez en cuando, ¿no es así? Estoy realmente contento de que hayas venido aquí porque, gracias a ti, finalmente puedo partir de este mundo. Oro, tripulación, equipo y un barco, amigo mío. ¿Recuerdas? ¿Te suena familiar? Eso es todo lo que necesitaba, y tú lo proporcionaste todo.";
			link.l1 = "De nada. Sin embargo, eso aún no aclara tu peculiar manera de hablar y tus casi divinos poderes. ¡Si eres tan todopoderoso, podrías haber conjurado tu propio barco, tripulación y oro hace mucho tiempo!";
			link.l1.go = "joruba_final_5";
		break;
		
		case "joruba_final_5":
			dialog.text = "Lo hice, como puedes ver. Cada uno tiene sus propios métodos.";
			link.l1 = "¿Pero cómo demonios? ¿Quién eres tú, exactamente?";
			link.l1.go = "joruba_final_6";
		break;
		
		case "joruba_final_6":
			dialog.text = "Bueno... eso es lo que hago, simplemente. Nos vemos en el nuevo mundo, "+GetPersonaName()+"Realmente nuevo la próxima vez, eso espero. Gracias y adiós.";
			link.l1 = "No, no quiero verte nunca más.";
			link.l1.go = "exit";
			link.l2 = "Entonces nos vemos por ahí, Aruba... esto fue interesante.";
			link.l2.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_FinalGood");
		break;
		
		case "joruba_insult":
			dialog.text = "Parece que todos los tratos están cancelados. Es hora de irnos, capitán. ";
			link.l1 = "Hora de que te j... ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Insult");
		break;
		
		case "ChickenGod_TheInquisition_1":
			dialog.text = "¡En nombre de la Inquisición Española, nómbrate!";
			link.l1 = "Capitán "+GetFullName(pchar)+". Y es cierto lo que dicen, nadie espera la Inquisición Española...";
			link.l1.go = "ChickenGod_TheInquisition_2";
		break;
		
		case "ChickenGod_TheInquisition_2":
			dialog.text = "... Este chiste siempre da en el clavo, aunque llevó a no pocos cristianos inocentes a la hoguera.";
			link.l1 = "...";
			link.l1.go = "ChickenGod_TheInquisition_3";
		break;
		
		case "ChickenGod_TheInquisition_3":
			dialog.text = "Solo bromeaba, Capitán. Usted estaba bromeando, y yo también. Mi nombre es Padre Emilio Bocanegra, y estos soldados de Cristo son mis guardias armados.";
			link.l1 = "¿Qué puedo hacer por usted, padre?";
			link.l1.go = "ChickenGod_TheInquisition_4";
		break;
		
		case "ChickenGod_TheInquisition_4":
			dialog.text = "¿Conoces a un tal señor Aruba?";
			link.l1 = "Sí, vivía en esta vieja pirámide hasta hace poco.";
			link.l1.go = "ChickenGod_TheInquisition_5";
		break;
		
		case "ChickenGod_TheInquisition_5":
			dialog.text = "¿Qué quieres decir con que él vivía allí? ¿Es posible vivir allí? ¿Y por qué 'hasta hace poco'?";
			link.l1 = "Este señor nos dejó en un barco hace unos minutos.";
			link.l1.go = "ChickenGod_TheInquisition_6";
		break;
		
		case "ChickenGod_TheInquisition_6":
			dialog.text = "¿Cómo lo sabes? ¡La bahía más cercana está a días de distancia!";
			link.l1 = "Este lago debe ser más grande de lo que parece. No tengo otra explicación para vos, padre.";
			link.l1.go = "ChickenGod_TheInquisition_7";
		break;
		
		case "ChickenGod_TheInquisition_7":
			dialog.text = "Cosas extrañas están sucediendo en las tierras del Virreinato.";
			link.l1 = "Estas son tierras inglesas, padre.";
			link.l1.go = "ChickenGod_TheInquisition_8";
		break;
		
		case "ChickenGod_TheInquisition_8":
			dialog.text = "Deja que los herejes sigan pensando así. Seguro que recuperaremos lo nuestro. Perdóname, hijo mío, por hacer tantas preguntas: Santiago me ha instruido para realizar una investigación oficial sobre esta pirámide... y su antiguo ocupante.";
			link.l1 = "¿Qué ocurrió exactamente, padre?";
			link.l1.go = "ChickenGod_TheInquisition_9";
		break;
		
		case "ChickenGod_TheInquisition_9":
			dialog.text = "Como el caso probablemente se cerrará, puedo entretenerte con una pequeña historia.\nLos rumores sobre este lugar han estado circulando por todo el continente durante algún tiempo. Habíamos recibido informes confiables de que varias personas que dejaron una marca significativa en la historia de la región habían hecho visitas regulares aquí en el pasado\nSin embargo, Santiago comenzó a prestar verdadera atención a estos rumores después del incidente de Panamá.\nUn cierto indio había causado un gran revuelo en esa gloriosa ciudad e incluso dio varios sermones de naturaleza bastante filosófica. Desafortunadamente, los habitantes de Panamá llegaron a conclusiones bastante superficiales y se convencieron de que esta pirámide contiene tesoros incalculables y cumple cualquier deseo\nHerejía de la más pura clase, por supuesto... así que tuvimos que abrir procedimientos contra algunos residentes panameños y este indio, Aguebana.";
			link.l1 = "¿Por qué no reprimieron las autoridades panameñas esto?";
			link.l1.go = "ChickenGod_TheInquisition_10";
		break;
		
		case "ChickenGod_TheInquisition_10":
			dialog.text = "Como siempre hacen en estos casos, afirmaron que estaban hechizados. Esta laguna legal podría haberse cerrado si hubiéramos interrogado a Aguebana, pero murió repentinamente.";
			link.l1 = "¿Cómo murió?";
			link.l1.go = "ChickenGod_TheInquisition_11";
		break;
		
		case "ChickenGod_TheInquisition_11":
			dialog.text = "La embriaguez lo mató. Sin embargo, su muerte no resolvió nuestros problemas, porque la herejía se había arraigado en todo el archipiélago, y cientos de personas emprendieron una especie de peregrinación a este antiguo templo.";
			link.l1 = "Nunca he visto multitudes de gente aquí antes... ¿Entonces qué, ibas a invadir Aruba y llevarlo a juicio?";
			link.l1.go = "ChickenGod_TheInquisition_12";
		break;
		
		case "ChickenGod_TheInquisition_12":
			dialog.text = "Por supuesto que no, hijo mío. El juicio de la Inquisición es severo pero justo. Debe haber una buena razón para un juicio. No, solo iba a recoger el testimonio del señor Aruba y entregarlo a Santiago.";
			link.l1 = "Bueno, eso es desafortunado para ti.";
			link.l1.go = "ChickenGod_TheInquisition_13";
		break;
		
		case "ChickenGod_TheInquisition_13":
			dialog.text = "No sabes nunca, hijo mío. Es la voluntad de Dios.";
			link.l1 = "Adiós, padre.";
			link.l1.go = "ChickenGod_TheInquisition_14";
		break;
		
		case "ChickenGod_TheInquisition_14":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Temple", "reload2", false);
			LAi_SetActorType(npchar);
			//LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "ChickenGod_TheInquisitionLeave", -1);
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition = "ChickenGod_TheInquisitionLeave";
		break;
		
	}
} 

void ChickenGod_InitAmmo() {
	if(LoadSegment("items\initItems.c")) {
		InitGunExt(		 "pistol1", "t3", 	 "bullet_double",               "", 100.0, 300.0,  60.0, 260.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 40, 20, 0);
		InitGunExt( 	 "pistol2", "t2", "grapeshot_double",               "",  60.0, 160.0,  20.0, 100.0,  0.0,  0.0, 0, 1, 1, 0, 1, 1, 40, 20, 0);
		InitGunExt(		 "pistol3", "t2", "grapeshot_double",               "",  80.0, 180.0,  30.0, 110.0,  0.0,  0.0, 0, 1, 1, 2, 1, 1, 40, 20, 0);
		InitGunExt(		 "pistol4", "t3",    "bullet_double",               "",  70.0, 270.0,  30.0, 230.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 35, 30, 0);
		InitGunExt(		 "pistol5", "t3", 	 "bullet_double",               "", 130.0, 330.0,  90.0, 290.0,  0.0,  0.0, 1, 0, 0, 2, 0, 0, 70, 30, 0);
		InitGunExt(		 "pistol6", "t3",    "bullet_double",               "", 100.0, 300.0,  60.0, 260.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 50, 20, 0);
		InitGunExt(		 "pistol8", "t4", "grapeshot_double",               "",  50.0, 100.0,  30.0,  60.0,  5.0,  5.0, 1, 1, 1, 0, 1, 1, 20, 20, 0);
		InitGunExt(		 "pistol9", "t3", 	 "bullet_double",               "", 100.0, 320.0,  80.0, 280.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 40, 30, 0);
		InitGunExt(		 "pistol10", "t3",   "bullet_double",               "", 140.0, 280.0, 100.0, 240.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 45, 30, 0);
		InitGunExt(		 "pistol11", "t3",   "bullet_double",               "",  10.0, 700.0,  10.0, 620.0, 40.0, 30.0, 1, 1, 0, 0, 0, 0, 45,100, 0);
		InitGunExt(		 "pistol12", "t3",   "bullet_double",               "",  80.0, 290.0,  60.0, 240.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 45, 20, 0);
		InitGunExt(		 "pistol13", "t3",   "bullet_double",               "", 130.0, 300.0,  90.0, 260.0, 15.0,  0.0, 1, 1, 0, 0, 0, 0, 60, 30, 0);
		InitGunExt(		 "howdah",  "t3", "grapeshot_double",	            "",  50.0, 140.0,  30.0,  70.0,  5.0,  5.0, 1, 1, 1, 0, 0, 1, 50, 30, 0);
		InitGunExt(		 "pistol14", "t3",   "bullet_double",               "", 130.0, 330.0,  90.0, 290.0,  0.0,  0.0, 1, 0, 0, 4, 0, 0, 70, 34, 0); // Дуэльный двухзарядный пистоль cle 1.3
		
		UnloadSegment("items\initItems.c");
	}
	
	CGInitGrapeGunExt(	"pistol2",	"t2",		3,		50,		4.25,	5.0,	3);		// трёхствольный дробовик, двойной заряд
	CGInitGrapeGunExt(	"pistol3",	"t2",		4,		40,		6.0,	5.0,	4);		// тромбон, двойной заряд
	CGInitGrapeGunExt(	"pistol8",	"t4",		4,		110,	5.0,	3.0,	2);		// бландербуз, двойной заряд
	CGInitGrapeGunExt(	"howdah",	"t3",		3,		85,		3.0,	5.5,	2);		// гауда, двойной заряд
	CGInitGrapeGunExt(	"mushket3",	"t2",		3,		60,		6.0,	3.0,	3);		// аркебуза, картечь
	CGInitGrapeGunExt(	"mushket6",	"t3",		3,		90,		4.0,	3.5,	2);		// башенный мушкетон, картечь
}

void CGInitGrapeGunExt(string id, string sAttr, int basedmg, int shards, float width, float height, int dispersion)
{
	ref gun = ItemsFromID(id);
	gun.type.(sAttr).basedmg = basedmg;
	gun.type.(sAttr).shards = shards;
	string sArea = "grapes_area_"+dispersion;
	gun.type.(sAttr).area = XI_ConvertString(sArea);
	gun.type.(sAttr).width = width;
	gun.type.(sAttr).height = height;
}

bool ChickenGod_FindQuestShips() {
	questShipsNum = 0;
	
	for(int i = 1; i < COMPANION_MAX; i++) {
		int index = GetCompanionIndex(pchar, i);
		if (index < 0) {
			continue;
		}
		
		sld = GetCharacter(index);
		int shipIndex = sti(sld.ship.type);
		if (shipIndex == SHIP_NOTUSED) {
			continue;
		}
		
		ref realShip = GetRealShip(shipIndex);
		if (!CheckAttribute(realShip, "QuestShip")) {
			continue;
		}
		
		if (!GetRemovable(sld) || !GetShipRemovable(sld)) {
			continue;
		}
		
		if (CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip")) {
			if (sti(realShip.BaseType) == SHIP_MAYFANG || sti(realShip.BaseType) == SHIP_MIRAGE || sti(realShip.BaseType) == SHIP_VALCIRIA) {
				continue;
			}
		}
		
		questShips[questShipsNum] = sti(sld.index);
		questShipsNum++;
	}
	
	return (questShipsNum > 0);
}

void ChickenGod_AddOfficerLink(aref link, string prefix, string id) {
	if (GetCharacterIndex(id) < 0) {
		return;
	}
	
	if (!CheckPassengerInCharacter(pchar, id)) {
		return;
	}
	
	if (id == "Mary" && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) {
		return;
	}
	
	if (id == "Helena" && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
		return;
	}
	
	sld = CharacterFromID(id);
	
	if (!GetRemovable(sld)) {
		return;
	}
	
	link.(id) = GetFullName(sld) + ".";
	link.(id).go = prefix + id;
}

bool ChickenGod_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}

bool ChickenGod_HaveOfficers() {
	object fakelink;
	
	ChickenGod_AddOfficerLink(&fakelink, "", "Duran");
	ChickenGod_AddOfficerLink(&fakelink, "", "Baker");
	ChickenGod_AddOfficerLink(&fakelink, "", "Folke");
	ChickenGod_AddOfficerLink(&fakelink, "", "Avendel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tonzag");
	if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(&fakelink, "", "Longway");
	ChickenGod_AddOfficerLink(&fakelink, "", "Knippel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tichingitu");
	ChickenGod_AddOfficerLink(&fakelink, "", "Irons");
	
	if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
		ChickenGod_AddOfficerLink(&fakelink, "", "Helena");
		ChickenGod_AddOfficerLink(&fakelink, "", "Mary");
	}
	
	return (GetAttributesNum(&fakelink) > 0);
}
