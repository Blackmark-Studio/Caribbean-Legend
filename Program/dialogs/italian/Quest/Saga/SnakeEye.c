// шаман команчей Змеиный Глаз
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "calendar")
			{
				dialog.text = "Saluti, mio smunto compare.";
				link.l2 = "Sono lieto di rivederti, fratello dalla pelle rossa. Ho di nuovo una faccenda importante da affidarti.";
				link.l2.go = "calendar";
				break;
			}
			dialog.text = "Saluti, mio amico pallido.";
			link.l1 = "Anch’io son lieto di vederti, Occhio di Serpente.";
			link.l1.go = "exit";
			if (CheckAttribute(npchar, "quest.amulet") && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Indian) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Amulet) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Obereg))
			{
				link.l2 = "Ti ho portato gli amuleti che volevi. Facciamo scambio.";
				link.l2.go = "SnakeEye_potion";
			}
			if (CheckAttribute(pchar, "questTemp.LSC")) // был в LSC
			{
				if (CheckAttribute(npchar, "quest.LSC_hello") && CheckCharacterItem(pchar, "buben"))
				{
					link.l2 = "Ho trovato il tuo tamburello, Occhio di Serpente. Dai un’occhiata.";
					link.l2.go = "LSC_buben";
				}
				if (CheckAttribute(npchar, "quest.LSC_tube") && CheckCharacterItem(pchar, "smoking_tube"))
				{
					link.l2 = "Ho trovato una pipa indiana interessante, Occhio di Serpente. Dai un'occhiata.";
					link.l2.go = "LSC_tube";
				}
				if (!CheckAttribute(npchar, "quest.LSC_hello"))
				{
					link.l2 = "Ciao, sciamano. Ho usato la statua e vissuto un viaggio incredibile. Avevi proprio ragione. Ho trovato il cimitero delle navi, il capitano bianco e persino la stiva con i rifornimenti!";
					link.l2.go = "LSC_hello";
				}
				if (CheckAttribute(npchar, "quest.LSC_hello") && pchar.questTemp.Saga.BaronReturn == "shamane")
				{
					link.l3 = "Occhio di Serpente, ho bisogno del tuo aiuto.";
					link.l3.go = "Saga_nathaniel";
				}
			}		
			NextDiag.TempNode = "First time";
		break;
		
	//---------------------------------------- первая встреча------------------------------------------------
		case "SnakeEye":
			dialog.text = "Salute, mio amico pallido.";
			link.l1 = "Salve, sciamano. E perché mai pensi che io sia tuo compare?";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "So molto, ma non sempre so esattamente cosa. Sei venuto qui con uno scopo. Il destino ti ha condotto fin qui e io ti do una mano.";
			link.l1 = "Bene a sapersi! In effetti sono qui per il tuo aiuto, amico dalla pelle rossa. Te lo dico senza giri di parole: che volevi dire quando hai parlato a moglie di Hawk di Kukulcan?";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "Anche i pesci morti vanno dove li porta la corrente. E l’uomo vivo, la sorte lo trascina da un destino all’altro. La meta del capitano incatenato, braccato da canaglie nella selva, era la statua di Kukulcan. Se si fosse sacrificato, sarebbe potuto fuggire lontano da qui.";
			link.l1 = "Non ho capito un accidente. Che storia è questa con la statua del vostro dio, e come diavolo ha fatto Hawk ad allontanarsi così a piedi che nessuno riesce a trovarlo ancora adesso?";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "Se Kukulcan ha inghiottito Hawk, allora potrebbe sputarlo fuori ovunque. Forse persino in un altro mondo. Kukulcan mi ha mangiato tre volte. E ogni volta mi sono ritrovato in posti diversi. Tanto tempo fa sono arrivato qui e ho deciso di non rischiare più. Non sono più entrato nella bocca di Kukulcan e non so dove sputa le sue vittime.";
			link.l1 = "Dio santo, questa roba supera ogni mia comprensione! Vuoi dirmi che quell’idolo di pietra può far sparire la gente e mandarli lontano?";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "Non solo questo. Kukulcan non domina soltanto lo spazio, ma anche il tempo. O forse persino di più. Raccontai al capitano incatenato della statua d’oro che divora gli uomini. Forse ha deciso di rischiare quando ha visto che gli inseguitori erano ormai alle calcagna...";
			link.l1 = "Aspetta, la statua è di pietra. E tu parli di una d’oro...";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "A mezzanotte l'idolo prende vita e si trasforma in oro. In quell'istante, lo spirito di Kukulcan lo anima. Temi d'avvicinarti, o potresti veder l'alba in un altro luogo. Persino le stelle mutano posizione nel cielo. Incontrerai chi non è ancora nato, o vedrai la nascita di chi è morto da secoli o deve ancora venire al mondo.";
			link.l1 = "Che diavolo... sempre enigmi e indovinelli... Tu mi incuriosisci, Occhio di Serpente. Hai detto d’aver affrontato tre incontri con Kukulcan, il dio in cui credi. E allora perché non dovrei tentare la sorte anch’io con l’idolo di un dio in cui non credo?";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "Peccato. Peccato che tu non creda. Forse è stato Kukulcan in persona a chiamarti, a farti lasciare la terra dei tuoi avi. Ma ancora non riesci a sentirlo. Ogni cosa avviene per un motivo. Se deciderai di rischiare, sappi che sono sopravvissuto ogni volta soltanto grazie alle portentose pozioni comanche.";
			link.l1 = "Comanche? È un’altra ciurma d’indiani, che diavolo?";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "Così chiamano i miei gente i cani nemici che mai più rivedrò. Questa pozione ridà vigore e forza, ti guarisce e salva anche dai peggiori veleni. Te ne servirebbero parecchie bottiglie, ma a me ne sono rimaste solo tre.\nErano quattro, ma una l’ho persa in un luogo strano, sembrava un cimitero di navi dei bianchi. È lì che la mia camminata in questo mondo è iniziata. Forse Kukulcan ha sputato il capitano proprio là. Se è vero, non gli invidio la sorte.";
			link.l1 = "Che razza di posto è questo? Un cimitero di navi?";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "Luogo strano... Non dovrebbe esistere, eppure esiste. Lì vivono uomini che uccidono solo per il colore della pelle. Tengono le provviste dentro una grande nave, proprio dove Kukulcan mi ha sputato fuori. Non sono entrato nella stiva che difendono dagli sciacalli, non sono gente che si fida. Se arrivi laggiù – cerca un’altra via d’uscita, non entrare nella stiva o ti metterai nei guai.\nIl Ragazzo Bianco può aiutarti a trovare un’altra statua, se ancora respira. Dagli questa perla bianca. Gli piacciono, quelle dannate perle.";
			link.l1 = "Hm. Mi gira già la testa e la faccenda si fa sempre più intrigante. Continua, fratello dalla pelle rossa.";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			Log_Info("You have received a white pearl");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "jewelry52");
			dialog.text = "Se trovi il capitano vivo, potrebbe essere malato fradicio. Non ho avuto tempo di dargli la pozione. Cerca il mio tamburello laggiù. Era di mio nonno, quel tamburello. Ho perso un sacco di roba nella borsa, ma solo il tamburello mi serve. Senza di quello, parlare coi spiriti è una vera impresa.";
			link.l1 = "Beh, questo posto sembra davvero intrigante! Speriamo che Hawk sia stato teletrasportato lì... Mi darai la tua pozione?";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "Te lo darò. Ma tu mi darai in cambio tre amuleti locali: "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian)+", "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet)+" e "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg)+"   Una fiaschetta per ogni amuleto, così è giusto. Torna quando avrai raccolto tutti gli amuleti. Allora li scambieremo. Non pensare che io sia un cane avaro... O forse ci ripenserai tu stesso, mentre vai a caccia degli amuleti.";
			link.l1 = "Non lo penserò mai. Aspettami, Occhio di Serpente, torno presto.";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			npchar.quest.amulet = "true";
			AddQuestRecord("BaronReturn", "3");
			AddQuestUserData("BaronReturn", "sItem1", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian));
			AddQuestUserData("BaronReturn", "sItem2", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet));
			AddQuestUserData("BaronReturn", "sItem3", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg));
			sld = characterFromId("Danielle");
			sld.quest.talk = "SnakeEye";
			pchar.quest.BaronReturn_out.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BaronReturn_out.win_condition.l1.location = pchar.location;
			pchar.quest.BaronReturn_out.function = "Saga_DannyTalk";
			pchar.questTemp.HelenDrinking.GiveAmulets = true;
			
			//if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap4_Start"))
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))	// Временно так
			{
				// Квест "Путеводная звезда", начало 4 этапа
				PChar.quest.PZ_Etap4_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap4_Start.win_condition.l1.location = "Shore9";
				PChar.quest.PZ_Etap4_Start.win_condition = "PZ_Etap4_Start";
				locations[FindLocation("Shore9")].DisableEncounters = true;
			}
		break;
		
		// даёт зелья - идем на телепортацию
		case "SnakeEye_potion":
			dialog.text = "Bene, amico mio. Mi hai portato gli amuleti così puoi andare da Kukulcan?";
			link.l1 = "Sì. Sono pronto a seguire lo stesso viaggio che fece Nathaniel, il capitano incatenato.";
			link.l1.go = "SnakeEye_potion_1";
		break;
		
		case "SnakeEye_potion_1":
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Indian, 1);
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Amulet, 1);
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Obereg, 1);
			TakeNItems(pchar, "Ultimate_potion", 3);
			Log_Info("You have given amulets");
			Log_Info("You have received three versatile potions");
			PlaySound("interface\important_item.wav");
			dialog.text = "Prendi queste pozioni. Ricorda che devi berne una subito dopo che Kukulcan ti ha sputato fuori, altrimenti schiatti o resti maledettamente malato. E bada bene, non ficcare il naso nella stiva dove i musi pallidi tengono la loro roba. C'è un altro modo per lasciare la nave. Anzi, due modi. Trova la donna rossa la prima notte, è cosa di massima importanza. Questo è tutto ciò che posso dirti.";
			link.l1 = "Me lo ricorderò, fratello dalla pelle rossa.";
			link.l1.go = "SnakeEye_potion_2";
		break;
		
		case "SnakeEye_potion_2":
			dialog.text = "Allora vai. Tocca Kukulcan a mezzanotte e ti divorerà. Chiamerò gli spiriti perché ti guidino.";
			link.l1 = "Grazie, Occhio di Serpente. Non ti preoccupare per me, andrà tutto a gonfie vele. Ci rivedremo!";
			link.l1.go = "SnakeEye_potion_3";
		break;
		
		case "SnakeEye_potion_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Saga.BaronReturn = "first_teleport";
			pchar.questTemp.Dolly = true; // телепорты работают!
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", true); // не пускать офицеров в локу телепорта
			DeleteAttribute(npchar, "quest.amulet");
			AddQuestRecord("BaronReturn", "4");
			sld = characterFromId("Danielle");
			sld.quest.talk = "teleport";
			pchar.quest.BaronReturn_out1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BaronReturn_out1.win_condition.l1.location = pchar.location;
			pchar.quest.BaronReturn_out1.function = "Saga_DannyTalk";
			QuestPointerToLoc("Pearl_Jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("Pearl_Jungle_03", "camera", "dolly");
		break;
		
		// пришёл из LSC
		case "LSC_hello":
			dialog.text = "Son lieto di rivederti, compare. Come diavolo sei scampato al cimitero delle navi?";
			link.l1 = "Ho trovato la statua di Kukulcan proprio dove mi avevi detto. Il Ragazzo Bianco mi ha dato una mano – Ole Christiansen. La statua era sprofondata in mare, ma sono riuscito a recuperarla. Mi ha trasportato in un villaggio indiano su Dominica.";
			link.l1.go = "LSC_hello_1";
			npchar.quest.LSC_hello = "true";
		break;
		
		case "LSC_hello_1":
			dialog.text = "Monkitekuvri ti ha incontrato là?";
			link.l1 = "Hm. Monkitekuvri? Chi diavolo sarebbe costui?";
			link.l1.go = "LSC_hello_2";
		break;
		
		case "LSC_hello_2":
			dialog.text = "È il capo del villaggio.";
			link.l1 = "Non gli ho chiesto il nome. Forse era Monkitekuvri, o forse no.";
			link.l1.go = "LSC_hello_3";
		break;
		
		case "LSC_hello_3":
			dialog.text = "Aveva forse un pomposo copricapo di piume d’uccello sulla testa?";
			link.l1 = "Certo che sì. Una marea di piume... Pare abbia spennato tutti i pappagalli della giungla.";
			link.l1.go = "LSC_hello_4";
		break;
		
		case "LSC_hello_4":
			dialog.text = "Si chiama Monkitekuvri. Non sono piume di pappagallo, ma piume d’aquila. Questo copricapo è il mio copricapo. L’ho donato a Monkitekuvri quando Kukulcan mi ha risputato fuori. Poi mi hanno portato davanti a un’altra statua...";
			link.l1 = "Non è incredibile! Pure me hanno 'sacrificato' a Kukulcan! E mi son ritrovato qui, accanto alla prima statua.";
			link.l1.go = "LSC_hello_5";
		break;
		
		case "LSC_hello_5":
			dialog.text = "Sì, amico mio pallido. Anche il mio viaggio si è concluso qui.";
			link.l1 = "Le statuette ci trasportano in cerchio... Ma che senso ha tutto ciò? Hai qualche idea, Occhio di Serpente?";
			link.l1.go = "LSC_hello_6";
		break;
		
		case "LSC_hello_6":
			dialog.text = "Suppongo che le statue non funzionino come si deve. Per ora spostano la gente qua e là, ma dovrebbero portarli tutte in un posto solo. C’è qualcosa che non va in quelle maledette statue.";
			link.l1 = "Perché mai ti è venuto in mente tutto ciò?";
			link.l1.go = "LSC_hello_7";
		break;
		
		case "LSC_hello_7":
			dialog.text = "Perché teletrasportarsi in cerchio non ha senso. Kukulcan deve radunare tutte le vittime in un solo luogo, non spostarle di qua e di là.";
			link.l1 = "E dove potrebbe mai essere, quel posto?";
			link.l1.go = "LSC_hello_8";
		break;
		
		case "LSC_hello_8":
			dialog.text = "Questo è un gran segreto, fratello bianco, persino per me.";
			link.l1 = "Capisco. Va bene, al diavolo gli idoli. Non mi avvicinerò mai più a loro. Ho trovato il capitano incatenato, non c’è più bisogno di scorrazzare tra quei portali.";
			link.l1.go = "LSC_hello_9";
			AddQuestRecord("BaronReturn", "12");
		break;
		
		case "LSC_hello_9":
			dialog.text = "Quando sei stato al cimitero delle navi. Hai trovato lì il mio tamburello?";
			if (CheckCharacterItem(pchar, "buben"))
			{
				link.l1 = "Penso di sì. Dai un'occhiata.";
				link.l1.go = "LSC_buben";
			}
			else
			{
				link.l1 = "No. Purtroppo non l'ho trovato. Ma so dove si trova l'isola e posso arrivarci. Cercherò il tuo tamburello.";
				link.l1.go = "LSC_hello_10";
			}
		break;
		
		case "LSC_hello_10":
			dialog.text = "Cercalo, amico pallido. Te ne prego davvero. Senza il mio tamburello non sento bene gli spiriti.";
			link.l1 = "D'accordo, Occhio di Serpente. A presto!";
			link.l1.go = "exit";
		break;
		
		case "LSC_buben":
			RemoveItems(pchar, "buben", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Questo è il mio tamburello. Grazie, amico pallido. Posso ripagarti. Ti dono quest’arma, che la tua gente non vedrà ancora per molto tempo. Quest’arma è delle facce pallide della mia epoca.";
			link.l1 = "Interessante! Fammi vedere, amico dalla pelle rossa...";
			link.l1.go = "LSC_buben_1";
		break;
		
		case "LSC_buben_1":
			GiveItem2Character(pchar, "pistol7");
			Log_Info("You have received a Colt revolver");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 3);
			dialog.text = "Prendilo. Ci sono solo tre cariche rimaste, il resto le ho già usate. Ma magari imparerai a fabbricare la polvere tu stesso. Ho perso diverse decine di pezzi per le cariche al cimitero delle navi, lì potresti trovarli.";
			link.l1 = "Oho! Questa sì che è una pistola! Non ne ho mai vista una simile... che strano congegno! Un tamburo che gira... cinque colpi! Roba pregiata!";
			link.l1.go = "LSC_buben_2";
		break;
		
		case "LSC_buben_2":
			dialog.text = "Si chiama revolver Colt. Non troverai un altro arnese simile a questo ai tuoi tempi. Facile da usare: alzi il cane e tiri il grilletto. Spara che è una meraviglia.";
			link.l1 = "Grazie! Grazie, Occhio di Serpente! Sarà una bella sorpresa per i miei nemici... Peccato che ci siano solo tre colpi...";
			link.l1.go = "LSC_buben_3";
		break;
		
		case "LSC_buben_3":
			dialog.text = "Prova a imparare da solo come preparare le cariche per la Colt. Allora sì che sarai un vero guerriero del tuo tempo. Ah, fratellino dal viso di latte, quasi dimenticavo: cercami la pipa al cimitero delle navi. Era una pipa davvero graziosa.";
			if (CheckCharacterItem(pchar, "smoking_tube"))
			{
				link.l1 = "Ah! E mi chiedevo a chi potesse appartenere questa pipa dipinta? Dai un'occhiata.";
				link.l1.go = "LSC_tube";
			}
			else
			{
				link.l1 = "Va bene. Cercherò anche la tua pipa. A presto!";
				link.l1.go = "exit";
			}
			npchar.quest.LSC_tube = "true";
		break;
		
		case "LSC_tube":
			RemoveItems(pchar, "smoking_tube", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Questa è la mia pipa, fratello mio. Sono lieto che tu l’abbia trovata. E posso darti un altro regalo in cambio. Questo è un libro astuto degli uomini pallidi dei miei tempi. Io non riesco a capirlo. Prova a trovare un uomo saggio che sappia leggere e comprendere questo libro.";
			link.l1 = "Grazie, Occhio di Serpente. Credo di conoscere qualcuno che potrebbe essere interessato a questa faccenda.";
			link.l1.go = "LSC_tube_1";
		break;
		
		case "LSC_tube_1":
			GiveItem2Character(pchar, "chemistry");
			Log_Info("You have received a Lavoisier's chemistry textbook");
			PlaySound("interface\important_item.wav");
			dialog.text = "Daglielo, fratello bianco. Questo libro contiene grandi segreti della saggezza dei visi pallidi.";
			link.l1 = "Bene. Ci si vede, Occhio di Serpente!";
			link.l1.go = "exit";
		break;
		
		// лечение Натаниэля
		case "Saga_nathaniel":
			dialog.text = "Ascolto, fratello dalla faccia di cera.";
			link.l1 = "Ho portato con me il capitano incatenato che cercavo al cimitero delle navi. Sta molto male. So che solo tu puoi salvarlo...";
			link.l1.go = "Saga_nathaniel_1";
		break;
		
		case "Saga_nathaniel_1":
			dialog.text = "Kukulcan ha divorato la sua salute. Credo di poterlo aiutare a guarire. Ma ci vorrà almeno una luna piena intera. Kukulcan ha mangiato il capitano tempo fa, e il male gli è penetrato fino alle ossa.";
			link.l1 = "Ti prego, guaritore, salvalo! Ti porterò tutto ciò che chiederai!";
			link.l1.go = "Saga_nathaniel_2";
		break;
		
		case "Saga_nathaniel_2":
			dialog.text = "Ci proverò, fratello bianco. Non devi portarmi nulla, ho già tutto. Il tempo rafforza la malattia, ma un capitano incatenato tornerà in salute tra una luna.";
			link.l1 = "Grazie, fratello dalla pelle rossa. Mi hai salvato la vita ancora una volta.";
			link.l1.go = "Saga_nathaniel_3";
		break;
		
		case "Saga_nathaniel_3":
			dialog.text = "Lascia il capitano incatenato nella mia capanna, fratello bianco, e cammina senza timore. Porta anche sua moglie, nessuno vedrà i miei riti.";
			link.l1 = "Va bene, Occhio di Serpente. Porterò Danielle con me. Ci si vede!";
			link.l1.go = "Saga_nathaniel_4";
		break;
		
		case "Saga_nathaniel_4":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "treatment";
			sld = characterFromId("Nathaniel");
			RemovePassenger(Pchar, sld);
			LAi_SetStayType(sld);
			sld.location = "none";
			pchar.quest.Saga_NatanTreatment1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Saga_NatanTreatment1.win_condition.l1.location = pchar.location;
			pchar.quest.Saga_NatanTreatment1.function = "Saga_NatanTreatment";
		break;
		
		case "calendar":
			dialog.text = "Ascolto, amico mio.";
			link.l1 = "Ricordi la nostra chiacchierata sulle statue di Kukulcan? Dicesti che 'dovrebbero condurre la gente in un luogo speciale'.";
			link.l1.go = "calendar_1";
		break;
		
		case "calendar_1":
			dialog.text = "Ricordo, capitano bianco.";
			link.l1 = "So dove quelle statue hanno portato la gente che Kukulcan ha divorato.";
			link.l1.go = "calendar_2";
		break;
		
		case "calendar_2":
			dialog.text = "Dove?";
			link.l1 = "Alla vecchia città Maya di Tayasal. Si trova nel cuore della giungla di Main.";
			link.l1.go = "calendar_3";
		break;
		
		case "calendar_3":
			dialog.text = "Molto interessante. Come ne sei venuto a conoscenza?";
			link.l1 = "È una lunga storia, Occhio di Serpente. Capisco anche come sei finito qui. Non sei nemmeno ancora nato, vero?";
			link.l1.go = "calendar_4";
		break;
		
		case "calendar_4":
			dialog.text = "Nemmeno mio padre è nato nel tuo tempo. Ma io vivo nel tuo tempo, ed è questa la grande meraviglia.";
			link.l1 = "In realtà una spiegazione c'è. Un sacerdote Itza di nome Kanek, che vive a Tayasal, ha invocato Kukulcan affinché nascesse come mortale in questo mondo per apprendere la saggezza della razza bianca. Inoltre ha creato una falla nel tempo che ha fatto piombare qui alcuni uomini dal futuro...";
			link.l1.go = "calendar_5";
		break;
		
		case "calendar_5":
			dialog.text = "Lasciar che Kukulcan assorba la saggezza dei popoli futuri?";
			link.l1 = "Sì. E Kukulcan intende tornare nel passato per portare la conoscenza al popolo Maya scomparso secoli fa. La storia cambierà e i Maya domineranno l’America, forse anche oltre...";
			link.l1.go = "calendar_6";
		break;
		
		case "calendar_6":
			dialog.text = "";
			link.l1 = "Ma qualcosa è andato storto coi portali, e ora trasportano la gente in tondo invece che a Tayasal. Ecco perché son qui: ho bisogno del tuo consiglio, Occhio di Serpente.";
			link.l1.go = "calendar_7";
		break;
		
		case "calendar_7":
			dialog.text = "Perché proprio io, capitano bianco?";
			link.l1 = "Perché sei stato divorato da Kukulcan. E perché la statua di Kukulcan vicino al tuo villaggio reca un simbolo strano su questa mappa, che è strettamente legato ai riti di Kanek.";
			link.l1.go = "calendar_8";
		break;
		
		case "calendar_8":
			dialog.text = "Fammi vedere questa mappa?";
			link.l1 = "Ecco, dai un’occhiata...";
			link.l1.go = "calendar_9";
		break;
		
		case "calendar_9":
			RemoveItems(pchar, "skinmap", 1);
			dialog.text = "(guardando) Questo segno rotondo, sì? E che vuol dire?";
			link.l1 = "Non lo so, sciamano. So soltanto che solo una delle tre statue di Kukulcan porta questo segno. E quella con il segno è la tua. Ne deduco che la tua statua è particolare. Hai qualche idea?";
			link.l1.go = "calendar_10";
		break;
		
		case "calendar_10":
			dialog.text = "Dammi tempo fino a domattina, fratello bianco. Lasciami questa mappa di cuoio. Devo consultare gli spiriti. Torna domani.";
			link.l1 = "Va bene, fratello dalla pelle rossa. Sarò qui domani. Ti ringrazio per l’aiuto.";
			link.l1.go = "calendar_11";
		break;
		
		case "calendar_11":
			DialogExit();
			SetFunctionTimerCondition("Tieyasal_CalendarThink", 0, 0, 1, false);
			pchar.questTemp.Tieyasal = "calendar_think";
			NextDiag.CurrentNode = "calendar_wait";
		break;
		
		case "calendar_wait":
			dialog.text = "Vieni più tardi, fratello bianco. Ora non mi scocciare.";
			link.l1 = "Certo, sciamano...";
			link.l1.go = "exit";
			NextDiag.TempNode = "calendar_wait";
		break;
		
		case "calendar_12":
			dialog.text = "Ho qualcosa da dirti, fratello bianco.";
			link.l1 = "Hai trovato qualcosa? Oppure hai qualche idea, magari?";
			link.l1.go = "calendar_13";
		break;
		
		case "calendar_13":
			dialog.text = "Gli spiriti degli antenati mi hanno donato una visione e sono andato da Kukulcan con la mappa. Ho cercato e ho trovato. Deve essere ciò che cerchi, fratello bianco.";
			link.l1 = "Che cosa hai scoperto?";
			link.l1.go = "calendar_14";
		break;
		
		case "calendar_14":
			dialog.text = "La statua di Kukulcan ha due morsetti di ferro e un incavo. L’incavo è rotondo, liscio. Sembra fatto apposta per quell’oggetto tondo e piatto che hai sulla tua mappa di cuoio.";
			link.l1 = "Che c’è?";
			link.l1.go = "calendar_15";
		break;
		
		case "calendar_15":
			dialog.text = "Non lo so. So solo che è rotondo, piatto, grande come una piccola zucca e spesso forse quanto un dito. Puoi andare a vedere tu stesso la rientranza e i ganci. Il gancio deve tenerlo fermo.";
			link.l1 = "Hai qualche idea? O almeno una vaga intuizione su cosa possa trattarsi?";
			link.l1.go = "calendar_16";
		break;
		
		case "calendar_16":
			dialog.text = "La pietra porta il segno del fuoco. So che fine ha fatto. Il cielo in fiamme l’ha colpita.";
			link.l1 = "Fulmine? È stato colpito da un fulmine?";
			link.l1.go = "calendar_17";
		break;
		
		case "calendar_17":
			dialog.text = "Ne sono certo. Ho chiesto a Miskito di questa statuetta. Un guerriero mi disse che molto tempo fa si vedevano poche cose belle e dipinte presso la statua. Somigliavano molto a delle pietre. Mi raccontò che erano pietre rosse, davvero belle. Un uomo bianco dal villaggio dei bianchi le comprò.";
			link.l1 = "Hmm. Da quel che capisco, pare che un fulmine abbia colpito questa cosa rotonda, l’abbia fatta a pezzi e poi quei pezzi siano stati venduti a qualche bianco, giusto?";
			link.l1.go = "calendar_18";
		break;
		
		case "calendar_18":
			dialog.text = "Par proprio di sì.";
			link.l1 = "E chi era quell’uomo bianco? Il tuo guerriero te l’ha detto?";
			link.l1.go = "calendar_19";
		break;
		
		case "calendar_19":
			dialog.text = "Me lo ha detto lui. Era gran compare dei Miskito e vive nel villaggio di Blueweld. Si fa chiamare Diavolo della Foresta. Lo conosco bene, dovresti conoscerlo anche tu.";
			link.l1 = "Jan Svenson? Aspetta un attimo... rocce dipinte di rosso, dici? Pare proprio che la fortuna oggi mi sorrida. Guarda qui, sciamano, guarda queste pietre rosse che ho! Il Diavolo della Foresta me le ha donate.";
			link.l1.go = "calendar_20";
		break;
		
		case "calendar_20":
			Log_Info("You have given ornamental pattern fragments");
			RemoveItems(pchar, "splinter_js", 1);
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			dialog.text = "Dev'essere loro. Cinque scogli. Guarda un po', fratello bianco. Se li metti così... (sistemando)";
			link.l1 = "...";
			link.l1.go = "calendar_21";
		break;
		
		case "calendar_21":
			dialog.text = "... allora abbiamo l’oggetto rotondo. Guarda! Si incastrano. Prima era un’unica cosa.";
			link.l1 = "Maledizione! E queste cose stavano in tasca mia da chissà quanto... Senti, stregone, se infilo i frammenti nell’incavo...";
			link.l1.go = "calendar_22";
		break;
		
		case "calendar_22":
			dialog.text = "Kukulcan sputerà fuori la vittima nella vecchia città degli indiani, come hai detto.";
			link.l1 = "Sarebbe magnifico! Devo proprio arrivarci! Dici che l’ornamento funzionerà, anche se è stato ridotto in frantumi?";
			link.l1.go = "calendar_23";
		break;
		
		case "calendar_23":
			dialog.text = "Penso che dobbiamo radunarli e poi mettere l’ornamento nell’incavo.";
			link.l1 = "Riunirli? Ma come diamine li mettiamo di nuovo assieme?";
			link.l1.go = "calendar_24";
		break;
		
		case "calendar_24":
			dialog.text = "Lascialo a me e agli spiriti degli antenati, fratello bianco. Non sono semplici pietre. È un oggetto miracoloso. Torna tra tre notti, fratello bianco. Chiamerò gli spiriti, la saggezza e l'arte dei vivi, e tenterò d'unire i frammenti.";
			link.l1 = "Incredibile... Come potrò mai sdebitarmi con te, Occhio di Serpente?";
			link.l1.go = "calendar_25";
		break;
		
		case "calendar_25":
			dialog.text = "Ringraziami dopo, fratello bianco. Ora va’. Torna fra tre notti.";
			link.l1 = "Bene. Spero che tu riesca...";
			link.l1.go = "calendar_26";
		break;
		
		case "calendar_26":
			DialogExit();
			SetFunctionTimerCondition("Tieyasal_CalendarDone", 0, 0, 3, false);
			NextDiag.CurrentNode = "calendar_wait";
		break;
		
		case "calendar_28":
			dialog.text = "Posso renderti felice, fratello bianco.";
			link.l1 = "Sei riuscito a riunire i frammenti?";
			link.l1.go = "calendar_29";
		break;
		
		case "calendar_29":
			dialog.text = "Sì. Non è stata cosa facile, e il calendario porta ancora i suoi segni, ma ora è fatta.";
			link.l1 = "Calendario? Perché l’hai chiamato così?";
			link.l1.go = "calendar_30";
		break;
		
		case "calendar_30":
			dialog.text = "Perché questa cosa rotonda è un calendario. L’ho studiata con attenzione. Serve a contare il tempo. Gli indiani della città antica contano le notti, le lune, gli anni e persino le ere.";
			link.l1 = "Incredibile... Anche se, ripensando a ciò che sono capaci di fare i sacerdoti Maya, la creazione di questo calendario non pare poi nulla di straordinario.";
			link.l1.go = "calendar_31";
		break;
		
		case "calendar_31":
			GiveItem2Character(pchar, "calendar_maya");
			sld = ItemsFromID("calendar_maya");
			sld.shown = "0";
			Log_Info("You have received a Maya calendar");
			dialog.text = "Prendilo, capitano bianco. Mettilo nell’incavo della statua. Forse allora ti sputerà fuori nella città degli indiani.";
			link.l1 = "Come posso sdebitarmi con te, Occhio di Serpente?";
			link.l1.go = "calendar_32";
		break;
		
		case "calendar_32":
			dialog.text = "Di' 'Grazie'. Che gli dèi ti guidino sul tuo cammino, anche se non li vedi. I bianchi dicono: destino. Kukulcan t’ha chiamato, gli dèi ti accompagnano. Va’, fa il tuo dovere e lascia che gli spiriti benevoli ti conducano.";
			link.l1 = "Grazie, Occhio di Serpente! Non ti scorderò mai.";
			link.l1.go = "calendar_33";
		break;
		
		case "calendar_33":
			TakeNItems(pchar, "Ultimate_potion", 4);
			Log_Info("You have received four versatile potions");
			PlaySound("interface\important_item.wav");
			dialog.text = "Aspetta. Stavamo quasi per dimenticare la cosa più importante. Kukulcan divora l’uomo e si nutre della sua vita. Ti ho preparato delle pozioni. Pozioni dei Comanche. Le do a te. Ho fatto quattro fiasche, così potrai portare con te tre compagni fedeli e coraggiosi.";
			link.l1 = "Hai fatto tanto per me, fratello dalla pelle rossa...";
			link.l1.go = "calendar_34";
		break;
		
		case "calendar_34":
			dialog.text = "Fratello non è solo una parola per gli indiani della tribù Comanche. Quando torni dalla città di Kukulcan, passa dal nostro villaggio. Cucineremo un sacco, un sacco di saraiaka. Sarò felice di rivederti.";
			link.l1 = "Certo, fratello dalla pelle rossa! Verrò senz'altro a trovarti!";
			link.l1.go = "calendar_35";
		break;
		
		case "calendar_35":
			DialogExit();
			pchar.questTemp.Tieyasal = "calendar_place";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Tieyasal", "17");
			sld = ItemsFromID("skinmap");
			sld.price = 100; // кожаную карту можно выкладывать 270912 
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
