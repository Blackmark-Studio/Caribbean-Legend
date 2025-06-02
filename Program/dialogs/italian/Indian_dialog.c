// диалог индейцев в поселениях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Non abbiamo nulla di cui parlare!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> индейцы в поселении
		case "IndianMan":
			NextDiag.TempNode = "IndianMan";
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Viso pallido","La squaw bianca")+" vuole parlare?","Tu di nuovo, "+GetSexPhrase("Viso pallido","Bianca squaw")+".",""+GetSexPhrase("Viso Pallido ama parlare. Sembra una squaw.","La squaw bianca ama parlare.")+"","Gli spiriti hanno portato il mio viso pallido "+GetSexPhrase("fratello","sorella")+" a me.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sì.","Sì, sono di nuovo io.","Molto poetico.","Sono anche felice di vederti.",npchar,Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		
		case "IndPearlMan_1":
			dialog.text = "Dimmi, perché sei venuto, viso pallido?";
			link.l1 = "Oh, niente in particolare, volevo solo ascoltare quello che avevi da dire...";
			link.l1.go = "exit";
		break;
		
		case "IndianWoman":
			NextDiag.TempNode = "IndianWoman";
			dialog.text = NPCStringReactionRepeat("L'uomo bianco vuole parlare?","Di nuovo tu, viso pallido?","Viso pallido ama parlare.","Gli spiriti hanno portato a me il mio fratello dal viso pallido.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sì.","Sì, sono di nuovo io.","Molto poetico.","Sono felice di vederti anche io.",npchar,Dialog.CurrentNode);
			link.l1.go = "IndianWoman_1";
		break;
		
		case "IndianWoman_1":
			dialog.text = LinkRandPhrase(""+npchar.name+" ascoltarti, figlio del mare.","Cosa vuoi da "+npchar.name+", viso pallido?","Le mie orecchie sono aperte alle tue parole, straniero.");
			if (CheckIndianGift() && !CheckAttribute(npchar, "quest.gift"))
			{
				link.l1 = LinkRandPhrase("Ho qualcosa per te. Vuoi dare un'occhiata?","Vuoi dare un'occhiata a qualcosa di davvero interessante? Ti piacerà sicuramente...","Ho qualcosa che ti piacerà, figlio della giungla. Vuoi dare un'occhiata?");
				link.l1.go = "gift";
			}
			link.l9 = "Oh, niente in particolare, volevo solo ascoltare quello che avevi da dire...";
			link.l9.go = "exit";
		break;
		
		case "gift":
			iTemp = 2;
			dialog.text = RandPhraseSimple(""+npchar.name+" vuole dare un'occhiata. Mostralo.",""+npchar.name+" è interessato. Mostrami.");
			if (CheckCharacterItem(pchar, "mineral6"))
			{
				link.l1 = "Da uno specchio.";
				link.l1.go = "gift_1";
			}
			for (i=50; i>=47; i--)
			{
				if (CheckCharacterItem(pchar, "jewelry"+i))
				{
					sTemp = "l"+iTemp;
					link.(sTemp) = "Give"+XI_ConvertString("jewelry"+i)+".";
					link.(sTemp).go = "gift_"+i;
					iTemp++;				
				}
			}
		break;
		
		case "gift_1":
			RemoveItems(pchar, "mineral6", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Ora "+npchar.name+" può guardarsi non solo nell'acqua del fiume! Grazie, gentile sconosciuto!";
			link.l1 = "Certo, ora puoi ammirare il tuo viso quanto vuoi...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_47":
			RemoveItems(pchar, "jewelry47", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Così bello! Questo braccialetto è per "+npchar.name+"! Grazie, gentile sconosciuto!";
			link.l1 = "Mettitelo sulla tua mano abbronzata, bellezza, sarai stupenda...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_48":
			RemoveItems(pchar, "jewelry48", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Che bell'anello? È per "+npchar.name+", sì? Grazie, gentile sconosciuto!";
			link.l1 = "Mettitelo al dito, e tutti i tuoi amici saranno gelosi...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_49":
			RemoveItems(pchar, "jewelry49", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Quelle meravigliose perline verdi sono per "+npchar.name+"? Così bella! Grazie, gentile sconosciuto!";
			link.l1 = "Adorna il tuo collo con essi, figlia della selva. Tutti ti ammireranno...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_50":
			RemoveItems(pchar, "jewelry50", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh, che bello anello verde! Questo è un regalo per "+npchar.name+"? Grazie, gentile sconosciuto!";
			link.l1 = "Sarà bellissimo sulla tua mano, bella...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_exit":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) // Addon 2016-1 Jason Пиратская линейка
			{
				dialog.text = "Volevo chiedere "+npchar.name+"qualcosa, figlio del mare?";
				link.l1 = "Hai ragione, bella. Io e i miei valorosi guerrieri stiamo andando alla selva, all'insediamento spagnolo tra le montagne e stiamo cercando una guida. Sarò generoso sia con l'uomo che con sua moglie. Ho molte ricchezze: bellissimi fucili, occhiali magici, specchi, collane, braccialetti e anelli. Forse tuo marito può essere la guida che stiamo cercando?";
				link.l1.go = "hayamee";
			}
			else
			{
				DialogExit();
			}
			ChangeIndianRelation(1.00);
			npchar.quest.gift = true;
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		// Кумвана, вождь деревни араваков
		case "cumvana":
			dialog.text = "Saluti, figlio del mare. Io sono Kumwana, capo del clan della Tartaruga del popolo Locono. Che affari ti portano nel mio villaggio?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "Ho portato un regalo per te, capo. Dai un'occhiata, ti piacerà.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "Capo, sono venuto a chiedere il tuo aiuto. Voglio raggiungere un insediamento spagnolo chiamato Merida, si trova tra le montagne nella tua selva, il problema è che non so come arrivarci.";
				link.l1.go = "cumvana_no";
			}
			DelLandQuestMark(npchar);
		break;
		
		case "cumvana_no":
			dialog.text = "È molto buono per te, figlio del mare, non conoscere quella strada. Conduce attraverso una foresta, terra della temeraria tribù dei Capong. Veri giaguari, sono, oh-ey! Io non vado mai in quel posto spagnolo. Il mio popolo - gente pacifica, non andiamo nella terra dei Capong. Kumwana non può darti un consiglio. Strada troppo pericolosa.";
			link.l1 = "Ma gli spagnoli hanno trovato una via! E non ho paura di quei Capongs...";
			link.l1.go = "cumvana_no_1";
		break;
		
		case "cumvana_no_1":
			dialog.text = "Ma dovresti. Sono gente crudele. Hanno ucciso molti dei miei in bosco. Kumwana ha detto tutto.";
			link.l1 = "Beh, merda...";
			link.l1.go = "cumvana_no_2";
		break;
		
		case "cumvana_no_2":
			DialogExit();
			AddQuestRecord("Roger_5", "5");
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_1":
			dialog.text = "Oh-ey! Tu di nuovo, figlio del mare. Cosa vuoi dire a Kumwana?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "Ti ho portato un dono, capo. Dai un'occhiata, ti piacerà.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "La speranza di trovare Merida è ancora con me...";
				link.l1.go = "cumvana_1_1";
			}
		break;
		
		case "cumvana_1_1":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_2":
			dialog.text = "I Locono sono sempre felici di vedere buoni amici.";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0)
			{
				link.l1 = "Regala una pistola."; // 5
				link.l1.go = "cumvana_2_1";
			}
			if (CheckCharacterItem(pchar, "compass1")) // 3
			{
				link.l2 = "Regala una bussola.";
				link.l2.go = "cumvana_2_2";
			}
			if (GetCharacterFreeItem(pchar, "spyglass1") > 0)
			{
				link.l3 = "Regala un cannocchiale economico.";
				link.l3.go = "cumvana_2_3";
			}
			if (GetCharacterFreeItem(pchar, "spyglass2") > 0)
			{
				link.l4 = "Regala un comune cannocchiale."; // 2
				link.l4.go = "cumvana_2_4";
			}
			if (GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l5 = "Regala un buon cannocchiale."; // 4
				link.l5.go = "cumvana_2_5";
			}
		break;
		
		case "cumvana_2_1":
			Log_Info("You have given a pistol");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "pistol5", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_3");
			dialog.text = "Oh-ey! Che bella arma di pallido volto! Kumwana accetta il tuo dono! Anche tu, figlio del mare, accetta un dono da Kumwana e dal popolo Locono.";
			link.l1 = "Grazie, capo!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_2":
			Log_Info("You have given a compass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "compass1", 1);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Amuleto magico dei visi pallidi! Kumwana accetta il tuo dono! Anche tu, figlio del mare, accetta un dono da Kumwana e dal popolo Locono.";
			link.l1 = "Grazie, capo!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_3":
			Log_Info("You have given a cheap spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass1", 1);
			GiveItem2Character(pchar, "obereg_2");
			GiveItem2Character(pchar, "indian_5");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Tubo magico dei visi pallidi! Kumwana accetta il tuo dono! Anche tu, figlio del mare, accetta un dono da Kumwana e dal popolo Locono.";
			link.l1 = "Grazie, capo!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_4":
			Log_Info("You have given a common spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass2", 1);
			GiveItem2Character(pchar, "obereg_6");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Tubo magico dei visi pallidi! Kumwana accetta il tuo dono! Anche tu, figlio del mare, accetta un dono da Kumwana e dal popolo Locono.";
			link.l1 = "Grazie, capo!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_5":
			Log_Info("You have given a decent spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass3", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_5");
			dialog.text = "Oh-ey! Tubo magico dei visi pallidi! Kumwana accetta il tuo regalo! Anche tu, figlio del mare, accetta un regalo da Kumwana e dal popolo Locono.";
			link.l1 = "Grazie, capo!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_3":
			dialog.text = "Cosa ti porta nel nostro villaggio, figlio del mare?";
			link.l1 = "Capo, sono venuto a chiedere il tuo aiuto. Voglio raggiungere un insediamento spagnolo chiamato Merida, si trova tra le montagne nella tua selva, il problema è che non so come arrivarci. Forse, potresti fornirmi un coraggioso guerriero che ci mostrerebbe la strada?";
			link.l1.go = "cumvana_4";
		break;
		
		case "cumvana_4":
			dialog.text = "Oh-ey! Strada pericolosa, molto pericolosa. Il cammino conduce attraverso una foresta, la terra dell'intrepida tribù dei Capong. Veri giaguari, sono, oh-ey! Io non vado mai in quel posto spagnolo. Il mio popolo - gente pacifica, non andiamo nella terra dei Capong.";
			link.l1 = "Devo proprio arrivare a Merida. Kumwana, chiedi ai tuoi uomini per favore, forse, qualcuno accetterà di unirsi alla mia unità? I miei guerrieri sono esperti, ben armati e non temono nulla, nemmeno il Diavolo. Proteggeremo la guida e la ricompenseremo generosamente quando sarà finita.";
			link.l1.go = "cumvana_5";
		break;
		
		case "cumvana_5":
			dialog.text = "Molto bene, figlio del mare. Riunirò un circolo di guerrieri e parlerò loro dei tuoi desideri. Vieni a trovarmi domani dopo l'alba.";
			link.l1 = "Grazie, capo!";
			link.l1.go = "cumvana_6";
		break;
		
		case "cumvana_6":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetStayType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			//AddQuestRecord("Roger_5", "6");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			SetLaunchFrameFormParam("The next day...", "Mtraxx_MeridaVozhdDialog", 0, 4.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 1, 0, 0);
			RecalculateJumpTable();
		break;
		
		case "cumvana_7":
			dialog.text = "Oh-ey! Tu di nuovo, figlio del mare. Cosa vuoi dire a Kumwana?";
			link.l1 = "Niente ancora, capo.";
			link.l1.go = "cumvana_7x";
			if(CheckAttribute(pchar,"questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_hayamee")
			{
				link.l2 = " Ascolta, Kumwana. Il mio popolo ed io abbiamo davvero bisogno di attraversare il fiume e raggiungere quella dannata cittadina. Lascia che ti spieghi quanto sia cruciale per noi.";
				link.l2.go = "cumvana_hard";
			}
		break;
		
		case "cumvana_hard":
			dialog.text = "I miei cacciatori ti hanno già informato che...";
			link.l1 = "Non c'è bisogno di ripeterti due volte, Kumwana. Ma guarda fuori - e non sopravvalutare le tue capacità. I miei coraggiosi ragazzi che sono venuti qui per le pietre spagnole sono sparsi nel tuo villaggio. E la loro pazienza si sta esaurendo. E cosa succederà quando sarà finalmente esaurita, è meglio che tu non lo sappia - credimi.";
			link.l1.go = "cumvana_medium_1";
			link.l2 = "Chiudi la bocca e ascolta, scimmia dalla pelle rossa. Il mio popolo può essere molto più terribile di questi maledetti Kapongs. Non farti ingannare dal fatto che siamo così gentili ora. Ti do una scelta semplice: o trovi una guida entro ventiquattro ore, o vi legheremo tutti e vi manderemo attraverso la giungla davanti alla nostra squadra. Se ci porti nella direzione sbagliata, perirai tu stesso nelle paludi o andrai legato a combattere i Kapongs. Capito?";
			link.l2.go = "cumvana_hard_1";
			link.l3 = "Kumwana, ho bisogno di questa guida. Abbiamo fatto un lungo viaggio, e davvero non voglio dire ai miei ragazzi che è stato tutto invano.";
			link.l3.go = "cumvana_good_1";
			pchar.questTemp.Mtraxx_MeridaZapugivanieIndeets = true;
		break;
		
		case "cumvana_good_1":
			dialog.text = "Kumwana ha già detto, nessuno dei Lokono vuole andare con l'uomo bianco.";
			link.l1 = "E non puoi fare nulla al riguardo? Chiedi a qualcuno personalmente. Ordina, dopotutto. Sei il capo o no?";
			link.l1.go = "cumvana_good_2";
		break;
		
		case "cumvana_good_2":
			dialog.text = "Il capo non costringe l'indiano. Il capo governa e desidera la pace per il suo popolo. Gli indiani sanno - il Kapong vedrà che i Lokono porteranno i visi pallidi. Le loro teste da catturare da Kanaima. Vengono per vendicarsi sui Lokono. Kapong - per uccidere. Cattura i Lokono, fai schiavi.";
			link.l1 = "E chi ha catturato le vostre teste? Quale spirito o demone rende gli indiani dei vermi così codardi? Beh, forse dovrò davvero abbandonare la campagna contro Merida. Ma ricorda una cosa, capo. Ogni volta che mi chiedono cosa so dei Lokono, risponderò invariabilmente - che sono una tribù di codardi senza valore. Guidati da un capo altrettanto codardo e miope come loro, il cui volto è distorto da una smorfia di orrore al solo ricordo dei Kapongs. Non guadagnerai gloria tra gli indiani, né rispetto tra noi, i volti pallidi.";
			link.l1.go = "cumvana_good_3";
		break;
		
		case "cumvana_good_3":
			dialog.text = "Viso pallido non conosce le usanze degli indiani...";
			link.l1 = "So abbastanza per sapere chi gli indiani chiamano un codardo e chi un valoroso guerriero. Addio, Kumwana. E ricorda le mie parole. Sei un governante codardo e miope.";
			link.l1.go = "cumvana_good_4";
		break;
		
		case "cumvana_good_4":
			DialogExit();
			ChangeIndianRelation(5.00);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			pchar.questTemp.Mtraxx = "fail";
			
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.function = "Mtraxx_MeridaHayameeGoodDialog";
		break;
		
		case "cumvana_medium_1":
			dialog.text = "Perché minacciarmi in questo modo? Pensiamo che tu sia bravo...";
			link.l1 = "Sto bene, finché tu collabori, capito? Hai un solo giorno. E credimi, i miei uomini faranno qualsiasi cosa io ordini. Siamo più forti. E se ne dubiti... Ho visto tua moglie. E le tue figlie. Penso che tu abbia capito il messaggio ora.";
			link.l1.go = "cumvana_hard_2";
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "cumvana_hard_1":
			dialog.text = "Perché minacciarmi in questo modo? Pensiamo che tu sia bravo...";
			link.l1 = "Sto bene, purché tu collabori, capito? Hai un solo giorno. E credimi, la mia gente farà tutto ciò che ordino. Siamo più forti. E se ne dubiti... Ho visto tua moglie. E le tue figlie. Penso che tu abbia capito il messaggio ora.";
			link.l1.go = "cumvana_hard_2";
		break;
		
		case "cumvana_hard_2":
			dialog.text = "Kumwana capisce, viso pallido. Nel villaggio, c'è un cacciatore di nome Tagofa. Forse può guidarti all'insediamento...";
			link.l1 = "Torno tra ventiquattro ore. Charlie Prince non ha più nulla da aggiungere, selvaggio.";
			link.l1.go = "cumvana_hard_3";
		break;
		
		case "cumvana_hard_3":
			DialogExit();
			ref Hayam = characterFromId("Hayamee");
			ChangeCharacterAddressGroup(Hayam, "none", "", "");
			Hayam.lifeday = 0;
			pchar.questTemp.Mtraxx = "merida_hayamee_hard";
			npchar.dialog.currentnode = "cumvana_7";
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeHardTagofaWait", 0, 0, 1, false);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			ChangeCharacterComplexReputation(pchar, "nobility", -80);
			ChangeOfficersLoyality("bad", 5);
			ChangeIndianRelation(-50.0);
			//log_Info("The attitude of the Indians has decreased");
			AddQuestRecord("Roger_5", "8a");
			pchar.GenQuest.CannotWait = true; //запретить отдыхать
			
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.function = "Mtraxx_MeridaHayameeHardLepriconDialog";
		break;
		
		case "cumvana_7x":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
		break;
		
		case "cumvana_8":
			dialog.text = "Figlio del mare, sei tu. Kumwana ha parlato con i guerrieri dei Locono.";
			link.l1 = "E allora? Hai un volontario?";
			link.l1.go = "cumvana_9";
		break;
		
		case "cumvana_9":
			dialog.text = "Abbiamo alcuni cacciatori in giro che ci sono stati. Ma temono i Capongs, i giaguari sono in guerra. Non vanno, dicono che Capong uccide la tua squadra. Non temono i volti pali.";
			link.l1 = "I miei guerrieri sono molto migliori di tutti loro! Parte della mia unità ha passato una vita nella giungla! Non siamo certo dei dilettanti!";
			link.l1.go = "cumvana_10";
		break;
		
		case "cumvana_10":
			dialog.text = "Mi dispiace, figlio del mare. I miei cacciatori hanno paura, i Capongs sono pericolosi, molto molto.";
			link.l1 = "Bene, allora forse, possono spiegare come arrivarci? In dettaglio.";
			link.l1.go = "cumvana_11";
		break;
		
		case "cumvana_11":
			dialog.text = "Per arrivarci dovresti navigare sul fiume e poi sbarcare in un luogo speciale. Se è il posto sbagliato, finirai nella palude e morirai. La nostra selva è piena di pericoli. Non troverai il posto da solo, figlio del mare.";
			link.l1 = RandSwear()+"E cosa dovrei fare poi? Come convincere i tuoi cacciatori?";
			link.l1.go = "cumvana_12";
		break;
		
		case "cumvana_12":
			dialog.text = "Kumwana non dirà più nulla, figlio del mare.";
			link.l1 = "Bene...";
			link.l1.go = "cumvana_13";
		break;
		
		case "cumvana_13":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			AddQuestRecord("Roger_5", "7");
			pchar.questTemp.Mtraxx = "merida_advice";
			LAi_SetHuberType(npchar);
			AddLandQuestMark(characterFromId("Lepricon"), "questmarkmain");
		break;
		
		// Хайами
		case "hayamee":
			if (npchar.id == "Hayamee")
			{
				dialog.text = "Mio marito Tagofa è il miglior cacciatore della tribù. Oh-ey! "+npchar.name+" è orgogliosa di suo marito. "+npchar.name+" spesso va con Tagofa a Selva. Vai lontano. Tagofa sa dove si trova l'insediamento spagnolo.";
				if (IsCharacterPerkOn(pchar, "Trustworthy") && stf(pchar.questTemp.Indian.relation) >= 40.0)
				{
					link.l1 = "Tagofa conosce la strada per la città spagnola che i visi pallidi chiamano Merida?";
					link.l1.go = "hayamee_1";
				}
				else
				{
					link.l1 = "Ebbene, ebbene... Tagofa sa come arrivare alla città spagnola?";
					link.l1.go = "hayamee_bad_1";
				}
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Mio marito non va nella selva, figlio del mare. Lui pesca. Bravo pescatore, oh-ey!","Mio marito buon cacciatore, oh-ey, ma lui non va nella giungla profonda."),RandPhraseSimple("Un giaguaro ha ferito mio marito durante la caccia. Ora si siede nel villaggio, fa le frecce, oh-ey!","Sei lune fa tre Capongs hanno attaccato mio marito. Ora lui non va a cacciare lontano dal villaggio. Mai! oh-ey!"));
				link.l1 = LinkRandPhrase("Peccato...","Peccato...","Che peccato..."));
				link.l1.go = "exit";
			}
		break;
		
		case "hayamee_bad_1":
			dialog.text = "Tagofa è cresciuto in questa giungla. Conosce ogni albero e ogni pietra intorno!";
			link.l1 = "Ti darò a te e a Tagofa molti doni se ci porterà lì. Gioielli, armi, qualsiasi cosa. Tutto quello che vuoi. Entro ragione, ovviamente, he-he. Come posso parlare con tuo marito?";
			link.l1.go = "hayamee_bad_2";
		break;
		
		case "hayamee_bad_2":
			dialog.text = "Tagofa non andrà con l'uomo bianco. Tagofa rimarrà nel villaggio. Vai a cacciare. Non combattere con il Kapong.";
			link.l1 = "Non dovrà combattere con i Kapong. Non appena li vede, può nascondersi. Solo il mio popolo combatterà.";
			link.l1.go = "hayamee_bad_3";
		break;
		
		case "hayamee_bad_3":
			dialog.text = "No, yalanaui. Il viso pallido non mantiene mai la sua parola. Il viso pallido parla - e la parola vola immediatamente nel vuoto. Il Kapong ucciderà Tagofa e poi verrà al nostro villaggio, ucciderà il Lokono.";
			link.l1 = "Pensi che questi Kapongs siano tutto ciò di cui devi preoccuparti? Ti sbagli di grosso...";
			link.l1.go = "hayamee_bad_4";
			if (stf(pchar.questTemp.Indian.relation) < 40.0) notification("The Indians don't respect you "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
		break;
		
		case "hayamee_bad_4":
			dialog.text = "Yahahu per entrare nel viso pallido! Hayami non parla più a yalanaui.";
			link.l1 = "Bene-bene...";
			link.l1.go = "hayamee_bad_5";
		break;
		
		case "hayamee_bad_5":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
		break;
		case "hayamee_1":
			dialog.text = "Tagofa è andato a caccia un giorno fa. Promise di tornare domani quando il sole dorme. Vieni domani figlio del mare, sarò con Tagofa in quella capanna, mentre cammini nel villaggio vai a destra. Gli chiederò se viene o non viene con te.";
			link.l1 = "Di a Tagofa che gli regalerò la pistola più bella. E a te, ti regalerò un sacco di gioielli.";
link.l1.go = "hayamee_1_1";
		break;
		
		case "hayamee_1_1":
			dialog.text = "I Lokono non si fidano dei Yalanaui. I Yalanaui ingannano l'indiano, rendono l'indiano uno schiavo. Ma i Lokono sentono il tuo nome, viso pallido. La mia fiducia è tua. Vieni domani dopo il tramonto, figlio del mare. Sarò con Tagofa in quella capanna. Gli chiederò se verrà con te o no.";
			link.l1 = "Dì a Tagofa che gli darò la mia pistola più bella. E per te ho molti gioielli.";
			link.l1.go = "hayamee_2";
			notification("The Indians respect you "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			notification("Trustworthy", "Trustworthy");
		break;
		
		case "hayamee_2":
			dialog.text = "Oh-ey!";
			link.l1 = "...";
			link.l1.go = "hayamee_3";
		break;
		
		case "hayamee_3":
			DialogExit();
			AddQuestRecord("Roger_5", "9");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.hour  = 22.0;
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.function = "Mtraxx_MeridaHayameeTimer";
		break;
		
		case "hayamee_4":
			pchar.quest.Mtraxx_MeridaPotionLate.over = "yes";
			dialog.text = ""+npchar.name+" è lieto di vedere un figlio del mare. Tagofa è tornato. Ma ha bevuto troppo kasheeri e dorme. Non svegliarlo, Tagofa riposa. Parlerò io.";
			link.l1 = "Molto bene, "+npchar.name+". Il tuo marito ci guiderà a Merida?";
			link.l1.go = "hayamee_5";
		break;
		
		case "hayamee_5":
			dialog.text = "Tagofa ha accettato di guidare i tuoi guerrieri attraverso la selva verso il villaggio spagnolo. Ma ci sono delle condizioni...";
			link.l1 = "Quali sono?";
			link.l1.go = "hayamee_6";
		break;
		
		case "hayamee_6":
			dialog.text = "Proteggi Tagofa dai guerrieri Capong. Tagofa non combatte né con gli spagnoli, né con i Capong. Se affronta il pericolo, scapperà e nessuno lo troverà, è il miglior cacciatore Locono.";
			link.l1 = "Capisco. Ti preoccupi per il tuo uomo, è comprensibile. Ti prometto che ci occuperemo di tutti quei Capongs da soli.";
			link.l1.go = "hayamee_7";
		break;
		
		case "hayamee_7":
			dialog.text = "Oh-ey! Tagofa vuole doni dal figlio del mare: uno piccolo per sparare molte pietre e uno grande per sparare una pietra, quelle belle. Vuole anche pallottole per ogni cannone: tante quante le dita di entrambe le mani, tre volte.";
			link.l1 = "Caspita! Il tuo uomo sa qualcosa di pistole, eh? Molto bene. Cosa altro?";
			link.l1.go = "hayamee_8";
		break;
		
		case "hayamee_8":
			dialog.text = "E Tagofa desidera un bel occhio magico di visi pallidi.";
			link.l1 = "Un cannocchiale? Bene. Qualcos'altro?";
			link.l1.go = "hayamee_9";
		break;
		
		case "hayamee_9":
			dialog.text = "Non più per Tagofa. "+npchar.name+" desidera cose belle. Anello d'oro con grande pietra rossa, e perle di moltissime pietre verdi. "+npchar.name+"l'ho visto su Mary Bianca a Maracaibo.";
			link.l1 = "Un anello d'oro con perle di rubino e giada?";
			link.l1.go = "hayamee_10";
		break;
		
		case "hayamee_10":
			dialog.text = "Non è giada. È lucente e gli uomini bianchi lo apprezzano.";
			link.l1 = "Smeraldo? Perle di smeraldo?";
			link.l1.go = "hayamee_11";
		break;
		
		case "hayamee_11":
			dialog.text = "Oh-ey!";
			link.l1 = "Eh, "+npchar.name+" sa qualcosa sui gioielli! Molto bene, lo otterrai.";
			link.l1.go = "hayamee_12";
		break;
		
		case "hayamee_12":
			dialog.text = "Porta tutte le cose a "+npchar.name+" insieme, figlio del mare. Poi Tagofa guiderà te e i tuoi guerrieri. Non perdere tempo, in mezza luna Tagofa ed io andremo al villaggio vicino. Per un giorno alto. Ora vai, "+npchar.name+" vuole dormire.";
			link.l1 = "Non ti farò aspettare troppo a lungo. Ci vediamo.";
			link.l1.go = "hayamee_13";
		break;
		
		case "hayamee_13":
			DialogExit();
			AddQuestRecord("Roger_5", "10");
			LAi_CharacterDisableDialog(npchar);
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeLate", 0, 0, 15, false); // таймер
			// Тагофу в сидячее положение
			pchar.quest.mtraxx_merida_wait2.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.hour  = 9.0;
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.function = "Mtraxx_MeridaTagofaHide";
		break;
		
		case "hayamee_14":
			bOk = GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0;
			dialog.text = "Hai portato cosa "+npchar.name+" e Tagofa ha chiesto?";
			if (bOk && GetCharacterFreeItem(pchar, "pistol3") > 0 && GetCharacterFreeItem(pchar, "pistol5") > 0 && GetCharacterItem(pchar, "bullet") >= 30 && GetCharacterItem(pchar, "grapeshot") >= 30 && GetCharacterItem(pchar, "gunpowder") >= 60 && CheckCharacterItem(pchar, "jewelry41") && CheckCharacterItem(pchar, "jewelry42"))
			{
				link.l1 = "Sì. Tutto è secondo la tua lista.";
				link.l1.go = "hayamee_15";
			}
			else
			{
				link.l1 = "No, ci sto ancora lavorando.";
				link.l1.go = "hayamee_14x";
			}
		break;
		
		case "hayamee_14x":
			DialogExit();
			npchar.dialog.currentnode = "hayamee_14";
		break;
		
		case "hayamee_15":
			pchar.quest.Mtraxx_MeridaHayameeLate.over = "yes";
			Mtraxx_MeridaRemoveGifts();
			dialog.text = ""+npchar.name+" è felice, figlio del mare. Ora chiamo marito. Lui va con te. Ma ricorda ciò che hai promesso di "+npchar.name+"!";
			link.l1 = "Sì-sì, ricordo tutto. Lo terrò al sicuro, non preoccuparti.";
			link.l1.go = "hayamee_16";
		break;
		
		case "hayamee_16":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee_peace";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7.0);
			DoQuestFunctionDelay("Mtraxx_MeridaTagofaEnter", 20.0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
			
		case "CitizenNotBlade":
			dialog.text = "Metti via la tua arma, viso pallido, o ti costringeremo a farlo!";
			link.l1 = LinkRandPhrase("Bene.","Bene.","Non preoccuparti, lo sto mettendo via...");
			link.l1.go = "exit";
		break;  

	}
}
