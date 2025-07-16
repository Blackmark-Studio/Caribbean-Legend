void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Se ha dado la alarma en la ciudad. ¡Todos te están buscando! No esperaría aquí demasiado tiempo si fuera tú.","Todo el destacamento de la guardia está recorriendo el pueblo tratando de encontrarte. ¡No soy un idiota y no voy a hablar contigo!","Corre, compañero, antes de que los soldados te hagan picadillo..."),LinkRandPhrase("¿Qué necesitas, bribón? ¡La guardia de la ciudad te está pisando los talones ahora mismo. No llegarás lejos, sucio pirata!","¡Fuera de mi casa, asesino! ¡Guardias!","¡No te tengo miedo, granuja! Pronto te colgarán, no te escaparás..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, no estoy muy preocupado por la alarma...","No tienen ninguna posibilidad de atraparme."),RandPhraseSimple("Cierra el pico, "+GetWorkTypeOfMan(npchar,"''")+", ¡o te cortaré la maldita lengua!","Heh, "+GetWorkTypeOfMan(npchar,"")+", ¡tú también quieres cazar a un pirata! Escucha, amigo, mantén la calma y vivirás..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+"¡Nunca te he visto antes, señor. Me atrevo a suponer, eres un capitán... ¿Adiviné bien? Mi nombre es "+GetFullName(npchar)+", y mi tienda está a tu servicio. Oro, plata y mucho más para despertar el interés de un hombre curioso.";
				Link.l1 = "Ya veo. Estoy "+GetFullName(pchar)+"Encantado de conocerte, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", señor. Me alegra verte de nuevo en mi tienda. ¿Te gustaría adquirir algunas pepitas de oro? ¿O tal vez estarías interesado en minerales hoy?";
				link.l1 = "Muéstrame tu mercancía, "+npchar.name+".";
				link.l1.go = "trade";
				link.l4 = "No, no necesito nada, "+npchar.name+". Solo he pasado a saludarte.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Como yo, señor. ¿Echará un vistazo a mi mercancía? Estoy seguro de que tengo algo que será de su interés.";
			link.l1 = "Esta es mi primera vez aquí y me gustaría saber un poco más sobre este asentamiento.";
			link.l1.go = "info";
			link.l2 = "Entonces muéstrame lo que tienes para vender.";
			link.l2.go = "trade";
		break;
		
		case "info":
			dialog.text = "Nuestra pequeña ciudad fue construida gracias a la mina de oro. Extraen mineral de oro, plata y pepitas doradas. A veces incluso gemas. Solíamos tener aquí solo una guarnición hasta que indios amistosos y algunos colonos blancos se unieron a nosotros.\nIgnacio Ortega ha construido una taberna y ha hecho nuestra vida un poco más alegre. Todo tipo de aventureros visitan este lugar con la estúpida intención de robarnos. No tenemos un tribunal aquí, así que su número disminuyó después de que colgamos a varios idiotas justo en el medio del pueblo.\nEl mineral de oro se envía a los barcos bajo la protección de soldados e indios amistosos. Las pepitas, sin embargo, puedes comprarlas aquí mismo, en esta tienda.\nAdemás, a veces tengo minerales muy interesantes para ofrecer, así que visítame cuando tengas tiempo, siempre reabastezco mis dependencias.";
			link.l1 = "¡Gracias por la historia interesante! La tendré en cuenta.";			
			link.l1.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("¡Robo a plena luz del día! ¿Qué está pasando aquí?! Espera, espera, camarada...","¡Eh, ¿qué haces ahí?! ¿Intentas robarme? Ahora estás jodido...","Espera, ¿qué demonios estás haciendo? ¡Resulta que eres un ladrón! Considera esto el fin del camino, bastardo...");
			link.l1 = LinkRandPhrase("¡Demonio!!","¡Caramba!","¡Ah, mierda!");
			link.l1.go = "fight_owner";
		break;
		
		case "fight_owner": // лесник . выход из диалога . если копался в сундуках. 
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}
