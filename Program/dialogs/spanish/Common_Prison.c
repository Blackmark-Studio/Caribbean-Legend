// городские тюрьмы
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;
	// belamour для ночного приключения -->
	int i;
	int SoldQty = 0;
	int SoldNum[10];
	// <--

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		//---------------- Начальник тюрьмы ------------------
		case "First_officer":
			dialog.text = RandPhraseSimple("Soy el alcaide de la prisión. ¿Qué necesitas aquí?","¿Qué necesitas? ¿Por qué has venido a la prisión?");
			NextDiag.TempNode = "First_officer";
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_prison" && !CheckAttribute(pchar, "questTemp.HelenSCprison"))
			{
				dialog.text = "¿Señorita MacArthur? Sorprendido de verte. No hemos arrestado a nadie de tu tripulación o del Capitán Swenson, hasta donde sé.";
				link.l1 = "Solo estoy aquí, señor. ¿Acaso no está permitido? No estaba charlando con los prisioneros a tus espaldas.";
				link.l1.go = "Helen_meeting";
				pchar.questTemp.HelenSCprison = true;
				break;
			}
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaTrevoga") && npchar.city == "SentJons")
			{
				dialog.text = "Ah, Charles de Maure... Deberías ser arrestado y unido a tu oficial, pero... el incidente en el banco ha sido considerado un lamentable malentendido.";
				link.l1 = "Me gusta cómo comenzaste esta conversación, Sr. "+GetFullName(NPChar)+". Puedo explicar todo.";
				link.l1.go = "DTSG_AntiguaTrevoga_2";
				break;
			}
			// <-- Длинные тени старых грехов
			
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "Oficial, he oído que hay un hombre llamado Folke Deluc en vuestra prisión. ¿Hay algo que pueda hacer para liberarlo?";
                link.l1.go = "Sharlie";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "Oficial, soy yo de nuevo sobre el prisionero Folke Deluc. He comprado los derechos de su deuda y quiero que este hombre sea liberado y entregado a mí. Aquí están sus papeles de deuda, échale un vistazo.";
                link.l1.go = "Sharlie_3";
				break;
			}	
			//<-- Бремя гасконца
			
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// Офицер с патентом
			if(IsOfficerFullEquip())
			{
				dialog.text = "Saludos, capitán. ¿Qué te trae por aquí?";
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "¡Saludos, Vicealmirante! ¿Cómo puedo ayudarte?";
			}
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Su Excelencia, Gobernador General! ¿Tiene alguna orden?";
			}
			// <-- legendary edition
			link.l1 = "Oh, nada especial, solo estaba dando una vuelta por la ciudad, así que llegué aquí de casualidad.";
			link.l1.go = "exit";
			link.l2 = "Quería hablar sobre algunos negocios.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakFort"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "F_ShipLetters_1";
				}
				else
				{
					link.l2.go = "quests";
				}		
			}
			else
			{
				if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
				{
					link.l2.go = "ReasonToFast_Prison1";
				}
				else
				{
					link.l2.go = "quests";
				}	
			}
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "Quiero entrar a la prisión.";
				link.l4.go = "ForGoodMove";		
			}
			if (CheckAttribute(pchar, "questTemp.jailCanMove.City") && npchar.city == pchar.questTemp.jailCanMove.City)
			{
				link.l5 = "Oye, ¿podrías decirme qué delito cometió el convicto llamado "+GetFullName(characterFromId(pchar.questTemp.jailCanMove.prisonerId))+"¿está cumpliendo condena por?";
				link.l5.go = "KnowAboutPrisoner";	
			}
			
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
				{
					bool zMsm = (CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour")) && (!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"));
					if(pchar.GenQuest.CaptainComission == "MayorTalkBad" || zMsm) //говорил с губером и отказался или узнал слухи, но не говорил с губером
					{
						link.l6 = "He oído que el antiguo capitán de una patrulla "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" está aquí bajo custodia. ¿Puedo hablar con él?";
						link.l6.go = "CapComission_PrisonBad1";
					}
					if(pchar.GenQuest.CaptainComission == "MayorTalkGood")
					{
						link.l6 = "Yo "+GetFullName(pchar)+", actuando en nombre y por orden del gobernador "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+"necesito hablar con el antiguo capitán "+pchar.GenQuest.CaptainComission.Name+".";
						link.l6.go = "CapComission_PrisonGood1";
					}
				}	
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "fort_keeper"  && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "Esto es sobre tu hija...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "begin" && NPChar.location == pchar.GenQuest.Marginpassenger.City + "_prison")
			{
				link.l12 = "Tengo asuntos contigo, oficial. Creo que te interesaría ya que está relacionado con tus deberes.";
				link.l12.go = "Marginpassenger";
			}
			
			// Warship, 16.05.11. Генер "Justice for sale".
			if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_prison")
			{
				link.l13 = "Quiero hablar contigo sobre un hombre en particular, "+PChar.GenQuest.JusticeOnSale.SmugglerName+". Él es tu prisionero, si no me equivoco.";
				link.l13.go = "JusticeOnSale_1";
			}
			
			// --> belamour ночной приключенец
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToJail"))
			{
				link.l14 = "Hola oficial. Que yo sepa, hace algún tiempo, un ciudadano borracho fue detenido después de intentar pelear con un guardia en las calles."; 
				link.l14.go = "NightAdventure_CitizenHomie";
			}
			
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToPrisoner"))
			{
				link.l14 = "Oficial, hablé con el centinela, y él retiró sus reclamaciones. Aquí tienes un comprobante de él."; 
				link.l14.go = "NightAdventure_HomieToPrisoner";
			}
			// <-- приключенец
			NextDiag.TempNode = "First_officer";
		break;
		
		// --> Jason Похититель
		case "Marginpassenger":
			dialog.text = "¿Sí? ¿Qué es lo que estás dispuesto a decirme?";
			link.l1 = "Recientemente, me han detenido en la calle por "+pchar.GenQuest.Marginpassenger.Name+" quien me ofreció organizar una fechoría sucia: capturar y luego pedir rescate por una persona llamada "+pchar.GenQuest.Marginpassenger.q1Name+". Es "+pchar.GenQuest.Marginpassenger.Text+"...";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Mmm... Eso es muy intrigante, ¡por favor, continúa!";
			link.l1 = "Él conocía el nombre del barco, en el cual "+pchar.GenQuest.Marginpassenger.q1Name+" planeaba zarpar. Es "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")))+" llamado '"+pchar.GenQuest.Marginpassenger.ShipName+"'. Además, me dijo la hora en que ese barco debía zarpar.";
			link.l1.go = "Marginpassenger_2";
		break;
	
		case "Marginpassenger_2":
			dialog.text = "¿Y él sugirió que capturaras al pasajero y luego exigieras un rescate por él?";
			link.l1 = "Exactamente. Para cobrar el rescate, iría a "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+", a cierta persona con el nombre de "+pchar.GenQuest.Marginpassenger.q2Name+". Le pagué por esta información, pero, por supuesto, no iba a secuestrar a esa persona.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "¿Así que decidiste venir a verme y dejarme saber?";
			link.l1 = "Exactamente. Estoy seguro de que las acciones de ese canalla están amenazando a los ciudadanos de tu ciudad, y espero que tomes medidas adecuadas.";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			dialog.text = "Tenías toda la razón cuando viniste a mí, "+GetAddress_Form(NPChar)+"¡Este granuja, "+pchar.GenQuest.Marginpassenger.Name+", ha estado bajo nuestro seguimiento durante mucho tiempo. Investigaré, y si se confirma todo lo que dijiste, encerraremos a este canalla detrás de las rejas por medio año. ¡Eso le enseñará a no tramar esas clases de planes contra ciudadanos respetables!\nBueno, por tu honestidad y disposición para servir a una buena causa, ciertamente informaré sobre tu acción a nuestro gobernador, lo cual, por supuesto, afectará su actitud hacia ti... de una manera positiva. ¡Gracias por tu ayuda, capitán!";
			link.l1 = "Hmm... De nada, fue un placer ayudar. ¡Adiós!";
			link.l1.go = "Marginpassenger_5";
		break;
		
		case "Marginpassenger_5":
			DialogExit();
			NextDiag.CurrentNode = "First_officer";
			AddQuestRecord("Marginpassenger", "20");
			AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
			CloseQuestHeader("Marginpassenger");
			pchar.quest.Marginpassenger_InWorld.over = "yes"; //снять таймер
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			ChangeContrabandRelation(pchar, -25);
			if (GetCharacterIndex("MarginCap") != -1)
			{
				sld = characterFromId("MarginCap");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter(sld.id);
				Group_DeleteGroup("Sea_MarginCap1");
			}
		break;
		//<-- Похититель

		case "EncGirl_1":
			dialog.text = "Estoy todo oídos.";
			link.l1 = "He traído a tu fugitivo.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "¡Oh, capitán, muchas gracias! ¿Cómo está ella? ¿Está herida? ¿Por qué se escapó? ¿Por qué?\n¿No entiende? ¡El novio es un hombre rico e importante! La juventud es ingenua y tonta... incluso cruel. ¡Recuérdalo!";
			link.l1 = "Bueno, tú eres su padre y la decisión final es tuya, pero yo no me apresuraría con la boda...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "¿Qué sabes tú? ¿Tienes tus propios hijos? ¿No? Cuando tengas uno, ven a verme y hablaremos.\nPrometí una recompensa a cualquiera que la devolviera a su familia.";
			link.l1 = "Gracias. Deberías vigilarla. Tengo la corazonada de que no se detendrá en eso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Prison1":
			pchar.questTemp.ReasonToFast.SpeakOther = true;
			dialog.text = "Estoy todo oídos, capitán.";
			link.l1 = "Quiero contarte sobre una colusión criminal entre un oficial de tu guarnición y piratas (explica el asunto).";
			if(makeint(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_Prison_BadRep";			
			}
			else
			{
				link.l1.go = "ReasonToFast_Prison_GoodRep";	
			}
		break;
		case "ReasonToFast_Prison_GoodRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Gracias,"+GetSexPhrase("señor","señorita")+"¡Daré inmediatamente la orden de arrestar al villano.\nSin embargo, has incurrido en gastos y las arcas municipales, ay, están vacías...";
				link.l1 = "¡Señor! No lo hice por el dinero...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_11";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Gracias, "+GetSexPhrase("señor","señorita")+"¡Inmediatamente daré la orden de arrestar al villano! Piénsalo. Queríamos recompensarlo con un arma personal por su excelente servicio. Qué bueno que todo se aclaró y no tengo nada de qué avergonzarme.";
				link.l1 = "Siempre contento de servir a la justicia.";
				link.l1.go = "ReasonToFast_Prison_GoodRep_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Mi"+GetSexPhrase("ster","ss")+"¡Habíamos sospechado de ese oficial y sus escorias durante bastante tiempo por sus actos sucios, pero creo que cometiste una imprudencia al lidiar con ellos sin testigos!";
				link.l1 = "¡Señor! Pero tuve que defenderme...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_31";	
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";	
			}
		break;
		
		case "ReasonToFast_Prison_BadRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "¡Capitán, te das cuenta de lo que has hecho?! ¡Hemos estado intentando preparar esta trampa durante más de un mes! Y ahora, solo para tu diversión, has arruinado la reunión de nuestra patrulla con el mensajero "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" ¿y ahora vienes aquí para alardear?! ¿Quizás, ahora puedes decirme cómo debería explicar todos los gastos y costos de esta operación?!";
				link.l1 = "¡Su Gracia! Simplemente se niega a ver el punto...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Permíteme mirar este mapa...\n¿Me estás tomando el pelo? ¿Esta arrugada hoja de pergamino es una prueba?";
				link.l1 = "¡Su Gracia! Simplemente se niega a ver el punto...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				TakeItemFromCharacter(pchar, "mapQuest");	
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";	
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Ahora esa es una justificación original de la destrucción de todo el grupo de patrulla. Bueno, al menos al venir aquí nos has ahorrado la necesidad de buscar al asesino.";
				link.l1 = "¡Su Gracia! Simplemente se niega a ver el punto...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_Prison_GoodRep_11":
			dialog.text = "No obstante, creo que tus esfuerzos deben ser recompensados. Toma este mapa; se encontró entre las pertenencias de un pirata que ha ido recientemente a la horca. Si Dios quiere, tal vez encuentres realmente ese tesoro, aunque lo veo bastante improbable...";
			link.l1 = "¡Gracias, eso es muy generoso de tu parte!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_21":
			dialog.text = "Tu celo es encomiable. Por favor, acepta esta espada como recompensa, es lo menos que puedo hacer por ti. Ah, y puedes quedarte con este mapa para ti. Estoy seguro de que hay muchas de estas falsificaciones en el Archipiélago.";
			link.l1 = "¡Gracias, eso es muy generoso de tu parte!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_31":
			dialog.text = "Puede ser, puede ser... Bueno, digamos que este trato fue decidido por la justicia divina y por la voluntad de nuestro Señor.";
			link.l1 = "¡Gracias, eso es muy generoso de tu parte!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");			
		break;
		
		case "ReasonToFast_Prison_BadRep1":
			dialog.text = "¡No te atrevas a darme lecciones! Para mí, es obvio que estás en colaboración con estos sinvergüenzas! ¡Guardias, arresten a este 'bienintencionado'!";
			link.l1 = "¡De ninguna manera!";
			link.l1.go = "fight";
			
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;			
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		// ------------------------- Повод для спешки -----------------------------
		
		// -------------------------- Операция 'Галеон' ----------------------------
		case "CapComission_PrisonBad1":
			dialog.text = "¿Y qué asuntos tienes con él?";
			link.l1 = "Tengo varios asuntos privados que discutir.";
			link.l1.go = "CapComission_PrisonBad2";
		break;
		
		case "CapComission_PrisonBad2":
			dialog.text = "Capitán, tengo una orden directa de detener y enviar a la residencia a cualquiera que pregunte acerca de "+pchar.GenQuest.CaptainComission.Name+"para un interrogatorio más profundo.";
			link.l1 = "¡Bonita organización tienes aquí! ¡Haciendo que los prisioneros vengan a ti para ser arrestados!";
			link.l1.go = "CapComission_PrisonBad3";
		break;
		
		case "CapComission_PrisonBad3":
			dialog.text = "¡Y sin embargo, te solicitaría que te rindas y entregues tus armas!";
			link.l1 = "¡Al diablo contigo! ¡Quítamelo a la fuerza, entonces!";
			link.l1.go = "fight";
			CaptainComission_GenerateCaptainInPrison(); // данила . на всякий случай ,чтобы сгенерился нормально.
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonGood1":
			dialog.text = "Sí, por supuesto. Tengo órdenes del gobernador para brindarte ayuda en este asunto. Ahora puedes visitar al prisionero.";
			link.l1 = "Gracias...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonFree1":
		if(CheckAttribute(pchar,"GenQuest.CaptainComission"))// лесник . разделение диалога если кеп убит или нет
		{
			dialog.text = "Ehm, capitán, no tengo la autoridad para liberar a este prisionero de la custodia. Debes solicitar un permiso del gobernador.";
			link.l1 = "Oficial, estoy actuando por el bien de la pesquisa. El prisionero accedió a cooperar con las autoridades y revelar el escondite. El tiempo es esencial: los contrabandistas pueden encontrar la preciosa carga y luego se perderá para la población.";
			link.l1.go = "CapComission_PrisonFree2";
		}
         else
		 {
         	dialog.text = "No deberías haberlo matado, capitán... Aunque a mí no me importa. Tendremos que ejecutarte en lugar de él. ¡Guardias! ¡Capturadlo!";
            link.l2 = "¡Elegiste al hombre equivocado para joder!...";
             link.l2.go = "fight";
			 NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		 }			 
		break;
		
		case "CapComission_PrisonFree2":
			dialog.text = "Pero podría asignarle escolta a él.";
			link.l1 = "No hay necesidad de... Tengo suficientes guardias. Además, no querría que se hiciera pública la ubicación del escondite.";
			link.l1.go = "CapComission_PrisonFree3";
		break;
		
		case "CapComission_PrisonFree3":
			dialog.text = "Hmm... oh, bueno. Pero responderás por él con tu cabeza.";
			link.l1 = "Por supuesto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		break;
		// -------------------------- Операция 'Галеон' ----------------------------
		
		case "F_ShipLetters_1":
			dialog.text = "Habla ahora, estoy escuchando.";
			link.l1 = "Tengo conmigo algunos documentos de un barco. Su dueño debe haberlos perdido, y creo que podrían ser de tu interés.";
			link.l1.go = "F_ShipLetters_2";
			pchar.questTemp.different.GiveShipLetters.speakFort = true;
		break;
		
		case "F_ShipLetters_2":			
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "¡Tonterías! ¡No me distraigas de mi trabajo! Ve a las autoridades portuarias, ¡si te importa!";
				link.l1 = "Bueno, gracias, supongo...";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Sí, es el dueño. Quizás, un premio de "+sti(pchar.questTemp.different.GiveShipLetters.price2)+" pesos servirán como una recompensa adecuada por tu vigilancia, capitán.";
					link.l1 = "Quizás no.";
					link.l1.go = "F_ShipLetters_3";	
					link.l2 = "Una oferta generosa. ¡Los documentos son tuyos, entonces!";
					link.l2.go = "F_ShipLetters_4";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "¡Oh, ahora eso es realmente interesante! Creo que la tesorería de la ciudad te pagará gustosamente "+sti(pchar.questTemp.different.GiveShipLetters.price4)+" pesos por tu contribución en la lucha contra el comercio ilegal.";
						link.l1 = "Quizás no.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Una oferta generosa. ¡Los documentos son tuyos, entonces!";
						link.l2.go = "F_ShipLetters_4";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "¡Oh Señor! Qué buena suerte que hayas venido a mí. Supongo que mi desafortunado colega estará encantado de pagarte "+sti(pchar.questTemp.different.GiveShipLetters.price3)+" pesos para evitar publicidad de este asunto.";
						link.l1 = "Quizás no.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Una oferta generosa. ¡Los documentos son tuyos, entonces!";
						link.l2.go = "F_ShipLetters_4";
					}
				}
			}
		break;
		
		case "F_ShipLetters_3":
			dialog.text = "Esta es mi ciudad, capitán.";
			link.l1 = "Lo recordaré.";
			link.l1.go = "exit";
		break;
		
		case "F_ShipLetters_4":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4)); 
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3)); 
				}
			}
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "8");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		
        case "ForGoodMove":
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "¡Por supuesto, puedes ver todo! ¡Aquí tengo el orden completo!";
				link.l1 = "Bueno, vamos a comprobarlo, teniente.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Por supuesto, Su Excelencia. Puede pasar.";
				link.l1 = "Gracias oficial.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// Офицер с патентом
			if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Bueno, no veo ninguna razón para rechazarte, después de todo, eres el capitán del barco al servicio de "+NationNameGenitive(sti(npchar.nation))+". Entra."; 
				link.l1 = "Gracias oficial.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// <-- legendary edition
			dialog.text = NPCStringReactionRepeat("¿Pero por qué lo necesitas? Créeme, no hay nada que valga ningún interés, excepto para los ladrones y bandidos.","Ya habíamos discutido ese deseo tuyo.","¿Otra vez? ¡Ya habíamos hablado de eso dos veces!","¿Hmm, otra vez...?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sin embargo, me gustaría unirme a tu recorrido por las casamatas. ¡Estoy muy interesado!","Sí, exactamente. Pero quería hablar de ello.","Bueno, quizás la tercera vez...","Espero que tus prisioneros no me abandonen.",npchar,Dialog.CurrentNode);
			link.l1.go = "ForGoodMove_1";
		break;
		
        case "ForGoodMove_1":
			pchar.questTemp.jailCanMove.money = 20+hrand(3)*10;
			if (sti(colonies[FindColony(npchar.city)].jail))
			{
				dialog.text = "Bueno, no veo ninguna razón para negarme. "+FindRussianDublonString(sti(pchar.questTemp.jailCanMove.money))+" y hasta que salgas de la prisión, puedes caminar libremente por los corredores e incluso conversar con los reclusos.";
				if (PCharDublonsTotal() >= sti(sti(pchar.questTemp.jailCanMove.money)))
				{
					link.l1 = "Estoy de acuerdo, ¡aquí están tus monedas!";
					link.l1.go = "ForGoodMove_agree";
				}
				link.l2 = "Eso no funcionará. Es demasiado para deambular sin rumbo por los corredores.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("No, esto está estrictamente prohibido por las regulaciones. ¿Qué? ¿Crees que tenemos un circo aquí? Lárgate y no me distraigas de mis deberes.","No puedo permitir que gente extraña ande por mi prisión. ¡Por favor, deja de molestarme!");
				link.l1 = "Está bien, como tú digas...";
				link.l1.go = "exit";
			}
		break;
		
        case "ForGoodMove_agree":
            dialog.text = "Está bien, puedes comenzar tu excursión ahora...";
			link.l1 = "Gracias, oficial.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.money)));
		break;
		
        case "KnowAboutPrisoner":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "Por asesinato."; break;
				case "1": sTemp = "Se le acusa de piratería."; break;
				case "2": sTemp = "Por bandidaje y robo."; break;
				case "3": sTemp = "Le pillaron robando."; break;
				case "4": sTemp = "Por hurto."; break;
				case "5": sTemp = "Por hacer trampas."; break;
				case "6": sTemp = "Por vagabundeo y mendicidad."; break;
			}
			dialog.text = sTemp;
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				link.l1 = "Ya veo... Entrégamelo, oficial, y entonces yo decidiré el destino de este prisionero por mí mismo.";
				link.l1.go = "KnowAboutPrisoner_gengov";
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				link.l1 = "Ya veo... Entrégamelo a mí, oficial, y luego decidiré yo mismo el destino de este prisionero.";
				link.l1.go = "KnowAboutPrisoner_admiral";
				DeleteAttribute(pchar, "questTemp.jailCanMove.City");
				break;
			}
			link.l1 = "Ya veo... ¿Y hay alguna posibilidad de comprar su libertad, pagar una fianza... o liberarlo de alguna otra manera?";
			link.l1.go = "KnowAboutPrisoner_" + pchar.questTemp.jailCanMove.ownerPrison;
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
		
        case "KnowAboutPrisoner_0":
			dialog.text = "Por supuesto que no. Ese pájaro de horca irá directo al infierno. ¡El gobernador tiene su causa bajo control especial!";
			link.l1 = "Je, ya veo...";
			link.l1.go = "notFree_exit";
		break;	
		
		case "KnowAboutPrisoner_1":
			dialog.text = "¿Estás bromeando? ¡Debe haber ido a la horca hace mucho tiempo! Seguramente pronto se casará con una cuerda. Simplemente olvídalo.";
			link.l1 = "Lo tengo. Y ya olvidado...";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_2":
			dialog.text = "No creo que sea así. Ha causado muchos problemas a nuestra gente del pueblo. Así que no lo pidas.";
			link.l1 = "Mmm, ya veo.";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_3":
			dialog.text = "Probablemente no. Es un ladrón, y un ladrón debe permanecer en la cárcel.";
			link.l1 = "¡Oh! Bien dicho, teniente!";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_4":
			dialog.text = "Realmente no lo sé. Ha robado solo una cosa insignificante. No puedo liberarlo, pero dejarlo pudriéndose en la cárcel ciertamente no está bien.";
			link.l1 = "Bueno, entonces entrégamelo, teniente. Yo pagaré su fianza, una cantidad razonable, por supuesto.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_5":
			dialog.text = "¿Liberarlo? Eso parece posible. En mi opinión, no tiene sentido detener a ese pequeño ladrón aquí.";
			link.l1 = "Bueno, entonces entrégamelo, teniente. Pagaré su fianza, una cantidad razonable, por supuesto.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
		case "KnowAboutPrisoner_6":
			dialog.text = "Hmm... Hay razón en tus palabras. Este vagabundo no pertenece aquí, solo está propagando suciedad y enfermedades...";
			link.l1 = "Bueno, entonces entrégamelo, teniente. Pagaré la fianza por él, una cantidad razonable, por supuesto.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_free":
			pchar.questTemp.jailCanMove.ownerPrison.money = 50+hrand(10)*10;
			dialog.text = "Está bien, tenemos un trato. "+FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money))+" al contado, y puedes llevártelo ahora mismo.";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.jailCanMove.ownerPrison.money))
			{
				link.l1 = LinkRandPhrase("¡Excelente! ¡Estoy de acuerdo!","¡Tenéis un trato, oficial!","Excelente. Estoy listo para pagar esa contribución.");
				link.l1.go = "KnowAboutPrisoner_agree";
			}
			link.l2 = "No, eso es demasiado caro. Creo que pasaré.";
			link.l2.go = "KnowAboutPrisoner_exit";
		break;
		
        case "KnowAboutPrisoner_agree":
			dialog.text = "Bien, puedes proceder a su celda y llevar a ese pillo contigo.";
			link.l1 = "Gracias.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.ownerPrison.money));
			Log_Info("Has dado " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money)) + "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		
        case "KnowAboutPrisoner_exit":
			dialog.text = "Bueno, es tu elección. No te daré otra oportunidad...";
			link.l1 = "No hace falta.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_expansive";
		break;
		
        case "notFree_exit":
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_notFree";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		// belamour legendary edition -->
		// генерал-губернатор
		case "KnowAboutPrisoner_gengov":
			dialog.text = "Por supuesto, su Excelencia, si así lo desea, lleve a este desafortunado. Solo tenga cuidado, sigue siendo un criminal...";
			link.l1 = "Eso es genial. No te preocupes teniente, sé lo que estoy haciendo.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// вице-адмирал
		case "KnowAboutPrisoner_admiral":
			dialog.text = "Bueno... Ni siquiera lo sé... En realidad, no puedo dejar ir a los prisioneros así como así. Pero todavía eres un vicealmirante, así que probablemente tengas el derecho de llevarte a este criminal.";
			link.l1 = "Eso es genial. No te preocupes teniente, sé lo que estoy haciendo.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// <-- legendary edition
		//---------------- Протектор ------------------
        case "First_protector":
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Gobernador General, ¡Su Excelencia! Entre, pero tenga cuidado: puede esperar cualquier cosa de estos criminales...";
				link.l1 = "No te preocupes, soldado, me encargaré si sucede algo.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "¡Saludos, Vicealmirante! Estoy de servicio aquí: me aseguro de que nadie entre o salga sin permiso. Pero usted, por supuesto, tiene el derecho de pasar libremente por aquí.";
				link.l1 = "Bueno, eso es maravilloso.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			if (sti(pchar.questTemp.jailCanMove))
			{
				dialog.text = RandPhraseSimple("Puedes pasar, el alcaide dio su permiso.","He recibido una orden del alcaide de la prisión. Puedes pasar libremente.");
				link.l1 = "Muy bien.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison.money");
			}
			else
			{
				dialog.text = RandPhraseSimple("¡No puedes avanzar más sin el permiso específico del alcaide de la prisión!","¡Solo respondo al alcaide de la prisión! Si intentas avanzar sin su permiso, ¡estás acabado!");
				link.l1 = RandPhraseSimple("Lo veo","De acuerdo")+", soldado.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First_protector";
		break;
		//---------------- Солдаты ------------------
        case "First_soldier":
            dialog.text = RandPhraseSimple("Estoy de servicio, no me molestes.","Sigue adelante, no me está permitido hablar contigo.");
			link.l1 = "Bien, soldado.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_soldier";
		break;
		//---------------- Заключенные ------------------
        case "First_prisoner": 
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) == RELATION_ENEMY)
			{
				dialog.text = LinkRandPhrase("¡Ho-ho, no es un gran momento!","Córtalos, "+GetSexPhrase("compañero","chica")+", ¡cortar!","¡Oh, infierno! ¡He perdido toda esperanza de ver el cadáver de mi carcelero!");
				link.l1 = RandPhraseSimple("¡Je!","¡Arrgh!");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.DeliverToBander")) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("Espera, "+GetSexPhrase("compañero","chica")+"¡¡Libérame!","Escucha, "+GetSexPhrase("compañero","chica")+", amablemente abre la celda.");
					link.l1 = "¿Por qué razón?";
					link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("¡Se me acusa de robo, pero no soy culpable!","Arrgh, tú, escoria bien arreglada... ¿Te gustaría sentarte en mi celda un rato?! Kheh-heh-heh...","¡No soy culpable!");
				link.l1 = RandPhraseSimple("¡Cállate!","No me importa una mierda sobre ti...");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.DeliverToBander") && !sti(colonies[FindColony(npchar.city)].HeroOwn)) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("Espera, "+GetSexPhrase("compañero","chica")+", ¡no pases tan rápido!","No te apresures, "+GetSexPhrase("compañero","chica")+", hablemos.");
					link.l1 = "¿Por qué razón?";
					if (rand(1))
					{
						link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
					}
					else
					{
						link.l1.go = "Deliver_1"; // на квест передачу весточки
					}
				}
			}
		break;
		// -------------------- освобождение заключённого --------------------
        case "Prisoner_1":
            dialog.text = "Escúchame, compañero. No pienses que no me veo bien y esas cosas. Solo necesito salir de aquí...";
			link.l1 = "¿¡Qué?!";
			link.l1.go = "Prisoner_2";
			GetChestPlaceName();
			pchar.questTemp.jailCanMove.prisonerId = npchar.id; //запомним Id
			pchar.questTemp.jailCanMove.IsTrue = rand(4); //вид клада
			pchar.questTemp.jailCanMove.Item1 = GenQuestPrison_GenerateArtefact();
			pchar.questTemp.jailCanMove.Item2 = GenQuestPrison_GenerateBlade();
			pchar.questTemp.jailCanMove.Name = GetFullName(npchar); //имя перца
			npchar.nation = PIRATE;
		break;
        case "Prisoner_2":
            dialog.text = "¡Lo que has oído! Ayúdame, y podré recompensarte...";
			link.l1 = "Ahora eso es interesante. ¿Quién eres y qué puedes ofrecerme?";
			link.l1.go = "Prisoner_3";
		break;
        case "Prisoner_3":
            dialog.text = "Mi nombre es "+GetFullName(npchar)+". Tengo algunas cosas escondidas en un lugar seguro. Solo sácame de aquí y llévame a "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Acc")+". Allí, en una gruta, tengo el tesoro. ¡Lo conseguiremos y compartiremos!";
			link.l1 = "¿Y qué tienes en tu alijo? ¿Y cómo puedo saber que estás diciendo la verdad?";
			link.l1.go = "Prisoner_4";
		break;
        case "Prisoner_4":
            dialog.text = "¡Juro que estoy diciendo la verdad! En cuanto al escondite, hay un tesoro y dinero...";
			link.l1 = "No, compañero. No voy a arriesgar mi pellejo por un alijo cuestionable. Lo siento...";
			link.l1.go = "Prisoner_5";
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) != RELATION_ENEMY)
			{			
				// belamour legendary edition адмирал и губернатор может договориться без денег
				bool bAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bool bGenGov = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == GetBaseHeroNation());
				if(!bAdmiral && !bGenGov)
				{
				link.l2 = "Bueno, podría valer la pena correr un riesgo... Sugiero lo siguiente: puedo eliminar a los guardias en la prisión y llevarte a mi barco. Si todo sale bien, quiero que te quedes a mi lado todo el tiempo hasta que lleguemos a la gruta en  "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc")+". ¿Trato?"; // belamour gen
				link.l2.go = "Prisoner_agree"; //силовой способ вызволения
				}
				link.l3 = "Está bien, intentaré ayudarte. Hablaré con el alcaide de la prisión. Quizás, pueda sacarte bajo fianza.";
				link.l3.go = "ToPrisonHead_agree"; //мирный способ вызволения
			}
			else
			{
				link.l2 = "Está bien, te creeré y abriré tu celda. Quiero que te quedes a mi lado todo el tiempo hasta que lleguemos a la gruta en "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc")+". ¿Trato?";
				link.l2.go = "Prisoner_agree_3"; //силовой способ вызволения, когда тюремщики убиты
			}
		break;
        case "Prisoner_5":
            dialog.text = RandPhraseSimple("¡Maldito seas, pillo!","Maldito me has estafado, escoria...");
			link.l1 = RandPhraseSimple("Y todo lo mejor para ti también. Adiós...","La luna no necesita el ladrido de los perros...");
			link.l1.go = "NoMoreTalkExit";
		break;
        case "Prisoner_agree":
            dialog.text = "Bien. No estoy en posición de ser exigente.";
			link.l1 = "Está bien. Ahora romperé tu cerradura para sacarte, y abriremos camino. ¿Estás listo?";
			link.l1.go = "Prisoner_agree_1";
		break;
        case "Prisoner_agree_1":
            dialog.text = "Sí, "+GetSexPhrase("compañero","chica")+", ¡Estoy listo!";
			link.l1 = "¡Entonces, vamos a ello!";
			link.l1.go = "Prisoner_agree_2";
		break;
        case "Prisoner_agree_2":
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

        case "Prisoner_agree_3":
            dialog.text = "Bien. No estoy en posición de ser exigente.";
			link.l1 = "Está bien. Sígueme tan rápido como puedas, aún necesitamos llegar a mi barco. ¡No te demores!";
			link.l1.go = "Prisoner_agree_4";
		break;
        case "Prisoner_agree_4":
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_agree":
            dialog.text = "Bueno, puedes intentarlo. ¡Espero que lo superemos! Pero no pierdas tiempo, en un par de días me habré ido de aquí...";
			link.l1 = "Espera aquí, yo organizaré todo.";
			link.l1.go = "NoMoreTalkExit";
			pchar.questTemp.jailCanMove.City = npchar.City; //город
			pchar.questTemp.jailCanMove.ownerPrison = rand(6); //характер преступления
			SetTimerCondition("GivePrisonFree_Over", 0, 0, 2, false);
			AddQuestRecord("GivePrisonFree", "5");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
		break;

        case "ToPrisonHead_canMove":
            dialog.text = "Bueno, ¿qué dices, "+GetSexPhrase("compañero","chica")+"?";
			link.l1 = "Todo ha sido arreglado, y puedo llevarte desde aquí.";
			link.l1.go = "ToPrisonHead_canMove_1";
		break;
        case "ToPrisonHead_canMove_1":
            dialog.text = "¡Entonces vámonos de aquí! ¡Oh, Señor, qué feliz estoy!";
			link.l1 = "Resumamos. Quiero que te quedes a mi lado todo el tiempo hasta que lleguemos a la gruta en "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Dat")+", no te quedarás más atrás que un solo paso. Solo por si acaso. ¿Estás de acuerdo?";
			link.l1.go = "ToPrisonHead_canMove_2";
		break;
        case "ToPrisonHead_canMove_2":
            dialog.text = "Por supuesto, ¡estoy de acuerdo! Más aún que no estoy en posición de elegir.";
			link.l1 = "Entonces eres libre.";
			link.l1.go = "ToPrisonHead_canMove_exit";
		break;
        case "ToPrisonHead_canMove_exit":
			pchar.quest.GivePrisonFree_Over.over = "yes";
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_notFree":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "murder"; break;
				case "1": sTemp = "piracy"; break;
				case "2": sTemp = "brigandry"; break;
				case "3": sTemp = "thievery"; break;
			}
            dialog.text = "Bueno, ¿qué dices, "+GetSexPhrase("compañero","chica")+"?";
			link.l1 = "No pude organizar tu liberación. Estás acusado de "+sTemp+", así que no puedes ser rescatado.";
			link.l1.go = "ToPrisonHead_notFree_1";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
		break;
		
        case "ToPrisonHead_notFree_1":
            dialog.text = "¡Pero fui calumniado! ¡Oh diablo! ¿Y qué haré ahora? ¡Voy a pudrirme aquí vivo!";
			link.l1 = "Lo siento, compañero, pero no hay nada que pueda hacer por ti.";
			link.l1.go = "ToPrisonHead_notFree_2";
			link.l2 = "Solo queda una oportunidad, liberarte con fuerza. Voy a romper tu cerradura ahora para sacarte, y vamos a abrirnos paso. ¿Estás listo?";
			link.l2.go = "Prisoner_agree_1";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		
        case "ToPrisonHead_notFree_2":
            dialog.text = RandPhraseSimple("¡Maldito seas!","Maldita sea, me has estafado, perra...");
			link.l1 = "Y todo lo mejor para ti también. Adiós...";
			link.l1.go = "NoMoreTalkExit";
			AddQuestRecord("GivePrisonFree", "7");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
		break;

        case "ToPrisonHead_expansive":
			dialog.text = "Entonces, ¿alguna buena noticia, "+GetSexPhrase("compañero","chica")+"?";
			link.l1 = "La fianza para tu liberación es demasiado alta, no tengo tal dinero. Tengo que dejar de ayudarte.";
			link.l1.go = "ToPrisonHead_notFree_2";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		//==> в месте, где клад припрятан
        case "PrisonerInPlace":
			switch (sti(pchar.questTemp.jailCanMove.IsTrue))
			{
				case 0:
					dialog.text = "Escucha, he revisado todo, pero no encontré ningún tesoro. Una lástima que resultó de esta manera. Alguien debe haberlo excavado antes que nosotros.";
					link.l1 = "¿¡Y cómo puede ser eso?!";
					link.l1.go = "PrisonerInPlace_1";
				break;
				case 1:
					dialog.text = "¡Lo he encontrado! El tesoro todavía está donde lo dejé.";
					link.l1 = "Excelente. Bueno, ¿entonces nos separamos?";
					link.l1.go = "Node_1";
				break;
				case 2:
					dialog.text = "Bueno, aquí está, mi escondite. No es mucho, pero esto es todo lo que tengo. Como acordamos, la mitad es tuya.";
					link.l1 = "Sí, el tesoro es modesto, de hecho. Bueno, aún mejor que nada.";
					link.l1.go = "Node_2";
				break;
				case 3:
					dialog.text = "Capitán, lo siento, pero... No hay tesoro.";
					link.l1 = "¿¡Qué?! ¡Me has engañado, canalla! Te llevé hasta esa isla, ¿y para qué? ¡No te saldrás con la tuya!";
					link.l1.go = "Node_3";
				break;
				case 4:
                    ok = GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(PChar, "map_part2") == 0;
                    if(GetCharacterItem(PChar, "map_part1") > 0 && !ok) // Первая половинка есть, но вторую дать нельзя
                    {
                        dialog.text = "Escucha, he revisado todo, pero no encontré ningún tesoro. Una lástima que resultó de esta manera. Alguien debe haberlo excavado antes que nosotros.";
                        link.l1 = "¿¡Y cómo puede ser eso?!";
                        link.l1.go = "PrisonerInPlace_1";
                    }
                    else
                    {
                        dialog.text = "¡Maldición... ¿Cómo puede ser eso? ¡No puede ser!";
                        link.l1 = "¿Qué pasa, compañero? ¿Dónde está el tesoro? ¡No me digas que no hay ninguno!";
                        link.l1.go = "Node_4";
                    }
				break;
			}
		break;
			
		case "Node_1":
			dialog.text = "Por supuesto, como se acordó. La mitad del tesoro es tuyo.";
			link.l1 = "¡Santo Señor, ahora hay seguramente un montón de cosas preciosas!";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("Has recibido tu parte del tesoro");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 4+hrand(4));
			TakeNItems(pchar, "jewelry1", 70+rand(15));
			TakeNItems(pchar, "jewelry2", 50+rand(15));
			TakeNItems(pchar, "jewelry3", 60+rand(15));
			TakeNItems(pchar, "jewelry4", 40+rand(10));
			TakeNItems(pchar, "jewelry5", 10+rand(10));
			TakeNItems(pchar, "jewelry46", 60+rand(20));
			TakeNItems(pchar, "jewelry47", 40+rand(15));
			TakeNItems(pchar, "jewelry40", 60+rand(20));
			AddQuestRecord("GivePrisonFree", "3_1");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_2":
			dialog.text = "Capitán, también está ese objeto indígena entre otras cosas. Puedes tenerlo además de tu parte.";
			link.l1 = "Bueno, ¡al menos algo valioso para tu liberación! Entrégamelo.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("Has recibido tu parte del tesoro");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item1;
			TakeNItems(pchar, sTemp, 1);
			TakeNItems(pchar, "jewelry5", 40+rand(10));
			TakeNItems(pchar, "jewelry6", 20+rand(20));
			TakeNItems(pchar, "jewelry17", 80+rand(20));
			TakeNItems(pchar, "jewelry13", 10+rand(10));
			TakeNItems(pchar, "jewelry10", 20+rand(20));
			TakeNItems(pchar, "jewelry12", 50+rand(20));
			TakeNItems(pchar, "jewelry11", rand(2)+1);
			AddQuestRecord("GivePrisonFree", "3_2");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_3":
			dialog.text = "Espera, Capitán, no te exaltes, déjame hablar. También soy marino, igual que tú. Fui encarcelado por error, lo juro. Tú eras mi única oportunidad de escapar, y tuve que mentirte acerca del tesoro.\nNo hay tesoro, pero escondí algo bueno allí. Tómalo, y déjame ir en paz. Quizás, en una batalla algún día, te ayude a sobrevivir.";
			link.l1 = "Está bien, de todas formas no esperaba mucho de ti. Gracias a Dios que no guardo rencor.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("Ha recibido material");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item2;
			TakeNItems(pchar, sTemp, 1);
			AddQuestRecord("GivePrisonFree", "3_3");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_4":
			dialog.text = "¡¡¡No!!! ¡No está allí! Maldita chatarra... Capitán, estaba absolutamente seguro de que lo encontraría aquí! Pero, al parecer, ¡me equivoqué! Algo en ese pedazo de papel era realmente poco claro...";
			link.l1 = "Vaya... Estás en un serio apuro, compañero. Pero aún así me gustaría escuchar tu explicación.";
			link.l1.go = "Node_4_1";
		break;
			
		case "Node_4_1":
			dialog.text = "Tenía un pedazo del mapa. ¡Eso era un mapa de verdad, lo juro! Pero es muy difícil decir, qué isla se mostraba en él... Pensé que era aquí... Pero, como ves ahora, me equivoqué.";
			link.l1 = "¿Qué pedazo de papel? ¡Dámelo ahora mismo!";
			link.l1.go = "Node_4_2";
		break;
			
		case "Node_4_2":
			AddMapPart();
			dialog.text = "Por supuesto, tómalo. Capitán, libérame... ¿por favor? Realmente pensé que el tesoro estaba allí. Tal vez, averigües dónde está y lo tomes para ti. Te lo ruego.";
			link.l1 = "Ya veo... De hecho, es difícil descifrar algo con ese pedazo. Se necesita la segunda mitad del mapa. Muy bien, lárgate. Ahora puedo ver que no fue tu culpa.";
			link.l1.go = "PrisonerInPlace_4";
		break;
			
		case "PrisonerInPlace_1":
			dialog.text = "Muy sencillo, "+GetSexPhrase("compañero","muchacha")+". Todo en la vida sucede.\nBueno, ya que estás aquí quédate y busca más. Bueno, ¡tengo que irme!\n¡Adiós, "+GetSexPhrase("mi amigo","chica")+", gracias por salvar mi vida. ¡Siempre te recordaré!";
			link.l1 = "¡Bribón! ¿Crees que te dejaré salir impune de esto?! ¡Eh! ¡Espera, cobarde!";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "4");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
        case "PrisonerInPlace_2":
			LAi_group_Delete("EnemyFight");
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableMonstersGen(pchar.location, false);
			npchar.lifeDay = 0;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();

            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup";
		break;
		
        case "PrisonerInPlace_3":
			dialog.text = "Aquí tienes. ¡Gracias!";
			link.l1 = "Adiós...";
			link.l1.go = "PrisonerInPlace_2";
		break;
		
        case "PrisonerInPlace_4":
			dialog.text = "¡Gracias, capitán! ¡Estaré rezando por ti hasta el resto de mis días!";
			link.l1 = "¡Oh, cállate! Ve en paz...";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "3_4");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
        
		// -------------------- освобождение заключённого --------------------
		// ------------------------ передать маляву --------------------------
        case "Deliver_1":
			dialog.text = "Me llaman "+GetFullName(npchar)+". Tengo una petición para ti, je-je...";
			link.l1 = "¿Qué pasa?";
			link.l1.go = "Deliver_2";
		break;
        case "Deliver_2":
			dialog.text = "Necesito que se envíe un mensaje fuera de la cárcel. ¿Lo harás?";
			link.l1 = "¿Y qué hay para mí?";
			link.l1.go = "Deliver_3";
		break;
        case "Deliver_3":
			dialog.text = "Los camaradas no te decepcionarán, lo prometo... ¿Entonces? ¿Estás dentro?";
			link.l1 = "No, no estoy interesado.";
			link.l1.go = "Prisoner_5";
			link.l2 = "Bueno, si no requiere demasiado esfuerzo de mi parte, puedo hacerlo.";
			link.l2.go = "Deliver_agree";
		break;
        case "Deliver_agree":
			dialog.text = "Bien. Ahora escúchame con atención. Dos camaradas están esperando mi mensaje en una casa, para que no sean aprehendidos durante una redada. Pero no tengo ni idea de qué casa es exactamente. Tendrás que buscar.";
			link.l1 = "¿Qué quieres decir con, buscar?";
			link.l1.go = "Deliver_4";
		break;
        case "Deliver_4":
			dialog.text = "Buscar como en buscar. Correrás por la ciudad, mirarás en las casas. Cuando llegues al lugar correcto, no te dejarán salir sin hablar. Pero ten en cuenta que como mucho me quedaría allí dos días más. Así que no te demores.";
			link.l1 = "Ya veo. Bueno, entrega tu misiva, entonces.";
			link.l1.go = "Deliver_5";
		break;
        case "Deliver_5":
			pchar.questTemp.jailCanMove.Deliver.locationId = GetBanderLocation(npchar); //Id коммона
			if (pchar.questTemp.jailCanMove.Deliver.locationId == "none")
			{
				dialog.text = "Mmm, sabes, simplemente no me agradas. He cambiado de opinión. ¡Vamos, no te quedes ahí parado!";
				link.l1 = "¡Mírate! Bueno, como desees...";
				link.l1.go = "NoMoreTalkExit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			}
			else
			{
				dialog.text = "Aquí. Gracias, "+GetSexPhrase("compañero","chica")+".";
				link.l1 = "Para nada.";
				link.l1.go = "NoMoreTalkExit";
				GiveItem2Character(Pchar, "Malyava");
				pchar.questTemp.jailCanMove.Deliver.Id = npchar.id; //Id зэка
				pchar.questTemp.jailCanMove.Deliver.name = GetFullName(npchar); //имя зэка
				pchar.questTemp.jailCanMove.Deliver.City = npchar.city; //город (Id колонии)
				pchar.questTemp.jailCanMove.Deliver.good = rand(3); //опрокинут или нет
				pchar.questTemp.jailCanMove.Deliver.price = rand(6)*500+500; //цена услуги
				pchar.quest.DeliverToBander.win_condition.l1 = "location";
				pchar.quest.DeliverToBander.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.locationId;
				pchar.quest.DeliverToBander.win_condition = "DeliverToBander";
				pchar.quest.DeliverToBander.again = true; 
				SetTimerCondition("DeliverToBander_over", 0, 0, 2, false);
				ReOpenQuestHeader("GivePrisonFree");
				AddQuestRecord("GivePrisonFree", "8");
				AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
				AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			}
		break;
		
		// Warship, 16.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "Sí, fue arrestado bajo el cargo de contrabando. Pero, ¿por qué te importa ese pájaro de la horca, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Su pandilla está planeando organizar su fuga y continuar con sus sucios actos.";
			link.l1.go = "JusticeOnSale_2";
			link.l2 = "He oído que él no era culpable.";
			link.l2.go = "JusticeOnSale_3";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "Debes notificar al gobernador, "+GetAddress_Form(NPChar)+"¡, estos granujas deben ser todos capturados!";
			link.l1 = "Haré justo eso.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "Escucha, "+GetFullName(PChar)+", ese tipo fue capturado mientras intentaba vender mercancías prohibidas, ¡justo en la ciudad! ¿Cómo puedes afirmar que no es culpable?";
			link.l1 = "Escuché que la acusación era infundada y que no tienes pruebas, ¿no es así? No puedes simplemente detener a un hombre que fue perjudicado.";
			link.l1.go = "JusticeOnSale_4";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "No tenemos ni testigos ni las mercancías, pero eso no cambia nada, capitán "+GetFullName(PChar)+"¡Esa persona es definitivamente culpable, y quizás no solo de comercio ilegal. De cualquier manera, ¿por qué te importaría el prisionero?";
			link.l1 = "Quizás, ¿mi palabra puede ser la fianza para ese prisionero desafortunado?";
			link.l1.go = "JusticeOnSale_5_WithoutMoney";
			
			if(sti(PChar.money) >= 5000)
			{
				link.l2 = "Quizás, ¿estos 5000 pesos pueden ser la fianza para ese desafortunado prisionero?";
				link.l2.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5_WithoutMoney":
			if(GetCharacterSkill(PChar, SKILL_LEADERSHIP) > hrand(100) || sti(PChar.money) < 5000)
			{
				dialog.text = "Está bien, "+GetAddress_Form(NPChar)+", toma a ese granuja y vete, antes de que cambie de parecer.";
				link.l1 = "Es genial ver el triunfo de la justicia, ¿no crees?";
				link.l1.go = "JusticeOnSale_6";
			}
			else
			{
				dialog.text = "No, "+GetAddress_Form(NPChar)+", eso no servirá.";
				link.l1 = "Entonces, quizás estos 5000 pesos puedan ser un argumento más convincente.";
				link.l1.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "Está bien, "+GetAddress_Form(NPChar)+", toma a ese granuja y vete, antes de que cambie de parecer.";
			link.l1 = "Es maravilloso ver el triunfo de la justicia, ¿no crees?";
			link.l1.go = "JusticeOnSale_6";
			AddMoneyToCharacter(PChar, -5000);
			PChar.GenQuest.JusticeOnSale.PrisonMoney = true;
		break;
		
		case "JusticeOnSale_6":
			DialogExit();
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_Smuggler", "mercen_"+(rand(9)+1), "man", "man", sti(PChar.rank)+5, PIRATE, -1, true, "marginal"));
			SetFantomParamFromRank(sld, sti(PChar.rank)+5, true);
			sld.name = PChar.GenQuest.JusticeOnSale.SmugglerName;
			sld.lastName = "";
			sld.dialog.filename = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "First time";
			sld.greeting = "Enc_Raiders"; 
			AddPassenger(PChar, sld, false);
			SetCharacterRemovable(sld, false);
			PChar.GenQuest.JusticeOnSale.SmugglerModel = sld.model;
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1  = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.function = "JusticeOnSale_ShoreEnterWithSmuggler";
			Log_Info("El capitán contrabandista está abordo");
			PlaySound("interface\notebook.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,0,60); // 280313 // лесник. прокрутка времени было так WaitDate("",0,0,0,2,5);
		break;
		// --> belamour ночной приключенец
		case "NightAdventure_CitizenHomie":
			dialog.text = "Sí, había uno tan violento. Fue grosero con un centinela, y luego se metió en una pelea. Nada más: estará tras las rejas durante varios días, se pondrá sobrio. ¿Por qué te importa él? Pareces ser un capitán, y este borracho no parece un marinero.";
			link.l1 = "Sí, eso es correcto, soy un capitán. Lo que pasa es que este borracho es un viejo conocido mío. Solo no le digas a nadie sobre esto, por favor. Si entiendo correctamente, ni siquiera agarró un arma. ¿Quizás lo liberarás esta vez a mi petición?";
			link.l1.go = "NightAdventure_CitizenHomie_1";
		break;
		
		case "NightAdventure_CitizenHomie_1":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomie") // отпустил под честное слово
			{
				dialog.text = "Sí, buen amigo mío. No te preocupes, no le diré a nadie. De hecho, ni siquiera pudo golpear correctamente, fue solo un intento, por eso lo metieron en la cárcel. Ya que preguntas, por respeto a ti, lo liberaré. Solo adviértele que se controle la próxima vez. O mejor aún, haz que beba menos.";
				link.l1 = "Gracias oficial.";
				link.l1.go = "NightAdventure_CitizenHomieOK";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM" || pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM") // поговорить с солдатом
			{
				dialog.text = "Sí, buen amigo. No te preocupes, no le diré a nadie. Solo que, logró golpear al centinela en la cara antes de que lo ataran. Así que no puedo soltarlo. A menos que, por supuesto, el centinela acepte retirar sus reclamaciones. Puedes hablar con él tú mismo, está patrullando alrededor de la ciudad hoy.";
				link.l1 = "No, me temo que si golpeó al guardia, entonces no puedo ayudarlo. Tendrá que permanecer detenido un par de días. Lamento molestarte, oficial.";
				link.l1.go = "CitizenHomieEnd";
				link.l2 = "Está bien, iré e intentaré negociar con el centinela.";
				link.l2.go = "NightAdventure_CitizenHomieSolder";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieOfficer") // выплата офицеру
			{
				dialog.text = "Sí, buen amigo. No te preocupes, no le diré a nadie. Lo que pasa es que atacar a un miembro de las fuerzas armadas mientras está de servicio es un delito. Puedo encontrarte a medio camino y liberarlo, pero solo bajo fianza.";
				link.l1 = "¿Y cuánto necesito pagar por ello?";
				link.l1.go = "NightAdventure_CitizenHomieOfficer";
			}
		break;
		
		case "NightAdventure_CitizenHomieOK":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
		break;
		
		case "NightAdventure_CitizenHomieEnd":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_CitizenHomieSolder":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				if(Characters[i].location != npchar.City+"_town") continue;
				if(Characters[i].chr_ai.type != "patrol") continue;
				while(SoldQty < 10) // на всякий случай, чтобы не было выхода за границы массива
				{                   // генерируется 7 солдат + 3 мушкетера
					SoldNum[SoldQty] = Characters[i].index;
					SoldQty++;
				}
			}
			iTemp = rand(SoldQty);
			pchar.GenQuest.NightAdventureSolNum = SoldNum[iTemp];
		break;
		
		case "NightAdventure_HomieToPrisoner":
			DeleteAttribute(pchar,"GenQuest.NightAdventureToPrisoner");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "*lee* Entonces... entonces... Bueno, ya que el centinela no tiene quejas, yo tampoco. Puedes llevarte a tu amigo. Solo adviértele que se controle la próxima vez. Mejor aún, hazle beber menos.";
			link.l1 = "Gracias oficial.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieOfficer":
			dialog.text = "Bueno, dado que no agarró un arma, son solo 1500 pesos.";
			link.l1 = "Me temo que no estoy listo para dar tanto. Bueno, considerando que solo estará aquí por unos días, supongo que no le hará daño. Quizás beba menos.";
			link.l1.go = "NightAdventure_CitizenHomieEnd";
			if(sti(pchar.money) >= 1500)
			{
				link.l2 = "Bien, estoy listo para pagar la fianza.";
				link.l2.go = "NightAdventure_CitizenHomieOfficer_1";
			}
		break;
		
		case "NightAdventure_CitizenHomieOfficer_1":
			AddMoneyToCharacter(pchar, -1500);
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "Puedes recoger a tu amigo. Solo adviértele que se controle la próxima vez. O mejor aún, haz que beba menos.";
			link.l1 = "Gracias oficial.";
			link.l1.go = "exit";
		break;
		// <-- ночной приключенец
		
		// --> Sinistra Путеводная звезда
		case "PZ_BasTer_ComendantDialog":
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerOpozdal"))
			{
				dialog.text = "Gracias por aceptar venir en lugar de iniciar una masacre. Al menos alguien está siendo razonable estos días.";
				link.l1 = "Entonces, ¿a qué debo esta atención, Monsieur Oficial? ¿Tiene algo que ver con el hecho de que estoy buscando a un hombre chino?";
				link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_1";
			}
			else
			{
				dialog.text = "Es bueno que hayas venido a nosotros por tu propia voluntad. Hemos tenido suficientes alborotadores últimamente.";
				link.l1 = "Bueno, como puedes ver, no soy uno de los violentos. Sin embargo... ¿por qué estoy aquí, oficial? Ya pregunté a tus hombres, pero no obtuve una respuesta, ¿es porque estoy buscando a un cierto hombre chino en la ciudad?";
				link.l1.go = "PZ_BasTer_ComendantDialog_1";
			}
			DeleteQuestCondition("PZ_BasTerPeshera");
			npchar.Dialog.Filename = "Common_Prison.c";
			npchar.Dialog.CurrentNode = "First_officer";
		break;
		// <-- Путеводная звезда
		case "Helen_meeting":
			dialog.text = "¡Por supuesto que no! Por favor, entra. Siempre eres bienvenido en nuestras mazmorras. Eh, lo digo en buen sentido, por supuesto. Entonces, ¿qué necesitas aquí?";
			link.l1 = "Oh, nada especial, solo paseando por la ciudad, así que llegué aquí de casualidad.";
			link.l1.go = "exit";
			link.l2 = "Quería hablar de algunos negocios.";
			link.l2.go = "quests";
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "Quiero entrar en la prisión.";
				link.l4.go = "ForGoodMove";		
			}
			NextDiag.TempNode = "First_officer";
		break;
	}
}

void GetChestPlaceName()
{
	string islandId;
	int iTemp = rand(3);
	switch (iTemp)
	{
		case 0: 
			pchar.questTemp.jailCanMove.islandId = "Bermudes";
			pchar.questTemp.jailCanMove.placeId = "Bermudes_Cavern";
		break;
		case 1: 
			pchar.questTemp.jailCanMove.islandId = "Caiman";
			pchar.questTemp.jailCanMove.placeId = "Caiman_Grot";
		break;
		case 2: 
			pchar.questTemp.jailCanMove.islandId = "Dominica";
			pchar.questTemp.jailCanMove.placeId = "Dominica_Grot";
		break;
		case 3: 
			pchar.questTemp.jailCanMove.islandId = "Terks";
			pchar.questTemp.jailCanMove.placeId = "Terks_Grot";
		break;
	}
}

string GetBanderLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест мэра по поиску шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[rand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GenQuestPrison_GenerateArtefact() // артефакты
{
	string itemID;
	switch(rand(7))
	{
		case 0:
			itemID = "indian_5";
		break;
		case 1:
			itemID = "indian_7"; 
		break;
		case 2:
			itemID = "indian_8"; 
		break;
		case 3:
			itemID = "indian_9"; 
		break;
		case 4:
			itemID = "indian_10"; 
		break;
		case 5:
			itemID = "indian_11"; 
		break;
		case 6:
			itemID = "indian_3"; 
		break;
		case 7:
			itemID = "indian_6"; 
		break;
	}
	return itemID;
}

string GenQuestPrison_GenerateBlade() // клинки и другое
{
	string itemID;
	switch(rand(8))
	{
		case 0:
			itemID = GetGeneratedItem("blade_16");
		break;
		case 1:
			itemID = GetGeneratedItem("blade_15"); 
		break;
		case 2:
			itemID = GetGeneratedItem("blade_13"); 
		break;
		case 3:
			itemID = "cirass2"; 
		break;
		case 4:
			itemID = GetGeneratedItem("blade_10"); 
		break;
		case 5:
			itemID = "spyglass3"; 
		break;
		case 6:
			itemID = "cirass6"; 
		break;
		case 7:
			itemID = "cirass7"; 
		break;
		case 8:
			itemID = "cirass1"; 
		break;	
		
	}
	return itemID;
}
