void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "¿Qué desea?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		case "dwh_gypsy_0":
			dialog.text = "...";
			link.l1 = "Escucha, cejinegra, escuché que curas a las personas, incluso de enfermedades graves. ¿Es cierto?";
			link.l1.go = "dwh_gypsy_1";
			DelLandQuestMark(npchar);
		break;
		
		case "dwh_gypsy_1":
			dialog.text = "Verdad, "+GetSexPhrase("cariño","hermosa")+". Para cada dolencia tengo mi propio enfoque. He puesto en pie a plebeyos, ricos y mercaderes. Incluso el gobernador ha recurrido a mis pociones cuando nadie más podía ayudar. Las enfermedades no temen al oro, pero no pueden resistir mis brebajes.";
			link.l1 = "Entonces, ¿por qué te niegas a curar a la niña gravemente enferma, la hija de Thomas Morrison?";
			link.l1.go = "dwh_gypsy_2";
			pchar.questTemp.DWH_gipsy = true;
		break;

		case "dwh_gypsy_2":
			dialog.text = "¿Quién te contó semejante tontería, "+GetSexPhrase("halconcito","palomita")+"? No me opongo a ayudar, pero su padre mismo me echó de la casa. Ya habíamos acordado que me encargaría del tratamiento, pero de repente cambió. Me echó por la puerta como si fuera un enemigo mortal.";
			link.l1 = "¿Es así? Entonces, ¿él mismo condenó a su hija al sufrimiento?";
			link.l1.go = "dwh_gypsy_2_1";
		break;

		case "dwh_gypsy_2_1":
			dialog.text = "¿Qué dices? Es un padre atento, cuesta imaginar por qué habría actuado así.";
			link.l1 = "¿Has intentado hablar con él de nuevo?";
			link.l1.go = "dwh_gypsy_3";
		break;

		case "dwh_gypsy_3":
			dialog.text = "No me deja acercarme a la casa. Escucha, "+GetSexPhrase("cariño","hermosa")+", si te importa el destino de una pobre chica, ¿quizás podrías intentar averiguar qué pasa? Habla con Thomas, ayúdame a salvar a la niña del sufrimiento.";
			link.l1 = "Por supuesto, ayudaré. ¿Dónde puedo encontrar a Thomas?";
			link.l1.go = "dwh_gypsy_4";
			link.l2 = "No, cejas negras. Sea como sea, creo que su padre tiene buenas razones para rechazar tu ayuda. No voy a involucrarme en esto. Que él decida por sí mismo, después de todo es su hija.";
			link.l2.go = "dwh_gypsy_otkaz";
		break;

		case "dwh_gypsy_otkaz":
			DialogExit();
			CloseQuestHeader("DWH");
		break;

		case "dwh_gypsy_4":
			dialog.text = "Su casa está junto al muro, en la parte norte de la ciudad, al lado de una lujosa mansión con columnas. Ve, "+GetSexPhrase("halconcito","palomita")+", habla con él y vuelve conmigo.";
			link.l1 = "Volveré pronto.";
			link.l1.go = "dwh_gypsy_5";
		break;

		case "dwh_gypsy_5":
			DialogExit();
			
			AddQuestRecord("DWH", "2");
			
			sld = CharacterFromID("DWH_gypsy");
			sld.dialog.currentnode = "dwh_gypsy_repeat";
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_Tomas", "citiz_13", "man", "man", 1, ENGLAND, -1, false, "quest"));
			sld.name = "Thomas";
			sld.lastname = "Morrison";
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas";
			ChangeCharacterAddressGroup(sld, "SentJons_houseS3", "goto", "goto1");
			sld.City = "SentJons";
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "dwh_gypsy_repeat":
			dialog.text = "Bueno, "+GetSexPhrase("cariño","cariña")+", ¿has hablado con Thomas?";
			link.l1 = "Todavía no.";
			link.l1.go = "dwh_exit";
		break;
		
		case "dwh_exit":
			DialogExit();
			NextDiag.TempNode = "dwh_gypsy_repeat";
		break;

		case "Tomas":
			dialog.text = "¡"+TimeGreeting()+"! ¿Qué le trae a mi casa?";
			link.l1 = "Soy el capitán "+GetFullName(pchar)+". Vengo por petición de la gitana. Ella no entiende por qué rechazó su ayuda y quiere saber la razón. ¿Está usted en posición de rechazar cualquier oportunidad, por pequeña que sea, de ayudar a su hija?";
			link.l1.go = "Tomas_1";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_1":
			dialog.text = "Oh, capitán... Comprenda, tuve que rechazarla, pero no fue por mi propia voluntad. Créame, daría todo por la recuperación de Esther.";
			link.l1 = "¿Qué podría haberle obligado a rechazar la ayuda que tanto necesita?";
			link.l1.go = "Tomas_2";
		break;

		case "Tomas_2":
			dialog.text = "Verá, nuestra familia siempre ha sido devota. Después de la muerte de mi esposa, Olivia, solo me sostengo gracias a la fe. Cuando la gitana ofreció su ayuda, acepté... con tal de salvar a mi hija. Pero... nuestro pastor se enteró.";
			link.l1 = "Déjeme adivinar: ¿está en contra de ese tipo de ayuda?";
			link.l1.go = "Tomas_3";
		break;

		case "Tomas_3":
			dialog.text = "Exactamente. Me convenció de que solo la oración y la voluntad del Señor pueden curar a mi hija. Y si me desvío de ese camino y recurro a la 'bruja', me amenazó con la excomunión. ¿Lo entiende? ¡Excomunión!";
			link.l1 = "¿Entonces la salud de Esther depende únicamente de la palabra del pastor?";
			link.l1.go = "Tomas_4";
		break;

		case "Tomas_4":
			dialog.text = "Vivimos para la iglesia. Es nuestro todo. Si la gitana fracasa, perderé no solo a mi hija, sino también mi lugar en este mundo. La gente se alejará, la iglesia me rechazará. Esther y yo quedaremos completamente solos.";
			link.l1 = "¿Y si el pastor diera su bendición? ¿Entonces permitiría que la gitana intentara curarla?";
			link.l1.go = "Tomas_5";
		break;

		case "Tomas_5":
			dialog.text = "Sí. Si la iglesia bendijera sus actos... entonces confiaría en ella. Estoy dispuesto a probar todo lo que pueda ayudar.";
			link.l1 = "Entiendo. Bien, Thomas, le ayudaré. Hablaré con su pastor. Tal vez pueda convencerlo.";
			link.l1.go = "Tomas_6";
		break;

		case "Tomas_6":
			dialog.text = "¿Está... está realmente dispuesto a ayudarnos? Capitán, rezaré por su éxito. Pero sepa esto... nuestro pastor es un hombre terco y de principios, convencerlo no será fácil.";
			link.l1 = "Los principios se vencen con buenos argumentos. Espere, volveré pronto.";
			link.l1.go = "Tomas_7";
		break;
		
		case "Tomas_7":
			DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("DWH", "3");
			pchar.questTemp.DWH_pastor = true;
			AddLandQuestMark(characterFromId("SentJons_Priest"), "questmarkmain");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterDisableDialog(sld);
		break;
		
		case "Tomas_11":
			dialog.text = "...";
			link.l1 = "Thomas, he logrado convencer al sacerdote.";
			link.l1.go = "Tomas_12";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_12":
			dialog.text = "¿De verdad? ¡Increíble! Entonces invitemos a la gitana de inmediato.";
			link.l1 = "Ciertamente lo haremos, pero hay un detalle. El sacerdote espera que todo esto no haga tambalear tu fe, y espera de ti un arrepentimiento sincero y buenas obras. La primera de estas podría ser la compra de una nueva campana para la parroquia.";
			link.l1.go = "Tomas_13";
		break;

		case "Tomas_13":
			dialog.text = "Oh, Capitán... Una campana cuesta bastante dinero. Es posible que tenga que desprenderme de algunas joyas de mi difunta esposa. Pero por Esther, estoy dispuesto a dar todo lo que tengo, e incluso más. Y por supuesto, rogaré al Señor por su perdón. Iré al herrero, haré el pedido y buscaré a la gitana\nY le pido que le diga al sacerdote que la campana estará lista pronto. La conseguiré incluso si tengo que sacarla de debajo de la tierra si es necesario.";
			link.l1 = "Muy bien, Thomas.";
			link.l1.go = "Tomas_14";
		break;
		
		case "Tomas_14":
			DialogExit();
			
			LAi_SetActorType(npchar);
			pchar.questTemp.DWH_pastor_PrinesDengi = true;
			AddLandQuestMark(characterFromId("SentJons_Priest"), "questmarkmain");
		break;
		
		case "Tomas_15":
			dialog.text = "...";
			link.l1 = "Le transmití sus palabras al sacerdote. Ya no pondrá más obstáculos, así que puede comenzar.";
			link.l1.go = "Tomas_16";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_16":
			dialog.text = "¡Gracias, "+GetSexPhrase("señor","señorita")+" capitán"+GetSexPhrase("","a")+", por su ayuda! Tome estos cincuenta doblones, es lo mínimo que puedo hacer por usted, pero es todo lo que tengo por el momento...";
			link.l1 = "¡Por favor! No le ayudé por dinero. Ahora todo está listo para proceder con... ejem... ¿el tratamiento?";
			link.l1.go = "Tomas_16_1";
			link.l2 = "Bueno, si insiste... ¿Puedo ayudar con algo más?";
			link.l2.go = "Tomas_16_2";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "Tomas_16_1":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.questTemp.DWH_GoodChoice = true;
		break;
		
		case "Tomas_16_2":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			AddItems(pchar, "gold_dublon", 50);
		break;
		
		case "gypsy_1":
			dialog.text = "Para preparar el brebaje que devolverá la salud a la niña, necesito mangarosa, una planta rara que crece donde rara vez pisan los humanos. Conozco una cueva detrás de la ciudad donde suelen merodear... indeseables. La usan para fumar sin saber su verdadero poder. Ayúdame, "+GetSexPhrase("halconcito","palomita")+", consígueme mangarosa, sin ella nada funcionará.";
			if (CheckAttribute(pchar, "questTemp.Mangarosa"))
			{
				link.l1 = "¿Mangarosa? Conozco esa planta.";
				link.l1.go = "gypsy_VD_manga_1";
			}
			else
			{
				link.l1 = "¿Cómo luce esa planta?";
				link.l1.go = "gypsy_VD_no_manga";
			}
		break;

		case "gypsy_VD_no_manga":
			dialog.text = "Es una planta bastante alta con hojas divididas y un aroma agradable y embriagador. No la confundirás con otra.";
			link.l1 = "Bien, encontraré esa mangarosa.";
			link.l1.go = "gypsy_2";
		break;

		case "gypsy_VD_manga_1":
			dialog.text = "¿También la mezclas con tabaco?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "¡No, para nada! Conozco a una curandera, Amelia. Ella prepara brebajes con esa planta que, sin exagerar, pueden cambiar la percepción de la realidad.";
				link.l1.go = "gypsy_VD_manga_1_2";
			}
			else
			{
				link.l1 = "No, pero he tenido mangarosa en mis manos un par de veces.";
				link.l1.go = "gypsy_VD_manga_2";
			}
		break;

		case "gypsy_VD_manga_1_2":
			dialog.text = "¿Así que conoces a Amelia? Bueno, "+GetSexPhrase("halconcito","palomita")+", pronto vas a hacerme la competencia. Pero no es momento de hablar de eso. Ve por la mangarosa, yo me encargo del resto.";
			link.l1 = "En camino.";
			link.l1.go = "gypsy_2";
			AddCharacterExpToSkill(pchar, "Fortune", 200);
		break;

		case "gypsy_VD_manga_2":
			dialog.text = "Veo que no eres cualquiera, "+GetSexPhrase("halconcito","palomita")+". Tienes gran conocimiento y una mente afilada como una navaja. No temes lo desconocido y buscas comprender lo que otros no pueden. Thomas tiene suerte de contar contigo. Ahora ve, tráeme la mangarosa y curaré a la niña.";
			link.l1 = "...";
			link.l1.go = "gypsy_2";
		break;
		
		case "gypsy_2":
			DialogExit();
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			
			AddQuestRecord("DWH", "5");
			
			// поход за мангаросой
			LAi_LocationDisableOfficersGen("Antigua_Grot", true);
			locations[FindLocation("Antigua_Grot")].DisableEncounters = true;
			PChar.quest.DWH_Grot.win_condition.l1 = "location";
			PChar.quest.DWH_Grot.win_condition.l1.location = "Antigua_Grot";
			PChar.quest.DWH_Grot.function = "DWH_Grot";
		break;
		
		case "Bandit_1":
			dialog.text = "Ja, ja. Te digo, Mark, es un ingenuo. Ni siquiera cierra la puerta de su casa.";
			link.l1 = "¿Y estás seguro de que su gallinita no va a estar en casa?";
			link.l1.go = "Bandit_2";
			
			locCameraSleep(true);
			sld = CharacterFromID("DWH_Bandit_1");
			CharacterTurnToLoc(sld, "goto", "ass4");
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "ass2");
		break;
		
		case "Bandit_2":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "", -1);
			DoQuestFunctionDelay("DWH_Grot_2", 4.0);
		break;
		
		case "Bandit_3":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "¡Mira lo que tenemos aquí, carne fresca! Vamos, vamos, no te quedes ahí parado. Vacía los bolsillos, y rápido, mientras aún estamos de buen humor.";
			link.l1 = "Tranquilos, bandidillos. Vengo por negocios, me envió "+sld.name+". Necesito mangarosa.";
			link.l1.go = "Bandit_4";
			
			locCameraSleep(false);
			locCameraFromToPos(3.39, 1.16, -1.80, true, 3.62, -0.50, 3.63);
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "goto2");
		break;
		
		case "Bandit_4":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "¿Dices que "+sld.name+" te envió? Está bien, tenemos mangarosa. Dame diez doblones de oro y es tuya.";
			if (PCharDublonsTotal() >= 10)
			{
				link.l1 = "Toma.";
				link.l1.go = "Bandit_5";
			}
			link.l2 = "¿Dinero? ¿Para qué necesitan dinero ustedes? No ando repartiendo limosnas. ¡Pero un par de pulgadas de acero bajo las costillas, eso sí puedo dar!";
			link.l2.go = "Bandit_7";
		break;
		
		case "Bandit_5":
			dialog.text = "Está bien, aquí tienes tu mangarosa. Y recuerda, no nos viste.";
			link.l1 = "Je. No hacía falta que lo dijeras.";
			link.l1.go = "Bandit_6";
			GiveItem2Character(PChar, "cannabis7");
			RemoveDublonsFromPCharTotal(10);
		break;

		
		case "Bandit_6":
			DialogExit();
			
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			LAi_LocationDisableOfficersGen("Antigua_Grot", false);
			locations[FindLocation("Antigua_Grot")].DisableEncounters = false;
			
			/*if (CheckAttribute(pchar, "questTemp.DWH_GoodChoice"))*/ SetFunctionLocatorCondition("DWH_VorovstvoSunduk", "Antigua_Grot", "box", "box1", false)
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_3";
			AddLandQuestMark(sld, "questmarkmain");
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("DWH_Bandit_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DWH_Podkreplenie");
			}
		break;
		
		case "Bandit_7":
			DialogExit();
			
			chrDisableReloadToLocation = true;
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			GiveItem2Character(NPChar, "cannabis7");
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("DWH_Bandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=3; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DWH_Bandit_"+i, "citiz_48", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
				if (i==4) sld.model = "citiz_49";
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "Antigua_Grot", "reload", "reload1");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "DWH_Grot_4");
		break;
		
				case "gypsy_3":
			if (CheckCharacterItem(PChar, "cannabis7"))
			{
				dialog.text = "...";
				link.l1 = "Mira, "+npchar.name+", ¿es esta la planta que necesitas?";
				link.l1.go = "gypsy_4";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "¿Trajiste lo que te pedí?";
				link.l1 = "Aún no, estoy trabajando en ello.";
				link.l1.go = "exit";
				NextDiag.TempNode = "gypsy_3";
			}
		break;
		
		case "gypsy_4":
			dialog.text = "Sí, es esa. Ahora tengo todo lo necesario y puedo comenzar.";
			link.l1 = "...";
			link.l1.go = "gypsy_5";
			TakeItemFromCharacter(pchar, "cannabis7");
		break;
		
		case "gypsy_5":
			StartInstantDialog("DWH_Tomas", "Tomas_17", "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c");
		break;
		
		case "Tomas_17":
			dialog.text = "Vamos rápido, no perdamos tiempo.";
			link.l1 = "...";
			link.l1.go = "Tomas_18";
			CharacterTurnByChr(npchar, CharacterFromID("DWH_gypsy"));
		break;
		
		case "Tomas_18":
			dialog.text = "Capitán, si no le importa, nos vemos luego. Ahora nos espera la parte más importante... del tratamiento.";
			link.l1 = "Por supuesto, Thomas. Espero que su hija se recupere pronto.";
			link.l1.go = "Tomas_19";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tomas_19":
			DialogExit();
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "gypsy_6":	// если не прошли проверку ВД у священника
			dialog.text = "...";
			link.l1 = ""+npchar.name+", Thomas no te echó por voluntad propia. El sacerdote le amenazó con la excomunión si aceptaba tu ayuda.";
			link.l1.go = "gypsy_7";
			DelLandQuestMark(npchar);
		break;
		
		case "gypsy_7":
			dialog.text = "Supe desde el principio, "+GetSexPhrase("cariño","hermosa")+", que me negó eso con el corazón pesado.";
			link.l1 = "¿Hay alguna manera de ayudarlo sin que la iglesia lo tome como un desafío?";
			link.l1.go = "gypsy_8";
		break;
		
		case "gypsy_8":
			dialog.text = "Ay, "+GetSexPhrase("cariño","hermosa")+", no es asunto fácil, pero los caminos los conozco, sé qué hacer. Solo que sin tu ayuda no podré, ya lo sabes.";
			link.l1 = "Por supuesto, puedes contar conmigo.";
			link.l1.go = "gypsy_10";
			link.l2 = "Lo siento, cejinegra, pero no tengo absolutamente ningún tiempo para ocuparme de esto. He hecho todo lo que estaba en mi poder. Ahora debo atender mis propios asuntos.";
			link.l2.go = "gypsy_9";
		break;
		
		case "gypsy_9":
			DialogExit();
			CloseQuestHeader("DWH");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			
			sld = CharacterFromID("DWH_Tomas");
			sld.lifeday = 0;
		break;
		
		case "gypsy_10":
			dialog.text = "Entonces esto es lo que necesito: un objeto que pertenezca a la niña, dos tallos de datura, uno de ipecacuana y uno de verbena. Si me traes todo esto, podré preparar una poción curativa para ella.";
			link.l1 = "Bien, conseguiré todo lo necesario.";
			link.l1.go = "gypsy_11";
		break;

		case "gypsy_11":
			DialogExit();
			AddQuestRecord("DWH", "7");
			
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "Tomas_21":
			dialog.text = "...";
			link.l1 = "Thomas, desafortunadamente, el sacerdote no atendió mis argumentos. Pero la gitana y yo podemos ayudarle. Necesito...";
			link.l1.go = "Tomas_22";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_22":
			dialog.text = "¿Me está sugiriendo que vaya contra la iglesia?";
			link.l1 = "Lo haremos todo en silencio, nadie se enterará. Muy pronto su hija podrá disfrutar de la vida nuevamente y caminar libremente por la ciudad, como corresponde a una joven dama.";
			link.l1.go = "Tomas_23";
			link.l2 = "¡Maldita sea, Thomas Morrison! ¿Quiere usted que su hija se recupere o solo se esconde detrás de palabras bonitas?";
			link.l2.go = "Tomas_24";
		break;

		case "Tomas_23":
			dialog.text = "Está bien, acepto. Pero por favor, actúe con cuidado. No quiero rumores innecesarios ni problemas.";
			link.l1 = "Por supuesto. Entonces, necesito un objeto personal de su hija, algo a lo que esté apegada.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Sneak", 200);
		break;

		case "Tomas_24":
			dialog.text = "Está bien, acepto. Pero por favor, actúe con cuidado. No quiero rumores innecesarios ni problemas.";
			link.l1 = "Por supuesto. Entonces, necesito un objeto personal de su hija, algo a lo que esté apegada.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Tomas_25":
			dialog.text = "Hmm... ¡Sí! Sé lo que servirá. Espere aquí, vuelvo enseguida.";
			link.l1 = "Estoy esperando...";
			link.l1.go = "Tomas_26";
		break;

		case "Tomas_26":
			DialogExit();
			SetLaunchFrameFormParam("Pasaron unos minutos...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("DWH_TomasGovotitAgain", 0.0);
			LaunchFrameForm();
		break;

		case "Tomas_27":
			dialog.text = "Aquí. Estas son cuentas de jade. Esther nunca se las quitaba, son muy preciadas para ella.";
			link.l1 = "Excelente. Ahora, todo lo que tiene que hacer es esperar. Nos vemos pronto, Thomas.";
			link.l1.go = "Tomas_28";
			GiveItem2Character(PChar, "jewelry49");
		break;
		
		case "Tomas_28":
			DialogExit();
			AddQuestRecord("DWH", "8");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "gypsy_21":
			dialog.text = "¿Has traído lo que te pedí?";
			if (GetCharacterItem(pchar, "cannabis1") >= 2 && GetCharacterItem(pchar, "cannabis4") >= 1 && GetCharacterItem(pchar, "cannabis3") >= 1)
			{
				link.l1 = "He reunido todo lo necesario.";
				link.l1.go = "gypsy_22";
			}
			link.l2 = "Recuérdame qué tengo que traer.";
			link.l2.go = "gypsy_napomni";
		break;

		case "gypsy_napomni":
			dialog.text = "Esto es lo que necesito: un objeto que pertenezca a la niña, dos tallos de datura, uno de ipecacuana y uno de verbena. Si me traes todo esto, podré preparar una poción curativa para ella.";
			link.l1 = "Bien, conseguiré todo lo necesario.";
			link.l1.go = "gypsy_napomni_2";
		break;

		case "gypsy_napomni_2":
			DialogExit();
			NextDiag.TempNode = "gypsy_21";
		break;

		case "gypsy_22":
			dialog.text = "Excelente. Ahora puedo preparar una poción curativa para la niña. Estará lista no antes de mañana por la mañana. Puedes encontrarme como siempre, en las calles de la ciudad.";
			link.l1 = "Muy bien, hasta entonces.";
			link.l1.go = "gypsy_23";
			DelLandQuestMark(npchar);
			RemoveItems(pchar, "cannabis1", 2);
			RemoveItems(pchar, "cannabis4", 1);
			RemoveItems(pchar, "cannabis3", 1);
			RemoveItems(pchar, "jewelry49", 1);
		break;
		
		case "gypsy_23":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("DWH", "11");
			SetTimerFunction("DWH_GypsyPrigotovilaZelie", 0, 0, 1);
		break;
		
		case "gypsy_31":
			dialog.text = "...";
			link.l1 = "Bueno, "+npchar.name+", ¿tu poción está lista?";
			link.l1.go = "gypsy_32";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_32":
			dialog.text = "Ahí está, "+GetSexPhrase("cariño","hermosa")+". Que la niña se ponga estos collares y beba el contenido del frasco hasta el fondo. En no más de un mes estará completamente sana.";
			link.l1 = "Se lo llevaré a Thomas de inmediato. Cuídate, cejinegra.";
			link.l1.go = "gypsy_33";
			GiveItem2Character(PChar, "quest_potion");
			GiveItem2Character(PChar, "jewelry49");
		break;

		case "gypsy_33":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);

			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "Tomas_31":
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				dialog.text = "...";
				link.l1 = "Thomas, todo está listo. Esther debe ponerse estos collares y beber la poción de una sola vez.";
				link.l1.go = "Tomas_32";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Tomas_31";
			}
		break;

		case "Tomas_32":
			dialog.text = "¡Gracias, "+pchar.name+"! Perdóneme, no quiero perder ni un minuto...";
			link.l1 = "Por supuesto, por supuesto.";
			link.l1.go = "Tomas_33";
			TakeItemFromCharacter(pchar, "quest_potion");
		break;
		
		case "Tomas_33":
			DialogExit();
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "Tomas_41":
			dialog.text = "¡Hola, "+pchar.name+"! ¡Mi Esther se ha recuperado! Está completamente sana y ahora está en la iglesia, orando a nuestro Señor Dios y agradeciéndole por habernos enviado a usted y a la gitana.";
			link.l1 = "Thomas, me alegra que todo haya salido bien. Cuide de la niña, ahora tiene por delante una larga y feliz vida.";
			link.l1.go = "Tomas_42";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_42":
			dialog.text = "Tome estos trescientos doblones. Lamentablemente, no puedo ofrecer más, ya que tuve que endeudarme para reunir esta suma. Pero sepa que ninguna palabra ni oro pueden expresar la gratitud que siento por usted, capitán"+GetSexPhrase("","a")+". No solo me liberó del temor por su vida, sino que también le dio a nuestra familia una esperanza para el futuro. ¡Siempre estaré agradecido!";
			link.l1 = "¡Gracias! Trescientos doblones es una recompensa bastante generosa, así que no se preocupe: ¡me ha agradecido más que suficiente!";
			link.l1.go = "Tomas_43";
			link.l2 = "No aceptaré su dinero, Thomas. ¡Ni se le ocurra insistir! No ayudé por interés. Mejor cómprele un bonito vestido a la joven Esther, se lo merece.";
			link.l2.go = "Tomas_46";
		break;

		case "Tomas_43":
			dialog.text = ""+pchar.name+", visítenos cuando quiera. Siempre será bienvenid"+GetSexPhrase("o","a")+" en nuestra casa. Y además, hable con la gitana, ella quería verle.";
			link.l1 = "¡Será un honor! Pero ahora, con su permiso, Thomas. Tengo asuntos que atender.";
			link.l1.go = "Tomas_44";
			AddItems(pchar, "gold_dublon", 300);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;

		case "Tomas_44":
			dialog.text = "Por supuesto. ¡Que Dios le acompañe, "+GetFullName(pchar)+"!";
			link.l1 = "Adiós.";
			link.l1.go = "Tomas_45";
		break;
		
		case "Tomas_45":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_41";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_46":
			dialog.text = "¡Es usted una persona nobilísima, "+GetFullName(pchar)+"! ¡Que la Virgen María le acompañe! Visítenos, siempre será un"+GetSexPhrase("","a")+" invitad"+GetSexPhrase("o","a")+" bienvenid"+GetSexPhrase("o","a")+" en nuestra casa. Y además, "+pchar.name+", hable con la gitana, ella quería verle.";
			link.l1 = "¡Sin duda! Pero ahora, con su permiso. Asuntos me esperan.";
			link.l1.go = "Tomas_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;

		case "Tomas_47":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_44";
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.DWH_QuestCompleted = true;
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1;
			
			AddSimpleRumourCity("¿Ha oído? "+GetFullName(pchar)+" consiguió un remedio para la hija de Thomas Morrison que milagrosamente restauró la salud de la pobre niña!", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Thomas Morrison enciende una vela en la parroquia diariamente por la salud de "+GetFullName(pchar)+". Dicen que gracias a sus esfuerzos, su hija se liberó de una enfermedad prolongada.", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Esther Morrison ha florecido ante nuestros ojos. Como si nunca hubiera estado enferma. Nadie puede explicar realmente qué hizo que la enfermedad retrocediera.", "SentJons", 10, 1, "");
		break;

		case "gypsy_41":
			dialog.text = "¡Ahí estás, "+GetSexPhrase("halconcito","palomita")+"! Sabía que volverías. Gracias a tus esfuerzos, la niña se ha recuperado y ahora revolotea como una paloma. Toda la ciudad la admira.";
			link.l1 = "Vamos, cejinegra, no fue solo por mis esfuerzos. Fue tu brebaje lo que la curó, así que no escondas tu mérito.";
			link.l1.go = "gypsy_42";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_42":
			dialog.text = "Tienes un buen corazón, "+GetSexPhrase("halconcito","palomita")+", ¡y una mente aguda! ¡Estás destinad"+GetSexPhrase("o","a")+" a la grandeza, esa es mi profecía!";
			link.l1 = "Heh... bueno, gracias, "+npchar.name+".";
			link.l1.go = "gypsy_43";
		break;
		
		case "gypsy_43": // плохой вариант
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "9");
			CloseQuestHeader("DWH");
		break;
		
		case "gypsy_44":
			dialog.text = "¡Ahí estás, "+GetSexPhrase("halconcito","palomita")+"! Sabía que aparecerías aquí de nuevo. Gracias a tus esfuerzos, la niña se ha recuperado y ahora revolotea como una paloma. Toda la ciudad la admira.";
			link.l1 = "Vamos, cejinegra, tú misma salvaste a la niña, ¿y quieres que yo recoja todos los laureles? ¡Así no va! Tú preparaste el brebaje, tú la pusiste de pie, tú debes recibir la gloria.";
			link.l1.go = "gypsy_45";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_45":
			dialog.text = "Tienes un buen corazón, "+GetSexPhrase("halconcito","palomita")+", y un alma noble. Tengo un regalo para ti, uno que cualquier capitán apreciaría. Toma. ¡Ahora las ratas en tu barco no tendrán ni paz ni dicha!";
			link.l1 = "¿Un regalo? ¡Qué inesperado!";
			link.l1.go = "gypsy_46";
			GiveItem2Character(PChar, "rat_poison");
		break;

		case "gypsy_46":
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				dialog.text = "Tu alma es pura, veo que no quemarás mangarosa por un placer momentáneo. Si la necesitas con urgencia, ven a mí, "+GetSexPhrase("halconcito","palomita")+". Tres tallos te costarán trescientos cincuenta doblones\nEsta hierba es caprichosa, ya sabes, no cualquiera puede encontrarla. Así que no me apresures: no la pidas más de una vez al mes, no la conseguiré antes de eso.";
			}
			else
			{
				dialog.text = "Tu alma es brillante, veo que no eres ningún ignorante, sabes de hierbas como las mejores curanderas. Puedes encontrar muchas cosas, aunque la suerte no siempre esté de tu lado. Se llama mangarosa. Si la necesitas, ven a mí, "+GetSexPhrase("halconcito","palomita")+". Te conseguiré tres tallos, pero no serán gratis: te costarán trescientos cincuenta doblones\nPero esta hierba es caprichosa, así que no me apresures. No la pidas más de una vez al mes - aunque eches todas las cartas del destino, no la conseguiré antes.";
			}
			link.l1 = "Bueno, gracias, "+npchar.name+".";
			link.l1.go = "gypsy_47";
		break;
		
		case "gypsy_47": // хороший вариант
			DialogExit();
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "10");
			CloseQuestHeader("DWH");
			AddQuestRecordInfo("Useful_Acquaintances", "1");
			
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
		
		case "Tomas_51":
			dialog.text = "Capitán, no dejo de pensar – ¡no puede ser otra cosa que el mismo Señor quien le haya guiado hasta aquí en el momento justo! Usted salvó a mi hija, y nunca lo olvidaré.";
			link.l1 = "Quizás, Thomas. Los caminos del Señor son inescrutables.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tomas_52";
			SetTimerFunction("DWH_Tomas_HelloAgain", 0, 0, 1);
		break;

		case "Tomas_52":
			dialog.text = "¿Le apetece un poco de vino, capitán? Tengo algo especial para los invitados distinguidos.";
			link.l1 = "Gracias, Thomas, pero por desgracia, debo marcharme.";
			link.l1.go = "exit";
		break;

		case "gypsy_Mangarosa":
			dialog.text = "¿Qué necesitas, mi halcón?";
			if (CheckAttribute(pchar, "questTemp.DWH_Mangarosa"))
			{
				link.l1 = "Dime, cejinegra, ¿tienes mangarosa para mí?";
				link.l1.go = "gypsy_Mangarosa_1";
			}
			link.l2 = "Solo vine a saludar. ¡Debo irme!";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;
		
		case "gypsy_Mangarosa_1":
			dialog.text = "¿¿Quién, si no yo, "+GetSexPhrase("cariño","hermosa")+", te conseguiría una rareza así? Trescientos cincuenta doblones – y será tuya, tres tallos, ni más, ni menos.";
			if (PCharDublonsTotal() >= 350)
			{
				link.l1 = "Tu precio es justo. El oro es tuyo.";
				link.l1.go = "gypsy_Mangarosa_2";
			}
			link.l2 = "¡Maldición! No tengo suficiente oro. Volveré más tarde.";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;

		case "gypsy_Mangarosa_2":
			dialog.text = " Así está mejor, "+GetSexPhrase("halconcito","palomita")+". Toma. Y no la desperdicies en vano, ya sabes – la mangarosa no es una hierba cualquiera, guarda un poder que no cualquiera puede manejar.";
			link.l1 = "No te preocupes, cejinegra, sabré darle un uso digno.";
			link.l1.go = "gypsy_Mangarosa_3";
			AddItems(pchar, "cannabis7", 3);
			RemoveDublonsFromPCharTotal(350);
		break;
		
		case "gypsy_Mangarosa_3":
			DialogExit();
			
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			DeleteAttribute(pchar, "questTemp.DWH_Mangarosa");
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
	}
}