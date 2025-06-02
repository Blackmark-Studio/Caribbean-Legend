// BOAL новый диалог офицера и компаньона 21/06/06
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
	ref    	sld, rItm, rItem;
	string 	attr, attrLoc, sGun, sBullet, attrL, sAttr;
	int    	iTemp, iTax, iFortValue, i;
	aref 	rType;
	
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
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Je, capitán, la mitad de la guarnición está tras de ti en este momento. Seguramente no es el mejor momento para ser contratado en tu tripulación!","¿Y luchando para abrirnos camino hasta el barco? No, capi, en otro momento...");
				link.l1 = RandPhraseSimple("Como desees...","De hecho, no iba a contratarte."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "¿Necesita un oficial, capitán?";
			if (FindFreeRandomOfficer() > 0)
			{
    			Link.l1 = "¿Un oficial? ¿Y en qué eres bueno?";
    			Link.l1.go = "Node_2";
			}
			Link.l2 = "No, tengo el juego completo.";
			Link.l2.go = "Exit";			
		break;
		
		case "CitizenNotBlade":
			dialog.text = "¡Capitán, ¿qué estás haciendo? Guarda tu arma, antes de que causes muchos problemas!";
			link.l1 = LinkRandPhrase("Bien.","Bien.","No te preocupes, lo estoy guardando...");
			link.l1.go = "exit";
		break;
		
		case "hired":
			Diag.TempNode = "Hired";
			// только наняли -->
			if (IsCompanion(NPChar))
			{
				Dialog.text = "¡Hoy, finalmente zarpamos!";
				link.l2 = "Sí ... Estoy contento.";
				link.l2.go = "Exit";
				break;
			}
			if (Npchar.location.group == "sit" && !isShipInside(pchar.location))
			{
				dialog.text = "Solo terminaré mi bebida, capitán, y luego iré al barco. No te preocupes, estaré allí a tiempo.";
				Link.l1 = "Está bien. Si llegas tarde, ¡te haré fregar la cubierta!";
				Link.l1.go = "Exit";
				break;
			}
			// только наняли <--
   			dialog.text = "¿Qué quieres, capitán?";
			// диалог компаньона на корабле.
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				Link.l2 = "Necesito darte varias órdenes.";
				Link.l2.go = "Companion_Tasks";
				break;
			}
			
			// на Тайясаль
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l66 = ""+npchar.name+", voy a una antigua ciudad india de Tayasal. Será un viaje peligroso e inusual, a través de un ídolo de teleportación. ¿Te unirás a mí?";
				if(npchar.id == "Folke")
				{
					Link.l66 = ""+npchar.name+", tengo una petición seria para ti. Es sobre un verdadero negocio, suicida pero malditamente rentable. Necesito un hombre leal en una misión a una antigua ciudad india. ¿Estás conmigo?";
				}
				if(npchar.id == "Duran")
				{
					Link.l66 = "Claude, una vez te quejaste de que los mercenarios están mal pagados.";
				}
				Link.l66.go = "tieyasal";
			}
			
			if (isOfficer(Npchar)) // проверка для кампуса, где слотовые офы
			{
				Link.l2 = "¡Ahora escucha mi orden!";
				Link.l2.go = "stay_follow";
			}

           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l8 = "Dame un informe completo del barco, "+GetStrSmallRegister(XI_ConvertString("tesorero"))+".";
			    Link.l8.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
			    if(!CheckAttribute(PChar, "TransferGoods.Enable"))
			    {
				    Link.l11 = "Quiero que compres mercancías mientras nos quedamos en la colonia.";
				    Link.l11.go = "TransferGoodsEnable";
			    }
			    else
			    {
				    Link.l11 = "Sabes, ya no necesitamos comprar bienes en las colonias.";
				    Link.l11.go = "TransferGoodsDisable";
			    }
			}
			
			if (pchar.location != "My_Campus") // patch-5
			{
			Link.l4 = "Oficial, tus servicios ya no son necesarios.";
			Link.l4.go = "AsYouWish";
			}
			
			
			// по тек локации определим можно ли тут приказать  -->
			if(IsEntity(&loadedLocation))
			{
				if(CheckAttribute(loadedLocation, "fastreload"))
				{
					iTemp = FindColony(loadedLocation.fastreload);
					if(iTemp != -1)
					{
						sld = GetColonyByIndex(iTemp);
						if(sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx"))
						{
							NPChar.ColonyIdx = iTemp;
							Link.l7 = "¡Te nombro ayudante de esta ciudad!";
							Link.l7.go = "Gover_Hire";
						}
					}
				}
			}
			
			Link.l9 = "¡Nada. ¡A sus anchas!";
			Link.l9.go = "Exit";
		break;
		
		// Тайясаль
		case "tieyasal":
			if(npchar.id == "Folke")
			{
				dialog.text = "¡Maldita sea, Cap! Pensé que te desharías de mí a la primera oportunidad que tuvieras, pero siempre me sorprendes. Por supuesto que estoy contigo, y gracias por darle a este idiota la verdadera vida de un lobo de mar!";
				Link.l1 = "¡Bien hecho, "+npchar.name+"!";
				Link.l1.go = "folke_tieyasal";
				break;
			}
			if(npchar.id == "Duran")
			{
				dialog.text = "¿Eh? ¿Realmente dije eso?";
				Link.l1 = "Lo hiciste. Te escuché atentamente entonces, y estoy listo para corregir la injusticia.";
				Link.l1.go = "Duran_tieyasal";
				break;
			}
			dialog.text = LinkRandPhrase("Lo siento, capi, pero eso no es lo que firmé. No pienses que soy un cobarde, pero no estoy dispuesto a ir y enfrentar una muerte segura. No estoy tan cansado de vivir, al menos no todavía. Puedes despedirme si quieres.","Capitán, ruego que me perdone. Mares, abordajes, ciudades enemigas, todo eso está perfectamente bien, pero no quiero meterme con esa brujería india. Si estás molesto con mi respuesta, puedes cancelar nuestro contrato.","Deseas lo imposible, capitán, y te das cuenta de ello. Nadie volverá con vida, incluyéndote a ti, así que pasaré. Si consideras mi negativa una violación de los términos del contrato, puedes cancelarlo.");
			link.l1 = LinkRandPhrase("No te culpo, oficial. Lo entiendo perfectamente.","Una lástima, pero puedo entenderte. Por eso te lo conté de antemano.","Contaba contigo... Pero puedo entender tu posición, oficial.");
			link.l1.go = "tieyasal_1";
		break;
		
		case "Duran_tieyasal":
			dialog.text = "¡Eh! ¿Entonces aumentarás mi paga?";
			Link.l1 = "¡De ninguna manera! Me voy a una antigua ciudad india. El trabajo es suicida, pero habrá oro allí...";
			Link.l1.go = "Duran_tieyasal_2";
		break;
		
		case "Duran_tieyasal_2":
			dialog.text = "No me interesa el oro. Sería un honor ayudarte, Cap, como una vez me ayudaste a mí. ¿Cuándo nos vamos?";
			Link.l1 = "¡Bien dicho, Claude! Está en plena preparación, no tardará mucho ahora.";
			Link.l1.go = "Duran_tieyasal_3";
		break;
		
		case "Duran_tieyasal_3":
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "folke_tieyasal":
			Achievment_Set("ach_CL_108");
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.Tieyasal = "true";
		break;
		
		case "TransferGoodsEnable":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
	        {
				dialog.text = "¡Capitán, ¿qué mercancías? ¡Primero necesitamos encontrarnos un barco!";
				Link.l1 = "Sí, tienes razón.";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
	        }
	        	
			PChar.TransferGoods.Enable = true;
		//	PChar.TransferGoods.TreasurerID = NPChar.id;
			Dialog.text = "Será hecho, "+GetSexPhrase("señor","señorita")+"¡capitán!";
			Link.l1 = "A sus anchas.";
			Link.l1.go = "TransferGoodsEnable_2";
        break;
        	
		case "TransferGoodsEnable_2":
			Diag.CurrentNode = "Hired";
			DialogExit();
			LaunchTransferGoodsScreen(); // Интерфейс автозакупки товаров
		break;
		
		case "TransferGoodsDisable":
			DeleteAttribute(PChar, "TransferGoods.Enable");
			Dialog.text = "Se hará, "+GetSexPhrase("señor","señorita")+"¡capitán!";
			Link.l1 = "Con calma.";
			Link.l1.go = "exit";
			Diag.TempNode = "Hired";
		break;
        
		case "ShowParam_exit":
			Diag.CurrentNode = "OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;
		
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();			
		break;

		case "exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
			if(CheckAttribute(pchar,"systeminfo.tutorial.Fighter") && Npchar.quest.officertype == "fighter")
			{
				DeleteAttribute(pchar,"systeminfo.tutorial.Fighter");
				LaunchTutorial("Fighter", 1);
			}
		break;

		case "exit_fire":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();			
				break;
			}
			//navy <--
			Diag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;

			DialogExit();			
		break;
		
		// boal 29.05.04 офицер хочет свалить -->
        case "WantToGo":
			if (npchar.id == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_SobytieKlodDuran"))
			{
				SetTimerCondition("SKD_DuranTavern", 0, 0, 30, false);
				pchar.questTemp.SKD_SobytieKlodDuran = true;
			}
			chrDisableReloadToLocation = false;
			Diag.TempNode = "Hired";
			dialog.text = LinkRandPhrase(LinkRandPhrase("Capitán, sabes, yo... Bueno, te pediría que me liberes. Es hora de que me establezca, me case y tenga algunos hijos. Todavía no tengo hogar propio, cuando me haga viejo no habrá nadie para traerme un vaso de agua.","Capitán, por favor, déjame renunciar. Durante todos estos años he estado deambulando por todo el mundo, y aún no he visto realmente nada. Solo quiero vivir una nueva vida, echar el ancla y ver el mundo desde una perspectiva diferente.","Capitán, el servicio naval es seguramente una cosa fina, hay buen beneficio y aventura, pero ha llegado el momento para mí de pensar en mí mismo. Como puedes imaginar, echar un ancla en un puerto tranquilo, comprar una casa, tener hijos. Por favor, déjame ir."),LinkRandPhrase("Capitán, sabes, realmente lo siento, pero estoy harto de todos esos deberes, vigilias y disciplina. Sabes, solo quiero vivir una vida libre al menos por un tiempo, pero entiendo que no estarás esperándome, así que... ¿Podrías darme de baja?","Capitán, sabes... Hay un pequeño barco que puedo permitirme, así que... Creo que probablemente sea el momento de iniciar mi propio negocio. Por favor, ¿podrías dejarme ir?","Capitán, acaban de ofrecerme un puesto en el puerto. La verdad, hace tiempo que deseo echar el ancla y establecerme en una vida matrimonial. Por favor, permíteme ir. Realmente no puedo perder una oportunidad así."),LinkRandPhrase("Capitán, estoy realmente enfermo de mar. Los doctores siguen diciéndome que es idiosincrasia. Por favor, por el amor de Dios, déjame ir, o simplemente saltaré por la borda en algún momento.","Capitán, creo que es hora de que me asiente y encuentre un lugar más tranquilo. Sabes, tengo miedo. Miedo a las balas perdidas, miedo a morir durante un abordaje. Rezo al Señor para que me mantenga vivo, y cuando cierro los ojos, veo todas las almas inocentes que he matado. Me están rogando que los perdone... Por favor, muestra algo de compasión, y déjame ir.","Capitán, mis viejas heridas me duelen, y la reciente contusión se recuerda a sí misma cada día. Pronto me despedirás, ¿y quién me contratará después de eso? Por favor, déjame ir, me curaré y encontraré un lugar más tranquilo."));
			Link.l1 = RandPhraseSimple(LinkRandPhrase("Todos se van eventualmente. Bien, eres libre de irte.","Puedo entender tu razonamiento. Tarde o temprano todas las cosas llegan a su fin. Bueno, vete entonces... y no guardes rencor si alguna vez te ofendí.","¿Esto otra vez? Has elegido deliberadamente el momento más inoportuno posible para dejarme, ¿verdad? Lo que sea. Adiós."),LinkRandPhrase("Difícil de creer en lo que me estás contando... Bueno, empaca tus cosas y vete.","¿Tú? No lo esperaba... Después de todo este tiempo luchando espalda con espalda... Bueno, no te detendré. Vaya con Dios.","Suena serio. Bueno, te deseo suerte, debes saber que te echaré de menos."));				
			Link.l1.go = "WantToGo_free";
			if (sti(Pchar.money) >= sti(NPChar.rank)*250)
			{
				Link.l2 = LinkRandPhrase("Ya veo... Así que así es, ¿eh? Y yo que contaba contigo... Bueno, si ya has tomado una decisión entonces dejémonos ir. Toma "+sti(NPChar.rank)*250+" pesos por tu leal servicio. Y no guardes rencor si alguna vez te ofendí.","Bueno, no guardo rencor y no recuerdo ningún mal. Si eso es lo que decidiste, entonces vete. Y toma "+sti(NPChar.rank)*250+" pesos para tener un nuevo comienzo, definitivamente vendrá bien.","Ya veo... Bueno, tarde o temprano eso tenía que suceder. Te daré "+sti(NPChar.rank)*250+" pesos para saldar tu vida. Y cuida también tu salud, el servicio naval está lleno de dificultades..."); 
				Link.l2.go = "Im_kind_A2_1";
			}
			Link.l3 = LinkRandPhrase("¿Así que lo dices...? ¿No te das cuenta de que al irte ahora simplemente me estás apuñalando por la espalda? No puedo dejarte ir ahora, ni siquiera lo pienses.","¡Vaya noticia! Sabes, se supone que la gente debe notificarme de estas cosas con anticipación. Así que olvídate de tu vida privada por un tiempo. Cuando llegue el momento, te sugeriré cuándo retirarte.","Sin renuncias. Tengo a todos en cuenta. No puedo dejar ir a todos solo por su deseo personal. Sirve, mientras considero si mereces un descanso.");	
			Link.l3.go = "WantToGo_Stay";
		break;
		
		case "Im_kind_A2_1":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*250)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "¡Gracias, capitán! Una generosidad realmente inesperada... Sabes, todavía tengo algunas de tus cosas, ¿quizás te gustaría recuperarlas?";
			Link.l1 = "Quizás... Encontrar una buena espada no es tan fácil en estos días.";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "Oh, no te molestes. Guárdalos como recuerdo de tu servicio.";
			Link.l2.go = "WantToGo_free";
		break;
		
		case "WantToGo_Stay":
			dialog.text = RandPhraseSimple("¿Pero cómo es eso, capitán? Incluso los esclavos son finalmente enviados a la orilla. ¡Y yo no soy un esclavo, así que puedo decidir mi destino por mí mismo!","Capitán, te he servido fielmente todo este tiempo. ¿No merezco el derecho de decidir mi destino por mí mismo?");
			Link.l1 = LinkRandPhrase("Veo que no puedo retenerte como están las cosas. Está bien, ¿qué tal algo de apoyo financiero? Esto nunca hará daño, puedes usar ese dinero para construirte un hogar acogedor en un puerto tranquilo o cuidar de tu salud.","Bueno, pongámoslo de esta manera. ¿Qué suma podría hacer que reconsideres tu decisión?","Tienes razón. Pero ¿qué tal una ayuda monetaria por única vez, eso cambiaría tu opinión?");
			Link.l1.go = "WantToGo_Stay_2";
			Link.l2 = PCharRepPhrase(RandPhraseSimple("Ah, no, mi amigo, aquí estás equivocado... Mientras estabas desperdiciando tu tiempo en las tabernas persiguiendo faldas tras las copas, entonces podías decidir por ti mismo, pero una vez que subiste a bordo de mi barco, entonces entregaste tu destino en mis manos.","Hmm. Ahora, eso es una declaración seria. Al parecer, has olvidado cómo te encontré, en una taberna apestosa sin un cobre en tu bolsillo. Ni siquiera se te puede mostrar una sola moneda de oro, porque de inmediato la convertirás en ron. 'Decide mi destino...' ¡Pfff! ¡Qué chiste!"),LinkRandPhrase("Mientras estés a mi servicio, soy yo quien toma las decisiones. ¡Y ahora, por favor, vuelve a tus deberes antes de que me enfades demasiado!","Hmm. Ahora, eso es una declaración seria. Pero aún no has trabajado todo el dinero que te pagaron por adelantado. Entonces, ¿se puede considerar tu demarche como un intento de extorsión, verdad?","Oh, ya veo... ¿Qué dicen de nuevo las regulaciones del barco? Aquí, párrafo dos: 'Quien intente abandonar sin permiso será abandonado en una costa desierta con una única bolsa de pólvora, una cantimplora de agua, una pistola y una sola bala'. Ahora, ¿cómo te gustaría eso?"));	
			Link.l2.go = "WantToGo_Stay_force";
		break;
		
	case "WantToGo_Stay_2":
		dialog.text = LinkRandPhrase("Bueno, esa es una historia diferente. "+sti(NPChar.rank)*500+" pesos en el clavo, y me quedaré contigo.","Bueno, quizás para "+sti(NPChar.rank)*500+" pesos podría quedarme, supongo.","Bueno, si lo pones de esa manera, por "+sti(NPChar.rank)*500+" pesos podría continuar mi servicio.");
		if (sti(Pchar.money) >= sti(NPChar.rank)*500)
		{
			Link.l1 = RandPhraseSimple("De acuerdo, aceptado.","Está bien. Aunque podrías pedir menos.","¡Veo que tienes un apetito considerable! Pero, te hice una promesa, ¿no es así?, y me mantendré fiel a mi palabra.");	
			Link.l1.go = "WantToGo_Stay_ForMoney";
		}
		Link.l2 = LinkRandPhrase("Eso es demasiado. Podría contratar a dos oficiales por ese precio. Tal vez, sea más sencillo simplemente dejarte ir.","Bueno, ciertamente tienes una alta opinión de ti mismo. Está bien, te dejaré ir. Pero verás por ti mismo, una vez que estés libre, que tu vida no será tan despejada como esperabas.","No voy a pagar tal dinero. Puedes irte, pero ni siquiera pienses en volver, no perdono la traición.");				
		Link.l2.go = "WantToGo_free";
	break;
	
	case "WantToGo_Stay_force":
		Npchar.loyality = makeint(Npchar.loyality) - 2;
		dialog.text = "Está bien, si lo pones de esta manera, me quedaré. Pero debes saber que al hacerlo voy en contra de mi propia voluntad.";
		Link.l1 = LinkRandPhrase("Muy bien. Regresa a tus deberes, y continuaremos esta conversación más tarde.","Regresa al barco. Y la próxima vez piensa de nuevo antes de pedir la jubilación.","Ciertamente. El deber es el deber, y no deberías estar entregándote a tus fantasías todavía.");
		Link.l1.go = "exit";
	break;
	
	case "WantToGo_Stay_ForMoney":
		Diag.TempNode = "Hired";
		NPChar.greeting = "Gr_Officer";
		if(NPChar.id == "Duran") NPChar.greeting = "Duran_officer";
		ChangeCharacterComplexReputation(pchar,"authority", 0.2);
		AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
		Npchar.loyality = makeint(Npchar.loyality) + 1;    
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
		NPChar.location = "none";
		LAi_SetOfficerType(NPChar);
	break;
	
	case "WantToGo_free":
		//navy -->
		if (CheckAttribute(NPChar, "PGGAi"))
		{	
			pchar.questTemp.FiringOfficerIDX = NPChar.index;
			AddDialogExitQuestFunction("PGG_FireOfficer");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();	
			break;
		}
		//navy <--
		Diag.TempNode = "WantToGo_free_Yet";
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
		AddDialogExitQuestFunction("LandEnc_OfficerFired");
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
	break;
	
	case "WantToGo_free_Yet":
		Diag.TempNode = "WantToGo_free_Yet";
		dialog.text = LinkRandPhrase("¡No lo puedo creer! Gracias Capitán, es un gran alivio para mi mente.","Gracias, capitán, por no intentar retenerme. Sabes, realmente quiero probar otras cosas en la vida.","Je, ahora tendré que acostumbrarme a mi nueva libertad. Solo ahora he comenzado a darme cuenta de lo harto que estaba de todo ese servicio de flota.");	
		Link.l1 = RandPhraseSimple("Bueno, te deseo la mejor de las suertes.","Ahora eres libre. Tu servicio ha terminado.");
		Link.l1.go = "exit";
	break;
	// boal 29.05.04 офицер хочет свалить <--
		
	// пассажир возмущен игроком и сваливает -->
	case "WantToRemove":
		if (npchar.id == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_SobytieKlodDuran"))
		{
			SetTimerCondition("SKD_DuranTavern", 0, 0, 30, false);
			pchar.questTemp.SKD_SobytieKlodDuran = true;
		}
        chrDisableReloadToLocation = false;
		if (Npchar.alignment == "good")
		{
			dialog.text = RandPhraseSimple(LinkRandPhrase("Capitán, no quiero actuar contra mi conciencia y participar en el bandolerismo.","Capitán, ya no deseo participar en tus disturbios. Soy un oficial, no un carnicero.","Capitán, tus modales bandidos de hacer negocios hacen mi estancia en tu tripulación imposible."),LinkRandPhrase("Capitán, debo admitir que mi empleo contigo fue un error decepcionante. No estoy dispuesto a sacrificar mi reputación por dinero alguno.","Capitán, has reunido en tu barco a todos los malhechores más villanos del Nuevo Mundo. Es repugnante para un hombre decente incluso mirarlos. No quiero seguir sirviendo con tal tripulación.","Capitán, has contratado a una tripulación completa de granujas, no hay un solo hombre decente con quien charlar. Desprecio tal servicio."))+"Adiós.";
			Link.l1 = "¿¡Qué?! ¡Es un barco militar, no una escuela de etiqueta! ¡Puedes irte al infierno entonces!";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Sabía que pronto te irías... este servicio no es para ti. Pero no me acuses de nada. Aquí están "+sti(NPChar.rank)*500+" pesos, los encontrarás útiles mientras buscas un trabajo a tu gusto.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = LinkRandPhrase("Ah, así que esa es la canción que estás cantando ahora. ¿Y qué hay de tu parte de cada y cada uno de los robos, te queman las manos? ¿O estás planeando retirarte a un monasterio para rezar por el perdón de tus pecados? ¡Menciona también una palabra por nosotros! ¡Ja-ja-ja-ja-ja!","Hmm. Ahora, eso es una afirmación seria. ¿Y dónde estaba tu inocente conciencia mirando mientras robábamos juntos a los comerciantes? ¿Cómo vas a limpiarla? ¿O vas a delatarnos, para que colguemos en la horca en buena compañía?","¡Oh, bravo! Al parecer, has olvidado cómo te encontré, en una taberna apestosa sin un cobre en tu bolsillo. Para tu información, como oficial no vales ni un maldito maravedí. ¡No vales nada!");
			Link.l3.go = "WantToGo_stop";
		}
		else
		{
            dialog.text = RandPhraseSimple(LinkRandPhrase("Capitán, realmente detesto tus nobles juegos y no voy a abandonar mis costumbres por el bien de tu serenidad. Adiós.","Capitán, ya no puedo permanecer en tu servicio. Ya he desperdiciado demasiado tiempo. Siendo un simple corsario, ya me ganaría una fortuna. Me voy.","Capitán, tus hombres me asquean. Ni un solo hombre decente, solo pantalones elegantes, ninguno con quien compartir una copa. Me voy."),LinkRandPhrase("Capitán, soy un oficial veterano, y su barco parece más un barco de carga. No me agrada tal servicio. Adiós.","Capitán, tu entera tripulación son todos unos finolis, no hay un solo hombre con quien beber o hablar. Tengo un fuerte desagrado por tal servicio. Adiós.","Capitán, solía pensar que servía bajo un verdadero corsario, ¡pero todo lo que hacemos es solo caridad! No quiero seguir perdiendo mi tiempo. Me voy."));
			Link.l1 = RandPhraseSimple("Ya veo. Teniendo en cuenta tu actitud, eso debería haber sucedido tarde o temprano. De acuerdo, no te retendré.","Tu declaración no fue inesperada. Francamente, he estado insatisfecho con tu actitud durante bastante tiempo.")+"Buena suerte.";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Sabía que pronto te irías... este servicio no es para ti. Pero no me acuses de nada. Aquí están "+sti(NPChar.rank)*500+" pesos, te vendrán bien mientras buscas un nuevo trabajo.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = RandPhraseSimple("Hmm. Ahora, esa es una declaración seria. Pero aún no has trabajado todo el dinero que se te pagó por adelantado. Entonces, tu demarche puede considerarse un intento de extorsión, ¿verdad?","Oh, ya veo... ¿Qué dicen los reglamentos del barco? Aquí, párrafo dos: 'Quien intente abandonar sin permiso será abandonado en una costa desierta con una sola bolsa de pólvora, un frasco de agua, una pistola y una única bala.' Ahora, ¿cómo te gustaría eso?");
			Link.l3.go = "WantToGo_stop";
		}
		break;
		
		case "WantToGo_stop":
			if (Npchar.alignment == "good")
			{
				dialog.text = LinkRandPhrase("¡Ni siquiera intentes insultarme! Trabajo por dinero, pero aún tengo el derecho de escoger el trabajo que me guste!","¡Soy un hombre libre! ¡Y tengo el derecho de tomar un nuevo trabajo cuando quiera!","No soy un esclavo para trabajar por comida, ¡así que mi conciencia está tranquila! Pero ya no participaré en robos!");
				Link.l1 = "Bueno, en realidad, estás equivocado... Mientras estabas bebiendo en la taberna, entonces podrías elegir cualquier trabajo que te gustara... Pero tan pronto como pisaste a bordo de mi barco, tu única vía de regreso se convirtió en una bala de cañón que destroza tu cuello... Y con tu lengua arrancada, para que no sueltes nada en el otro mundo...";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "Está bien. Puedes irte... Pero Dios te prohíba encontrarme en alta mar. Juro que lamentarás el momento en que decidiste no quedarte a mi lado.";
				Link.l2.go = "exit_fire_5";
			}
			else
			{
				dialog.text = LinkRandPhrase("¡Ni siquiera intentes intimidarme! Trabajo por dinero, ¡pero aún tengo el derecho de elegir un trabajo que me guste!","¡Soy un hombre libre! ¡Y tengo el derecho de tomar un nuevo trabajo cuando quiera!","¡No soy tu esclavo! ¡Y no voy a seguir llevando una vida miserable en tu viejo cascarón!");
				Link.l1 = "Bueno, en realidad, estás equivocado... Mientras estabas bebiendo en la taberna, podías elegir cualquier trabajo que te gustara... Pero en cuanto pusiste un pie a bordo de mi barco, tu único camino de regreso se convirtió en una bala de cañón que destroza tu cuello... Y con la lengua arrancada, para que no divulgues nada en el otro mundo...";
				// belamour legendary edition можно запугать офицера -->
				//if (makeint(Pchar.Rank) > makeint(NPchar.Rank) || CheckCharacterPerk(pchar, "IronWill"))
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "Está bien. Puedes irte... Pero Dios te prohíba encontrarte conmigo en mar abierto. Te juro, lamentarás el momento en que decidiste no quedarte a mi lado.";
				Link.l2.go = "exit_fire_5";
			}
		break;
		
		case "WantToGo_stop_stay":
			dialog.text = RandPhraseSimple("Si lo pones de esta manera, me quedaré, simplemente no tengo otra opción. Pero ten en cuenta que no lo hago por mi propio gusto...","Está bien, si lo pones de esa manera, me quedaré. Pero que sepas que al hacerlo voy en contra de mi propia voluntad.");
			Link.l1 = RandPhraseSimple("Eso está bien... Sirve hasta que decida cuándo dejarte ir.","Eso está bien. Sigue sirviendo... Decidiré cuándo dejarte ir.");
			Link.l1.go = "WantToGo_Munity"; //этот линк ведет к бегству
		break;
		
		case "WantToGo_stop_fight":
			dialog.text = NPCharRepPhrase(NPChar,"¡Nunca me obligarás a reconsiderar! ¡No tienes derechos para mantenerme como esclavo! Voy a irme, aléjate o estás acabado.","¿Crees que puedes asustar a un oficial veterano?! Más de una vez he estado a un pelo de la muerte. Y si lo pones de esa manera, es mucho mejor morir en una batalla justa que durante un sangriento saqueo!");
			Link.l1 = NPCharRepPhrase(NPChar,"Bueno... cada uno elige su propio destino. Espero que hayas dicho tus oraciones antes de venir a mí.","Si hubiera sabido que eso sucedería cuando te recogí en la taberna, te habría dejado colgando de la horca en su lugar. Y ahora no es demasiado tarde para organizarlo...");
			Link.l1.go = "WantToGo_stop_fight_1";
			Link.l2 = NPCharRepPhrase(NPChar,"Bueno, puedes irte si necesitas tanto tu libertad. Pero no te daré ninguna recomendación.","Está bien. Puedes irte... Pero Dios te prohíba encontrarme en alta mar. Te lo juro, te arrepentirás del momento en que decidiste no quedarte a mi lado.");
			Link.l2.go = "exit_fire_5";	
		break;
		
		case "WantToGo_stop_fight_1":
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			dialog.text = NPCharRepPhrase(NPChar,"¡Deja de intimidarme ya! ¿Quién de tus cobardes se atreverá a enfrentarme? ¡Si yo fuera capitán, ya estarían nadando en dinero! ¿Y después de que te has involucrado en toda esta caridad, temes que tu tripulación se pase a mi lado?!","¡Deja tus maneras, no me asustarás! Adiós.");
			Link.l1 = NPCharRepPhrase(NPChar,"No, compadre, no vivirás lo suficiente para llegar a la horca. Tal lujo no es para ti...","No tan rápido camarada, aún no estamos a mano, me debes.");
			Link.l1.go = "Get_out_fight";
		break;	
		///////////////////////////////////////////////////////////////////////////////////
		case "WantToGo_Munity":	//zagolski. отыгрыш бегство офицера
			Diag.TempNode = "Hired";
			// belamour legendary edition в ближайшее время не подойдет от страха
			/* if(CheckCharacterPerk(pchar, "IronWill"))
			{
				Npchar.loyality = makeint(Npchar.loyality) + 3 + hrand(sti(GetSummonSkillFromNameToOld(pchar,SKILL_FORTUNE)+GetSummonSkillFromNameToOld(pchar,SKILL_LEADERSHIP)));
				log_info(GetFullName(Npchar)+" increased his loyalty");
				log_testinfo("Loyalty has become: " + Npchar.loyality + " of " + MAX_LOYALITY);
			}
			else
			{ */
				if (!CheckAttribute(pchar, "questTemp.MutinyOfficerIDX"))
				{
					pchar.questTemp.MutinyOfficerIDX = npchar.index;
					npchar.quest.Mutiny = true; // mitrokosta доп защита от багов
					SetFunctionTimerCondition("mOfficer_fc", 0, 0, 1, false);
				}
			//}
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
			DialogExit();
		break;
		////////////////////////////////////////////////////////////////////
		// пассажир возмущен игроком и сваливает <--
		
		case "Node_2":
			dialog.text = NPCharRepPhrase(Npchar,RandSwear()+"Soy el mejor "+XI_ConvertString(Npchar.quest.officertype)+" dentro de estas aguas. "+Npchar.quest.officertype_2+"Y estoy listo para hacerte un favor y servir bajo tu mando.","Bueno, dicen que no soy malo "+XI_ConvertString(Npchar.quest.officertype)+". "+Npchar.quest.officertype_2+"Puedes llevarme en tu barco, capitán, y verlo por ti mismo.");
			Link.l1 = "¿Y cuánto quieres?";
			Link.l1.go = "price";
			Link.l2 = "¿Y qué tipo de especialista eres tú?";
			Link.l2.go = "ShowParam_exit";
			Link.l3 = "¡Ay, ya tengo un "+XI_ConvertString(Npchar.quest.officertype)+".";
			Link.l3.go = "Exit";
		break;

		case "OnceAgain":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Je, capitán, la mitad de la guarnición te persigue en este momento. ¡Seguramente no es el mejor momento para ser contratado en tu tripulación!","¿Y luchando para abrirnos camino hasta el barco? No, capi, en otro momento...");
				link.l1 = RandPhraseSimple("Como deseas...","De hecho, no iba a contratarte."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "¿Has cambiado de opinión, capitán? ¿Has decidido que una nueva "+XI_ConvertString(Npchar.quest.officertype)+"¿no haría daño?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "Algo así. ¿Cuánto quieres?";
                Link.l1.go = "price";
			}
			Link.l2 = "¿Y de qué eres capaz?";
			Link.l2.go = "ShowParam_exit";
			// boal <--
			Link.l3 = "Tengo un set completo. Nos vemos.";
			Link.l3.go = "exit";
		break;

		case "price":
			dialog.text = "Creo que podemos estar de acuerdo en "+Npchar.quest.OfficerPrice+" pesos.";
			if(Npchar.rank >= 15)
			{
				dialog.text = "Creo que podemos estar de acuerdo en "+(makeint(Npchar.quest.OfficerPrice)/ 100+30)+" doblones.";
			}	
			Link.l1 = "¿No es eso un poco demasiado?";
			Link.l1.go = "trade";
			Link.l2 = "Estoy de acuerdo. Considérate parte de la tripulación.";
			Link.l2.go = "hire";
			Link.l3 = "No vales este dinero.";
			Link.l3.go = "exit";
		break;

		case "trade":
			if (GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) >= Rand(12) && (sti(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100) >= sti(Npchar.quest.OfficerLowPrice))// bug fix
			{
				Npchar.quest.OfficerPrice = makeint(makeint(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100); // пусть будет коммерция перса голой
				dialog.text = "Está bien... Supongo que podría estar de acuerdo incluso en "+Npchar.quest.OfficerPrice+" pesos. ¿Qué dices?";
				if(Npchar.rank >= 15)
				{
					dialog.text = "Supongo que podría estar de acuerdo incluso en "+(makeint(Npchar.quest.OfficerPrice)/ 100+30)+" doblones. ¿Qué dices?";
				}
				Link.l1 = "Ahora eso está mejor. Estás dentro.";
				Link.l1.go = "hire";				
				Link.l2 = "Aún pienso que es un poco demasiado. Adiós.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = "Lo siento, capitán, pero valgo exactamente lo que pedí. Si es demasiado para ti, entonces ve a buscar a alguien más.";
				Link.l1 = "Está bien, estoy de acuerdo. Te llevaré.";
				Link.l1.go = "hire";				
				Link.l2 = "Eso es lo que voy a hacer. Adiós.";
				Link.l2.go = "exit";
			}
		break;

		case "hire":
			dialog.text = "Veo que te falta dinero, ¡capitán! Lo siento, pero no trabajo a crédito.";
			Link.l1 = "¡Oh, diablo!";
			Link.l1.go = "Exit";
			if(Npchar.rank < 15 && makeint(Pchar.money) >= makeint(Npchar.quest.OfficerPrice))
			{
				AddMoneyToCharacter(Pchar, -(makeint(Npchar.quest.OfficerPrice)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "Gracias, capitán. No te arrepentirás de tu elección.";
				Link.l1 = "Espero que sí.";
				Link.l1.go = "Exit_hire";								
			}
			if(Npchar.rank >= 15 && PCharDublonsTotal() >= makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)))
			{
				RemoveDublonsFromPCharTotal(makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "Gracias, capitán. No lamentará su elección.";
				Link.l1 = "Espero que sí.";
				Link.l1.go = "Exit_hire";								
			}
		break;

		case "OnboardSoon":			
			Diag.TempNode = "OnboardSoon";
			dialog.text = "Solo terminaré mi bebida, capitán, y luego iré al barco. No te preocupes, estaré allí a tiempo.";
			Link.l1 = "Está bien. Si llegas tarde, ¡te haré fregar la cubierta!";
			Link.l1.go = "Exit";											
		break;
        
		case "QMASTER_1":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = "¡Capitán, pero no tienes barco!";
				Link.l1 = "Gracias por recordarme...";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}
			// Rebbebion, добавил фикс отображения знака процента
			dialog.text = "Máxima actividad de ratas en viaje "+FloatToString(50.0 /(2.0+GetSummonSkillFromNameToOld(PChar,SKILL_REPAIR)+GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)),1)+"%% del total de la cantidad de carga. Para "+GetCrewQuantity(PChar)+" marineros vamos a necesitar "+makeint((GetCrewQuantity(PChar)+6)/ 10)+" alimentos por día. Esto sin contar con los esclavos que se están transportando.";
			Link.l1 = "Gracias.";
			Link.l1.go = "Exit";
			Diag.TempNode = "Hired";
		break;
        
        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = "¿Cuáles son tus órdenes?";
            Link.l1 = "¡Quédate aquí!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "¡Sígueme y no te quedes atrás!";
            Link.l2.go = "Boal_Follow";
            // boal 05.09.03 offecer need to go to abordage <--
			if (npchar.id == "OffMushketer")
			{
				Link.l3 = "Quiero que te mantengas a cierta distancia del objetivo.";
				Link.l3.go = "TargetDistance";
			}
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l4 = "Necesitamos cambiar el tipo de munición para tu arma de fuego.";
					Link.l4.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l5 = "Necesitamos cambiar el tipo de munición para tu mosquete.";
					Link.l5.go = "SetMusketBullets";
				}
					Link.l6 = "Necesitamos cambiar tu arma prioritaria para el combate.";
					Link.l6.go = "SetPriorityMode";
			}
		break;

		case "SetGunBullets":
			Dialog.Text = "Selecciona el tipo de munición:";
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
			Diag.CurrentNode = Diag.TempNode;
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
				Link.(attrL).go = "SetMusketBullets1_" + i;
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
			Diag.CurrentNode = Diag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "Al comienzo de la pelea usarás:";
			Link.l1 = "Espada";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Escopeta";
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
		
		case "TargetDistance":
			dialog.text = "¿Qué distancia exactamente, capitán? Indica en pasos, pero no más de 20.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Capitán, ¿estás bien?";
				link.l1 = "Lo siento, mi culpa...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Me quedaré en el lugar sin moverme. ¿Es eso lo que quieres de mí, capitán?";
				link.l1 = "Sí. Eso es exactamente lo que se necesita de ti.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Creo que te dije que no puedo estar a más de 20 pasos del objetivo.";
				link.l1 = "Está bien, mantén la distancia de 20 metros.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Entendido y tenido en cuenta.";
			link.l1 = "Bien.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;

		case "AsYouWish":
			// проверка на море -->
			if (bSeaActive)
			{
				attr = Sea_FindNearColony();
				if (attr == "none")
				{
					dialog.text = "Capitán, aunque realmente no entiendo su razonamiento, ¿podríamos hablar de esto en la orilla? ¿O decidió simplemente echarme por la borda?";
					Link.l1 = "Hmm... No, eso no es lo que quería decir. Quédate aquí hasta que lleguemos al puerto.";
					Link.l1.go = "Exit";	
					break;	
				}
			}
			// проверка на море <--
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) < 41) //герой против злодея
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("¡Esto es nuevo!","¿Por qué, en el cielo?","¿Cuál es la razón?!"),RandPhraseSimple("¿Capitán, estás loco? ¡Decir tal noticia a propósito de nada!","¡Vaya! ¿Y qué he hecho yo para disgustarte?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Decidí poner orden en la tripulación. Y no me gustan tus relaciones con tus colegas","Tus ventajas no fueron tan buenas como se discutió en la contratación. Entonces,","¡Los matones y granujas en mi equipo no se quedarán! Entonces,"),LinkRandPhrase("Llegó a mi conocimiento que estás robando ron, acostumbrando secretamente a mi tripulación a beber en exceso y así disminuyendo su moral. Por lo tanto,","Estoy harto de tus modales de bandido y no voy a tolerarlo. Así que,","Constantemente pasas tu tiempo en la cabaña central para un juego de cartas o dados, distrayendo a los otros oficiales del desempeño de su deber. Esto no puede continuar indefinidamente. Entonces,"))+"empaca tus pertenencias y abandona el barco.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A1_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A1_strife";
				}
				break;	
			}
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) >= 41) // герой против героя
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("¿Puedo saber la razón de tal decisión?","Obviamente, ¿tal decisión está bien fundamentada?"),RandPhraseSimple("Explícate, capitán","Eso es bastante inesperado. Pero aún me gustaría saber la razón."));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Estoy totalmente insatisfecho con tu actitud hacia tus deberes.","Lamentablemente, no fuiste un buen oficial y probablemente nunca lo serás...","Eres un buen oficial y tu servicio fue justo, pero ahora nuestros caminos se han separado. No me preguntes por qué."),LinkRandPhrase("Te advertí que la pasión por el ron te destruiría. ¿Cómo puedo confiar en un hombre en una pelea que ni siquiera es capaz de meter su espada en la vaina?","Eres un marinero y oficial terrible... Creo que pasarás más tiempo en la costa que en el mar.","No estoy satisfecho con tus cualificaciones, pero ahora finalmente he encontrado un reemplazo decente."));
				Link.l1.go = "Get_out_A2";
				break;	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) >= 41) // злодей против героя 
			{		
				dialog.text = RandPhraseSimple(RandPhraseSimple("¿Hmm... Puedo saber la razón?","Esa es una afirmación seria. ¿Puedo saber con qué en particular estás insatisfecho?"),RandPhraseSimple("Explícate, capitán.","Obviamente, ¿tal afirmación está bien fundamentada?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Estoy totalmente insatisfecho con tu calificación, por lo tanto","Lamentablemente, no te mostraste como un oficial decente. Entonces,","Estoy harto de tus modales nobles. No voy a tolerarlos eternamente, así que"),LinkRandPhrase("Llegó a mi conocimiento que estás instigando a la tripulación a la desobediencia. ¡No habrá disturbios en mi barco! Y no me agradezcas que no te haya echado antes. Así que","Tus nobles principios te honran, pero son contrarios a la vida de ladrón de corsario libre. Entonces","No me gusta tu relación con tus deberes. Así que"))+"empaca tus pertenencias y abandona el barco.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A3_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A3_strife";
				}	
				break;
	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) < 41) // злодей против злодея
			{	
				dialog.text = RandPhraseSimple(LinkRandPhrase("Capitán, ¡realmente no esperaba eso! ¿Quizás explicarías qué está pasando?","¡Capitán, qué te carcome?!","¿Qué quieres decir con eso, capitán?!"),RandPhraseSimple("¿Qué diablos, capitán?! Todo parecía estar bien ayer, y ahora aquí estamos, ¿qué pasó?","¡Vaya! Quizás, ¿te explicarías?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Eres un completo vago e inútil, incluso un grumete en un barco costero lo haría mejor. He estado sufriendo por tu culpa durante demasiado tiempo. Así que","He estado pensando en despedirte durante un tiempo, y ahora finalmente he encontrado un reemplazo decente. Así que","Llegó a mi conocimiento que estás robando ron, acostumbrando secretamente a mi tripulación a la bebida fuerte y así bajando su moral. Por lo tanto"),LinkRandPhrase("Cuando te contraté, te jactabas de ser el mejor oficial de toda la flota, pero resultó que solo eras un vago, así que","Te advertí que tu hábito de beber terminaría mal. ¿Por qué debería mantener a un borracho inútil en mi barco? Así","En lugar de servir, estás constantemente vagando en alguna parte o jugando a las cartas o dados. ¿Esperabas que esto pudiera continuar para siempre? Así que"))+"empaca tus pertenencias y abandona el barco.";
				Link.l1.go = "Get_out_A4";
				break;
			}
		break;
	
		case "Get_out_A1_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("¡Así que así hablas ahora! Está bien, como desees. Pero tenlo por seguro: no volveré a ti, ¡incluso si me estoy muriendo de hambre!","Sinceramente, tampoco me gustan mucho tus nobles juegos. Así que adiós...","¡Oh, vete al infierno! Quédate con tus lambiscones. ¡Un 'héroe', en efecto!"),LinkRandPhrase("En realidad, nunca me gustó servirte... Tienes una barcaza de carga allí, no un barco decente. Más bien parece una escuela de terminación...","Sabes, estoy harto de tu tripulación, todos esos presumidos, solo pequeños críos, ni un solo hombre de verdad...","Está bien, capitán, como usted diga. Pero Dios sabe, había estado haciendo bien mi trabajo..."));
			Link.l1 = "Espera. En este momento no puedo abandonar el barco sin un oficial. Pero más tarde volveremos a esta conversación.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Entonces vete en paz.";
			Link.l2.go = "Exit_Fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "No te enfades. He preparado para ti una indemnización por despido, "+sti(NPChar.rank)*500+" pesos. Espero que esto elimine todas las preguntas.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife":
			dialog.text = LinkRandPhrase("¡Disculpa! ¿Qué quieres decir con 'abandonar el barco'?! ¡No expuse mi cabeza a la metralla solo para que me echaras cuando quieras!","¡Ja! 'Abandonar barco'! ¿Realmente piensas que te permitiré que me deseches como a un gatito?!","Tranquilo, capitán, la gente seria no resuelve asuntos de tal manera. No me tratarán como a un novato.");
			Link.l1 = "Está bien, puedes quedarte por ahora, pero solo hasta que encuentre un sustituto decente.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Repito, tu servicio ha terminado. Puedes recoger tus cosas.";
			Link.l2.go = "Get_out_A1_strife_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "No te alteres. He preparado "+sti(NPChar.rank)*500+" pesos para ti. Espero que esto elimine todas las preguntas.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife_1":
			dialog.text = RandPhraseSimple("En realidad, no ardo en deseos de quedarme aquí. ¡Pero tampoco me iré sin una compensación!","¡Ahora, ciertamente no me quedaré en esa vieja tina tuya, pero primero me compensarás!")+" "+sti(NPChar.rank)*1000+" pesos, y nos olvidaremos el uno del otro.";
			Link.l1 = "Me he alterado un poco... Por favor, acepta mis disculpas y vuelve a tus deberes.";
			Link.l1.go = "exit_bad1";
			Link.l2 = "¿De qué dinero hablas si siempre has recibido tu parte justa? ¡Esto me parece extorsión!";
			Link.l2.go = "Get_out_А1_strife_battle";
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l3 = "Muy bien. Devuelve el equipo, y luego tendrás lo que pediste.";
				Link.l3.go = "Get_out_А1_chang";
			}
		break;

		case "Get_out_А1_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Ahora esa es una historia diferente. ¡Adiós!";
			Link.l1 = "Realmente espero que nuestros caminos nunca se crucen de nuevo.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_А1_strife_battle":
			dialog.text = LinkRandPhrase("Considera esto una compensación por daños morales. No toleraré tal trato, ¡y quien se atreva a tratarme así lo lamentará!","¡Esto no es una extorsión, sino más bien una compensación por esta estúpida pérdida de mi tiempo! ¡Y lo conseguiré, sin importar el costo!","He desperdiciado demasiado tiempo sirviendo bajo un marica como tú. Podría hacer una fortuna saqueando barcos mercantes. Así que solo quiero compensar mi beneficio perdido.");
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l1 = "Está bien. Aquí está tu dinero... ¡Y ahora lárgate!";
				Link.l1.go = "Get_out_А1_ForMoney_angry";
			}
			Link.l2 = "¡Parece que estás olvidando quién eres! ¡No permitiré que imbéciles como tú me griten!";
			Link.l2.go = "Get_out_А1_strife_death";
		break;

		case "Get_out_А1_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("good");
			dialog.text = "¡Adelante, capitán! ¡Muéstrate!";
			Link.l1 = "¡Dios sabe, yo no lo quería!";
			Link.l1.go = "Get_out_fight";
		break;
	
		case "Get_out_А1_ForMoney_angry":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			OfficersReaction("bad");
			dialog.text = "Ahora esa es una historia diferente. ¡Adiós!";
			Link.l1 = "Realmente espero que nuestros caminos nunca se crucen de nuevo.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_A2":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Bueno, está decidido, entonces. Adiós, capitán, y no guardes rencor...","Una lástima, capitán. Pero Dios sabe, lo intenté. Adiós.","Bueno, capitán, ¡ciertamente es difícil complacerte! Bien, te deseo la mejor de las suertes."),LinkRandPhrase("Una lástima, capitán. Sabes, me gustaba trabajar para ti.","Sí, las cosas suceden... Pero no guardo rencor. Adiós.","Eres injusto conmigo, capitán. Aun así, respeto tu decisión. Adiós."));
			Link.l1 = "Espera, he cambiado de opinión. Volvamos a hablar de esto más tarde.";
			Link.l1.go = "exit_good";
			Link.l2 = "No te enfades. Buena suerte para ti...";
			Link.l2.go = "exit_fire_2";
			Link.l3 = "Espera... Te equipé bien. Devuélvelos, no estoy para equipar a una horda...";
			Link.l3.go = "Return_items_A2";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l4 = "Espera... No quiero que te vayas con las manos vacías. Aquí, toma "+sti(NPChar.rank)*500+" pesos. Te vendrá bien mientras buscas un nuevo trabajo.";
			}
			Link.l4.go = "Im_kind_A2";
		break;

		case "Return_items_A2":
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "Ah, claro, recupéralo todo...";
			Link.l1 = "Sé que me entiendes bien...";
			Link.l1.go = "Get_out_А2_chang";
		break;

		case "Im_kind_A2":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "¡Gracias, capitán! Una generosidad realmente inesperada... Como puedes imaginar, todavía tengo algunas de tus cosas, ¿quizás te gustaría recuperarlas?";
			Link.l1 = "Quizás... Encontrar una buena espada no es tan fácil estos días...";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "Oh, no te preocupes. Guárdalos como recuerdo de tu servicio.";
			Link.l2.go = "exit_fire_2";
		break;

		case "Get_out_A3_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Está bien, como desees. Pero tenlo por seguro: ¡¡No volveré a ti, incluso si me estoy muriendo de hambre!!","Capitán, tus formas bandidas de hacer negocios también me enferman. Tarde o temprano, esto tenía que suceder. Y no hay necesidad de inventar ninguna razón.","Quédate con tus malhechores, entonces. Un hombre decente ni siquiera mostraría su cara en el salón de tu barco. ¡Qué burdel tienes aquí, Dios me perdone!"),LinkRandPhrase("Sinceramente, tampoco me gustó mi servicio bajo tu mando. Has contratado a una tripulación completa de granujas, ni un solo hombre decente con quien charlar.","Sí, si mantienes esa actitud hacia tu tripulación, pronto estarás completamente solo y no habrá necesidad de inventar ninguna razón.","Nuestra enemistad es mutua, y eso me reconforta. Adiós."));
			Link.l1 = "Espera. Ahora no es el mejor momento para tu retiro. Pero todas las reclamaciones se mantienen.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Vete, vete. Me las arreglaré bien sin tus sermones.";
			Link.l2.go = "exit_fire_3";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Espera. Te daré "+sti(NPChar.rank)*500+" pesos. No quiero que mueras en la cuneta, para que me sienta culpable de ello.";
				Link.l3.go = "Get_out_А3_ForMoney";
			}
		break;

		case "Get_out_А3_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("Bueno, gracias. Adiós...","Gracias por tu comprensión. Buena suerte.","Ahora hemos terminado. Buena suerte...");
			Link.l1 = "Sé que me entiendes bien.";
			Link.l1.go = "exit_fire_3";
		break;
	
		case "Get_out_A3_strife":
			dialog.text = LinkRandPhrase("Pero capitán, en ese caso me dejas en tierra. ¿Realmente estás dispuesto a enviarme del barco directamente al atrio?","Eres injusto conmigo, capitán. Pero no guardaré rencor si recibo una compensación decente.","¿Y esta es tu gratitud por todas mis heridas de combate? Bueno, supongo que no puedo prescindir de una compensación monetaria.");
			Link.l1 = "Está bien, he cambiado de opinión. Puedes quedarte, pero volveremos a hablar de esto.";
			Link.l1.go = "exit_bad";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Oh, no te preocupes por eso. Aquí, "+sti(NPChar.rank)*500+" pesos. Eso compensará tu tiempo en mi barco.";
				Link.l2.go = "Get_out_А3_ForMoney";
				Link.l3 = "Te daré el dinero. Aún así, te equipaste bien gracias a mí, y supongo que es apropiado devolverme las cosas.";
				Link.l3.go = "Return_items_A3";
			}
			Link.l4 = "¿Oh, de veras? ¿Y qué hay de tu parte, la cual has estado recibiendo regularmente?! Sabía que todo terminaría en quejas y suplicando por una prima.";
			Link.l4.go = "Get_out_A3_strife_1";
		break;

		case "Return_items_A3":
			dialog.text = "Sabía que dirías eso, pero solo recuperarás tu equipo cuando yo reciba "+sti(NPChar.rank)*1000+" pesos. ¡De lo contrario, solo puedes tenerlo sobre mi cadáver!";
			Link.l1 = "Está bien, toma tu dinero, entonces.";
			Link.l1.go = "Get_out_А3_chang";
			Link.l2 = "¿Estás loco o qué?! ¿Exigiendo tal suma por lo que se te había dado gratis?! Ahora veo que tu avaricia ha ganado claramente sobre tu fingida bondad.";
			Link.l2.go = "Get_out_A3_strife_1";
		break;

		case "Get_out_A3_strife_1":
			dialog.text = "¡No te atrevas a insultarme! Puede que no sea el mejor en la Marina, pero aún soy un oficial de combate. ¡Y seré respetado, incluso por un patán como tú!";
			Link.l1 = "Si aún no lo entiendes, lo repetiré una vez más: deja de mendigar, no obtendrás nada de mí.";
			Link.l1.go = "Get_out_А3_strife_death";
		break;

		case "Get_out_А3_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("bad");
			dialog.text = "¡Bueno, aún conseguiré una satisfacción!";
			Link.l1 = "Ah, entonces eso es un desafío, ¿no es así? Como desees entonces...";
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_A4":
			dialog.text = RandPhraseSimple(LinkRandPhrase("¡Esa es mi suerte! ¡Puse mi corazón y alma en el servicio solo para ser expulsado sin siquiera un beneficio de servicio!","¡Qué desgracia! Me contratan y luego me echan casi de inmediato. No tengo ni idea de a qué santo prenderle una vela estos días...","¡Rayos! Despedido por tercera vez este año, todos los lunes. Tal vez, no debería presentarme ante el capitán cuando tengo resaca."),LinkRandPhrase("Bueno, como desees. Ruega para que nunca nos encontremos de nuevo.","Como desees. Ten en cuenta, sin embargo, que nunca encontrarás un oficial mejor.","Está bien, capitán, como usted diga. Pero Dios sabe que había estado haciendo bien mi trabajo..."));
			Link.l1 = "Espera. Ahora no es el mejor momento para tu jubilación. Pero todas las reclamaciones se mantienen.";
			Link.l1.go = "exit_good";
			Link.l2 = RandPhraseSimple("Lárgate ahora. Y agradece a Dios que hoy estoy de buen humor.","Pierde el tiempo ahora. Eres tan buen oficial como la mierda es buena para hacer balas.");
			Link.l2.go = "exit_fire_4";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Espera. Te daré "+sti(NPChar.rank)*500+" pesos. No quiero que mueras en la cuneta, para que luego me sienta culpable de ello.";
				Link.l3.go = "Get_out_А4_ForMoney";
			}
			Link.l4 = "Espera... Te equipé bien, devuélveme mis cosas.";
			Link.l4.go = "Return_items_A4";
		break;

		case "Get_out_А4_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("¡Oh, gracias, capitán! Eso es realmente amable de tu parte...","Gracias por tu comprensión. Buena suerte.","Ahora hemos terminado. Buena suerte...");
			Link.l1 = "Buena suerte. Espero que no lo desperdicies todo en la primera taberna.";
			Link.l1.go = "exit_fire_4";
		break;

		case "Return_items_A4":
			if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
			{
				dialog.text = LinkRandPhrase("¡Y ahora te llevas mi equipo! ¡Oh, por Dios, al diablo con todo! Me iré a pescar, lo juro...","Veo que has decidido dejarme totalmente limpio. Oh, bueno. Ahora solo hay un camino para mí, al atrio...","¡Oh, muchas gracias! Ahora has decidido robarme. ¡Oh, qué destino tan cruel...! Tómalo entonces, ¡tómalo! ¿Qué puedo hacer de todos modos...?");
				Link.l1 = "Pierde el tiempo ahora. Eres tan buen oficial como la mierda es buena para hacer balas.";
				Link.l1.go = "Get_out_А4_chang_1";
			}
			else	
			{
				dialog.text = RandPhraseSimple("Como desees, capitán, pero primero sé tan amable de entregarme "+sti(NPChar.rank)*1000+" pesos, por favor. Que esto sea una compensación del daño moral.","Está bien. Pero aún quiero recibir "+sti(NPChar.rank)*1000+" pesos como compensación por mi duro y fiel servicio.");
				if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
				{
					Link.l1 = "¡Qué villano! Bueno, aquí está tu dinero.";
					Link.l1.go = "Get_out_А4_chang";
				}
				Link.l2 = "¡¿Estás loco?! ¿Te atreves a pedir tanto dinero después de todo lo que te di?";
				Link.l2.go = "Get_out_A4_strife";
				Link.l3 = "¡Ah-ha! ¡Estaba bromeando! No podría echar a un viejo amigo como si de una gorra llena de agujeros se tratara.";
				Link.l3.go = "exit_bad1";
			}
		break;

		case "Get_out_A4_strife":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "¡Bueno, entonces no obtendrás nada! ¡No daré un paso hasta que escuche el tintineo de mi dinero!";
			Link.l1 = RandPhraseSimple("¡Pronto escucharás el tintineo de mi espada!","¡Entonces serás llevado con los pies por delante!");
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_fight":
			CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
			LAi_CharacterDisableDialog(NPChar);
			LAi_SetWarriorType(Npchar);
			LAi_group_MoveCharacter(Npchar, "TmpEnemy");
			LAi_group_SetHearRadius("TmpEnemy", 100.0);
			LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			if (PChar.location == Get_My_Cabin() || findsubstr(PChar.location, "_tavern" , 0) != -1 || findsubstr(PChar.location, "_store" , 0) != -1)
            {
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff");
            }
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

	    case "Get_out_А1_chang": // интерфейс обмена
			Diag.TempNode = "Fired_1";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А2_chang": // интерфейс обмена
			Diag.TempNode = "Fired_2";
			LAi_CharacterDisableDialog(NPChar);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А3_chang": // интерфейс обмена
			Diag.TempNode = "Fired_3";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang_1": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

	    case "exit_bad":
			Npchar.loyality = makeint(Npchar.loyality) - 3;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_bad1":
			Npchar.loyality = makeint(Npchar.loyality) - 2;
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			Diag.CurrentNode = Diag.TempNode;			
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_good":
			Npchar.loyality = makeint(Npchar.loyality) - 1;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_1":	//navy -->			
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_1";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_2":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_2";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_3":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_3";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_4":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_4";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_5":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_1";
			OfficersReaction("good");
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "Fired_1":
			Diag.TempNode = "Fired_1";      
			dialog.text = "¿¡Qué ahora?! ¡Ya hemos hablado de todo! Nunca más pondré un pie en tu barco.";
			Link.l1 = RandPhraseSimple("Pírate ya. No es una gran pérdida, después de todo.","Está bien, vete, entonces. No te retendré.");	
			Link.l1.go = "Exit";
		break;

		case "Fired_2":
			Diag.TempNode = "Fired_2"; 
			dialog.text = "¿Algo más, capitán? Pensé que ya habíamos discutido todo...";
			Link.l1 = "No, nada. Solo quería decir adiós...";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_3":
			Diag.TempNode = "Fired_3"; 
			dialog.text = "Capitán, hemos discutido todo y expresado nuestras demandas. No vas a decir que has cambiado de opinión, ¿verdad?";
			Link.l1 = "Bien, vete, entonces. Después de todo, no es una gran pérdida.";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_4":
			Diag.TempNode = "Fired_4"; 
			dialog.text = "Capitán, ¿qué otras preguntas podrían haber? Sólo para decirte, estoy muy ofendido, y no tengo ningún deseo de volver...";
			Link.l1 = "Está bien, vete entonces. No es que te necesitara tanto.";	 
			Link.l1.go = "Exit";
		break;
		
		// boal 05.09.03 offecer need to go to abordage -->
	    case "Boal_Stay":
            //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
            //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
		    Diag.TempNode = "Hired";
		    dialog.text = "¡A la orden Capitán!";
		    Link.l1 = "A sus anchas.";
		    Link.l1.go = "Exit";
		    Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	    break;
		
	    case "Boal_Follow":
		    SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		    Diag.TempNode = "Hired";
		    dialog.text = "¡Aye-aye Capitán!";
		    Link.l1 = "A sus anchas.";
		    Link.l1.go = "Exit";
	    break;
        // boal 05.09.03 offecer need to go to abordage <--

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
            dialog.Text = "¡Capitán! ¡Sería un honor!";
            Link.l1 = "Mantén el orden y haz prosperar la ciudad, y yo iré navegando de vez en cuando para cobrar los aranceles.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "He cambiado de opinión.";
            Link.l2.go = "Exit";
            Diag.TempNode = "Hired";
        break;

        case "Exit_Gover_Hire":
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            attr = sld.id + "_townhall";

            // снимем пассажира -->
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			// снимем пассажира <--
		    sld.OfficerIdx = sti(NPChar.index);
			ChangeCharacterAddressGroup(NPChar, attr, "sit", "sit1");
			LAi_SetHuberTypeNoGroup(NPChar);
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
            LAi_LoginInCaptureTown(NPChar, true);
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecordInfo("Gen_CityCapture", "t3_1");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Main":
            iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
            if (iTemp > 0)
            {
				dialog.Text = "¿Cuáles son tus órdenes? La última vez que me visitaste "+FindRussianDaysString(iTemp)+" hace.";
			}
			else
			{
			    dialog.Text = "¿Cuáles son tus órdenes?";
			}

            Link.l1 = "¿Cuánto dinero de impuestos tienes "+NPCharSexPhrase(NPChar,"recolectado","recolectado")+"¿en este punto?";
        	Link.l1.go = "Gover_Tax";
            Link.l8 = "Se te necesita en el barco, te relevo del deber en la ciudad.";
            Link.l8.go = "Gover_Fire";
			Link.l9 = "Todo lo mejor.";
            Link.l9.go = "Exit";
            Diag.TempNode = "Gover_Main";
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
        break;

        case "Gover_Tax":
            iTemp = GetNpcQuestPastDayParam(NPChar, "StartTaxDate");
            iTax  = makeint((GetCharacterSkillSimple(NPChar, SKILL_COMMERCE) + GetCharacterSkillSimple(NPChar, SKILL_LEADERSHIP)) / 2);
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			if (CheckAttribute(sld, "FortValue"))
			{
			    iFortValue = sti(sld.FortValue);
			}
			else
			{
			    iFortValue = 20;
			}
			NPChar.Gover_Tax_Sum = iFortValue*iTax*iTemp;
			dialog.Text = "Mis habilidades permiten recolectar "+FindRussianMoneyString(iFortValue*iTax)+" Por día. Terminado "+FindRussianDaysString(iTemp)+" Yo "+NPCharSexPhrase(NPChar,"recogido","recolectado")+" "+FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum))+".";
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
			    Link.l1 = "Quiero llevarme todo el dinero recaudado en impuestos.";
            	Link.l1.go = "Gover_Tax_Get";
			}
			Link.l2 = "¡Gracias por el servicio!";
            Link.l2.go = "Exit";
        break;

        case "Gover_Tax_Get":
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "¡Genial! No soy un tierra firme, ya sabes.";
            Link.l8 = "Eso es bueno.";
            Link.l8.go = "exit_hire";
            Diag.TempNode = "Hired";
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            DeleteAttribute(sld, "OfficerIdx");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecordInfo("Gen_CityCapture", "t3_2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
        break;
        //////////////////////////////    офицер-наместник <--

		//Указания для компаньона 19.02.08 -->
		case "Companion_Tasks":
			dialog.Text = "Te estoy escuchando.";
			Link.l1 = "Esto es sobre abordaje.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Esto es acerca de tu barco.";
			Link.l2.go = "Companion_TaskChange";
			if(bBettaTestMode) // Только при бета-тесте
			{
			    Link.l3 = "Quiero que dejes mi escuadrón por un tiempo y busques fortuna por tu cuenta.";
			    Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Nada hasta ahora.";
			Link.l8.go = "exit";
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "Entonces, ¿cuál es tu deseo?";
			Link.l1 = "No abordes los barcos enemigos. Cuida de ti mismo y de la tripulación.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Quiero que abordes los barcos enemigos.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Entonces, ¿cuál es tu deseo?";
			Link.l1 = "Me gustaría que no cambies tu barco por otro después de abordar. Es demasiado valioso.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Cuando abordas barcos enemigos, puedes tomarlos para ti, si resultan ser decentes.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "¡Aye-aye Capitán!";
			Link.l1 = "A sus anchas.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Será hecho, Capitán.";
			Link.l1 = "A sus anchas.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "¡Ajá, Capitán!";
			Link.l1 = "A gusto.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Se hará, Capitán.";
			Link.l1 = "A sus anchas.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--
	
		// Самостоятельное плавание компаньона -->
		case "CompanionTravel":
			if(GetAttrValue(PChar, "CompanionTravel") == 3) // Если уже троих отпустил
			{
				dialog.Text = "Capitán, no abandonaré su escuadrón, porque ya ha despedido a tres barcos.";
					Link.l1 = "Sí, quizás, tienes razón.";
					Link.l1.go = "exit";
				break;
			}
		
			dialog.Text = "Sin problema, capi. ¿En qué ciudad nos encontraremos?";
			for(iTemp=0; iTemp<MAX_COLONIES; iTemp++)
			{
				sld = &colonies[iTemp];
				attr = sld.ID;
				if(sld.nation == "none" || sld.nation == PIRATE || attr == "Panama" || attr == "FortOrange") continue;
				attrLoc = "l" + iTemp;
				Link.(attrLoc) = "En la " + XI_ConvertString("Colony" + attr + "Dat");
				Link.(attrLoc).go = "CompanionTravelToColony_" + attr;
			}
				Link.l99 = "He cambiado de opinión.";
				Link.l99.go = "exit";
		break;
			
		case "CompanionTravel_EnemyColony":
			dialog.Text = "Capitán, pero no puedo esperarte en la colonia, ¡que es hostil para nosotros!";
				Link.l1 = "Sabes, olvídate de todos estos viajes...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoCrew":
			dialog.Text = "¡Capitán, casi no tenemos marineros en la tripulación! ¿De qué viaje estás hablando?!";
				Link.l1 = "Eso es correcto, realmente nos faltan marineros...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoFood":
			dialog.Text = "Capitán, no tengo suficientes provisiones a bordo para un viaje así.";
				Link.l1 = "Sí, tienes razón. El viaje puede esperar...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoHP":
			dialog.Text = "Capitán, pero mi barco está en mal estado. ¡Sería imprudente para mí zarpar solo bajo tales circunstancias!";
				Link.l1 = "Sí, tienes razón. Tu barco necesita reparación.";
				Link.l1.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart":
			dialog.Text = "Ya veo. Hasta "+XI_ConvertString("Colony"+characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID+"Gen")+" ir "+sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days)+" días, ¿qué hago al llegar?";
				Link.l1 = "Atraca en el puerto de la colonia durante un mes.";
				Link.l1.go = "CompanionTravel_PrepareStart_2";
				Link.l2 = "Sabes, he cruzado mi mente. Quédate conmigo...";
				Link.l2.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart_2":
			dialog.Text = "Entiendo, capitán. Partiré de inmediato.";
				Link.l1 = "Sí, por favor hazlo.";
				Link.l1.go = "CompanionTravel_Start";
		break;
			
		case "CompanionTravel_Start":
			Diag.CurrentNode = "CompanionTravel_LastNode";
			NPChar.quest.meeting = true;
			CompanionTravel_SetTraveller(NPChar);
			DialogExit();
		break;
			
		case "CompanionTravel_LastNode":
			Dialog.text = RandPhraseSimple("Hoy, zarparé de nuevo...",
			"No olvides nuestra reunión en "+XI_ConvertString("Colony"+characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID+"Dat")+".");
				link.l2 = "...";
				link.l2.go = "Exit";
				Diag.TempNode = "CompanionTravel_LastNode";
		break;
			
		case "CompanionTravel_ToSquadron":
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				dialog.text = "Yo también lo desearía. A partir de ahora, mi barco vuelve a estar bajo tu mando, cap.";
					Link.l1 = "Bien.";
					Link.l1.go = "exit";
					Diag.TempNode = "hired";
					CompanionTravel_DeleteSpecialShipAttributes(NPChar);
					Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID); // Потрем группу
					SetCompanionIndex(PChar, -1, sti(NPChar.index));
					PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
					DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				dialog.text = "Capitán, ya tienes cinco barcos en tu escuadrón, ¿qué vas a hacer con el sexto? Bueno, creo que preferiría esperarte aquí en mi barco. Tus nuevos compañeros no me parecen confiables. Sus barcos se hundirán pronto y volverás a buscarme.";
					Link.l1 = "Oye, ¿no eres inteligente? ¡Deberías ser un almirante, no solo un capitán!";
					Link.l1.go = "exit";
					Diag.TempNode = "CompanionTravel_ToSquadron_2";
					NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2"; // ставим снова эту ноду
			}
		break;
			
		case "CompanionTravel_ToSquadron_2":
			dialog.text = "Oh, capitán, has vuelto, tal como dije. Entonces, ¿hay ahora un lugar vacante en tu escuadrón?";
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				Link.l1 = "Sí, "+NPChar.name+", hay uno. Bienvenido al escuadrón.";
				Link.l1.go = "exit";
				Diag.TempNode = "hired";
				CompanionTravel_DeleteSpecialShipAttributes(NPChar);
				Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID);
				SetCompanionIndex(PChar, -1, sti(NPChar.index));
				PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
				DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				Link.l1 = "Aún no, desafortunadamente.";
				Link.l1.go = "exit";
				Diag.TempNode = "CompanionTravel_ToSquadron_2";
				NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2";
			}
		break;
		// <-- Самостоятельное плавание компаньона
		
		case "tonzag_after_boarding":
			dialog.text = "¡Capitán, las cosas están de la mierda! El enemigo nos tiene en un apretón firme, me temo que no soltarán hasta que estemos muertos! Nuestra gente está en verdaderos problemas ahora, ¡y la mayoría de las tripulaciones de los cañones están fuera de combate!";
			link.l1 = "Les ayudaré. ¡Toma el mando y sácanos de aquí!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "¡Sí, señor!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "¡Victoria, Capitán! El grupo de desembarco ha sido destruido, el enemigo eligió retirarse y se dirigió al sur. El estado del barco es aceptable. Tripulación viva: "+GetCrewQuantity(pchar)+" gente. ¡Informe completado!";
			link.l1 = "¡Gracias! ¡Ron para todos y fortalecer la vigilancia hasta que lleguemos al puerto!";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "¡Hurra! ¡Sí sí!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_AlonsoBoardingDialog");
		break;
	}
}
