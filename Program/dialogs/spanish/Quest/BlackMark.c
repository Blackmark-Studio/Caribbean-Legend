void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "¿Qué necesitas?";
			link.l1 = "No es nada.";
			link.l1.go = "exit";
		break;
		
		case "BM_Contra_1":
			dialog.text = "¿Quién eres tú, y qué demonios haces merodeando por aquí?!";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Tranquilo, camarada. Solo estoy de paso. No voy a interferir con tu... lo que sea que esto sea.";
			}
			else
			{
				link.l1 = "¿Eh? ¿Es este faro tuyo? La próxima vez, pon un cartel con tu nombre en una de las palmeras o construye una maldita cerca.";
			}
			link.l1.go = "BM_Contra_2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Contra_2":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "¡Lárgate de aquí! Si arruinas el trato espantando a un cliente, yo...";
			}
			else
			{
				dialog.text = "Escucha, chaval, no nos hagas a mí y a mis chicos llamarte para ver si tu espada es tan afilada como tu lengua. Solo desaparece y...";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosPatrolPribegaet");
		break;
		
		case "BM_Contra_3":
			dialog.text = "Bueno, Frankie, ¿cuál es?";
			link.l1 = "...";
			link.l1.go = "BM_Contra_3_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay12", "1", 1.9);
		break;
		case "BM_Contra_3_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_4", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_4":
			dialog.text = "No... Que me condenen, pero no reconozco a ninguna de esas caras.";
			link.l1 = "...";
			link.l1.go = "BM_Contra_4_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay15", "1", 1.9);
		break;
		case "BM_Contra_4_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_5", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_5":
			dialog.text = "¿Qué?! ¿Estás seguro?";
			link.l1 = "...";
			link.l1.go = "BM_Contra_5_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolZhitel"));
		break;
		case "BM_Contra_5_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_6", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_6":
			dialog.text = "¿Crees que estoy ciego?! ¡Te digo que, qué...";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			CharacterTurnByChr(CharacterFromID("BM_PatrolOff"), CharacterFromID("BM_PatrolZhitel"));
			AddDialogExitQuest("BM_BarbadosMayakVystrel");
		break;
		
		case "BM_Contra_7":
			dialog.text = "¿Qué demonios?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay9", "1", 1.9);
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_7_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_8", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_8":
			dialog.text = "¿Quién disparó?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_8_1";
			locCameraFromToPos(-84.11, 6.33, -62.68, true, -78.07, 3.20, -66.67);
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 1.9);
		break;
		
		case "BM_Contra_8_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_9", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_9":
			dialog.text = "¿Nos tomas por tontos, escoria? ¡Pongan sus armas en el suelo, todos ustedes! ¡Y tú también!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_9_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_9_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_10", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_10":
			dialog.text = "Solo mantén la calma, oficial. No somos nosotros, ¿no ves? Nuestras armas están justo donde estaban. ¡Y no toques la tuya!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_10_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		case "BM_Contra_10_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_11", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_11":
			dialog.text = "¿¡Me estás dando órdenes, maldito bastardo?! ¡Arrestenlos a todos, ahora!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_11_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_11_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_12", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_12":
			dialog.text = "¡Al diablo contigo! Eso no va a suceder. ¡Chicos, a las armas!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosMayakBoinya");
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		
		case "BM_Irons_1":
			dialog.text = "¡Oye, oye, cuidado! Alguien podría morir si sigues agitando ese hierro tan salvajemente.";
			link.l1 = "¿Ja, quién?";
			link.l1.go = "BM_Irons_2";
			LAi_SetCurHPMax(npchar);
			SetOfficerToMushketer(npchar, "mushket1", true);
		break;
		
		case "BM_Irons_2":
			dialog.text = "Yo, por supuesto.";
			link.l1 = "¿Qué demonios...? ¿Quién diablos eres tú?";
			link.l1.go = "BM_Irons_4";
			link.l2 = "Eso es exactamente lo que estoy tratando de hacer. ¿Vamos?";
			link.l2.go = "BM_Irons_3";
		break;
		
		case "BM_Irons_3":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			npchar.MusketerDistance = 10;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "BM_Irons_4":
			if (startHeroType == 4)
			{
				dialog.text = "¡Soy Tommy! Tommy Irons. Supongo. ¿Quién eres tú? Eres una mujer valiente, te lo digo, caminando por ahí así, jejeje.";
				link.l1 = "Valiente, en verdad. Y no tengo miedo de cerrarte la boca si debo. Hace calor aquí, así que me visto ligeramente, no para complacerte a ti ni a los tuyos. Me llamo Helen MacArthur. Mis amigos podrían llamarme Rumba, pero tú ciertamente no eres uno de ellos. ¿Y a qué venía ese 'supongo'?";
				link.l1.go = "BM_Irons_5";
			}
			else
			{
				dialog.text = "¡Soy Tommy! Tommy Irons. Supongo. ¿Y tú?";
				link.l1 = ""+GetFullName(pchar)+". Y ¿qué significa exactamente ese 'supongo'?";
				link.l1.go = "BM_Irons_5";
			}
			LAi_SetCurHPMax(pchar);
		break;
		
		case "BM_Irons_5":
			dialog.text = "Eso significa exactamente lo que significa. Perdí la memoria, me dieron una buena paliza en la batalla. Sabes, a veces lo pierdes todo. Sin embargo, tengo suerte. Solo olvidé mi nombre. Afortunadamente para mí, tengo este colgante alrededor del cuello que dice 'Thomas'. Pero prefiero Tommy. Y Irons. Luché en los Ironsides para Cromwell, recuerda eso. Pero 'Ironsides' es demasiado voluminoso. Irons es mucho mejor.";
			link.l1 = "Veo qué te pasa, Tommy. Entonces, dime, ¿qué fue? ¿Apuntabas a alguien en particular? ¿Diste en el blanco? ¿O solo disparabas por diversión? No me sorprendería.";
			link.l1.go = "BM_Irons_6";
		break;
		
		case "BM_Irons_6":
			dialog.text = "¡Le di, y le di fuerte! De todas las maneras. ¿Recuerdas a ese pijo? Siguió mi rastro y trajo soldados con él. Todo un escuadrón, solo porque me acosté con su esposa.";
			link.l1 = "Lo golpeaste de verdad, je. ¿Supongo que os atrapó a los dos en el acto?";
			link.l1.go = "BM_Irons_7";
		break;
		
		case "BM_Irons_7":
			dialog.text = "¡Ja! No lo creerías, no. La moza lo confesó después. Conciencia culpable, o tal vez no lo disfrutó tanto como yo, jeje. ¿Quién sabe qué ocurre en las cabezas de las mujeres? A mí realmente no me importa, ¡ja-ja-ja!";
			link.l1 = ""+GetSexPhrase(" Hmm, es una rara. ","Hombres... Un minuto están tratando de averiguar qué hay en nuestras cabezas, al siguiente dicen que no les importa. Pero tienes razón en una cosa: lo que hizo fue extraño. Debería haberlo dejado atrás y olvidarlo como una pesadilla. Eso es exactamente lo que yo haría si llegara a eso.")+"";
			link.l1.go = "BM_Irons_8";
		break;
		
		case "BM_Irons_8":
			dialog.text = "¡Exactamente! La gente dice que hay algo mal en mí. Me siento apenado por los soldados que murieron. Lo sé, yo mismo fui un simple soldado una vez. ¿No te lo dije?";
			link.l1 = "Sí, lo hiciste. De los Ironsides. Cromwell.";
			link.l1.go = "BM_Irons_9";
		break;
		
		case "BM_Irons_9":
			dialog.text = "Oh, ¿sí? No recuerdo si lo hice o no. ¿Sabes cómo terminé en el Nuevo Mundo? ¿Te lo cuento?";
			link.l1 = "No, y no me interesaría, Tommy.";
			link.l1.go = "BM_Irons_10";
		break;
		
		case "BM_Irons_10":
			dialog.text = "Sí, sí. Te lo diré.";
			link.l1 = "Está bien, al diablo con eso, solo dispara. Quiero decir, adelante.";
			link.l1.go = "BM_Irons_11";
		break;
		
		case "BM_Irons_11":
			dialog.text = "¡Entonces no me interrumpas! ¿Dónde estaba? ¡Ah, sí, estaba herido, ¿ves? Me dieron mi renuncia oficial porque estaba del lado ganador. ¡Pero deberías haber visto las caras de esos ratas de escritorio! ¡Pensaban que lo estaba fingiendo, que estaba pretendiendo perder la memoria! Seguían preguntando por mi familia.";
			link.l1 = "Bueno, ¿qué les dijiste?";
			link.l1.go = "BM_Irons_12";
		break;
		
		case "BM_Irons_12":
			dialog.text = "¿Qué les dije? Les dije que no recordaba. Y no mentía, nunca conocí a mis padres. Me criaron las calles, los obreros y los sirvientes en los barrios bajos. Me uní a la Revolución por ellos. Aunque la ingratitud de la gente es asombrosa: si hubiera perdido un brazo o una pierna, se habrían visto obligados a darme una jubilación inmediata a un héroe como yo. Y por cierto, ¡casi pierdo la cabeza, literalmente!";
			link.l1 = "Bueno, ¿cómo llegaste al Nuevo Mundo, héroe de guerra?";
			link.l1.go = "BM_Irons_13";
		break;
		
		case "BM_Irons_13":
			dialog.text = "¿Lo dudas? Luchar por el pueblo, ¿qué no hay de heroico en eso? ¡Espero que algún día mariquitas como tú sepan lo que es la verdadera libertad!";
			link.l1 = "Aunque la libertad es algo bueno, de alguna manera lo hiciste sonar como una amenaza. Está bien, Tommy, sigue.";
			link.l1.go = "BM_Irons_14";
		break;
		
		case "BM_Irons_14":
			dialog.text = "Ay. Recibí mi renuncia después de que ganáramos la Revolución, y luego me di cuenta de que no podía hacer nada más que disparar y golpear a la gente en la cara. Y no puedes reincorporarte al ejército, se reirían de ti, especialmente después de haber luchado tanto por mi renuncia. Je, me parece que incluso si hubiera perdido un brazo o una pierna, las ratas de escritorio habrían pensado que los estaba escondiendo en algún lugar para cosérmelos de nuevo más tarde una vez que obtuviera mis papeles de salida, ¡ja-ja-ja!";
			link.l1 = "Eso es gracioso. Pero aún no me has dicho cómo terminaste aquí.";
			link.l1.go = "BM_Irons_15";
		break;
		
		case "BM_Irons_15":
			dialog.text = "Oh, eres tan aburrido. ¿No te enseñaron paciencia, "+GetSexPhrase("mozo","chica")+"? No tenía nada que hacer en casa más que disparar a patos y ciervos, así que fui al Nuevo Mundo. Navegué con piratas por un tiempo para divertirme, y cuando me cansé de la anarquía, me convertí en mercenario.";
			link.l1 = "No es una historia muy original.";
			link.l1.go = "BM_Irons_16";
		break;
		
		case "BM_Irons_16":
			dialog.text = "¿Tal vez tengas uno mejor? No necesitas un guardaespaldas, ¿por casualidad? Porque pareces... débil. Me preocupa que no llegues lejos, jeje. Recuerda, es el séquito el que hace a los reyes. Y un mal séquito puede derribarlos.";
			link.l1 = "¿Y qué tipo de "+GetSexPhrase("rey","reina")+" ¿estaría yo con una comitiva como tú? "+GetSexPhrase("Rey","Reina")+" del montón de estiércol?";
			link.l1.go = "BM_Irons_17";
		break;
		
		case "BM_Irons_17":
			dialog.text = "No, ¡no! Te estoy haciendo una oferta genuina, y tú...";
			link.l1 = "Aún no he recibido ninguna oferta. ¿Cuánto pides por tus servicios, Tommy?";
			link.l1.go = "BM_Irons_18";
		break;
		
		case "BM_Irons_18":
			dialog.text = "¡Quinientos doblones por adelantado! Para asegurarme de que hablas en serio y no eres solo un fracaso. Y una tarifa mensual después de eso. Creo que podemos llegar a un acuerdo.";
			link.l1 = "Y tú no...";
			link.l1.go = "BM_Irons_19";
		break;
		
		case "BM_Irons_19":
			dialog.text = "... ¿crees que tienes agallas? Je, ni siquiera voy a discutir contigo, ¿viste cómo disparé a ese cornudo desde el faro? ¡De un solo tiro! Tampoco hay regateos, si es eso lo que piensas. Tienes que demostrar que puedes permitirte un profesional como yo.";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "¡Sí, puedo! Quinientas piezas de oro. Aquí tienes.";
				link.l1.go = "BM_Irons_Hire1";
			}
			link.l2 = "Tuviste suerte con ese disparo. Y ahora estás intentando inflar tu valor con fanfarronerías. Puedo prescindir de un profesional como tú. Es demasiado honor y demasiado dinero.";
			link.l2.go = "BM_Irons_NoHire1";
			link.l3 = "No puedo permitírmelo ahora mismo, ya que no llevo tanto en mis bolsillos. Quédate aquí y no vayas a ninguna parte - conseguiré el oro del barco y volveré.";
			link.l3.go = "BM_Irons_Wait1";
		break;
		
		case "BM_Irons_Hire1":
			RemoveDublonsFromPCharTotal(250);
			
			dialog.text = "¡No eres tan malo como pensaba! Pero será mejor que te asegures de que no me aburra. Sería un desperdicio de mi talento, ¿no crees? Tommy y "+pchar.name+"¡Sacudamos el Caribe!";
			link.l1 = "Aprende a respetar la cadena de mando, Tommy. Y en segundo lugar, soy el capitán para ti. ¿Entiendes?";
			link.l1.go = "BM_Irons_Hire2";
		break;
		
		case "BM_Irons_Hire2":
			dialog.text = "Heh, lo hago, Capitán Aburrido, "+GetSexPhrase("señor","señorita")+".";
			link.l1 = "Oh, ya empiezo a arrepentirme de esto...";
			link.l1.go = "Irons_hire";
		break;
		
		case "Irons_Hire":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			DeleteAttribute(npchar, "LifeDay");
			LAi_SetImmortal(npchar, false);
			npchar.quest.OfficerPrice = 15000;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.CanTakeMushket = true;
			pchar.questTemp.IronsItemsBlock = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Irons_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_SetHP(npchar, 170.0, 170.0);
			
			// Костыли, нужно украсить интерфейс офицера ==>
			//RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			//TakeItemFromCharacter(npchar, "unarmed");
			//GiveItem2Character(npchar, "blade_42");
			//EquipCharacterByItem(npchar, "blade_42");
			//EquipCharacterByItem(npchar, "mushket1");
			//EquipCharacterByItem(npchar, "indian_2");
			// <== Костыли, нужно украсить интерфейс офицера
			
			if (CheckAttribute(pchar, "questTemp.BM_hireInGrot"))
			{
				AddQuestRecord("BlackMark", "4");
			}
			else
			{
				AddQuestRecord("BlackMark", "1");
			}
			
			// Продолжение через месяц в джунглях
			SetTimerCondition("BM_FirstJungle_Time", 0, 0, 14, false);
		break;
		
		case "BM_Irons_NoHire1":
			dialog.text = "Bueno, eres un idiota, joven "+GetSexPhrase("hombre","Mujer")+"¡Y completamente carente de juicio. Sugiero que lo arregles o no durarás mucho. Especialmente en el Archipiélago.";
			link.l1 = "Me las arreglaré sin ti, Tommy. Adiós.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsGoodbye");
		break;
		
		case "BM_Irons_Wait1":
			dialog.text = "¿Hablas en serio? ¡Un montón de soldados acaban de morir aquí, genio! Probablemente enviarán otro escuadrón pronto. No, podría cerrar la puerta del faro y organizar una defensa, pero ¿quiero hacerlo? No.";
			link.l1 = "¿Entonces qué sugieres?";
			link.l1.go = "BM_Irons_Wait2";
		break;
		
		case "BM_Irons_Wait2":
			dialog.text = "Reúnete conmigo en una cueva en la jungla. Te daré un par de días para ganar lo suficiente para pagar por mis servicios - sabes cómo manejar una hoja, tal vez lo logres.";
			link.l1 = "¿Hablas en serio? Allí estarás como una rata acorralada.";
			link.l1.go = "BM_Irons_Wait3";
		break;
		
		case "BM_Irons_Wait3":
			dialog.text = "Solo si me buscan específicamente, con un gran destacamento. Así que creo que estaré bien. Y ahora debo irme - estarán aquí pronto. Hasta luego.";
			link.l1 = "Sí, yo también debo irme, por si acaso.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsToCave");
		break;
		
		case "BM_Irons_WaitInCave1":
			dialog.text = "¡Ah, ahí estás! Empezaba a pensar que no tenías lo necesario para ganar dinero. A veces pienso que personas como tú nacen con eso. Y si no, mueren en la pobreza sin trabajar un día como gente honesta.";
			link.l1 = "Bueno, bueno, Tommy. Si no quieres unirte a mi tripulación, entonces no lo hagas. Veo que te gusta anidar en este agujero.";
			link.l1.go = "BM_Irons_WaitInCave2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Irons_WaitInCave2":
			dialog.text = "Evidentemente no te has escondido en fosas durante la temporada de lluvias en Irlanda, "+GetSexPhrase("mozalbete","mi chica")+"¡Pero ir contigo es mejor que esconderme aquí. Ahora, sobre ese oro...";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Aquí tienes tu oro.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "Aún no lo tengo. Pensé en comprobar si te habías largado a otro lugar.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_Irons_HireInCave1":
			RemoveDublonsFromPCharTotal(250);
			pchar.quest.BM_IronsTimeOver.over = "yes";
			pchar.questTemp.BM_hireInGrot = true;
			
			dialog.text = "¡Ahora estamos hablando! ¿Qué hacemos a continuación... Capitán?";
			link.l1 = "Primero que nada, salgamos de este lugar húmedo, o empezaré a estornudar.";
			link.l1.go = "BM_Irons_HireInCave2";
		break;
		
		case "BM_Irons_HireInCave2":
			dialog.text = "Oh, deberías probar la guerra. Me siento casi como en casa en lugares como este.";
			link.l1 = "Ya veo, así que obtuviste tu renuncia y te olvidaste del respeto y la subordinación, ¿eh, Tommy? No te preocupes, no dudaré en enseñarte de nuevo si es necesario. Ahora vámonos.";
			link.l1.go = "Irons_hire";
		break;
		
		case "BM_Irons_NoHireInCave1":
			NextDiag.TempNode = "BM_Irons_WaitInCave3";
			
			dialog.text = "Je, ¡Tommy Irons nunca huye! Mantiene su palabra. ¿Mantendrás la tuya?";
			link.l1 = "Trabajando en ello.";
			link.l1.go = "Exit";
		break;
		
		case "BM_Irons_WaitInCave3":
			dialog.text = "¿Trajiste el oro?";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Aquí está tu oro.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "No lo tengo todavía. Pensé en comprobar si te habías ido a otro sitio.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_IronsJungleUhodit":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			
			sld = characterFromID("Irons");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.lifeday = 0;
			LAi_CharacterDisableDialog(sld);
			GiveItem2Character(sld, "blade_42");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			//LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			AddQuestRecord("BlackMark", "5");
			AddQuestUserData("BlackMark", "sSex1", GetSexPhrase("","а"));
			CloseQuestHeader("BlackMark");
		break;
		
		case "BM_IronsFirstJungle_1":
			dialog.text = "Escucha, Capitán...";
			link.l1 = "¿Qué sucede, Tommy?";
			link.l1.go = "BM_IronsFirstJungle_2";
		break;
		
		case "BM_IronsFirstJungle_2":
			dialog.text = "¿No tendrías una ronda extra de municiones contigo? No solo una bala, sino un cartucho completo envuelto en papel.";
			link.l1 = "¿Es esta otra de tus bromas? Te doy balas y cartuchos regularmente, lo que necesites. ¿Y por qué exactamente un cartucho, no un puñado?";
			link.l1.go = "BM_IronsFirstJungle_3";
		break;
		
		case "BM_IronsFirstJungle_3":
			dialog.text = "¿Por qué estás tomando tan mal mi petición? No estoy pidiendo malditas perlas, solo un cartucho. Incluso esperé hasta que estuviéramos en la jungla para no distraerte de los asuntos en la ciudad. Entonces, ¿tienes una ronda?";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "Sí, tengo una ronda. Aquí tienes. Solo no me hagas una broma estúpida con esa bala. ¿Entiendes, Tommy?";
				link.l1.go = "BM_IronsFirstJungle_7";
			}
			link.l2 = "No en este momento, no. No es como si llevara un solo cartucho en mi bolsillo, preguntándome qué pasaría si Tommy pidiera uno...";
			link.l2.go = "BM_IronsFirstJungle_4";
		break;
		
		case "BM_IronsFirstJungle_4":
			dialog.text = "Bueno, es un buen punto, y eres rápido para captar las cosas, jeje. Pero me temo que aquí es donde nos separamos, entonces.";
			link.l1 = "¿Hablas en serio? ¿Estás ofendido por una bala? Vamos, vayamos al barco y consíguete una allí. Si lo necesitas tan urgentemente, te conseguiré una, diez, lo que necesites.";
			link.l1.go = "BM_IronsFirstJungle_5";
		break;
		
		case "BM_IronsFirstJungle_5":
			dialog.text = "No.  No hay nada especial en ti, después de todo. Un buen capitán siempre puede proveer a su tripulación con todo lo que necesitan. Así que me iré.";
			link.l1 = "¿Y si estuviésemos en el mar, se nos acabara el ron, y quisieras más? ¿Desatarías el esquife y zarparías? ¿O te lanzarías al agua?";
			link.l1.go = "BM_IronsFirstJungle_6";
		break;
		
		case "BM_IronsFirstJungle_6":
			dialog.text = "¡Ja-ja-ja! Me reí, pero en este triste momento ni siquiera una buena broma ayudará. Adiós, Capitán Aburrido.";
			link.l1 = "Bueno, al diablo contigo, Tommy. Adiós.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsFirstJungle_7":
			dialog.text = "No puedo prometer nada, je-je. Un buen chiste mantiene las cosas ligeras. Pero gracias, por supuesto.";
			link.l1 = "Está bien, vamos, bribón.";
			link.l1.go = "BM_IronsFirstJungle_8";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsFirstJungle_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			Return_IronsOfficer();
			SetTimerCondition("BM_SecondJungle_Time", 0, 0, 14, false);
		break;
		
		case "BM_IronsSecondJungle_1":
			dialog.text = "¡Eh, Capitán!";
			link.l1 = "¿Sí, Tommy?";
			link.l1.go = "BM_IronsSecondJungle_2";
		break;
		
		case "BM_IronsSecondJungle_2":
			dialog.text = "¿Tienes otro cartucho de papel?";
			link.l1 = "¿Qué le pasó al último? ¿Y cuál fue esa broma sobre el cartucho? He estado esperando dos semanas por alguna estúpida broma tuya, pero nada.";
			link.l1.go = "BM_IronsSecondJungle_3";
		break;
		
		case "BM_IronsSecondJungle_3":
			dialog.text = "Ah, será un chiste de muerte, confía en mí. Te encantará, jeje. Solo que todavía no lo he armado del todo. Y, ¿qué hay del cartucho?";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "Aquí tienes. Espero disfrutar realmente de tu próxima broma. ¿Y dónde pusiste la última ronda? Te di muchas de esas. ¿O guardas la munición para luchar en un lugar y las bromas en otro?";
				link.l1.go = "BM_IronsSecondJungle_7";
			}
			link.l2 = "¡No cargo municiones para tus estúpidas bromas, Tommy! ¡Podrías haber pedido todo un lote en lugar de solo un cartucho hace dos semanas!";
			link.l2.go = "BM_IronsSecondJungle_4";
		break;
		
		case "BM_IronsSecondJungle_4":
			dialog.text = "¡Lo hice! Pensé que quienquiera que afirme ser mi capitán siempre guarda lo que su tripulación necesita.";
			link.l1 = "No pretendo ser nada, Tommy. Elegí ser yo mismo hace mucho tiempo. Quien esté cómodo conmigo, bien. Si no, también bien.";
			link.l1.go = "BM_IronsSecondJungle_5";
		break;
		
		case "BM_IronsSecondJungle_5":
			dialog.text = "Heh, tú y yo somos parecidos en ese aspecto. Pero tengo ciertos requisitos para mi capitán. Y ya no los cumples, joven. Aquí es donde nos separamos.";
			link.l1 = "¿Hablas en serio? ¿Porque no tenía un maldito cartucho de papel?";
			link.l1.go = "BM_IronsSecondJungle_6";
		break;
		
		case "BM_IronsSecondJungle_6":
			dialog.text = "Eso está fuera de cuestión. Usualmente aconsejo a la gente hacer lo que les gusta y tomar lo que quieren de la vida. Te aconsejaría pensar más en tu gente en el futuro. Adiós.";
			link.l1 = "Y te aconsejaría que cuides de tu cabeza - le han hecho más daño de lo que te das cuenta. Adiós, Tommy.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsSecondJungle_7":
			dialog.text = "Lo descubrirás. Todo a su debido tiempo, jeje.";
			link.l1 = "Oh, tengo un mal presentimiento sobre esto, Tommy...";
			link.l1.go = "BM_IronsSecondJungle_8";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsSecondJungle_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			Return_IronsOfficer();
			SetTimerCondition("BM_ThirdJungle_Time", 0, 0, 14, false);
		break;
		
		case "BM_IronsThirdJungle_1":
			dialog.text = "Tengo una pregunta para usted, Capitán.";
			link.l1 = "¿Qué pasa, Tommy?";
			link.l1.go = "BM_IronsThirdJungle_2";
		break;
		
		case "BM_IronsThirdJungle_2":
			dialog.text = "¿No lo adivinaste? Adivinar es una habilidad útil, jeje. Tú, yo, la jungla... Hace unas dos semanas, tuvimos esta conversación. Necesito otro cartucho de papel.";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "Esto se está convirtiendo en una tradición divertida, ¿no es así? Han pasado dos semanas - Tommy pide un cartucho. Aquí tienes. ¿Cuántos más necesitas para esa broma tuya?";
				link.l1.go = "BM_IronsThirdJungle_5";
			}
			link.l2 = "¿Cuánto tiempo más, Tommy?! ¿Cuánto tiempo va a continuar esto? ¿Acaso ustedes, Ironsides, solo reciben un cartucho antes de cada batalla?! No tengo que llevar una bala conmigo en todo momento por tus caprichos, ¡lo sabes!";
			link.l2.go = "BM_IronsThirdJungle_3";
		break;
		
		case "BM_IronsThirdJungle_3":
			dialog.text = "En realidad, como mi capitán, es tu deber proporcionarme todo lo que necesito para las batallas y más.";
			link.l1 = "Estás confundido, Tommy. Es tu deber obedecer las órdenes de tu capitán. Siempre les suministro todo: medicinas, municiones, ron. ¡El hecho de que no tomes lo que necesitas a tiempo y luego actúes como un mendigo es solo culpa tuya!";
			link.l1.go = "BM_IronsThirdJungle_4";
		break;
		
		case "BM_IronsThirdJungle_4":
			dialog.text = "Eres tan listo, ¿por qué no has logrado nada de interés aquí hasta ahora? Te diré por qué. Porque no piensas a futuro, y nunca estás preparado para nada. No sabes lo que estás haciendo, aburrido. No reconoceré a una persona así como mi comandante, así que adiós.";
			link.l1 = "¡Y tú no usas la cabeza para nada! ¡Buen viaje, maldito bufón!";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsThirdJungle_5":
			dialog.text = "Este servirá, jeje.";
			link.l1 = "¿Por fin lo has conseguido, entonces? ¿Pero para qué?";
			link.l1.go = "BM_IronsThirdJungle_6";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsThirdJungle_6":
			dialog.text = "Solo te estaba gastando una broma, viendo si volvías a ser tu gruñón de siempre. Jeje. Pero gracias por el cartucho.";
			link.l1 = "Tus chistes son extraños, Tommy.";
			link.l1.go = "BM_IronsThirdJungle_7";
		break;
		
		case "BM_IronsThirdJungle_7":
			dialog.text = "Eso también era una broma. No los coleccionaba; los seleccionaba. Necesitaba un cartucho que fuera casi perfecto. Este servirá. Sí, con este cartucho, la bala irá lejos y certera. Igual que cuando le volé la cabeza al viejo Reasley, ¡ja, ja, ja!";
			link.l1 = "Viejo Reasley, dijiste... Frankie el Cornudo, ¿verdad? ¿El que disparaste en el faro? Entonces, ¿se conocen desde hace mucho tiempo?";
			link.l1.go = "BM_IronsThirdJungle_8";
		break;
		
		case "BM_IronsThirdJungle_8":
			dialog.text = "¿Qué? Oh, demonios, se me escapó. Pero no me importa, nunca he sido bueno para mentir o guardar secretos.";
			link.l1 = "Supongo que la segunda bala estaba destinada a alguien en particular, ¿verdad, Tommy?";
			link.l1.go = "BM_IronsThirdJungle_9";
		break;
		
		case "BM_IronsThirdJungle_9":
			dialog.text = "Bien, genio. Pues, me conozco a mí mismo y mis objetivos, y no me avergüenzo. Por eso no me importa lo que pienses - te contaré toda la historia, ¿por qué demonios no?";
			link.l1 = "Bueno, dime entonces. No hará daño saber en qué andas.";
			link.l1.go = "BM_IronsThirdJungle_10";
		break;
		
		case "BM_IronsThirdJungle_10":
			dialog.text = "Bueno, no me interrumpas, como sueles hacer. Había dos bastardos en la compañía conmigo - Francis Reasley y Gabriel Callow. ¡Ratas de verdad! ¡Incluso peores que esos ratas de escritorio que no querían darme mi renuncia, la cual, no fue fácil de conseguir!";
			link.l1 = "¿Y qué hicieron? Especialmente el segundo, Callow. ¿También te acostaste con su esposa? ¿Y él también envió soldados tras de ti?";
			link.l1.go = "BM_IronsThirdJungle_11";
		break;
		
		case "BM_IronsThirdJungle_11":
			dialog.text = "Calla la boca, ¿quieres? Aunque... no me importaría, jeje. Pero no. Los realistas nos atacaron ese día. Caballería también. Eran muchos más. Gabe y Frankie corrieron como conejos asustados. Pero yo me quedé con los muchachos. Fui el único que sobrevivió. He olvidado mucho de mi infancia y juventud, pero no eso.";
			link.l1 = "¿Y quieres venganza porque huyeron? No todos luchan por una idea. Todos quieren sobrevivir. O casi todos. Incluso si alguien lucha por la Revolución, podrían haberse unido por accidente y arrepentirse de ello.";
			link.l1.go = "BM_IronsThirdJungle_12";
		break;
		
		case "BM_IronsThirdJungle_12":
			dialog.text = "Ja, si cazara a todos los cobardes, tendría que disparar al mundo entero. Cobardes, al diablo con ellos. Pero ellos me traicionaron. Dijeron a todos que yo traicioné a la Revolución y masacré a toda nuestra compañía por órdenes de los partidarios del Rey. Te mentí sobre algo, Capitán.";
			link.l1 = "¿Qué es? Además del hecho de que mentiste sobre Frankie cazándote solo por lo que hiciste con su esposa?";
			link.l1.go = "BM_IronsThirdJungle_13";
		break;
		
		case "BM_IronsThirdJungle_13":
			dialog.text = "¡No, no! No te mentí, solo que no te conté todo. Hay una diferencia. Sobre lo que mentí fue sobre la renuncia. No hubo renuncia. Hubo un tribunal. Y el viejo afortunado Tommy: decidieron no colgarlo sino enviarlo a las canteras en las colonias del sur. Barbados, para ser exactos.";
			link.l1 = "Sí, eso fue afortunado. ¿Cuántos años trabajaste allí?";
			link.l1.go = "BM_IronsThirdJungle_14";
		break;
		
		case "BM_IronsThirdJungle_14":
			dialog.text = "Ninguno. Desde que el tribunal terrenal me condenó por culpa de esos ratas, el celestial allá arriba decidió salvarme. Tan pronto como cruzamos al Archipiélago, sentimos su atmósfera - nuestro barco fue abordado por piratas.";
			link.l1 = "¿Así que en lugar de las canteras y plantaciones de Barbados, fuiste vendido por piratas a la esclavitud? Pero dijiste que nunca trabajaste en las canteras.";
			link.l1.go = "BM_IronsThirdJungle_15";
		break;
		
		case "BM_IronsThirdJungle_15":
			dialog.text = "Eso es lo que dije: alguien allá arriba decidió rescatarme. ¡Vaya rescate fue, jeje! Lo has entendido bien: los piratas vencieron a aquellos que disfrutan abusar de hombres atados y encadenados. Pero aún así fue una pelea ardiente, tan ardiente como el sol aquí. Y nuestros salvadores sufrieron algunas bajas. Así que ofrecieron a todos los que querían unirse a ellos.";
			link.l1 = "¿Y te uniste a ellos? Dijiste que navegaste con piratas.";
			link.l1.go = "BM_IronsThirdJungle_16";
		break;
		
		case "BM_IronsThirdJungle_16":
			dialog.text = "¡Demonios, sí! Los mejores años de mi vida. Jack Mills era un capitán con mayúscula C - Espero que seas como él algún día. Navegué en su 'Grulla' durante unos dos años hasta...";
			link.l1 = "... hasta que te cansaste de la anarquía, como dijiste? ¿Por qué dices que esos fueron los mejores años de tu vida?";
			link.l1.go = "BM_IronsThirdJungle_17";
		break;
		
		case "BM_IronsThirdJungle_17":
			dialog.text = "Eh... hasta que oí que esos dos traidores también acabaron en el Archipiélago. Sí, lo sé, te dije que estaba harto de la piratería en alta mar y todo eso. Y ya te he dicho que no me importa lo que pienses. Eso sigue siendo cierto, pero no te conocía bien cuando nos conocimos por primera vez. No sabía cómo reaccionarías. Por eso dije cosas diferentes.";
			link.l1 = "Eres un mentiroso, ¡Tommy! Pero está bien, ¿por qué dejaste el 'Grulla'?";
			link.l1.go = "BM_IronsThirdJungle_18";
		break;
		
		case "BM_IronsThirdJungle_18":
			dialog.text = "Porque Jack era un verdadero líder, así que dijo que no haría un desvío por un hombre, esperarlo, jugar a la venganza y meterse con oficiales prominentes de la Marina Británica en lugar de atacar a los gordos barcos mercantes.";
			link.l1 = "¿Oficiales prominentes? Frank era un civil, creo.";
			link.l1.go = "BM_IronsThirdJungle_19";
		break;
		
		case "BM_IronsThirdJungle_19":
			dialog.text = "Eh, no siempre fue uno de ellos. Siempre fue algo, turbio. Y cuando intentó tenderle una trampa a alguien, lo echaron en desgracia. Intentó navegar en un comerciante, pero el trabajo honesto no era lo suyo. Terminó estableciéndose aquí.";
			link.l1 = "Aún no lo llamaría un oficial prominente.";
			link.l1.go = "BM_IronsThirdJungle_20";
		break;
		
		case "BM_IronsThirdJungle_20":
			dialog.text = "No olvides a Gabe. Se hizo teniente en casa. Y obtuvo su comisión aquí en Port Royal como capitán del barco, el 'Principio'.";
			link.l1 = "No suena muy inglés.";
			link.l1.go = "BM_IronsThirdJungle_21";
		break;
		
		case "BM_IronsThirdJungle_21":
			dialog.text = "¡Buen punto! El barco cambió de manos como una doncella de puerto, así que vio todo tipo de cosas. Pero todavía es apto para navegar. Y Gabe es un capitán hábil, maldita sea.";
			link.l1 = "¿Y Jack tenía miedo de tratar con él? ¿Es tan bueno como dices?";
			link.l1.go = "BM_IronsThirdJungle_22";
		break;
		
		case "BM_IronsThirdJungle_22":
			dialog.text = "¡Está bien, está bien! Más bien, no quería perder el tiempo por mí. Hablando de Jack, me gustaron un par de tradiciones que vi por primera vez de él: el tablón y repartir marcas negras. Eso me dio una idea divertida en aquel entonces.";
			link.l1 = "¿Marcas negras... ? ¿Te refieres a una mancha negra, verdad? ¿Y qué fue, Tommy? No creo que él sabría qué hacer si le hubieras entregado una mancha negra. ¿Eso fue lo que pasó? Querías entregarla, y él te atacó en cuanto te vio, así que corriste al faro, y él llevó un escuadrón de soldados con él, diciéndoles que eras un pirata?";
			link.l1.go = "BM_IronsThirdJungle_23";
		break;
		
		case "BM_IronsThirdJungle_23":
			dialog.text = "Prefiero llamarlo una marca negra. Suena mejor. Una simple marca negra no le habría hecho darse cuenta de nada. Pero una marca negra hecha con nuestro pañuelo de seda, que era una característica distintiva de nuestra compañía, eso lo entendería. La deslicé discretamente en su bolsillo. Luego me aseguré de que me viera dirigiéndome al faro. Ya sabes el resto.";
			link.l1 = "¿Y los contrabandistas?";
			link.l1.go = "BM_IronsThirdJungle_24";
		break;
		
		case "BM_IronsThirdJungle_24":
			dialog.text = "En el lugar equivocado, en el momento equivocado. Incluso me dieron un poco de lástima. Pero solo un poco, jeje.";
			link.l1 = "¿Y para Frankie?";
			link.l1.go = "BM_IronsThirdJungle_25";
		break;
		
		case "BM_IronsThirdJungle_25":
			dialog.text = "¿A quién le importa ahora? Tenemos peces más grandes que freír. Eso deja a Gabe. Eso va a ser complicado. Necesitamos...";
			link.l1 = "¿Nosotros?";
			link.l1.go = "BM_IronsThirdJungle_26";
		break;
		
		case "BM_IronsThirdJungle_26":
			dialog.text = "Bueno, es una cosa aprender una historia interesante, ¡y otra crearla uno mismo! Así que aquí está el plan. Necesitaremos dejarle a Gabe otra marca negra especial - ya tengo una hecha. Luego seguiremos su rastro hasta Portland Cove, donde nos ocuparemos de él sin dejar rastro.";
			link.l1 = "¿Y dónde vamos a plantarlo?";
			link.l1.go = "BM_IronsThirdJungle_27";
		break;
		
		case "BM_IronsThirdJungle_27":
			dialog.text = "Ja ja ja, eso es lo que quise decir cuando dije que deseaba que fueras más como Jack, Capitán. Vamos, no seas aburrido, ¡puedo ver que tus ojos arden!";
			link.l1 = "Más bien, en realidad estaba algo interesado en tu historia.";
			link.l1.go = "BM_IronsThirdJungle_28";
		break;
		
		case "BM_IronsThirdJungle_28":
			dialog.text = "¡En su casa, por supuesto! ¿Qué clase de pregunta es esa? Se ha establecido en Port Royal. Así que tú y yo atracaremos en la cala, para que podamos dejar la isla si algo sale mal.";
			link.l1 = "¿Sabes dónde está su casa?";
			link.l1.go = "BM_IronsThirdJungle_29";
		break;
		
		case "BM_IronsThirdJungle_29":
			dialog.text = "No.  Pero no es difícil de averiguar. Preguntaremos a los borrachos - venderían a su madre si les invitas a un trago o dos. Bueno, ¿qué piensas de mi plan?";
			if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) > 24 && GetSummonSkillFromName(pchar, SKILL_GRAPPLING) > 24 && GetSummonSkillFromName(pchar, SKILL_SAILING) > 24)
			{
				link.l1 = "Si es el capitán de un barco con destino a Jamaica, está de patrulla todo el tiempo en las aguas de la isla. Atacar bajo una bandera falsa es mejor que intentar algo en la ciudad.";
				link.l1.go = "BM_IronsThirdJungle_Sea1";	// Морской вариант
				notification("Skill Check Passed", SKILL_SAILING);
				notification("Skill Check Passed", SKILL_ACCURACY);
				notification("Skill Check Passed", SKILL_GRAPPLING);
			}
			else
			{
				if (GetSummonSkillFromName(pchar, SKILL_SAILING) < 25) notification("Skill Check Failed (25)", SKILL_SAILING);
				if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) < 25) notification("Skill Check Failed (25)", SKILL_ACCURACY);
				if (GetSummonSkillFromName(pchar, SKILL_GRAPPLING) < 25) notification("Skill Check Failed (25)", SKILL_GRAPPLING);
			}
			link.l2 = "No es sin fallos, y estás dejando mucho al azar. Pero en general, es factible. Estoy contigo, Tommy. Te deshiciste de uno, no puedes dejar ir al otro, ¿verdad?";
			link.l2.go = "BM_IronsThirdJungle_Land1";	// Сухопутный вариант
			link.l3 = "No me voy a involucrar en tu venganza y arriesgar mi relación con Inglaterra por esta aventura donde tanto depende del azar, Tommy.";
			link.l3.go = "BM_IronsThirdJungle_Otkaz1";	// Отказ
		break;
		
		case "BM_IronsThirdJungle_Sea1":
			dialog.text = "Eres un temerario, ¡Capitán! Empiezo a apreciarte. Pero Gabe en el viejo 'Principio' no es presa fácil, es mucho más peligroso que otros capitanes en un barco como ese.";
			link.l1 = "¿Qué piensas que soy, un cobarde, Tommy? Lo abordaremos nosotros mismos, y podrás tener una charla de corazón a corazón con él. Dale la marca negra justo antes de que sea depuesto.";
			link.l1.go = "BM_IronsThirdJungle_Sea2";
		break;
		
		case "BM_IronsThirdJungle_Sea2":
			dialog.text = "Je,   puede que tú no seas un cobarde,   pero él sí lo es, aunque es inteligente. No atacará a un soldado o incluso a un pirata más grande que su barco. Si ve algo así en el horizonte, se esconderá bajo el ala del fuerte.";
			link.l1 = "Hmm, ¿qué tal los barcos mercantes?";
			link.l1.go = "BM_IronsThirdJungle_Sea3";
		break;
		
		case "BM_IronsThirdJungle_Sea3":
			dialog.text = "¡Sí, eso podría funcionar! Pero, de nuevo, nada más grande que una barca. Gabe no es solo un cobarde, nunca ha sido lo suficientemente codicioso como para dejar que eso pese más que su cautela.";
			link.l1 = "Esperemos que funcione, Tommy. Entonces, una barca de quinta categoría ondeando colores españoles o holandeses. ¡Prepárate para encontrarte con tu viejo camarada de guerra!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SeaVariant");
		break;
		
		case "BM_IronsThirdJungle_Land1":
			dialog.text = "¡Sabía que podía contar contigo! Puede que algún día seas un mejor capitán que Jack. Y en cuanto a mi suerte... Me ha llevado hasta aquí, así que volveré a confiar en ella. ¿Nos vamos, entonces?";
			link.l1 = "Sí, no alarguemos esto demasiado. Cuanto antes termine, mejor.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_LandVariant");
		break;
		
		case "BM_IronsThirdJungle_Otkaz1":
			dialog.text = "Je, esperaba lo contrario, pero me temía esto - no tienes agallas para este tipo de cosas, "+GetSexPhrase("mozalbete","mi chica")+". Cualquier capitán de verdad ha tenido al menos algunas ocasiones como esa donde ha tratado discretamente con ratas. A veces incluso con sus propias ratas.";
			link.l1 = "Supongo que se supone que debo caer en esa provocación y decir que he cambiado de opinión y demostrar que soy un verdadero capitán, ¿eh, Tommy? Pero entiendo tu deseo de venganza. No voy a obligarte a dejar la tripulación como lo hizo Jack. ¿Cuánto tiempo necesitas para eso? Llegaré a Jamaica para entonces.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz2";
		break;
		
		case "BM_IronsThirdJungle_Otkaz2":
			dialog.text = "Ja ja ja, estás creciendo. Casi te respeto por no caer en la trampa. Pero no tienes que esperar y recogerme después; terminaré esto yo mismo. Después de todo, lo único que siempre quise es alguien dispuesto a hacer algo por mí como mi capitán. Así que adiós. Cuida de Inglaterra, ja-ja.";
			link.l1 = "Eres realmente extraño. Pero como quieras. ¡Adiós! Y buena suerte con tu venganza, Tommy.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz3";
		break;
		
		case "BM_IronsThirdJungle_Otkaz3":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			
			sld = characterFromID("Irons");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			AddQuestRecord("BlackMark", "6");
			AddQuestUserData("BlackMark", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("BlackMark", "sSex1", GetSexPhrase("к","чка"));
			CloseQuestHeader("BlackMark");
		break;
		
		case "BM_IronsJamaicaShore1":
			dialog.text = "Estupendo, podemos retirarnos rápidamente de aquí si surge la necesidad. Toma esto: dale a Gabe la nota y una marca negra una vez que descubras dónde vive y cuándo está en casa.";
			link.l1 = "Oh, así que ahora estás dando las órdenes, Tommy. Pero recuerda, todavía soy tu capitán. ¿Qué planeas hacer mientras estoy en el pueblo?";
			link.l1.go = "BM_IronsJamaicaShore2";
		break;
		
		case "BM_IronsJamaicaShore2":
			dialog.text = "Heh, ¿cómo podría olvidar eso, Capitán Aburrido? Si Gabe me ve por las calles, o dará la alarma o se escabullirá de la isla, ese maldito cobarde. No te preocupes, prepararé una emboscada justo aquí, jejeje.";
			link.l1 = "Una emboscada, dices. Está bien, Tommy. Vamos a darle a tu viejo camarada de guerra una reunión apropiada, ¡ja ja ja ja!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsJamaicaGo");
		break;
		
		case "BM_Pyanitsa_0":
			dialog.text = "¡Hic! ¡Ese es un ron estupendo! Hic... ¡Salud!";
				link.l1 = "Escucha, compañero, ¿qué se dice en la ciudad sobre el Capitán Gabriel Callow?";
			link.l1.go = "BM_Pyanitsa_1";
			DelLandQuestMark(npchar);	//Удаляем квестмарку
		break;
		
		case "BM_Pyanitsa_1":
			dialog.text = "¿Viejo Gabe?! ¡Sólo cosas buenas! ¿Por qué, hic, qué es eso?";
			link.l1 = "Oh, ¿de veras? Me alegra oírlo. Bueno, hay problemas con un pirata. El Comandante se encarga principalmente de los asuntos de tierra, y no quiero molestar a Su Señoría.";
			link.l1.go = "BM_Pyanitsa_2";
		break;
		
		case "BM_Pyanitsa_2":
			dialog.text = "¡Entonces ve directamente a Gabe, te digo! No hay un capitán más honesto o valiente en la ciudad que Gabe. Incluso el Coronel Doyley lo tiene en alta estima. Navega en un barco que una vez perteneció al mismísimo Nicolas Sharp, ¿puedes creerlo?";
			link.l1 = "No estoy lo suficientemente borracho como para creer eso todavía, camarada.";
			link.l1.go = "BM_Pyanitsa_3";
		break;
		
		case "BM_Pyanitsa_3":
			dialog.text = "A-Ah, ¡pero si lo eres! ¡Es el Principio! ¿Te suena, eh?";
			link.l1 = "¿Un barco español del trofeo, dices? ¿Por qué?";
			link.l1.go = "BM_Pyanitsa_4";
		break;
		
		case "BM_Pyanitsa_4":
			dialog.text = "¿Cuándo fue la última vez que viste un rosado con tus propios ojos, eh? ¡Sé lo que digo, caray!";
			link.l1 = "Bueno, no sé si el diseño del barco es tan inusual.";
			link.l1.go = "BM_Pyanitsa_5";
		break;
		
		case "BM_Pyanitsa_5":
			dialog.text = "¡Pero lo es! ¡Nadie comandaría tal chatarra ahora, con todos los nuevos diseños alrededor! ¡Dejaron de construirlos en los astilleros hace casi t-treinta años! Nic la navegó él mismo, te lo digo.";
			link.l1 = "Está bien, lo compraré. Entonces, ella es el barco. ¿Cómo es que este cascarón no se ha desmoronado aún?";
			link.l1.go = "BM_Pyanitsa_6";
		break;
		
		case "BM_Pyanitsa_6":
			if (sti(pchar.basenation) == ENGLAND) sStr = "our";
			else sStr = "your";
			dialog.text = "Bueno, no es tan rápida como en sus mejores años, ¡como yo después de otro trago, ja-ja-ja! Pero un buen capitán aún puede sacar algo de esta vieja dama. Gabe también intenta no ponerla en la línea de fuego.";
			link.l1 = "Entonces, ¿por qué no ha sido renombrado el barco? El Buque de Su Majestad Azote, tal vez, bajo "+sStr+"¿ antiguo régimen?";
			link.l1.go = "BM_Pyanitsa_7";
		break;
		
		case "BM_Pyanitsa_7":
			dialog.text = "Trad... Trad-trad-tradición, ¡ay! Nic mismo nunca la renombró después de huir de una plantación española en Cuba. Nunca quiso olvidar la experiencia, ¡y tampoco los españoles! Déjame decirte, aquella batalla cerca de la costa de Tendales...";
			if (startHeroType == 4)
			{
				link.l1 = "Tendales, ¿verdad? Huh, la última vez que escuché ese nombre fue cuando era niño. No pensé que aún hubiera alguien que conociera y recordara estas ahora abandonadas rocas.";
				link.l1.go = "BM_Pyanitsa_8";
			}
			else
			{
				link.l1 = "¿Tendales? ¿Dónde está eso?";
				link.l1.go = "BM_Pyanitsa_8";
			}
		break;
		
		case "BM_Pyanitsa_8":
			dialog.text = "¿O fue, ugh, Highrock? N-no, definitivamente no allí... ¡De todos modos, no importa! Nic luchó y ganó en ese rosa, una victoria increíble contra el bergantín Sepia, enviado tras él por Desmond Ray Beltrop, Barón Pirata. Se derramaron sangre mutuamente por mucho tiempo hasta que Nic abatió al propio Desmond.";
			if (startHeroType == 4)
			{
				link.l1 = "¡Vaya, eso es impresionante! Aunque, no esperarías otra cosa de Nicholas. Eh, los Sharps y los Beltrops siempre están juntos, luego separados - aparentemente, la historia realmente se repite de vez en cuando.";
				link.l1.go = "BM_Pyanitsa_9";
			}
			else
			{
				link.l1 = "Impresionante. Entonces, ¿cómo se deshizo Sharp del barco? ¿La vendió en el astillero?";
				link.l1.go = "BM_Pyanitsa_9";
			}
		break;
		
		case "BM_Pyanitsa_9":
			dialog.text = "Nah. Después de ese abordaje, empezó a hacer agua, así que Nic la abandonó. Luego, con la gran marea, la rosa fue llevada a la orilla, justo cerca del pueblo.";
			link.l1 = "Como si a alguien le interesara ese pecio.";
			link.l1.go = "BM_Pyanitsa_10";
		break;
		
		case "BM_Pyanitsa_10":
			dialog.text = "Oh, ¡pero la Marina estaba interesada! Tipos prácticos. Vieron un barco bajo bandera inglesa pero con un nombre español y se interesaron. Nic murió unos años después, pero su barco siguió navegando, cambiando de manos, siempre de manera sangrienta.";
			link.l1 = "Esta es solo otra historia de un barco fantasma, mientras que la capitanía de Gabe es muy real. Así que creo que iré a verlo. ¿Sabes dónde vive?";
			link.l1.go = "BM_Pyanitsa_11";
		break;
		
		case "BM_Pyanitsa_11":
			dialog.text = "¡Ja, ja! ¡Por supuesto, hip, lo sé! ¡Todos lo saben! El viejo Gabe vive junto al viejo molino de viento. Solo rodea la taberna y mira hacia arriba... hip!";
			link.l1 = "¿Cuándo está en casa? Parece que es un hombre ocupado.";
			link.l1.go = "BM_Pyanitsa_12";
		break;
		
		case "BM_Pyanitsa_12":
			dialog.text = "¡Así es, camarada! Tiene mucho que hacer. Sólo está en casa por las tardes, desde las diez en punto. Y se levanta a las seis en punto, todos los días, por su cuenta. ¡Disciplina de hierro!";
			link.l1 = "¡Muchas gracias! Ya he tenido suficiente de estas historias de piratas por ahora.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SearchGabeHouse");
		break;
		
		case "BM_Callow1":
			if (startHeroType == 4) 
			{
				dialog.text = "¿Eres realmente... Rumba? He oído hablar de ti... ¡pero nunca te has vuelto contra los tuyos antes!";
				link.l1 = "Y yo no lo he hecho. Mi disputa no es con mi país. Es contigo, Gabe.";
				link.l1.go = "BM_Callow_Helena1";
			}
			else
			{
				dialog.text = "Eres   no un comerciante...";
				link.l1 = "¡Sorpresa, Gabe! Me dijeron que eras cauteloso e incluso cobarde. La codicia ha nublado tu juicio, ¿verdad? Ningún comerciante buscaría abordar como lo hice yo.";
				link.l1.go = "BM_Callow2";
			}
		break;
		
		case "BM_Callow_Helena1":
			dialog.text = "¿Conmigo? ¿Cuál es el problema? Podríamos tener una conversación adecuada en mi lugar, o incluso en el tuyo. Como capitanes, y... ¡¿QUÉ haces AQUÍ?!";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_Callow2":
			dialog.text = "De hecho. ¿Y tú quién eres? No, al diablo contigo, sin embargo. ¿Quién es ese...?";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_IronsClone1":
			dialog.text = "¿Thomas, eres tú...?";
			link.l1 = "Oh sí, Gabe. Y he venido a castigarte por lo que me hiciste aquel día.";
			link.l1.go = "BM_IronsClone2";
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			CharacterTurnByChr(sld, CharacterFromID("IronsClone"));
			sld = CharacterFromID("IronsClone");
			CharacterTurnByChr(sld, &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)]);
		break;
		
		case "BM_IronsClone2":
			dialog.text = "¿Castigarme a mí?! ¡Cuida tu lengua, Thomas! ¡Si alguno de nosotros merece castigo, eres tú! ¡Dijiste que traerías refuerzos! ¡Y esperamos, muriendo bajo las balas y espadas de la caballería del Rey!";
			link.l1 = "¡Corrí como un condenado para traer ayuda! ¡Pero fui superado por otra maldita fuerza! ¡Los malditos partidarios de Charles estaban por todas partes! ¡Me tenían acorralado, casi muero! Menos mal que pensaron que estaba muerto. ¿Pero sabes lo que vi, Gabe?!";
			link.l1.go = "BM_IronsClone3";
		break;
		
		case "BM_IronsClone3":
			dialog.text = "¿Qué pasa, Tom? ¡¿Estás dispuesto a inventar cualquier historia que puedas para que este hombre te crea?!";
			link.l1 = "Je, ese hombre no me traicionará de todos modos. No es una rata como algunas personas.";
			link.l1.go = "BM_IronsClone4";
		break;
		
		case "BM_IronsClone4":
			dialog.text = "¡No tiene elección! ¡Atacar un barco de la armada inglesa!";
			link.l1 = "Oh, él tuvo una opción desde el principio. Y eligió ayudarme. Tú y Frankie también tuvieron una opción. Eligieron huir para no morir. Y luego regresaron y me encontraron, medio muerto. Y contaron sus viles mentiras en el tribunal. ¡Sabían que nadie me escucharía porque me habían golpeado en la cabeza y había perdido la memoria!";
			link.l1.go = "BM_IronsClone5";
		break;
		
		case "BM_IronsClone5":
			dialog.text = "Nadie te habría escuchado de todos modos. Siempre has sido un... maltrecho, Thomas.";
			link.l1 = "Ah, así que no estás escondiendo lo que hiciste ese día. Tengo algo para ti, Gabe. Una marca negra. Pero ¿de qué sirve dártela ahora que el barco ha sido confiscado y estamos a punto de destriparte?, je je je je je je...";
			link.l1.go = "BM_IronsClone6"; // здесь переход на кейс с боёвкой
		break;
		
		case "BM_IronsClone6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			locCameraTarget(PChar);
			locCameraFollow();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			
			sld = CharacterFromID("IronsClone");
			LAi_SetCheckMinHP(sld, 1, true, "");
			LAi_SetCurHPMax(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "reload", "reload1", "BM_IronsCloneMushket", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "BM_CabinDialog4");
		break;
		
		case "BM_IronsClone8":
			dialog.text = "Bueno, Gabe ha sido depuesto, jejeje. He querido decir eso durante mucho tiempo. Lástima que ya no puedas oírlo, camarada. ¡Oh, espera! Quizás puedas - desde el Infierno.";
			link.l1 = "Vamos, Tommy. Aunque no lo oyera, vio y sabía que este era exactamente tu plan y venganza. Y no había nada que pudiera hacer al respecto.";
			link.l1.go = "BM_IronsClone9";
		break;
		
		case "BM_IronsClone9":
			if (startHeroType == 4) 
			{
				dialog.text = "Heh, ¡tienes razón! ¡Maldita sea, tienes razón! Gracias por ayudarme en esto. Sabes, pensé que eras solo una niña mimada en un atuendo llamativo que consiguió un barco para dar un paseo. ¡Pero eres una maldita buena capitana! Apuesto a que le darías a Jack una buena competencia.";
			}
			else
			{
				dialog.text = "¡Je, tienes razón! ¡Maldita sea, tienes toda la razón! Gracias por ayudarme con esto. Sabes, creo que eres tan buen capitán como Jack. ¡O incluso mejor!";
			}
			link.l1 = "Oh, ahora me estás halagando. Gracias. Supongo.";
			link.l1.go = "BM_IronsClone10";
		break;
		
		case "BM_IronsClone10":
			dialog.text = "En absoluto. No hay adulación alguna. Como habrás notado, rara vez alabo a alguien de esa manera. Así que cierra la maldita boca y alégrate de que piense tan bien de ti.";
			link.l1 = "No diría que me gusta la forma en que lo estás presentando, aunque me alegra que en general pienses en mí como un buen capitán. Pero... la cadena de mando, Tommy, la cadena de mando.";
			link.l1.go = "BM_IronsClone11";
		break;
		
		case "BM_IronsClone11":
			if (startHeroType == 4) 
			{
				dialog.text = "¡Oh, vamos! Siento que todo lo que hemos pasado nos ha acercado, Ellie. Podríamos ser más que solo capitán y oficial. Admítelo, aunque sea solo para ti misma, tú también lo sientes.";
				link.l1 = "Solo en tus sueños más salvajes, Tommy. Y es Helen, no Ellie. Pero supongo que puedes llamarme Rumba ahora.";
				link.l1.go = "BM_IronsClone12";
			}
			else
			{
				dialog.text = "¡Oh, vamos, aburrido! Me parece que ya no somos solo un capitán y su oficial, sino los más verdaderos amigos. ¿No lo crees así?!";
				link.l1 = "Je. Quizá. Es mejor ser tu amigo que tu enemigo. Y ya que la etiqueta claramente no es lo tuyo, supongo que tendré que acostumbrarme a ello.";
				link.l1.go = "BM_IronsClone12";
			}
		break;
		
		case "BM_IronsClone12":
			dialog.text = "Tengo un... regalo para usted, Capitán.";
			link.l1 = "¡Vaya, mira eso! ¿Una marca negra? ¿También quieres que me destituyan, eh, Tommy? ¿Quieres ser capitán tú mismo? ¡Ja-ja-ja-ja! Pensé que dijiste que éramos camaradas.";
			link.l1.go = "BM_IronsClone13";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_IronsClone13":
			dialog.text = "Es una MARCA negra, imbécil. Sabes, estoy empezando a pensar que tan pronto como bordé la calavera y los huesos en este pañuelo, empezó a traerme suerte. No puedo explicarlo. Tómalo. Además... si quieres, siempre puedes tomar prestada mi confiable espada y armadura... lo que queda de ella, ¡ja-ja! ¡Te será útil! Llegarás lejos. Y quiero ser testigo de ello. No quiero que te mate una bala perdida.";
			link.l1 = "¡Gracias, camarada! Haré lo mejor que pueda. Y tú, observa y admira, ¡ja-ja-ja!";
			link.l1.go = "BM_IronsClone14";
		break;
		
		case "BM_IronsClone14":
			dialog.text = "Admirar, claro, ja-ja-ja. Sí. Entonces, ¿qué has decidido hacer con este barco? Por un lado, ya no es de mucha utilidad. Por otro lado, no hay más como él. No creo que vuelva a haberlo jamás.";
			if (startHeroType == 4) 
			{
				link.l1 = "Aún no he decidido... Sabes, Tommy, siento una especie de conexión con este barco. No puedo explicarlo. Así que, saquemos primero este apestoso cadáver de aquí. Si no hay fugas en la bodega, probablemente me quede con esta chica para mí.";
			}
			else
			{
				link.l1 = "No lo sé, Tommy. Aún no he decidido. Mientras tanto, deshagámonos del cuerpo de Gabe. Por si acaso nos quedamos con el barco.";
			}
			link.l1.go = "BM_IronsClone15";
		break;
		
		case "BM_IronsClone15":
			DialogExit();
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		case "BM_IronsPinkPotopil1":
			dialog.text = "¡Bueno, hiciste un buen trabajo con esa antigua nave, capitán! Y aunque quería acabar con Gabe con mis propias manos, no enfureceré al Creador menospreciando esta victoria.";
			link.l1 = "Eso sería innecesario, Tommy. Espero que tu alma esté en paz ahora.";
			link.l1.go = "BM_IronsPinkPotopil2";
		break;
		
		case "BM_IronsPinkPotopil2":
			if (startHeroType == 4) 
			{
				dialog.text = "Siento que todo lo que hemos pasado nos ha acercado más, Ellie. Podríamos ser más que solo capitán y oficial. Admítelo, aunque sea solo para ti misma, tú también lo sientes.";
				link.l1 = "Solo en tus sueños más salvajes, Tommy. Y es Helen, no Ellie. Pero supongo que puedes llamarme Rumba ahora si dejas de adularme.";
			}
			else
			{
				dialog.text = "¡Nunca he estado tan feliz en mi vida! Gracias por ayudarme a superar esto. Sabes, creo que eres tan buen capitán como Jack. ¡O incluso mejor!";
				link.l1 = "Oh, me halagas. Gracias por la comparación también, supongo.";
			}
			link.l1.go = "BM_IronsPinkPotopil3";
		break;
		
		case "BM_IronsPinkPotopil3":
			if (startHeroType == 4) 
			{
				dialog.text = "No en absoluto. No hay halagos en lo absoluto. Como ya habrás notado, rara vez alabo a alguien de esa manera. Así que cállate y alégrate de que piense tan bien de ti.";
				link.l1 = "No diría que me gusta cómo lo dices, pero me alegra que en general pienses en mí como un buen capitán. Pero... la cadena de mando, Tommy, la cadena de mando.";
			}
			else
			{
				dialog.text = "Para nada. Ningún halago en absoluto. Como ya habrás notado, rara vez elogio a alguien así. Así que cállate y alégrate de que pienso tan bien de ti.";
				link.l1 = "No diría que me gusta cómo lo expresas, pero me alegra que generalmente pienses en mí como un buen capitán. Pero... la cadena de mando, Tommy, la cadena de mando.";
			}
			link.l1.go = "BM_IronsPinkPotopil4";
		break;
		
		case "BM_IronsPinkPotopil4":
			if (startHeroType == 4) 
			{
				dialog.text = "¡Oh, vamos, aburrido! Me parece que tú y yo ya no somos solo un capitán y su oficial, sino los más verdaderos amigos. ¿No lo crees?!";
				link.l1 = "Heh. Quizás. Es mejor ser tu amigo que tu enemigo. Y dado que la etiqueta claramente no es lo tuyo, supongo que tendré que acostumbrarme a ello.";
			}
			else
			{
				dialog.text = "¡Oh, vamos, aburrido! Me parece que tú y yo ya no somos solo un capitán y su oficial, sino los más verdaderos amigos. ¿No lo crees así?!";
				link.l1 = "Je. Quizás. Es mejor ser tu amigo que tu enemigo. Y dado que la etiqueta claramente no es lo tuyo, supongo que tendré que acostumbrarme a ello.";
			}
			link.l1.go = "BM_IronsPinkPotopil5";
		break;
		
		case "BM_IronsPinkPotopil5":
			if (startHeroType == 4) 
			{
				dialog.text = "Tengo un... regalo para usted, Capitán.";
			}
			else
			{
				dialog.text = "Tengo un... regalo para usted, Capitán.";
			}
			link.l1 = "¡Vaya, mira eso! ¿Una marca negra? ¿Tú también quieres que me destituyan, eh, Tommy? ¿Quieres ser capitán tú mismo? ¡Ja-ja-ja-ja! Pensé que dijiste que éramos compañeros.";
			link.l1.go = "BM_IronsPinkPotopil6";
		break;
		
		case "BM_IronsPinkPotopil6":
			dialog.text = "Es una MARCA negra, imbécil. Sabes, estoy empezando a pensar que en cuanto bordé la calavera y los huesos cruzados en este pañuelo, empezó a traerme suerte. No puedo explicarlo. Tómalo. Además... si quieres, siempre puedes tomar prestada mi fiel espada y armadura... lo que queda de ella, ¡ja, ja! ¡Te será útil! Llegarás lejos. Y quiero presenciarlo. No quiero que te mate una bala perdida.";
			link.l1 = "¡Gracias, compañero! Haré lo mejor que pueda. Y tú, observa y admira, ¡ja-ja-ja!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_PinkPotopil_4");
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabeHouseGood1":
			notification("Reputation Check Passed", "None");
			if (startHeroType == 4)
			{
				dialog.text = "¿Quién necesita creer en tal cosa... Lo siento, señorita. "+TimeGreeting()+". ¿Cómo puedo ayudarte? Pareces muy preocupado.";
			}
			else
			{
				dialog.text = "¿Qué? ¿Quién viene a estas horas tan tardías? Parecéis bastante preocupado, señor. ¿Qué puedo hacer por vos?";
			}
			link.l1 = "Le pido disculpas por interrumpir su descanso, Capitán Callow. Mi nombre es "+GetFullName(pchar)+", y vengo en nombre de uno de tus viejos camaradas de guerra.";
			link.l1.go = "BM_GabeHouseGood2";
		break;
		
		case "BM_GabeHouseGood2":
			dialog.text = "¿Cuál camarada? Tuve muchos, tanto en el Viejo Mundo como en el Nuevo.";
			link.l1 = "Al principio, solo tenía la intención de dejar algo en uno de tus baúles. O quizás en la mesa, para que lo notaras antes. Se trata de un hombre de tu pasado. Aquí, échale un vistazo y léelo tú mismo.";
			link.l1.go = "BM_GabeHouseGood3";
		break;
		
		case "BM_GabeHouseGood3":
			dialog.text = "¿Una marca negra? No recuerdo a ningún pirata entre mis camaradas. ¿O acaso algunos de los muchachos cayeron en esa vida? ¿Seda negra? De verdad... Oh, Thomas. Me sorprende que un hombre como tú tenga tratos con ese canalla.";
			link.l1 = "Lamento, pero no te corresponde llamarlo sinvergüenza. Huiste del campo de batalla y calumniaste a Tom. Quizás más tarde te arrepentiste y te convertiste en un oficial ejemplar aquí en el Archipiélago, pero eso no cambia el pasado.";
			link.l1.go = "BM_GabeHouseGood4";
		break;
		
		case "BM_GabeHouseGood4":
			dialog.text = "¿Te dijo eso? No es de extrañar: siempre supo cómo encontrar al hombre adecuado para contar sus historias. Thomas tenía una lengua de plata. No lo conoces a él ni la verdadera historia, ni en lo que te estás metiendo. Puedo contártelo, ya que no voy a dormir de todos modos.";
			link.l1 = "Nunca es mala idea escuchar. Continúa, Capitán Callow.";
			link.l1.go = "BM_GabeHouseGood5";
		break;
		
		case "BM_GabeHouseGood5":
			dialog.text = "¿Así que Thomas afirma que yo huí y luego lo calumnié? ¡Pues debes saber que fue al revés! Cuando se acercó la caballería del Rey, Tom dijo que iba a buscar refuerzos. Así que no retrocedimos, esperamos. ¡Toda nuestra compañía fue aniquilada! Si no hubiéramos esperado los refuerzos que prometió, podríamos habernos retirado y sobrevivido. Al final, solo quedamos yo, Frankie, y el maldito Thomas.";
			link.l1 = "Entonces, lo que estás diciendo es...";
			link.l1.go = "BM_GabeHouseGood6";
		break;
		
		case "BM_GabeHouseGood6":
			dialog.text = "¡Digo que la sangre de nuestros muchachos está tanto en las manos de Tom como en las de los realistas! ¡Tiene suerte de haber sido condenado a trabajos forzados y no a la horca! ¡Y ahora tiene el descaro de guardar rencor y desafiarme a un duelo! ¡No es digno de ello!";
			link.l1 = "¿Entonces no irás? Te das cuenta de lo que eso significa. Las leyes del honor están escritas para todos.";
			link.l1.go = "BM_GabeHouseGood7";
		break;
		
		case "BM_GabeHouseGood7":
			dialog.text = "Lo hago, por supuesto. Y por eso iré. Necesitamos terminar lo que nuestro tribunal republicano no pudo debido a los honores militares pasados de Tom. Y tú... pareces una persona decente. Te aconsejaría que elijas a tus conocidos con más cuidado. No te involucres con Tom y su tipo.";
			link.l1 = "Pero Thomas es ahora mi subordinado, un oficial en mi barco. "+GetSexPhrase("Le echaré un ojo y no dejaré que se deshonre más si sobrevive a su encuentro contigo.","")+"";
			link.l1.go = "BM_GabeHouseGood_Tommi1";
			link.l2 = "¿Y qué harías tú en mi lugar, Capitán Callow?";
			link.l2.go = "BM_GabeHouseGood_Gabe1";
		break;
		
		case "BM_GabeHouseGood_Tommi1":
			dialog.text = "Eh, si Tom pudo convencerte de su historia, no tendrá problemas en hacerlo de nuevo.";
			link.l1 = ""+GetSexPhrase("Pero por las leyes del honor, no puedo traicionarlo. Estoy","Estoy")+" responsable de mis hombres... No seré como él. Y seré más cuidadoso y crítico con él de ahora en adelante si sobrevive.";
			link.l1.go = "BM_GabeHouseGood_Tommi2";
		break;
		
		case "BM_GabeHouseGood_Tommi2":
			dialog.text = "Es una decisión difícil. Pero no intentaré hacerte cambiar de opinión. Bueno, adiós "+GetSexPhrase("señor","señorita")+". Todavía tengo que prepararme para encontrarme con Tom.";
			link.l1 = "Adiós, Capitán Callow.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_GabeHouseGood_Gabe1":
			dialog.text = "¡Que se haga justicia! Ayúdame a derrocar a Thomas, "+pchar.lastname+". Es un raro canalla y un cobarde, pero un gran tirador - no será fácil. Pero juntos...";
			link.l1 = "¿Hmm, ayudarte a derrotar a Thomas? ¿Hay mucho honor en tal duelo? Podéis resolverlo vosotros mismos, y yo me mantendré al margen.";
			link.l1.go = "BM_GabeHouseGood_Gabe2";
		break;
		
		case "BM_GabeHouseGood_Gabe2":
			dialog.text = "Sabiéndolo, dudo que tenga un duelo justo. Al mantenerte neutral, solo estás consintiendo la injusticia. ¿Tengo razón?";
			link.l1 = "Parece que conoces a Tom mejor que yo, y cómo es realmente. Tienes razón: ya está preparando una emboscada en la Bahía de Portland, y cuenta con mi ayuda, al igual que tú ahora.";
			link.l1.go = "BM_GabeHouseGood_Gabe3";
		break;
		
		case "BM_GabeHouseGood_Gabe3":
			dialog.text = "Entonces no es un duelo, sino una trifulca. Pero no sugiero que matemos a Thomas nosotros mismos. ¡Lo arrestaremos! Traeré soldados, y terminaremos lo que no pudimos en el Viejo Mundo. Si intentan exonerarlo de nuevo, escribiré al Coronel o incluso lo traeré aquí para el juicio. Si Thomas no depondrá las armas, es su propia culpa.";
			link.l1 = "Eso suena mucho mejor.";
			link.l1.go = "BM_GabeHouseGood_Gabe4";
		break;
		
		case "BM_GabeHouseGood_Gabe4":
			dialog.text = "Me alegra oírlo, "+pchar.lastname+"¡Me doy cuenta de que puede no ser fácil para ti tomar tal decisión, pero te aseguro que has tomado la decisión correcta. Y para asegurarlo, voy a ayudarte con algo más.";
			link.l1 = "¿Qué pasa, Capitán Callow?";
			link.l1.go = "BM_GabeHouseGood_Gabe5";
		break;
		
		case "BM_GabeHouseGood_Gabe5":
			dialog.text = "Aquí, toma esto. No es un regalo, sino un préstamo - Thomas, como dije, es un muy buen luchador, y es mejor enfrentarlo con un arma adecuada, no un pedazo de hierro oxidado. El Coronel Doyley mismo me dio esta belleza, pero para una pelea real, siempre elegiría un mandoble.";
			link.l1 = "En efecto, es un espléndido estoque. Gracias.";
			link.l1.go = "BM_GabeHouseGood_Gabe6";
			GiveItem2Character(PChar, "blade_40");
		break;
		
		case "BM_GabeHouseGood_Gabe6":
			dialog.text = "No me agradezcas - te lo estoy prestando, no regalando, ¿recuerdas? Ahora dirígete a la cala y juega tu papel con nuestro querido Tom, mientras yo reúno refuerzos. Nos vemos allí.";
			link.l1 = "Nos vemos allí, Capitán Callow.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_GabePlan");
		break;
		
		case "BM_GabeHouseNeutral1":
			notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
			if (startHeroType == 4)
			{
				dialog.text = "¿Quién eres tú, señorita? Debes tener la dirección equivocada. Yo, eh, no pedí ningún servicio nocturno.";
				link.l1 = "Helen MacArthur.  Y mantén tus deseos a raya, Sr. Callow. Soy una chica decente. Nuestro clima me hace sentir calor, incluso por la noche. ¿No te dio vergüenza decirle eso a una chica extraña? Me han dicho que eres un oficial ejemplar.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
			else
			{
				dialog.text = "¿Quién eres tú, y qué deseas? No me gusta tu sonrisa, señor.";
				link.l1 = ""+GetFullName(pchar)+". Y no eres muy hospitalario, Sr. Callow.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
		break;
		
		case "BM_GabeHouseNeutral2":
			dialog.text = "¿Saludas a los extraños a esta hora de manera diferente?";
			link.l1 = "Me dijeron que no estás en casa en otros momentos.";
			link.l1.go = "BM_GabeHouseNeutral3";
		break;
		
		case "BM_GabeHouseNeutral3":
			dialog.text = "Por supuesto que no - tengo servicio, deber y trabajo honesto, palabras que parecen desconocidas para ti, a juzgar por tu apariencia.";
			link.l1 = "¡Qué confianza en sí mismo! Pero entonces, no habrías convencido al coronel Doyley y a los demás de tu honestidad de otra manera. No necesito nada de ti, Gabe, pero un viejo conocido tuyo sí. Aquí tienes.";
			link.l1.go = "BM_GabeHouseNeutral4";
		break;
		
		case "BM_GabeHouseNeutral4":
			dialog.text = "¿Convencido? ¿Gabe? ¡Digo! ¿Una mancha negra? ¿Entonces eres un pirata? Espera un minuto... seda negra... ¿podría ser esto...? Oh, ya veo. Thomas, maldito bastardo, todavía enojado conmigo y Frank por denunciarte, ja ja ja ja!";
			link.l1 = "¡Por todos los diablos! Tom es un oficial en mi barco y merece respeto. Es uno de los mejores tiradores del Archipiélago.";
			link.l1.go = "BM_GabeHouseNeutral5";
		break;
		
		case "BM_GabeHouseNeutral5":
			dialog.text = "No dije que fuera un mal tirador. Pero veo que no conoces bien a Thomas. Él es quien nos traicionó a todos. Pero veo que no tiene sentido discutir contigo, claramente sois el uno para el otro.";
			link.l1 = "No me importa. Guarda tus cuentos para Doyley y todos esos ingenuos simplones. Si eres tan valiente y honorable como dicen, aceptarás el desafío y vendrás ahora. Entonces, ¿lo aceptas?";
			link.l1.go = "BM_GabeHouseNeutral6";
		break;
		
		case "BM_GabeHouseNeutral6":
			dialog.text = "Lo hago, lo hago. Ahora sal de mi casa antes de que llame a los guardias.";
			link.l1 = "Será un placer, Gabe.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_IronsJamaicaJungle1":
			if (CheckAttribute(pchar, "questTemp.BM_GabePlan"))
			{
				dialog.text = "¿Por qué estás tan nervioso? ¿Estás asustado, o qué?";
				link.l1 = "Cualquiera se pondría nervioso al ver a un hombre con un mosquete corriendo hacia ellos - no te reconocí al principio. ¿Qué haces aquí, Tommy? ";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_2";
			}
			else
			{
				dialog.text = "¿Cómo te fue? Eh, eh, ¿por qué me miras así? Me asustaste, jejeje.";
				link.l1 = "¿Quién asusta a quién! ¿Quién sale corriendo así?! ¡Quedamos en recibir a los invitados en la cala!";
				link.l1.go = "BM_IronsJamaicaJungle2";
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_2":
			dialog.text = "Heh, bueno, tal vez. Me cansé de esperar, tanto a nuestros queridos invitados como a ti. Y decidí que este lugar era más apropiado para una buena emboscada. Después de todo, soy un cazador, no un duelista.";
			link.l1 = "Entiendo.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_3";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_3":
			dialog.text = "Ay. Entonces, ¿dejaste mi regalo en la casa de Gabe? Te llevó bastante tiempo. Yo sería mucho más rápido si pudiera entrar al pueblo. ¿Qué te tiene los ojos en movimiento, Capitán? ¿Qué pasa?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(De confianza) Estoy nervioso. Gabe es un cobarde, pero no es estúpido. ¿Y si en lugar de él viene todo un pelotón de soldados? ¿O se acercan a la cala y hunden nuestro barco primero?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD1";
				notification("Trustworthy", "Trustworthy");
			}
			else
			{
				link.l2 = "Gabe me vio. Tuve que correr.";
				link.l2.go = "BM_IronsJamaicaJungle_GabePlan_4";
				notification("Perk Check Failed", "Trustworthy");
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD1":
			dialog.text = "Heh, lo entiendo - yo mismo no estoy completamente seguro de que funcione. ¿Es la primera vez que algo tan grande te ha sucedido, eh? Está bien, pasa. Lo tengo todo planeado. Si los soldados vienen sin Gabe, simplemente nos vamos. Si vienen con Gabe, le meteré una bala entre los ojos, y de nuevo, simplemente nos vamos. Y si un barco llega a la bahía, corremos hacia Maroon Town - no se atreverán a ir allí, y luego decidimos qué hacer a continuación.";
			link.l1 = "Veo que realmente has pensado en todo, Tommy.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD2";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD2":
			dialog.text = "Por supuesto que sí. Ahora esperemos a nuestro invitado...";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe");
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_4":
			dialog.text = "Ja ja, eres tan buen ladrón como yo soy realista. Pero ¿por qué no me miras a los ojos... Capitán? Estabas hablando con Gabe, ¿verdad?";
			link.l1 = "No, ¿de qué estás hablando? ¿Por qué siquiera hablaría con él?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_5";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_5":
			dialog.text = "Porque todos ustedes son unos fanfarrones. Todo lo que hacen es hablar. Entonces, ¿qué te dijo nuestro querido Gabe?";
			link.l1 = "¿Importa, Tommy?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_6";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_6":
			dialog.text = "Francamente, no. Lo hace si no me apuñalas por la espalda. Pero parece que ya lo has hecho. Te convenció de ponerte de su lado, ¿no es así?";
			link.l1 = "No. No exactamente. Baja el arma, Tommy. Te prometo que no tiene que pasar nada irreparable. Podrías trabajar en las canteras, quizás. Le pediré a Gabe que muestre misericordia. Incluso le pediré al Coronel Doyley si hace falta.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_7";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_7":
			dialog.text = "Qué buen samaritano eres. ¿Mostrando misericordia para que pueda toser mis pulmones después de años en la cantera? No volveré a los barcos prisión. Nunca más. Y tú... Debería haber sabido que eras solo otra rata. Hay algo en la forma en que te ves. Me ocuparé de ti primero, así Gabe será más fácil después.";
			link.l1 = "¡No nos dejas otra opción!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaSTommi");
		break;
		
		case "BM_GabePlan_TommiMertv":
			dialog.text = "Bueno, veo que ya lo has hecho, "+GetSexPhrase("señor","señorita")+". Y estaba reuniendo una escuadra, pensando que la ventaja numérica haría que Tom lo pensara dos veces y depusiera las armas.";
			link.l1 = "Y te has tomado tu tiempo, Capitán Callow.";
			link.l1.go = "BM_GabePlan_TommiMertv2";
		break;
		
		case "BM_GabePlan_TommiMertv2":
			dialog.text = "Te lo dije, estaba reuniendo hombres. Los mejores de nuestra guarnición. Después de todo, Tom es un soldado veterano. ¿Pero a quién le estoy diciendo esto? Bien hecho, "+GetSexPhrase("Sr.","falla")+" "+pchar.lastname+". "+GetSexPhrase("Estoy orgulloso de ti, joven.","Debo admitir que posees partes iguales de belleza, inteligencia y destreza, señorita")+". Como te dije cuando nos conocimos por primera vez, tomaste la decisión correcta. Ahora se ha hecho justicia.";
			link.l1 = "Te salió tan bien. ¿Te sientes orgulloso?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict";
			link.l2 = "Bueno, no soy un soldado veterano, pero puedo luchar, como quizás haya notado. Pero gracias, señor. La justicia no es una palabra vacía para mí.";
			link.l2.go = "BM_GabePlan_TommiMertv_Mir";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir":
			dialog.text = "Y eso es encomiable, "+GetSexPhrase("joven","jovencita")+" Sin embargo, aún queda una cosa más por hacer para completar este buen día.";
			link.l1 = "Hmm, ¿y qué es eso? Tom ya está derrotado, después de todo.";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir2":
			dialog.text = "Tienes algo que me pertenece. Devuélveme mi hermoso estoque italiano, por favor. No es solo un mondadientes, después de todo, sino un recuerdo: un regalo del propio Coronel Doyley.";
			if (!CheckCharacterItem(PChar, "blade_40"))
			{
				link.l1 = "Eh... Verá, Capitán Callow... el estoque se ha perdido. Lo he perdido. Lo siento.";
				link.l1.go = "BM_GabePlan_TommiMertv_Poteryal";			//Потеряли Рапиру
				break;
			}
			if (CheckCharacterItem(PChar, "blade_40"))
			{
				link.l2 = "Ah, por supuesto. Por favor. No tenía la intención de robarlo. No voy a mentir, me gustaría quedármelo. Pero aquí lo tiene, Capitán Callow.";
				link.l2.go = "BM_GabePlan_TommiMertv_Soglasen";			//Согласен
			}
			if (CheckCharacterItem(PChar, "blade_42"))
			{
				link.l3 = "Tengo una mejor oferta para usted, Capitán.";
				link.l3.go = "BM_GabePlan_TommiMertv_Obmen";			//Обмен
			}
			link.l4 = "Pero acabas de llamarlo mondadientes. Además, dijiste que ni siquiera te gustan los estoques. Yo, en cambio, merezco una recompensa.";
			link.l4.go = "BM_GabePlan_TommiMertv_Otkaz";				//Отказ
		break;
		
		case "BM_GabePlan_TommiMertv_Soglasen":
			dialog.text = "¡Cualquiera habría querido quedarse con esta belleza! Gracias por devolvérmela. Mucha gente habría sido terca en tu lugar.";
			link.l1 = "Es tuyo. ¿Supongo que hemos terminado aquí?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_40");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen":
			dialog.text = "No estoy interesado. Simplemente devuelve el estoque, y nos iremos en buenos términos, "+GetSexPhrase("Sr.","señorita")+" "+pchar.lastname+".";
			link.l1 = "Tengo entendido que este estoque es valioso para ti porque te gustan las armas con historia, ¿verdad? Tengo uno igual, y este es el que te gustaría llevar contigo en lugar de guardar en un cajón.";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen2";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen2":
			dialog.text = "¿Es así? Bueno, no puedo prometer que llegaremos a un acuerdo, pero estoy escuchando. De hecho, estoy interesado en armas con historia. Pero este estoque fue un regalo del Coronel. Por eso es tan valioso para mí.";
			link.l1 = "Mencionaste que te gustan las espadas anchas. Aquí. Perteneció a nuestro querido Tommy. Imagina por lo que ha pasado esta arma a lo largo de los años. Y por lo que seguirá pasando contigo.";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen3";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen3":
			dialog.text = "¡Eres muy persuasivo, joven! Empuñando la espada de Thomas... qué irónico. Bueno, toma el estoque. No me desprendo de él a la ligera, que conste.";
			link.l1 = "Me alegra que hayamos podido llegar a un acuerdo. ¿Creo que eso es un adiós, Capitán Callow?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_42");
			AddCharacterExpToSkill(pchar, "Leadership", 250);
			AddCharacterExpToSkill(pchar, "Commerce", 500);
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal":
			dialog.text = "¿¡QUÉ?! ¿Cómo pudiste... Cómo pudiste perder un maldito estoque entero?! ¡Eres un idiota!";
			link.l1 = "¡Cálmate! Es solo un estoque. Nunca lo usarías de todos modos. Tom está muerto, ¿no es eso lo único que importa ahora?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal2";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal2":
			dialog.text = "¿¡Solo un estoque?! ¡Era mi tesoro! ¡Un regalo del Coronel Doyley en persona! ¡No me importa si no lo usaba!";
			link.l1 = "Entonces no deberías habérmelo dado, ¿verdad?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal3";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal3":
			dialog.text = "Deberías mantener la boca cerrada ahora, "+GetSexPhrase("Sr.","señorita")+" "+pchar.lastname+"Podríamos habernos separado en paz. Pero ahora... ahora me gustaría darte una lección, "+GetSexPhrase("joven muchacho","jovencita")+".";
			link.l1 = "Los cementerios están llenos de maestros como tú.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz":
			dialog.text = "Por supuesto que sí. Pero no puedes simplemente tomar el arma personal de un oficial porque le echaste una mano, ¿verdad?";
			link.l1 = "Estaría de acuerdo, pero tú no lo usas de todos modos. Solo colgará de un clavo en tu habitación. Mientras que conmigo, encontrará un uso digno. El Coronel Doyley no va a comprobar si lo has extraviado, ¿verdad?";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz2";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz2":
			dialog.text = "Esto no está a discusión, joven. Te dije desde el principio, no es un regalo. Dame el estoque. Ahora.";
			link.l1 = ""+GetSexPhrase("No soy uno de tus soldaditos de juguete","No soy una de tus rameras del puerto")+", recibir órdenes de ti. Soy un capitán de barco, igual que tú. El estoque se queda conmigo, te guste o no.";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz3";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz3":
			dialog.text = "Parece que Thomas te ha causado bastante efecto. Entonces muere por ello, si tanto lo deseas.";
			link.l1 = "¡Mis pensamientos exactamente!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Platok":
			dialog.text = "Aquí, toma esto. No lo necesito en absoluto. Será tu recuerdo del día. Trata de ser un poco menos crédulo de ahora en adelante. Y no dejes que sinvergüenzas como Thomas te involucren en sus asuntos sucios.";
			link.l1 = "Je, ¿me estás dando una mancha negra, Capitán Callow?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok2";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabePlan_TommiMertv_Platok2":
			dialog.text = "Bueno, ninguno de nosotros es pirata, ¿verdad, "+pchar.name+"? Que sea un recordatorio. Cuídate, el Archipiélago necesita hombres como tú. "+GetSexPhrase("Tal vez sugeriría unirse a la Armada y escribir una recomendación para el Coronel Doyley...","")+"";
			link.l1 = "Lamento no poder aceptar tu oferta, Capitán.";
			if (startHeroType == 3)
			{
				link.l1 = "Hm. Lo pensaré. Muy detenidamente.";
			}
			if (startHeroType == 4)
			{
				link.l1 = "Adiós, señor.";
				link.l1.go = "exit";
				AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
				break;
			}
			link.l1.go = "BM_GabePlan_TommiMertv_Platok3";
		break;
		
		case "BM_GabePlan_TommiMertv_Platok3":
			dialog.text = "Como quieras. Bueno, adiós, "+GetSexPhrase("Sr.","señorita")+" "+pchar.lastname+"Te mereces llevar lo que queda de los Ironsides. Adiós.";
			link.l1 = "Adiós, señor.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict":
			dialog.text = "No me gusta tu tono, "+GetSexPhrase("señor","señorita")+"¿Cuál es tu punto?";
			link.l1 = "Has estado demorando deliberadamente, reuniendo a tus 'mejores hombres'. ¿Para qué? ¿Para atrapar a un solo hombre? ¡Deberías haber tomado a unos cuantos soldados que patrullan la ciudad y venir en mi ayuda de inmediato!";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict2";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict2":
			dialog.text = "¿Traer carne de cañón?! Tom no era solo un guardia de ciudad como ellos. Tenía un entrenamiento y experiencia completamente diferentes: ¡es un maldito Acorazado, igual que yo! ¿Cómo no te das cuenta de eso?";
			link.l1 = "¡Oh, al contrario, sí me doy cuenta! Por eso tú y yo estamos aquí: para cruzar espadas con Tom, permitiendo que los muchachos lo capturen vivo. Además, tú también eres de los Ironclad. Incluso de la misma compañía. ¿Tenías tanto miedo de enfrentarte a él cara a cara?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict3";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict3":
			dialog.text = "¿Cómo te atreves a acusarme de cobardía, joven"+GetSexPhrase("cito","cita")+"? ¡Pregúntale a cualquiera, y te contará en detalle las hazañas que he hecho por esta ciudad!";
			link.l1 = "Aún no he terminado. Empiezo a preguntarme si estas ‘hazañas' fueron hechas por tus propias manos. Querías que Tom y yo nos matáramos entre nosotros para que pudieras llevarte toda la gloria. Ya lo has hecho antes, ¿no es así?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict4";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict4":
			dialog.text = "He tenido suficiente de tus acusaciones, "+GetSexPhrase("Sr.","señorita")+" "+pchar.lastname+"¿Quieres conflicto? Lo tendrás. Ahora mismo.";
			link.l1 = "La verdad duele, ¿no es así, Gabe?";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Conflict = true;
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_1":
			dialog.text = "";
			link.l1 = "¡Gabe! ¡Ha pasado tanto tiempo, tantos crudos inviernos! Y mírate, todavía con esa misma expresión de autosuficiencia, ¡maldito seas!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_2":
			dialog.text = "¡Thomas! Debiera estar complacido, pues hoy finalmente terminaré con mis propias manos lo que nuestro sistema de justicia no pudo hacer durante años. Y como estoy de buen humor, te permito deponer las armas y seguirnos. Incluso podrías ser enviado de nuevo a trabajos forzados. En ese caso, te llevaré personalmente allí.";
			link.l1 = "¡Je, hazme hacerlo! ¡¡¡Tú piensas que un par de tipos a tu lado me detendrán!!!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_3";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_3":
			dialog.text = "¿Quién dice que son los únicos conmigo? Estoy hablando de la persona que está a tu lado ahora mismo.";
			link.l1 = "¿Qué?";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_4";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_4":
			dialog.text = "Thomas, Thomas, Thomas... estás, como siempre, solo en este mundo. ¡Casi me siento apenado por ti!";
			link.l1 = "¡Malditas ratas! ¡Miserables!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_5";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_5":
			StartInstantDialog("Irons", "BM_GabePlan_GazgovorTommiAndGabe_6", "Quest\BlackMark.c");
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_6":
			dialog.text = "¿Qué significa eso?! ¿Qué quiso decir con eso?!";
			link.l1 = "Tommy, escucha...";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_7";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_7":
			dialog.text = "¡Eso es exactamente lo que estoy haciendo! ¡Dime que está mintiendo!";
			link.l1 = "Lamentablemente, tiene razón. Depongan las armas. Y nadie tiene que morir hoy. Yo mismo hablaré bien de ustedes para que no los cuelguen. Incluso pueden regresar a una vida honrada algún día.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_8";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_8":
			dialog.text = "¡Eso no te corresponde decidir! ¡Y ciertamente no a ti! ¡Quién necesita enemigos con un comandante como ese! Otra maldita rata.";
			link.l1 = "Vamos, Tommy. No hay escapatorias limpias para gente como tú.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_9";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_9":
			dialog.text = "Un lugar en tu tripulación, en tu barco sería un comienzo, ¡si tan solo estuvieras dispuesto a defender a tus hombres! Pero eso ya no importa. ¡Malditos sean, todos ustedes! Te sacaré las tripas cobardes, maldito ratón. Y tú, Gabe, intentaré llevarte conmigo...";
			link.l1 = "¡Espera, Tommy, no!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe_Fight");
		break;
		
		case "BM_GabePlan_GabeWin_1":
			dialog.text = "Felicidades, "+GetSexPhrase("joven","joven señorita")+"¡Estoy impresionado de que hayas logrado hacer que Thomas sintiera que todo iba según su plan - tenía un olfato para la traición.";
			link.l1 = "Ah, gracias, por supuesto, Capitán Callow.";
			link.l1.go = "BM_GabePlan_GabeWin_2";
		break;
		
		case "BM_GabePlan_GabeWin_2":
			dialog.text = "¿Algo te preocupa, "+GetSexPhrase("señor","señorita")+" "+pchar.lastname+"?";
			link.l1 = "Tom... él no solo estaba enfadado porque yo estuviera de tu lado. Había verdadera desesperación e incomprensión en su voz, como si...";
			link.l1.go = "BM_GabePlan_GabeWin_3";
		break;
		
		case "BM_GabePlan_GabeWin_3":
			dialog.text = "...como si él fuera el agraviado aquí. Era de esperar. Recuerda, Charles, un monstruo puede sentir dolor. Pero no deja de ser un monstruo. Muchos criminales a menudo están sinceramente convencidos de su rectitud e inocencia.";
			link.l1 = "Trataré de tenerlo en cuenta. Creo que hemos terminado aquí, ¿no crees, Capitán?";
			link.l1.go = "BM_GabePlan_GabeWin_4";
		break;
		
		case "BM_GabePlan_GabeWin_4":
			dialog.text = "En general, sí, pero todavía queda una cosa más por hacer para completar este buen día.";
			link.l1 = "¿Oh? ¿Qué es?";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_IronsJamaicaJungle2":
			dialog.text = "Tardaste lo tuyo. Así que pensé en hacer un poco de reconocimiento. De todos modos, creo que es mejor emboscarlos aquí en lugar de jugar a ser duelistas elegantes en la playa. ¿Espero que hayas podido encontrar la casa de Gabe y dejar todo a la vista?";
			link.l1 = "Por supuesto que lo hice, ¿por quién me tomas, por un idiota? En realidad, soy tu capitán, Tommy. ¿Qué sería de ti si sirvieras a un idiota?";
			link.l1.go = "BM_IronsJamaicaJungle3";
		break;
		
		case "BM_IronsJamaicaJungle3":
			dialog.text = "Ja-ja-ja-ja, ¡no creerías con qué frecuencia he tenido que lidiar con porquerías así en el servicio! Pero en nuestro caso, afortunadamente, no es el caso. Muy bien, entonces. Estamos esperando compañía. ¿Listo?";
			link.l1 = "Bueno, a menos que toda la flota o la guarnición de Port Royal aparezcan aquí, estoy listo.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CreateGabeInJungle");
		break;
		
		case "BM_GabeJungle1":
			dialog.text = "¿Thomas? Realmente eres tú después de todo...";
			link.l1 = "Por supuesto que soy yo, ¿o esperabas a alguien más, Gabe? Je, pareces pálido, como si hubieras visto un fantasma. También estás más gordo que cuando estabas en la Vieja Inglaterra.";
			link.l1.go = "BM_GabeJungle2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabeJungle2":
			dialog.text = "Ahora estoy finalmente convencido de que realmente eres tú. Grosero como siempre. Pero está bien, pronto cerraré tu sucia boca para siempre, malnacido.";
			link.l1 = "¡Ja-ja-ja, ahora sí que hablamos! Sabes, en realidad me has decepcionado, Gabe. ¡Otra vez! Claramente necesitabas traer más hombres contigo incluso para enfrentarte solo a mí. ¡Y somos dos! ¿O era todo lo que podían darte, cobarde?";
			link.l1.go = "BM_GabeJungle3";
		break;
		
		case "BM_GabeJungle3":
			dialog.text = "¡Basta! No veo el sentido de seguir hablando.";
			link.l1 = "¡Estoy de acuerdo contigo en eso! "+pchar.name+"¡A la batalla, Capitán!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GabeJungleFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "BM_IronsJamaicaJungle4":
			dialog.text = "Je, ¡ahí lo tienes! Descansa en paz, maldito bastardo.";
			link.l1 = "Bueno, ¿estás satisfecho, Tommy? Sabes, mucha gente empeora después de vengarse.";
			link.l1.go = "BM_IronsJamaicaJungle5";
		break;
		
		case "BM_IronsJamaicaJungle5":
			dialog.text = "Ja, ¿leíste eso en algún lugar? Nunca entendí a esos nenazas. ¡Bah! ¿Estoy satisfecho? ¡Estoy tan feliz que estoy a punto de mear en mis pantalones! ¡Esos bastardos eran la raíz de mis mayores desgracias!";
			link.l1 = "Me alegro por ti. ¿No hay nadie más de quien debas vengarte? ¿Debo esperar más bromas sobre cartuchos de papel de tu parte?";
			link.l1.go = "BM_IronsJamaicaJungle6";
		break;
		
		case "BM_IronsJamaicaJungle6":
			dialog.text = "Tranquilo, Gabe fue el último. Y sobre las bromas, no te preocupes, no habrá más, al menos no en lo que a ti concierne.";
			link.l1 = "¿Volvemos al barco entonces?";
			link.l1.go = "BM_IronsJamaicaJungle7";
		break;
		
		case "BM_IronsJamaicaJungle7":
			dialog.text = "Volveríamos a ella de todos modos, ya sea que todavía tenga a alguien de quien vengarme o no. Pero espera un momento...";
			link.l1 = "Oh,  así que todavía no ha terminado...";
			link.l1.go = "BM_IronsJamaicaJungle8";
		break;
		
		case "BM_IronsJamaicaJungle8":
			dialog.text = "Lo es, lo es. Hay algo que quiero decirte. Es algo que le digo a muy pocas personas. Y no lo diré de nuevo. Si te ríes de mí, me enojaré mucho contigo.";
			link.l1 = "Prometo no reírme. De todos modos, encuentro tus bromas más tensas que graciosas.";
			link.l1.go = "BM_IronsJamaicaJungle9";
		break;
		
		case "BM_IronsJamaicaJungle9":
			dialog.text = "Bien. Entonces. Estoy muy agradecido de que decidieras ayudarme en lugar de hacer lo que hizo Jack. Eres un verdadero amigo, Capitán. Gracias. Además... si quieres, puedes tomar prestada mi fiel espada y mi armadura... Lo que queda de ella, ¡ja, ja!";
			link.l1 = "Bueno, gracias por decir eso. No todos los días se escucha algo así de tus oficiales. Vamos, camarada.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_FinalInJungleWithTommy");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Irons_officer":
			dialog.text = "¡Aaaaye-aye!, ¿Capitán?";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "Entonces, Rumba, ¿sobre los huesos de quién bailaremos esta noche?";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "¿Sí, Ellie?";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Soy todo oídos, capitán.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "¿"+pchar.name+"?";
			}
			//////
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal") && !CheckAttribute(pchar, "questTemp.BM_TommiTieyasalOtkaz"))
			{
				Link.l4 = "Tommy, me gustaría preguntarte algo muy serio. Hay uno... un ídolo de piedra de los pieles rojas. Y voy a necesitar ayuda. Solo puedo pedirlo a mis amigos más cercanos, como tú. Los novatos o aquellos en quienes aún no confío demasiado no servirán.";
				Link.l4.go = "tieyasal_1";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tommy, deja de contar las gaviotas. ¿Has contabilizado toda la carga? Dame un informe completo con un pronóstico.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Tommy, a partir de hoy, necesito que compres ciertos bienes en los puertos.";
				Link.l12.go = "QMASTER_2";
				
				if (startHeroType == 4)
				{
					Link.l11 = "Tommy, ¿podrías reportar todo sobre el barco?";
					Link.l12 = "Tommy, me estoy cansando mucho. ¿Podrías abastecerte de ciertos bienes en cada puerto?";
				}
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l11 = "Prepárame un informe sobre el estado del barco y todo lo que hay en él, Tommy.";
					Link.l12 = "¿Podrías abastecerte de ciertos bienes durante nuestras escalas en el puerto?";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l11 = "Cuenta todo lo que tengo en el barco e informa sobre su estado general.";
					Link.l12 = "Necesito que compres estos bienes durante nuestras escalas en cada puerto.";
				}
			}
			//////
			Link.l1 = "¡Escucha atentamente mi orden!";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Alguien seguro. Pero por ahora, escucha mis órdenes.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Escucha mi orden... Tommy. ";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "Eso es bueno, porque tengo una nueva orden para ti, Tommy.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Escucha mi orden, Tom.";
			}
			Link.l1.go = "stay_follow";
			//////
			link.l2 = "Nada, Tommy. A sus órdenes.";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "Veremos cómo va, Tommy.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "No, Tom, nada.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "No, nada.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Nada, todo está bien.";
			}
			link.l2.go = "exit";
			NextDiag.TempNode = "Irons_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "No he empezado siquiera con el inventario. Deberías agradecer que estoy contando nuestras ganancias y pérdidas en absoluto, y mucho menos regateando con esos mercaderes codiciosos. El inventario no es mi asunto, nunca tuve que hacerlo en el ejército, y no voy a empezar ahora.";
			Link.l1 = "Esto no es el ejército, Tommy. Pero bien, lo entiendo, no te obligaré.";
			if (startHeroType == 4)
			{
				dialog.Text = "No soy un escriba, Ellie. Una vez conocí a un tipo, Daniel Crimson, que siempre decía ser escriba, pero apenas había visto el campo de batalla. Sin embargo, ese hombre era una bestia en la lucha. Eso no soy yo, y no voy a mentir al respecto. El inventario simplemente no es lo mío. Ya estoy haciendo nuestras cuentas por tu bien. No insistas.";
				Link.l1 = "Está bien, Tommy, no lo haré.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Mira, no soy un escriba. Nadie ha exigido esto a soldados comunes como yo, ni siquiera en el ejército. No cambiemos esa regla.";
				Link.l1 = "Está bien, no lo hagamos.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "La única cosa que puedo contar es cuántos de nuestros enemigos he disparado, ja-ja-ja. Y aun así perderé la cuenta. Soy un simple soldado, ¿sabes? Quién diablos sabe del barco - he sido un marinero de agua dulce la mayor parte de mi vida.";
				Link.l1 = "Parece que tendré que hacerlo yo mismo.";
			}
			Link.l1.go = "exit";
		break;

		case "QMASTER_2":
			dialog.text = "¿Por quién me tomas, por algún contramaestre de poca monta? Sentíamos nada más que desprecio por esos cobardes sin agallas en casa. Puede que no sea noble, pero todavía tengo mi orgullo.";
			link.l1 = "Está bien, está bien, si no quieres, entonces no quieres.";
			link.l1.go = "exit";
			if (startHeroType == 4)
			{
				dialog.Text = "Escucha, era un simple y honesto soldado, no un oficial de suministros, muchacha. No sé mucho al respecto y no quiero empezar a aprender. Es como pedirte que ensamblar y desensamblar un mosquete a tiempo.";
				Link.l1 = "Bueno, podría nombrar de memoria cada parte del aparejo fijo y de labor de este barco. Pero como desees, Tom. El asunto está cerrado.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "No, no pude. Quizás lo olvidaste o no lo sabes en absoluto, así que te lo explicaré. Para ti, esto sería una tarea rutinaria, pero en nuestro ejército, no tratamos muy bien los servicios de suministro y retaguardia. Por favor, no me cuentes entre ellos.";
				Link.l1 = "Ja, ja, bien, bien.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Mira, te respeto, por supuesto, pero no voy a pasar por encima de mí mismo y hacer algo que no puedo hacer y no puedo soportar. Apenas aprendí a contar en aquel entonces, y tú quieres que sea un verdadero proveedor. Por cierto, no nos gustaban - ahorran en municiones, agua, comida y su frescura.";
				Link.l1 = "Mm, está bien, olvidémoslo.";
			}
		break;
		
		case "stay_follow":
            dialog.Text = ""+GetSexPhrase("Ah, ¿una orden, eh? Te gustan las maniobras y todas esas cosas del ejército, ¿verdad? Yo preferiría que simplemente me dijeras qué hay que hacer.","Eres como un sargento o algo así. No te queda bien, eres demasiado hermosa para eso. No habrías sobrevivido ni un día en el ejército. Pero te estoy escuchando.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Aparentemente, realmente eres un gran fanático de los uniformes, los ejercicios y todo eso. Pero bueno, continúa.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "¿Cuál?";
			}
			
            Link.l1 = ""+GetSexPhrase("No vayas a ninguna parte y no hagas nada, solo observa, ¿entiendes? Te conozco.","Quédate justo donde estás, ¿me entiendes?")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "Solo quédate aquí, no vayas a ningún lado y no toques nada.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Quédate aquí y no dejes que nadie pase.";
			}
			Link.l1.go = "Boal_Stay";
            Link.l2 = ""+GetSexPhrase("Sigue mi estela y no te distraigas con nada, incluidas esposas descarriadas o viejos camaradas de guerra que aparezcan de repente.","Quédate cerca, ¿de acuerdo? Me gustaría tener mi espalda cubierta.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "Sígueme. Veo que estás perdido en tus pensamientos.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Sígueme, de lo contrario te has detenido por alguna razón.";
			}
			Link.l2.go = "Boal_Follow";
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Necesito que dispares a algo diferente esta vez.";
					Link.l3.go = "SetGunBullets";
					if (pchar.sex == "man" && pchar.rank >= 15)
					{
						Link.l3 = "Necesito que dispares diferentes tipos de munición en la próxima pelea.";
					}
					if (pchar.sex == "man" && pchar.rank >= 25)
					{
						Link.l3 = "Usarás munición diferente en la próxima batalla.";
					}
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Cambia el tipo de munición de tu mosquete.";
					Link.l4.go = "SetMusketBullets";
				}
				Link.l5 = "Cambia tu arma prioritaria para el combate.";
				Link.l5.go = "SetPriorityMode";
				Link.l6 = "Me gustaría que mantuvieras una cierta distancia entre tú y tus enemigos.";
				Link.l6.go = "TargetDistance";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l6 = "Me gustaría que mantuvieras cierta distancia del enemigo, Tommy.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l6 = "Mantén una cierta distancia entre tú y el enemigo, Tommy.";
				}
			}
		break;
		
		case "SetGunBullets":
			Dialog.Text = ""+GetSexPhrase("¿Qué clase de proyectiles? Espero que hayas fabricado cuidadosamente cada uno porque quién sabe dónde aterrizarán, jeje.","Dispararé cualquier cosa por ti. Lo que sea, pero nunca salvas, jeje. ")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "¡Siento que algo interesante se está gestando! Bueno, ¿qué tipo?";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "luchando de nuevo... Está bien, ¿qué tipo?";
			}
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;

		case "SetMusketBullets":
			Dialog.Text = "Selecciona el tipo de munición:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "Al comienzo de la lucha usarás:";
			Link.l1 = "Espada";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Mosquete";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = ""+GetSexPhrase("¿Incluso si te apalean allí, jeje? Entendido, solo miraré.","¿Intentas convertirme en un guardia? ¿Y si te golpean o algo así?")+"";
            Link.l1 = ""+GetSexPhrase("¡Oye, ten cuidado! Encontraremos una solución si llega a eso.","Bueno, no vas a quedarte mirando, ¿verdad? Si crees que tu capitán es tan maravilloso como dices, harás algo al respecto.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "¿Incluso para golpear la cabeza? Está bien, está bien, no me mires así, lo entiendo.";
				Link.l1 = "Eso espero.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "No temas, nadie pasará.";
				Link.l1 = "Si no extrañas a nadie, por supuesto. Pero bien.";
			}
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = ""+GetSexPhrase("Muy gracioso. Pero entiendo tu punto.","Oh, no te preocupes, siempre tengo tu espalda bajo mi ojo vigilante, jeje.")+"";
            Link.l1 = ""+GetSexPhrase("Bien.","Dios, eres insufrible, Tom.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Bueno, estoy tratando de recordar algo muy importante. Y luego me doy cuenta de que ni siquiera sé qué es, ya que perdí la memoria en aquel entonces, así que no saldrá nada de esto. Bueno, vámonos.";
				Link.l1 = "Perspicaz, debo decir.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Bueno, estoy aquí porque me ordenaste hacerlo antes. Voy, voy.";
				Link.l1 = "Mm-m, está bien, está bien.";
			}
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = ""+GetSexPhrase("¿Qué clase de distancia? Ten en cuenta que más allá de veinte yardas, no podré apuntar con precisión. A menos, claro, que no necesites que realmente le dé a algo, jeje.","Como si quisiera acercarme a hombres apestosos después de estar cerca de ti. Entonces, ¿cuál es la distancia? Pero recuerda, realmente no puedo apuntar mi fuego más allá de veinte yardas, nadie puede.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Está bien, ¿qué distancia? Pero permíteme recordarte que no podré disparar con precisión y lentitud a más de veinte metros en el fragor de la batalla.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Vale. ¿Qué? Recuerda que más allá de... bueno, ya no somos unos críos, tú y yo lo sabemos.";
			}
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = ""+GetSexPhrase("No deberías intentar hacer humor.","Aún tienes mucho que aprender de mí sobre el humor, muchacha. ¡Pero estás progresando!")+"";
				link.l1 = ""+GetSexPhrase("Qué raro, a mí siempre me han dicho lo contrario.","Muy gracioso, Tommy.")+"";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "No es tu peor chiste. Tal vez algún día dejes de ser un aguafiestas, je-je.";
					Link.l1 = "Oh, bueno.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Ja-ja-ja, buen chiste.";
					Link.l1 = "En realidad, yo sólo... está bien.";
				}
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Bueno, entonces me quedaré quieto y mantendré mi posición. Si luchas contra ellos desde muy lejos, es tu trasero el que está en juego, jeje.";
				link.l1 = "No seas sarcástico; mantenerte firme es exactamente lo que quiero que hagas a partir de ahora.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Je, podrías haberme dicho que aguantara la línea, y no hablar de distancias y números.";
					Link.l1 = "Bueno, lo principal es que me entendiste.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Entendido, mantendré la posición aquí. Luego acércalos para que pueda disparar.";
					Link.l1 = "Ciertamente.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Mira, sé que te gustaría que cada disparo que hago fuera como el del faro, pero eso no va a suceder. Era una buena posición allí. Tranquilo y firme. No puedes replicar eso en el calor de la batalla.";
				link.l1 = "Ah. Entonces mantente a veinte yardas de distancia.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Sé que te gustaría eso, a todos los muchachos les gustaría eso, pero como aquella vez, en el faro, ya no funcionará más. Necesitaré un buen punto, y que nadie me alcance, de lo contrario mis nervios se quebrarán.";
					Link.l1 = "Hm-m, está bien.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Sin duda he perfeccionado mis habilidades desde entonces, pero lo imposible seguirá siendo imposible: en el fragor de la batalla, nunca podría repetir ese disparo desde el faro. Incluso con un mosquete de rueda.";
					Link.l1 = "Y lo imposible es posible, Tommy. Pero bueno, no significa no.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = RandPhraseSimple("Muy bien. Mantendré exactamente esa distancia, pero si estamos luchando dentro de una taberna o cueva, saldré para mantenerla, jeje.","Lo intentaré. Pero las cubiertas y los espacios confinados podrían dictar sus propios términos.");
			link.l1 = ""+GetSexPhrase("No es gracioso, Tommy. Actúa según la situación, pero sin bromas ni tus estúpidas travesuras.","Lo sé, Thomas, no soy tonto.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Intentaré recordar.";
				Link.l1 = "Está bien, cuento contigo.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Sí, capitán.";
				Link.l1 = "A tus órdenes, Tommy.";
			}
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal_1":
			dialog.text = "¿Ayudar con qué, robarlo? ¿Pero por qué? Me siento halagado, por supuesto, pero podrías haberlo dicho todo hace mucho tiempo. Adelante, escúpelo.";
			link.l1 = "¿Cuida tu boca, eh? Bueno, maldita sea, realmente no me importa cómo te expreses, siempre y cuando estés de mi lado. Entonces, ese ídolo. A través de él, puedes... mágicamente llegar a otro lugar. No me mires así, sé cómo suena. Pero ya he pasado por esto antes y lo he visto todo con mis propios ojos. Es... seguro si bebes un elixir.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Veo que ya has tomado unas copas. Aunque no, pareces sobrio. Y dicen de mí que siempre hablo tonterías...";
			link.l1 = "¿Vienes conmigo o no? Se supone que el ídolo nos llevará a una antigua ciudad maya, y ¿quién sabe qué nos espera allí? Eres uno de esos en quienes creo que puedo confiar en un momento difícil. Y ahora ha llegado justo ese momento.";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Tengo un mal presentimiento sobre todo esto. Si no fueras mi capitán, diría que perteneces a un manicomio. Lo siguiente será que me digas que Dios existe.";
			link.l1 = "Lo hace, Tommy. Y, como descubrí para mi sorpresa en este Archipiélago, no solo el nuestro. Tú mismo podrías ver toda la diablura que ocurre aquí. Y probablemente hayas notado la influencia de baratijas benditas o malditas.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "La brujería también existe en casa. Y siempre ha tenido una explicación normal. Lo siento, capitán, pero no bailaré alrededor de ídolos de piedra contigo. Disparar a los enemigos - con mucho gusto. Puede que haya perdido la memoria, pero no he perdido la cabeza. Al menos, eso creo.";
			link.l1 = "Bueno, no puedo obligarte. Así que... como desees, Tommy.";
			link.l1.go = "tieyasal_5";
			link.l2 = "Dudo que tengas las pelotas para dispararles, valiente, si tienes miedo de acercarte al ídolo.";
			link.l2.go = "tieyasal_6";
		break;
		
		case "tieyasal_5":
			dialog.text = "Oh bueno-bueno, no hagas pucheros. Está bien, si regresas después de bailar alrededor de ese ídolo, entonces lo pensaré para la próxima vez.";
			link.l1 = "No puede que haya una próxima vez. Vuelve al barco, Tom.";
			link.l1.go = "exit";
			pchar.questTemp.BM_TommiTieyasalOtkaz = true;
		break;
		
		case "tieyasal_6":
			dialog.text = "No tengo miedo, no me malinterpretes. Pero estoy acostumbrado a escuchar a mi instinto, nunca me ha fallado a lo largo de los años. Y ahora me dice que nada bueno saldrá de esto. Y de todos modos... Bueno, te ofenderás.";
			link.l1 = "Adelante, cuéntame.";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "¡Pues, si ese es el caso! Acordé luchar codo a codo contigo. Pero, ¿y si, imaginemos, esta cosa realmente funciona? ¿Qué pasa si está maldita? No voy a morir por nadie, lo siento.";
			link.l1 = "Ahora te has demostrado, Tommy. Necesitaba a las personas más leales ahora. Y ahora veo que no eres uno de ellos. Voy allí. Y tú... haz lo que quieras.";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Míralo. Está ofendido después de todo.";
			link.l1 = "Cierra la boca. Si nos encuentras tan repugnantes, no tienes que volver al barco.";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "¡Vaya! ¿Hablas en serio? Bueno, tal vez sea lo mejor. No quiero estar con aguafiestas que ni siquiera entienden los chistes. En ese caso... adiós, Su Excelencia.";
			link.l1 = "Adiós, Tommy. Y vete al infierno.";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			DialogExit();
			RemovePassenger(pchar, npchar);
			DeleteAttribute(npchar, "OfficerImmortal");
			npchar.lifeday = 0;
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
	}
} 