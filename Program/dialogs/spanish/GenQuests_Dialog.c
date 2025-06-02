void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ref rItem, rChar, sld, MerPrm;
	aref arTemp1, arTemp2;
	bool bTemp;
	int iBanditsCount, i, iMoney, iNation, iTmp, iGoods, iRank, iScl;
	String sTitle, sGroup, sTemp, sText; // belamour 
	float locx, locy, locz;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Esto es un error. Contacta con los desarrolladores e infórmales sobre cómo y dónde lo encontraste";
					link.l1 = RandSwear()+"¡Les haré saber!";
					link.l1.go = "exit";
					
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Soldier_")) // Солдеры по квесту "встреча в бухте"
			{
				dialog.text = "No estoy autorizado para tratar contigo. Habla con nuestro oficial.";
					link.l1 = LinkRandPhrase("Por supuesto...","Entiendo.","¡Ciertamente!");
					link.l1.go = "exit";
				break;
			}
			
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Officer_")) // Офицер по квесту "встреча в бухте"
			{
				dialog.text = "¡Preséntate! ¡Quiero saber con quién estoy hablando!";
					link.l1 = "Mi nombre es "+GetFullName(PChar)+"¿Qué está pasando aquí?";
					link.l1.go = "ContraMeetManQuest_Sold_1";
				break;
			}
					
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && PChar.location == PChar.GenQuest.ContraMeetMan.ShoreID) // Квестовый чел по генеру "meeting in the cove" 
			{
				dialog.text = "Capitán, tu nombre es "+GetFullName(PChar)+", ¿no es así?";
					link.l1 = "Sí, tienes razón.";
					link.l1.go = "ContraMeetManQuest_1";
					link.l2 = "No. Me has confundido con otro.";
					link.l2.go = "exit";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && CheckAttribute(PChar, "GenQuest.ContraMeetMan.ContraIsDead")) // В комнате таверны после убицства контриков
			{
				LAi_LocationFightDisable(LoadedLocation, false);
				dialog.text = PChar.name+", ¡muchísimas gracias! Si no fueras tú, mi destino sería poco envidiable... ¿Cómo puedo agradecerte?";
					link.l1 = "No necesito nada...";
					link.l1.go = "ContraMeetManQuest_7";
					link.l2 = "No rechazaría una pequeña recompensa.";
					link.l2.go = "ContraMeetManQuest_8";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_Contrick_0") // Контрик в комнате по квесту "встреча в бухте"
			{
				iMoney = (rand(3)+2)*500;
				PChar.GenQuest.ContraMeetMan.Money = iMoney;
				if(!CheckAttribute(PChar, "GenQuest.ContraMeetMan.ManIsTraitor")) // Просто платят деньги
				{
					dialog.text = "...Hmm, ese es él, en efecto... Gracias, "+GetSexPhrase("compañero","moza")+", sin tu ayuda lo habríamos pasado mal, no hay forma de que salgamos del pueblo. Aquí, toma "+FindRussianMoneyString(iMoney)+" y puedes perderte. Y tendremos una 'charla' con nuestro amigo...";
						link.l1 = "...";
						link.l1.go = "ContraMeetManQuest_3";
				}
				else
				{
					dialog.text = "...Hmm, ese es él, en efecto... Gracias, "+GetSexPhrase("compañero","moza")+",  sin tu ayuda habríamos pasado un mal rato, no hay manera de que salgamos del pueblo. Aquí, toma "+FindRussianMoneyString(iMoney)+" y puedes perderte. ¡Destriparemos a este sucio traidor ahora!";
						link.l1 = "Por supuesto. Hasta que nos encontremos de nuevo, caballeros...";
						link.l1.go = "ContraMeetManQuest_4";
						link.l2 = "¿¡Qué?! No, no permitiré que asesines a un hombre, sin importar quién sea... ¡Y no necesito tu maldito dinero!";
						link.l2.go = "ContraMeetManQuest_5";
				}
					break;
			}
			
			if(NPChar.id == "ContraDeliverQuest_Soldier_0") // Солдер в комнате
			{
				dialog.text = "Entonces... ¿Qué tenemos aquí? ¿¡Piratas!? Tendrán que venir con nosotros a la oficina del comandante para una investigación...";
					link.l1 = "¡No somos piratas en absoluto! ¡Ni siquiera conozco a este hombre! ¡Él acaba de alquilar y mudarse a esta habitación y no tuve tiempo de empacar mis pertenencias y salir!";
					link.l1.go = "ContraDeliverQuest_Sold1";
					break;
			}
				
			if(CheckAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom") && NPChar.id == "ContraDeliverQuest_Contra_1")
			{
				dialog.text = "¿Entonces qué decías? ¿Tienes un mensaje para mí?! ¡Estoy esperando!";
					link.l1 = "Aquí tienes...";
					link.l1.go = "ContraDeliverQuest_1";
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom");
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.GoToTavern");
					break;
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "¡Eh, tú! Sí, tú. Veo que eres un hombre decente y adinerado.";
					link.l1 = "No puedo decir lo mismo de ti.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_1";
					break;
			}
					
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.WayOfShortVariant") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "¡Espera! ¡Oye, "+GetSexPhrase("compañero","moza")+", ¡muéstranos cuán pesada es tu bolsa!";
					link.l1 = "Entonces, ¿ya has despilfarrado todo el dinero de la iglesia?";
					link.l1.go = "Church_GenQuest_2_1";
					break;
			}
			
			if(NPChar.id == "ReasonToFast_Hunter")
			{
				if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > sti(pchar.questTemp.ReasonToFast.p2))
				{
					dialog.text = "¡Eh, en el bote! Hic... Despeja la vía, necesito hablar con los muchachos...";
					link.l1 = "¿No estás un poco mareado, amigo? Ve a dormirlo.";
					link.l1.go = "ReasonToFast_Hunter1";
				}
				else
				{
					dialog.text = "¡Oye, capitán! ¡Larga el ancla!";
					link.l1 = "¿Y por qué demonios debería yo....?";
					link.l1.go = "ReasonToFast_Hunter2";
				}
				link.l2 = "¿No eres un poco demasiado grosero?";
				link.l2.go = "ReasonToFast_Hunter3";	
			}
			
			if(NPChar.id == "PirateOnUninhabited_0")
			{
				dialog.text = RandPhraseSimple("¡Salve a ti! ¡Finalmente, el Señor ha escuchado nuestras plegarias y ha enviado a un gallardo capitán a esta costa abandonada!","¡Gracias a la Providencia! ¡Ahora los carroñeros locales no se alimentarán de nuestros huesos podridos!");
				link.l1 = "Hola, buen hombre, soy el capitán "+GetFullName(PChar)+"Veo que estás bastante en un lío aquí.";
				link.l1.go = "PiratesOnUninhabited_3";
				link.l2 = "Hombre bueno, tengo mis propios asuntos que atender y no tengo tiempo que perder en tus problemas.";
				link.l2.go = "PiratesOnUninhabited_1";
			}
			
			if(NPChar.id == "ShipWreck_0")
			{
				dialog.text = RandPhraseSimple("¡Oh, capitán! ¡Es una buena fortuna que Dios te haya enviado un viento favorable y te haya guiado a este lugar desierto!","¡Capitán! ¡Gracias a la Providencia que decidió echar el ancla en esta costa desierta!");
				link.l1 = "Hola, buen hombre, soy el capitán "+GetFullName(pchar)+"Veo que estás en serios problemas aquí.";	
				link.l1.go = "ShipWreck_2";
				link.l2 = "Hombre bueno, tengo mis propios asuntos que atender y no tengo tiempo que perder en tus problemas.";
				link.l2.go = "ShipWreck_1";
			}
			
			if(NPChar.id == "Convict_0")
			{
				dialog.text = LinkRandPhrase("Espera, "+GetAddress_Form(pchar)+"¡Nos concederías un minuto de tu precioso tiempo?","¿Perdería un noble?"+GetSexPhrase("ter","s")+" ¿escuchar la humilde petición de estos hombres indignos?","Noble mis"+GetSexPhrase("ter","s")+", por favor, conceded un poco de vuestro valioso tiempo para hablar con el desdichado.");
				link.l1 = LinkRandPhrase("No tengo tiempo para esto.","¡Piérdete, tengo mucho que hacer sin ti!","Déjame en paz, no tengo tiempo para ti.");
				link.l1.go = "Convict_0End";
				link.l2 = LinkRandPhrase("¿Qué quieres?","¿Qué necesitas?","¿Cuál es el problema?");
				link.l2.go = "Convict_Begin";
			}
			
			// Warship, 15.05.11. Генер "Justice for sale".
			if(HasSubStr(NPChar.id, "JusticeOnSale_Jungle_"))
			{
				dialog.text = "¡Hola, capitán! ¿Está interesado en baratijas indias y mercancías que no se pueden comprar en las tiendas ordinarias? ¿O quizás en efectivo?";
					link.l1 = "Truhanes como tú suelen exigir, no ofrecer nada. ¿Por qué eres tan extrañamente cortés?";
					link.l1.go = "JusticeOnSale_1";
					link.l2 = "¡Mi pistola suele hablar con los bastardos como tú!";
					link.l2.go = "JusticeOnSale_2";
			}
		break;
		
		// Генератор "Situation in the hold - Ransom"
		case "Hold_GenQuest1":
			pchar.quest.Hold_GenQuest_FindCharTimeIsOver.over = "yes";
			dialog.text = "Te escucho, capitán. ¿Estás aquí por negocios?";
			link.l1 = "Estoy buscando al señor "+pchar.GenQuest.Hold_GenQuest.Name+".";
			link.l1.go = "Hold_GenQuest2";
		break;
		
		case "Hold_GenQuest2":
			dialog.text = RandPhraseSimple("Yo soy "+pchar.GenQuest.Hold_GenQuest.Name+". ¿A quién le debo el honor?","Lo has encontrado. ¿Qué puedo hacer por ti?");
			link.l1 = "Soy capitán "+GetFullName(pchar)+", quería hablar contigo sobre "+pchar.GenQuest.Hold_GenQuest.CapName+".";
			link.l1.go = "Hold_GenQuest3";
		break;
		
		case "Hold_GenQuest3":
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			pchar.GenQuest.Hold_GenQuest.RansomSum = makeint(3 * sti(sld.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(sld, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500); 
						
			switch(hrand(3))
			{
				case 0:
					dialog.text = "¿Y quién es?";
					link.l1 = "Espera... ¿Tú eres "+pchar.GenQuest.Hold_GenQuest.Name+", y no sabes sobre "+pchar.GenQuest.Hold_GenQuest.CapName+"?";
					link.l1.go = "Hold_GenQuest40";
				break;
				case 1:
					dialog.text = "¡Vaya! ¿Hace bastante tiempo que oí hablar de ese viejo zorro? ¿Qué le ha pasado esta vez?";
					link.l1 = "Esta vez está en serios problemas... Lo tienen cautivo y necesita tu ayuda.";
					link.l1.go = "Hold_GenQuest50";
				break;
				case 2:
					dialog.text = "Está bien, soy todo oídos.";
					link.l1 = "Su nave fue atacada por los piratas, y ahora está cautivo. Me aconsejó que lo viera a usted respecto al rescate.";
					link.l1.go = "Hold_GenQuest60";
				break;
				case 3:
					dialog.text = "Sí, me alegra escuchar sobre un viejo amigo. ¿Cómo le va?";
					link.l1 = "Su situación es tan desesperada que es difícil siquiera imaginarla.";
					link.l1.go = "Hold_GenQuest70";
				break;				
			}	
		break;
		
		case "Hold_GenQuest40":
			// dialog.text = "¡De hecho, soy "+pchar.GenQuest.Hold_GenQuest.Name+"! ¿Pero por qué debería saber algo sobre ese "+pchar.GenQuest.Hold_GenQuest.CapName+"?";
			dialog.text = "Así es, yo soy "+pchar.GenQuest.Hold_GenQuest.Name+"¡Pero nombre "+pchar.GenQuest.Hold_GenQuest.CapName+" no me dice nada."; // belamour gen
			link.l1 = "Lo siento. Tal vez me equivoqué...";
			link.l1.go = "Hold_GenQuest41";
		break;
		
		case "Hold_GenQuest41":
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest50":
			dialog.text = "¡Caray! ¿Y cómo se supone que debo ayudarle? ¿Liberándolo matando a todos sus enemigos o qué? ¡Ja-ja-ja!";
			link.l1 = "No-no, eso no es necesario. Solo necesitas entregar "+pchar.GenQuest.Hold_GenQuest.RansomSum+"pesos como rescate.";
			link.l1.go = "Hold_GenQuest51";
		break;		
		
		case "Hold_GenQuest51":
			dialog.text = "¡Qué desfachatez! ¿Y por qué debería pagar un rescate por él? ¡No es ni mi pariente ni mi amigo!";
			link.l1 = "Hmm... Me dijo que eras su única esperanza. Y también mencionó alguna deuda tuya...";
			link.l1.go = "Hold_GenQuest52";
		break;		
		
		case "Hold_GenQuest52":
			dialog.text = LinkRandPhrase("¡Qué tipo tan insolente! Es él quien me debe dinero, para tu información. ¡Pero eso no es razón para que lo rescate con la esperanza de que pague ambas deudas!","¡Qué sinvergüenza! Me estafó cuando estábamos dividiendo nuestro negocio, ¡y ahora tiene el descaro de pedirme que pague su rescate!","¡Vaya sorpresa! ¿Por qué debería pagar un rescate por él? No somos tan cercanos.");
			link.l1 = "Entonces, ¿puedo decirle que te negaste a pagar su rescate y no reconociste tu deuda?";	
			link.l1.go = "Hold_GenQuest53";
		break;
		
		case "Hold_GenQuest53":
			dialog.text = "¡Dios mío! ¿De qué deuda estás hablando? ¡Ya te he explicado todo! Y si no tienes más preguntas además de esta historia tonta, entonces permíteme retirarme.";
			link.l1 = "Ya veo. Bueno, no tengo más preguntas para ti, pero tengo unas cuantas para ese compañero tuyo.";
			link.l1.go = "Hold_GenQuest54";
		break;
		
		case "Hold_GenQuest54":
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar)); // НПС вешать собрались? )))
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen				
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest60":
			dialog.text = "Hmm... Y tú, según entiendo, eres quien lo tiene... Bueno, supongo que lo ayudaré. ";
			link.l1 = "Muy bien. El rescate será "+pchar.GenQuest.Hold_GenQuest.RansomSum+" pesos.";
			link.l1.go = "Hold_GenQuest61";
		break;
		
		case "Hold_GenQuest61":
			dialog.text = "Me malinterpretaste: soy miembro del consejo de la ciudad. Vigilamos el cumplimiento de la carta.\n"+"¡Guardias! ¡Guardias! ¡Arréstenlo bajo sospecha de tráfico de esclavos y saqueo de barcos de "+NationNameGenitive(sti(pchar.GenQuest.Hold_GenQuest.Nation))+"!";
			link.l1 = "Bueno, 'compañero', solo déjame llegar a ti...";
			link.l1.go = "Hold_GenQuest62";
		break;
		
		case "Hold_GenQuest62":
			LAi_SetImmortal(NPChar, false);
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen	
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_SetWarriorTypeNoGroup(NPChar);
   	        LAi_warrior_DialogEnable(NPChar, false);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");			
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheckFunction("TmpEnemy", "Hold_GenQuest_AfterBattle");
			chrDisableReloadToLocation = true; 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);  
			AddDialogExitQuest("MainHeroFightModeOn"); 
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
			DialogExit();
		break;
		
		case "Hold_GenQuest70":
			dialog.text = "¿Qué estás diciendo?! ¿Y cómo puedo ayudarle?";
			link.l1 = "Está cautivo y me pidió que hablara contigo acerca de su rescate.";
			link.l1.go = "Hold_GenQuest71";
		break;		
		
		case "Hold_GenQuest71":
			dialog.text = "Por supuesto, por supuesto. Haré todo lo que pueda. ¿Dónde los tienen? ¿Y cuál es la cantidad del rescate?";
			link.l1 = "Los piratas exigen "+pchar.GenQuest.Hold_GenQuest.RansomSum+" pesos. Debo entregar el dinero al puerto, y entonces tu amigo será liberado.";
			link.l1.go = "Hold_GenQuest72";
		break;
		
		case "Hold_GenQuest72":
			dialog.text = "Aquí está el dinero. Afortunadamente, tenía suficiente conmigo.";
			link.l1 = "Sí, eso es afortunado, de verdad. Ve al puerto, entonces, y pronto volverás a ver a tu compañero.";
			link.l1.go = "Hold_GenQuest73";
		break;
		
		case "Hold_GenQuest73":
			addMoneyToCharacter(pchar, sti(pchar.GenQuest.Hold_GenQuest.RansomSum));
			AddQuestRecord("HoldQuest", "11");
			AddQuestUserData("HoldQuest", "sNameChar", GetFullName(NPChar)); // belamour gen 
			AddQuestUserData("HoldQuest", "sName", NPChar.Hold_GenQuest.Name); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.RansomSum);
			pchar.GenQuest.Hold_GenQuest = "prisoner_ransom";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;				
		// Генератор "Situation in the hold - Ransom"
		
		// Генератор "Situation in the hold - Partner in crime"
		case "Hold_GenQuest80":
			dialog.text = "Hola, capitán, lamento no haber tenido el honor de presentarme. Dijeron que me estabas buscando.";
			link.l1 = "En efecto, si usted es señor "+pchar.GenQuest.Hold_GenQuest.Name+". Soy capitán "+GetFullName(pchar)+", quería hablar contigo.";
			link.l1.go = "Hold_GenQuest81";
		break;
		
		case "Hold_GenQuest81":
			dialog.text = "¿Y qué tipo de negocio es ese, capitán "+GetFullName(pchar)+"?";
			link.l1 = "He oído que posees algo de lo que no te importaría desprenderte.";
			link.l1.go = "Hold_GenQuest82";
		break;
		
		case "Hold_GenQuest82":
			dialog.text = "¿Qué es exactamente lo que insinúas?";
			link.l1 = "No seas tan terco, buen hombre, sé muy bien sobre tu turbio pasado, y sobre un mapa improvisado, en el cual está la ubicación del tesoro"+GetName(NAMETYPE_VIP,pchar.GenQuest.Hold_GenQuest.PirateName,NAME_ACC)+" está indicado.";
			link.l1.go = "Hold_GenQuest83";
		break;
		
		case "Hold_GenQuest83":
			dialog.text = "¡Maldita sea! Siempre supe que ese canalla"+pchar.GenQuest.Hold_GenQuest.CapName+" ¡lo contaría tarde o temprano! ¿En qué estaba pensando cuando le ofrecí este trato?";
			link.l1 = "Deja de quejarte ya. No tengo malas intenciones... Solo véndeme este mapa y lleva la vida a la que estás acostumbrado.";
			link.l1.go = "Hold_GenQuest84";
		break;
		
		case "Hold_GenQuest84":
			dialog.text = "Si tan solo pudiera estar tan seguro de eso... ¿Y cuánto me vas a ofrecer por ello? Seguramente debes saber que había mucho oro en el cofre. Lo llevaban cuatro hombres, que el Señor descanse sus almas...";
			link.l1 = "Pero "+GetName(NAMETYPE_VIP,pchar.GenQuest.Hold_GenQuest.PirateName,NAME_NOM)+" ya podría haber reclamado su tesoro...";
			link.l1.go = "Hold_GenQuest85";
		break;
		
		case "Hold_GenQuest85":
			dialog.text = "Eso también es cierto... Está bien, estoy dispuesto a vendértelo por "+pchar.GenQuest.Hold_GenQuest.Sum+"pesos. De todos modos, no me atreveré a perturbar a los muertos.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Hold_GenQuest.Sum) && !CheckCharacterItem(pchar,"mapQuest") && !CheckCharacterItem(pchar,"map_full"))
			{
				link.l1 = "De acuerdo. Tienes un trato.";
				link.l1.go = "Hold_GenQuest86";
			}	
			link.l2 = "No, buen hombre, ese pedazo de papel no vale este dinero. Adiós...";
			link.l2.go = "Hold_GenQuest87";
			pchar.quest.Hold_GenQuest_GetMapTimeIsOver.over = "yes";
		break;
		
		case "Hold_GenQuest86":		
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Hold_GenQuest.Sum));
			GiveItem2Character(pchar, "mapQuest"); 
			rItem = ItemsFromID("mapQuest");
			Hold_GenQuest_GenerateTreasureMap(rItem);
			AddQuestRecord("HoldQuest", "15");
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);						
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;	
		
		case "Hold_GenQuest87":
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			AddQuestRecord("HoldQuest", "16");
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_GEN)); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);			
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");				
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		// Генератор "Situation in the hold - Partner in crime"
		
		// Генератор "Shipwrecked"
		case "ShipWreck_1":
			dialog.text = "¿Cómo puede ser esto posible, capitán?! Dios nunca te perdonará tal pecado.";
			link.l1 = "Depende de Él decidir.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
		
		case "ShipWreck_2":
			pchar.GenQuest.ShipWreck.StartShipType = PiratesOnUninhabited_GenerateShipType(); 		
			pchar.GenQuest.ShipWreck.ShipTypeName = GenerateRandomNameToShip(sti(pchar.GenQuest.ShipWreck.Nation));			
			
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("Hola, soy "+pchar.GenQuest.ShipWreck.Name+", capitán del "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Acc"))+ " '"+pchar.GenQuest.ShipWreck.ShipTypeName+", mi barco se estrelló en los arrecifes no lejos de la costa."+"Solo unos pocos marineros de toda la tripulación lograron sobrevivir. La marea nos ha arrastrado a esta costa desolada. Habíamos estado muriendo de hambre y sed durante "+(5+hRand(7))+"semanas por ahora","Hola, soy "+pchar.GenQuest.ShipWreck.Name+", capitán del "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Gen"))+" '"+pchar.GenQuest.ShipWreck.ShipTypeName+". Nuestro barco naufragó no lejos de aquí."+"Logramos llegar a esta costa en los naufragios, pero este lugar parece deshabitado. Nos vimos obligados a sobrevivir con mariscos y frutas de palma durante "+(5+hRand(7))+" semanas ya.");
				link.l1 = RandPhraseSimple("¿Y cuántos de ustedes quedan?","¿Y cuántos de vosotros lograron sobrevivir?");
				link.l1.go = "ShipWreck_3";
			}
			else
			{						
				pchar.GenQuest.ShipWreck.Mutiny = "true"; // belamour gen кавычки
				pchar.GenQuest.ShipWreck.BadName = GenerateRandomName_Generator(sti(pchar.GenQuest.ShipWreck.Nation), "man");
				pchar.GenQuest.ShipWreck.City = GetQuestNationsCity(sti(pchar.GenQuest.ShipWreck.Nation));
				dialog.text = "Oh, capitán, nuestras bajas son realmente terribles... Hola, soy "+pchar.GenQuest.ShipWreck.Name+", capitán y propietario de "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Gen"))+" ' "+pchar.GenQuest.ShipWreck.ShipTypeName+". O, debería decir, ex capitán y propietario. "+"Este bastardo "+pchar.GenQuest.ShipWreck.BadName+" a quien contraté en "+XI_ConvertString("Colony"+pchar.GenQuest.ShipWreck.City+"Voc")+" había provocado un motín en mi tripulación. Al final, nos dejaron en este lugar perdido. Sucedió "+(5+hRand(7))+" hace semanas.";
				link.l1 = "¿Y luego qué? ¿Toda tu tripulación se unió a los amotinados?";
				link.l1.go = "ShipWreck_4";			
			}
		break;
		
		case "ShipWreck_3":
			dialog.text = RandPhraseSimple("De toda la tripulación, solo "+ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty))+" sobrevivieron. El resto murió, algunos de ellos estando ya aquí por heridas y fiebre",
				"Solo " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + " han tenido suerte. Otros han encontrado su fin... ya sea en las profundidades o en las dunas de esta costa.");
			link.l1 = LinkRandPhrase("Sí, ese es un destino poco envidiable. Pero tal es la suerte del marinero, cualquiera podría terminar en tu lugar.","Ya veo... Dios tiene cada vida en sus manos, solo que está demasiado ocupado para recordar a todos.","En efecto. El hombre propone, pero Dios dispone.");
			link.l1.go = "ShipWreck_5";	
		break;
		
		case "ShipWreck_4":
			dialog.text = "¡Por supuesto que no! Aquellos que se negaron a unirse a los amotinados fueron muchos, pero esos villanos capturaron el arsenal, y es bueno que no opusimos resistencia, o nos habrían matado sin piedad. Muchos ya han sucumbido aquí a la fiebre y al veneno de insectos ponzoñosos, solo "+ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty))+" sobrevivimos. Gracias a Dios, nuestras tribulaciones finalmente han terminado.";
			link.l1 = RandPhraseSimple("Sí, eso seguramente fue un golpe de mala suerte.","Oh, bueno, muchas cosas extrañas pueden suceder en estos lugares olvidados por Dios.");
			link.l1.go = "ShipWreck_5";			
			link.l2 = "Espera, amigo. ¿Y cómo voy a saber que no te dejaron en tierra como instigadores de un motín?";
			link.l2.go = "ShipWreck_6";			
		break;
		
		case "ShipWreck_5":
			dialog.text = RandPhraseSimple("Capitán, espero que tenga varios camarotes libres en su barco. Todos nosotros tenemos familias, y probablemente están lamentando nuestra pérdida mientras hablamos. Le estaríamos muy agradecidos.","Capitán, estamos totalmente desesperados, eres nuestra única esperanza. Por favor, no nos niegues tu ayuda, llévanos de esta tierra olvidada por Dios.");
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l1 = "Ohh... ¿y adónde querrías que te lleve?";
				link.l1.go = "ShipWreck_7";			
			}
			link.l2 = RandPhraseSimple(RandPhraseSimple("Lamento mucho, pero no hay ni una sola hamaca libre, y mucho menos las cabinas. Los marineros están durmiendo en cubierta, ni siquiera pueden descansar bien después de una guardia...","Realmente odiaría decepcionarte, pero el barco está sobrecargado y la gente tiene que dormir con mal tiempo. Si hubiera un brote de enfermedad, perdería a la mitad de la tripulación."),RandPhraseSimple("Lamento mucho, pero no hay absolutamente ningún espacio libre para la tripulación en mi barco. No puedo llevar a bordo a más pasajeros.","Tengo que decepcionarte, pero mi barco está sobrecargado. Temo a la epidemia."));
			link.l2.go = "ShipWreck_8";	
			if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "Eres un marinero experimentado y deberías saber que la presencia de alguien que ha sufrido un naufragio es muy mal presagio. Mis marineros simplemente os lanzarán a todos por la borda.";
				link.l3.go = "ShipWreck_9";
			}
		break;
		
		case "ShipWreck_6":
			dialog.text = "¿Qué estás diciendo, "+GetAddress_Form(npchar)+" "+pchar.lastname+"? ¿No tienes corazón? ¡Soy un comerciante, bien conocido en el Caribe! Bueno... Supongo que solía ser uno. Ahora no, sin barco ni dinero...";
			link.l1 = "¿Cómo es eso...? Apuesto a que ustedes fueron los verdaderos instigadores del motín, y ahora obtuvieron lo que merecían.";
			link.l1.go = "ShipWreck_18";
			if(GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "Pero qué bribón es ese "+pchar.GenQuest.ShipWreck.BadName+". ¡¿Realmente vas a dejar que se salga con la suya y someterte a este destino?!";
				link.l2.go = "ShipWreck_19";
			}	
		break;		
		
		case "ShipWreck_7":
			if(rand(1) == 0)
			{
				if(rand(100) < 90)
				{
					pchar.GenQuest.ShipWreck.variant = "1";
					dialog.text = "A cualquier asentamiento de "+NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation))+".";
					link.l1 = "Bueno, tengo suficientes taquillas y hamacas libres. Súbete al bote.";
					link.l1.go = "ShipWreck_10";
					link.l2 = "Hmm... Tenemos batallas por delante, y no sé dónde estarás más seguro, a bordo de mi barco o en esta acogedora cala.";
					link.l2.go = "ShipWreck_11";
				}
				else
				{				
					dialog.text = "¡A Dunkerque! Mi madre vive allí...";
					link.l1 = "¿Estás loco o qué?! Me imagino que recibiste demasiados golpes en la cabeza...";
					link.l1.go = "ShipWreck_12";					
					pchar.GenQuest.ShipWreck.Crazy = true; // получите психа на борт :-)
					
				}				
			}
			else
			{
				pchar.GenQuest.ShipWreck.variant = "2";
				dialog.text = "Donde quieras, realmente no nos importa. No tenemos nada con qué pagarte, de todos modos...";
				link.l1 = "Bueno, tengo suficientes cofres libres y hamacas. Súbete al barco.";
				link.l1.go = "ShipWreck_10_1";
				link.l2 = "Hmm... Tenemos batallas por delante, y no sé dónde estarás más seguro, a bordo de mi barco o en esta acogedora cala.";
				link.l2.go = "ShipWreck_11";		
			}						
		break;		

		case "ShipWreck_8":
			pchar.GenQuest.ShipWreck.FoodQty = sti(pchar.GenQuest.ShipWreck.Qty) * 10 + rand(10);
			pchar.GenQuest.ShipWreck.MedicamentQty = sti(pchar.GenQuest.ShipWreck.Qty) * 5 + rand(10);
			pchar.GenQuest.ShipWreck.AmunitionQty = sti(pchar.GenQuest.ShipWreck.Qty) * 3 + rand(5);
			pchar.GenQuest.ShipWreck.RumQty = sti(pchar.GenQuest.ShipWreck.Qty) * 7 + rand(10);
			if(GetFreeCrewQuantity(pchar) < sti(pchar.GenQuest.ShipWreck.Qty))
			{
				if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))
				{
					dialog.text = "¡Pero al rehusarte, ciertamente nos condenarás a la muerte! Bueno, intentaremos abrirnos camino hasta el barco, ¡aunque nos cueste la vida!";
					link.l1 = "¿Qué? Mírate, apenas te mantienes en pie...";
					link.l1.go = "ShipWreck_8_1";
					link.l2 = "Puedes intentar...";
					link.l2.go = "ShipWreck_16";
				}
				else
				{
					dialog.text = "¡Pero no puedes dejarnos aquí! ¡Sin tu ayuda, pronto pereceremos todos!";
					if(GetSquadronGoods(pchar, GOOD_WEAPON) < sti(pchar.GenQuest.ShipWreck.AmunitionQty) || GetSquadronGoods(pchar, GOOD_RUM) < sti(pchar.GenQuest.ShipWreck.RumQty))
					{			
						link.l1 = "Lo único que puedo hacer por ti es dejarte suficientes provisiones y medicinas y darte un bote. Al menos no vas a morir de hambre y sed. En cuanto a la navegación, no necesito enseñarte eso.";
						link.l1.go = "ShipWreck_8_2";
					}
					else
					{
						if(rand(1) == 0)
						{
							link.l1 = "Lo único que puedo hacer por ti es dejarte suficientes provisiones y medicinas y darte un bote. Al menos no vas a morir de hambre y sed. En cuanto a la navegación, no necesito enseñarte eso.";
							link.l1.go = "ShipWreck_8_2";
						}
						else
						{
							link.l1 = "Puedo dejarte suficiente medicina, municiones, ron y provisiones para un mes. Volveré yo mismo o enviaré a alguien por ti.";
							link.l1.go = "ShipWreck_8_4";
						}
					}
				}
			}
			else
			{
				if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL) // плохиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						dialog.text = "¡Pero al rehusarte, sin duda nos condenarás a la muerte! Bueno, intentaremos abrirnos paso hasta el barco, ¡aunque nos cueste la vida!";
						link.l1 = "¿Qué? Míraos, apenas os mantenéis en pie...";
						link.l1.go = "ShipWreck_8_1";
						link.l2 = "Puedes intentar...";
						link.l2.go = "ShipWreck_16";					
					}
					else
					{
						link.l1 = "Lo único que puedo hacer por ti es dejarte suficientes provisiones y medicinas y darte un bote. Al menos no moriréis de hambre y sed; en cuanto a la navegación, no necesito enseñaros nada.";
						link.l1.go = "ShipWreck_8_2";					
					}
				}
				else // кибальчиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						if(rand(1) == 0)
						{
							dialog.text = "¡Pero al rehusarte, sin duda nos condenarás a la muerte! Bueno, intentaremos abrirnos camino hacia el barco, ¡aunque nos cueste la vida!";
							link.l1 = "¿Qué? Mírense, apenas se mantienen en pie...";
							link.l1.go = "ShipWreck_8_1";
							link.l2 = "Puedes intentarlo...";
							link.l2.go = "ShipWreck_16";						
						}
						else
						{
							dialog.text = "¿Cómo pudiste hacernos esto?!.. ¡No solo has ignorado el Código del Mar, también has mancillado tu honor!";
							link.l1 = "¡Seguramente no eres tú quien debe hablar de mi honor, camarón!";
							link.l1.go = "ShipWreck_16";
						}	
					}
					else
					{
						link.l1 = "Lo único que puedo hacer por ti es dejarte suficientes provisiones y medicinas y darte un barco. Al menos no vas a morir de hambre y sed. En cuanto a la navegación, no necesito enseñarte eso.";
						link.l1.go = "ShipWreck_8_2";											
					}						
				}
			}			
		break;				
	
		case "ShipWreck_8_1":
			dialog.text = "Tienes razón, no tenemos ninguna oportunidad. Muy bien, que Dios sea tu juez, y que cada uno reciba lo que merece.";
			link.l1 = "Bueno, puedo encargarme de ello...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
	
		case "ShipWreck_8_2":
			dialog.text = "Bueno... Nos dejas sin opción... Rezaremos para que las tormentas y la sed no nos quiten la vida antes de llegar a lugares habitados...";
			link.l1 = "Adiós. Que el Señor vele por ti...";
			link.l1.go = "ShipWreck_8_3";
		break;
		
		case "ShipWreck_8_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 25);
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			Log_SetStringToLog("Has gastado " + pchar.GenQuest.ShipWreck.FoodQty + " unidades de provisiones.");
			Log_SetStringToLog("Has gastado " + pchar.GenQuest.ShipWreck.MedicamentQty + "unidades de medicina.");
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_7";
			NextDiag.CurrentNode = NextDiag.TempNode;			
		break;
	
		case "ShipWreck_8_4":	
			dialog.text = "Al parecer, no tenemos elección... Pero te lo ruego, capitán, por favor regresa tan pronto como puedas o envíanos una nave de expedición.";
			link.l1 = "Se me ocurrirá algo. Solo espera.";
			link.l1.go = "ShipWreck_8_5";
		break;
	
		case "ShipWreck_8_5":		
			pchar.quest.ShipWreck_LocationExit.over = "yes";
			AddCharacterExpToSkill(pchar, "Leadership", 50); 
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			RemoveCharacterGoods(pchar, GOOD_WEAPON, sti(pchar.GenQuest.ShipWreck.AmunitionQty));
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.GenQuest.ShipWreck.RumQty));			
			Log_SetStringToLog("Has gastado " + pchar.GenQuest.ShipWreck.FoodQty + " unidades de provisiones.");
			Log_SetStringToLog("Has gastado " + pchar.GenQuest.ShipWreck.MedicamentQty + "unidades de medicina.");		
			Log_SetStringToLog("Has gastado " + pchar.GenQuest.ShipWreck.AmunitionQty + " unidades de armas.");
			Log_SetStringToLog("Has gastado " + pchar.GenQuest.ShipWreck.RumQty + " unidades de ron");	
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "11");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);			
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "10");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_6";
			NextDiag.CurrentNode = NextDiag.TempNode;	
			pchar.GenQuest.ShipWreck = "SailorsOnShore";
			SetFunctionTimerCondition("ShipWreck_SaveSailors", 0, 0, 30, false);
			pchar.GenQuest.ShipWreck.Shore = pchar.location;
			SaveCurrentQuestDateParam("GenQuest.ShipWreck");
			SetFunctionLocationCondition("ShipWreck_MeetInShore", pchar.GenQuest.ShipWreck.Shore, true);
		break;
	
		case "ShipWreck_8_6":			
			dialog.text = RandPhraseSimple("Capitán, por favor recuerde que es nuestra única esperanza...","¿Por qué te demoras? Cada minuto que pasamos aquí es insoportable para nosotros...");
			link.l1 = "Haré todo lo que pueda. Adiós...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_6";		
		break;

		case "ShipWreck_8_7":			
			dialog.text = RandPhraseSimple("Adiós, capitán... Debemos prepararnos para el viaje.","Adiós... Y enciende las velas para salvar nuestras almas...");
			link.l1 = "Adiós. Que el Señor vele por ti...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_7";		
		break;
		
		case "ShipWreck_9":
			pchar.GenQuest.ShipWreck = "SailorsOnShoreFight"; // belamour gen
			dialog.text = "¿Cómo pudiste hacernos esto?! ¡No solo has ignorado el Código del Mar, sino que también has mancillado tu honor!";
			link.l1 = "¡Seguramente no eres tú quien debe hablar de mi honor, renacuajo!";
			link.l1.go = "ShipWreck_16";
		break;					
		
		case "ShipWreck_10":
			dialog.text = "¡Gracias, capitán! La carga no debería llevar mucho tiempo. ¡Dios, cuánto habíamos rezado para que llegara ese momento!";
			link.l1 = "Eso es estupendo. Espero que tus pruebas terminen pronto.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Nation_City";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.nation = sti(pchar.GenQuest.ShipWreck.Nation);
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "2");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "1");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				// <-- belamour
			}
			
		break;							

		case "ShipWreck_10_1":
			dialog.text = "¡Gracias, capitán! La carga no debería llevar mucho tiempo. ¡Dios, cuánto habíamos rezado para que llegara ese momento!";
			link.l1 = "Eso es genial. Espero que tus pruebas pronto lleguen a su fin.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "4");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
			}
			else
			{
				AddQuestRecord("ShipWrecked", "3");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				// <-- belamour
			}			
		break;							
				
		case "ShipWreck_11":
			dialog.text = "¡Vamos! ¿De verdad, capitán?! ¿Le tememos a la muerte?! La hemos engañado una vez, podemos hacerlo de nuevo. Simplemente no queremos perder nuestras vidas así. Pudrirnos aquí, solos\nNos uniremos gustosamente a tu tripulación y lucharemos valientemente bajo tu bandera. Solo no nos dejes aquí...";
			link.l1 = "Veo que estás dispuesto a hacer cualquier cosa solo para salir de aquí. Pero mírate, ¿qué clase de marineros podrías ser?";
			link.l1.go = "ShipWreck_14";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l2 = "Esa es una buena idea. Supongo que puedo contratarte.";
				link.l2.go = "ShipWreck_15";
			}	
		break;									
		
		case "ShipWreck_12":
			dialog.text = "No, no, ¡no estoy bromeando! Por favor, llévame lejos de este matadero caribeño... ¡fuera de este infierno! Sabes, soy un hombre rico... un hombre muy rico. Ni siquiera el Papa ha visto tanto oro en toda su vida. Te cubriré de oro...";
			link.l1 = "Oh, cielos... Está bien, sube al bote...";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			ChangeOfficersLoyality("bad_all", 1);
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "5");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
			AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
			// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины
			if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
			{
				AddQuestUserData("ShipWrecked", "sText", "wrecked");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "sText", "wrecked");
			}
			// <-- belamour
		break;							

		case "ShipWreck_13": // берем пассажирами
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			//Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.variant"))
			{
				if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
				if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			}	
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "ShipWreck_13_again";
			}
			DialogExit();
		break;
		
		case "ShipWreck_13_again":
			dialog.text = LinkRandPhrase("¿Por qué te demoras, capitán? Ordena levar anclas.","Lo sentimos, capitán, pero debemos prepararnos para zarpar.","¡Somos tan afortunados de que hayas decidido venir aquí!");
			link.l1 = "Date prisa. El barco no esperará a nadie.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_13_again";		
		break;
		
		case "ShipWreck_14":
			dialog.text = "Capitán, no tenemos nada que perder. La muerte ya nos sigue los pasos... Preferimos morir en una pelea justa que ser devorados por asquerosos coyotes...";
			link.l1 = "¡Oh, entonces es un desafío, ¿eh?! Muy bien, ¡resolvamos nuestras disputas"+GetSexPhrase(", como hombres","")+"!";
			link.l1.go = "ShipWreck_16";
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;		
		
		case "ShipWreck_15":
			dialog.text = "Lo juro, capitán, no se arrepentirá. Seremos los mejores marineros de todo el archipiélago.";
			link.l1 = "¡Genial! Sube al bote...";
			link.l1.go = "ShipWreck_17";			
		break;				
		
		case "ShipWreck_16":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetImmortal(rChar, false);
				if(CheckPassengerInCharacter(pchar, "ShipWreck_" + i)) 
				{
					RemovePassenger(pchar, rChar);
				}
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ShipWreckGroup");
			}

			LAi_Group_SetRelation("ShipWreckGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("ShipWreckGroup", LAI_GROUP_PLAYER, true);
			if(pchar.GenQuest.ShipWreck == "fight" || pchar.GenQuest.ShipWreck == "SailorsOnShoreFight") // belamour gen
			{
				LAi_group_SetCheck("ShipWreckGroup", "OpenTheDoors"); 
				LAi_group_SetCheckFunction("ShipWreckGroup", "ShipWreck_AfterBattle");
			}	
			DialogExit();		
		break;
		
		case "ShipWreck_17": // принимаем в команду
			if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
			if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;			
				rChar.Dialog.currentnode = "ShipWreck_17_again";
			}
			AddCharacterCrew(pchar, sti(pchar.GenQuest.ShipWreck.Qty));
			// --> belamour gen по количеству персон
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5) sText = "";	
			else sText = "";
			Log_Info("Tu tripulación ha aumentado en " + pchar.GenQuest.ShipWreck.Qty + " hombres" + sText + ".");
			// <-- belamour gen 
			Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			pchar.quest.ShipWreck_LocExit.over = "yes"; // Снимаем прерывание на выход из локации			
			DeleteAttribute(pchar, "GenQuest.ShipWreck");			
			AddCharacterExpToSkill(pchar, "Leadership", 50); 			
			DialogExit();
		break;

		case "ShipWreck_17_again":
			dialog.text = LinkRandPhrase("Lo juro, capitán, no se arrepentirá.","Has tomado la decisión correcta, capitán.","Capitán, ¡asegúrate de que tuviste tanta suerte como nosotros!");
			link.l1 = RandPhraseSimple("Eso espero.","Apresúrate. El barco no estará esperando a nadie.");
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_17_again";
		break;
		
		case "ShipWreck_18":
			dialog.text = "Capitán, ¿por qué ofendería a la gente honrada con tal desconfianza? Solo mire sus caras, ¿realmente cree que podrían ser amotinados?";
			link.l1 = "De acuerdo, pero ¿qué se supone que debo hacer contigo ahora?";
			link.l1.go = "ShipWreck_20";
		break;
		
		case "ShipWreck_19":
			dialog.text = "¿Y qué puedo hacer? Al menos ahora estoy vivo... ¡y agradezco a Dios haber salido! Pero si me ayudas a recuperar mi barco y vengarme por mi humillación, estoy dispuesto a darte todo lo que ese canalla haya robado y escondido en la bodega.";
			link.l1 = "Está bien, tienes un trato.";
			link.l1.go = "ShipWreck_13";
			ShipWreck_SetCapToMap();
			SetFunctionTimerCondition("prosralisrok", 0, 0, 180, false); // таймер лесник тамймер на поиск корабля 																																   
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "16");
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			// --> belamour окончание по количеству персон
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " his sailors");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " his sailor");
			}
			// <-- belamour
			AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
		break;
		
		case "ShipWreck_20":
			dialog.text = "No estamos en posición de dar órdenes. Depende de ti, solo llévanos a cualquier asentamiento o acéptanos en tu tripulación.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l1 = "Está bien, te llevaré a mi tripulación. ¡Pero nada de tonterías! ¡Tengo una disciplina estricta en mi barco!";
				link.l1.go = "ShipWreck_17";
			}
			link.l2 = "No te llevaré a ningún lado. Ya tengo suficientes matones en mi tripulación.";	
			link.l2.go = "ShipWreck_22";
			link.l3 = "Está bien, sube al bote, te llevaré a algún lugar.";
			link.l3.go = "ShipWreck_10_1";
		break;		
		
		case "ShipWreck_22":
			dialog.text = "Vaya... No nos dejas otra opción... Rezaremos para que la Providencia nos muestre misericordia y nos permita salir de este lugar peligroso. Si Dios quiere, tal vez aún lleguemos a tierra habitada...";
			link.l1 = "Adiós. Que el Señor vele por ti...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;		
		
		case "ShipWreck_30":
			if(pchar.GenQuest.ShipWreck == "SailorsSaved")
			{
				dialog.text = "Muchas gracias, capitán "+GetFullName(pchar)+"¡Has hecho tanto por nosotros que ninguna gratitud sería suficiente para recompensarte! Y aunque todas nuestras pertenencias no valen ni un cobre, permíteme ofrecerte este amuleto. Será muy útil para un capitán que frecuentemente se involucra en batallas navales.";
				link.l1 = "¡Gracias por tu regalo! ¡Este chisme es muy útil, de verdad! Adiós, capitán "+pchar.GenQuest.ShipWreck.Name+"y buena suerte en tus travesías.";
				link.l1.go = "ShipWreck_47";
			}
			else
			{
				dialog.text = "Capitán, muchas gracias. Has hecho mucho por nosotros, y cualquier recompensa sería inferior comparada con nuestro agradecimiento. Por favor, acepta este modesto obsequio como muestra de nuestra gratitud.";
				link.l1 = "En serio, no deberías haberte molestado... Tienes mucha más necesidad de dinero que yo. Aun así, es muy amable de tu parte. Gracias, y adiós.";
				link.l1.go = "ShipWreck_31";
			}	
		break;
		
		case "ShipWreck_31":
			//addMoneyToCharacter(pchar, sti(pchar.rank) * 200 + rand(2000));
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			TakeNItems(pchar, "jewelry2", 15+hrand(10));
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony"+ Locations[FindLocation(PChar.location)].townsack + "Acc"));
			CloseQuestHeader("ShipWrecked");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_32":	
			dialog.text = "Capitán, sepa que hay personas que irían hasta el fin del mundo por usted, de ahora en adelante. Es una lástima que no tenga nada con qué agradecerle. Aún así... Por favor, acepte este baratillo, lo encontré en esa cala maldita. Espero que le traiga suerte.";
			link.l1 = "Cualquiera habría hecho lo mismo en mi lugar. Adiós.";
			link.l1.go = "ShipWreck_33";
		break;
		
		case "ShipWreck_33":
			GiveItem2Character(pchar, pchar.GenQuest.ShipWreck.Prize);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + Locations[FindLocation(PChar.location)].townsack + "Acc")); // belamour gen: просто pchar.location ничего не даст
			CloseQuestHeader("ShipWrecked");		
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_34":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Capitán, ¿ya estamos en Dunkerque?","¿Estamos realmente en Dunkerque, capitán?"),RandPhraseSimple("Capitán, ¿es Europa?","¿Hemos navegado a Europa tan rápido?"));
			bTemp = !GetCharacterItem(pchar, "map_full") && !GetCharacterItem(pchar, "map_part2");
			bTemp = !GetCharacterItem(pchar, "map_part1") || bTemp;
			if(rand(100) > 75 && !isDay() && bTemp)
			{
				link.l1 = "Ajá...";
				link.l1.go = "ShipWreck_40";
			}
			else
			{
				link.l1 = LinkRandPhrase("Todavía no...","¿Qué Dunkerque? ¿Qué Europa? ¡Mira alrededor!","¡Dios mío!");
				link.l1.go = "ShipWreck_35";
			}
		break;
		
		case "ShipWreck_35":
			dialog.text = LinkRandPhrase("¡Pero, capitán, hiciste una promesa!","¿Cómo pudiste romper tu palabra, capitán?","¿Y cuándo llegamos a Europa?");
			if(rand(100) < 70)
			{
				link.l1 = "Está bien. Señor, reúna a sus hombres y sus pertenencias y vaya a donde elija.";
				link.l1.go = "ShipWreck_36";
			}
			link.l2 = RandPhraseSimple(LinkRandPhrase("¿Estás seguro de que realmente necesitamos llegar a Dunkerque?","Sabes, mi barco no está diseñado para navegar por el océano.","Capitán, ¿y qué pasa con el Caribe?"),LinkRandPhrase("Pero yo tenía otros planes...","¿Por qué quieres ir a Europa en primer lugar...?","¡Piensa en todas esas seductoras mujeres mulatas! Nunca las encontrarás en Europa..."));
			link.l2.go = "ShipWreck_37";	
		break;
		
		case "ShipWreck_36":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			pchar.GenQuest.ShipWreck = "fight";
			dialog.text = "¿Pero cómo?.. ¿¡Cómo te atreves!? ¿¡Qué clase de traición es esta!? ¡Te enseñaré a ser fiel a tu palabra!";
			link.l1 = "Bueno, tú lo pediste...";
			link.l1.go = "ShipWreck_16";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		case "ShipWreck_37":
			dialog.text = LinkRandPhrase(RandPhraseSimple("¡No! ¡Necesito llegar a Dunkerque!","¡En lugar de enseñarme geografía, deberías cumplir con tu obligación!"),RandPhraseSimple("¡No quiero oír nada al respecto! ¡Me prometiste llevarme a Europa!","No, capitán, eso no servirá. Estamos navegando hacia Europa."),"¡No voy a llevar una vida miserable por el resto de mis días en este agujero!");
			link.l1 = "Oh, no sé si esto va a terminar...";
			link.l1.go = "ShipWreck_38";
		break;		
		
		case "ShipWreck_38":
			chrDisableReloadToLocation = false;			
			SetFunctionExitFromLocationCondition("ShipWreck_ExitFromTown", pchar.location, false);				
			if(!CheckAttribute(pchar,"GenQuest.ShipWreck.CrazyRec")) // mitrokosta исправлена блокировка поручения капитана
			{
				pchar.GenQuest.ShipWreck.CrazyRec = true;
				AddQuestRecord("ShipWrecked", "7");
			}
			DialogExit();
		break;
		
		case "ShipWreck_40":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			dialog.text = "¡Mira! ¡Ese es un hombre decente! ¡Europa! ¡Maldita vieja Europa! ¡Sí-sí-sí! \n¡Oh, sí! Has cumplido con tu parte del trato y yo haré lo mismo. Aquí, toma esta mitad del mapa. La otra mitad la tenía mi socio. ¿Descansa en paz o descansa en el agua? Lo que sea. Él fue quien me convenció de participar en esta aventura.";
			link.l1 = "Espera, ¿entonces no eres marinero? ¿Tu compañero era un capitán?";
			link.l1.go = "ShipWreck_41";
		break;
		
		case "ShipWreck_41":
			dialog.text = "¡Dios mío!.. ¡Por supuesto que no! Bueno, sí, no soy marinero. Y él fue arrastrado por la borda por una enorme ola, cuando decidió navegar más lejos de la costa. Luego asumí el mando y ordené navegar hacia la cala... Y lo hicimos bien abriéndonos paso entre los arrecifes, hasta que todo fue decidido por un accidente fatal. El barco chocó con un fragmento de roca y se hundió...";
			link.l1 = "Ahora eso es una verdadera muestra de incompetencia...";
			link.l1.go = "ShipWreck_42";
		break;
		
		case "ShipWreck_42":
			dialog.text = "Escucha, ¿es esto realmente Dunkirk? Solo piénsalo, han pasado solo seis meses y todo el lugar ha cambiado\nAquí, toma el mapa, o su parte, para ser más específicos. ¡El tesoro está dentro de una cueva! No tengo idea de qué isla, pero eres un marinero experimentado, encontrarás la ubicación exacta algún día... Te garantizo que hay innumerables riquezas del pirata llamado aaarrrrrhg...";
			link.l1 = "Gracias, buen hombre. Incluso si no hay ningún tesoro, no me enfadaré demasiado. Adiós, y espero que nunca más nos volvamos a ver...";
			link.l1.go = "ShipWreck_43";
		break;
		
		case "ShipWreck_43":
			sld = CharacterFromID("ShipWreck_0");
			RemovePassenger(pchar, sld);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddMapPart();
			AddQuestRecord("ShipWrecked", "9");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");	
			AddSimpleRumourCity(LinkRandPhrase(RandPhraseSimple("Dicen que un chiflado apareció hace poco en la isla. Le está diciendo a todo el mundo que había perdido sus documentos, y está intentando presentar una solicitud para ser capitán en un barco con destino a Dunkerque.",
				"Dicen que un maníaco apareció recientemente en la isla. Robó una pala en la tienda y ahora está cavando una fosa más allá de las puertas del pueblo..."),
				RandPhraseSimple("Imagínate, hace poco un europeo de visita, con ropas gastadas y sucias, ¡intentó conseguir una audiencia con el gobernador! Afirmó que necesitaba ver al gobernador de Dunkerque lo antes posible.",
				"Hace poco hubo un escándalo en el ayuntamiento. Atraparon a un vagabundo que decía conocer personalmente al gobernador de Dunkerque."),
				"Algún psicópata te estuvo buscando hace poco. Decía que le debías dinero..."), pchar.location, 5, 3,"");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_44":
			dialog.text = RandPhraseSimple("¡Capitán, es simplemente genial que no nos hayas olvidado! ¡Todos hemos estado rezando por ti!","Capitán, ¿está cerca nuestra salvación? ¡Cuánto habíamos rezado para que llegara! Algunos ya empezaron a desesperarse...");
			link.l1 = "Saludos, "+pchar.GenQuest.ShipWreck.Name+"¡Cómo podría dejar a mis colegas en tal estado? ¿A dónde?";
			link.l1.go = "ShipWreck_45";
			link.l2 = "Saludos, "+pchar.GenQuest.ShipWreck.Name+"¡ Me temo que tengo malas noticias para ti. Hubo un cambio de planes, y no podré llevarte a bordo.";
			link.l2.go = "ShipWreck_9";
		break;
		
		case "ShipWreck_45":
			dialog.text = "No nos importa a dónde ir, mientras esté lo suficientemente lejos de este maldito lugar... ¿Nos permitirías comenzar a embarcarnos?";
			link.l1 = "Sí, adelante con eso. Pronto tus pruebas terminarán.";
			link.l1.go = "ShipWreck_46";
		break;

		case "ShipWreck_46":
			ChangeCharacterComplexReputation(pchar,"nobility", 4);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.dialog.currentnode = "ShipWreck_13_again";
			}			
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen снять таймер на 30 дней	 
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny")) DeleteAttribute(pchar,"GenQuest.ShipWreck.Mutiny"));
			SetFunctionExitFromLocationCondition("ShipWreck_LocationExit", pchar.location, false);				
			DialogExit();			
		break;

		case "ShipWreck_47":
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			GiveItem2Character(pchar, "indian_10");
			AddQuestRecord("ShipWrecked", "15");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			CloseQuestHeader("ShipWrecked");				
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_48":
			dialog.text = "Gracias, capitán. Ya comenzábamos a desesperarnos, pero literalmente nos has devuelto a la vida.";
			link.l1 = "No fue nada... Adiós.";
			link.l1.go = "ShipWreck_49";
		break;
		
		case "ShipWreck_49":
			AddQuestRecord("ShipWrecked", "17");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");								
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_50":
			dialog.text = "¿Qué demonios quieres de mí?";
			link.l1 = "He venido"+GetSexPhrase("","...")+" a enviarte saludos de una persona llamada"+pchar.GenQuest.ShipWreck.Name+"¿Lo conoces?"; // belamour gen
			link.l1.go = "ShipWreck_51";
		break;
		
		case "ShipWreck_51":
			dialog.text = "Es una lástima que no estrangulé a ese sinvergüenza antes. Bueno, entonces, supongo que ha llegado el momento de pagar por mi benevolencia...";
			link.l1 = "Efectivamente... Y el tiempo se ha acabado...";
			link.l1.go = "ShipWreck_52";
		break;
		
		case "ShipWreck_52":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheckFunction(LAI_GROUP_BRDENEMY, "ShipWreck_afterCabinFight");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;

		case "ShipWreck_53":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			pchar.quest.ShipWreck_ShipSink.over = "yes";
			dialog.text = "¡Buen trabajo, capitán! ¿Todo como acordamos, entonces? ¿Nosotros nos quedamos con el barco y tú con la carga?";
			link.l1 = "Claro. Toma el barco y haz buen uso de él.";
			link.l1.go = "exit";

			NextDiag.TempNode = "ShipWreck_53_again";		
			AddDialogExitQuestFunction("ShipWreck_SetShipNew");
		break;
		
		case "ShipWreck_53_again":
			dialog.text = "Te saludo, capitán "+GetFullName(pchar)+".";
			link.l1 = "Entonces, ¿qué te parece tu barco?";
			link.l1.go = "ShipWreck_53_again1";
		break;
		
		case "ShipWreck_53_again1":
			dialog.text = "Je, está chirriando y crujiendo, igual que yo. Creo que a ambos no nos queda mucho tiempo para navegar por los mares...";
			link.l1 = "Buena suerte, entonces...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_53_again";		
		break;
		// Генератор "Shipwrecked"
		
		// Генератор "State convicts"
		case "Convict_0End":
			DialogExit();
			pchar.GenQuest.Convict = "close";
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("Convict_DialogDisable");
		break;
		
		case "Convict_Begin":					
			switch(sti(pchar.GenQuest.Convict.var))
			{
				case 0:
					dialog.text = "Capitán, por favor ayúdenos a conseguir un barco o una chalupa, una tartana, lo que sea, realmente no importa. Estamos en tales circunstancias que debemos huir de este lugar inhóspito, pero no podemos aparecer en el asentamiento.";
					link.l1 = "¿Y qué clase de circunstancias son esas?";
					link.l1.go = "Convict_11";
				break;
				case 1:
					dialog.text = "Capitán, ¿nos prestaría un par de cientos de pesos? No lo pediríamos, pero realmente estamos en una necesidad desesperada.";
					link.l1 = "¿En gran necesidad, dices? Apuesto a que simplemente te has quedado sin ron y eso ciertamente es una gran necesidad.";
					link.l1.go = "Convict_12";			
				break;
				case 2:
					pchar.GenQuest.Convict.ToCity = FindColonyWithMayakExceptIsland(GetCharacterCurrentIslandId(pchar));	
					pchar.GenQuest.Convict.Mayak = GetMayakByCityName(pchar.GenQuest.Convict.ToCity);
					dialog.text = "Capitán, ¿sería tan amable de llevar a nuestra humilde compañía al faro de "+XI_ConvertString("Colony"+pchar.GenQuest.Convict.ToCity+"Gen")+"?";
					link.l1 = "Mirándote, no diría que eres demasiado humilde.";
					link.l1.go = "Convict_13";								
				break;
			}						
			link.l2 = LinkRandPhrase("No doy limosnas los viernes.","No tengo tiempo para estas tonterías.","No ayudo a gente extraña.");
			link.l2.go = "Convict_14";
			Convict_GetMineType();
			pchar.GenQuest.Convict.ShoreLocation = SelectQuestShoreLocation();
		break;
		
		case "Convict_11":
			dialog.text = "Somos fugitivos... de "+GetStrSmallRegister(XI_ConvertString("TipoDeMina"+pchar.GenQuest.Convict.MineType+"Dat"))+". Pronto el antiguo amo se dará cuenta... y entonces estaremos muertos, seguro.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l1 = "¿Sabes cómo manejar las velas?";
				link.l1.go = "Convict_11_1";
			}	
			link.l2 = "¿Y con qué vas a pagar?";
			link.l2.go = "Convict_11_2";
		break;
		
		case "Convict_12":
			dialog.text = "No es un buen momento para que pensemos en ron. Ha pasado una semana desde que escapamos, ahora nos estamos escondiendo en la jungla y muriéndonos de hambre.";
			if(sti(pchar.money) >= 3000)
			{
				link.l1 = "Bueno, supongamos que puedo darte dinero... ¿y luego qué? ¿Vas a quedarte escondido hasta que eventualmente te descubra una patrulla?";
				link.l1.go = "Convict_12_1";		
				link.l2 = "Está bien, ¿cuánto necesitas?";
				link.l2.go = "Convict_12_2";
			}	
			link.l3 = "¡Tengo poca charla con tipos como tú, cabezas en el bloque del verdugo, y eso es todo!";
			link.l3.go = "Convict_12_3";
		break;		
		
		case "Convict_12_1":
			if(hrand(1) == 0 && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				dialog.text = "¿Y qué más podemos hacer? Nos encantaría conseguir trabajo como marineros, pero considerando que somos fugitivos, ¿quién nos va a contratar?";
				link.l1 = "Te contrataré si sabes manejar las velas y no muestras signos de cobardía.";
				link.l1.go = "Convict_12_1_1";
			}
			else
			{
				dialog.text = "Ya hemos llegado a un acuerdo con los marineros locales. Para salir de aquí, solo nos faltan tres mil.";
				link.l1 = "Bueno, aquí están tus tres mil, si eso realmente te va a ayudar.";
				link.l1.go = "Convict_12_1_2";
			}
			link.l2 = "Bueno, no lo sé... Estos son tus propios problemas, y no voy a ayudarte a resolverlos.";
			link.l2.go = "Convict_12_1_End"; // выход из локи с закрытием квеста
		break;
		
		case "Convict_12_1_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Por favor, capitán, contrátenos, ¡seguro que no se arrepentirá! Habíamos estado piratas con "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+"en el Adriático, hasta que finalmente fue ahorcado y nosotros,"+pchar.GenQuest.Convict.ConvictQty+" hombres, fueron desterrados a este lugar.";
			link.l1 = "Está bien. Hay un lugar cercano, conocido como "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+" . Alrededor de la medianoche te recogeré allí. Espero que no te pierdas.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";		
		break;

		case "Convict_12_1_2":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			iTmp = hrand(3);
			if(iTmp <= 1)
			{
				dialog.text = "¡Por supuesto, nos va a ayudar enormemente! Zarpamos hoy, si el viento es favorable y los pescadores no nos fallan. Gracias, capitán, y que Dios os ayude...";
				link.l1 = "Buena suerte para ti también.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			if(iTmp == 2)
			{
				dialog.text = "¡Eso sí que es un golpe de suerte! Ni siquiera podíamos esperar conseguir el dinero tan rápido. Capitán, permítame presentarle un amuleto que tomamos de nuestro antiguo jefe. Quizás, también le traiga buena suerte a usted.";
				link.l1 = "Gracias, eso es algo decente, sin duda. Buena suerte para ti.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			if(iTmp == 3)
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "¡Ahora, ahí va un hombre generoso que no teme gastar la moneda, porque sabe cómo ganarla!\nAnoche vimos a los contrabandistas locales cargando "+MerPrm.QuestGoodsIdx+". Estaba oscuro, pero logramos discernir el nombre del barco en el costado de uno de los botes, '"+MerPrm.ShipName+"... y ese barco navega bajo la bandera de "+MerPrm.nation+". Quizás, encuentres esta información útil, je-je.";			
				link.l1 = "Hmm... Bueno, tal vez lo haga. Adiós a vosotros, rastreadores.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");			
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}
		break;
		
		case "Convict_12_2":
			dialog.text = "Oh cielos, no estamos en posición de hacer demandas. Cualquier cosa que puedas prescindir, estaremos agradecidos por cualquier cosa.";
			link.l1 = "300 pesos.";
			link.l1.go = "Convict_12_2_1";
			link.l2 = "1000 pesos.";
			link.l2.go = "Convict_12_2_2";
			link.l3 = "3000 pesos.";
			link.l3.go = "Convict_12_2_3";
		break;
		
		case "Convict_12_2_1":
			addMoneyToCharacter(pchar, -300);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			dialog.text = "Gracias, capitán, y que Dios te cuide...";
			link.l1 = "Buena suerte a ti también.";
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_2":
			addMoneyToCharacter(pchar, -1000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 40);
			if(hrand(1) == 0)
			{
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				dialog.text = "¡Eso sí que es un golpe de suerte! Ni siquiera podíamos esperar conseguir el dinero tan rápido. Capitán, permítame presentarle un chisme que tomamos de nuestro antiguo jefe. Quizás, también le traiga buena suerte a usted.";
				link.l1 = "Gracias, eso es algo decente, sin duda. Buena suerte.";
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 20);
			}
			else
			{
				dialog.text = "Gracias, capitán, y que Dios vele por ti...";
				link.l1 = "Buena suerte a ti también.";
			}
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_3":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			if(hrand(1) == 0)
			{
				dialog.text = "¡Vaya golpe de suerte! Ni siquiera podíamos esperar conseguir el dinero tan rápidamente. Capitán, permítame presentarle un abalorio que le hemos quitado a nuestro antiguo jefe. Tal vez, también le traiga buena suerte a usted.";
				link.l1 = "Gracias, eso es algo decente, sin duda. Buena suerte para ti.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			else
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "¡Ahora, ahí va un hombre generoso que no teme gastar la moneda, porque sabe cómo ganarla!\nAnoche vimos a los contrabandistas locales cargando "+MerPrm.QuestGoodsIdx+". Estaba oscuro, pero logramos discernir el nombre del barco en el costado de uno de los botes '"+MerPrm.ShipName+"... y ese barco navega bajo la bandera de "+MerPrm.nation+" . Quizás, encuentres esta información útil, je-je.";
				link.l1 = "Hmm... Bueno, tal vez lo haga. Adiós a vosotros, rastreadores.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);				
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}			
		break;
		
		case "Convict_12_1_End":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");	
			pchar.GenQuest.Convict = "close";
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_12_3":
			if(hrand(1) == 0)
			{
				dialog.text = "¡No nos condenes, capitán! Tenemos una chuchería decente, por favor, acéptala como rescate y déjanos ir...";
				link.l1 = "Entrégalo, entonces, y piérdete, mientras aún puedas.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "Ahora no tenemos otra opción, un hombre no morirá dos veces. ¡A la última batalla, muchachos!";
				link.l1 = "¡Ahora esa es una historia diferente!";
				link.l1.go = "Convict_Fight";
			}			
		break;
		
		case "Convict_13":
			dialog.text = "Bueno, ciertamente no somos santos, pero no estamos buscando pelea por nada... Somos fugitivos y necesitamos salir de aquí lo antes posible.";
			link.l1 = "¿Tienes algo para pagar el pasaje?";
			link.l1.go = "Convict_13_1";		
			link.l2 = "Oh, ya veo... No, no mancharé mi reputación por tu culpa. Adiós.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "¡Por supuesto! Estamos bastante acostumbrados a los abordajes y esas cosas. Durante casi dos años nosotros y el difunto "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" estaban aterrorizando a los comerciantes locales, ¡pero ay! Fue ahorcado, y "+pchar.GenQuest.Convict.ConvictQty+" hombres de nosotros fueron condenados a trabajos forzados.";
			link.l1 = "¿Qué tal si te unes a mi tripulación? Soy generoso"+GetSexPhrase("","")+", pero no te prometo una vida tranquila.";
			link.l1.go = "Convict_11_3";			
		break;
		
		case "Convict_11_2":
			dialog.text = "Sí, agarramos algo con "+GetStrSmallRegister(XI_ConvertString("TipoDeMina"+pchar.GenQuest.Convict.MineType+"Gen"))+", así que podemos pagar el doble. ASÍ QUE confío en que el precio está acordado. Y no te atrevas a traer guardias. No perdonamos la traición..."; // belamour gen
			link.l1 = "Está bien, espérame en la playa "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation+"Gen")+". Más cerca de la medianoche habrá un bote para ti ... ¡Y no quiero ver ningún truco!"; // belamour gen
			link.l1.go = "Convict_11_4";
			link.l2 = "No, mis amigos. ¿Y si les doy el barco y me apuñalan por la espalda? No, no les voy a ayudar en este asunto.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_3":
			dialog.text = "Con gran placer, "+GetSexPhrase("señor","señorita")+" capitán. Estamos bastante familiarizados con eso, y ciertamente no vamos a ser admitidos en la Armada con tales recomendaciones de todos modos, je-je.";
			link.l1 = "Muy bien. Hay un lugar cercano, conocido como "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+". Después de la medianoche te recogeré allí. Espero que no te pierdas.";
			link.l1.go = "Convict_11_6";
		break;
		
		case "Convict_11_4":
			dialog.text = "Pero, "+GetSexPhrase("señor","señorita")+" capitán, ¿estamos tomando aún un riesgo mayor? ¿Y si decides entregarnos al comandante?";
			link.l1 = "Eso es cierto... Está bien, si no estoy allí al amanecer, entonces el trato se cancela.";
			link.l1.go = "Convict_11_7";			
		break;
		
		case "Convict_11_5":
			if(makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 79) //макс. репутатция 90
			{
				dialog.text = "Oh, capitán, contábamos con usted...";
				link.l1 = "No es un problema. Si tienes dinero, encontrarás pasaje. Adiós.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "Eres listo, capitán, como puedo ver. Estoy seguro de que vas a correr directo al comandante, ¿verdad? ¿Y piensas que te saldrás con la tuya?";
				link.l1 = "¿Y planeas detenerme, por lo que puedo ver?! ¡Entonces recibirás lo que mereces!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "fight";
			}	
		break;
		
		case "Convict_11_6":
			pchar.GenQuest.Convict = "ToShore";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "1");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen"));	// belamour gen	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);	
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_11_7":
			pchar.GenQuest.Convict = "GetShip";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "2");		
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));					
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();		
			AddDialogExitQuestFunction("Convict_DialogDisable");		
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_13_1":
			pchar.GenQuest.Convict.Sum = (sti(pchar.rank)+10)*100+1000;
			dialog.text = "Hay algo. Revolvimos los cofres de nuestro jefe, pero luego hubo un alboroto al respecto, y tuvimos que abrirnos paso a golpes. Solo "+PChar.GenQuest.Convict.ConvictQty+" hombres lograron sobrevivir.";
			link.l1 = "Considerando las circunstancias, no te daré pasaje más barato que "+FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum))+" pesos por persona.";
			link.l1.go = "Convict_13_2";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "Veo que no sois cobardes. ¿Os uniríais a mi tripulación?";
				link.l2.go = "Convict_13_3";
			}
		break;
		
		case "Convict_13_2":
			dialog.text = "¿Y tenemos elección? Está bien, "+FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum))+"... ";
			link.l1 = "Entonces ve a "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation+"Dat")+". Enviaré un bote por ti después de la medianoche."; // belamour gen 
			link.l1.go = "Convict_13_4";
			pchar.GenQuest.Convict = "ToMayak";
			pchar.GenQuest.Convict.Sum = sti(pchar.GenQuest.Convict.Sum) * sti(pchar.GenQuest.Convict.ConvictQty);
		break;
		
		case "Convict_13_3":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "¿Y por qué no? Conocemos esas cosas, hemos estado pirateando con "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" en "+RandPhraseSimple("Gibraltar","Canal de la Mancha")+" antes de que nos quedáramos atrapados aquí.";
			link.l1 = "Muy bien. Hay un lugar cercano, conocido como "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+". Alrededor de la medianoche te recogeré allí. Espero que no te pierdas.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";
		break;
		
		case "Convict_13_4":
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "8");					
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen"));
			AddQuestUserData("Convict", "sSum", pchar.GenQuest.Convict.Sum);
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Dat"));	// belamour gen	 	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
				
		case "Convict_14":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Eh, capitán, tú también fuiste pobre una vez, tenías los bolsillos vacíos. Y ahora desprecias a la gente sencilla como nosotros."),RandPhraseSimple("Heh, la gente se está volviendo demasiado egoísta en estos días. Vives como si tuvieras dos siglos por delante.","Ah, veo que acabas de llegar de Europa, aún no has olido el hedor de nuestro vertedero tropical."));
			link.l1 = LinkRandPhrase("¿Estás tratando de hacerme pasar vergüenza? ¡Haré que tu lengua sea un par de pulgadas más corta!","¿Me estás intimidando? ¡Agarra bien tu sombrero ahora!","¿Eres un filósofo o qué? ¡Te meteré algo de sentido a golpes!");
			link.l1.go = "Convict_Fight";	
			pchar.GenQuest.Convict = "fight";
		break;
		
		case "Convict_Fight":
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	 
			LAi_LockFightMode(pchar, false); 
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			iTemp = sti(PChar.GenQuest.Convict.ConvictQty);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID("Convict_" + i);
				DeleteAttribute(rChar, "City");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ConvictGroup");
				LAi_SetImmortal(rChar, false);
			}
			LAi_group_SetRelation("ConvictGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ConvictGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ConvictGroup", "OpenTheDoors"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "Convict_15":
			dialog.text = LinkRandPhrase("Entonces, ¿capitán? ¿Nos ha traído un barco?","Saludos, capitán. Entonces, ¿qué hay de nuestro trato?","Hola, capitán. Ya comenzábamos a preocuparnos. Todo fue bien, supongo?");
			if(Convict_CheckShipType(SHIP_TARTANE) || Convict_CheckShipType(SHIP_WAR_TARTANE))
			{
				link.l1 = "Sí, aquí está tu bañera. Y no te olvides del pago. Yo pagué "+pchar.GenQuest.Convict.ShipPrice+" monedas por ello, así que me debes "+sti(pchar.GenQuest.Convict.ShipPrice)* 2+", tal como acordamos.";
				link.l1.go = "Convict_15_1";
			}	
			link.l2 = "No, he cambiado de opinión. Busca otro ayudante. Adiós...";
			link.l2.go = "Convict_15_2";
		break;
		
		case "Convict_15_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "¡Pero por supuesto! ¡Nos quitaron la libertad, pero no la conciencia! Por favor, acepte su dinero junto con nuestra gratitud infinita. Realmente nos ha ayudado. ¿Le importa si le pagamos en lingotes de plata?";
					link.l1 = "Claro que no. Buena suerte en tu viaje. Y reza para que no te encuentre en el mar abierto, te despacharé rápidamente.";
					link.l1.go = "Convict_15_1_1End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Commerce", 30);
					TakeNItems(pchar, "jewelry6", makeint(sti(pchar.GenQuest.Convict.ShipPrice)/50));
				break;
				case 2:
					dialog.text = "Capitán, sabes, pensamos que el dinero realmente no es tan importante en la vida. Y, francamente, lo necesitamos mucho más que tú en este momento. Pero tenemos una cosa que robamos de nuestro antiguo jefe. Quizás te interese mucho más que el oro. ¿Quieres echar un vistazo?...";
					link.l1 = "Sí, tienes razón. Eso es realmente algo maravilloso. Muy bien, está bien, tienes un trato, gracias y adiós.";
					link.l1.go = "Convict_15_1_2End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Fortune", 30);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				break;
				case 3:
					pchar.GenQuest.Convict = "FightInShore";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					dialog.text = "¿Por qué necesitarías tanto dinero, capitán? De todos modos, eres rico, y estamos condenados si no conseguimos este barco. Así que... simplemente te lo vamos a quitar. Sin resentimientos.";
					link.l1 = "Ése fue tu último error. Sin un barco aún podrías nadar, pero ahora o flotarás o te hundirás.";
					link.l1.go = "Convict_Fight";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Sneak", 30);
				break;
			}
		break;
	
		case "Convict_15_1_1End":
			AddQuestRecord("Convict", "4");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
	
		case "Convict_15_1_2End":
			AddQuestRecord("Convict", "5");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;	
	
		case "Convict_15_2":
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");
			for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
			{
				sld = CharacterFromID("Convict_" + i);
				sld.LifeDay = 0;
			}	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);	
			LAi_group_Delete("ConvictGroup");
			DeleteAttribute(pchar, "GenQuest.Convict");
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16":
			dialog.text = RandPhraseSimple("¿Entonces, capitán? ¿Podemos empezar a cargar nosotros mismos?","¡Por fin! Ya empezábamos a preocuparnos, pensamos que habías cambiado de opinión.");
			link.l1 = "Lo siento, he cambiado de planes. Tendrás que buscar otro capitán ahora.";
			link.l1.go = "Convict_16_1";
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				link.l2 = "Sube al bote, no tengo mucho tiempo.";
				link.l2.go = "Convict_16_2";			
			}			
			if(pchar.GenQuest.Convict == "ToShore" && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l2 = "Sube al bote, no tengo mucho tiempo.";
				link.l2.go = "Convict_16_2";			
			}			
		break;
		
		case "Convict_16_1":
			if(rand(1) == 0)
			{
				dialog.text = "¡Maldito seas! ¿Seguro que ya has enviado una patrulla tras nosotros? ¡No te saldrás con la tuya!";
				link.l1 = "¿De qué estás hablando?! ¡¿Quieres morir o qué?!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "ShoreFight";
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			else
			{
				dialog.text = "Capitán, "+GetSexPhrase("¿eres un hombre de palabra?","¿eres una mujer de fiar?")+" ¿O solo eres un maldito charlatán...?";
				link.l1 = "Será mejor que cuides tu lengua...";
				link.l1.go = "Convict_16_3";
			}
		break;
		
		case "Convict_16_2":
			if(pchar.GenQuest.Convict == "ToShore")
			{
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterCrew(pchar, sti(pchar.GenQuest.Convict.ConvictQty));
				OfficersReaction("bad");
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "10");
				CloseQuestHeader("Convict");				
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				AddQuestRecord("Convict", "10");
				sld = characterFromId("Convict_0");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false); 
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				SetFunctionLocationCondition("Convict_OnMayak", pchar.GenQuest.Convict.Mayak, true);
				locations[FindLocation(pchar.GenQuest.Convict.Mayak)].DisableEncounters = true;			
			}
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");
			pchar.GenQuest.Convict = "close";
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");				
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			AddDialogExitQuestFunction("Convict_DialogDisable");			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
						
		case "Convict_17":
			dialog.text = LinkRandPhrase("Oh, gracias, "+GetSexPhrase("hombre amable","dama justa")+".","Gracias, capitán, realmente me has salvado del lazo.","Muy agradecido por tan buen viaje.");
			link.l1 = LinkRandPhrase("Todo eso está muy bien, pero estoy esperando el dinero.","Es hora de pagar, ya sabes.","Efectivo al momento, como acordamos.");
			link.l1.go = "Convict_17_1";
		break;
		
		case "Convict_17_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "Por supuesto, ¡qué preguntas! Aquí tienes tu dinero en lingotes de oro y por favor acepta nuestra más sincera gratitud.";
					link.l1 = "Buena suerte para ti también. Adiós.";
					link.l1.go = "Convict_17_1_1End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Commerce", 80);
					TakeNItems(pchar, "jewelry5", makeint(sti(pchar.GenQuest.Convict.Sum)/200));
					break;
				case 2:
					dialog.text = "Capitán, sabes, pensamos que el dinero realmente no es tan importante en la vida. Y, francamente, lo necesitamos mucho más que tú en este momento. Pero tenemos una cosa que le robamos a nuestro antiguo jefe. Tal vez te interese mucho más que el oro. ¿Quieres echar un vistazo?...";
					link.l1 = "Sí, tienes razón. Eso es algo maravilloso, en verdad. Muy bien, de acuerdo, tienes un trato, gracias y adiós.";
					link.l1.go = "Convict_17_1_2End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Fortune", 80);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
					break;
				case 3:
					dialog.text = "¿Por qué necesitas tanto dinero? De todas formas, ya eres rico. Nos has ayudado, te ayudaremos en otra ocasión.";
					link.l1 = "No habrá tal ocasión. Recen sus oraciones, canallas, no tolero deudas.";
					link.l1.go = "Convict_Fight";
					pchar.GenQuest.Convict = "MayakFight";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Sneak", 80);			
					break;
			}
		break;
		
		
		case "Convict_17_1_1End":
			AddQuestRecord("Convict", "11");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	//belamour gen			
			AddQuestUserData("Convict", "sSum", makeint(pchar.GenQuest.Convict.Sum));
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_17_1_2End":
			AddQuestRecord("Convict", "12");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	// belamour gen	
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;		
		// <-- Генератор "State convicts"
		
		// Генератор "A reason to hurry" -->
		// Встреча с ОЗГ на берегу
		case "ReasonToFast_Hunter1":
			dialog.text = "Fui enviado aquí por "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" él mismo...";
			link.l1 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+"  te está esperando con una respuesta desde hace un par de horas ya. Me envió inmediatamente después de ti.";
			link.l1.go = "ReasonToFast_Hunter4";
		break;
		
		case "ReasonToFast_Hunter2":
			dialog.text = "Te he estado siguiendo en tu estela durante bastante tiempo, pero eres demasiado rápido.";
			link.l1 = "¿Y qué?";
			link.l1.go = "ReasonToFast_Hunter6";		
		break;
		
		case "ReasonToFast_Hunter3":
			dialog.text = "Será mejor que me digas cuánto paga el gobernador a sus subordinados.";
			link.l1 = "¡Maldita sea!";
			link.l1.go = "ReasonToFast_Fight";		
		break;
		
		case "ReasonToFast_Hunter4":
			dialog.text = "¡No he estado bebiendo! Estaba buscando al contramaestre...";
			link.l1 = "Ve ahora... Te diré "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+", que te perdiste en la selva.";
			link.l1.go = "ReasonToFast_Hunter5";		
			AddQuestRecord("ReasonToFast", "5");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
		break;
		
		case "ReasonToFast_Hunter5":
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_HunterGoOut");
		break;
		
		case "ReasonToFast_Hunter6":
			pchar.questTemp.ReasonToFast = "MeetHunterFail";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_PatrolAngry");
		break;
		
		case "ReasonToFast_Fight":
			LAi_SetPlayerType(pchar);
			pchar.questTemp.ReasonToFast = "PatrolAngry";
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять
			sTemp = "Patrol" + pchar.questTemp.ReasonToFast.LocIdx + "_";
			sGroup = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			iTemp = sti(pchar.questTemp.ReasonToFast.PatrolNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("ReasonToFast_Hunter");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		// бой с кэпом пиратского корабля
		case "ReasonToFast_FightCap": 
			dialog.text = "Y eres uno astuto. Reza al Dios para que tus trucos no sean descubiertos por "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+".";
			link.l1 = "No lo sabrá si no se lo dices... Y no lo harás, ¿verdad?";
			link.l1.go = "ReasonToFast_FightCap_1";
		break;
		
		case "ReasonToFast_FightCap_1":
			dialog.text = "¿Por qué? ¡Seguro que lo haré, y con gran placer!";
			link.l1 = "De todos modos te colgará por esa necedad. Así que no perdamos tiempo, y te ayudaré a escapar de la horca.";
			link.l1.go = "ReasonToFast_FightCap_2";
		break;
		
		case "ReasonToFast_FightCap_2":
			dialog.text = "Hmm... ¿Y cómo vas a hacer eso?";
			link.l1 = "Te mataré yo mismo...";
			link.l1.go = "ReasonToFast_FightCap_Last";
		break;
		
		case "ReasonToFast_FightCap_Last":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;		
		
		// встреча с лакеем в резиденции
		case "ReasonToFast_Lakey":
			dialog.text = "¿Tienes asuntos aquí, "+GetSexPhrase("monsieur","mademoiselle")+"?";
			link.l1 = "No-no, estoy aquí por invitación de la encantadora esposa del gobernador, echando un vistazo a esta verdaderamente lujosa residencia.";
			link.l1.go = "ReasonToFast_Lakey1";
			link.l2 = "Tengo un mensaje de personas que conoces.";
			link.l2.go = "ReasonToFast_Lakey2";
			link.l3 = "¡Sí. Quiero llevarte ante la justicia!";
			link.l3.go = "ReasonToFast_Lakey3";
			pchar.questTemp.ReasonToFast = "MeetLakey";
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_Lakey1":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "Ah sí, tuve mucha suerte de servir en una casa tan hermosa.";
			link.l1 = "No es de extrañar...";
			link.l1.go = "ReasonToFast_Lakey11";
		break;

		case "ReasonToFast_Lakey11":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "¡No olvides echar un vistazo a nuestro jardín!";
			link.l1 = "¡Gracias, buen hombre!";
			link.l1.go = "exit";			
			bDisableFastReload = false;
		break;
		
		case "ReasonToFast_Lakey2":
			dialog.text = "Ehh... ¿"+pchar.questTemp.ReasonToFast.password+"?";
			link.l1.edit = 1;			
			link.l1 = ""; 
			link.l1.go = "ReasonToFast_Lakey21";
		break;

		case "ReasonToFast_Lakey3":
			dialog.text = "¡No te saldrás con la tuya, traidor!";
			link.l1 = "¡Quieto, canalla!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;			
		break;

		case "ReasonToFast_Lakey21":
			if(GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipName) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "¡Rápido ahora! ¡Tomen todo lo valioso y corran!";
				link.l1 = "Creo que también deberías correr.";
				link.l1.go = "ReasonToFast_Lakey_exit";
				TakeNItems(pchar,"icollection", sti(pchar.questTemp.ReasonToFast.p8));
				TakeNItems(pchar,"Chest", sti(pchar.questTemp.ReasonToFast.p7));
				pchar.questTemp.ReasonToFast = "LakeyExitSuccess";					
				bDisableFastReload = true;		
				//chrDisableReloadToLocation = true;			
			}
			else
			{
				dialog.text = "Mmm, disculpe, debo retirarme.";
				link.l1 = "¡Quieto, canalla!";
				link.l1.go = "ReasonToFast_Lakey_exit";
				pchar.questTemp.ReasonToFast = "LakeyExitFail";
				bDisableFastReload = false;
			}			 
		break;

		case "ReasonToFast_Lakey_exit":
			DialogExit();	
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.ReasonToFast_ClearLakey.over = "yes"; //снимаем таймер
			ReasonToFast_SetHunterCoastal();
			AddDialogExitQuest("ReasonToFast_LakeyGoOut");
		break;		
		
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("¡Eres "+GetSexPhrase("un ladrón, por lo que veo! ¡Guardias, arréstenlo!","una ratera, por lo que veo! ¡Guardias, arréstenla!")+"","¡No puedo creerlo! ¡Me di la vuelta un segundo, y ya estás hurgando en mi cofre! ¡Detengan al ladrón!","¡Guardias! ¡Robo! ¡Detened al ladrón!");
			link.l1 = "¡Aaaah, diablos!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;
		break; 
		// Генератор "A reason to hurry" <--
		
		// ситуации с капитаном захваченного корабля
		// взрыв на корабле
		case "ShipSituation11": // пираты или ДУ
			dialog.text = RandPhraseSimple("Hola, "+GetSexPhrase("compañero","muchacha")+"¡He preparado una sorpresa para ti, encendí la mecha hasta la cámara de pólvora. ¡Va a volar todo por los aires!","¿Por qué estás ahí parado? ¡Hay un incendio en la cámara de pólvora! ¡Va a explotar, y los fuegos artificiales se verán en Europa!");
			link.l1 = RandPhraseSimple("¡Canalla, no me engañarás! ¡Lucha, cobarde!","¿Veo que las ratas abandonan el barco, y tú eres de los primeros?");
			link.l1.go = "ShipSituation12";
		break;
		
		case "ShipSituation12":
			dialog.text = RandPhraseSimple("Deberías correr también, si aprecias tu vida... Bueno, no tengo tiempo, un barco me está esperando. ¡Que lo pases bien pescando!","No tengo tiempo para hacer de héroe, los muchachos en el bote me están esperando. ¡Que lo paséis bien pescando, ganador!");
			link.l1 = RandPhraseSimple("¡Maldita sea! ¡Corta los defensas! ¡Vete!","¡Oh, Dios, cómo pudimos meternos en semejante lío! ¡Abran los canales del mar! ¡Zarpen!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation21": // военный корабль (не флагман)
			dialog.text = "¿Y qué?! ¿Crees que ganaste la pelea?! Ni hablar. He incendiado la santabárbara, no saldrás vivo de este barco.";
			link.l1 = RandPhraseSimple("Eres un sinvergüenza, ¡no me engañarás! ¡Lucha, cobarde!","¿Veo a las ratas abandonando el barco, y tú eres de los primeros?");
			link.l1.go = "ShipSituation22";
		break;
		
		case "ShipSituation22":
			dialog.text = RandPhraseSimple("Estoy atado por un juramento, pero eso no significa que tenga que morir en vano. Lamento no ofrecerte un lugar en el bote, los marineros no lo entenderán.","Los barcos están enlazados entre sí en el abordaje, así que tu destino está sellado. Discúlpame, pero mi bote me espera...");
			link.l1 = RandPhraseSimple("¡Maldita sea! ¡Corta los defensas! ¡Lárgate!","¡Oh, Dios, cómo pudimos meternos en tal lío! ¡Abran las entradas del mar! ¡Retírense!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation31": // ОЗГ
			dialog.text = RandPhraseSimple("¡Eres victorioso! ¡Bienvenido al infierno! He incendiado la santabárbara.","¡Aquí estás, buen hombre! Y has terminado, he incendiado el polvorín.");
			link.l1 = RandPhraseSimple("Eres un canalla, ¡no me engañarás! ¡Lucha, cobarde!","¿Veo a las ratas abandonando el barco, y tú eres de los primeros?");
			link.l1.go = "ShipSituation32";
		break;
		
		case "ShipSituation32":
			dialog.text = RandPhraseSimple("Llevaba un buen tiempo siguiéndote. Es una pena que tuve que sacrificar mi barco, pero tu cabeza vale por dos nuevos de todos modos. ¡Que te diviertas pescando!","¿Ves cómo te vas a ir? Con fuegos artificiales, como un príncipe indio"+GetSexPhrase("ce","¡carajo!")+"Pero no me rendiré como un perdedor, tu cabeza vale mucho más que mi barco. Adiós por ahora, mi bote no va a esperar mucho tiempo...");
			link.l1 = RandPhraseSimple("¡Maldita sea! ¡Corta los defensas! ¡Zarpa!","¡Oh, Dios, cómo pudimos meternos en semejante lío! ¡Abran las bocas del mar! ¡Zarpemos!");
			link.l1.go = "ShipSituation_End";			
		break;
		
		case "ShipSituation_End":
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			NPChar.LifeDay = 0;
			LAi_LockFightMode(pchar, false);	
			Log_Info(XI_ConvertString("El barco puede explotar"));
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;	
			pchar.GenQuest.ShipSituation.Explosion.CapId = NPChar.CaptanId;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		// эпидемия
		case "ShipEpidemy1":
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = RandPhraseSimple("¡Espera, capitán! Un par de palabras.","¡Espera, capitán! Creo que esto podría ser interesante para ti.");
			link.l1 = LinkRandPhrase("¿Por qué hablar durante una pelea?!","¿Y de qué debería hablar con un muerto?","¿Cuál es el trato? ¿Quieres hacer un testamento a mi nombre?");
			link.l1.go = "ShipEpidemy2";
		break;
		
		case "ShipEpidemy2":
			dialog.text = "Hay un brote de enfermedad a bordo. He perdido un cuarto de mi tripulación durante el viaje. Están todos condenados...";
			link.l1 = RandPhraseSimple("¡Maldito canalla! ¿Por qué no has mostrado una señal de que hay un desastre en tu barco?!","¿Has olvidado el código del mar? ¡Deberías haber izado una señal en el mástil indicando que hay un desastre en tu barco!");
			link.l1.go = "ShipEpidemy3";
		break;
		
		case "ShipEpidemy3":
			dialog.text = "Íbamos a morir de todos modos. ¡Por eso no nos rendimos, queríamos llevarte a ti y a tus demonios al otro mundo con nosotros! Ahora estoy completamente satisfecho. Puedes terminar tu vil acto.";
			link.l1 = RandPhraseSimple("¡Te haré pagar por eso!..","Me gusta la idea de que mueras primero. Y lo veré.");
			link.l1.go = "ShipEpidemy31";
			link.l2 = RandPhraseSimple("No mancharé mi espada con tu vil sangre, puedes vivir, aunque... ¿para qué? Me llevo a mi tripulación lejos de ese viejo cascarón podrido.","Deberías ser enviado a la horca por eso, pero no hay necesidad de ello ahora. Me llevo a mis hombres... Puedes vivir, aunque tu tiempo será corto...");
			link.l2.go = "ShipEpidemy32";
			pchar.GenQuest.ShipSituation.Epidemy.CapId = NPChar.CaptanId;
			pchar.GenQuest.ShipSituation.Epidemy = ShipSituation_4;
		break;
		
		case "ShipEpidemy31":
			pchar.GenQuest.QuestAboardCabinDialogIdx = NPChar.index;
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Died"; // вражеский кэп на волосок от смерти от переизбытка стали и свинца в организме
			LAi_LockFightMode(pchar, false);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "ShipEpidemy32":
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			LAi_LockFightMode(pchar, false);	
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Live"; // вражеский кэп остался в живых
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		// ситуации с капитаном захваченного корабля
		
		// Генератор "A damsel in the jungle"
		case "EncGirl_Lover":
			dialog.text = "Hola, capitán, me dijeron que me buscabas.";
			link.l1 = "Soy yo, si tú lo eres "+pchar.GenQuest.EncGirl.sLoverId+".";
			link.l1.go = "EncGirl_Lover1";
		break;
		
		case "EncGirl_Lover1":
			dialog.text = "Así es. ¿Algo importante?";
			link.l1 = "No sé si eso es importante para ti, pero he traído "+pchar.GenQuest.EncGirl.name+". Ella huyó de casa y ahora te está esperando no muy lejos de la taberna.";
			link.l1.go = "EncGirl_Lover2";
		break;
		
		case "EncGirl_Lover2":
			dialog.text = "¡Oh, cielos... Sabía que todo terminaría así... ¿Y por qué huyó? ¿Te lo dijo?";
			link.l1 = "Su padre quiere casarla con el hijo del usurero.";
			link.l1.go = "EncGirl_Lover3";
		break;
		
		case "EncGirl_Lover3":
			pchar.GenQuest.EncGirl.LoverCity = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			pchar.GenQuest.EncGirl.LoverIsland = GetIslandByCityName(pchar.GenQuest.EncGirl.LoverCity);
			dialog.text = "¡Oh no, no podemos permitir que eso suceda! Capitán, estoy en una situación tan estúpida... Quería pedirle que nos llevara a "+XI_ConvertString(pchar.GenQuest.EncGirl.LoverIsland+"Acc")+" a la ciudad llamada "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.LoverCity)+", pero ahora mismo no tengo dinero y todavía no he encontrado trabajo. Tengo una familia adinerada y una carrera prometedora en "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.LoverCity)+"...\nTe aseguro que mis padres estarán encantados de verme con una joven prometida y te recompensarán bien. Entonces, ¿aceptas?";
			link.l1 = "...Escucha ahora, tengo planes totalmente diferentes. Puedo darte un consejo para conseguir trabajo como marinero y alquilar un camarote para tu novia con tu salario. La gente llega a Europa de esa manera, y ese asentamiento tuyo está a un vuelo nocturno de pájaro.";
			link.l1.go = "EncGirl_Lover4";
			link.l2 = "Ah, la juventud... ¿Te das cuenta de lo que me estás pidiendo que haga? ¿Llevarme a una chica lejos de sus padres sin su bendición? ... ¿Y qué clase de hombre rechazaría tal cosa? ¡Por supuesto que estoy dentro!";
			link.l2.go = "EncGirl_Lover5";
		break;
		
		case "EncGirl_Lover4":
			npchar.lifeDay = 0;
			AddDialogExitQuestFunction("EncGirl_LoverExit");	
			DialogExit();
		break;
		
		case "EncGirl_Lover5":
			AddDialogExitQuestFunction("EncGirl_ToLoverParents");	
			DialogExit();
		break;
		
		case "EncGirl_Lover6":
			AddSimpleRumourCityTip(RandPhraseSimple("¿Te has enterado? " + pchar.GenQuest.EncGirl.name + " huyó con su amante. Decidió no atar su vida a un inválido. Seguramente ese fue el error de sus padres, no debieron dejarse tentar por el dinero de su prometido e intentar dar a semejante belleza en matrimonio a un espanto.",  
				"¿Te has enterado?" + pchar.GenQuest.EncGirl.name + " engañó tanto a su padre como a su futuro prometido. Dicen que un noble capitán la ayudó a ella y a su amante a llegar a otra isla, donde vivían los padres de su amante... ¡Qué cosas, todavía hay gente que no ha olvidado el sabor de la pasión!"), pchar.GenQuest.EncGirl.LoverCity, 3, 2, "citizen,habitue", "");
			dialog.text = "Gracias, capitán. Recordaremos tu ayuda por el resto de nuestros días.";
			link.l1 = "No fue nada. Espero que todo te salga bien.";
			link.l1.go = "EncGirl_Lover7";
		break;
		
		case "EncGirl_Lover7":
			switch (rand(4))
			{
				case 0:
					sTemp = "la tienda";
					pchar.GenQuest.EncGirl.LoverFather = "store_keeper";
				break;
				case 1:
					sTemp = "el astillero";					
					pchar.GenQuest.EncGirl.LoverFather = "shipyard_keeper";
				break;
				case 2:
					sTemp = "la oficina portuaria";					
					pchar.GenQuest.EncGirl.LoverFather = "portman_keeper";
				break;
				case 3:
					sTemp = "la taberna";					
					pchar.GenQuest.EncGirl.LoverFather = "tavern_keeper";
				break;
				case 4:
					sTemp = "el banco";					
					pchar.GenQuest.EncGirl.LoverFather = "usurer_keeper";
				break;
			}	
			pchar.GenQuest.EncGirl.FatherLoc = sTemp;
			dialog.text = "Prometí presentarte a mis padres. Si tienes un momento libre, por favor, ven a "+sTemp+", mi padre trabaja allí, y le contaré lo que has hecho por nosotros. Estoy seguro de que estará encantado de verte.";
			link.l1 = "Está bien, pasaré en cuanto tenga un momento. Sean felices y cuídense el uno al otro, ambos...";
			link.l1.go = "EncGirl_Lover8";
		break;
		
		case "EncGirl_Lover8":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			npchar.lifeday = 0;
			AddQuestRecord("JungleGirl", "16");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sText", pchar.GenQuest.EncGirl.FatherLoc);
			if((GetSummonSkillFromName(pchar, SKILL_FORTUNE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)) < 175)
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 0; // папочка жениха счастлив за сына :)
			}
			else
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 1; // папочка жениха разъярен за то что сын притащил в дом шалаву :)
			}
			chrDisableReloadToLocation = false; 
			pchar.GenQuest.EncGirl = "toLoverFather";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.function = "EncGirl_GenQuest_GetLoverFather";
			DialogExit();	
		break;
		// Генератор "A damsel in the jungle"
		
		// Генератор "Captain's request"
		case "CaptainComission_1":
			dialog.text = RandPhraseSimple("¡Espera! ¡Espera, capitán! Por favor.","Capitán, por favor, espera, te lo suplico...");
			link.l1 = LinkRandPhrase("¿Qué? ¿Perdiste el aliento?","¡Levanta tu espada, cobarde!","¿Qué pasa? ¿Olvidaste hacer un testamento?");
			link.l1.go = "CaptainComission_2";
		break;
		
		case "CaptainComission_2":
			dialog.text = "Espera... Estoy herido y soy demasiado débil para seguir luchando... No pido clemencia, pero tengo un asunto pendiente. Por favor, prométeme que cumplirás la última voluntad de un moribundo.";
			link.l1 = RandPhraseSimple("¡No seas un cobarde, capitán, acepta la muerte como un hombre debe hacerlo!","Capitán, ¿qué sentimentalismo es este? Una batalla está rugiendo a nuestro alrededor, así que terminemos lo que empezamos.");
			link.l1.go = "CaptainComission_21";
			link.l2 = "Habla ahora y sé rápido.";
			link.l2.go = "CaptainComission_22";
		break;
		
		case "CaptainComission_21":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_22":		
			if(rand(1) == 0) // "Ransom"
			{
				CaptainComission_Init(NPChar);
				dialog.text = "Dime "+pchar.GenQuest.CaptainComission.Name+" del asentamiento de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City)+", que no logré cumplir su petición... antes de que tuviera tiempo de... Que me perdone...";
				link.l1 = RandPhraseSimple("¿Y eso es todo?! Bien, puedo hacerlo. Oye, amigo...","Está bien, le diré si tengo tiempo. Oye, amigo...");
				link.l1.go = "CaptainComission_22_1";
				link.l2 = "No lo creo. No tengo tiempo para semejantes tonterías. Terminemos lo que empezamos.";
				link.l2.go = "CaptainComission_22_2";
			}
			else // "Operation 'Galleon'"
			{			
				CaptainComission_GaleonInit(NPChar);
				dialog.text = "Por favor, dile al capitán de una patrulla "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Gen"))+" '"+pchar.GenQuest.CaptainComission.ShipTypeName+"' "+pchar.GenQuest.CaptainComission.Name+", que no debería mostrar su cara en "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+"... "+"Las autoridades están al tanto de las verdaderas circunstancias de su muerte "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+" ' "+pchar.GenQuest.CaptainComission.VictimShipName+"... el tiempo apremia, va a ser arrestado... navegando hacia "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Acc")+" de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City1+"Gen")+", el viaje tomará casi quince días... ahh... debería apresurarse..."; // belamour gen
				link.l1 = RandPhraseSimple("No prometo nada, pero lo intentaré cuando se presente la ocasión. Oye, amigo...","Está bien, le diré si tengo tiempo. Oye, amigo...");
				link.l1.go = "CaptainComission_300";
			}					
		break;
		
		case "CaptainComission_22_1":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));	
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();	
		break;
		
		case "CaptainComission_22_2":
			dialog.text = "¡Qué crueldad! Espero que paguéis por ello.";
			link.l1 = "Y por mucho más...";
			link.l1.go = "CaptainComission_22_3";
		break;
		
		case "CaptainComission_22_3":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			pchar.GenQuest.CaptainComission = "Begin_2";
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_3":
			dialog.text = LinkRandPhrase("Te estoy escuchando, "+GetAddress_Form(pchar)+".","¿Qué querías?","¿Cómo puedo ayudarte?");
			if (pchar.GenQuest.CaptainComission == "Begin_1" || pchar.GenQuest.CaptainComission == "Begin_2") // лесник - доп.проверка если есть квест. для перехода .
			{	
			link.l1 = "¿Eres "+pchar.GenQuest.CaptainComission.Name+"¿Tengo asuntos contigo, Capitán?"+pchar.GenQuest.CaptainComission.CapName+" me pidió que te pasara una información importante.";
			link.l1.go = "CaptainComission_4";
			break;
			}
			link.l2 = "No, nada...";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_3"; // лесник - переход чтобы не вызывал баг при повтороном обращении
		break;
		
		case "CaptainComission_4":
			dialog.text = "¿Lo hizo? Está bien. Entonces, ¿qué es lo que capitán "+pchar.GenQuest.CaptainComission.CapName+"¿quería que supiera?";
			link.l1 = "Me pidió que te dijera que no podrá cumplir con tu petición.";
			link.l1.go = "CaptainComission_5";
		break;
		
		case "CaptainComission_5":
			dialog.text = "¿De qué estás hablando?! Lo conozco desde hace años, es un hombre muy honesto. ¡Simplemente no podría haberte dicho eso!";
			link.l1 = "Digamos que fue por razones fuera de su control. En otras palabras, ese fue su último deseo.";
			link.l1.go = "CaptainComission_6";
		break;
		
		case "CaptainComission_6":
			CaptainComission_GetPirateIsland();
			CaptainComission_GetFamilyType();
			if(pchar.GenQuest.CaptainComission == "Begin_1")
			{
				dialog.text = "¡Ah, esto está completamente fuera de lugar! Tanto tiempo desperdiciado\n"+"Capitán, en ese caso, tengo que pedirle que me ayude. Piratas de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Gen")+" han capturado a mi pariente "+pchar.GenQuest.CaptainComission.SlaveName+" y están exigiendo un rescate por él. ¿Podrías emprender esta misión? La recompensa debería ser bastante generosa.";
				link.l1 = "Desafortunadamente, tengo otros planes.";
				link.l1.go = "CaptainComission_6_1";
				link.l2 = "Intentaré ayudarte si lo explicas con más detalle.";
				link.l2.go = "CaptainComission_6_2";
			}
			
			if(pchar.GenQuest.CaptainComission == "Begin_2")
			{
				dialog.text = "¡Ah, esto está completamente fuera de lugar! Tanto tiempo perdido\n¿Y qué pasa con los cofres?";
				link.l1 = "Umm... ¿qué cofres?";
				link.l1.go = "CaptainComission_6_3";
				pchar.GenQuest.CaptainComission.CanFindChest = true;
			}	
		break;
		
		case "CaptainComission_6_1":
			dialog.text = "Es una pena, capitán... Es una lástima que no esté dispuesto a ayudarme.";
			link.l1 = "Ese no es un asunto de mi voluntad, amigo mío. Debes entender. Adiós.";
			link.l1.go = "CaptainComission_6_1End";
		break;
		
		case "CaptainComission_6_2":
			dialog.text = "Ayer recibí una carta de "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_ACC)+", en el cual me informaba que el rescate va a ser más alto, y también amenaza con venderlo como esclavo. El difunto capitán debería haber notificado "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_ACC)+", que estoy de acuerdo con las condiciones anteriores, y hago un pago por adelantado. Pero ahora veo por qué los piratas han subido la apuesta.";
			link.l1 = "¿Y qué estás sugiriendo?";
			link.l1.go = "CaptainComission_6_21";
		break;
		
		case "CaptainComission_6_3":
			dialog.text = "Oh, "+GetSexPhrase("compañero","moza")+", Siento que hay juego sucio aquí. Te advierto que esto es muy peligroso y puede causar terribles consecuencias. Capitán "+pchar.GenQuest.CaptainComission.CapName+" tenía tres cofres llenos de oro, que debería haber entregado a "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_DAT)+" en "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Acc")+" como rescate por un hombre,  "+pchar.GenQuest.CaptainComission.SlaveName+"Y si quisiera que vinieras a nosotros, no podría haber olvidado contarte sobre los cofres.";
			link.l1 = "Al decir lo último, no parecía que hubiera terminado su frase. Esperaba que me contaras más.";
			link.l1.go = "CaptainComission_6_31";
		break;
		
		case "CaptainComission_6_1End":
			AddQuestRecord("CaptainComission1", "3");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCharType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			CloseQuestHeader("CaptainComission1");
			sld = CharacterFromID("CapComission_1"); // удаление если послал нахуй. лесник.
			sld.LifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DialogExit();	
		break;
		
		case "CaptainComission_6_21":
			dialog.text = "Me queda no hay otra opción... Ya he reunido la suma requerida, 150 000 pesos. Te pido que lo entregues a "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Acc")+" y trae a mi pariente aquí. Te pagaré 40 000 tan pronto como esté hecho.";
			link.l1 = "Está bien, estoy listo.";
			link.l1.go = "CaptainComission_6_22";
			link.l2 = "Desafortunadamente, tengo otros planes.";
			link.l2.go = "CaptainComission_6_1";			
		break;
		
		case "CaptainComission_6_22":
			dialog.text = "Entonces toma el dinero y que nuestro Señor te bendiga. Pero por favor, date prisa. Me temo que "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_NOM)+" no esperará y venderá al pobre alma a la esclavitud.";
			link.l1 = "Espérame aquí. No creo que me tome mucho tiempo.";
			link.l1.go = "CaptainComission_6_22End";
		break;
		
		case "CaptainComission_6_22End":
			AddQuestRecord("CaptainComission1", "4");
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sFamilyType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			addMoneyToCharacter(pchar, 150000);
			pchar.GenQuest.CaptainComission = "Begin_11";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "goodSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_6_31":
			dialog.text = "No importa\nA la gente que reunió el rescate no le importará. Solo necesitan el resultado, respirando y en una pieza, "+pchar.GenQuest.CaptainComission.SlaveName+" . Así que no pierdas tiempo.";
			link.l1 = "¿Y qué pasa si me niego?";
			link.l1.go = "CaptainComission_6_32";
		break;
						
		case "CaptainComission_6_32":
			dialog.text = "En realidad, no necesito tu consentimiento. Solo te estoy notificando que si no entregas "+pchar.GenQuest.CaptainComission.SlaveName+" vivo y coleando a la taberna, enviaré cazadores de recompensas tras de ti...";
			link.l1 = "Hmm... Eso es serio. ¿Y si lo hago?";
			link.l1.go = "CaptainComission_6_33";
		break;
		
		case "CaptainComission_6_33":
			dialog.text = "Entonces lo discutiremos más a fondo.";
			link.l1 = "Está bien... Veamos cómo resulta.";
			link.l1.go = "CaptainComission_6_33End";
		break;
		
		case "CaptainComission_6_33End":
			AddQuestRecord("CaptainComission1", "5");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCapName",pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			pchar.GenQuest.CaptainComission = "Begin_22";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "badSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_7":
			if(pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Hola, capitán "+GetFullName(pchar)+"¿Alguna novedad?","Entonces, capitán, ¿ya has entregado el rescate?","Hola, espero que hayas venido con buenas noticias?");
					if(makeint(pchar.money)>=150000)
					{
						link.l1 = "Desafortunadamente, mis planes han cambiado, así que tengo que romper nuestro trato.";
						link.l1.go = "CaptainComission_7_1";
					}
					link.l2 = "Todavía no. Todavía estoy ocupado con eso.";
					link.l2.go = "CaptainComission_7_2";
				}
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
				{
					dialog.text = LinkRandPhrase("¡Oh, me alegra saludarte, capitán!"+GetFullName(pchar)+"¿Alguna buena nueva?","Entonces, capitán, ¿ha rescatado a nuestro amigo sufriente?","Me alegra verte vivo y coleando, capitán. ¿Cuál es el estado de nuestro asunto mutuo?");
					link.l1 = "Sin novedades hasta ahora, pero estoy en ello.";
					link.l1.go = "CaptainComission_7_3";
					link.l2 = "Escucha, amigo, ¿y por qué estás tratando de hacerme responsable de ese trato?";
					link.l2.go = "CaptainComission_7_4";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "GetSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Hola, capitán "+GetFullName(pchar)+"¿Alguna noticia?","Entonces, capitán, ¿ya ha entregado el rescate?","Hola, espero que hayas venido con buenas noticias?");
					link.l1 = "Sí. Tu petición fue cumplida, "+pchar.GenQuest.CaptainComission.SlaveName+" está en el tablón de mi barco y se está preparando para venir a la orilla.";
					link.l1.go = "CaptainComission_30";
				}
				else
				{
					dialog.text = LinkRandPhrase("¡Oh, me alegra saludarte, capitán!"+GetFullName(pchar)+"¿Alguna buena noticia?","Entonces, capitán, ¿has rescatado a nuestro amigo sufriente?","Me alegra verte vivo y coleando, capitán. ¿Cuál es el estado de nuestro asunto mutuo?");	
					link.l1 = "He traído al hombre del que hablamos. Está a bordo de mi barco.";
					link.l1.go = "CaptainComission_32";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "SlaveDied")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Hola, capitán "+GetFullName(pchar)+"¿Alguna novedad?","Entonces, capitán, ¿ya has entregado el rescate?","Hola, ¿espero que hayas venido con buenas noticias?");
					link.l1 = "Saludos, "+pchar.GenQuest.CaptainComission.Name+", tengo que disgustarte.";
					link.l1.go = "CaptainComission_50";
				}
				else
				{
					dialog.text = LinkRandPhrase("¡Oh, me alegra saludarte, capitán!"+GetFullName(pchar)+"¿Alguna buena noticia?","Entonces, capitán, ¿ha rescatado a nuestro amigo sufriente?","Me alegra verte vivo y coleando, capitán. ¿Cuál es el estado de nuestro asunto mutuo?");
					link.l1 = "El hombre por quien intercedías está muerto.";
					link.l1.go = "CaptainComission_60";
				}
			}
		break;
		
		case "CaptainComission_30":
			dialog.text = "Gracias, capitán, ha hecho un gran favor a nuestra familia. Aquí está su recompensa... Son tres cofres, equivale exactamente a 40 000 pesos. Por favor, discúlpeme, debo verlo ahora.";
			link.l1 = "Por supuesto, que tengáis un cálido encuentro y buena suerte a ambos.";
			link.l1.go = "CaptainComission_30_1";
			if(CheckAttribute(pchar, "GenQuest.CaptainComission.SlaveAddMoney"))
			{
				link.l2 = "Entiendo perfectamente tu impaciencia, pero han surgido circunstancias imprevistas que me obligaron a asumir costos adicionales.";
				link.l2.go = "CaptainComission_31";
			}	
		break;
		
		case "CaptainComission_30_1":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 3);
			Log_Info("Has recibido los cofres");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("CaptainComission1", "14");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_31":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 2);
			Log_Info("Has recibido unos cofres");
			PlaySound("interface\important_item.wav");
			dialog.text = "No entiendo... Ya hemos acordado la suma de tu pago, ¿verdad?";
			link.l1 = "Lo hemos hecho, pero en lugar de 150000 pesos me vi obligado a pagar 200000, sin mencionar el viaje a Barbados.";
			link.l1.go = "CaptainComission_31_1";
		break;
		
		case "CaptainComission_31_1":
			dialog.text = "Capitán, esto es solo un resultado de tu propia lentitud. Los piratas no hicieron ninguna demanda adicional conmigo. ¿Qué tipo tan extraño, intentando ganar algo a costa de las penurias de los demás?";
			link.l1 = "Está bien, veo que es inútil tratar de explicarte algo...";
			link.l1.go = "CaptainComission_31_1End";
		break;
		
		case "CaptainComission_31_1End":
			AddQuestRecord("CaptainComission1", "15");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_32":
			dialog.text = "¡Excelente! Y dudabas de que trabajaríamos bien juntos.";
			link.l1 = "Pero tuve que gastar mucho en este asunto.";
			link.l1.go = "CaptainComission_32_1";
		break;
		
		case "CaptainComission_32_1":
			GetSlaveSpeciality();
			dialog.text = "Lo sé, lo sé... Pero también es tu culpa. ¿Cómo pudiste hundir tres cofres con oro, que tuvimos que sacar literalmente del tesoro, para que "+NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation))+" podría tener tal especialista "+pchar.GenQuest.CaptainComission.SlaveSpeciality+"?";
			link.l1 = "Sabed que no os lo entregaré sin una compensación adecuada.";
			link.l1.go = "CaptainComission_32_2";
		break;
		
		case "CaptainComission_32_2":
			dialog.text = "Bueno, eres un hombre inteligente, seguramente entiendes que es demasiado tarde para negociar. Podríamos haber arrestado tu embarcación con su carga.\nPero la compensación fue proporcionada antes. Por lo tanto, el gobierno de "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+" te felicita por una operación exitosa y te presenta este valioso regalo y una modesta recompensa.";
			link.l1 = "Mm... Bueno, todavía mejor que nada. Toma a tu precioso especialista.";
			link.l1.go = "CaptainComission_32_2End";
		break;
		
		case "CaptainComission_32_2End":
			AddQuestRecord("CaptainComission1", "16");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSpeciality", pchar.GenQuest.CaptainComission.SlaveSpeciality);
			AddQuestUserData("CaptainComission1", "sNation", NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)));
			CloseQuestHeader("CaptainComission1");			
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 15);			
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Item); 
			TakeNItems(pchar, "jewelry5", 100);
			PlaySound("interface\important_item.wav");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_1":
			dialog.text = "¡Oh, qué lástima! Ya he perdido demasiado tiempo. ¡Realmente me has decepcionado, capitán!";
			link.l1 = "Entiendo, pero las circunstancias no se pudieron superar. Aquí está tu dinero.";
			link.l1.go = "CaptainComission_7_1End";
		break;
		
		case "CaptainComission_7_1End":
			AddQuestRecord("CaptainComission1", "8");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			rChar = characterFromId("CapComission_1");
			rChar.lifeDay = 0; 
			pchar.quest.CaptainComission1_30DaysIsLeft.over = "yes";
			addMoneyToCharacter(pchar, -150000);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_2":
			dialog.text = "¿Podrías darte prisa, por favor? Temo que los piratas cambien los términos del trato una vez más.";
			link.l1 = "No te preocupes, lo manejaremos.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_3":
			dialog.text = "¿Espero que te des cuenta de que estás trabajando contra reloj?";
			link.l1 = "¡Una vez más! Estoy en ello. Ten paciencia.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_4":
			dialog.text = "¡Dios nos salve! Sin presión, simplemente una ayuda del modesto puritano\nEs tu propia culpa. Mataste al capitán "+pchar.GenQuest.CaptainComission.CapName+", perdimos nuestro oro y fracasamos en el rescate de un hombre muy valioso. Ahora es un dolor de cabeza y tu responsabilidad. Ni pienses que estás perdonado... Pagarás por todo.";
			link.l1 = "¡Que te den!";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		// диалоги с управляющим на плантации
		case "CaptainComission_10":
			dialog.text = "Hola, ¿querías algo?";
			link.l1 = "¿Puedo ver al propietario de esta plantación?";
			link.l1.go = "CaptainComission_10_1";
		break;
		
		case "CaptainComission_10_1":
			dialog.text = "No está aquí, está buscando a un esclavo fugitivo, Blade, o Blood, no recuerdo... Y soy el administrador "+npchar.name+" y estoy autorizado a resolver todos los asuntos mientras el jefe está de licencia.";
			link.l1 = "¿Lo eres? Eso es bueno... ¿Y vender esclavos son también tus asuntos?";
			link.l1.go = "CaptainComission_10_2";
		break;
		
		case "CaptainComission_10_2":
			dialog.text = "Por supuesto. ¿Cuántos quieres comprar?";
			link.l1 = "Solo uno.";
			link.l1.go = "CaptainComission_10_3";
		break;
		
		case "CaptainComission_10_3":
			dialog.text = "Eh... ¿Estás seguro de que solo necesitas un esclavo?";
			link.l1 = "Por supuesto que lo estoy. Su nombre es "+pchar.GenQuest.CaptainComission.SlaveName+".";
			link.l1.go = "CaptainComission_10_4";
		break;
		
		case "CaptainComission_10_4":
			if(rand(1) == 0)
			{
				dialog.text = "Pero ciertamente te das cuenta de que el precio de un esclavo será más alto en comparación con el precio de un esclavo en un lote más grande, ¿no?";
				link.l1 = "Por supuesto que sí. ¿Puedes nombrar el precio?";
				link.l1.go = "CaptainComission_11";
			}
			else
			{
				if(rand(100) < makeint(sti(pchar.rank) + 0.75 * GetSummonSkillFromName(pchar, SKILL_FORTUNE)))
				{
					dialog.text = "Hum... ¿Espero que sepas por quién estás intercediendo?";
					link.l1 = "¿Qué quieres decir?";
					link.l1.go = "CaptainComission_12";
				}
				else
				{
					dialog.text = "Oh, ese holgazán. No daría ni un cobre por él. Desde que lo trajeron aquí, nunca hizo ningún trabajo real. No tengo idea de por qué el coronel desperdiciaría dinero en estos convictos del estado. Ahora, los negros son otra historia. Son grandes trabajadores, lo llevan en la sangre, fuertes y dóciles. Y créeme, pueden hacer absolutamente cualquier trabajo. La cosecha de caña de azúcar o servir como mayordomo, lo harán de la mejor manera posible, solo dales un poco de 'persuasión'...";
					link.l1 = "Amigo, me importan un comino tus negros. Solo me interesa ese holgazán del que hablabas, no vivirá mucho de todas formas, lo necesito como carne de cañón y pagaré más por él.";
					link.l1.go = "CaptainComission_13";
				}
			}
		break;
		
		case "CaptainComission_11":
			dialog.text = "Seguro, seguro. Déjame ver los precios\n¡Oh!!! 150000 pesos.";
			link.l1 = "Vaya...";
			link.l1.go = "CaptainComission_11_1";
		break;
		
		case "CaptainComission_11_1":
			dialog.text = "El precio debería estar en la lista de precios. Aquí. Sabes, no lo entiendo del todo. Otros esclavos se venden a precios razonables, pero ese se está vendiendo por una fortuna...";
			if(sti(pchar.money) >= 150000)
			{
				link.l1 = "Creo que entiendo de qué va el asunto... Muy bien, aquí está el dinero, y me lo llevo conmigo.";
				link.l1.go = "CaptainComission_14";
			}	
			link.l2 = "Hmm... Pero no estoy rescatando a un rehén, quiero comprar un esclavo común. ¿No crees que por esa suma se podría comprar un barco decente completamente equipado?";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_12":
			dialog.text = "Ese no es un esclavo ordinario. El Coronel Bishop incluso ha ordenado que lo vigilen.";
			link.l1 = "¿Entonces ni siquiera puedo comprarlo?";
			link.l1.go = "CaptainComission_12_1";
		break;
		
		case "CaptainComission_12_1":
			dialog.text = "Por supuesto que puedes. El coronel ha fijado un precio por él: 200000 pesos, según la lista de precios.";
			if(sti(pchar.money) >= 200000)
			{
				link.l1 = "¡Vaya! Bueno, seguramente ese coronel debe estar al tanto de qué tipo de persona es ese esclavo...";
				link.l1.go = "CaptainComission_16";
			}	
			link.l2 = "Hmm... Pero no estoy rescatando a un rehén, quiero comprar un esclavo ordinario. ¿No crees que con tal suma se podría comprar un barco decente y completamente equipado?";
			link.l2.go = "CaptainComission_15";	
		break;
		
		case "CaptainComission_13":
			dialog.text = "Ah, sí. Perdóname. Déjame ver los precios que ha dejado el Obispo.\nAha, aquí está. Bueno. ¡Oh!.. ¡150 000 pesos!..";
			if(sti(pchar.money) >= 15000)
			{
				link.l1 = "Aparentemente es algún tipo de error. Ciertamente te das cuenta de que ningún esclavo puede costar tanto. Supongo que hay un cero de más, y la suma debería ser 15000 pesos. Y aún así es demasiado, considerando que es un holgazán y un idiota.";
				link.l1.go = "CaptainComission_17";
			}	
			link.l2 = "Hmm... Pero no estoy rescatando a un rehén, quiero comprar un esclavo común. ¿No crees que por esa suma se podría comprar un barco decente completamente equipado?";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_14":
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 150000;
			dialog.text = "¡Genial! ¡Eso es genial! Lo traerán aquí ahora mismo... Ehh... ¿Té, tal vez?";
			link.l1 = "No, gracias... Saluda al coronel Bishop...";
			link.l1.go = "CaptainComission_14_1";
		break;
		
		case "CaptainComission_14_1":
			dialog.text = "¿Y de quién, podría saberlo?";
			link.l1 = "Mmm... No importa, no te molestes. Adiós.";
			link.l1.go = "CaptainComission_14_1End";
		break;
		
		case "CaptainComission_14_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_15":
			dialog.text = "Lo siento, pero no hay nada que pueda hacer. Aquí está la lista de precios.";
			link.l1 = "Oh, ya basta, 'lista de precios, lista de precios...' No podéis decidir ni la cosa más simple sin el Obispo. Decidle... No importa, no le digáis nada.";
			link.l1.go = "CaptainComission_15_1";
		break;
		
		case "CaptainComission_15_1":
			dialog.text = "Así que no vas a comprar a ese esclavo.";
			link.l1 = "No. Adiós.";
			link.l1.go = "CaptainComission_15_1End";
		break;
		
		case "CaptainComission_15_1End":
			OfficersReaction("bad");
			AddQuestRecord("CaptainComission1", "30");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			NextDiag.TempNode = "CaptainComission_19";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_16":
			dialog.text = "No sé nada al respecto. Solo tengo instrucciones específicas sobre la venta de ese esclavo en particular.";
			link.l1 = "¡Tonterías... Está bien, lo que sea. Aquí está el dinero. Trae al esclavo!";
			link.l1.go = "CaptainComission_16_1"; 
		break;
		
		case "CaptainComission_16_1":
			addMoneyToCharacter(pchar, -200000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 200000;
			dialog.text = "Por supuesto. Será entregado aquí en un instante.";
			link.l1 = "Adiós.";
			link.l1.go = "CaptainComission_16_1End";
		break;
		
		case "CaptainComission_16_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_17":
			dialog.text = "Mm... Sí, tal vez tengas razón. Debe ser un error.";
			link.l1 = "Bueno, si hemos acordado el precio, ¿puedo llevármelo ahora?";
			link.l1.go = "CaptainComission_17_1";
		break;
		
		case "CaptainComission_17_1":
			dialog.text = "Sí, por supuesto. Lo traerán aquí en un momento.";
			link.l1 = "Muy bien. Aquí está tu dinero... Adiós.";
			link.l1.go = "CaptainComission_17_1End";
		break;
		
		case "CaptainComission_17_1End":
			addMoneyToCharacter(pchar, -15000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 15000;
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_18":
			dialog.text = "¿Quieres un poco de té, capitán?";
			link.l1 = "No, gracias.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_19":
			dialog.text = "¿Has decidido comprarlo?";
			link.l1 = "No. Adiós.";
			link.l1.go = "exit";
		break;
		
		// диалоги с рабом
		case "CaptainComission_20":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Hola, capitán. ¿Cómo puedo ayudarte? No puedo creer que este tormento finalmente haya terminado.";
				link.l1 = "Deberías agradecer no a mí, sino más bien a tu pariente "+pchar.GenQuest.CaptainComission.Name+" de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+". Ha reunido el rescate.";
				link.l1.go = "CaptainComission_201";
			}
			else
			{
				dialog.text = "Hola, capitán. Me dijeron que pagaste el rescate por mí. Debo agradecerte por eso, aunque me doy cuenta de que solo eras un mensajero.";
				link.l1 = "Pareces no estar tan contento con tu libertad recién recuperada. ¿Te preocupa algo?";
				link.l1.go = "CaptainComission_202";
			}
		break;
		
		case "CaptainComission_201":
			dialog.text = "Por favor, si no interfiere demasiado con tus planes, llévame a él. Me gustaría agradecerle personalmente.";
			link.l1 = "Por supuesto, lo haré. Ven, te llevaré al barco.";
			link.l1.go = "CaptainComission_201_1";
		break;
		
		case "CaptainComission_201_1":
			AddQuestRecord("CaptainComission1", "11");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			DialogExit();
		break;
		
		case "CaptainComission_202":
			dialog.text = "Para estar seguro de mi libertad, necesito saber los nombres de aquellos que han pagado por ella.";
			link.l1 = "Bueno, fui yo quien pagó, aunque no fue por mi propia voluntad.";
			link.l1.go = "CaptainComission_202_1";
		break;
		
		case "CaptainComission_202_1":
			dialog.text = "Entonces, mis sospechas fueron confirmadas. ¿Fuiste obligado a hacerlo por "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation))+"?";
			link.l1 = "Sí, es "+pchar.GenQuest.CaptainComission.Name+" de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+".";
			link.l1.go = "CaptainComission_202_2";
		break;
		
		case "CaptainComission_202_2":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta 
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "Ya veo. No tengo idea de lo que te habían prometido, pero aquí está el trato: llévame a la taberna de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.SlaveCity+"Gen")+", estaré seguro allí de verdad. A cambio, compartiré con usted alguna información que poseo.";
			link.l1 = "Está bien, más aún porque no han prometido nada hasta ahora. Ven conmigo, te llevaré a mi barco.";
			link.l1.go = "CaptainComission_202_3";
			link.l2 = "No me arriesgaré a atraer problemas por información dudosa.";
			link.l2.go = "CaptainComission_203";
		break;
		
		
		
		case "CaptainComission_202_3":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			rChar = characterFromId("CapComission_1");
			ChangeCharacterAddress(rChar, "none", "");			
			rChar.lifeDay = 0; 
			AddQuestRecord("CaptainComission1", "12");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.quest.CapComission_DeliveSlave.win_condition.l1 = "location";
			pchar.quest.CapComission_DeliveSlave.win_condition.l1.location = pchar.GenQuest.CaptainComission.SlaveCity + "_tavern";
			pchar.quest.CapComission_DeliveSlave.function = "CaptainComission_DeliveSlave";
			LAi_SetActorType(NPChar);
			LAi_ActorFollow(NPChar, PChar, "OpenTheDoors", -1.0); //лесник  идем за ГГ
			DialogExit();
		break;
		
		case "CaptainComission_203":
			dialog.text = "Lamentablemente, no puedo revelártelo ahora. Esto puede significar problemas para ambos.";
			link.l1 = "Con más razón... Sígueme y nada de tonterías, por favor. Considérate arrestado una vez más.";
			link.l1.go = "CaptainComission_203_1";
		break;
		
		case "CaptainComission_203_1":
			AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0); //лесник - провожаем на корабль типа..
			DialogExit();
		break;
		
		case "CaptainComission_50":
			dialog.text = "¡¿Qué?! ¿Los piratas han alterado el trato de nuevo? ¡Pero no puedo sacar más dinero del negocio! ¡De esa manera pronto estaré en bancarrota!";
			link.l1 = "No... Tu pariente ha perecido en las plantaciones de Barbados durante un intento de fuga fallido.";
			link.l1.go = "CaptainComission_51";
		break;
		
		case "CaptainComission_51":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			dialog.text = "Oh... Estoy totalmente destrozado... ¿Cómo ocurrió eso?";
			link.l1 = "Los piratas no esperaron el rescate y lo vendieron como esclavo. Fui por él a Barbados, pero no pude salvarlo...";
			link.l1.go = "CaptainComission_52";
		break;
		
		case "CaptainComission_52":
			dialog.text = "¡Jesús! ¿Qué está pasando?\nBien, capitán, gracias por su participación. Y por favor, devuelva el dinero que le he dado.";
			link.l1 = "Mis gastos superaron todas las expectativas, así que me quedaré con tu dinero... Adiós.";
			link.l1.go = "CaptainComission_53";
			if(sti(pchar.money) >= 150000)
			{
				link.l2 = "Claro, tómalo... Lamento no haber podido ayudarte... Adiós.";
				link.l2.go = "CaptainComission_54";
			}
		break;
		
		case "CaptainComission_53":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			OfficersReaction("bad");			
			AddQuestRecord("CaptainComission1", "22");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_54":
			OfficersReaction("good");
			addMoneyToCharacter(pchar, -150000);
			AddQuestRecord("CaptainComission1", "23");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_60":
			dialog.text = "Lástima. No tienes idea de lo mal que está realmente...";
			link.l1 = "No hay nada que pueda hacer al respecto. Incluso me alegra que todo haya sucedido de esta manera. Adiós.";
			link.l1.go = "CaptainComission_61";
		break;
		
		case "CaptainComission_61":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -15);
			AddQuestRecord("CaptainComission1", "32");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");			
			DialogExit();
		break;
		
		// диалог с рабом в колодках
		case "CaptainComission_70":
			dialog.text = "Bebe... capitán, trae un poco de agua...";
			link.l1 = "Eh, compañero, ¿no eres tú "+pchar.GenQuest.CaptainComission.SlaveName+"?";
			link.l1.go = "CaptainComission_71";
		break;
		
		case "CaptainComission_71":
			dialog.text = "Sí... Ese soy yo...";
			link.l1 = "¡Escucha! Si no quieres perecer aquí, como un pez plano en un bajío, recógete y escúchame. ¿Sabes dónde se encuentra el Faro de Barbados?";
			link.l1.go = "CaptainComission_72";
		break;
		
		case "CaptainComission_72":
			dialog.text = "Hago...";
			link.l1 = "Una vez que tengas la oportunidad, corre allí. Intentaré arreglar tal oportunidad para ti.";
			link.l1.go = "CaptainComission_73";			
		break;
		
		case "CaptainComission_73":	
			LAi_SetPlayerType(pchar); 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);			
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			for(i = 0; i < 3; i++)
			{
				if (GetCharacterIndex("SlaveGuard_" + i) == -1) continue;
				sld = CharacterFromID("SlaveGuard_" + i);			
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SlaveGuards");
			}
						
			LAi_group_SetRelation("SlaveGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetRelation("SlaveGuards", sTemp, LAI_GROUP_NEITRAL);			
			LAi_group_SetAlarmReaction("SlaveGuards", sTemp, LAI_GROUP_NEITRAL, LAI_GROUP_FRIEND);
			LAi_group_FightGroups("SlaveGuards", LAI_GROUP_PLAYER, true);
			LAi_group_SetAlarm("SlaveGuards", LAI_GROUP_PLAYER, 0);
			LAi_group_SetCheck("SlaveGuards", "OpenTheDoors");
			LAi_group_SetCheckFunction("SlaveGuards", "CaptainComission_GuardsAfter");
			
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		// диалог охранников раба
		case "CaptainComission_80":
			dialog.text = RandPhraseSimple("Adelante y pregunta, capitán, pero sé rápido, estoy de servicio.","Habla, pero sé rápido y no me molestes con pequeñeces.");
			link.l1 = RandPhraseSimple("¿Puedes decirme cómo puedo encontrar a un cierto esclavo? Su nombre es "+pchar.GenQuest.CaptainComission.SlaveName+".","En algún lugar de esta plantación debería haber un esclavo llamado "+pchar.GenQuest.CaptainComission.SlaveName+"¿Puedes decirme cómo podría hablar con él?");
			link.l1.go = "CaptainComission_81";			
		break;
		
		case "CaptainComission_81":
			dialog.text = "Hoy está castigado y bajo guardia.";
			link.l1 = "Gracias.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_80";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_85":
			dialog.text = "Gracias... capitán, me has salvado la vida...";
			link.l1 = "Corre al faro de Barbados y espérame allí.";
			link.l1.go = "CaptainComission_86";
		break;
		
		case "CaptainComission_86":
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			LAi_group_AttackGroup(sTemp, LAI_GROUP_PLAYER);
			DialogExit();
		break;
		
		case "CaptainComission_90":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Capitán, ¿cómo puedo agradecerle? Todavía no puedo creer que este tormento finalmente haya terminado.";
				link.l1 = "Ya fui agradecido por tu pariente "+pchar.GenQuest.CaptainComission.Name+" de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+". Actúo siguiendo sus instrucciones.";
				link.l1.go = "CaptainComission_91";
			}
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
			{
				dialog.text = "Gracias, capitán. No sé en nombre de quién actúas, pero incluso una mala libertad es mejor que una buena esclavitud.";
				link.l1 = "¿Qué quieres decir?";
				link.l1.go = "CaptainComission_92";
			}
		break;
		
		case "CaptainComission_91":
			dialog.text = "Si no afecta demasiado tus planes, por favor llévame con él. Estoy demasiado cansado de todo esto.";
			link.l1 = "Por supuesto que lo haré... si logramos salir de aquí con vida.";
			link.l1.go = "CaptainComission_91End";
		break;
		
		case "CaptainComission_91End":
			pchar.GenQuest.CaptainComission = "toOurTavern";
			rChar = CharacterFromID("CapComission_Slave");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_92":
			dialog.text = "¿Y puedo saber los nombres de las personas que pagaron por mi libertad?";
			link.l1 = "Bueno, en realidad, no me pagaron. No me dejaron otra opción.";
			link.l1.go = "CaptainComission_93";
		break;
		
		case "CaptainComission_93":
			dialog.text = "Entonces, mis sospechas se confirmaron. ¿Fuiste obligado a hacerlo por "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation))+"?";
			link.l1 = "Sí, es "+pchar.GenQuest.CaptainComission.Name+" de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+".";
			link.l1.go = "CaptainComission_94";
		break;		
		
		case "CaptainComission_94":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "No tengo ni idea de lo que te han prometido, pero aquí está el trato: llévame a la taberna de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.SlaveCity+"Gen")+", estaré seguro allí de verdad. A cambio, compartiré contigo algo de la información que poseo.";
			link.l1 = "Está bien, tanto más, ya que no han prometido nada hasta ahora. Ven conmigo, te llevaré a mi barco.";
			link.l1.go = "CaptainComission_95";
			link.l2 = "No me arriesgo a atraer problemas sobre mí por alguna información cuestionable.";
			link.l2.go = "CaptainComission_96";
		break;	
		
		case "CaptainComission_95":
		AddQuestRecord("CaptainComission1", "12"); // поставил запись в СЖ лесник
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.GenQuest.CaptainComission = "toEnemyTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_96":
			dialog.text = "Lamentablemente, no puedo revelártelo por ahora. Esto puede significar problemas para ambos.";
			link.l1 = "Con más razón... Sígueme y nada de tonterías, por favor. Considérate arrestado una vez más.";
			link.l1.go = "CaptainComission_97";
		break;
		
		case "CaptainComission_97":	
            AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);		
			pchar.GenQuest.CaptainComission = "toTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_100":		
			dialog.text = "Gracias, capitán. Ahora finalmente estoy a salvo. No le ofrezco dinero, porque estoy seguro de que el conocimiento y su aplicación hábil valen mucho más que el metal perecedero.";
			link.l1 = "Estoy esperando la información";
			link.l1.go = "CaptainComission_101";
		break;
		
		case "CaptainComission_101":
			GetSlaveSpeciality();
			dialog.text = "La cuestión es que soy un científico, especialista en "+pchar.GenQuest.CaptainComission.SlaveSpeciality+" y "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.EnemyNation))+" me había estado ofreciendo cooperación durante bastante tiempo,"+"pero soy un ingeniero militar y mantengo mis juramentos de lealtad. Intentaron robarme, aunque los verdaderos problemas comenzaron cuando los piratas supieron mi verdadera identidad e importancia\n"+"Al final, lograron capturarme, pero el oro era lo único que querían, nunca necesitaron mi conocimiento. Mis amigos y enemigos no lograron pagar mi rescate a tiempo y fui vendido a las plantaciones. Ya conoces el resto.";
			link.l1 = "Sí, ay de ingenio, como dicen, en verdad.";	
			link.l1.go = "CaptainComission_102";
		break;
		
		case "CaptainComission_102":
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					sTemp = "proteger tu nave y su tripulación durante el combate.";
				break;	
				case 1:
					sTemp = "recargar rápidamente sus cañones y disparar con puntería en condiciones de polvareda.";
				break;					
				case 2:
					sTemp = "manejar rápidamente las velas y maniobrar en combate.";
				break;					
			}
			dialog.text = "Bueno, podrías decir eso. Así que, si prestas atención a lo que puedo contarte, te volverás mucho más hábil en la destreza de "+sTemp;
			link.l1 = "Gracias, esa información es muy útil, en verdad.";
			link.l1.go = "CaptainComission_103";
		break;
		
		case "CaptainComission_103":
			dialog.text = "Bueno, adiós y gracias por todo.";
			link.l1 = "Gracias a ti también. Adiós, y trata de no dejarte atrapar la próxima vez.";
			link.l1.go = "CaptainComission_104";
		break;
		
		case "CaptainComission_104":
			AddQuestRecord("CaptainComission1", "21");
			CloseQuestHeader("CaptainComission1");
			// а теперь раздача слонов !!!!!!!
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_DEFENCE, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_REPAIR, 10);
					}					
				break;
				case 1:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_CANNONS, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_ACCURACY, 10);
					}	
				break;
				case 2:
					AddCharacterSkill(pchar, SKILL_SAILING, 10);
				break;
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "","OpenTheDoors", -1.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		// Генератор "Captain's request"
		
		// Генератор "Operation 'Galleon'"
		case "CaptainComission_300":
			ReOpenQuestHeader("CaptainComission2");
			AddQuestRecord("CaptainComission2", "1");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //ПРАВКА
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCapName",  pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipTypeNom", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))));
			AddQuestUserData("CaptainComission2", "sCity2", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen"));
			AddQuestUserData("CaptainComission2", "sCity11", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));			
			SetFunctionLocationCondition("CaptainComission_GenerateQuestContinuation", GetArealByCityName(pchar.GenQuest.CaptainComission.City), false);
			SetFunctionTimerCondition("CaptainComission_TimeIsOver", 0, 0, 15, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission");
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();			
		break;
		
		// диалог с кэпом на палубе 
		case "CaptainComission_301":
		    if (!CheckAttribute(pchar,"GenQuest.pizdezh_uze_bil")) // проверка если разговор уже состоялся . чтобы не повторяться. лесник
			{
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			dialog.text = RandPhraseSimple("¡Ahoy!, soy el capitán "+GetFullName(NPChar)+", ¿qué te trajo a la cubierta de mi barco '"+pchar.GenQuest.CaptainComission.ShipTypeName+"'?","¡Ahoy!, siempre me alegra tener invitados en mi barco. Capitán "+GetFullName(NPChar)+" a su servicio.");
			link.l1 = "Hola, soy el capitán "+GetFullName(pchar)+", actuando en nombre del capitán "+pchar.GenQuest.CaptainComission.CapName+". Me pidió que te dijera que serías arrestado en "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+". Las autoridades saben sobre "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+"."; // ПРАВКА + belamour gen
			link.l1.go = "CaptainComission_302";
			break;
			}
			dialog.text = "¿Qué diablos estás haciendo aquí? ¡Hemos arreglado todo! ¡Vuelve a tu barco!";
			link.l2 = "Uhh..Sí, ¡correcto!";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_301"; // чтобы не было перехода на баг  - и т.д.  лесник 
			
		break;
		
		case "CaptainComission_302":
			dialog.text = "¡Ah, qué lástima! Déjame pensar...\n¿Y dónde está el capitán "+pchar.GenQuest.CaptainComission.CapName+"?";
			link.l1 = "Murió.";
			link.l1.go = "CaptainComission_303";
		break;
		
		case "CaptainComission_303":
			dialog.text = "¡Maldición! Las cosas solo empeoran... Escucha, "+GetFullName(pchar)+", No estoy listo para enfrentar tal giro de los acontecimientos. Capitán "+pchar.GenQuest.CaptainComission.CapName+" y acordé reunirme en "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+". El plan era cargar algo de mercancía en su nave. Ahora que el capitán está muerto, no puedo aparecerme en el asentamiento\nParece que no me queda más que pedirte un favor.";
			link.l1 = "Mi consentimiento dependerá del tipo de ayuda que necesites.";
			link.l1.go = "CaptainComission_304";
		break;
		
		case "CaptainComission_304":
			pchar.GenQuest.CaptainComission.ShoreLocation = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Ayúdame con los hombres y las lanchas. Necesito que se lleven la carga de "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+". Puedes quedarte con la parte del capitán difunto del cargamento.";
			link.l1 = "Hmm... Aparentemente, has mordido más de lo que podías masticar. Necesito más información.";
			link.l1.go = "CaptainComission_305";
			link.l2 = "Lamentablemente, no estoy en posición de perder tiempo en eso.";
			link.l2.go = "CaptainComission_306";
		break;
		
		case "CaptainComission_305":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "Está bien, te daré detalles\n"+"Durante una de las patrullas regulares me encontré con un barco bajo la bandera de "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+"Habían ignorado mis órdenes de rendirse."+"Cuando tras una corta persecución alcanzamos a "+sTemp+" '"+pchar.GenQuest.CaptainComission.VictimShipName+"' y así levantaron la bandera negra. El fuerte estaba bastante lejos, así que tuvimos que luchar por nuestra cuenta. Destruyeron nuestro bauprés, por eso no pudimos evitar el abordaje.\n"+"Fue cerca, pero logramos matarlos a todos gracias a la Santa María y una unidad de mosqueteros. Imagina nuestra felicidad cuando nos enteramos de que "+sTemp+" estaba lleno de. "+"   Hemos decidido que esta es una recompensa decente por nuestras heridas y las muertes de nuestros camaradas\nYa estaba oscuro, tomamos "+sTemp+" a la bahía más cercana y esconder la carga en tierra. Luego habíamos explotado "+sTemp+" y he informado sobre el navío pirata hundido. Por supuesto, no mencioné la carga.";
			link.l1 = "Aparentemente, alguien todavía lo ha soltado...";	
			link.l1.go = "CaptainComission_307";
		break;
		
		case "CaptainComission_306":
			dialog.text = "Es una lástima, capitán... Es una lástima que no estés dispuesto a ayudarme.";
			link.l1 = "Ese no es un asunto de mi voluntad, mi querido. Debes entender. Adiós.";
			link.l1.go = "CaptainComission_306End";			
		break;
		
		case "CaptainComission_306End":
			AddQuestRecord("CaptainComission2", "3");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", 1.5);			
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
		break;
		
		case "CaptainComission_307":
			dialog.text = "No creo que fueran mis hombres. Lo más probable es que el dueño de la carga esté ansioso por aliviar el dolor de la pérdida\n¿Entonces? ¿Puedo contar con tu asistencia?";
			link.l1 = "Sí, suena bien.";
			link.l1.go = "CaptainComission_308";
			link.l2 = "No, mi amigo. Primero: no sé cuánto cargamento irá a mi bodega. Y segundo: no hay garantía de que las autoridades no lo hayan encontrado ya y lo hayan llevado, dejando una emboscada en el escondite.";
			link.l2.go = "CaptainComission_309";
		break;
		
		case "CaptainComission_308":
			dialog.text = "Reunámonos en "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+" entonces, justo después de la medianoche. Mi posición actual requiere ser discreta. Debemos evitar las patrullas."; // belamour gen
			link.l1 = "Está bien, espérame allí.";
			link.l1.go = "CaptainComission_313";
//			bQuestDisableMapEnter = true;
		break;
		
		case "CaptainComission_309":
			dialog.text = "Lástima, pero no me dejas otra opción. Un barco no es suficiente para llevar todo el cargamento. Arriesgué mi carrera y mi propia vida por ello. Seguramente, tu tripulación me ayudará con gusto a cambio de una buena parte.";
			link.l1 = "¿Y qué estás sugiriendo?";
			link.l1.go = "CaptainComission_310";
		break;
		
		case "CaptainComission_310":
			dialog.text = "Tomaré tu embarcación y te dejaré en "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+"."; // belamour gen
			link.l1 = "Tu éxito me parece poco probable. Volveré a mi barco, incluso si tengo que cortar a toda tu tripulación.";
			link.l1.go = "CaptainComission_311";
			link.l2 = "Me parece que no tengo elección. Bueno, me someteré a la violencia...";
			link.l2.go = "CaptainComission_312";
		break;
		
		case "CaptainComission_311":
			pchar.GenQuest.CaptainComission.FightAfterDeck = true; //после резни на палубе - драка в море		
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "CaptainComission_FightInDeck", 3.5);
			DialogExit();
		break;
		
		case "CaptainComission_312":
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_toShore");
		break;
		
		case "CaptainComission_313": 		
			NextDiag.TempNode = "CaptainComission_314";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("CaptainComission2", "7");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreNameDat", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat"));
			SetFunctionTimerCondition("CaptainComission_SailToShore", 0, 0, 1, false);
		    pchar.GenQuest.pizdezh_uze_bil = "true"; // лесник временная запоминалка для диалога 
			DialogExit();			
		break;
		
		case "CaptainComission_314":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = "Capitán, debemos apresurarnos. Temo que una patrulla pueda avistarnos.";
			link.l1 = "Está bien, apresurémonos.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_315":
			dialog.text = "Capitán, ordene lanzar todos los botes salvavidas. Tendremos que ir varias veces, y me temo que una patrulla podría llegar a la cala. ";
			link.l1 = "No te preocupes, todo debería estar bien. Los barcos ya están llegando a la orilla.";
			link.l1.go = "CaptainComission_316";
		break;
		
		case "CaptainComission_316":
			dialog.text = "Oh, maldita sea. Ahora tenemos compañía...";
			link.l1 = "En verdad, si mencionas a un tonto, aparecerá de inmediato...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.pizdezh_uze_bil"); // удаление проверки на повтор диалога лесник
			AddDialogExitQuestFunction("CaptainComission_GenerateShorePatrol");
		break;
		
		// диалог с патрулем на берегу
		case "CaptainComission_317":
			dialog.text = "Capitán, estamos buscando a un criminal de guerra "+pchar.GenQuest.CaptainComission.Name+",  quien ha ocultado un valioso cargamento de las autoridades. Sus documentos, por favor.";
			link.l1 = "¿Qué documentos, oficial? Hemos desembarcado para reponer nuestras provisiones de agua fresca.";
			link.l1.go = "CaptainComission_318";
		break;
		
		case "CaptainComission_318":
			dialog.snd = "Voice\COGU\COGU004"; 
			dialog.text = "Y aquí está él, "+pchar.GenQuest.CaptainComission.Name+" él mismo . ¡Entreguen sus armas y síganme, los dos!";
			link.l1 = "Eso fue un muy mal momento, oficial...";
			link.l1.go = "CaptainComission_319";
		break;
		
		case "CaptainComission_319":
			DialogExit();
			for (i = 1; i <= sti(pchar.GenQuest.CaptainComission.SoldierQty); i++)
			{
    			sTemp = "SoldierIDX" + i;
				sld = GetCharacter(sti(pchar.GenQuest.CaptainComission.(sTemp)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			
			LAi_group_SetHearRadius("CoastalGuards", 100.0);			
		    sld = characterFromId("CapComission_1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);		
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);
            LAi_SetFightMode(Pchar, true);
				
		break;
		
		case "CaptainComission_320":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие если жив.
			pchar.GenQuest.CaptainComission.GoodsQty = makeint((sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) - sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Capacity")) + rand(250)) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));	
			pchar.GenQuest.CaptainComission.GoodsQtyNorm = sti(pchar.GenQuest.CaptainComission.GoodsQty);
			dialog.text = "Debemos apresurarnos antes de que lleguen los refuerzos. La carga está a punto de terminar, y tu parte es "+pchar.GenQuest.CaptainComission.GoodsQty+" unidades de "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+".";
			link.l1 = "Excelente. Es hora de partir ahora. Un placer hacer negocios contigo.";
			link.l1.go = "CaptainComission_321";
		break;
		
		case "CaptainComission_321":		
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;
			dialog.text = "Y solo una petición más. Las autoridades seguramente nos perseguirán, ¿podrías escoltar mi barco hasta "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+", que está en "+XI_ConvertString(GetIslandByCityName(sTemp)+"Voc")+"?"; // belamour gen
			link.l1 = "No, mi amigo, de ahora en adelante, cada hombre por sí mismo. Adiós...";
			link.l1.go = "CaptainComission_322";
			if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l2 = "Por supuesto, podría hacer eso por una buena recompensa.";
				link.l2.go = "CaptainComission_323";
			}				
		break;
		
		case "CaptainComission_322":
			Group_DeleteGroup("Sea_CapComission_1"); 
			sld = characterFromId("CapComission_1");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			sld.lifeDay = 0; 	
			CaptainComission_GenerateCoastalPatrol();
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			AddQuestRecord("CaptainComission2", "10");
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;
		
		case "CaptainComission_323":
			sld = characterFromId("CapComission_1");
			Fantom_SetCharacterGoods(sld, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoFreeSpace(sld), 1);
			pchar.GenQuest.CaptainComission.ConvoyMoney = makeint((sti(pchar.rank)*100 + sti(NPChar.rank)*170 + hRand(30)*20) * 2.5);
			pchar.GenQuest.CaptainComission.iDay  = 15 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "Por supuesto. Por la escolta estoy dispuesto a pagar  "+pchar.GenQuest.CaptainComission.ConvoyMoney+" pesos. Pero hay una condición más, no debería tomar más de "+pchar.GenQuest.CaptainComission.iDay+" días. Es importante.";	
			link.l1 = "Trato hecho. Partamos de inmediato.";
			link.l1.go = "CaptainComission_324";
			NextDiag.TempNode = "CaptainComission_325";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_324":
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха 
			sld = characterFromId("CapComission_1");
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(sld);
			LAi_ActorSetStayMode(sld);
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", sTemp, 5, false);
			SetShipRemovable(sld, false);
			SetCharacterRemovable(sld, false);
			Group_ChangeCharacter(PLAYER_GROUP, "CapComission_1");
			AddQuestRecord("CaptainComission2", "11");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));		
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.CaptainComission.ConvoyCity) + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.ConvoyMoney);
			CaptainComission_GenerateCoastalPatrol();
			pchar.quest.CaptainComission_MapEnter.win_condition.l1 = "MapEnter";
			pchar.quest.CaptainComission_MapEnter.function = "CaptainComission_MapEnter"; 
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1 = "Character_sink";
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_CapShip_Sink.function = "CaptainComission_CapShip_Sink";
			DialogExit();
		break;
		
		case "CaptainComission_325":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = LinkRandPhrase("Capitán, estamos perdiendo el tiempo. Podrían encontrarnos en cualquier momento.","Capitán, estamos corriendo contra el reloj. No olvides que me están buscando.","Capitán, no debemos demorarnos. Mi barco es demasiado grande para evitar la atención de la patrulla.");
			link.l1 = LinkRandPhrase("Sí, tienes razón. Tenemos que apresurarnos.","Entonces carguen sus traseros en los botes sin más demora.","Eso es... Reúne a tus hombres. Nos vamos.");
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_326_0":
			dialog.text = "Capitán, necesito hablar con mis hombres.";
			link.l1 = "Adelante.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_326":
			sld = characterFromId("Blaze");
			dialog.text = "Te saludo, capitán "+pchar.CaptainComission.Name+". Entonces, ¿has traído toda la carga? ¿Y dónde está el capitán "+pchar.CaptainComission.CapName+"?";
			link.l1 = pchar.CaptainComission.CapName+" murió. Tenía que preguntar "+NPCharSexPhrase(sld,"este caballero","esta dama")+" para ayuda. Te presentaré, este es el capitán "+pchar.CaptainComission.FullName+".";
			link.l1.go = "CaptainComission_327";
		break;
		
		case "CaptainComission_327":
			sld = characterFromId("Blaze");
			dialog.text = "Y "+NPCharSexPhrase(sld,"¿quién es él? ¿Es él?","¿quién es ella? ¿Es ella?")+" ¿consciente de nuestros asuntos?";
			link.l1 = "En general, sí. Pero hay un problema -"+NPCharSexPhrase(sld,"él está seguro","ella está segura")+", que la mitad de la carga pertenece a "+NPCharSexPhrase(sld,"él","ella")+"  Debemos convencer "+NPCharSexPhrase(sld,"él","ella")+", que este no es exactamente el caso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialog");
		break;
		
		case "CaptainComission_328":
			dialog.text = "Mi amigo "+GetFullName(pchar)+", ya has escuchado lo que necesitabas saber. Necesitamos acceder a tu bodega.";
			link.l1 = "¿Y crees que mis muchachos se quedarán ahí parados mirando, mientras unos harapientos vacían su bodega?";
			link.l1.go = "CaptainComission_329";
		break;
		
		case "CaptainComission_329":
			pchar.GenQuest.CaptainComission.GoodsSum = 2 * sti(pchar.GenQuest.CaptainComission.GoodsQtyNorm) * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost);
			dialog.text = "Tienes un punto. Dinero en efectivo por la cantidad, digamos, "+pchar.GenQuest.CaptainComission.GoodsSum+" pesos, nos librará de la necesidad de enfrentarnos con tu tripulación. Ten en cuenta que esto cubre la mitad de nuestra carga, así que todo es justo. Si estás de acuerdo con esto, entonces nadie saldrá herido.";
			link.l1 = "¿Y qué si me niego?";
			link.l1.go = "CaptainComission_330";
		break;
		
		case "CaptainComission_330":
			dialog.text = "En ese caso, la violencia es inevitable. Tú serás la primera víctima y encontrarás la paz en esta acogedora cala, y tu tripulación simplemente será incapaz de venir en tu ayuda... ¿Cómo te gustaría eso?";
			link.l1 = "Me dejas sin elección. Bueno, simplemente los mataré a todos.";
			link.l1.go = "CaptainComission_331";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsSum))
			{
				link.l2 = "Creo que no tengo elección. Muy bien, aquí está tu dinero.";
				link.l2.go = "CaptainComission_332";
			}	
		break;
		
		case "CaptainComission_331":
			dialog.text = "Bueno, esa es una decisión apropiada para "+GetSexPhrase("un noble caballero","una dama valiente")+".";
			link.l1 = "¡Deja de filosofar! ¡Vamos al grano!";
			link.l1.go = "CaptainComission_334";
			CaptainComission_ChangeCaptain();
		break;
		
		case "CaptainComission_332":
			dialog.text = "Una sabia decisión. Te deseo buena suerte.";
			link.l1 = "Que te atragantes con ello...";
			link.l1.go = "CaptainComission_333";
		break;
		
		case "CaptainComission_333":
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);// лесник - разрешить снова драться после сдачи денег. но после драки кулаками не машут ..как говориться))
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsSum));
			AddQuestRecord("CaptainComission2", "17");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", UpperFirst(XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsSum);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GangExit");
		break;

		case "CaptainComission_334":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheckFunction(sGroup, "CaptainComission_GangDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;

		case "CaptainComission_340":
			dialog.text = "Capitán "+GetFullName(pchar)+", llegamos tarde. Espero que entiendas que ahora no eres elegible para una recompensa.";
			link.l1 = "Claro que sí. Ya he ganado una buena moneda, gracias a ti. Adiós...";
			link.l1.go = "CaptainComission_341";
		break;
		
		case "CaptainComission_341":
			Group_DeleteGroup("Sea_CapComission_1");			
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			AddQuestRecord("CaptainComission2", "15");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");					
			DialogExit();
		break;
		
		case "CaptainComission_Canoneer":
			dialog.text = "¿Comprarías un poco de ron para un viejo soldado que ha sufrido mucho en las batallas por la gloria de la Corona?";
			link.l1 = "¡Tabernero! ¡Sirve un poco de ron para nosotros!";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_Canoneer1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("CaptainComission_TalkCanoneer");
		break;
		
		case "CaptainComission_Canoneer1":
			dialog.text = "Oh, gracias, "+GetAddress_Form(pchar)+", muy amable de tu parte tratar a un lisiado que ha perdido completamente la memoria...";
			link.l1 = "¿Completamente, dices?";
			link.l1.go = "CaptainComission_Canoneer2";
		break;
		
		case "CaptainComission_Canoneer2":
			dialog.text = "Absolutamente, señorita"+GetSexPhrase("ter","s")+" capitán... completamente. No recuerdo nada excepto un niple volando directamente hacia mi cabeza. Mira qué agujero hizo en ella, supongo que toda mi memoria debe haberse escapado por ahí.";
			link.l1 = "Amigo, guarda tus patéticas historias para las amas de casa. He visto a gente que sufrió un golpe directo de metralla, su memoria fue completamente borrada... junto con sus cabezas... Y aquí estás hablando de una cadena de disparos imaginaria. Mejor hablemos del capitán "+pchar.GenQuest.CaptainComission.Name+". ";
			link.l1.go = "CaptainComission_Canoneer3";
		break;
		
		case "CaptainComission_Canoneer3":
			dialog.text = "Oh, bueno, ya sabes. Tengo que ganarme la vida de alguna manera. En cuanto al capitán "+pchar.GenQuest.CaptainComission.Name+", no hay beneficio para mí en parlotear... Si cobrara cien monedas por cada pregunta sobre él, ahora tendría más oro que el que el gobernador recauda de sus súbditos en un año... ";
			link.l1 = "¿Y has intentado vender la carga, escondida por ese capitán?";
			link.l1.go = "CaptainComission_Canoneer4";
		break;
		
		case "CaptainComission_Canoneer4":
			dialog.text = "¿Qué? ¿Otro sabueso? Te lo digo una vez más, no recuerdo a ningún capitán "+pchar.GenQuest.CaptainComission.Name+"¡Estoy contuso, y tengo el certificado del médico que lo confirma! ¿Qué más necesitas?!";
			link.l1 = "¡Guau, no te emociones tanto! Sabes... Llegó demasiado tarde. Capitán "+pchar.GenQuest.CaptainComission.CapName+" me pidió que dijera eso "+pchar.GenQuest.CaptainComission.Name+" no debería mostrar su rostro en ese asentamiento, las autoridades saben sobre las circunstancias de la destrucción de "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Acc"))+"..."+pchar.GenQuest.CaptainComission.VictimShipName+", y él será arrestado.";
			link.l1.go = "CaptainComission_Canoneer5";
		break;
		
		case "CaptainComission_Canoneer5":
			dialog.text = "Uf. Deberías haber dicho eso de inmediato y no estar hablando en círculos. Fui yo quien le preguntó al capitán "+pchar.GenQuest.CaptainComission.CapName+" interceptar nuestro barco a su regreso. "+"Fue movido en los muelles justo después de esa maldita pelea. ¿Qué hacía ese maldito pirata allí con sus mercancías? Tantos muchachos están muertos por su culpa.";
			link.l1 = "¿Y cómo lograste sobrevivir?";
			link.l1.go = "CaptainComission_Canoneer6";	
		break;
		
		case "CaptainComission_Canoneer6":
			dialog.text = "Por error. Para ser honesto, por mi maldito error. No fui lo bastante rápido, así que nuestro bote no salió del área de peligro. Sin embargo, solo yo sufrí. Me golpeó un naufragio y me lanzó al agua. Ni siquiera recuerdo cómo llegué a la orilla.";
			link.l1 = "¿Y cómo lograste escabullirte de la pesquisa?";
			link.l1.go = "CaptainComission_Canoneer7";
		break;
		
		case "CaptainComission_Canoneer7":
			dialog.text = "Les dije que estaba contuso durante el abordaje y que no sabía nada sobre ningún cargamento. También fingí ser débil de mente, apenas me había puesto de pie justo antes de la llegada de "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+". No podía moverme adecuadamente, mi coordinación estaba arruinada.";
			link.l1 = "Eh, pero ¿quién soltó el secreto sobre la carga, de todos modos?";
			link.l1.go = "CaptainComission_Canoneer8";
		break;
		
		case "CaptainComission_Canoneer8":
			dialog.text = "Los piratas han enviado una carta al gobernador, supuestamente en nombre del mercader herido. Decidieron vengarse del capitán por su persistencia. Fue su culpa, su estúpida obstinación nos llevó a este lío.";
			link.l1 = "¿Pero cómo te encontraste con ese pirata en primer lugar?";
			link.l1.go = "CaptainComission_Canoneer9";
		break;
		
		case "CaptainComission_Canoneer9":
			dialog.text = "No lo sé. Era una patrulla ordinaria y había un barco ordinario navegando bajo la bandera de "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+". No tengo idea de por qué el capitán decidió inspeccionarlo, pero no prestaron atención a un disparo de advertencia, y cuando los alcanzamos, izaron una 'Jolly Roger'. "+"No tuvimos el apoyo del fuerte, así que la pelea no fue fácil. Luego la parte del abordaje. Aún no sé cómo logramos derrotarlos.\n"+"Bueno, y vimos toda esa preciosa carga. El mismo diablo debió habérnosla dado. Tuvimos que esconder la carga en la costa y volar el barco capturado por los aires. Estaba demasiado dañado.";
			link.l1 = "¿No tienes miedo de que todos tus esfuerzos y sacrificios sean en vano, si los hombres del gobernador descubren el escondite?";	
			link.l1.go = "CaptainComission_Canoneer10";
		break;
		
		case "CaptainComission_Canoneer10":
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			pchar.GenQuest.CaptainComission.CanoneerCity = Colonies[iTmp].id;			
			pchar.GenQuest.CaptainComission.Sum = 20000 + 2000 * sti(pchar.rank);
			dialog.text = "No lo encontrarán. He volado bien la entrada de la cueva, después de todo, yo era el mejor experto en explosivos de todo el escuadrón. Solo los contrabandistas pueden encontrar mi escondite, ellos conocen cada pulgada de este lugar.\n"+"Mira, yo mismo no tengo ni idea de qué hacer con el botín. No puedo ni venderlo ni moverlo por mi cuenta. Además, nadie hará negocios con un cráneo roto. No quiero hacer dinero con la muerte de mis camaradas de tripulación, pero puedo decirte la ubicación del escondite para "+pchar.GenQuest.CaptainComission.Sum+"  pesos si me llevas a "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.CanoneerCity)+".";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				link.l1 = "Estoy de acuerdo. Aquí tienes tu dinero. Ahora habla.";	
				link.l1.go = "CaptainComission_Canoneer11";
			}
			else
			{
				link.l1 = "¡Maldita sea! Está bien, espera aquí, iré a buscar el dinero.";
				link.l1.go = "CaptainComission_Canoneer12";				
			}	
			link.l2 = "Eso es demasiado, compañero. Además, no tengo un barco adecuado. Bueno, buena suerte para ti y adiós...";
			link.l2.go = "CaptainComission_Canoneer13";
		break;
		
		case "CaptainComission_Canoneer11":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.Sum));
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "Bueno, está bien. Nos vemos esta noche después de la medianoche alrededor de "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+". Y asegúrate de tener espacio en tu bodega para "+pchar.GenQuest.CaptainComission.GoodsQty+" piezas. "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+". Sería una pena tirar algo de eso..."; // belamour gen
			link.l1 = "Me encargaré de eso. Nos vemos en la ensenada...";
			link.l1.go = "CaptainComission_Canoneer14";
		break;
		
		case "CaptainComission_Canoneer12":
			AddQuestRecord("CaptainComission2", "41");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //Gen лесник
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.Sum);
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			SetFunctionTimerCondition("CaptainComission_CanoneerWaitMoney", 0, 0, 1, false);
			NextDiag.TempNode = "CaptainComission_Canoneer15";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer13":
			AddQuestRecord("CaptainComission2", "40");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(NPChar);
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer14":
			AddQuestRecord("CaptainComission2", "43");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat"));	// belamour gen
			LAi_CharacterDisableDialog(NPChar);
			SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			SetFunctionTimerCondition("CaptainComission_MeetCanoneerInShoreTimer", 0, 0, 1, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer15":
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				dialog.text = "Y aquí estás, al fin. Ya empezaba a preocuparme. Pensé que simplemente me entregarías a las autoridades.";
				link.l1 = "Aún no me he vuelto loco. Aquí tienes tu dinero. Ahora es tu palabra.";
				pchar.quest.CaptainComission_CanoneerWaitMoney.over = "yes";// лесник . снят таймер ожилания бабла
				link.l1.go = "CaptainComission_Canoneer11";
			}	
			else
			{
				dialog.text = "Entonces, ¿dónde está el dinero?";	
				link.l1 = "¡Maldita sea! Está bien, espera aquí, lo iré a buscar.";
				link.l1.go = "exit";
				NextDiag.TempNode = "CaptainComission_Canoneer15";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
		break;
		
		case "CaptainComission_350":
			dialog.text = "Capitán, al parecer, llegamos tarde. Los contrabandistas han encontrado el escondite.";
			link.l1 = "No voy a renunciar a mi botín, ni siquiera el mismo diablo me lo quitará.";
			link.l1.go = "CaptainComission_351";
			link.l2 = "Renuncio, lidia con tus competidores tú mismo.";	
			link.l2.go = "CaptainComission_352";
		break;
		
		case "CaptainComission_351":
			DialogExit();
			AddDialogExitQuest("CaptainComission_GangDialog_1");
		break;
		
		case "CaptainComission_352":
			DialogExit();
			//SetFunctionExitFromLocationCondition("CaptainComission_NoGangDialog", pchar.location, false);
			 AddDialogExitQuestFunction("CaptainComission_NoGangDialog");   // лесник - исправлено . предыдцщий код не работал
		break;
		
		case "CaptainComission_360":
			dialog.text = "Capitán, tenemos un asunto serio aquí. Le aconsejo que retire su escuadrón antes de que lleguen nuestros barcos.";
			link.l1 = "Caballeros, parece que están intentando tomar lo que no les pertenece.";
			link.l1.go = "CaptainComission_361";
		break;
		
		case "CaptainComission_361":
			dialog.text = "¡Oh, ¿de veras?! ¿Tienes idea de con quién estás hablando?";
			link.l1 = "Te estoy hablando a ti, amigo. Esa carga tiene un dueño legítimo, y yo lo represento.";
			link.l1.go = "CaptainComission_362";
		break;
		
		case "CaptainComission_362":
			dialog.text = "¡No permitiremos que interfieras con nuestros asuntos, incluso si fueras el Mesías de nuestro Dios! ¿Despeja el canal, si aprecias tu vida?";
			link.l1 = "¿No fui claro? ¡Ese cargamento es mío, y no me iré sin él!";
			link.l1.go = "CaptainComission_363";
		break;
		
		case "CaptainComission_363":
			dialog.text = "¡Al demonio con eso! ¡Si tanto lo deseas, entonces lo esperarás aquí, para siempre!";
			link.l1 = "El destino decidirá quién se quedará aquí para siempre.";
			link.l1.go = "CaptainComission_364";
		break;
				
		case "CaptainComission_364":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				rChar = CharacterFromID("CapComission_1");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);						
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				rChar = CharacterFromID("CapComission_Canoneer");
				//LAi_SetWarriorType(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);			
			}	
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckCaptainAfterBattle");
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckGangAfterBattle");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_365":
			dialog.text = "Capitán, ordene a sus hombres que se apresuren, una patrulla puede llegar en cualquier momento. Además, los contrabandistas obviamente también estaban esperando sus transportes.";
			link.l1 = "Sí,  necesitamos darnos prisa... Cargad la mercancía en las bodegas, y salgamos de aquí.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_365";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_366":
			dialog.text = "Gracias, capitán "+GetFullName(pchar)+". Si no hubieras sido tú, los contrabandistas se habrían llevado nuestro cargamento, y esos muchachos que cayeron defendiéndolo habrían muerto en vano...";
			link.l1 = "Y gracias por confiar en mí.";
			link.l1.go = "CaptainComission_367";
		break;
		
		case "CaptainComission_367":
			dialog.text = "Tengo un amuleto, aquí, le debo mi vida. Por favor, acéptalo, podría ser tu amuleto de la suerte. Y gracias de nuevo, amigo. Que los vientos siempre estén de tu lado.";
			link.l1 = "Gracias por el regalo, no lo esperaba. Y será mejor que cuides tu salud mientras tengas monedas en los bolsillos.";
			link.l1.go = "CaptainComission_368";
		break;
		
		case "CaptainComission_368":
			LAi_SetActorType(NPChar);
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.LifeDay = 0;
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "48");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity + "Gen"));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_370":
			if(pchar.GenQuest.CaptainComission == "MayorTalkBad")
			{
				pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			}	
			dialog.text = "Al parecer, hoy es mi día de visita. ¿Me necesitas?";
			link.l1 = "Si eres capitán "+pchar.GenQuest.CaptainComission.Name+", entonces sí.";
			link.l1.go = "CaptainComission_371";
		break;
		
		case "CaptainComission_371":
			dialog.text = "...antiguo capitán"+pchar.GenQuest.CaptainComission.Name+"...";
			link.l1 = "Yo soy "+GetFullName(pchar)+", y tengo un par de preguntas para ti.";
			link.l1.go = "CaptainComission_372";
		break;
		
		case "CaptainComission_372":
			dialog.text = "¿Y por qué crees que respondería a ellas?";
			link.l1 = "Capitán "+pchar.GenQuest.CaptainComission.CapName+" me pidió que te advirtiera que las circunstancias de la destrucción de "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Acc"))+"' "+pchar.GenQuest.CaptainComission.VictimShipName+"se hizo conocido por las autoridades, "+"pero no vi tu barco en el viaje desde "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City1+"Gen")+".";
			link.l1.go = "CaptainComission_373";	
		break;
		
		case "CaptainComission_373":
			dialog.text = "¿Y dónde está el capitán "+pchar.GenQuest.CaptainComission.CapName+"?";
			link.l1 = "Murió.";
			link.l1.go = "CaptainComission_374";
		break;
		
		case "CaptainComission_374":
			dialog.text = "Ya veo... ¿Así es como está la cosa, eh? Muchas piezas encajan ahora. Así que, alguien ha soltado que saqueamos "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+". "+"Tarde o temprano, encontrarán la carga y me colgarán. El c>apitán "+pchar.GenQuest.CaptainComission.CapName+" está muerto, eso significa que nadie puede ayudarme.\nExcepto tú.\n"+GetFullName(pchar)+", sáqueme de aquí y le recompensaré.";
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "El gobernador recibió un mensaje del dueño de la carga. Y los números en él son bastante impresionantes, ¿sabes?";
					link.l1.go = "CaptainComission_375";
				}
				else
				{
					link.l1 = "No puedes esperar que te ayude con los ojos vendados.";
					link.l1.go = "CaptainComission_375";
				}
			}			
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "El gobernador recibió un mensaje del dueño de la carga. Y las cifras en él son bastante impresionantes, ¿sabes?";
					link.l1.go = "CaptainComission_375";				
				}
				else
				{
					link.l1 = "Hay rumores en la colonia de que tienes tratos con los contrabandistas...";
					link.l1.go = "CaptainComission_375";				
				}
			}
		break;
		
		case "CaptainComission_375":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "Parece que tendré que contarte toda la historia.\n"+"Durante una de las patrullas regulares me encontré con un barco bajo la bandera de "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+"  Ignoraron mis órdenes de rendirse. "+"Hemos llegado "+sTemp+" '"+pchar.GenQuest.CaptainComission.VictimShipName+" tras una breve persecución y alzaron la bandera negra. El fuerte estaba bastante lejos, así que tuvimos que luchar por nuestra cuenta. Destruyeron nuestro botalón, por eso no pudimos evitar el abordaje.\n"+"Fue cerca, pero logramos matarlos a todos gracias a la Santa María y a una unidad de mosqueteros. Imagina nuestra felicidad cuando descubrimos que "+sTemp+" estaba lleno de objetos de valor. "+"Hemos decidido que esto es una recompensa decente por nuestras heridas y las muertes de nuestros hombres\nYa estaba oscuro, logramos tomar "+sTemp+" a la bahía más cercana y esconde el cargamento en tierra. Luego quemamos "+sTemp+"y informé sobre un barco pirata hundido. Por supuesto, no mencioné la carga.";		
			link.l1 = "Creo que no tiene sentido que intentes engañarme. Así que te propongo un trato, muéstrame el escondite y te llevaré a cualquier lugar del archipiélago que desees.";
			link.l1.go = "CaptainComission_376";
		break;
		
		case "CaptainComission_376":
			dialog.text = "Ja-ja-ja... No, capitán, no abandonaré el asentamiento sin mi parte, incluso si tengo que colgarme en la horca.";
			link.l1 = "Está bien. Tendrás tu mitad.";
			link.l1.go = "CaptainComission_377";
			link.l2 = "Hmm... Sabes, no estoy dispuesto a arriesgar mi cabeza por tu bienestar. Adiós...";
			link.l2.go = "CaptainComission_378";
		break;
		
		case "CaptainComission_377":
			dialog.text = "Ahora estás hablando. Estoy listo\nPrimero, debes esconderme a bordo de tu nave. Te mostraré la bahía donde está escondido el alijo.";
			link.l1 = "Entonces actuemos rápido y coordinados. Abriré tu celda, y tú me seguirás. No te quedes atrás y no hagas preguntas hasta que estemos fuera del fuerte.";
			link.l1.go = "CaptainComission_379";
		break;
		
		case "CaptainComission_378":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			sld = CharacterFromID("CapComission_1");
			sld.LifeDay = 0;
			ChangeCharacterComplexReputation(pchar,"nobility", -5);			
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(npchar);// лесник - запрет диалога
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_379":
			AddQuestRecord("CaptainComission2", "21");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition = "CaptainComission_PrisonFree_Death";
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_group_Register("CapComission_Prison");
			LAi_group_SetRelation("CapComission_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "CapComission_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "CapComission_Prison");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CaptainComission.PrisonFree = true;
			if(pchar.GenQuest.CaptainComission == "MayorTalkGood") 
			{
				chrDisableReloadToLocation = true;	
				sld = CharacterFromId(pchar.GenQuest.CaptainComission.City + "JailOff");	
				sld.dialog.currentnode = "CapComission_PrisonFree1";
			}	
			pchar.quest.CapComission_ExitFromPrison.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_ExitFromPrison.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_ExitFromPrison.win_condition = "CaptainComission_ExitFromPrison"; 
			DialogExit();
		break;		
		
		case "CaptainComission_380":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			pchar.quest.CaptainComission_PrisonFree_Death.over = "yes";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakCaptain");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PrisonFree");
			pchar.GenQuest.CaptainComission = "CanGetGoods";
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Gracias por el rescate. Vamos a movernos a "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Dat")+", señalaré la ubicación del escondite.  Debemos darnos prisa antes de que los salvajes encuentren el lugar.";	// belamour gen	
			link.l1 = "¿Estás seguro de que podremos recoger toda la carga?";
			link.l1.go = "CaptainComission_381";
		break;
		
		case "CaptainComission_381":
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "Tienes razón, asegúrate de tener suficiente espacio para "+pchar.GenQuest.CaptainComission.GoodsQty+" piezas de "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+". Sería una lástima perder un botín tan valioso con tanta sangre sobre él. No nos darán una segunda oportunidad.";
			link.l1 = "Me encargaré de eso.";
			link.l1.go = "CaptainComission_382";
		break;
		
		case "CaptainComission_382":
			AddQuestRecord("CaptainComission2", "24");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			SetFunctionLocationCondition("CaptainComission_MeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false); 
			SetFunctionTimerConditionParam("CaptainComission_CapEscapeTimer", 0, 0, 1, MakeInt(24 - GetHour()), false);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false; // Откроем выход
			DeleteAttribute(pchar,"TownEscape");
			QuestOpenSeaExit();
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "CaptainComission_383":
			dialog.text = "Capitán, no necesitamos testigos. Por favor, trate de persuadir a estas personas para que abandonen la cala.";
			link.l1 = "Está bien, hagámoslo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialogGetGoods");
		break;
		
		case "CaptainComission_384":
			dialog.text = "Capitán, lo siento, pero este no es el mejor lugar para tus ejercicios. Ese muelle ya está ocupado.";
			link.l1 = "Caballeros, no he venido aquí de turismo. Tengo negocios aquí.";
			link.l1.go = "CaptainComission_385";
		break;
		
		case "CaptainComission_385":
			dialog.text = "Bueno, aquí tampoco estamos cazando medusas, da la vuelta a tus barcos y lárgate al diablo de aquí.";
			link.l1 = "No quiero perder mi tiempo persuadiéndote para que te vayas. O lo haces de buena gana y vives, o te quedas aquí para siempre.";
			link.l1.go = "CaptainComission_386";
		break;
		
		case "CaptainComission_386":
			dialog.text = "Veo que tienes problemas para entender mis palabras. Muy bien, será tu funeral...";
			link.l1 = "¡Eso es mejor!";
			link.l1.go = "CaptainComission_364";
		break;
		
		case "CaptainComission_387":
			LAi_LocationDisableOfficersGen(pchar.GenQuest.CaptainComission.ConvoyShore, false);
			pchar.GenQuest.CaptainComission.MaxGoodsQty = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if(sti(pchar.GenQuest.CaptainComission.MaxGoodsQty) > sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.MaxGoodsQty = pchar.GenQuest.CaptainComission.GoodsQty;
			dialog.text = "Estamos aquí. El escondite está en una grieta en esa peña. La entrada está bloqueada con rocas. En el escondite, hay "+pchar.GenQuest.CaptainComission.GoodsQty+" unidades de "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+". ¿Recuerdas que la mitad es mía?";
			link.l1 = "Claro que sí. Tenemos algo de tiempo mientras mis hombres cargan las mercancías. Hablemos sobre a dónde debemos llevarte a ti y tu carga.";
			link.l1.go = "CaptainComission_388";
			if (!CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{	
			link.l2 = "Muy bien. Ahora dime, ¿hay alguna razón para que comparta?";
			link.l2.go = "CaptainComission_389";
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				link.l3 = "Capitán "+pchar.GenQuest.CaptainComission.Name+", tengo que decirte algo desagradable. Trabajo para el gobernador. Y tengo la intención de entregarle toda la carga que has escondido. Deberías volver a la prisión y esperar allí tu destino.";
				link.l3.go = "CaptainComission_389";
				link.l2 = "Muy bien. Pero aquí está la cosa... Al principio quería entregarte a las autoridades, pero ¿por qué haría eso ahora? Y ¿por qué compartiría contigo?";
			    link.l2.go = "CaptainComission_3899"; // // лесник . отдельный диалог в случае обмана всех.
			}	
		break;
		
		case "CaptainComission_388":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;			
			pchar.GenQuest.CaptainComission.iDay  = 20 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "Necesito llegar a "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+", en "+XI_ConvertString(GetIslandByCityName(sTemp)+"Voc")+" para "+pchar.GenQuest.CaptainComission.iDay+" días.   Mi gente allí   debe haber preparado   la mercancía para vender."; // belamour gen
			link.l1 = "Está bien. Entonces, es hora de partir.";
			link.l1.go = "CaptainComission_391";
		break;
		case "CaptainComission_3899": // лесник . отдельный диалог в случае обмана всех.
		    DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "Correcto. Uno siempre debe confiar en la mente, no en el corazón. Vive y aprende\nAunque no esperaba esto, siempre estoy listo para una pelea. Responderás por tu traición.";
			link.l1 = "Bueno, si tienes suerte...";
			link.l1.go = "CaptainComission_390";
			SetFunctionTimerConditionParam("CaptainComission_NaebalGubera", 0, 0, 1, MakeInt(24 - GetHour()), false);
		break;
		
		case "CaptainComission_389":
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "Correcto. Uno siempre debe confiar en la mente, no en el corazón. Vivir y aprender\nAunque no esperaba esto, siempre estoy listo para una pelea. Responderás por tu traición.";
			link.l1 = "Estoy a su servicio...";
			link.l1.go = "CaptainComission_390";
		break;
		
		
		case "CaptainComission_390":
			LAi_SetPlayerType(pchar);
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_SetImmortal(rChar, false);// лесник.  
			LAi_group_MoveCharacter(rChar, "EnemyFight");		
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors"); 			
			if(pchar.GenQuest.CaptainComission == "CapDuel")
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CaptainDiedDuel");
			}
			else
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CheckCaptainDied");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_391":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			pchar.GenQuest.CaptainComission.CapGoodsQty = sti(pchar.GenQuest.CaptainComission.GoodsQty)/2;
			if(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) > sti(pchar.GenQuest.CaptainComission.MaxGoodsQty)) pchar.GenQuest.CaptainComission.CapGoodsQty = pchar.GenQuest.CaptainComission.MaxGoodsQty;
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))AddQuestRecord("CaptainComission2", "53");// лесник. выбор записи в СЖ
			else AddQuestRecord("CaptainComission2", "26");// смотря по какому пути пошел 
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.MaxGoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum1", pchar.GenQuest.CaptainComission.CapGoodsQty);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sDays", pchar.GenQuest.CaptainComission.iDay);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyIsland + "Gen")); // belamour gen
			OfficersReaction("bad");
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				ChangeCharacterComplexReputation(pchar,"nobility", -5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
			}
			CaptainComission_GenerateCoastalPatrol();
			pchar.GenQuest.CaptainComission = "GetGoodsEscape";
			SetFunctionLocationCondition("CaptainComission_CapMeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission.DeleiveCapShore");	
			DialogExit();
		break;
		
		case "CaptainComission_392":
			dialog.text = "Al parecer, llegamos tarde... Los clientes no esperaron, y no tengo oportunidad de organizar el almacenamiento y la venta de la carga por mí mismo...";
			link.l1 = "¿Tienes alguna propuesta particular al respecto?";
			link.l1.go = "CaptainComission_393";
		break;
		
		case "CaptainComission_393":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Capitán "+GetFullName(pchar)+", sé que es un poco incómodo, pero... ¿podrías darme un equivalente monetario de mi parte? Supongo, "+pchar.GenQuest.CaptainComission.GoodsPrice+" pesos podrían ser un buen compromiso.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				link.l1 = "Sí, es un precio justo. No me importa. Aquí está tu dinero, y adiós.";
				link.l1.go = "CaptainComission_394";
			}
			link.l2 = "Oh, no, mi amigo, eso no servirá. No puedo estar cuidándote para siempre. Si no quieres recoger tu carga, simplemente me la quedaré. Ten por seguro que encontraré maneras de almacenarla y eventualmente venderla.";
			link.l2.go = "CaptainComission_3951";
		break;
		
		case "CaptainComission_394":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			dialog.text = "Espera, capitán. Quiero agradecerte por mi rescate. Sabes, casi había perdido la esperanza... Aquí, estoy seguro de que encontrarás este amuleto bastante útil en muchas situaciones difíciles... Adiós por ahora.";
			link.l1 = "Gracias. No lo esperaba. Un placer hacer negocios contigo.";
			link.l1.go = "CaptainComission_395";
		break;
		
		case "CaptainComission_3951": // лесник . верное назначение диалога
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes";
			dialog.text = "No esperaba eso de ti... Al parecer, no tengo otra opción más que retarte a un duelo.";
			link.l1 = "Estoy a tu servicio...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
		break;
		
		case "CaptainComission_395":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "32");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");	
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_396_0":
			dialog.text = "Capitán, necesito hablar con mis hombres.";
			link.l1 = "Adelante.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_396":
			sld = characterFromId("Blaze");
			dialog.text = "Te saludo, capitán "+GetFullName(pchar)+". Entonces, ¿has traído toda la carga? ¿Y dónde está el capitán "+pchar.CaptainComission.CapName+"?";
			link.l1 = pchar.CaptainComission.CapName+" murió, y fui arrestado por una denuncia. Y si el capitán "+pchar.CaptainComission.FullName+" no me hubiera ayudado, no me habrías visto ni a mí ni a la carga.";
			link.l1.go = "CaptainComission_397";
		break;
		
		case "CaptainComission_397":
			sld = characterFromId("Blaze");
			dialog.text = "Y "+NPCharSexPhrase(sld,"¿quién es él? ¿Es él","¿Quién es ella? ¿Es ella")+"¿al tanto de nuestros asuntos?";
			link.l1 = "Por supuesto. "+NPCharSexPhrase(sld,"Él me sacó","Ella me sacó")+" de la cárcel y se comprometió a entregarme aquí la mitad del cargamento; la otra mitad se la prometí "+ NPCharSexPhrase(sld, "","") +" como compensación.";
			link.l1.go = "CaptainComission_398";
		break;
		
		case "CaptainComission_398":
			sld = characterFromId("Blaze");
			dialog.text = "Eh, capitán, de ninguna manera. ¡Es tu problema! Sugerí que nos lleváramos el barco, pero tú te preocupabas demasiado por tu maldita carrera. Y aquí estás, tu amado gobernador te tiene en prisión."+" ¡Tu parte fue mucho menor que la mitad! ¡No pusimos nuestras cabezas bajo las descargas de metralla para que te lleves la mitad entera para ti mismo!";
			link.l1 = "Escucha, contramaestre, ¿no recuerdas que el barco estaba completamente destrozado? ¿Que casi estaba bajo el agua? ¿No entiendes que si no le hubiera dado a este hombre la mitad, nunca habrías vuelto a ver ni un pequeño trozo de la carga?";	
			link.l1.go = "CaptainComission_399";
		break;
		
		case "CaptainComission_399":
			dialog.text = "¡No me engañarás! ¿Cómo podríamos saber que no estabas en colusión? ¿Y si no hubo arresto en absoluto? ¿Y si simplemente fuiste demasiado codicioso y decidiste robar nuestras pertenencias? ¿O piensas que hemos olvidado cómo manejar una espada?!";
			link.l1 = "Veo que te has vuelto loco. No oyes nada más que el tintineo de las monedas en tus oídos.";
			link.l1.go = "CaptainComission_400";
		break;
		
		case "CaptainComission_400":
			sld = characterFromId("Blaze");
			dialog.text = "¡Chicos! ¡Mirad cómo está hablando ahora nuestro capitán! ¡De hecho, la avaricia lo ha consumido por completo! ¡Vendió nuestra parte a "+NPCharSexPhrase(sld,"un bribón","una aventurera")+"¡¡";
			link.l1 = "¡Cierra esa bocaza ahora, o te haré callar para siempre!";
			link.l1.go = "exit";
			AddDialogExitQuest("CaptainComission_ShoreGangDialog");
		break;
		
		case "CaptainComission_401":
			dialog.text = "Lamento, capitán, que haya tenido que presenciar esta escena ridícula e incluso participar en ella. Cuesta creer que hace apenas un mes éramos una tripulación unida, y cada uno de nosotros con gusto sacrificaría su vida para salvar a un amigo.";
			link.l1 = "Debo admitir que no puedo imaginar eso, sin ofender.";
			link.l1.go = "CaptainComission_402";
		break;
		
		case "CaptainComission_402":
			dialog.text = "Lamentablemente, no tengo la oportunidad de organizar el almacenamiento y la venta de la carga por mi cuenta...";
			link.l1 = "¿Tienes alguna proposición particular al respecto?";
			link.l1.go = "CaptainComission_403";
		break;
		
		case "CaptainComission_403":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Capitán "+GetFullName(pchar)+", sé que es un poco incómodo, pero... ¿podrías darme el equivalente monetario de mi parte? Supongo, "+pchar.GenQuest.CaptainComission.GoodsPrice+" pesos podrían ser un buen compromiso.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				pchar.quest.CaptainComission_Capitan_Cdox.over = "yes"; // на всякий случай .лесник
				pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник
				link.l1 = "Está bien, no me importa. Aquí tienes tu dinero, y adiós.";
				link.l1.go = "CaptainComission_404";
			}	
			link.l2 = "No, eso no funcionará. Puedes llevarte tu cargamento o dejarlo en la bodega, pero no te daré ni una sola moneda.";
			link.l2.go = "CaptainComission_405";
		break;
		
		case "CaptainComission_404":
			bTemp = false;
			if(hrand(1) == 0)
			{
			    NPChar.reputation = 60 + rand(20); 
				NPChar.alignment = "good"; 
			}	
			else
			{
			    NPChar.reputation = 10 + rand(20); 
				NPChar.alignment = "bad"; 			
			}
			if (NPChar.alignment == "good" && sti(pchar.reputation.nobility) > 50) bTemp = true; 
			if (NPChar.alignment == "bad" && sti(pchar.reputation.nobility) <= 50) bTemp = true;
			
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			
			if(!bTemp || FindFreeRandomOfficer() < 0)
			{
				dialog.text = "Espera, capitán. Quiero agradecerte por mi rescate. Sabes, casi había perdido la esperanza... Aquí, estoy seguro de que encontrarás este amuleto bastante útil en muchas situaciones difíciles... Adiós por ahora.";
				link.l1 = "Gracias. No lo esperaba. Un placer hacer negocios contigo.";
				link.l1.go = "CaptainComission_406";
			}
			else
			{
				dialog.text = "Espera... Acabo de pensar... Sabes, mi carrera ha terminado ahora, no tengo tripulación y estoy exiliado en mi tierra natal. Seguramente necesitarás hombres de confianza con mano firme, que sepan mantener la boca cerrada. Por favor, acéptame en tu tripulación, prometo que no te arrepentirás.";
				if(!CaptainComission_CheckAllPassengersHired())
				{
					link.l1 = "Para ser honesto, he estado esperando tu acuerdo por un tiempo. Claro. Nos vemos a bordo.";
					link.l1.go = "CaptainComission_407";
				}	
				link.l2 = "Hmm... sabes, me parece que eres demasiado listo para estar sirviendo a alguien. Adiós...";
				link.l2.go = "CaptainComission_408";
			}
		break;
		
		case "CaptainComission_405":
			dialog.text = "Bueno, aparentemente, hoy claramente no es mi día de suerte... Está bien, capitán, desenvainemos nuestras espadas y terminemos con todo de una vez...";
			link.l1 = "Estoy a tu servicio...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
			pchar.GenQuest.CaptainComission.Duel = true;
		break;
		
		case "CaptainComission_406":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "34");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
	
		
		case "CaptainComission_407":	
			AddQuestRecord("CaptainComission2", "36");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");		
			npchar.CaptainComission = true;
			SetCharacterRemovable(Npchar, true);
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
			NPChar.Dialog.CurrentNode = "hired";
            NPChar.greeting = "Gr_Officer"; 			
			NPChar.quest.OfficerPrice = sti(pchar.rank)*500;	
			NPChar.loyality = MAX_LOYALITY;
			DeleteAttribute(NPChar, "LifeDay");
			NPChar.id = "GenChar_" + NPChar.index;// лесник . смена ИД при взятии в оффы. 
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(NPChar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired"); 
			NPChar.quest.meeting = true; 
			DialogExit();
		break;		
		
		case "CaptainComission_408":
			AddQuestRecord("CaptainComission2", "35");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);						
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;		
		// Генератор "Operation 'Galleon'"
		
		// Квест "meeting in the cove" -->
		// Офицер
		case "ContraMeetManQuest_Sold_1":
			dialog.text = "Ninguno de tus asuntos. Ahora dime, ¿qué andas husmeando aquí? ¿No estás buscando a un hombre que acaba de ser detenido?!";
				link.l1 = "¿Un hombre?! No...";
				link.l1.go = "ContraMeetManQuest_Sold_2";
			break;
			
		case "ContraMeetManQuest_Sold_2":
			dialog.text = "Bien por ti. De lo contrario, también irías a prisión junto con él. Así que no te metas por aquí, marinero. ¡Lárgate!";
				link.l1 = "Sí, será mejor que me vaya...";
				link.l1.go = "ContraMeetManQuest_Sold_3";
			break;
			
		case "ContraMeetManQuest_Sold_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteQuestCondition("ContraMeetManQuest_TimeIsLeft"); // Время больше не роляет
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "8");
			PChar.GenQuest.ContraMeetMan.ToTavernPatrolInShore = true;
			LAi_CharacterDisableDialog(NPChar);
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			ContraMeetManQuest_DeletePatrolFromShore(); // По выходу потрем всех из локации
			break;
			
		// Сам чел
		case "ContraMeetManQuest_1":
			dialog.text = "¡Estupendo! Deberíamos dirigirnos a la taberna con ese contrabandista ahora. ¡No quisiera quedarme aquí!";
				link.l1 = "Sin problema con eso. Vamos...";
				link.l1.go = "ContraMeetManQuest_2";
			break;
			
		case "ContraMeetManQuest_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorFollowEverywhere(NPChar, "", -1);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "3");
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			PChar.GenQuest.ContraMeetMan.ToTavernWithMan = true;
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			break;
		
		// Контрики в комнате таверны	
		case "ContraMeetManQuest_3":
			ContraMeetManQuest_ContersGoQut();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "4");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ChangeContrabandRelation(PChar, 5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "5");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContraBeatMan();
			ChangeContrabandRelation(PChar, 5);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_5":
			dialog.text = "Je-je... Parece que, "+GetSexPhrase("compañero","moza")+", te irás al infierno con él muy pronto... ¡Oye, compañero, vamos a destriparlos a ambos!";
				link.l1 = "¡Cerdo asqueroso! ¡Defiéndete!";
				link.l1.go = "ContraMeetManQuest_6";
			break;
			
		case "ContraMeetManQuest_6":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraMeetManQuest_PlayerBeatContra();
			break;
			
		case "ContraMeetManQuest_7":
			dialog.text = "Gracias una vez más, "+PChar.name+". Adiós...";
				link.l1 = "...";
				link.l1.go = "ContraMeetManQuest_9";
			break;
			
		case "ContraMeetManQuest_8":
			iMoney = (rand(3)+2)*500;
			PChar.GenQuest.ContraMeetMan.Money = iMoney;
			dialog.text = "¿Una recompensa?! Oh, claro. Aquí, toma "+FindRussianMoneyString(iMoney)+" y adiós...";
				link.l1 = "Adiós...";
				link.l1.go = "ContraMeetManQuest_10";
			break;
			
		case "ContraMeetManQuest_9":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "6");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoney));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_10":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "7");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
		// <-- Квест "meeting in the cove"
			
		// Квест на доставку письма контрику -->
		case "ContraDeliverQuest_Sold1":
			dialog.text = "¡Heh! ¿Esperas que creamos esa mierda?! ¡Chicos, apresad a estos dos pájaros de horca!";
			//if(80 > rand(100) || sti(PChar.skill.Fortune) > rand(100)) // Попытка отмазаться
			//{
				link.l1 = "Oficial, está cometiendo un grave error al intentar detener a dos personas inocentes. Créame, no conozco a ese hombre y me importa un bledo."+" Estoy seguro de que su comandante estará muy disgustado con usted, si detiene a dos ciudadanos respetuosos de la ley...";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty";
			//}
			/*else // Тюрьма
			{
				link.l1 = "";
				link.l1.go = "ContraDeliverQuest_Sold2_Prison";
			}*/
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty":
			dialog.text = "Hmm... Sí, quizás tengas razón. El comandante seguramente estará disgustado con eso. ¿Sabes qué? Olvidemos este pequeño incidente.";
				link.l1 = "Gracias, oficial, nos ha ahorrado tiempo. Me gustaría pedirle que sea más cuidadoso la próxima vez, seguramente no querrá ser degradado, ¿verdad?";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty1";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty1":
			dialog.text = "No, de ninguna manera. En ese caso, por favor, dispérsense. Nos vemos...";
				link.l1 = "¡Eso es mejor!";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty2";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraDeliverQuest_SoldiersGoOut();
			break;
		
		case "ContraDeliverQuest_1":
			iMoney = (rand(3)+2)*500;
			if(rand(1) == 0) // Денег не даёт
			{
				dialog.text = "¡Excelente! ¡Y ahora puedes perderte!";
					link.l1 = "¿Qué?! ¿Y qué pasa con el dinero? Teníamos un trato...";
					link.l1.go = "ContraDeliverQuest_NoMon";
			}
			else // Деньги или патруль
			{
				if(rand(2) == 1) // Патруль
				{
					dialog.text = "Gracias por la entrega. Ahora puedes largarte... espera, alguien viene...";
						link.l1 = "¿Qué?!";
						link.l1.go = "ContraDeliverQuest_Patrol";
				}
				else // Просто отдает деньги
				{
					dialog.text = "Estupendo. Gracias por la entrega. Aquí, toma "+FindRussianMoneyString(iMoney)". Y ten en cuenta que los contrabandistas siempre recordarán a la buena gente...";
					link.l1 = "Eso espero. Adiós.";
					link.l1.go = "ContraDeliverQuest_GoWithMoney";
					PChar.GenQuest.ContraDeliver.Money = iMoney;
				}
			}
			
			ChangeContrabandRelation(PChar, 5); // Письмо доставили - повышаем отношение у контриков
			ChangeCharacterComplexReputation(pchar,"nobility", -5); // Помогли контрикам - репу понижаем
			RemoveItems(PChar, "letter_1", 1);
			BackItemDescribe("letter_1");
			DeleteAttribute(&Items[FindItem("letter_1")], "City");
			rChar = &Characters[GetCharacterIndex(Locations[FindLocation(PChar.location)].townsack + "_Smuggler")];
			SaveCurrentNpcQuestDateParam(rChar, "work_date");
			break;
			
		case "ContraDeliverQuest_Patrol":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_LocationFightDisable(LoadedLocation, true); // Чтоб не поубивали кого-нить
			ContraDeliverQuest_GeneratePatrolToRoom();
			break;
			
		case "ContraDeliverQuest_NoMon":
			dialog.text = "Escucha... tú y yo no teníamos ningún trato entre nosotros. Reclama tu dinero de quien hizo ese trato contigo.";
				link.l1 = "Bueno, ¡definitivamente no es mi día de suerte, ¿qué más puedo decir?! Está bien, nos vemos...";
				link.l1.go = "ContraDeliverQuest_GoWithoutMoney";
				link.l2 = RandSwear()+"¡Responderás por eso! ¡Prepárate para morir!";
				link.l2.go = "ContraDeliverQuest_PrepareToFight";
			break;
			
		case "ContraDeliverQuest_GoWithoutMoney": // Уходим без денег
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			PChar.GenQuest.ContraDeliver.Complete.WithoutMoney = true;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "4");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ContraDeliver.QuestTown));
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
			
		case "ContraDeliverQuest_PrepareToFight":
			dialog.text = "¿Te atreves a desafiarme, "+GetSexPhrase("cachorro","escoria")+"? No tienes ni idea de lo que es bueno para ti. ¡Te destriparé!";
				link.l1 = "...";
				link.l1.go = "ContraDeliverQuest_Fight";
			break;
			
		case "ContraDeliverQuest_Fight": // Бой
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetImmortal(NPChar, false);
			LAi_ActorAttack(NPChar, PChar, "");
			LAi_SetFightMode(PChar, true);
			SetFunctionNPCDeathCondition("ContraDeliverQuest_ContraIsDead", NPChar.ID, false);
			break;
			
		case "ContraDeliverQuest_GoWithMoney": // Уходим с деньгами
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraDeliver.Money));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "3");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraDeliver.Money)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ContraDeliver"); // Квест пройден - атрибуды потрем
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
		// <-- Квест на доставку письма контрику
			
		// Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем -->
		case "ChurchGenQuest_1_DeckDialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern")) // Если ждёт в таверне
				{
					dialog.text = RandPhraseSimple("¡Medio millar de hombres! ¡Y un muerto en el cofre! ¡Hic!","¡Bebe! ¡Hic! Y el diablo se encargó del, ¡Hic!... resto.");
						link.l1 = "Ohh... Bueno. Hola, señor "+GetFullname(NPChar)+".";
						link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_2";
						PChar.Quest.Church_GenQuest1_Timer.over = "yes";
				}
				else // на палубе своего шипа
				{
					if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
					{
						dialog.text = "Está bien, veamos ahora... Tres piezas de lona, tablones para el casco del barco, reemplazar las jarcias y cuerdas de las brazas...";
							link.l1 = "Hola, señor "+GetFullName(NPChar)+". Soy el capitán "+PChar.name+".";
							link.l1.go = "ChurchGenQuest1_DialogShip_1";
					}
					else
					{
						dialog.text = LinkRandPhrase("¡Deja mi barco inmediatamente, tengo mucho que hacer sin ti!","¡Has recibido tus libros, ¿qué más quieres?!","¡Hice todo lo que querías, ¿qué más quieres de mí?!");
							link.l1 = "¡No te entusiasmes tanto o te dará un ataque al corazón!";
							link.l1.go = "exit";
					}					
				}
			}
			else
			{
				dialog.text = RandPhraseSimple("¡Ron, ron! Dame ron... ¡Hic!","Ha pasado un tiempo... hic... desde que me embriagué así...");
					link.l1 = "Sí, tu bodega está llena... ¿tal vez sea hora de dirigirse a una cala?";
					link.l1.go = "exit";
			}			
			NextDiag.TempNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_2":
			dialog.text = RandPhraseSimple("¡Por favor, tome asiento, cap... hic... tán! ¿Cuál es tu veneno?","¡Siéntate, capitán! ¿Qué te gustaría beber? Hip...");
					link.l1 = "Gracias, pero preferiría una buena conversación con un hombre decente.";
					link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_3";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_3":
			dialog.text = "¿Estás tratando, ¡hip!... de insultarme?... ¡No hay ni un solo hombre decente en esa taberna! ¡Hip! ¡Solo bandidos y asesinos! ¡Todos ellos extorsionistas, y ese... el primero entre ellos! ¡Su cabecilla, una morena en su garganta!";
				link.l1 = "Me refiero a ti. Tú eres con quien deseo hablar. ¿Y quién es el líder de los bandidos y por qué él...?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_4";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_4":
			dialog.text = "Señor"+GetSexPhrase("","ita")+", ¿cuál era tu nombre, una vez más? ¡Te respeto! ¡Nadie ha llamado a un viejo lobo de mar un hombre decente hasta ahora! ¡Haría cualquier cosa por ti! ¡Te daría todo mi dinero, hasta el último peso!... Oh, lo olvidé. Estoy sin dinero. Ni siquiera me quedan roolies. Ese bastardo, ese extorsionador me quitó hasta la última chuchería, ¡que los diablos carguen sus cañones con sus tripas en el infierno!";
				link.l1 = "¿Señor capitán? ¿Está bien? Creo que está delirando. Vine a preguntarle por unos libros.";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_5";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_5":
			dialog.text = "¡No, no! Este viejo capitán puede estar borracho, pero aún conserva su ingenio. Los libros y los pergaminos me los dio el Padre "+PChar.GenQuest.ChurchQuest_1.ToName+", los estaba llevando a "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+". Y por la mañana fui a la iglesia y mencioné estos libros al padre. Por supuesto, él quería verlos, ya sabes cómo son, están locos por las vidas de los santos y todo ese rollo. Así que envié a un grumete a buscar el cofre con ellos. Y mientras esperaba, decidí apostar un poco... y de alguna manera perdí todo mi dinero. ¡Todo! ¡Nada con qué pagar el licor! Así que el tabernero tomó los libros en prenda, y luego también le di los pergaminos...";
				link.l1 = "Entonces, vendiste los libros, los libros sagrados que te confió el sacerdote  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Gen")+"...";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_6";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_6":
			dialog.text = "Lo sé, lo sé... Me quemaré en el Infierno por toda la eternidad. Ahora no puedo mostrar mi cara ni al Padre, que me dio esa tarea, ni a quien debía entregar los papeles... ¿Quién rezará ahora por mi alma? ¿Y si me excomulgan? Ay, pobre de mí... Necesito un trago... ";
				link.l1 = "¡Guau, relájate, no es tan malo! Tus acciones fueron pésimas e impías, y sin embargo estoy dispuesto a ayudarte. Pagaré tu deuda y compraré estos manuscritos. Además, como ya conozco a ambos sacerdotes mencionados, navegaré directamente hacia "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+" para entregar los documentos allí. ¿Trato hecho?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_7";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_7":
			dialog.text = "¡Salvador! Ángel de Dios... ¡Por supuesto, estoy de acuerdo! Te daría todo... ¡todo! Si tan solo pudiera tomar otra bebida...";
				link.l1 = "Supongo que ya has tenido suficiente... Oh, lo que sea. Te compraré más ron del tabernero.";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_8";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_8":
			DialogExit();
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap");
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithBarmen = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7_2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			NextDiag.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogShip_1":
			dialog.text = "...¡y las sábanas! Tenemos que reemplazar las sábanas también... Oh, hola. Por favor, no se ofenda, señorita"+GetSexPhrase("ter","s")+" como-te-llames, pero ahora mismo, como puedes ver, estoy bastante ocupado, así que si tienes asuntos conmigo, por favor, sé rápido.";
				link.l1 = "Por lo que sé, padre "+PChar.GenQuest.ChurchQuest_1.ToName+" te dio algunos papeles sagrados en "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Voc")+". Prometiste entregárselos a "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+" porque de todas formas navegabas en esa dirección."; // belamour gen
				link.l1.go = "ChurchGenQuest1_DialogShip_2";
			break;
			
		case "ChurchGenQuest1_DialogShip_2":
			dialog.text = "Me dirigía en esa dirección, hasta que esa maldita tormenta casi destruyó mi viejo cascarón, ¡y me quedé atrapado aquí por quién sabe cuánto tiempo! Esos estafadores en los muelles siguen intentando colarme tablones podridos arrastrados por la marea para el casco del barco, y para las velas, algo de arpillera vieja, en la que sus abuelas dormían cuando aún eran jóvenes.";
				link.l1 = "Señor, la próxima vez escucharé con gusto sus magníficas historias, pero ahora me gustaría saber más sobre el destino de los libros y manuscritos que ha recibido en "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Dat")+".";
				link.l1.go = "ChurchGenQuest1_DialogShip_3";
			break;
			
		case "ChurchGenQuest1_DialogShip_3":
			dialog.text = "Nadie, ¿me oyes? ¡Nadie se atreve a culparme por el retraso en la entrega de estos malditos papeles!";
				link.l1 = "¡Oh, no, ciertamente no quise decir eso. Solo quería aliviar tu carga. La cosa es que "+PChar.GenQuest.ChurchQuest_1.ToName+" está bastante preocupado por los libros y papeles que deben ser entregados a "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+"De hecho, voy a navegar allí ahora mismo.";
				link.l1.go = "ChurchGenQuest1_DialogShip_4";
			break;
			
		case "ChurchGenQuest1_DialogShip_4":
		if(rand(3) != 1)
		{
			dialog.text = "Me parece, mis"+GetSexPhrase("ter","s")+", que tienes un consejero espiritual en cada puerto. Aunque eso no es de mi incumbencia. ¡Si te importa esa porquería, entonces agarra tus libros y piérdete! ¡Que te vaya bien!";
				link.l1 = "Gracias, señor capitán. Buena suerte con sus reparaciones.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_1";
		}
		else // Свитки не отдает
		{
			dialog.text = "No te preocupes por eso, mis"+GetSexPhrase("ter","s")+", y viaja a "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+" a la ligera, ya que fui yo quien se comprometió a entregar esos documentos, y seré yo quien lo haga a toda costa, para que nadie grite en cada esquina que el capitán "+NPChar.name+" ¡no fue fiel a su palabra!";
				link.l1 = "Pero señor capitán, el punto en realidad es...";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2";
		}
			break;
			
		case "ChurchGenQuest1_DialogShip_5_1":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2":
			dialog.text = "En realidad, el punto es que no tengo ningún asunto contigo. El Santo Padre me encargó una tarea, entregar los libros a "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+" y entrégaselos al cura. Y no te veo allí. ¡Para nada! Buena suerte.";
//				link.l1 = "Está bien, entonces. Eres un hombre muy responsable, aunque es tu único mérito. Buena suerte, mi descortés amigo";
//				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_1"; // Сваливаем, поверили ему
				link.l2 = "He tenido suficiente de tu comportamiento insolente. Tu boca estúpida puede forzar incluso a un ángel a cometer violencia. ¡Debo cumplir la voluntad de mi santo padre y usaré mi arma si es necesario!";
				link.l2.go = "ChurchGenQuest1_DialogShip_5_2_2"; // 
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_1":
			DialogExit();
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "11");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete.NoManuscripts = true; // Квест выполнен без манускриптов
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_2":
			dialog.text = "Tranquilo, tranquilo, capitán "+PChar.name+". ¿Qué te pasa? Bueno, veo que si no traes estos papeles, todos esos Santos Padres estarían bastante enfadados contigo, por no mencionar a nuestro Padre en el Cielo. Muy bien, lleva tus tesoros teológicos y ve con la bendición de Dios.";
				link.l1 = "Alegre de que no solo hayas entendido mi posición, sino que también hayas recordado mi nombre. Te sugiero que lo recuerdes cada vez que estés a punto de hacer algo tonto.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_3"; // Сваливаем, поверили ему
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_3":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		// <-- Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем
			
		case "Left_Time_Case":
			dialog.text = RandPhraseSimple("Piérdete...","¡No me molestes!");
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Left_Time_Case";
			break;
			
		case "Church_GenQuest_2_1":
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 1)
			{
				dialog.text = RandSwear()+"¡No debiste haber dicho eso! ¡Ahora tendré que enviarte al Señor para que reces por el perdón de mis pecados!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 2)
			{
				dialog.text = RandSwear()+"¡No deberías haber dicho eso! ¡Ahora tendré que enviarte al Señor para que ores por el perdón de nuestros pecados!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) > 2)
			{
				dialog.text = RandSwear()+"¡No deberías haber dicho eso! ¡Ahora tendré que enviarte al Señor para que reces por el perdón de todos nuestros pecados!";
			}
			
				link.l1 = "Apenas, compañero. ¡Todos responderán por sí mismos ante Dios!";
				link.l1.go = "exit";
				NPChar.money = sti(PChar.GenQuest.ChurchQuest_2.MoneyCount);
				LAi_LocationFightDisable(LoadedLocation, false);
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_1":
			dialog.text = "Eh, ¿por qué maldecir? ¿Y si tengo negocios contigo?";
				link.l1 = "¡Eso sí que es noticia! ¡Sabes, tengo conversaciones breves con tipos como tú!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_2";
				LAi_LocationFightDisable(LoadedLocation, false);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_2":
			dialog.text = "Bueno, tampoco voy a tener largas charlas contigo. Pero, quizás, te interese comprar un par de baratijas a buen precio.";
				link.l1 = "¿Tengo pinta de ser un maldito receptor de bienes robados?!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_3":
			if(rand(1) == 0)
			{
				dialog.text = "Tranquilo, tranquilo, ¡no hay ladrones entre nosotros! ¡Este jarrón nos fue dado por trabajo honesto! Sólo mira... oro puro, adornado con perlas. Pero el punto es que no lo necesitamos. Así que solo queremos venderlo y repartir el dinero.";
					link.l1 = "Déjame echar un vistazo más de cerca... ¡Ay, madre mía! ¡Esta es la copa de la comunión! ¡Entonces, sois esos blasfemos que han saqueado la iglesia de "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+"¡¿Ahí estás?!";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_4";
					break;
			}
		
			dialog.text = "Silencio, señorita"+GetSexPhrase("ter","s")+" ¡Hipócrita! Sabes, estamos un poco cortos de dinero, así que decidimos vender algo. Echa un vistazo a este jarrón... oro puro, adornado con perlas. Precio especial para ti, digamos, mil monedas.";
				link.l1 = "Déjame echar un vistazo más de cerca... ¡Ay, Dios mío! ¡Esta es la copa de comunión!!! Entonces, sois esos blasfemos que han saqueado la iglesia de "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+"¿¡Ahí estás!?";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_1";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_4":
			dialog.text = "Detén tus caballos, mis"+GetSexPhrase("ter","s")+"¡.. Maldita sea, le dije a ese cabeza de chorlito que no armara un escándalo hasta que fuera el momento adecuado...";
				link.l1 = "¿Qué estás balbuceando? Muy bien, haz tu elección: o me das tu botín robado voluntariamente, o llamo a los guardias.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_5";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_5":
			dialog.text = "Escucha, "+GetSexPhrase("buen hombre","jovencita")+", no necesitamos ninguna pelea, así que resolvamos este asunto pacíficamente. Debes creerme, no saqueamos esa iglesia, ni tampoco tenemos dinero. Sí, hemos recibido varios pesos y ese baratillo dorado por simular el robo. Y esta copa dorada fue lo único que nos quedó después de pagar a los contrabandistas...";
				link.l1 = "Entonces, estás tratando de decir que...";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_6";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_6":
			dialog.text = "¡Ese maldito sacerdote nos contrató, eso es lo que estoy diciendo! Pero ¿por qué tuvo que enviarte a ti en nuestro camino?.. Bueno, ahora estamos a mano. Toma este jarrón y muéstraselo a ese hipócrita, verás por ti mismo cómo se retorcerá como un calamar en el bajío.";
				link.l1 = "Dame la copa y piérdete, antes de que cambie de opinión.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_7";
				link.l2 = "Hablas con suavidad, pero no soy tan fácil de engañar. Si quieres convencerme, primero convence a mi espada.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_8";
				// Тут давать чашу, если будет
				ChurchGenQuest2_GiveCup();
				PChar.GenQuest.ChurchQuest_2.Complete.PriestIsThief = true;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_7":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
				LAi_ActorRunToLocation(rChar, "reload", "reload1_back", "none", "", "", "", -1);
			}
			
			// Разрешим генерацию энкаунтеров, откроем выходы
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_1");
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_2");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_1":
			if(PChar.GenQuest.ChurchQuest_2.BanditsCount == 1)
			{
				dialog.text = RandSwear()+"¿No les dije a esos desgraciados: mantengan sus manos codiciosas y no tomen nada más que dinero del cura?";
			}
			else
			{
				dialog.text = RandSwear()+"¿No les dije a esos insaciables carajos: mantengan sus manos codiciosas y no tomen nada más que dinero del sacerdote?";
			}
			
					link.l1 = "¿Qué estás balbuceando? Muy bien, elige: o me entregas tu botín robado de buena gana, o llamo a los guardias.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2":
			dialog.text = "Estoy tomando una decisión diferente, cierra tu bocaza y dame tu bolsa, y te perdonaré la vida.";
				link.l1 = "¡Te ayudaré a conseguir una audiencia con nuestro Señor ahora!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_1";
				link.l2 = "Está bien, te daré algo de dinero, pero sólo por mi propia voluntad, para que tú y tus amigos podáis llevar una vida honesta y no tengáis que degradaros con el robo.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_2";
				link.l3 = "Eh... Está bien, dejemos nuestras diferencias a un lado y volvamos al comienzo de nuestra conversación. Entonces, ¿cuánto querías por esa cosa?";
				link.l3.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_1":
			// Не забыть чашу!
			ChurchGenQuest2_GiveCup();
			PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
			NPChar.money = ((rand(3) + 6) * 1000);
			PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_2":
			AddMoneyToCharacter(PChar, -sti(PChar.money)/2); // Забираем половину денег
			PChar.GenQuest.ChurchQuest_2.Complete.Without_All = true; // Полностью проигрышный вариант. Остаемся ни с чем
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "First time";
			}
			
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "11_2");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3":
			iMoney = makeint(makeint(Pchar.money)/20)*10;
			dialog.text = "No necesito problemas, tampoco, "+GetAddress_Form(pchar)+", pero ahora el precio ha subido. Por esa copa preciosa requeriré todo lo que llevas contigo.";
			if(iMoney >= makeint(Pchar.rank)*300)
			{
				link.l1 = "¡Escoria codiciosa! Solo tengo "+FindRussianMoneyString(iMoney)+"conmigo. ¡Tómalo y piérdete!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1";
			}
			else
			{
				link.l1 = "Elección incorrecta, rata codiciosa. ¡No sacarás provecho a mi costa!"+GetSexPhrase(" Soy libre como el viento... hoy aquí, mañana allá; hoy soy pobre, mañana seré rico...","")+"";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2";
			}
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_GiveCup();	// Даем чашу
			AddMoneyToCharacter(PChar, -(makeint(makeint(Pchar.money)/20)*10));
			PChar.GenQuest.ChurchQuest_2.Complete.Only_With_Cup = true;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "Left_Time_Case"; // Диалог не забыть поменять.
			}
			
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_3");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2":
			dialog.text = "¿No estarás tratando de decir que justo hoy "+GetSexPhrase("no tienes dinero","no tienes dinero")+"?";
				link.l1 = "Exactamente, mi codicioso amigo, para tu gran decepción. Y ahora debo disculparme, tengo mucho que hacer.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3";	
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3":
			dialog.text = "¡Detente! Vamos a comprobar eso, y si no has dicho la verdad, ¡meteré tu lengua mentirosa en una colonia de hormigas!";
				link.l1 = "¡Después de decir eso, estás acabado!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4";
			break;
			
		// Можно этот кэйс - Church_GenQuest_2_ShoreBandit_Real_Band_2_1
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4":
				// ГГ как-бы может обыскать трупики и забрать все барахло...
				PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
				NPChar.money = ((rand(3) + 6) * 1000);
				PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
				sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
				AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_4");
				AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("Soy honesto, como un verdadero caballero","Soy honesta"));
			break;
			
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// ГЕНЕР "PIRATES ON AN UNINHABITED ISLAND"
		///////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "PiratesOnUninhabited_1":
			dialog.text = "Oh, no hay nada que decidir. Podemos decidirlo todo por nosotros mismos. Pero tomaremos tu barco y nos largaremos de aquí.";
			link.l1 = "Hay una condición, primero tendrás que quitarme mi espada...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_2":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				LAi_SetImmortal(CharacterFromID("PirateOnUninhabited_" + i), false);
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_3":
			PChar.GenQuest.PiratesOnUninhabited.MainPirateName = GetRandName(NAMETYPE_NICK, NAME_GEN);
			PChar.GenQuest.PiratesOnUninhabited.BadPirateName = GetRandName(NAMETYPE_ORIG, NAME_NOM);
			
				i = PiratesOnUninhabited_GenerateShipType();
				PChar.GenQuest.PiratesOnUninhabited.StartShipType = i;
			
			if(hrand(1) == 0)
			{
				PChar.GenQuest.PiratesOnUninhabited.Shipwrecked = true;
				
				dialog.text = "¡Hola, capitán! Aparentemente, la Providencia misma te envió a salvar "+PChar.GenQuest.PiratesOnUninhabited.MainPirateName+" y sus muchachos. Aquí estamos en grave necesidad."+"Nuestra "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[i].Name))+"se estrelló en la tormenta en los arrecifes locales, y las olas arrastraron a la orilla a los sobrevivientes de la tripulación."+"Por "+(5+hRand(7))+" semanas habíamos estado mirando el horizonte con la esperanza de ver la vela de un barco que vendría a rescatarnos.";
				link.l1 = RandPhraseSimple(RandPhraseSimple("Sí, ese es un destino poco envidiable. Pero tal es la suerte de la vida de un marinero, cualquiera podría terminar en tu lugar.","Ya veo... Dios sostiene cada vida, es solo que está demasiado ocupado para recordar a todos."),RandPhraseSimple("Efectivamente. El hombre propone, pero Dios dispone.","Sí, eso fue sin duda un golpe de mala suerte."));
				link.l1.go = "PiratesOnUninhabited_4";
			}
			else
			{
				dialog.text = "¡Fue muy serio! Ese bribón "+PChar.GenQuest.PiratesOnUninhabited.BadPirateName+" no pudo pensar en otro castigo que no fuera marcharse "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_ACC)+" en una isla deshabitada, ¡como un perro sarnoso! "+"¡Él esperaba que el sol y la sed nos secaran como un macarelo seco en el puesto de un pescador! Pero se equivocó, porque la Providencia misma estaba de nuestro lado, ya que te envió aquí para rescatarnos...";
				link.l1 = RandPhraseSimple("No tan rápido, amigo. Por lo que puedo decir, sois hombres de una profesión libre, y no habéis terminado aquí por accidente.","¿Ya hablando de salvación? Por lo que entiendo, estás aquí por algunos logros especiales.");
				link.l1.go = "PiratesOnUninhabited_41";
			}
		break;
		
		case "PiratesOnUninhabited_4":
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = 5 + hrand(5);
			
			dialog.text = RandPhraseSimple("Capitán, por favor, sea un alma bondadosa y ayude "+PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))+" hombres desamparados. Eres nuestra única esperanza, salvo nuestro más gracioso Señor.","Capitán, ¿tendría taquillas libres en su barco para "+PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))+" ¿hombres indigentes?");
			
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l1 = "Ohh... ¿y adónde quieres que te lleve?";
				link.l1.go = "PiratesOnUninhabited_5";
			}
			
			link.l2 = RandPhraseSimple(RandPhraseSimple("Lamento mucho, pero no hay ni una sola hamaca libre, y mucho menos camarotes. Los marineros duermen en la cubierta, ni siquiera pueden descansar bien por la noche después de una guardia...","Realmente odiaría decepcionarte, pero el barco está sobrecargado, y la gente tiene que dormir en el mal tiempo. Si hubiera un brote de enfermedad, perdería a la mitad de la tripulación."),RandPhraseSimple("Lamento mucho, pero no hay absolutamente ningún espacio libre para tripulación en mi barco. No puedo llevar a bordo a más pasajeros.","Tengo que decepcionarte, pero mi barco está sobrecargado de tripulantes. Temo la epidemia..."));
			link.l2.go = "PiratesOnUninhabited_21";
			
			if(stf(PChar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "Eres un marinero experimentado y deberías saber que la presencia de alguien que ha sufrido un naufragio es un muy mal augurio. Mis marineros simplemente os arrojarán a todos por la borda.";
				link.l3.go = "PiratesOnUninhabited_7";
			}
		break;
		
		case "PiratesOnUninhabited_5":
			dialog.text = "Hmm... Sabes, por varias razones nos gustaría mantenernos lo más lejos posible de las autoridades... Por favor, llévanos a cualquier cala en una isla habitada o en el continente, y luego podremos valernos por nosotros mismos.";
			link.l1 = "Bueno, tengo suficientes cofres y hamacas libres. Súbete al bote.";
			link.l1.go = "PiratesOnUninhabited_10";
			link.l2 = "Hmm... mala suerte... Tenemos batallas por delante, y no sé dónde estarás más seguro, a bordo de mi barco o en esta acogedora cala.";
			link.l2.go = "PiratesOnUninhabited_6";
		break;
		
		case "PiratesOnUninhabited_6":
			dialog.text = "¡Oh, capitán! Estos son tiempos en los que uno no puede sentirse seguro ni siquiera en la cama con su esposa, ja-ja, y mucho menos en el mar... Mira a estos matones, cada uno de ellos está listo para pelear con las manos desnudas contra cañones. No ansían la seguridad ni el confort en absoluto, eso se puede leer en sus caras.";
			link.l1 = "En sus caras, solo puedo leer la disposición de apuñalar a su necio benefactor por la espalda.";
			link.l1.go = "PiratesOnUninhabited_7";
			link.l2 = "Hmm... Eso, de hecho, es una buena idea. Dime amigo, ¿están tus matones dispuestos a servir en mi tripulación?";
			link.l2.go = "PiratesOnUninhabited_8";
		break;
		
		case "PiratesOnUninhabited_7":
			dialog.text = "Una lástima, capitán... Veo que no podemos resolverlo de manera amistosa. Supongo que tendré que recordarte el código del mar. Y ten en cuenta que, cuando se trata de un abordaje, no tenemos igual...";
			link.l1 = "Bueno, ahora finalmente puedo ver quién eres realmente...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", -3.0);
		break;
		
		// Берем их в команду
		case "PiratesOnUninhabited_8":
			dialog.text = "¡Por supuesto! ¡Estarían encantados de volverse parte de tu grupo de abordaje! ¡Nadie podrá vencerlos en una pelea, salvo quizás el mismísimo Davy Jones! ¡Ja-ja-ja!";
			link.l1 = "Está bien, entonces. Cargad vuestros traseros en los botes...";
			link.l1.go = "PiratesOnUninhabited_9";
		break;
		
		case "PiratesOnUninhabited_9":
			bTemp = CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked");
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;
				
				if(bTemp)
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				}
				else
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_43_again";
				}
			}
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount));
			
			Log_Info("Su tripulación se incrementó en " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " hombres.");
			OfficersReaction("bad");
			
			//PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			//DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_10":
			dialog.text = "¡Gracias, capitán! La carga no debería llevar mucho tiempo. ¡Dios, cómo habíamos rezado para que llegara ese momento!";
			link.l1 = "Muy bien, entonces.";
			link.l1.go = "PiratesOnUninhabited_11";
		break;
		
		// Берем их в пассажирами - держать курс на населенный остров
		case "PiratesOnUninhabited_11":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
			}
			
			Log_Info("Su tripulación se incrementó en " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " hombres.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			OfficersReaction("good");
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			
			if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.TreasureMap"))
			{
				if(CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked"))
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "1");
					AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
					// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины 
					if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
					{
						AddQuestUserData(sTitle, "sText", "wrecked pirate");
					}
					else
					{
						AddQuestUserData(sTitle, "sText", "wrecked pirate");
					}
					// <-- belamour gen
				}
				else
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "11");
					AddQuestUserData(sTitle, "pirateName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
				}
			}
			else
			{
				AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "5");
				AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
				// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData(sTitle, "sText", "wrecked pirate");
				}
				else
				{
					AddQuestUserData(sTitle, "sText", "wrecked pirate");
				}
				// <-- belamour gen
			}
			
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1.location = PChar.location;
			PChar.Quest.PiratesOnUninhabited_LocExitGood.function = "PiratesOnUninhabited_LocationExit_Good";
			
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1.location_type = "seashore";
			PChar.Quest.PiratesOnUninhabited_OnShore.again = true;
			PChar.Quest.PiratesOnUninhabited_OnShore.function = "PiratesOnUninhabited_OnShore";
			
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1.location_type = "mayak";
			PChar.Quest.PiratesOnUninhabited_OnMayak.again = true;
			PChar.Quest.PiratesOnUninhabited_OnMayak.function = "PiratesOnUninhabited_OnShore";
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_11_Again":
			dialog.text = LinkRandPhrase("¿Por qué te demoras, capitán? Ordena levar anclas.","Lo sentimos, capitán, pero debemos prepararnos para zarpar.","¡Qué suerte que hayas decidido venir aquí!");
			link.l1 = "Date prisa. El barco no esperará a nadie.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_11_Again";
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове
		case "PiratesOnUninhabited_12":
			if(hrand(1) == 0)
			{
				// Успешное завершение квеста - даст награду
				dialog.text = "Gracias, capitán. En verdad, acertamos al creer en nuestra suerte... Por favor, acepte esta gema, la encontré en esa cala maldita. Espero que le traiga suerte.";
				link.l1 = "No esperaba tal regalo.";
				link.l1.go = "PiratesOnUninhabited_13";
			}
			else
			{
				// Требуют денег
				dialog.text = "Capitán, por favor, no piense que somos demasiado insolentes, pero realmente estamos escasos de dinero. Sabe, hemos perdido todo lo que teníamos. ¿Podría prestarnos un par de puñados de pesos? Le devolveremos el dinero seguro... cuando se presente la oportunidad...";
				link.l1 = "¡Vaya! En verdad, la desfachatez no tiene límites. Bueno, lo único que podría hacer por ti ahora, después de todo lo que ya he hecho, sería no informar a las autoridades sobre ti.";
				link.l1.go = "PiratesOnUninhabited_15";
				link.l2 = "¿No me digas... Y cuánto quieres?";
				link.l2.go = "PiratesOnUninhabited_17";
			}
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_13":
			AddItems(PChar, "jewelry4", 1);
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				
				rChar.Dialog.currentnode = "PiratesOnUninhabited_14";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "2");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_14":
			dialog.text = LinkRandPhrase("Gracias, capitán.","Capitán, estamos tan agradecidos contigo.","¡Rezaremos por usted, capitán "+PChar.name+"!");
			link.l1 = "Buena suerte para ti. Adiós...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_14";
		break;
		
		case "PiratesOnUninhabited_15":
			dialog.text = "Heh, capitán... Sabes, nos llevamos bien... Sería una verdadera lástima matarte...";
			link.l1 = "¡Puedes intentarlo!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
		break;
		
		case "PiratesOnUninhabited_16":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "3");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_17":
			iMoney = sti(PChar.rank) * 500;
			PChar.GenQuest.PiratesOnUninhabited.Money = iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			
			dialog.text = "Bueno, dime, "+iMoney+" pesos para cada uno de nosotros estaría bien... Por supuesto, si no crees que esta compensación por todo nuestro dolor y sufrimiento es demasiado pequeña, je-je...";
			link.l1 = RandPhraseSimple("Al contrario, estoy seguro de que es demasiado... Una soga al cuello para cada uno de vosotros sería lo mejor.","¡Yo mismo te colgaré como monos en las palmas por tal dinero!");
			link.l1.go = "PiratesOnUninhabited_18";
			
			if(sti(PChar.money) >= iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				link.l2 = "Está bien, tómalo. ¿Espero no deberte nada más?";
				link.l2.go = "PiratesOnUninhabited_19";
			}
		break;
		
		case "PiratesOnUninhabited_18":
			dialog.text = "¡Qué generosidad! Francamente, estaba pensando que ya habías tenido la oportunidad de ver que siempre conseguimos lo que deseamos. Y esta vez tampoco vamos a dar marcha atrás...";
			link.l1 = "¡Puedes intentarlo!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_19":
			dialog.text = "¡Oh no, capitán, ¿qué está diciendo?! Definitivamente encenderemos una vela en su nombre, si alguna vez entramos en una iglesia... ¡jajá!";
			link.l1 = "Eso espero...";
			link.l1.go = "PiratesOnUninhabited_20";
			
			iMoney = sti(PChar.GenQuest.PiratesOnUninhabited.Money);
			
			AddMoneyToCharacter(PChar, -iMoney);
			AddMoneyToCharacter(NPChar, iMoney);
		break;
		
		case "PiratesOnUninhabited_20":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_CharacterDisableDialog(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
			OfficersReaction("good");
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Acc")));
			CloseQuestHeader(sTitle);
			
			NPChar.SaveItemsForDead = true; // сохранять на трупе вещи
			NPChar.DontClearDead = true;  // не убирать труп через 200с
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_21":
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				// Игрок врет - свободное место есть
				dialog.text = "¡Oh no, capitán, ¿qué está diciendo?! Definitivamente encenderemos una vela en su nombre, si alguna vez entramos en una iglesia...¡jajaja!";
				link.l1 = "Eso espero...";
				link.l1.go = "PiratesOnUninhabited_23";
			}
			else
			{
				dialog.text = "Je, capitán, eso no es mucho problema. Yo y mis muchachos estamos dispuestos a liberar una docena de hamacas en tu barco de aquellos que las ocupan actualmente...";
				link.l1 = "Hmm... eso suena como una amenaza...";
				link.l1.go = "PiratesOnUninhabited_22";
			}
		break;
		
		case "PiratesOnUninhabited_22":
			dialog.text = "Bueno, en realidad, es una amenaza. Necesito tu barco, y saldré de este lugar, ¡con o sin tu consentimiento!";
			link.l1 = "Bueno, ahora finalmente puedo verte por lo que realmente eres...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_23":
			dialog.text = "Le entiendo, capitán. Le entiendo perfectamente... ¿Quién querría estar cuidando a pobres piratas, que han estado pidiendo una soga?.. Pero... ¿y si le ofrezco un intercambio? Nos lleva a alguna cala en una isla habitada o en el continente, y a cambio le doy un mapa del tesoro. ¿Tenemos un trato?";
			link.l1 = "Hum... ¿Y cómo puedes garantizar que este mapa no es una falsificación?";
			link.l1.go = "PiratesOnUninhabited_25";
			link.l2 = "Ja, estoy seguro de que tu mapa cuesta tanto como el trozo de papel en el que fue dibujado...";
			link.l2.go = "PiratesOnUninhabited_24";
		break;
		
		case "PiratesOnUninhabited_24":
			dialog.text = "Bueno... Nos dejas sin elección... Aun así, vamos a salir de este lugar, ¡con o sin tu consentimiento!";
			link.l1 = "Bueno, ahora finalmente puedo ver quién eres realmente...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_25":
			dialog.text = "¿Y cómo puedes garantizar que no nos entregarás a las autoridades en el puerto más cercano? Ambos estamos jugando sin ver las cartas del otro...";
			link.l1 = "De acuerdo, tienes un trato.";
			link.l1.go = "PiratesOnUninhabited_11";
			PChar.GenQuest.PiratesOnUninhabited.TreasureMap = true;
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове. Вариант, когда нам обещали карту сокровищ
		case "PiratesOnUninhabited_26":
			// PChar.GenQuest.PiratesOnUninhabited.MainPirateName - имя в родительном падеже
			
			dialog.text = "Gracias, capitán "+PChar.name+". Has cumplido"+GetSexPhrase("","")+" tu promesa, es hora "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_DAT)+" para cumplir el mío. No tengo el mapa conmigo, pero te diré dónde está el tesoro. Ve a la cala...";
			link.l1 = "¡Oh, así que ahora lo pones de esa manera! Veo que ibas a engañarme desde el principio...";
			link.l1.go = "PiratesOnUninhabited_27";
			link.l2 = "Supe de inmediato que no se podía confiar en ti...";
			link.l2.go = "PiratesOnUninhabited_30";
			link.l3 = "Eso es lo que pasa cuando confías en un pirata. ¿Qué clase de gente sois? ¡Nada es sagrado para vosotros!";
			link.l3.go = "PiratesOnUninhabited_33";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_27":
			dialog.text = "No hagas un escándalo... No soy un santo, ¡pero cumplo mi palabra!";
			link.l1 = "¿Y esperas que te crea una vez más? ¿Para que mañana todo el archipiélago se burle de mí?";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		case "PiratesOnUninhabited_28":
			dialog.text = "Mm... Aparentemente, no habrá una resolución pacífica. Pero, Dios sabe, yo no lo quería...";
			link.l1 = "¡Desenvaina tu espada, o te aplastaré como la rata que eres!";
			link.l1.go = "PiratesOnUninhabited_29";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_29":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "6");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_30":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "¿Y qué más podría haber hecho? ¿Quedarme en ese charco apestoso con mis muchachos y pudrirme hasta la muerte? Será mejor que me escuches..."+XI_ConvertString(sTitle+"Gen")+" capitán "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" hay un escondite donde guarda su botín. Pero ten cuidado "+GetSexPhrase(" "," ")+", frecuenta ese lugar. Encontrar el alijo no será difícil, si mantienes la cabeza fría..."; // belamour gen
			link.l1 = "¿Y esperas que te crea una vez más? ¿Para que mañana todo el archipiélago se burle de mí?";
			link.l1.go = "PiratesOnUninhabited_28";
			link.l2 = "Está bien. Pero si me engañas una vez más, te encontraré.";
			link.l2.go = "PiratesOnUninhabited_31";
		break;
		
		case "PiratesOnUninhabited_31":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				rChar.Dialog.currentnode = "PiratesOnUninhabited_32";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "7");
			AddQuestUserData(sTitle, "capName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.TreasureShore + "Gen"))); // belamour gen
			
			// Таймер для клада. По прошествии 10 дней в кладе будут всякие бакланы и т.д.
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1 = "Timer";
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.function = "PiratesOnUninhabited_TreasureLose"; // belamour gen
			
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1 = "Location";
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1.Location = PChar.GenQuest.PiratesOnUninhabited.TreasureShore;
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.function = "PiratesOnUninhabited_InTreasureLoc";
			
			DialogExit();
			
			// Курс в бухту, которую назвал пират. У нас сроку 10 дней, котом клад пропадёт
		break;
		
		case "PiratesOnUninhabited_32":
			sTemp = ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC);
			
			dialog.text = LinkRandPhrase("Escucha "+sTemp+", está hablando con sensatez.","No te enfades con "+sTemp+", simplemente no tenía otra opción.","Gracias, capitán.");
			link.l1 = "Buena suerte para ti...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_32";
		break;
		
		case "PiratesOnUninhabited_33":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "¿Y qué más podría haber hecho? ¿Quedarme en ese charco apestoso con mis muchachos y pudrirme hasta morir? Será mejor que me escuches..."+XI_ConvertString(sTitle+"Gen")+" capitán "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" hay un escondite donde guarda su botín. Pero ten cuidado, lo visita con frecuencia. No será difícil encontrar el escondite, si mantienes la cabeza fría..."; // belamour gen
			link.l1 = "¿Y esperas que te crea una vez más? ¿Para que mañana todo el archipiélago se burle de mí?";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		// Пираты в бухте с сокровищем
		case "PiratesOnUninhabited_34":
			dialog.text = "¿Quién eres tú,"+GetSexPhrase(" compañero"," muchacha")+"¿Y qué te ha traído a este lugar desierto?";
			link.l1 = "Me detuve para reponer mi suministro de agua fresca.";
			link.l1.go = "PiratesOnUninhabited_35";
			link.l2 = "Estoy aquí en nombre de "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_GEN)+".";
			link.l2.go = "PiratesOnUninhabited_38";
			NextDiag.TempNode = "PiratesOnUninhabited_34";
		break;
		
		case "PiratesOnUninhabited_35":
			dialog.text = "Has elegido un mal lugar para eso... Está bien, tómate tu tiempo.";
			link.l1 = "¡Ajá...";
			link.l1.go = "exit";
			link.l2 = "¿Y quién eres tú para decirme lo que debo hacer?";
			link.l2.go = "PiratesOnUninhabited_36";
		break;
		
		case "PiratesOnUninhabited_36":
			dialog.text = "Estoy diciéndole a todos qué hacer. Y aquellos que se creen demasiado listos colgarán de la palmera.";
			link.l1 = "Cortaré tu lengua, perro.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_37":
			DialogExit();
			LAi_Group_SetRelation("PiratesOnUninhabited_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		
		case "PiratesOnUninhabited_38":
			dialog.text = "¿Y por qué no vino él mismo?";
			link.l1 = "No quería, se quedó en "+LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen"))+" y esperándome."; // belamour gen
			link.l1.go = "PiratesOnUninhabited_39";
		break;
		
		case "PiratesOnUninhabited_39":
			dialog.text = "¡Ese viejo sinvergüenza! Intenta engañarnos una vez más, ¿no? Eso no funcionará. ¡Dile que solo podrá recoger el dinero junto con nosotros!";
			link.l1 = "Me dijo que no volviera sin dinero y que no llevara a nadie a bordo...";
			link.l1.go = "PiratesOnUninhabited_40";
		break;
		
		case "PiratesOnUninhabited_40":
			dialog.text = "Bueno, si confías tanto en él, puedes quedarte aquí. Pero nos llevaremos tu barco, tu dinero y nos dirigiremos a "+LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen"))+". Nos morimos de ganas de ver el rostro de "+PChar.GenQuest.PiratesOnUninhabited.MainPirateName+"."; // belamour gen
			link.l1 = "Si lo extrañas tanto, puedes nadar hasta allí... o puedes morir aquí.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.GenQuest.PiratesOnUninhabited.UseMainPiratename = true;
		break;
		
		// Ветка из PiratesOnUninhabited_3
		case "PiratesOnUninhabited_41":
			iBanditsCount = 5 + hrand(5);
			iMoney = GetFreeCrewQuantity(PChar);
			
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = iBanditsCount;
			
			dialog.text = "Eres una persona astuta. Pero permíteme asegurarte que nuestro conflicto con el capitán "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_ABL)+" es puramente de naturaleza ideológica. Le he advertido que sus operaciones sucias serían castigadas un día y ahora mis "+iBanditsCount+" camaradas y yo estamos sufriendo la ira de Dios y la justicia.";
			link.l1 = "¿Qué dices? Apuesto a que fuiste tú el verdadero instigador del motín, y has recibido lo que merecías.";
			link.l1.go = "PiratesOnUninhabited_42";
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l2 = "Por supuesto... Sería bueno también escuchar la versión del capitán "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" sobre sus desacuerdos.";
				link.l2.go = "PiratesOnUninhabited_44";
			}
		break;
		
		case "PiratesOnUninhabited_42":
			dialog.text = "Capitán, ¿por qué ofende a personas honestas con su desconfianza? Solo mire sus caras... ¿realmente cree que son amotinados? Son tan humildes como pueden ser los hombres... ¡Pero no tienen igual en una lucha por una causa justa bajo un buen mando! Puedo responder personalmente por cada uno de ellos.";
			link.l1 = "Está bien, pero ¿qué haré contigo ahora?";
			link.l1.go = "PiratesOnUninhabited_43";
		break;
		
		case "PiratesOnUninhabited_43":
			iBanditsCount = sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			iMoney = GetFreeCrewQuantity(PChar);
			
			dialog.text = "Lo que desees. Depende de ti, llévanos a un asentamiento o acéptanos en tu tripulación, me pareces un buen capitán.";
			
			if(iMoney >= iBanditsCount)
			{
				link.l1 = "Está bien, te llevaré a mi tripulación. ¡Pero nada de tonterías! ¡Tengo una disciplina estricta en mi barco!";
				link.l1.go = "PiratesOnUninhabited_9"; // Берем в команду
			}
			
			link.l2 = "No te voy a llevar a ninguna parte. Ya tengo suficientes matones en mi tripulación.";
			link.l2.go = "PiratesOnUninhabited_24"; // Рубилово и конец квеста
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l3 = "Está bien, súbete al bote, te llevaré a algún lugar.";
				link.l3.go = "PiratesOnUninhabited_11"; // В пассажиры и на остров
			}
		break;
		
		case "PiratesOnUninhabited_43_again":
			dialog.text = LinkRandPhrase("Lo juro, capitán, no lo lamentarás.","Has hecho la elección correcta, capitán.","Capitán, ¡tenga la seguridad de que tuvo tanta suerte como nosotros!");
			link.l1 = RandPhraseSimple("Eso espero.","Apresúrate. El barco no esperará a nadie.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_43_again";
		break;
		
		case "PiratesOnUninhabited_44":
			sTitle = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.PiratesOnUninhabited.StartShipName = sTitle;
			
			dialog.text = "Eso se puede arreglar fácilmente. Navega en el '"+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Name+"Voc"))+"' "+sTitle+" y está involucrado en el comercio de esclavos... Hagámoslo de esta manera: Si lo encontramos, tú te quedas con la carga y nosotros con el barco. Ah, y también puedes preguntarle si sabe sobre "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_ACC)+". Espero que no se haga caca en los pantalones cuando escuche ese nombre, porque es mi barco..."; // belamour gen
			link.l1 = "De acuerdo, tienes un trato.";
			link.l1.go = "PiratesOnUninhabited_45";
		break;
		
		case "PiratesOnUninhabited_45":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				rChar.location = "none"; // Убираем из локации при выходе   исправлено с NPChar на rChar - лесник
				rChar.location.locator = ""; // лесник  - так же исправлено .  тогда бага не будет.
			}
			
			Log_Info("Su tripulación se incrementó en " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " hombres.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1)
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			//NPChar.FaceId = 101; // лесник потом подобрать аву бандиту.   
			
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "13");
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			// --> belamour окончание по количеству персон
			if(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) >= 5)
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors");
			}
			else
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailor");
			}
			// <-- belamour
			AddQuestUserData(sTitle, "badCapName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Voc")) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PiratesOnUninhabited_SetCapToMap(); // Ставим корабль на карту
			
			DialogExit();
		break;
		
		// Диалог с кэпом в каюте
		case "PiratesOnUninhabited_46":
			dialog.text = "¿Qué demonios quieres de mí?";
			link.l1 = "Vine a saludar de parte de "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_GEN)+"Me imagino que lo conoces, ¿verdad?";
			link.l1.go = "PiratesOnUninhabited_47";
			
			PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
			PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
			Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
		break;
		
		case "PiratesOnUninhabited_47":
			dialog.text = "Es una pena que no estrangulara a ese canalla antes. Bueno, supongo que ha llegado el momento de pagar por mi benevolencia...";
			link.l1 = "En efecto... Y el tiempo se ha acabado...";
			link.l1.go = "PiratesOnUninhabited_48";
		break;
		
		case "PiratesOnUninhabited_48":
			LAi_CharacterDisableDialog(NPChar);
			LAi_Group_Attack(NPChar, Pchar);
			
			LAi_SetCurHPMax(NPChar);
			QuestAboardCabinDialogFree(); // важный метод
			
			LAi_Group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_Group_SetCheckFunction(LAI_GROUP_BRDENEMY, "PiratesOnUninhabited_CapDeath");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_49":
			dialog.text = "¡Buen trabajo, capitán! ¿Todo como acordamos, entonces? ¿Nosotros conseguimos el barco y tú obtienes la carga?";
			link.l1 = "Claro. Toma el barco y haz buen uso de él.";
			link.l1.go = "PiratesOnUninhabited_50";
		break;
		
		case "PiratesOnUninhabited_50":
			NPChar.LifeDay = 0;
			NPChar.location = "none"; // Убираем из каюты
			NPChar.location.locator = "";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "14");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			ChangeAttributesFromCharacter(CharacterFromID("PiratesOnUninhabited_BadPirate"), NPChar, true);
			DialogExit();
			
		break;
		
		// На палубе, когда корабль с нашим пиратом отпустили
		case "PiratesOnUninhabited_50_Deck1":
			dialog.text = "Te saludo, capitán "+PChar.name+".";
			link.l1 = "Entonces, ¿qué piensas de tu barco?";
			link.l1.go = "PiratesOnUninhabited_50_Deck2";
		break;
		
		case "PiratesOnUninhabited_50_Deck2":
			dialog.text = "Heh... está chirriando y crujiendo, igual que yo. Creo que a ambos no nos queda mucho tiempo para navegar los mares...";
			link.l1 = "Buena suerte, entonces...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_50_Deck1";
		break;
		
		// В бухте, вариант, когда корабль, который нужно было захватить, утопили
		case "PiratesOnUninhabited_51":
			dialog.text = "¿Por qué has hundido mi barco? ¿Acaso recuerdas nuestro trato?";
			link.l1 = "¿Qué, no quería que él me hundiera en su lugar. ¿No ves que apenas lo logré?";
			link.l1.go = "PiratesOnUninhabited_52";
		break;
		
		case "PiratesOnUninhabited_52":
			if(hrand(1) == 1)
			{
				dialog.text = "¿Quién pelea así? ¡Has perdido semejante barco! ¡Maldita sea! ¿Qué demonios hace aquí un niño como tú?";
				link.l1 = "Cortaré tu lengua, perro.";
				link.l1.go = "PiratesOnUninhabited_53";
			}
			else
			{
				iMoney = sti(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Price);
				iMoney = MakeInt((iMoney / 1.2 + hrand(iMoney - (iMoney / 1.2))) * 1.2);
				dialog.text = "¿Quién pelea así? ¡Has perdido semejante barco! ¿Tienes idea de cuánto me costó?"+FindRussianMoneyString(iMoney)+"¡Ahora me debes...!";
				link.l1 = "¿No sería demasiado para ti? No olvides que ya te he hecho un favor.";
				link.l1.go = "PiratesOnUninhabited_54";
				
				if(sti(PChar.money) >= iMoney)
				{
					link.l2 = "¡Maldito seas con ese maldito barco! ¡Toma tu dinero y no vuelvas a cruzarte en mi camino!";
					link.l2.go = "PiratesOnUninhabited_55";
				}
			}
		break;
		
		case "PiratesOnUninhabited_53":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "15");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_54":
			dialog.text = "¿Y de qué me sirve ese favor ahora?! Si el capitán "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_NOM)+"¡está en el fondo del mar ahora con mi barco! ¡Ahora ni recibo mi parte, ni recupero mi barco! ¡Qué destino, morir en la cuneta, como un vagabundo!!!";
			link.l1 = "¿Pero por qué? Puedo organizarte un funeral espectacular. Justo aquí, si te parece bien...";
			link.l1.go = "PiratesOnUninhabited_53";
		break;
		
		case "PiratesOnUninhabited_55":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "16");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// КОНЕЦ
		
		// Warship, 15.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "Pensaba que podríamos... llegar a un acuerdo, quizás. Si nos haces un favor, te lo devolveremos, je-je.";
			link.l1 = "¿Un favor? ¿Y cuál es el trato y qué ofreces a cambio?";
			link.l1.go = "JusticeOnSale_3";
		break;
		
		case "JusticeOnSale_2":
			LAi_Group_SetRelation("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, true);
			
			DialogExit();
			LAi_SetFightMode(PChar, true);
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "Nuestro capitán "+PChar.GenQuest.JusticeOnSale.SmugglerName+" fue atrapado por la patrulla de "+XI_ConvertString("Colony"+PChar.GenQuest.JusticeOnSale.CityId+"Gen")+"Lo tienen encarcelado, pero no tienen suficientes pruebas para colgarlo. No podemos sacarlo nosotros mismos\n"+"Usted es un hombre respetado. La gente le conoce. Tal vez podría negociar, pagar la fianza o simplemente comprar su libertad. Confíe en nosotros, dejaremos la isla tan pronto como tengamos a nuestro hombre, ¡así que su renombre no sufrirá!"; // belamour gen
			link.l1 = "Digamos que puedo ayudarte. Pero, ¿qué hay de mi pago?";
			link.l1.go = "JusticeOnSale_4";
			link.l2 = "¡Vete al infierno, engendro del diablo! ¡No quiero tener nada que ver contigo!";
			link.l2.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "¿Te gustaría tener varios abalorios y talismanes indios? Son bastante raros... ¿O prefieres efectivo al momento? ¿Varios miles de pesos, digo yo?";
			link.l1 = "¡Vete al infierno, engendro del diablo! ¡No tendré tratos contigo!";
			link.l1.go = "JusticeOnSale_5";
			link.l2 = "Estoy interesado en las chucherías indias. Supongo que aceptaré.";
			link.l2.go = "JusticeOnSale_6";
			link.l3 = "El efectivo es el mejor amigo del marinero. El dinero no tiene olor, como todos sabemos. Estoy de acuerdo.";
			link.l3.go = "JusticeOnSale_7";
		break;
		
		case "JusticeOnSale_5":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			DialogExit();
		break;
		
		case "JusticeOnSale_6":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 0; // Подрякушки.
			dialog.text = "Gracias, capitán. Te compensaremos la suma de la fianza además de tu recompensa. Supongo que deberías hablar con el comandante sobre nuestro capitán. Quizás, puedas persuadirlo. Una vez que lo saques, ven a "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+", ahí es donde nuestro barco ha echado el ancla, "+LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name))+" '"+PChar.GenQuest.JusticeOnSale.ShipName+"'. Te estaremos esperando en la orilla."; // belamour gen
			link.l1 = "... ";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_7":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 1; // Монеты.
			
			dialog.text = "Gracias, capitán. Te compensaremos la suma de la fianza además de tu recompensa. Supongo que deberías hablar con el comandante sobre nuestro capitán. Tal vez logres persuadirlo. Una vez que lo saques, ven a "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+",   es donde nuestro barco ha echado el ancla, "+LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name))+"'"+PChar.GenQuest.JusticeOnSale.ShipName+"'. Te estaremos esperando en la orilla."; // belamour gen
			link.l1 = "... ";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			ReOpenQuestHeader("JusticeOnSale");
			AddQuestRecord("JusticeOnSale", "1");
			AddQuestUserData("JusticeOnSale", "cityName", XI_ConvertString("Colony" + PChar.GenQuest.JusticeOnSale.CityId + "Gen")); // belamour gen
			PChar.GenQuest.JusticeOnSale.MayorWait = true;
			PChar.GenQuest.JusticeOnSale.PrisonWait = true;
			
			DialogExit();
		break;
		
		case "JusticeOnSale_9":
			if(hrand(1) == 0)
			{
				if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
				{
					// Награда побрякушками.
					dialog.text = "¡Estamos aquí, capitán! ¡Hiciste un gran trabajo engañando a esos burócratas barrigudos! Aquí está tu recompensa. ¡Chicos, traigan los chucherías!";
				}
				else
				{
					// Награда золотом.
					dialog.text = "¡Estamos aquí, capitán! ¡Hiciste un gran trabajo engañando a esos burócratas barrigones! Aquí está tu recompensa. ¡Chicos, traigan el cofre!";
				}
				
				link.l1 = "¡Dame mi parte y piérdete!";
				link.l1.go = "JusticeOnSale_10";
			}
			else
			{
				// Массакра.
				dialog.text = "¡Estamos allí, capitán! Veo que lo has arreglado todo muy bien. Pero ya ves... no necesitamos testigos, así que... ¡Agradezcamos al capitán, muchachos!";
				link.l1 = RandSwear()+"¡Debería haberte disparado justo cuando te conocí!";
				link.l1.go = "JusticeOnSale_11";
			}
			chrDisableReloadToLocation = false;
		break;
		
		case "JusticeOnSale_10":
			DialogExit();
			if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddItems(PChar, "indian_"+(1+hrand(10)), 1);
				}
				else
				{
					AddItems(PChar, "obereg_"+(1+hrand(10)), 1);
				}
			}
			else
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 700 + hrand(2000));
				}
				else
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 500 + hrand(1000));
				}
			}
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_ActorGoToLocation(rChar, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), "none", "", "", "", 3.0);
			}
			AddQuestRecord("JusticeOnSale", "3");
			CloseQuestHeader("JusticeOnSale");
		break;
		
		case "JusticeOnSale_11":
			AddQuestRecord("JusticeOnSale", "4");
			CloseQuestHeader("JusticeOnSale");
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_Group_MoveCharacter(rChar, "JusticeOnSale_ShoreGroup");
			}
			
			LAi_Group_SetRelation("JusticeOnSale_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;
		
		// belamour постоялец-->
		case "Unwantedpostor_room":
			dialog.text = ""+GetSexPhrase("¿Quién eres? ¿Y por qué irrumpes en mi habitación?","Vaya. ¿Quién eres? Esta es mi habitación, por supuesto, pero no me importa tal compañía. ¿Es esta una entrega de amor?")+"";
			link.l1 = ""+GetSexPhrase("Ya no es tuya. El posadero me alquiló la habitación, y como no estás pagando por ella, estás a punto de salir de aquí. Ahora podemos hacer esto por las buenas o por las malas. La decisión es tuya.","Estás soñando. En nuestro caso, es limpieza. Así que limpia este lugar de ti mismo. Esta es mi habitación ahora, ya que, a diferencia de ti, yo siempre pago a los posaderos.")+"";
			link.l1.go = "Unwantedpostor_room_1";
		break;
		
		case "Unwantedpostor_room_1":
			If(sti(pchar.reputation.fame) > 60)
			{
				dialog.text = ""+GetSexPhrase("Creo que he oído hablar de ti. Está bien, tú ganas, me iré, todavía quiero vivir...","Hmm, he oído mucho sobre ti. Supongo que no solo es tu lengua la que es afilada. Está bien, no te enojes, la habitación es tuya.")+"";
				link.l1 = ""+GetSexPhrase("Hiciste una buena decisión.","Buen chico.")+"";
				link.l1.go = "Unwantedpostor_peace";
				break;
			}
			dialog.text = ""+GetSexPhrase("¿Así es, eh? Bueno, elijo el camino difícil.","¡Maldita sea! Quería tratar contigo amablemente...")+"";
			link.l1 = ""+GetSexPhrase("Como desees...","¿Y tú lo llamas 'amablemente'? Te compadezco. Aunque, quizás no.")+"";
			link.l1.go = "Unwantedpostor_fight";
		break;
		
		case "Unwantedpostor_peace":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			DeleteAttribute(PChar, "GenQuest.Unwantedpostor");
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 180, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "Fortune", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Sneak", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Leadership", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetFightMode(pchar, true);
			sld = characterFromId("Berglar_Unwantedpostor"); 
			LAi_SetWarriorType(sld);
			LAi_Group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_SetCheckMinHP(sld, 10, true, "Unwantedpostor_Win");
			LAi_SetCheckMinHP(pchar, 10, true, "Unwantedpostor_Lose");	
		break;
		
		case "Unwantedpostor_Win":
			dialog.text = ""+GetSexPhrase("Está bien, ¡alto! ¡No me mates! Me voy.","¡Alto! ¿Qué se supone que debemos hacer ahora, matarnos unos a otros por esta habitación? ¡Atragántate con ella, es toda tuya. Apestoso...")+"";
			link.l1 = ""+GetSexPhrase("Decisión correcta. Otra vez, piensa con la cabeza: no todos son tan amables como yo, pueden matar sin querer.","Hombres.")+"";
			link.l1.go = "Unwantedpostor_Win_1";
		break;
		
		case "Unwantedpostor_Win_1":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) DeleteAttribute(PChar, "GenQuest.Unwantedpostor"); // полуночная драка
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 170+rand(20), false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "FencingL", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingS", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingH", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_Lose":
			dialog.text = ""+GetSexPhrase("Bueno, ¿me echaste? Sal de aquí antes de que te corte.","Así que todo lo que sabes hacer es charlar. Alégrate de que todavía estoy de buen humor, de lo contrario te habría hecho algo aún peor. ¡Lárgate de aquí!")+"";
			link.l1 = ""+GetSexPhrase("Maldita sea...","Maldita sea, te subestimé... Está bien, está bien, me voy ahora.")+"";
			link.l1.go = "Unwantedpostor_Lose_1";
		break;
		
		case "Unwantedpostor_Lose_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sld = CharacterFromID("Berglar_Unwantedpostor");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) pchar.GenQuest.Unwantedpostor = "Lose"; // если драка за полночь перевалит
			DoQuestReloadToLocation(Locations[FindLocation(pchar.location)].fastreload+"_tavern", "reload", "reload2_back", "");	
		break;
		// <-- belamour постоялец
		
		// belamour пьяный матрос -->
		case "GuiltySailor":
			dialog.text = "¿Ah?.. Lárgate, novato, yo no bebo... ¡hic!.. con cualquiera.";
			link.l1 = "Te voy a dar una paliza tan fuerte ahora mismo que no beberás durante otra semana.";
			link.l1.go = "GuiltySailor_1";
		break;
		
		case "GuiltySailor_1":
			dialog.text = "¿Qué?! ¿Sabes con quién estás hablando? Soy un marinero del barco '"+pchar.ship.name+"¡Solo tengo que decirle al capitán, y no tendrás tiempo ni de salir de la ciudad! Lárgate de aquí mientras aún estés entero."; 
			link.l1 = "...";
			link.l1.go = "GuiltySailor_2";
		break;
		
		case "GuiltySailor_2":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "GuiltySailor_3";
		break;
		
		case "GuiltySailor_3":
			dialog.text = "¿Capitán?..";
			link.l1 = "Fregarás la cubierta durante un mes.";
			link.l1.go = "GuiltySailor_4";
		break;
		
		case "GuiltySailor_4":
			NPChar.Dialog.currentnode = "GuiltySailor_Again";
			SetFunctionTimerCondition("GuiltySailor_NextQ", 0, 0, 45+rand(45), false);
			DialogExit();
		break;
		
		case "GuiltySailor_Again":
			dialog.text = "Lo siento, capitán!";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "GuiltySailor_Again";
		break;
		// <-- пьяный матрос
		
		// belamour хороший специалист -->
		case "ExpertSailor":
			int ExpertSailorVar = 1 + hrand(2);
			dialog.text = "¡Saludos, capitán! Sé que eres el capitán, sí.";
			link.l1 = "Saludos. ¿Cómo sabes que soy el capitán?";
			link.l1.go = "ExpertSailor_"+ExpertSailorVar;
		break;
		
		case "ExpertSailor_1": // матрос
			dialog.text = "Ja, soy un lobo de mar experimentado, he estado navegando por el mar durante más de una década. Me dedicaba principalmente a la navegación: navegué en calma, en tormenta, en un lugre, e incluso en un navío de guerra. Es cierto, el mes pasado me hirieron después de una dura batalla, hubo una fuerte tormenta y nadie se atrevió a subir a la vela, así que lo hice yo, pero pagué un precio por ello, por suerte solo me torcí el tobillo y no pude caminar durante unas semanas. Así que me enviaron a tierra. Ahora estoy mejor y estoy sentado aquí, esperando una oportunidad.";
			link.l1 = "Interesante. No me importaría tener un especialista en este asunto. ¿Te gustaría unirte a mi equipo?";
			link.l1.go = "ExpertSailor_1_1";
		break;
		
		case "ExpertSailor_1_1":
			dialog.text = "¿Por qué no? Ya extraño la cubierta del barco y el ruido de las velas llenas de viento fresco. También podría entrenar a tu equipo, si es necesario. Pero te pediré inmediatamente mil pesos, de lo contrario, mis bolsillos ya están vacíos. Luego, como el resto del equipo. Soy una persona honesta.";
			link.l1 = "No, probablemente me negaré. Si a todos los marineros se les paga mil pesos por contratación, me iré a la quiebra. No me culpes.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Trato hecho. No me importa pagar mil pesos por un buen especialista. Espera... aquí tienes. Y te espero en el barco.";
				link.l2.go = "ExpertSailor_payS";
			}
		break;
		
		case "ExpertSailor_nomoney":
			DialogExit();
			NPChar.Dialog.currentnode = "ExpertSailor_Again";
		break;
		
		case "ExpertSailor_payS":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Sailors", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_2": // канонир
			dialog.text = "Ja, soy un lobo de mar experimentado, he estado navegando por más de una década. La mayoría del tiempo estuve cerca de los cañones: disparé desde falconetes, carronadas, culebrinas, sacres... serví en un lugre, e incluso en un navío de línea. La verdad, el mes pasado fui herido tras una dura batalla, un rebote de metralla me alcanzó, nada serio, solo un rasguño en la pierna, así que me mandaron a tierra. Ahora estoy mejor y estoy aquí sentado, esperando una oportunidad.";
			link.l1 = "Interesante. No me importaría tener un especialista en este asunto. ¿Te gustaría unirte a mi equipo?";
			link.l1.go = "ExpertSailor_2_1";
		break;
		
		case "ExpertSailor_2_1":
			dialog.text = "¿Por qué no? Ya extraño la cubierta de artillería, el olor a pólvora quemada y el rugido de las descargas de cañón. También podría entrenar a tu tripulación, si es necesario. Pero te pediré inmediatamente mil pesos, de lo contrario mis bolsillos ya están vacíos. Luego, como el resto de la tripulación, soy un hombre honesto.";
			link.l1 = "No, probablemente me negaré. Si a todos los marineros pagan mil pesos por la contratación, me arruinaré. No me culpes.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Trato hecho. No me importa gastar mil pesos por un buen especialista. Espera... aquí tienes. Y te espero en el barco.";
				link.l2.go = "ExpertSailor_payС";
			}
		break;
		
		case "ExpertSailor_payС":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Cannoners", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_3": // солдат
			dialog.text = "Ja, soy un lobo de mar experimentado, he estado navegando por más de una década. Principalmente luché en batallas de abordaje: peleé contra piratas y ejércitos regulares, sé cómo manejar todo tipo de armas, he estado en un lugre e incluso en un acorazado. Es cierto, el mes pasado fui herido después de una dura batalla, fue solo un pequeño rasguño de sable en mi espalda, el cobarde no pudo enfrentarse a mí, pero lo maté en respuesta, oh, deberías haber visto sus caras cuando vieron el rasguño ja-ja. Así que me enviaron a tierra. Ahora estoy mejor y aquí sentado esperando una oportunidad.";
			link.l1 = "Interesante. No me importaría tener un especialista en este asunto. ¿Te gustaría unirte a mi equipo?";
			link.l1.go = "ExpertSailor_3_1";
		break;
		
		case "ExpertSailor_3_1":
			dialog.text = "¿Por qué no? Ya extraño el sonido de los sables, el crujir de los barcos acercándose por los costados y la adrenalina de la batalla. También podría entrenar a tu equipo, si es necesario. Pero te pediré de inmediato mil pesos, de lo contrario mis bolsillos ya están vacíos. Luego, como el resto del equipo, soy un hombre honesto.";
			link.l1 = "No, probablemente me negaré. Si a todos los marineros se les paga mil pesos por contratarlos, me arruinaré. No me culpes.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Trato hecho. No me importa pagar mil pesos por un buen especialista. Espera... aquí tienes. Y te espero en el barco.";
				link.l2.go = "ExpertSailor_payA";
			}
		break;
		
		case "ExpertSailor_payA":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Soldiers", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_Again":
			dialog.text = "¡Buena suerte en el mar, capitán!";
			link.l1 = "Tú también.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ExpertSailor_Again";
		break;
		// <-- хороший специалист
		
		//belamour ночной приключенец -->
		// матрос -->
		case "NightAdventure_Sailor":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "¿Q-quién eres?";
			link.l1 = "Soy capitán "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Lo siento, camarada, tengo prisa.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_SailorTavern":          link.l1.go = "NightAdventure_Sailor_1_1"; break; // до таверны
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1"; break; // шулер
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1"; break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorBoat":      		 link.l1.go = "NightAdventure_Sailor_3_1"; break; // до пирса
				case "NightAdventure_SailorShip":            link.l1.go = "NightAdventure_Sailor_3_1"; break;
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";       break; // наезд
			}
		break;
		// до таверны 
		case "NightAdventure_Sailor_1_1":
			dialog.text = "¿Capitán?.. ¡hic! C-capitán... escoltadme a la t-taberna... ¡hic!.. ¿eh? Por favor. Parece que... me p-perdí en esta en esta c-colonia, sí... ¡hic!..";
			link.l1 = "¡Quítate de encima, no tengo tiempo!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Está bien, vamos. No parece que puedas llegar allí por ti mismo.";
			link.l2.go = "NightAdventure_Sailor_1_2";
		break;
		
		case "NightAdventure_Sailor_1_2":
			dialog.text = "Solo... hip!.. lentameeente, p-por favor. No puedo... hip!.. ponerme... de pie...";
			link.l1 = "Está bien, vamos, despacio.";
			link.l1.go = "NightAdventure_Sailor_tavern";
		break;
		
		case "NightAdventure_Sailor_tavern":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = "NA_SailorTavern"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// шулер
		case "NightAdventure_Sailor_2_1":
			dialog.text = "¿Capitán?.. ¡hip!.. C-capitán... ¡ayúdame!";
			link.l1 = "¡Déjame en paz, no tengo tiempo!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "¿Qué te pasa?";
			link.l2.go = "NightAdventure_Sailor_2_2";
		break;
		
		case "NightAdventure_Sailor_2_2":
			dialog.text = "Allí... en la taberna... ¡hip!.. ¡el Fullero!";
			link.l1 = "Bueno, ¿y qué tiene de malo eso? En cualquier taberna de cualquier colonia hay tahúres, como suciedad.";
			link.l1.go = "NightAdventure_Sailor_2_3";
		break;
		
		case "NightAdventure_Sailor_2_3":
			dialog.text = "C-capitán, usted... no entiende... ¡hip!... ¡Él me dejó... sin un solo peso! ¡Hip!.. Y luego... me echó... ¡hip!..";
			link.l1 = "Entonces, ¿qué quieres de mí ahora?";
			link.l1.go = "NightAdventure_Sailor_2_4";
		break;
		
		case "NightAdventure_Sailor_2_4":
			dialog.text = "Ven c-conmigo... ¡hip!... ¡Acaba con él! H-haz que... ¡hip!... me devuelva mi dinero. ¡hip!...";
			link.l1 = "No tienes que ser un tahúr para vencer a un borracho en el tablero. Bebe menos la próxima vez.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Bueno, ¿para qué necesito esto, eh? .. Está bien, vamos, veamos a tu timador.";
			link.l2.go = "NightAdventure_Sailor_2_5";
		break;
		
		case "NightAdventure_Sailor_2_5":
			dialog.text = "Solo... hip!.. despaaaacio, p-por favor. No estoy... hip!.. en... pie...";
			link.l1 = "Bien, vamos despacio.";
			link.l1.go = "NightAdventure_Sailor_gambler";
		break;
		
		case "NightAdventure_Sailor_gambler":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = "NA_SailorGambler"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// диалог в таверне с матросом
		case "NA_SailorTavern":
			dialog.text = "C-capitán... ¡hip!.. muchas gracias... ¡me ayudaste! Yo... aquí tienes... ¡hip!.. Es para ti.";
			link.l1 = "Vamos, no importa... No bebas así más. O al menos no busques aventuras.";
			link.l1.go = "NA_SailorTavern_1";
		break;
		
		case "NA_SailorTavern_1":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar, "slave_01");  Log_Info("Ha recibido el Arpón");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar, "potion5");   Log_Info("Has recibido Raíz de jengibre");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar, "cartridge"); Log_Info("Has recibido Cartucho de papel");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar, "amulet_8");  Log_Info("Has recibido el amuleto 'Ancla'.");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar, "amulet_9");  Log_Info("Has recibido el amuleto 'Encolpion'.");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar, "obereg_7");  Log_Info("Has recibido el amuleto 'Percador'.");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar, "obereg_11"); Log_Info("Has recibido el amuleto 'Peregrino'.");}
			}
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// разговор про  шулера
		case "NA_SailorGambler":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShuler0")
			{
				dialog.text = "¡C-capitán!.. El... ¡Hic!.. Tahúr!..";
				link.l1 = "¿Quién, yo? ¿Tahúr?";
				link.l1.go = "NA_SailorGamblerBelka";
			}
			else	
			{
				dialog.text = "¡Ahí está, capitán! ¡Hic!.. S-sentado en la mesa...";
				link.l1 = "Vamos...";
				link.l1.go = "NA_SailorGamblerCards"; 
			}
					
		break;
		// шулер сбежал
		case "NA_SailorGamblerBelka": 
			dialog.text = "No... ¡hic!... ¡Afilador!... ¡Ha desaparecido!...";
			link.l1 = "Bueno, se fue, así que no te esperó.";
			link.l1.go = "NA_SailorGamblerBelka_1";
		break;
		
		case "NA_SailorGamblerBelka_1":
			dialog.text = "¿Y qué es... lo siguiente? ¡Hic!";
			link.l1 = "Bueno, no puedes hacer nada ahora. Definitivamente no voy a buscarlo por la noche en toda la colonia. No bebas así más. O al menos no apuestes mientras estés borracho.";
			link.l1.go = "NA_SailorGamblerBelka_2";
		break;
		
		case "NA_SailorGamblerBelka_2":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		// шулер остался таверне
		case "NA_SailorGamblerCards":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			iNation = npchar.nation
			iRank = MOD_SKILL_ENEMY_RATE+sti(pchar.rank);
			iScl = 15 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("NightAdventure_CardProf", "citiz_"+(rand(9)+11), "man", "man", iRank, iNation, 1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_04", "pistol1", "bullet", iScl*2);
			sld.dialog.filename    = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "NightAdventure_CardProf";
			sld.greeting = "player";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			AddMoneyToCharacter(sld, sti(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(sld, "totem_13");
			FreeSitLocator(pchar.location, "sit_front4");
			ChangeCharacterAddressGroup(sld, pchar.location, "sit", "sit_front4");
			LAi_SetSitType(sld);
			chrDisableReloadToLocation = false;
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// разговор с самим шулером
		case "NightAdventure_CardProf":
			dialog.text = "Te sugiero un juego de dados. ¿Te animas?";
			link.l1 = "De ninguna manera. Soy el capitán del barco y no juego con fulleros. Pero puedo aplastarte fácilmente si no devuelves el dinero a ese buen hombre allá.";
			link.l1.go = "NightAdventure_CardProf_1";
		break;
		
		case "NightAdventure_CardProf_1":
			dialog.text = "¿Con tahúres?! ¿Soy yo un tahúr? ¿A quién devolver el dinero, a ese borracho?! Me ofendes, capitán...";
			link.l1 = "Puedo ofender más. Devuelve el dinero.";
			link.l1.go = "NightAdventure_CardProf_2";
		break;
		
		case "NightAdventure_CardProf_2":
			dialog.text = "Sí, ¡no soy un tahúr! Soy un jugador limpio. La suerte gana, y tu amigo simplemente tuvo mala suerte, eso es todo.";
			link.l1 = "La suerte, ¿eh? Dame tus dados y veré qué tan afortunado será el resultado.";
			link.l1.go = "NightAdventure_CardProf_3";
		break;
		
		case "NightAdventure_CardProf_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveMoney") // отдал деньги
			{
				AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money));
				dialog.text = "Está bien, está bien, cálmate, capitán. Bueno, vencí al borracho, y hice un poco de trampa, y eso es lo que hace cada segundo jugador. Aquí está su dinero.";
				link.l1 = "Eso es mejor. Y, espero que entiendas que si mi amigo ahora dice que esta no es toda la cantidad, entonces volveré a por ti.";
				link.l1.go = "NightAdventure_CardProf_GiveMoney";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveOk") // играл честно
			{
				dialog.text = "Sí, por favor, aquí están mis dados. Ambos juegos. Revisa. No tengo nada que esconder.";
				link.l1 = "Así que... Pareja... Nada... Pareja... Full... Nada... Nada... Dos Parejas... Trío... Nada... Pareja...";
				link.l1.go = "NightAdventure_CardProf_Ok";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerFight") // драка
			{
				dialog.text = "Sí, por favor, aquí están mis dados. Ambos juegos. Comprueba. No tengo nada que ocultar.";
				link.l1 = "Entonces... Cuatro iguales... Cuatro iguales... Full... Full... Cuatro iguales... Póker... Full... Póker... Cuatro iguales... Full... Hmm, ¿y cómo me vas a explicar esto?";
				link.l1.go = "NightAdventure_CardProf_Fight";
			}
		break;
		// разошлись миром
		case "NightAdventure_CardProf_GiveMoney":
			dialog.text = "Entiendo todo, aquí está toda la suma. Buena suerte a ti y a tu amigo.";
			link.l1 = "Tú también.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_1";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_GiveMoney_2";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// матрос забирает свои деньги
		case "NightAdventure_CardProf_GiveMoney_2":
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			dialog.text = "¡Pero... él no quería admitirlo! ¡Hic!..";
			link.l1 = "Sí, lo intenté evadir. Aquí, guarda tu dinero.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_3";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_3":
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
			dialog.text = "C-capitán... ¡hip!.. muchas gracias... ¡me ayudaste! Yo... 'vomita al lado'... aquí tienes... ¡hip!.. Es para ti.";
			link.l1 = "Vamos, ugh... no importa... No bebas así más. O al menos no juegues cuando estés borracho.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_4";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// играл честно
		case "NightAdventure_CardProf_Ok":
			dialog.text = "¿Pues bien? ¿Convencido?";
			link.l1 = "Hum, realmente parecen dados ordinarios ...";
			link.l1.go = "NightAdventure_CardProf_Ok_1";
		break;
		
		case "NightAdventure_CardProf_Ok_1":
			dialog.text = "Te lo dije. Y tu amigo está simplemente borracho. Tampoco quiso admitir su derrota, así que te trajo aquí.";
			link.l1 = "Está bien, lamento el incidente. Buena suerte.";
			link.l1.go = "NightAdventure_CardProf_Ok_2";
		break;
		
		case "NightAdventure_CardProf_Ok_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_Ok_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// подходит матрос
		case "NightAdventure_CardProf_Ok_3":
			dialog.text = "Entonces... ¡hic!.. ¿qué es?.. Él... ¡hic!.. ¿no es un t-tramposo?..";
			link.l1 = "Bueno, parece que ha jugado limpio.";
			link.l1.go = "NightAdventure_CardProf_Ok_4";
		break;
		
		case "NightAdventure_CardProf_Ok_4":
			dialog.text = "¿Y qué es... lo siguiente? ¡Hip!...";
			link.l1 = "Bueno, ya no hay nada que puedas hacer. Honestamente te ganó. No bebas así más. O al menos no apuestes cuando estés borracho.";
			link.l1.go = "NightAdventure_CardProf_Ok_5";
		break;
		
		case "NightAdventure_CardProf_Ok_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// драка 
		case "NightAdventure_CardProf_Fight":
			dialog.text = "Suerte. Sólo tuviste suerte, eso es todo. La suerte es una dama caprichosa.";
			link.l1 = "Hmm, de verdad. Bueno, juguemos contigo entonces, pero ten en cuenta que juego con estos dados!";
			link.l1.go = "NightAdventure_CardProf_Fight_1";
		break;
		
		case "NightAdventure_CardProf_Fight_1":
			dialog.text = "¿Estos?.. Eso es... No, ¡no quiero jugar contigo! Me insultaste. Y de todos modos, estoy sin blanca...";
			link.l1 = "¿Quizás quieras que le cuente a todos en esta taberna sobre tus dados? ¿O tal vez mostrárselos? Y luego les hablas sobre la suerte. ¿Qué te parece?";
			link.l1.go = "NightAdventure_CardProf_Fight_2";
		break;
		
		case "NightAdventure_CardProf_Fight_2":
			dialog.text = "¿Qué?! ¿Quién te crees que eres?! ¿Intentas chantajearme?! ¡Te haré un par de agujeros ahora, si no te largas!";
			link.l1 = "Prefiero quedarme aquí y mostrarle a todos tus dados.";
			link.l1.go = "NightAdventure_CardProf_Fight_3";
		break;
		
		case "NightAdventure_CardProf_Fight_3":
			dialog.text = "¡Bueno, ven aquí, carroña!";
			link.l1 = "No pierdas los pantalones.";
			link.l1.go = "NightAdventure_CardProf_Fight_4";
		break;
		
		case "NightAdventure_CardProf_Fight_4":
			LAi_LocationDisableOfficersGen(pchar.location, true); // офицеров не  пускать
			SetFunctionLocationCondition("NightAdventure_Duel", Locations[FindLocation(pchar.location)].fastreload+"_town", false);
			pchar.quest.NightAdventure_KillPhant.over = "yes";
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// матрос на выходе
		case "NightAdventure_CardProf_Fight_5":
			dialog.text = "¿C-capitán?.. ¿Tú... hic!.. te metiste en una pelea?.. ¿Y este... hic!.. timador?";
			link.l1 = "Él mismo recibió un puñetazo. No jugará con nadie más.";
			link.l1.go = "NightAdventure_CardProf_Fight_6";
		break;
		
		case "NightAdventure_CardProf_Fight_6":
			dialog.text = "Pero... ¡él no q-quería admitirlo! ¡Hic!..";
			link.l1 = "Sí, intentó evadirlo. Simplemente no tenía tu dinero. Probablemente lo gastó.";
			link.l1.go = "NightAdventure_CardProf_Fight_7NM";
			link.l2 = "Sí, intentó evadirlo. Aquí, tu dinero.";
			link.l2.go = "NightAdventure_CardProf_Fight_7";
		break;
		
		case "NightAdventure_CardProf_Fight_7NM": // скажем, что нет денег
			ChangeCharacterComplexReputation(pchar,"nobility", -5); 
			ChangeOfficersLoyality("bad", 2); 
			dialog.text = "¿Y qué sigue... a-a continuación? ¡Hic!";
			link.l1 = "Bueno, ya no puedes hacer nada. Honestamente, te ganó. No bebas así más. O al menos no juegues cuando estés borracho.";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
		break;
		
		case "NightAdventure_CardProf_Fight_7": // деньги есть
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			ChangeCharacterComplexReputation(pchar,"nobility", 3); 
			ChangeOfficersLoyality("good", 1); 
			dialog.text = "C-capitán... ¡hip!.. muchas gracias... ¡me ayudó mucho! Yo...'vomita al lado'... aquí tiene... ¡hip!.. Es para usted.";
			link.l1 = "Vamos, ugh... no importa... No bebas así nunca más. O al menos no juegues cuando estés borracho.";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
		break;
		
		case "NightAdventure_CardProf_Fight_End": 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DialogExit();
			
		break;
		// проводить до пирса
		case "NightAdventure_Sailor_3_1":
			dialog.text = "¿Capitán?.. ¡hip!.. C-capitán... escoltadme hasta el m-m-muelle... ¡hip!.. ¿eh? Por favor. Yo... ¡hip!.. n-necesito ir al ... barco... El contramaestre... va a maldecir... ¡hip!.. si llego t-tarde...";
			link.l1 = "¡Quítame las manos de encima, no tengo tiempo!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Está bien, vamos. No parece que puedas llegar allí por ti mismo.";
			link.l2.go = "NightAdventure_Sailor_3_2";
		break;
		
		case "NightAdventure_Sailor_3_2":
			dialog.text = "Solo... hic!.. len-ta-men-te, p-por favor. No estoy... hic!.. capaz de... mantenerme en pie...";
			link.l1 = "Está bien, vamos despacio.";
			link.l1.go = "NightAdventure_Sailor_3_3";
		break;
		
		case "NightAdventure_Sailor_3_3":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorBoat")
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorBoat"; 
			}
			else
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorShip"; 
			}
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocatorCondition("NightAdventure_ToBoat",  npchar.City+"_town", "quest", "quest1", false)
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		// вариант просто проводить
		case "NA_SailorBoat":
			dialog.text = "C-capitán... ¡hip!.. muchas gracias... ¡me ayudaste mucho! Yo...'vomita a un lado'... aquí tienes... ¡hip!.. Es para ti.";
			link.l1 = "Vamos, ugh... no importa... No bebas así más. O al menos no busques aventura.";
			link.l1.go = "NA_SailorBoat_1";
		break;
		
		case "NA_SailorBoat_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13)  {GiveItem2Character(pchar, "slave_01");  Log_Info("Ha recibido Arpón");}
			if(GetDataDay() >= 13 && GetDataDay() < 19)  {GiveItem2Character(pchar, "potion5");   Log_Info("Has recibido Raíz de jengibre");}
			if(GetDataDay() >= 19 && GetDataDay() < 25)  {GiveItem2Character(pchar, "cartridge"); Log_Info("Has recibido Cartucho de papel");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar, "amulet_8");  Log_Info("Has recibido el amuleto 'Ancla'.");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar, "amulet_9");  Log_Info("Has recibido el amuleto 'Encolpion'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar, "obereg_7");  Log_Info("Has recibido el amuleto 'Percador'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar, "obereg_11"); Log_Info("Has recibido el amuleto 'Peregrino'.");}
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", -1); 
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// просится на корабль
		case "NA_SailorShip":
			dialog.text = "¡C-capitán!.. ¡Barco!";
			link.l1 = "¿Qué 'barco'?";
			link.l1.go = "NA_SailorShip_1";
		break;
		
		case "NA_SailorShip_1":
			dialog.text = "¡B-barco!.. ¿Dónde está?.. ¡hip!..";
			link.l1 = "Obviamente, se fue. Necesitas beber menos en las tabernas. Todo el barco no esperará a un marinero borracho.";
			link.l1.go = "NA_SailorShip_2";
		break;
		
		case "NA_SailorShip_2":
			dialog.text = "Pero yo... ¡hip!... no estoy borracho... casi... tal vez...";
			link.l1 = "Ah, sí, en efecto. Buena suerte.";
			link.l1.go = "NA_SailorShip_3";
		break;
		
		case "NA_SailorShip_3":
			dialog.text = "¡Espera, c-capitán! ¡L-llevame... hic!.. a tu b-barco! No b-beberé más... hic!..";
			if(GetFreeCrewQuantity(pchar) > 0)
			{
				link.l1 = "Bueno, ¿qué puedes hacer al respecto? Pero ve inmediatamente al barco. Y Dios no lo quiera, si te veo borracho en algún lugar, fregarás la cubierta hasta la próxima parada en el puerto.";
				link.l1.go = "NA_SailorShip_4";
			}
			link.l2 = "¿Para que te emborraches con mi salario y luego tenga que buscarte por todas las tabernas y portales de la colonia? No, no necesito tal felicidad.";
			link.l2.go = "NA_SailorShip_6";
			
		break; 
		
		case "NA_SailorShip_4": 
			AddCharacterCrew(pchar, 1);
			dialog.text = "¡Sí, c-capitán!.. ¡hip!..";
			link.l1 = "¡Lo tengo!";
			link.l1.go = "NA_SailorShip_5";
		break;
		
		case "NA_SailorShip_5": 
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", 5.0); // побежит вдохновленный 
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NA_SailorShip_6": 
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload4_back");
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "NightAdventure_OpenLoc", -1);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// пьяные наезды
		case "NightAdventure_Bull":
			switch (rand(5))
			{
				case 0:
				dialog.text = "¿Capitán?.. ¡hip!.. Eres... una rata de tierra... ¡hip!.. ¡no un capitán!..";
				link.l1 = "He cortado a cientos de personas como tú en peleas de abordaje, así que lárgate, borracho.";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 1:
				dialog.text = "Capitán... ¡hic!.. ¿C-capitán de ese t-trasto en la redada?.. ¡hic!..";
				link.l1 = "Si ves este abrevadero en el horizonte cuando estés en el mar, es mejor que te lances al agua de inmediato: con los tiburones tendrás más posibilidades de sobrevivir que contra mi barco. ¡Ahora, lárgate!";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 2:
				dialog.text = "¿Capitán?.. ¡hip!.. ¡Eres un bebedor de leche, no un capitán!.. Tu m-madre todavía era una niña... ¡hip!.. cuando yo surcaba los mares...";
				link.l1 = "Pero a tu madre probablemente le alegraría saber que un muchachito como yo se convirtió en capitán, y tú quedaste siendo un marinero borracho, apto solo para fregar las cubiertas.";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 3:
				dialog.text = "¿Capitán?.. ¡Cuidado... hic!.. capitán... te tumbaré los dientes... hic!.. no tendrás tiempo ni de parpadear!..";
				link.l1 = "El retroceso te matará. ¡Fuera de aquí! Sáqueme los dientes si te atreves...";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 4:
				dialog.text = "¿Capitán?.. Parece... hic!.. a-a algún tipo de pilluelo...";
				link.l1 = "Parece que aún no te has mirado en el espejo...  ";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 5:
				dialog.text = "¿C-capitán?.. Yo no... ¡hic!.. hubiera aceptado s-servir... en tu barco... ¡hic!..";
				link.l1 = "Y nadie te ofreció ir a mi barco para que aceptaras. Quítate de mi camino.";
				link.l1.go = "NightAdventure_End";
				break;
			}
		break;
		
		case "NightAdventure_End":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_Again";
		break;
		
		case "NightAdventure_Again":
			NextDiag.TempNode = "NightAdventure_Again";
			dialog.text = "¡Hic!..";
			link.l1 = "Ve a dormir.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_SailorAgain":
			dialog.text = "¡Hic!.. Sí... ¿todavía lejos?..";
			link.l1 = "Estamos cerca, ten paciencia.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// <-- матрос
		// горожанин -->
		case "NightAdventure_Citizen":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "¿Q-quién... hic!.. eres tú?..";
			link.l1 = "Soy capitán "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Lo siento, amigo, tengo prisa.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_CitizenHomie":          link.l1.go = "NightAdventure_Citizen_1_1"; break; // выручить приятеля
				case "NightAdventure_CitizenHomieSolderNM":  link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_CitizenHomieSolderGM":  link.l1.go = "NightAdventure_Citizen_1_1"; break;
				case "NightAdventure_CitizenHomieOfficer":   link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1";  break; // шулер
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1";  break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";        break;// наезд
			}
		break;
		
		// дружок
		case "NightAdventure_Citizen_1_1":
			dialog.text = "¿Capitán?.. ¡hic!.. C-capitán... ¡ayúdame! Yo... quiero decir... ¡hic!.. mi amigo... realmente necesita tu a-ayuda! Por favor.";
			link.l1 = "No voy a resolver los problemas de cada borracho que encuentro en medio de la noche..";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Bien, dime qué le pasó a tu amigo allí.";
			link.l2.go = "NightAdventure_Citizen_1_2";
		break;
		
		case "NightAdventure_Citizen_1_2":
			dialog.text = "Mi amigo ... él, en general ... se emborrachó. Así, en general ... ¡hip! ... se emborrachó ...";
			link.l1 = "Por supuesto, puse en cintura a los marineros que estaban bebiendo en servicio, pero con métodos bastante radicales. No creo que tu amigo lo necesite.";
			link.l1.go = "NightAdventure_Citizen_1_3";
		break;
		
		case "NightAdventure_Citizen_1_3":
			dialog.text = "¡No! Él... él está con la g-guardia. Se a-arrgumentó con él. Y se metió en una pelea. Y él... ¡hip!.. fue llevado a la prisión... ¡está solo b-borracho!";
			link.l1 = "¿Y qué quieres de mí ahora? Él mismo tiene la culpa: hay que beber menos. O al menos no buscar aventuras por su cuenta...";
			link.l1.go = "NightAdventure_Citizen_1_4";
		break;
		
		case "NightAdventure_Citizen_1_4":
			dialog.text = "Habla con el alcaide, cap... ¡hip! ... capitán. Él dejará ir... ¡déjalo ir! Hmm... aquí está... ¡hip!.. qué suerte tienes... Mi amigo solo... discutió... bueno... y quiso darme un puñetazo en la cara... pero... ¡hip!... no consiguió el arma...";
			link.l1 = "Ahora no tengo nada más que hacer, excepto sacar borrachos de la prisión por la noche que se pelearon con los guardias. No, que se quede unos días. Quizás la próxima vez lo pienses mejor.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Aye, al infierno contigo. Bien, hablaré con el carcelero.";
			link.l2.go = "NightAdventure_Citizen_1_5";
			if(GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && !CheckNationLicence(HOLLAND))
			{
				link.l2 = "No estoy seguro de que al alcaide le guste mi acento. Solo se lo informará al gobernador más tarde. Así que sigue adelante sin mí.";
				link.l2.go = "NightAdventure_Citizen_RE";
			}
			if(ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
			{
				link.l2 = "Me temo, amigo, que el camino a los calabozos locales está bloqueado para mí. El carcelero guarda mi retrato como un icono, y no tengo intención de instalarme en esos hospitalarios apartamentos suyos. Así que lo siento, pero no puedo ayudarte.";
				link.l2.go = "NightAdventure_Citizen_NR";
			}
		break;
		
		case "NightAdventure_Citizen_1_5":
			DialogExit();
			pchar.GenQuest.NightAdventureToJail = true;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			chrDisableReloadToLocation = true; //закрыть локацию пока бежит
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_CitizenHomiePresent":
			dialog.text = "T-gracias... capitán. Y por mi a-amigo también. A-aquí... es para usted.";
			link.l1 = "La próxima vez, vigila a tu amigo cuando se emborrache y decida pelear con los guardias. No todas las noches hay capitanes que caminan por las calles, listos para negociar con el alcaide por algunos borrachos. Buena suerte.";
			link.l1.go = "NightAdventure_CitizenHomiePresent_1";
		break;
		
		case "NightAdventure_CitizenHomiePresent_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5.0);
			sld = characterFromId("NightAdventure_Homie");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			if(GetDataDay() < 7) 						{GiveItem2Character(pchar, "indian_2");  Log_Info("Has recibido el amuleto 'Probador de pólvora'.");}
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar, "obereg_5");  Log_Info("YHas recibido el amuleto 'Tortuga de jade'.");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar, "obereg_6");  Log_Info("Has recibido el amuleto 'Puño de mono'.");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar, "obereg_8");  Log_Info("Has recibido el amuleto 'Abalorios de mercader'.");}
			if(GetDataDay() == 25) 		    			{GiveItem2Character(pchar, "indian_9");  Log_Info("Has recibido el amuleto 'Baldo'.");}
			if(GetDataDay() == 26) 	    				{GiveItem2Character(pchar, "obereg_11"); Log_Info("Has recibido el amuleto 'Peregrino'.");}
			if(GetDataDay() >= 27 && GetDataDay() < 31) {GiveItem2Character(pchar, "obereg_4");  Log_Info("Has recibido el amuleto 'Abanico de gitana'.");}
			if(GetDataDay() == 31) 	    				{GiveItem2Character(pchar, "amulet_11"); Log_Info("YHas recibido el amuleto 'Cimaruta'.");}
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_Citizen_RE":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)  < (rand(100)+rand(100)))
			{
				dialog.text = "¡Oh!.. Entonces sé cómo... ¡hip!.. liberar a mi... a-amigo... ¡hip!.. ¡Guardias! ¡Un e-espía en la ciudad!.. ¡hip!..";
				link.l1 = "Elegiste una muy mala opción para liberar a tu amigo.";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "Ah, e- extranjero... ¡hip! .. Tú... tendrás problemas... ¡hip! .. Está bien... tengo aquí... ¡hip! .. todo está bajo control.";
				link.l1 = "Por supuesto. Si algo sucede, vendré a ti de inmediato.";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Citizen_NR":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE) < (rand(100)+rand(100)))
			{
				dialog.text = "Ah ... así que tú ... ¡hic! .. ¡Eres un criminal! ¡Guardias!";
				link.l1 = "¡Ah, así que ahora hablas de esa manera!";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "Oh, cómo... ¡hip! ... lo siento. ¿Y qué si... me dejas... negociar por ti con... ¡hip!.. el guardián, y tú... ¡hip!.. por m-mi amigo?..";
				link.l1 = "No, no necesitas negociar por mí, gracias. Buena suerte.";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Fight":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			LAi_group_Attack(NPChar, Pchar);
		break;
		// контрабандист 
		case "NightAdventure_Pirate": 
			LAi_RemoveLoginTime(npchar);
			dialog.text = "¿Q-qui-quién... hic!.. eres tú?...";
			link.l1 = "Soy capitán "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Lo siento, compañero, tengo prisa.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_Bull":          		 link.l1.go = "NightAdventure_Bull";       break; // пьяные наезды
				case "NightAdventure_PiratePeace":           link.l1.go = "NightAdventure_PirateCave"; break; // до пещеры
				case "NightAdventure_PirateBad":             link.l1.go = "NightAdventure_PirateCave"; break;
			}
		break;
		
		case "NightAdventure_PirateCave":
			dialog.text = "¿Capitán?.. ¡hip!.. C-capitán... escucha, acompáñame a la cueva cerca de la ciudad... ¡hip!.. ¿eh? P-por favor.";
			link.l1 = "¿A la cueva? No entiendo. ¿Por qué vas a la cueva? ¿Y por qué me necesitas a mí?";
			link.l1.go = "NightAdventure_PirateCave_1";
		break;
		
		case "NightAdventure_PirateCave_1":
			dialog.text = "Verá... c-capitán... ¡hic!.. Me he quedado sin d-dinero para las bebidas... Y en... ¡hic!.. en una cueva tengo... un escondite, así que... ¡hic!.. Pero yo... es que... tengo miedo de ir solo por la s... s... selva... ¡hic!.. de noche... Así que...";
			link.l1 = "¡Quítate de encima, no tengo tiempo!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Está bien, vamos. No parece que puedas llegar allí por ti mismo";
			link.l2.go = "NightAdventure_PirateCave_2";
		break;
		
		case "NightAdventure_PirateCave_2":
			dialog.text = "Solo... hic!.. len-ta-men-te, p-por favor. No... hic!.. puedo... mantenerme... en pie...";
			link.l1 = "Bien, vamos despacio.";
			link.l1.go = "NightAdventure_PirateCave_3";
		break;
		
		case "NightAdventure_PirateCave_3":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = true; // что взяли квест
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			string NAIsland = GetIslandByCityName(npchar.city);
			string NACave = "absent. Tell belamour that you are";
			// найти пещеру на острове
			i = Findlocation(NAIsland+"_Grot");
			if(i != -1) NACave = NAIsland+"_Grot";
			i = Findlocation(NAIsland+"_Cave");
			if(i != -1) NACave = NAIsland+"_Cave";
			// для мейна и капстервиля
			i = Findlocation(npchar.city+"_Cave");
			if(i != -1) NACave = npchar.city+"_Cave";
			i = Findlocation(npchar.city+"_Grot");
			if(i != -1) NACave = npchar.city+"_Grot";
			
			log_testinfo("Cueva "+NACave+" en la isla " +NAIsland);
			SetFunctionLocationCondition("NightAdventure_InCave", NACave, false);
			SetFunctionLocationCondition("NightAdventure_InFort", npchar.city+"_ammo", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_PirateCave_4": // диалог в пищере
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PiratePeace")
			{
				AddMoneyToCharacter(pchar, 1000);
				TakeNItems(pchar, "potionrum", 1);   
				TakeNItems(pchar, "potionwine", 1);
				PlaySound("interface\important_item.wav");
				Log_Info("Ha recibido alcohol")
				dialog.text = "C-capitán... ¡hip!.. muchas gracias... ¡me ayudaste! Yo... aquí tienes... ¡hip!.. Es para ti.";
				link.l1 = "Vamos, ugh... olvídalo... No bebas así más.";
				link.l1.go = "NightAdventure_PirateCave_4_1";
				break;
			} 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PirateBad")
			{
				dialog.text = "¡Excelente, capitán! Me alegra que haya aceptado.";
				link.l1 = "Bueno, ¿dónde está tu escondite? Espera un minuto, parece que no estás borracho.";
				link.l1.go = "NightAdventure_PirateCave_5";
				break;
			} 
		break;
		
		case "NightAdventure_PirateCave_4_1": // мирный исход
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
		break;
		
		case "NightAdventure_PirateCave_5": // драка
			dialog.text = "Sí, no bebí mucho, no te preocupes por mí. Y sobre el escondite... ¡Chicos!";
			link.l1 = "...";
			link.l1.go = "NightAdventure_PirateCave_6";
		break;
		
		case "NightAdventure_PirateCave_6": 
			DialogExit();
			AddDialogExitQuestFunction("NightAdventure_PiratesInCave");
		break;
		
		case "NightAdventure_PirateCave_7": 
			dialog.text = "Chicos, traje un alijo aquí. Necesitan abrirlo. A menos, por supuesto, que este alijo se abra por sí mismo, de buena manera. Capitán, ¿qué piensas?";
			link.l1 = LinkRandPhrase("Creo que sería mejor si te embriagaras hasta perder la memoria. Al menos seguirías con vida. Y ahora solo hay un camino ... "," Creo que no tienes la cabeza muy bien puesta, ya que decidiste robar al capitán de un barco de guerra ... "," Creo que probablemente estás cansado de vivir, ya que decidiste intentar esto...");
			link.l1.go = "NightAdventure_PirateCave_8F";
			link.l2 = "Bien, supongo que es mejor irnos en buenos términos. ¿Y cuánto necesitas?";
			link.l2.go = "NightAdventure_PirateCave_8A";
		break;
		
		case "NightAdventure_PirateCave_8F": 
			dialog.text = "Entonces, ¿de buena manera no abriremos el escondite?";
			link.l1 = "Me temo que ese fue el último escondite de tu vida.";
			link.l1.go = "NightAdventure_PirateCave_9F";
		break;
		
		case "NightAdventure_PirateCave_9F": 
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			sld = CharacterFromID(pchar.GenQuest.NightAdventureId);
			sld.SaveItemsForDead   = true; // сохранять на трупе вещи
			sld.DontClearDead = true;  // не убирать труп через 200с
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			LAi_SetFightMode(pchar, true);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_PirateCave_8A": // испугался
			iMoney = sti(pchar.money)/3;
			dialog.text = "Oh, no somos codiciosos. Solo "+FindRussianMoneyString(iMoney)+"."; 
			link.l1 = "Me temo que ese fue el último alijo de tu vida.";
			link.l1.go = "NightAdventure_PirateCave_9F";
			link.l2 = "Bien, hazlo a tu manera. Nunca más ayudaré a un borracho...";
			link.l2.go = "NightAdventure_PirateCave_9A";
		break;
		
		case "NightAdventure_PirateCave_9A": 
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_PirateCaveAgain";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false); 
			iMoney = sti(pchar.money)/3;
			AddMoneyToCharacter(pchar, -iMoney);
			AddMoneyToCharacter(npchar, iMoney);
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				sld.dialog.currentnode = "NightAdventure_PirateCaveAgain";
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_Group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "NightAdventure_PirateCaveAgain": 
			dialog.text = "Capitán, me sorprendes con tu generosidad. ¿Quieres compartir más con nosotros?";
			link.l1 = "Ya te he dado todo. Me voy...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_PirateCaveAgain";
		break;
		
		// дворянин -->
		case "NightAdventure_Noble":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "¿Q-quién... hic!.. eres tú?...";
			link.l1 = "Soy capitán "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Lo siento, camarada, tengo prisa.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_NobleGame":             link.l1.go = "NightAdventure_NobleGame";  break; // карты
				case "NightAdventure_NobleGameDuel":         link.l1.go = "NightAdventure_NobleGame";  break; 
				case "NightAdventure_NobleWhore": 			 link.l1.go = "NightAdventure_NobleWhore"; break; // жрица
			}
		break;
		// карты
		case "NightAdventure_NobleGame": 
			dialog.text = "¿Capitán?.. ¡hic!.. oh, "+GetAddress_Form(NPChar)+" ... L-lo s-siento mucho... ¡hip!.. por mi... c-condición. ¿Te gustaría acompañarme? ¡hip!.. P-por favor."; 
			link.l1 = "Lo siento, "+GetAddress_Form(NPChar)+", pero estoy ocupado."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "¿Unirme? Lo siento, pero hoy no bebo..."; 
			link.l2.go = "NightAdventure_NobleGame_1";
		break;
		
		case "NightAdventure_NobleGame_1":
			dialog.text = "¡Oh, no necesitas... hic!.. b-bebida! Aquí está la cosa... Bueno... Tomé un trago con mi amigo... Así que... ya estoy mareado... ¿ves?";
			link.l1 = "Está bien. Entonces, ¿necesitas ayuda para despejarte?";
			link.l1.go = "NightAdventure_NobleGame_2";
		break;
		
		case "NightAdventure_NobleGame_2": 
			dialog.text = "¡No realmente! Estoy bien. Ahora quiero j-jugar... a las cartas, en general quiero jugar... ¡hip!.. P-pero no por miserables... p-pesos... con esos harapientos en... ¡hip!.. la t-taberna... ¡Sino con un verdadero noble! ¡hip!.. ¡Por apuestas reales!.."; 
			link.l1 = "Lo siento, "+GetAddress_Form(NPChar)+", qué puedo decir... No soy fanático del juego. Hay que pagar los sueldos de los marineros, mantener el barco, ya sabes..."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Hmm, está bien, juguemos. ¿Vamos a la taberna?"; 
			link.l2.go = "NightAdventure_NobleGame_3";
		break;
		
		case "NightAdventure_NobleGame_3": 
			dialog.text = "¡Está bien! Sólo... hic!.. des-pa-cio, p-por favor. Yo no... hic!.. puedo... ponerme en pie..."; 
			link.l1 = "Está bien, vayamos despacio."; 
			link.l1.go = "NightAdventure_NobleGame_4";
		break;
		
		case "NightAdventure_NobleGame_4":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleGame_5"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleGame_5": 
			pchar.quest.NightAdventure_Intavern.over = "yes";
			FreeSitLocator(pchar.location, "sit_front4");
			FreeSitLocator(pchar.location, "sit_base4");
			dialog.text = "¡P-por esa mesa... hic!.. vamos!"; 
			link.l1 = "Está bien, vamos."; 
			link.l1.go = "NightAdventure_NobleGame_6";
		break;
		
		case "NightAdventure_NobleGame_6": 
			DialogExit();
			//if(CheckAttribute(pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LAi_Fade("NightAdventure_NobleGameDialogPrep", "NightAdventure_NobleGameDialog");
		break;
		
		case "NightAdventure_NobleGame_7": 
			dialog.text = "¡No tienes... idea, c-capitán, de lo... hip!.. de lo feliz que estoy de encontrarme con un verdadero noble! hip!.. En este yermo... normalmente solo... hip!.. b-basura..."; 
			link.l1 = "Sí, está a montones en las colonias locales. Bueno, ¿jugamos?"; 
			link.l1.go = "NightAdventure_NobleGame_8";
		break;
		
		case "NightAdventure_NobleGame_8": 
			dialog.text = "¡Sí, juguemos! ¡hip!.. ¿Qué apuestas?.."; 
			if(sti(pchar.money) > 10000)
			{
				link.l1 = "Jugamos por 1000 pesos."; 
				link.l1.go = "NightAdventure_NobleGame_9_1";
			}
			if(sti(pchar.money) > 20000)
			{
				link.l2 = "Jugamos por 2000 pesos."; 
				link.l2.go = "NightAdventure_NobleGame_9_2";
			}
			link.l3 = "Hmm, lo siento, parece que mi bolsillo está vacío en este momento..."; 
			link.l3.go = "NightAdventure_NobleGame_Голодранец";
		break;
		
		case "NightAdventure_NobleGame_Голодранец": 
			dialog.text = "¿Q-qué?.. ¿No tienes... hic!.. dinero para jugar... conmigo?.."; 
			link.l1 = "Bueno, pasa. Jugaremos la próxima vez, no te preocupes."; 
			link.l1.go = "NightAdventure_NobleGame_Голодранец_1";
		break;
		
		case "NightAdventure_NobleGame_Голодранец_1": 
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // открыть локацию
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_9_1": 
			DialogExit();
			npchar.money = 15000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 1000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_9_2": 
			DialogExit();
			npchar.money = 30000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 2000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_Win": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Win");
			dialog.text = "¡Hic!.. ¡Lo pasé de maravilla, c-capitán! ¡hic!.."; 
			link.l1 = "Estoy de acuerdo contigo. Al menos toma un descanso de los negocios."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd";
		break;
		
		case "NightAdventure_NobleGame_Lose": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Fail");
			dialog.text = "¡Hic!.. ¡Lo pasé de maravilla, c-capitán! ¡hic!.."; 
			link.l1 = "Estoy de acuerdo contigo. Al menos tómate un descanso de los negocios."; 
			link.l1.go = "NightAdventure_NobleGame_Lose_1";
		break;
		
		case "NightAdventure_NobleGame_Lose_1": 
			dialog.text = "A veces solo necesitas... ¡hip!.. p-pasar tiempo con una agradable... ¡hip!.. compañía. ¡Muchísimas gracias... ¡hip!.. por tu compañía!"; 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleGameDuel")
			{		
				link.l1 = "Sí, acabo de perder en pedazos. ¿Y cómo es posible que ganaste incluso en esos casos cuando tenía todas las posibilidades de ganar?"; 
				link.l1.go = "NightAdventure_NobleGame_Duel";
				break;
			}	
			link.l1 = "Mutuamente, gracias por el juego y por la conversación."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd": 
			dialog.text = "A veces solo necesitas... ¡hip!.. p-pasar tiempo con una buena... ¡hip!.. compañía. Muchas gracias... ¡hip!.. por tu compañía!"; 
			link.l1 = "Mutuamente, gracias por el juego y por la conversación."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // открыть локацию
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_Duel": 
			dialog.text = "Solo suerte, c-capitán... ¡hip!.."; 
			link.l1 = "No parece solo suerte...."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_1";
		break;
		
		case "NightAdventure_NobleGame_Duel_1": 
			dialog.text = "¿Qué insinúas? ¿Quieres decir que jugué deshonestamente? ¡Tú mismo lo viste todo, tomamos cartas del mismo mazo!"; 
			link.l1 = "Sí, lo vi. Y también vi que hace un minuto apenas movías la lengua, y ahora hablas como si no estuvieras borracho."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_2";
		break;
		
		case "NightAdventure_NobleGame_Duel_2": 
			dialog.text = "¡Ah, maldición! ¡Y me atrapaste bien! Está bien, lo admito, no me esconderé. No estaba borracho. Pero ¿sabes lo bien que la gente cae por esos supuestos ricos y borrachos que quieren jugar a las cartas? Todo aquel que tiene algo para apostar es casi el primero en correr a la taberna para rápidamente obtener una ganancia indudablemente grande de un noble indudablemente rico pero borracho. Déjame decirte que eres el primero en llegar al fondo de mí."; 
			link.l1 = "Entonces, ¿qué ahora? ¿Me devolverás mi dinero de buena manera?"; 
			link.l1.go = "NightAdventure_NobleGame_Duel_3";
		break;
		
		case "NightAdventure_NobleGame_Duel_3": 
			dialog.text = "Ja ja ja, no me hagas reír, capitán. ¡Por supuesto, no te devolveré nada! Y no pienses que puedes obligarme. Puedo fácilmente hacerme pasar por un noble respetado que es atacado por algún capitán descarriado. Así que mi consejo para ti es: acepta tu derrota y simplemente vete."; 
			link.l1 = "Bueno, sinceramente deseo que no te encuentres conmigo en circunstancias menos afortunadas, porque entonces ya no te reirás así. Adiós."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
			link.l2 = "Y mi consejo para ti, intenta encontrar tiempo para conseguir una espada."; 
			link.l2.go = "NightAdventure_NobleGame_Duel_4";
		break;
		
		case "NightAdventure_NobleGame_Duel_4": 
			dialog.text = "No te atreverías... Es una taberna, llena de gente..."; 
			link.l1 = "Solo soy un capitán descarriado, ¿qué me importan las reglas de decencia? Y en la taberna del puerto por la noche, ¿qué podría pasar...? De todas formas manejo la espada mejor que tú."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_5";
		break;
		
		case "NightAdventure_NobleGame_Duel_5": 
			dialog.text = "¡¿Oh, es así?! ¡Bueno, ahora veremos quién la maneja mejor!"; 
			link.l1 = "A su servicio..."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_6";
		break;
		
		case "NightAdventure_NobleGame_Duel_6": 
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionLocationCondition("NightAdventure_KillPhant", NPChar.City+"_town", false);
			npchar.money = 0;
			AddMoneyToCharacter(npchar, makeint(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(npchar, "totem_13");
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			chrDisableReloadToLocation = false; // открыть локацию
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// жрица
		case "NightAdventure_NobleWhore": 
			dialog.text = "¿Capitán?.. ¡hic!.. oh, "+GetAddress_Form(NPChar)+" ... l-lo siento m-mucho... ¡hip!.. por mi... c-condición. ¿Puedes ayudarme? ¡hip!.. P-por favor."; 
			link.l1 = "Lo siento, "+GetAddress_Form(NPChar)+",  pero estoy ocupado."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Oh... escuchando."; 
			link.l2.go = "NightAdventure_NobleWhore_1";
		break;
		
		case "NightAdventure_NobleWhore_1": 
			dialog.text = "Es una cosa así... En general... Estoy... ya mareado... Puedes ver... ¡hip!.. ¿sí?"; 
			link.l1 = "Para ser honesto, sí. ¿Necesitas ayuda para despejarte?"; 
			link.l1.go = "NightAdventure_NobleWhore_2";
		break;
		
		case "NightAdventure_NobleWhore_2": 
			dialog.text = "¡Para nada! Estoy b-bien. Quiero una dama. Pero estoy tan b-borracho... ¡hip!.. La m-madame me echará, así que. ¿Podrías... hip!... n-negociar por mí? Te daré dinero."; 
			link.l1 = "Lo siento, "+GetAddress_Form(NPChar)+", pero cómo puedo decirte... No voy a burdeles. Honor, reputación... ya sabes ..."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Oh, está bien, te ayudaré."; 
			link.l2.go = "NightAdventure_NobleWhore_3";
		break;
		
		case "NightAdventure_NobleWhore_3": 
			dialog.text = "Solo... hipo!.. leeeento, p-por favor. No estoy... hipo!.. capaz de... levantarme..."; 
			link.l1 = "Está bien, vamos despacio."; 
			link.l1.go = "NightAdventure_NobleWhore_4";
		break;
		
		case "NightAdventure_NobleWhore_4":
			DialogExit();
			if(npchar.city != "Charles" || npchar.city != "Tortuga") // вход только с парадного
			{
				LocatorReloadEnterDisable(npchar.city+"_town", "reload91", true);
			}
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventure_money = 3000+(rand(4)*500);
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleWhore_5"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_InBrothel", npchar.City+"_Brothel", false);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleWhore_5": 
			pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhoreMoney";
			AddMoneyToCharacter(pchar, 5000);
			dialog.text = "Aquí está el dinero... ¡hip!... Te estaré esperando a-aquí."; 
			link.l1 = "Bien, volveré pronto."; 
			link.l1.go = "NightAdventure_NobleWhore_6";
		break;
		
		case "NightAdventure_NobleWhore_6": 
			LAi_SetCitizenType(npchar);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload1_back", true); 
			LocatorReloadEnterDisable(npchar.city + "_SecBrRoom", "reload2", true); 
			NPChar.Dialog.currentnode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "J-justo... tráeme... hic!.. lo... mejor!.. Sí..."; 
			link.l1 = "Está bien, de acuerdo, lo entiendo."; 
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleWhore_7": // заказ исполнен
			dialog.text = "¡Hic!.. ¿Cuánto tiempo más?"; 
			link.l1 = "La mejor chica de esta colonia te está esperando arriba."; 
			link.l1.go = "NightAdventure_NobleWhore_8";
		break;
		
		case "NightAdventure_NobleWhore_8": 
			dialog.text = "¡Sí!.. Esta noche... es genial... G-gracias, "+GetAddress_Form(NPChar)+". El resto del dinero... ¡hip!... tómalo. Y me hundo... en... mi..... hermosa... da-dama...";
			link.l1 = "Bueno, que lo pases bien."; 
			link.l1.go = "NightAdventure_NobleWhore_9";
		break;
		
		case "NightAdventure_NobleWhore_9": 
			DialogExit();
			chrDisableReloadToLocation = true; // закрыть пока бежит
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "", "", "", "NightAdventure_OpenBrothel", -1);
		break;
		
		case "NightAdventure_NobleBrothelAgain":
			NextDiag.TempNode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "¡Hic!.. ¿Cuánto más tiempo?";
			link.l1 = "Pronto negociaré, ten paciencia.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleEnd":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_NobleEndAgain";
		break;
		
		case "NightAdventure_NobleEndAgain":
			NextDiag.TempNode = "NightAdventure_NobleEndAgain";
			dialog.text = "¡Hic!..";
			link.l1 = "Necesitas dormir.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleTownAgain":
			dialog.text = "¡Hic!.. Sí... ¿todavía falta mucho?..";
			link.l1 = "Estamos casi aquí, ten paciencia.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// <-- ночной приключенец
		
		// belamour квест на получение фонаря Xenon -->
		case "CemeteryMan":
			dialog.text = "¿Eh? ¿Quién eres tú? ¿Qué haces aquí?";
			link.l1 = "Podría preguntarte lo mismo.";
			link.l1.go = "CemeteryMan_1";
		break;
		
		case "CemeteryMan_1":
			dialog.text = "¿Nosotros? Oh, nosotros... um... Estamos recogiendo flores aquí...";
			link.l1 = "¿Flores del cementerio? Bueno, ¿cómo va el herbario?";
			link.l1.go = "CemeteryMan_2";
		break;
		
		case "CemeteryMan_2":
			dialog.text = "¿Herb... Está relacionado con las hierbas?";
			link.l1 = "Entonces... creo que entiendo lo que está pasando aquí.";
			link.l1.go = "CemeteryMan_3";
		break;
		
		case "CemeteryMan_3":
			dialog.text = "¡No somos merodeadores! ¡No hables de nosotros así! Somos solo...";
			link.l1 = "¿Qué?";
			link.l1.go = "CemeteryMan_4";
		break;
		
		case "CemeteryMan_4":
			dialog.text = "Bueno, nosotros... ¡Mi padre nos prohíbe vernos! ¡Y su padre también! Así que nosotros... estábamos buscando un lugar sin testigos. Para estar solos. La cerradura de la puerta está rota de todos modos, así que es fácil entrar aquí...";
			link.l1 = "Ya veo de dónde provenían aquellos aterradores gemidos del alma inquieta...";
			link.l1.go = "CemeteryMan_5";
		break;
		
		case "CemeteryMan_5":
			DialogExit();
			sld = characterFromId("CemeteryCouple_2");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "CemeteryMan_6":
			dialog.text = "Bueno, si lo has averiguado todo, ¿quizás nos dejes en paz?";
			link.l1 = "¿No tienes miedo de concertar tus citas en una cripta? No es el mejor lugar...";
			link.l1.go = "CemeteryMan_7";
		break;
		
		case "CemeteryMan_7":
			dialog.text = "¡No somos supersticiosos! Y aunque fuera aterrador, ¿qué opción tenemos? En la ciudad, los padres se habrían enterado de inmediato. Pero aquí nadie nos delatará. Así que, por ahora, es la mejor opción.";
			link.l1 = "Lo siento mucho, pero ¿podrías buscar otro lugar? No me malinterpretes, entiendo todo... la juventud y todo eso... pero tus citas asustaron al guardián del cementerio hasta la muerte, con todos esos ruidos y gemidos que salen de la cripta cada noche.";
			link.l1.go = "CemeteryMan_8";
		break;
		
		case "CemeteryMan_8":
			dialog.text = "Bueno... Asustar al guardia no era parte de nuestro plan. Pero entonces, ¿dónde más podemos encontrarnos? ¿O sugieres que tengamos nuestras citas bajo el cielo abierto?";
			link.l1 = "El amor no conoce fronteras. Encuentra otro lugar donde definitivamente no molestarás a nadie. Entonces nadie te molestará a ti. Probablemente. Y es mejor resolver las cosas con tus padres, ¿no planeas esconderte para siempre, verdad?";
			link.l1.go = "CemeteryMan_9";
		break;
		
		case "CemeteryMan_9":
			dialog.text = "Bien, pensaremos en algo... No asustaremos más al guardia; tienes mi palabra.";
			link.l1 = "Maravilloso. ¡Buena suerte!";
			link.l1.go = "CemeteryMan_10";
		break;
		
		case "CemeteryMan_10":
			sld = characterFromId("CemeteryCouple_1");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("CemeteryCouple_2");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			pchar.questTemp.Lantern = "ToKeeper";
			DeleteAttribute(pchar,"questTemp.Lantern.nation");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("NoiseCemetery", "2");
			DialogExit();
		break;
		
		case "CemeteryGirl":
			dialog.text = "¿Qué?!";
			link.l1 = "Oh, nada...";
			link.l1.go = "CemeteryGirl_1";
		break;
		
		case "CemeteryGirl_1":
			DialogExit();
			sld = characterFromId("CemeteryCouple_1");
			sld.dialog.currentnode = "CemeteryMan_6";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		// <-- квест на получение фонаря 

		//замечание по обнажённому оружию от персонажей типа citizen // лесник вставил в ген.квесты чтобы не было пустого диалога .
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Escucha, soy ciudadano de la ciudad y te pediría que bajes tu espada.","Escucha, soy ciudadano de la ciudad y te pediría que bajes tu espada.");
			link.l1 = LinkRandPhrase("Bien.","Como desees...","Como dices...");
			link.l1.go = "exit";
		break;																																																				  
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;
	}
}

void ChurchGenQuest2_GiveCup()
{
	AddItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	rItem.Name = "itmname_ChurchGenQuest2Cup"; // rItem.Name = "itmname_bible";
	rItem.City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen");
	rItem.Weight = 15.0; // rItem.Weight = 2;
	rItem.picIndex = 13; // itm.picIndex = 6;
	rItem.picTexture = "ITEMS_31"; // itm.picTexture = "ITEMS_9";
	ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest2Cup");
}

// Для генера "Пираты на необитаемом острове"
String PiratesOnUninhabited_GetStringNum(int _num)
{
	String retValue = "";
	
	switch(_num)
	{
		case 5: retValue = "five"; break;
		case 6: retValue = "six"; break;
		case 7: retValue = "seven"; break;
		case 8: retValue = "eight"; break;
		case 9: retValue = "nine"; break;
		case 10: retValue = "ten"; break;
	}
	
	return retValue;
}

int PiratesOnUninhabited_GenerateShipType()
{
	int rank = sti(PChar.rank);
	int retShipType;
	
	if(rank < 5)
	{
		switch(hrand(1))
		{
			case 0: retShipType = SHIP_LUGGER; break;
			case 1: retShipType = SHIP_SLOOP; break;
		}
	}
	
	if(rank >= 5 && rank < 20)
	{
		switch(hrand(3))
		{
			case 0: retShipType = SHIP_SLOOP; break;
			case 1: retShipType = SHIP_BRIGANTINE; break;
			case 2: retShipType = SHIP_SCHOONER_W; break;
			case 3: retShipType = SHIP_BRIG; break;
		}
	}
	
	if(rank >= 20)
	{
		switch(hrand(2))
		{
			case 0: retShipType = SHIP_CORVETTE; break;
			case 1: retShipType = SHIP_GALEON_H; break;
			case 2: retShipType = SHIP_FRIGATE; break;
		}
	}
	
	return retShipType;
}

String PiratesOnUninhabited_GenerateTreasureShore(ref _boxId)
{
	String retShoreId;
	
	switch(hrand(4))
	{
		case 0:
			retShoreId = "Shore9";
			_boxId = "box1";
		break;
		
		case 1:
			retShoreId = "Shore55";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	
		case 2:
			retShoreId = "Shore_ship1";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 3:
			retShoreId = "Shore_ship2";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 4:
			retShoreId = "Shore_ship3";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	}
	
	return retShoreId;
}

void PiratesOnUninhabited_SetCapToMap()
{
	int temp;
	String group = "PiratesOnUninhabited_SeaGroup";
	ref character = GetCharacter(NPC_GenerateCharacter("PiratesOnUninhabited_BadPirate", "", "man", "man", sti(pchar.rank) + 5, PIRATE, -1, true, "soldier"));		
	character.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType), true, character);
	character.Ship.Name = PChar.GenQuest.PiratesOnUninhabited.StartShipName;
    SetBaseShipData(character);
    SetCrewQuantityFull(character);
    Fantom_SetCannons(character, "pirate");
    Fantom_SetBalls(character, "pirate");
	Fantom_SetUpgrade(character, "pirate");
	
	character.Ship.Mode = "pirate";	
	SetCaptanModelByEncType(character, "pirate");

	DeleteAttribute(character, "SinkTenPercent");
	DeleteAttribute(character, "SaveItemsForDead");
	DeleteAttribute(character, "DontClearDead");
	DeleteAttribute(character, "AboardToFinalDeck");
	DeleteAttribute(character, "SinkTenPercent");
	
	character.AlwaysSandbankManeuver = true;
	character.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	character.DontRansackCaptain = true; //не сдаваться
	
	SetAllPerksToChar(character, false);
	
	Group_FindOrCreateGroup(group);
	Group_SetTaskAttackInMap(group, PLAYER_GROUP);
	Group_LockTask(group);
	Group_AddCharacter(group, character.id);
	Group_SetGroupCommander(group, character.id);
	SetRandGeraldSail(character, PIRATE);
	
	character.fromCity = SelectAnyColony(""); // Колония, из бухты которой выйдет
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придёт
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
	
	character.mapEnc.type = "trade";
	character.mapEnc.worldMapShip = "quest_ship";
	character.mapEnc.Name = LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'";
	
	Map_CreateTrader(character.fromShore, character.toShore, "PiratesOnUninhabited_BadPirate", GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)) + 3);
	
	temp = GetCharacterFreeSpace(character, GOOD_SLAVES); // Сколько влезет рабов
	AddCharacterGoodsSimple(character, GOOD_SLAVES, makeint(temp / 2 + hrand(temp / 2)) - 1);
	
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1 = "Character_sink";
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1.character = "PiratesOnUninhabited_BadPirate";
	PChar.Quest.PiratesOnUninhabited_ShipSink.function = "PiratesOnUninhabited_ShipSink";
	
	Log_TestInfo("Pirates on an uninhabited island: cap left " + character.fromCity + " and went to: " + character.toShore);
}
// belamour gen количество каторжан прописью -->
String Convict_GetStringNum(int iCQTY)
{
	String ConvictStr = "";
	
	switch(iCQTY)
	{
		case 2: ConvictStr = "two"; break;
		case 3: ConvictStr = "three"; break;
		case 4: ConvictStr = "four"; break;
		case 5: ConvictStr = "five"; break;
		case 6: ConvictStr = "six"; break;
		case 7: ConvictStr = "seven"; break;
	}
	
	return ConvictStr;
}
// <-- gen
