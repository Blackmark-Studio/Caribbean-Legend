// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?","¿Cómo puedo ayudarte, "+GetAddress_Form(NPChar)+"?"),"Intentaste hacerme una pregunta hace poco, "+GetAddress_Form(NPChar)+"... ","En todo el día de hoy, es la tercera vez que hablas de alguna pregunta...","¿Más preguntas, supongo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...","No tengo nada de qué hablar en este momento."),"Umph, ¿dónde se ha ido mi memoria...?","Sí, realmente es la tercera vez...","No, ¿qué preguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_1"))
			{
				link.l1 = "Dicen que te han dejado sin tu preciado gin. ¿O son solo rumores?";
				link.l1.go = "OS_Tavern1_1";
			}
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_3"))
			{
				link.l1 = "¡Buenas noticias, "+npchar.name+"! ¡He encontr"+GetSexPhrase("ado","ado")+" tu barril!";
				link.l1.go = "OS_Tavern3_1";
			}
			//<-- Старые счёты
		break;
		
		//--> Старые счёты
		case "OS_Tavern1_1":
			dialog.text = "Por desgracia, es cierto. ¿Qué más has oído? ¿Sabes algo? Te lo ruego, dime si sabes dónde encontrarlo. Si no lo recupero... tendré que abandonar la ciudad. O me iré por mi cuenta, o me sacarán en un ataúd.";
			link.l1 = "Hmm... No pinta bien la cosa, amigo. No, sólo he oído algo de pasada sobre tu problema. ¿Cómo pudiste perder algo tan valioso para ti?";
			link.l1.go = "OS_Tavern1_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OS_Tavern1_2":
			dialog.text = "Ah... ¿Qué puedo decir...? ¡Lo robaron justo delante de mis narices! Por la mañana, el barril seguía allí. Lo trajeron hace dos días y me lo llevé a casa por la noche para dormir tranquilo. Lo devolví por la mañana, lo puse bajo el mostrador. Y por la tarde... como si se lo hubiera llevado el viento. ¡Nadie vio ni oyó nada!";
			link.l1 = "Vaya, vaya...";
			link.l1.go = "OS_Tavern1_3";
		break;
		
		case "OS_Tavern1_3":
			dialog.text = "Si tuviera alguna pista, ya habría salido a buscarlo. Pero no hay nada... es como si ese barril fuera demasiado bueno para este mundo y se lo hubieran llevado los cielos. Estoy dispuesto a pagar ciento cincuenta doblones a quien lo devuelva. Es más, colocaré una placa con su nombre en la taberna para que todos conozcan su hazaña.";
			link.l1 = "Intentaré ayudarte. Pero volveremos a lo de la placa más adelante. Dime mejor, ¿quién sabía del barril? ¿Y quién más, aparte de ti, podría haber estado tras la barra?";
			link.l1.go = "OS_Tavern1_4";
			link.l2 = "¿Ciento cincuenta doblones por un barril? Curioso. Pero no es asunto mío. Arréglatelas como puedas.";
			link.l2.go = "OS_Tavern1_end";
		break;
		
		case "OS_Tavern1_end":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			CloseQuestHeader("OS");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			sld = CharacterFromID("OS_Pirate");
			sld.lifeday = 0;
		break;
		
		case "OS_Tavern1_4":
			dialog.text = "Bueno... realmente nadie. Tal vez mi camarera, pero lo dudo mucho. Ese día hubo una fiesta tremenda en la taberna: la tripulación del 'Sea Beast' regresó de una cacería con un botín decente. No tuvo ni un minuto para sentarse, y mucho menos para merodear detrás de la barra.";
			link.l1 = "¿Está seguro de eso?";
			link.l1.go = "OS_Tavern1_5";
		break;

		case "OS_Tavern1_5":
			dialog.text = "Totalmente. No le gustó nada trabajar sin descanso y por la noche ya estaba al límite. Uno de los marineros comenzó a acosarla, y ella gritó tanto que a todos les zumbaban los oídos. Incluso tuve que salir de detrás de la barra para calmar a la gente. Aunque, por lo general, no reacciona así.";
			link.l1 = "¿Eso es todo? ¿Nada más digno de mención ese día?";
			link.l1.go = "OS_Tavern1_6";
		break;

		case "OS_Tavern1_6":
			dialog.text = "Mientras resolvía el primer escándalo, estalló una pelea en la esquina de la taberna: dos marineros se enzarzaron. Pero no duró mucho, parecía que eran del mismo equipo, y los separaron rápidamente. Después de eso, todo se calmó, y no pasó nada más notable.";
			link.l1 = "Bien, estoy preparad"+GetSexPhrase("o","a")+" para comenzar la búsqueda. Esperad. Creo que pronto el barril volverá a estar bajo vuestra, ejem... atenta vigilancia.";
			link.l1.go = "OS_Tavern1_7";
		break;

		case "OS_Tavern1_7":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			AddQuestRecord("OS", "2");

			sld = GetCharacter(NPC_GenerateCharacter("OS_Matros_1", "citiz_31", "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
			sld.dialog.filename = "Quest\\MiniEvents\\OldScores_dialog.c";
			sld.dialog.currentnode = "OS_Matros";
			LAi_SetImmortal(sld, true);
			sld.City = "PuertoPrincipe";
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_town", "goto", "goto14");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "OS_Tavern3_1":
			dialog.text = "¿Lo encontraste? ¡¿De verdad?! ¡Capitán, me has salvado la vida! ¿Quién está detrás de esto? ¡Debo saber el nombre de ese desgraciado!";
			link.l1 = "Fue una artimaña cuidadosamente planeada por cierto Jack Wales, junto con el capitán del 'Sea Beast'. Reclutaron a sus marineros e interpretaron una verdadera obra para distraerte. Cuando te alejaste de la barra, el barril quedó desatendido y lo robaron sin esfuerzo.";
			link.l1.go = "OS_Tavern3_2";
			DelLandQuestMark(npchar);
			pchar.questTemp.CameraDialogMode = true;
		break;

		case "OS_Tavern3_2":
			dialog.text = "¡Increíble! ¡Jack Wales! Así que ha vuelto... Y parece que intenta recuperar la taberna. ¡Ese zorro nunca se rinde!";
			link.l1 = "¿Así que él era el dueño antes? Tranquilo, no volverá a lograr nada. Lo envié al otro mundo.";
			link.l1.go = "OS_Tavern3_3";
		break;

		case "OS_Tavern3_3":
			dialog.text = "¡Capitán! ¡Eso es asombroso! Me has librado de un temor constante por mi futuro. Siempre supe que tarde o temprano regresaría... Hace años competíamos por esta taberna, y logró quedarse con ella\nPero su alegría le costó caro: celebró tanto que ni se dio cuenta cuando me la ganó en una partida de cartas. A la mañana siguiente vino rogando que se la devolviera, prometiéndome cualquier cosa\nPero no soy tan tonto como para aceptar. Luego desapareció... Sabía que no lo dejaría así. Sentía que algún día volvería. Y ese día ha llegado.";
			link.l1 = "Hay que reconocerlo, lo organizó todo con mucha habilidad.";
			link.l1.go = "OS_Tavern3_4";
		break;

		case "OS_Tavern3_4":
			dialog.text = "¡Espera! ¿Cómo se enteró siquiera del barril? Creo... ¡creo que empiezo a entender! ¡La camarera! Por eso salió corriendo como si se hubiera quemado, sin despedirse siquiera. Al parecer, se enteró de que te deshiciste de Jack. Todo encaja. Capitán, estoy en deuda con usted...";
			link.l1 = "...";
			link.l1.go = "OS_Tavern3_5";
		break;
		
		case "OS_Tavern3_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_3");
			ChangeShowIntarface();
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Zaharia", "Marlow", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
			sld.name = GetCharacterName("Zachary");
			sld.lastname = GetCharacterName("Marlow");
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_tavern", "reload", "reload1");
			TeleportCharacterToPosAy(sld, -1.30, 0.00, -0.67, 1.50);
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "Zaharia_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
