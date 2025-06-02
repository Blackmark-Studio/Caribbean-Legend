// Тичингиту - индеец-офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

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
		case "First time":
			dialog.text = "¿Qué quieres?";
			link.l1 = "Nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "¿Qué quieres, cara pálida? Tichingitu no tiene nada que decirte.";
			link.l1 = "¿Tu nombre es Tichingitu? Hm. Escucha, guerrero, no he venido aquí para mirarte. He venido a hacerte una pregunta: ¿Por qué te metiste en la casa de ese hombre gordo?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "";
			link.l1 = "¿No dices nada? No es inteligente. Serás colgado por robo y todo lo demás que has hecho. Dime por qué cometiste tal acto y tal vez pueda ayudarte.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Tichingitu viene a la ciudad de los rostros pálidos a través de muchos, muchos caminos, a través de grandes aguas, desde grandes bosques y pantanos. Tichingitu está cansado y quiere comer. Tichingitu muere de hambre. Nadie quiere ayudar a Tichingitu. Ellos gritan, 'Vete, perro de piel roja'. El dueño de la taberna expulsa al indio como a un perro sarnoso. Tichingitu quiere comer.";
			link.l1 = "¡Maldita sea!, ¿pero por qué viniste a este asentamiento desde... tu bosque?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Tichingitu expulsado de la tribu nativa. Tichingitu se pelea con el chamán de la tribu, chamán le cuenta al jefe, chamán maldice a Tichingitu, Tichingitu deja la tribu, muy, muy lejos de la tierra nativa. Tichingitu sin hogar, sin arma, sin nada.";
			link.l1 = "Eso es lo que llamo una desgracia. ¿Por qué te peleaste con los tuyos?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Chamán de la tribu malvado hombre. Él dice que espíritu maligno se asentó en cuerpo de esposa. Esposa debe morir. Mi esposa solo está enferma, ningún espíritu asentado. Tichingitu trata esposa, chamán mata esposa. Tichingitu se opone al chamán, todos se oponen a Tichingitu, Tichingitu se va.";
			link.l1 = "¿Intentaste salvar a tu esposa? ¿Por eso te echaron del pueblo?";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Sí, cara pálida. Tichingitu no tiene elección. O roba o muere de hambre...";
			link.l1 = "Bueno, digo yo... Una soga por unas pocas monedas miserables robadas por un hombre hambriento... Tichingitu, intentaré ayudarte. Conozco a Fadey, ese hombre fornido en cuya casa te colaste. Tal vez pueda hacer algo... Iré a hablar con el comandante.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
			pchar.questTemp.Sharlie.Tichingitu = "commandante";
			AddLandQuestMark(characterFromId("BasterJailOff"), "questmarkmain");
			AddQuestRecord("Tichingitu", "2");
		break;
		
		case "Tichingitu_wait":
			dialog.text = "Tichingitu espera. Indio no teme a la muerte. Chamán maldice a Tichingitu, Tichingitu debe morir.";
			link.l1 = "No todo está perdido todavía. Intentaré ayudar...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			dialog.text = "Tichingitu espera. Indio no teme a la muerte. Chamán maldecir Tichingitu, Tichingitu debe morir.";
			link.l1 = "No hay necesidad de ser pesimista. Tu encarcelamiento ha llegado a su fin. He ayudado a liberarte.";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			dialog.text = "¿Broma de cara pálida? ¿Tichingitu libre?";
			link.l1 = "No, no estoy bromeando. Están a punto de abrir tu celda y dejarte salir. Sígueme, te sacaré de la cárcel.";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			DialogExit();
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			DoQuestReloadToLocation("BasTer_exittown", "rld", "aloc9", "TichingituFree"); // 170712
			pchar.quest.FreeTichingituOver.over = "yes"; //снять таймер
			if (GetHour() > 17.0)
			{
				WaitDate("", 0, 0, 0, 13, 0);
				RecalculateJumpTable();
				RefreshWeather();
				RefreshLandTime();
			}
			if (GetHour() < 8.0)
			{
				WaitDate("", 0, 0, 0, 7, 0);
				RecalculateJumpTable();
				RefreshWeather();
				RefreshLandTime();
			}
		break;
		
		case "Tichingitu_9":
			dialog.text = "";
			link.l1 = "Ahí estás, libre de nuevo. Adelante, Tichingitu, asegúrate de no robar nada más y no te metas en más problemas. Será mejor que encuentres alguna aldea india y vivas con los tuyos, no creo que estén en contra de aceptarte.";
			link.l1.go = "Tichingitu_10";
		break;
		
		case "Tichingitu_10":
			dialog.text = "Tichingitu no ir. Amo salvar la vida de Tichingitu. Tichingitu quedarse. La vida de Tichingitu pertenece al amo.";
			link.l1 = "¿Eh? ¿De qué estás hablando? ¿Qué maestro, qué vida? ¿No entiendes lo que te estoy diciendo? ¡Eres libre! ¡Vete!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "Indio tiene deuda, amo blanco. Tichingitu le sirve con fe y verdad. Tichingitu sabe cómo luchar. Tichingitu muere en batalla por amo. Él se queda.";
			link.l1 = "¡Oh Señor! Maldición... ¿Qué clase de amo soy para ti, Tichingitu? Te ayudé para no convertirte en esclavo.";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu no esclavo. Tichingitu indio libre. Tichingitu quiere servirle. Tichingitu sabe cómo luchar, cualquier perro muere antes de acercarse al amo. Tichingitu sabe cómo limpiar y cargar mosquete. Tichingitu puede disparar mosquete.";
			link.l1 = "Aunque... Sabes, Tichingitu, esa no es una mala idea. Necesito gente leal y no pareces ser un mal hombre. Además, sabes cómo disparar un mosquete. ¿Y qué vas a hacer solo de todos modos? Terminarás robando otra cosa y la próxima vez definitivamente serás ahorcado... Está bien, puedes quedarte. Pero recuerda: la vida no va a ser tranquila conmigo.";
			link.l1.go = "Tichingitu_13";
			link.l2 = "Está bien, suficiente. Ve en paz, hermano de piel roja. ¡Que tus dioses te protejan!";
			link.l2.go = "Tichingitu_exit";
		break;
		
		case "Tichingitu_exit":
			DialogExit();
			AddQuestRecord("Tichingitu", "5");
			CloseQuestHeader("Tichingitu");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.Tichingitu");
			pchar.systeminfo.tutorial.Fighter = true;
		break;
		
		case "Tichingitu_13":
			dialog.text = "Tichingitu no tiene miedo de nada, amo blanco. Tichingitu se alegrará de servirte. Tichingitu fiel hasta el último aliento.";
			link.l1 = "Está bien. ¡Bienvenido a la tripulación, Tichingitu!";
			link.l1.go = "Tichingitu_hire";
		break;
		
		case "Tichingitu_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			LAi_SetImmortal(npchar, false);
			npchar.quest.OfficerPrice = sti(pchar.rank)*20;
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
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Tichingitu_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			DeleteAttribute(pchar, "questTemp.Sharlie.Tichingitu");
			pchar.OfficerAttRange = 35.0;
			
			AddQuestRecord("Tichingitu", "4");
			CloseQuestHeader("Tichingitu");
			// Sinistra - Начало квеста "Знакомство с индейцами"
			string sModel = "Miskito_"+(rand(5)+1);
			sld = GetCharacter(NPC_GenerateCharacter("ListKakao", sModel, "man", "man", 1, PIRATE, -1, false, "quest"));
			sld.name = "Cocoa";
			sld.lastname = "Leaf";
			GiveItem2Character(sld, "blade_01");
			EquipCharacterByItem(sld, "blade_01");
			AddItems(sld, "jewelry53", rand(20)+180);
			AddItems(sld, "cannabis1", 3);
			GiveItem2Character(sld, "indian_10");
			GiveItem2Character(sld, "talisman11");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_ListKakao";
			ChangeCharacterAddressGroup(sld, "BasTer_ExitTown", "item", "item3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			//LaunchTutorial("Fighter", 1);
		break;
		
	//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Tichingitu_officer":
			dialog.text = "Tichingitu te escucha, Capitán "+pchar.name+".";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Tichingitu, estoy a punto de partir hacia un antiguo pueblo indígena llamado Tayasal. No te mentiré, es un viaje extremadamente peligroso y muy inusual: a través de un ídolo de teletransportación. Tú... ¿Me acompañarás?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tichingitu, dame un informe completo del barco.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Quiero que compres ciertos bienes cada vez que estemos atracados.";
				Link.l12.go = "QMASTER_2";
			}

			Link.l1 = "¡Escucha mi orden!";
            Link.l1.go = "stay_follow";
			link.l2 = "Nada por el momento. ¡A sus órdenes!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "¿Informe del barco? Tichingitu no tiene informe, amo. Solo armas y ropa. Tichingitu no tomó informe de ningún lado.";
			Link.l1 = "Está bien, como sea.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Maestro, Tichingitu nunca pone un pie en una colonia sin usted. Cuando Tichingitu entra en una tienda, todos piensan que Tichingitu es un ladrón otra vez. Entonces, prisión.";
			link.l1 = "Sí, probablemente tienes razón. No otra vez esa cosa de prisión. Además, nadie jamás creerá que eres un pagador.";
			link.l1.go = "exit";
		break;
		
		case "stay_follow":
            dialog.Text = "¿Qué órdenes tienes?";
            Link.l1 = "¡Detente aquí!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "¡Sígueme y no te quedes atrás!";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Necesitas cambiar el tipo de munición para tu arma de fuego.";
					Link.l3.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Cambia el tipo de munición para tu mosquete.";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "Cambia tu arma prioritaria para el combate.";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "Quiero que mantengas distancia del objetivo.";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Elige el tipo de munición:";
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
			Dialog.Text = "Al comienzo de la pelea, usarás:";
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
            dialog.Text = "¡Cambio de plan!";
            Link.l1 = "A sus anchas.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "¡Cambio de plan!";
            Link.l1 = "A sus órdenes.";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "¿Qué tan lejos, Capitán? Dile a Tichingitu cuántas yardas, pero no más de veinte.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Capitán, perdona a Tichingitu pero yo no te entiendo.";
				link.l1 = "Lo siento, mi error...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Tichingitu permanece inactivo, no se mueve. ¿Eso es lo que quieres, capitán?";
				link.l1 = "Sí, precisamente así.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Tichingitu no puede quedarse a más de veinte yardas del objetivo. Entonces falla.";
				link.l1 = "Está bien, mantén la distancia a veinte yardas.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Tichingitu entiende todo. Tichingitu toma la posición que tú digas.";
			link.l1 = "Bien.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "La vida de Tichingitu hace mucho tiempo se convirtió en la vida de mi Capitán. El indio no olvida lo que el Capitán hizo por Tichingitu. Tichingitu lo seguirá a donde el Capitán diga, sin preguntas, sin vacilación.";
			link.l1 = "¡Gracias, mi amigo!";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "¿Cuándo partiremos?";
			link.l1 = "Un poco más tarde. Por ahora tendremos que prepararnos para el viaje.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "21");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Pagamos al hombre blanco cien doblones, nos vamos y completamos nuestro trabajo libremente.";
			link.l1 = "¿Y qué si nos atrapan de nuevo?";
			link.l1.go = "tonzag_jailed_1";
			locCameraFromToPos(-16.78, 1.88, -1.70, true, -5.00, -6.10, -20.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Pagamos mil doblones.";
			link.l1 = "Cínico pero muy agudo.";
			link.l1.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Guadalupe es peor.";
			link.l1 = "¿Cómo es eso?";
			link.l1.go = "tonzag_jailed_3";
		break;
		
		case "tonzag_jailed_3":
			dialog.text = "Allí, quieren colgar solo a Tichingitu. Aquí, quieren colgar a más de uno. No está tan mal.";
			link.l1 = "¡Ahora eso es puro cinismo!";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "Disparo a quemarropa. Capitán, el viejo es fuerte, podemos salvarlo si actuamos rápidamente.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
			AddDialogExitQuestFunction("Tonzag_JailFear");
		break;
		
		case "tonzag_dead":
			dialog.text = "El hombre blanco no conoce la misericordia. Muchos de los míos, Capitán. Tantos. Pero los tuyos más.";
			link.l1 = "¿Son ellos tu tribu?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "Algunos... algunos de los míos.";
			link.l1 = "Resiste, amigo.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
	// Тичингиту говорит о том, что нужно спасти Делюка
		case "Del_Deluck":
			dialog.text = "¿Más de cien doblones?";
			link.l1 = "¿Eh? ¿Estás preguntando si pagaré de nuevo por la liberación de Deluc de la prisión?";
			link.l1.go = "Del_Deluck_1";
		break;
		
		case "Del_Deluck_1":
			dialog.text = "Sí.";
			link.l1 = "No estoy seguro yo mismo... ¿Qué piensas tú?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "Deberíamos sacarlo de allí.";
			link.l1 = "Eso es honorable. Nunca dejes a los tuyos atrás, ¿eh?";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "O déjalo. Deja al débil frente a un jaguar en la selva.";
			link.l1 = "¿Quién?";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			dialog.text = "El gran gato.";
			link.l1 = "Tichingitu, estoy teniendo problemas para entenderte. Solo dime: ¿qué debo hacer en esta situación?";
			link.l1.go = "Del_Deluck_5";
		break;
		
		case "Del_Deluck_5":
			dialog.text = "Usa tu propia cabeza.";
			link.l1 = "¡Muy útil!";
			link.l1.go = "Del_Deluck_6";
		break;
		
		case "Del_Deluck_6":
			DialogExit();
			AddQuestRecord("FolkeDeluc", "2");
			Return_TichingituOfficer();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
