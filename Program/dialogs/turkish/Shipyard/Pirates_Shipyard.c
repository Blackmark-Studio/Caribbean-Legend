// диалог по городам
// Это мастер тюнинга
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    string 	sTemp;
	int 	amount, iSan, iOil, iSil, iRop;
	int iTemp, iSum; // 280912
	ref 	shTo;
	string 	s1;
 
	switch (Dialog.CurrentNode)
	{		
		// -----------------------------------Диалог первый - первая встреча
		case "First time":  // перехват основного диалога, только один раз
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "Off... Ne berbat bir iklim... Benim adım "+GetFullName(npchar)+", ve Tanrı beni kahretsin, eğer bu Tanrı'nın unuttuğu adalardaki en iyi gemi ustası ben değilsem. Ama şu nem beni mahvediyor...";
				Link.l1 = pcharrepphrase("Bin köpekbalığı eksikti, şimdi de yaşlı birinin homurdanmalarıyla uğraşıyorum. Benim adım "+GetFullName(pchar)+", sanırım hakkımda bir şeyler duymuşsundur.","Nem rutubet, nem de başka bir şey, efendim. Yaşlılıktan. Benim adım "+GetFullName(pchar)+", sanırım hakkımda bir şeyler duymuşsundur.");
				Link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else // нужно, если по квестам будет сброс на  "First time"
			{
				dialog.text = "Ah, yine sen, sürekli dertlerinden bahsediyorsun... (öksürür).";
				link.l1 = pcharrepphrase("Haklısınız, yine ben geldim. Ama hâlâ ruhunuzu Tanrı'ya teslim etmemişken iş konuşalım.","Hafızanız sizi yanıltmıyor, şimdi izninizle, daha özel bazı sorulara geçelim.");
				link.l1.go = "node_3";
				link.l2 = pcharrepphrase("Sürekli mırıldanmalarından bıktım. Hoşça kal.","Artık gitmem gerek. Rahatsız ettiğim için üzgünüm");
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Master_Ship";
			Dialog.CurrentNode = "Master_Ship";
		break;
		
		case "Master_Ship":
		//Jason ----------------------------------- Хронометр Алекса ------------------------------------------
			if (CheckAttribute(npchar, "quest.sextant") && CheckAttribute(pchar, "questTemp.AlexClock") && pchar.location == "Pirates_shipyard" && !CheckAttribute(npchar, "quest.clock"))
			{
				dialog.text = "Aha, Kaptan "+GetFullName(pchar)+"! Ne güzel, uğradınız!";
				Link.l1 = "Bana bir konuda ihtiyacın var gibi görünüyor, değil mi? Genelde bu kadar nazik olmazsın.";
				Link.l1.go = "clock_begin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "clock" && pchar.location == "Pirates_shipyard")
			{
				dialog.text = "Sana yine eli boş döndün kaptan! Peki ya... misafirler ne oldu?";
				Link.l1 = "Gittiler. Onlara sordum, ve gittiler.";
				Link.l1.go = "clock_complete";
				break;
			}
		//<-- хронометр Алекса
			dialog.text = "Ah, yine sen, sürekli dertlerinden bahsediyorsun... (öksürür)";
			link.l1 = pcharrepphrase("Haklısın, yine ben geldim. Ama hâlâ canın bedendeyken iş konuşalım.","Hafızanız sizi yanıltmıyor, şimdi izninizle, biraz daha özel sorulara geçelim.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("Sürekli homurdanmandan bıktım. Elveda.","Artık gitmem gerek. Rahatsız ettiğim için kusura bakmayın.");
			link.l2.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;

		case "node_1":
			dialog.text = "Şimdiki gençler... Hiç saygı göstermiyorsunuz. Ateşli kafalar, sert eller, ne istiyorsunuz?";
			link.l1 = pcharrepphrase("Doğru. Ama er ya da geç her şeyin bir sonu var, ve senin vaktin de yaklaşıyor gibi görünüyor...","Bana öyle geliyor ki, gençliğinizde siz de büyüklerinize pek saygı duymuyordunuz. Yanılıyor muyum?");
			link.l1.go = "node_2";
		break;

		case "node_2":
			dialog.text = "Büyüklerine karşı gelme, velet.";
			link.l1 = pcharrepphrase("Sakin ol şimdi. Sakinleş. Kendini fazla yorma, yoksa kalp krizi geçirebilirsin. Karayipler'in en iyi gemi ustasının ölümüne sebep olmakla suçlanmak istemem. Şimdi işimize bakalım.","Saygısızlığını yaşına duyduğum saygıdan dolayı affediyorum. Ve şimdi, işin varsa, artık asıl meseleye geçelim.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("Pekala, benden bu kadar öğüt yeter! Hoşça kal!","Anlaşılan aynı fikirde olmayacağız. Hoşça kal.");
			link.l2.go = "exit";
		break;

		case "node_3":
			dialog.text = "(öksürerek)... İnsanlar yaşlı bir adama rahat vermez oldu. Bu sefer benden ne istiyorsun, "+GetAddress_Form(NPChar)+"? ";
			link.l1 = pcharrepphrase("Tersanenin hizmetlerinden yararlanmam gerekiyor.","Tersanenin hizmetlerinden yararlanmak istiyorum.");
			link.l1.go = "shipyard_dlg";
            Link.l2 = "Bir sorum var.";
			Link.l2.go = "quests"; //(пересылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = "Mali durumlar hakkında konuşmak istiyorum.";
				link.l3.go = "LoanForAll";//(перессылка в файл города)
			}
			link.l9 = pcharrepphrase("Lanet olsun, halletmem gereken acil işlerim var. Hoşça kal.","Gitme zamanım geldi. Üzgünüm.");
			link.l9.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;
		
		case "shipyard_dlg":			
			dialog.Text = "Hadi ama, ne istiyorsun? Yaşlı bir adamı rahatsız etme...";
			link.l2 = "Sadece tersanenin hizmetlerinden yararlanmak istiyorum.";
			link.l2.go = "shipyard";
			link.l3 = "Gemi için silahlara ihtiyacım var.";
			link.l3.go = "Cannons";
			if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
			{
					link.l4 = "Yelkenlerimin görünümünü değiştirmek istiyorum.";
					link.l4.go = "SailsGerald";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_hull"))
			{
					link.l50 = "Gemim oldukça... özel. Birkaç değişiklik yapmak istiyorum.";
					link.l50.go = "FDM";
			}
			/*if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_cabin") && npchar.quest.FDM_cabin == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
			{
					link.l50 = "Kabin yenilemesi için daha fazla sandığım var.";
					link.l50.go = "FDM_cabin_pay";
			}*/
			// Xenon -->
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmoney")
			{
					link.l50 = "Geminin yeniden inşası için buradayım.";
					link.l50.go = "FDM_hull_givemoney";
			}

			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmaterials")
			{
					link.l50 = "Gemi onarım işi için buradayım.";
					link.l50.go = "FDM_hull_checkmaterials";
			}
			// <-- Xenon
			link.l9 = pcharrepphrase("Lanet olsun, halletmem gereken acil işlerim var, hoşça kal.","Gitme vakti geldi. Üzgünüm.");
			Link.l9.go = "ship_tunning_not_now";
		break;	
		
		///////////////////////////////  квестовые ветки
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim?"),"Az önce bana bir soru sormaya çalıştınız...","Benim tersanemde ya da bu kasabada, sizin kadar meraklı insanlarla hiç karşılaşmadım.","Bu kadar çok soru neden? Benim işim gemi yapmak. Hadi ona bakalım.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Hm, şey...","Peki, hadi...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "Step_Door"))
			{
				link.l2 = "Dinle, geçmek isterdim ama o kapı kilitli...";
				link.l2.go = "Step_Door_1";
			}

			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAlexus"))
			{
				link.l1 = "Bir anlaşma teklif etmek istiyorum.";
				link.l1.go = "Al_ShipLetters_1";// генератор  "Найденные документы"
				pchar.questTemp.different.GiveShipLetters.speakAlexus = true;
			}
			if(CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "go") // 280912
			{
				link.l1 = "Fırkateyn için gereken malzemeler hakkında konuşmaya geldim.";
				link.l1.go = "clock";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Dinle, "+npchar.name+", son zamanlarda Isla Tesoro'da Miguel Dichoso'yu gördün mü?";
				link.l1.go = "tieyasal";
			}
		break;
//*************************** Генератор - "Найденные судовые документы" **************
		
		case "Al_ShipLetters_1":
			dialog.text = "Şartlarınızı söyleyin.";
			s1 = "I lucked into finding an absolutely legal ship's documents packet that hasn't been called for search yet.";
			s1 = s1 + "The ship is afloat and it hasn't been excluded from the registry, don't worry. Just a blind fool-owner had the misfortune of losing these papers...";
			link.l1 = s1;
			link.l1.go = "Al_ShipLetters_2";			
		break;
		case "Al_ShipLetters_2":
			s1 = "Let me take a look! It really looks to be freshly filled out. Well, luck is in your favor, sir! ";
			s1 = s1 + "I actually needed a packet just like this. I, in turn, will offer you " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. What do you say?";
			dialog.text = s1;
			link.l1 = "Gerçekten krallara layık bir cömertlik! Elbette kabul ediyorum!";
			link.l1.go = "Al_ShipLetters_3";
			link.l2 = "Hayır, sanmıyorum.";
			link.l2.go = "exit";
		break;
		case "Al_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		

//*************************** Открывание двери ***************************
 		case "Step_Door_1":
			dialog.text = "Doğru. Eğer bu kapıdan geçmek istiyorsan, bana 20.000 peso ödemelisin. Ödemezsen açmam. Burası hayır kurumu değil. Zaten oraya gitmeni de tavsiye etmem. Senin için gitmesen daha iyi olur...";
			if(sti(pchar.money) >= 20000)
			{
    			link.l1 = "Al paran burada. Aç kapıyı.";
    			link.l1.go = "Step_Door_2";
            }
            else
            {
    			link.l1 = "O kadar param yok.";
    			link.l1.go = "Step_Door_3";
            }
            link.l2 = "Olmaz! Bir kapı için asla para ödemem.";
    		link.l2.go = "exit";
		break;
		
 		case "Step_Door_2":
			npchar.Step_Door = true; // fix
			dialog.text = "İçeri gir. Kapı açık. Bana teşekkür etmene gerek yok!";
			link.l1 = "Hayır, neden olmasın. Teşekkür ederim. "+npchar.name+"...";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
            AddMoneyToCharacter(pchar, -20000);
			pchar.quest.CloseBermudesDungeonDoor.win_condition.l1 = "MapEnter";
            pchar.quest.CloseBermudesDungeonDoor.win_condition = "CloseBermudesDungeonDoor";
		break;
		
 		case "Step_Door_3":
			dialog.text = "Peki, eline geçince geri gel. Yoksa beni ikna etmeye çalışma. Boşuna...";
			link.l1 = "Ah, gerçekten nutkum tutuldu!";
			link.l1.go = "exit";
		break;
		
	// ------------------------------------------- хронометр Ђлекса ----------------------------------------------// Addon-2016 Jason замена дублонов на песо везде
		case "clock_begin":
			dialog.text = "Hadi ama, yaşlı bir adama bu kadar katı davranma... Gerçekten yardımına ihtiyacım var, kaptan.";
			link.l1 = "Söyle bana, usta. Sana ne oldu?";
			link.l1.go = "clock_begin_1";
		break;
		
		case "clock_begin_1":
			sTotalTemp = "Steven Dodson";
			if (pchar.questTemp.Alex.Clock == "terrax") sTotalTemp = "Marcus Tyrex";
			dialog.text = "Karayip Korsanları Kardeşliği'nin yeni lideri, "+sTotalTemp+", yeni bir gemi, bir fırkateyn sipariş etti. Ayrıca oldukça zorlu istekleri var: güçlendirilmiş bir gövde, yüksek hız ve iyi manevra kabiliyeti, bir de mümkün olan en büyük kalibrede toplar\nBir amiralin—affedersiniz, kardeşliğin liderinin—gemisi elbette özel olmalı, ama bu da demek oluyor ki onu inşa etmek için özel malzemelere ihtiyacım var. Bunları mutlaka duymuşsundur. Demir ağaç, reçine, gemi ipeği ve halatlar...";
			link.l1 = "Bunu Kardeşliğin liderine anlat o zaman. Yoksa bundan mı çekiniyorsun "+sTotalTemp+" bunun için kafanı keseceğim mi?";
			link.l1.go = "clock_begin_2";
		break;
		
		case "clock_begin_2":
			dialog.text = "Ona söyledim... Şu var ki, yeni liderimizin bu malzemeleri bulup getirecek ne zamanı ne de imkânı var. Ne kadar nadir olduklarını bilmelisiniz. Ve bu özelliklere sahip bir fırkateyni onlar olmadan inşa etmem imkânsız.";
			link.l1 = "Ve sanırım gemi için malzemeleri de benim bulmamı istiyorsunuz?";
			link.l1.go = "clock_begin_3";
		break;
		
		case "clock_begin_3":
			dialog.text = "Evet, öyle. Liderimizin iyi bir dostusunuz. "+sTotalTemp+" kendisi size çok şey borçlu olduğunu söylüyor ve her türlü saygıyı hak ettiğinizde ısrar ediyor... Ben de düşündüm ki: madem onun dostusunuz, belki ona yardım etmekten çekinmezsiniz? Aynı zamanda, benim ne kadar zor bir durumda olduğumu da anlıyorsunuz, değil mi? Tüm malzemelerin ücreti ödenecek, "+sTotalTemp+" altınını tutmaz.";
			link.l1 = "Üzgünüm efendim, ama en az sizin kadar yoğunum "+sTotalTemp+". Malzemeleri toplamak sonsuzluk kadar sürebilir diye korkuyorum. Bu yüzden, bence başkasına sorsan daha iyi olur.";
			link.l1.go = "clock_exit";
			link.l2 = "Pekala, eğer "+sTotalTemp+"Senden bir gemi sipariş ettim - elbette yardımcı olmaya çalışacağım. Gerçekten dostuz ve dostlar birbirine yardım etmeli. Kaç malzemeye ihtiyacın var?";
			link.l2.go = "clock_begin_4";
		break;
		
		case "clock_exit":
			dialog.text = "Bu çok kötü. Gerçekten çok kötü. Sana güveniyordum. Eh, derler ya, hayır demek hayırdır...";
			link.l1 = "...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.AlexClock");
		break;
		
		case "clock_begin_4":
			dialog.text = "100 birim demir ağacı, 150 kap reçine, 110 top gemi ipeği ve 90 makara kenevir halatım eksik. Ne dersin? Bunların hepsini dört ay içinde bulabilir misin? Sanırım daha fazla vaktim kalmadı.";
			link.l1 = "En azından deneyeceğim.   Peki ya ödeme?";
			link.l1.go = "clock_begin_5";
		break;
		
		case "clock_begin_5":
			dialog.text = "Fiyatlarım şöyle: demir ağacı parçası 4000 peso, reçine kabı 1400 peso, ipek topu 2500 peso ve halat sargısı 1500 peso. Eğer hepsini bana getirirsen, senden yana çok güzel bir hediyem olacak.";
			link.l1 = "Ne acaba, merak ediyorum?";
			link.l1.go = "clock_begin_6";
		break;
		
		case "clock_begin_6":
			dialog.text = "Önce malzemeleri getir bana. Ama sana temin ederim: bu işine yarayacak ve bu şey eşsiz. Karayipler'de, hatta tüm dünyada bir eşi daha yok. Umarım içindeki o küçük merak kıvılcımı, malzemeleri benim için toplama isteğini ateşlemiştir.";
			link.l1 = "Pekâlâ, sen de tam bir tilkiymişsin usta! Tamam, anlaştık.";
			link.l1.go = "clock_begin_7";
		break;
		
		case "clock_begin_7":
			dialog.text = "Çok mutluyum. Dönüşünüzü dört gözle bekleyeceğim.";
			link.l1 = "Umarım çok uzun sürmez...";
			link.l1.go = "clock_begin_8";
		break;
		
		case "clock_begin_8":
			DialogExit();
			pchar.questTemp.AlexClock = "go";
			npchar.quest.clock = "true";
			SetFunctionTimerCondition("AlexClock_Over", 0, 0, 122, false); // таймер
			AddQuestRecord("alex_clock", "1");
			// запоминаем переменные
			pchar.questTemp.AlexClock.Sandal = 100;
			pchar.questTemp.AlexClock.Oil = 150;
			pchar.questTemp.AlexClock.Shipsilk = 110;
			pchar.questTemp.AlexClock.Ropes = 90;
		break;
		
		case "clock":
			dialog.text = "Harika! Bugün bana ne getirdiniz?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && !CheckAttribute(npchar, "quest.sandal"))
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "Demir ağaç, şu miktarda "+FindRussianQtyString(iSan)+".";
				link.l1.go = "sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && !CheckAttribute(npchar, "quest.oil"))
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "Reçineler, şu miktarda "+FindRussianQtyString(iOil)+".";
				link.l2.go = "oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && !CheckAttribute(npchar, "quest.shipsilk"))
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "Gemi ipeği, miktarı "+FindRussianQtyString(iSil)+".";
				link.l3.go = "shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && !CheckAttribute(npchar, "quest.ropes"))
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "Kenevir halatları, şu miktarda "+FindRussianQtyString(iRop)+".";
				link.l4.go = "ropes";
			}
			link.l5 = "Şu an için bir şey yok. Sadece hâlâ anlaşmamızın geçerli olduğundan emin olmak istedim.";
			link.l5.go = "exit";
		break;
		
		case "clock_1":
			if (CheckAttribute(npchar, "quest.sandal") && CheckAttribute(npchar, "quest.oil") && CheckAttribute(npchar, "quest.shipsilk") && CheckAttribute(npchar, "quest.ropes")) // все привез
			{
				dialog.text = "Harika! İhtiyacım olan tüm malzemeler elimde. Yardımın için binlerce kez teşekkürler, kaptan. Bana gerçekten büyük bir iyilik yaptın.";
				link.l1 = "Evet, her zaman, kaptan. Ben de oldukça memnunum: Bir dostuma yardım ettim ve güzel para kazandım. Şimdi ise, bana söz verdiğiniz o gizemli eşyanız hakkında konuşmamıza dönelim.";
				link.l1.go = "clock_2";
			}
			else
			{
				dialog.text = "Beni şaşırtacak başka bir şey var mı, kaptan?";
				link.l1 = "Ne yazık ki, şimdilik bu kadar. Sadece beklemeye devam et.";
				link.l1.go = "exit";
				link.l2 = "Evet, bir şey daha var...";
				link.l2.go = "clock";
			}
		break;
		
		case "sandal": // бакаут
			amount = sti(pchar.questTemp.AlexClock.Sandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 4000*iSan;
				dialog.text = "Pekala, tamam. Şuna ihtiyacım olacak "+FindRussianQtyString(amount)+" demir ağacı. Bana getirmişsin "+FindRussianQtyString(iSan)+". .   Yani, bana getireceğin geriye kalan şey şu: "+FindRussianQtyString(iTemp)+". Tamam, parça başına 4000 peso üzerinden, ödülünüz toplamda "+FindRussianMoneyString(iSum)+". Lütfen, alın.";
				link.l1 = "Teşekkürler! Kalanını yakında alacaksınız.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				pchar.questTemp.AlexClock.Sandal = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 4000*amount;
				dialog.text = "Pekala, tamam. Ayrıca şuna da ihtiyacım olacak "+FindRussianQtyString(amount)+"  demir ağacı getirmişsin. "+FindRussianQtyString(iSan)+". Demek demir ağacı işini de hallettik! Pekâlâ, tanesi 4000 peso üzerinden, ödülünüz toplamda "+FindRussianMoneyString(iSum)+". Lütfen, alın.";
				link.l1 = "Teşekkür ederim!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.sandal = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "oil": // смолы
			amount = sti(pchar.questTemp.AlexClock.Oil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1400*iOil;
				dialog.text = "Pekâlâ, tamam. Ayrıca şuna da ihtiyacım olacak "+FindRussianQtyString(amount)+" reçineler. Bana getirmişsin "+FindRussianQtyString(iOil)+". Yani, bana getirmen gereken tek şey kaldı "+FindRussianQtyString(iTemp)+". Tamam, konteyner başına 1400 peso üzerinden, ödülünüz toplamda "+FindRussianMoneyString(iSum)+". Lütfen, alın.";
				link.l1 = "Teşekkürler! Kalanını yakında alacaksınız.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				pchar.questTemp.AlexClock.Oil = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "resins");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1400*amount;
				dialog.text = "Pekâlâ, tamam. Ayrıca şuna da ihtiyacım olacak "+FindRussianQtyString(amount)+" reçineler. Bana getirmişsin "+FindRussianQtyString(iOil)+". Reçineleri de hallettik! Tamam, konteyner başına 1400 peso üzerinden, ödülünüz toplamda "+FindRussianMoneyString(iSum)+". Lütfen, alın.";
				link.l1 = "Teşekkür ederim!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.oil = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "resins");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "shipsilk": // шёлк
			amount = sti(pchar.questTemp.AlexClock.Shipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 2600*iSil;
				dialog.text = "Pekala, tamam. Ayrıca şuna da ihtiyacım olacak "+FindRussianQtyString(amount)+" ipek. Bana getirmişsin "+FindRussianQtyString(iSil)+". Yani, bana getirmen gereken tek şey şu: "+FindRussianQtyString(iTemp)+". Tamam, parça başına 2600 peso üzerinden, ödülünüz toplamda "+FindRussianMoneyString(iSum)+". Lütfen, alın.";
				link.l1 = "Teşekkürler! Kalanını yakında alacaksınız.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				pchar.questTemp.AlexClock.Shipsilk = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "silk");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 2600*amount;
				dialog.text = "Pekâlâ, tamam. Ayrıca şuna da ihtiyacım olacak "+FindRussianQtyString(amount)+" ipek. Bana getirmişsin "+FindRussianQtyString(iSil)+". Pekala, ipek işini de hallettik! Parça başına 2600 peso üzerinden, ödülünüz toplamda "+FindRussianMoneyString(iSum)+". Lütfen, alın.";
				link.l1 = "Teşekkür ederim!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.shipsilk = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "silk");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "ropes": // канаты
			amount = sti(pchar.questTemp.AlexClock.Ropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1500*iRop;
				dialog.text = "Pekala, tamam. Ayrıca şuna da ihtiyacım olacak "+FindRussianQtyString(amount)+" halatlar. Bana getirdin "+FindRussianQtyString(iRop)+" . Yani, bana hâlâ getirmen gereken şey şu: "+FindRussianQtyString(iTemp)+" . Yani, parça başına 1500 peso üzerinden, toplam ödülünüz "+FindRussianMoneyString(iSum)+". Lütfen, alın.";
				link.l1 = "Teşekkürler! Kalanını yakında alacaksınız.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				pchar.questTemp.AlexClock.Ropes = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ropes");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1500*amount;
				dialog.text = "Pekala, tamam. Şuna ihtiyacım olacak "+FindRussianQtyString(amount)+" halatlar. Bana getirmişsin "+FindRussianQtyString(iRop)+" . Halat işini zaten hallettik. Peki, parça başına 1500 peso üzerinden, ödülünüz toplamda "+FindRussianMoneyString(iSum)+". Lütfen, alın.";
				link.l1 = "Teşekkür ederim!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.ropes = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ropes");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "clock_2":
			dialog.text = "Evet, evet... benim meselem hakkında, tabii ki. M-m-mmm... Hmmm... nereye koymuştum... ahhh...";
			link.l1 = "Ne oldu, kaptan? Oldukça endişeli görünüyorsunuz. Bir sorun mu var? Bir sıkıntı mı çıktı?";
			link.l1.go = "clock_3";
		break;
		
		case "clock_3":
			dialog.text = "Kesinlikle. Sorunlar. Son zamanlarda çıkanlar. Kahrolası define avcıları...";
			link.l1 = "Sakin ol, sakin ol. Bu yaşta böyle endişelenmek sana iyi gelmez. Allah korusun, bir kalp atışı kadar yakın olabilirsin. O zaman Kardeşler Birliği'nin başı için fırkateyni kim inşa edecek? Sakin ol ve bana anlat, kim bu hazine avcıları?";
			link.l1.go = "clock_4";
		break;
		
		case "clock_4":
			dialog.text = "Şurada, masamın yanında bir kapı var. O kapı doğrudan eski bir kasaya açılır. O kasada, hazine sandıklarından birinde, yirmi yıl önce o lanet girdaptan çekilip buraya düştüğümde yanımda olan eşyalarımın durduğu metal kutumu saklarım...";
			link.l1 = "Hangi huni? Neyden bahsediyorsun?";
			link.l1.go = "clock_5";
		break;
		
		case "clock_5":
			dialog.text = "Ah, saçmalamalarımı mazur gör. Yaşlanmak kolay değil, delikanlı. Beni affet. Ama bu konuya girmeyelim şimdi. Önemli olan, sana hediye edilen bir kutunun zindandaki sandıkta olması. Şu anda orayı birkaç serseri işgal etmiş durumda. Ne bizim adamlarımız, ne de Isla Tesoro'danlar.\nHazine avcıları—biri onlara buranın hazinelerle dolu olduğunu söylemiş olmalı. Burada görünmeye cesaret edemezlerdi ama ben de onları görmeye gitmeye korkuyorum, anlıyor musun? Yüzleri...";
			link.l1 = "Anladım. Kapını aç. Davetsiz misafirlerini buradan çıkaracağım.";
			link.l1.go = "clock_6";
		break;
		
		case "clock_6":
			dialog.text = "Bu kadar kolay mı? Onları kovacak mısın? Tek başına? Korkmuyor musun? Sadece iste, bütün yerleşke senin için savaşır...";
			link.l1 = "Daha az laf, daha çok iş, usta. Şu kapıyı aç, gerisini bana bırak. Eşyalarını hangi sandıkta saklıyorsun?";
			link.l1.go = "clock_7";
		break;
		
		case "clock_7":
			dialog.text = "Koridorun hemen sonunda, bir sürü boş tahta fıçı var. Onların arkasında, köşede yerde küçük bir sandık duruyor. Ona bir kilit çaktım, bu yüzden o davetsiz misafirler bulsalar bile kirli ellerini içine sokamazlar diye düşünüyorum. Al, anahtarı burada.";
			link.l1 = "İleriye dönük düşündüğüne sevindim. Burada bekle ve hiçbir yere ayrılma.";
			link.l1.go = "clock_8";
		break;
		
		case "clock_8":
			DialogExit();
			GiveItem2Character(pchar, "key3"); 
			bDisableFastReload = true;//закрыть переход
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", true);//офицеров не пускать
			pchar.quest.Alex_Chest.win_condition.l1 = "location";
			pchar.quest.Alex_Chest.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.Alex_Chest.function = "AlexClock_Chest";
			pchar.quest.AlexClock_Over.over = "yes"; //снять прерывание
			pchar.questTemp.AlexClock = "chest";
			AddQuestRecord("alex_clock", "3");
		break;
		
		case "clock_complete":
			dialog.text = "Sadece seni dinleyip gittiler mi?";
			link.l1 = "Evet, doğru. Oldukça kibar adamlarmış meğer. Onlara, varlıklarının yaşlı ve saygın bir gemi ustasını korkuttuğunu anlattım, onlar da yaşınıza duydukları saygıdan buradan ayrıldılar. Artık oraya gönül rahatlığıyla inebilirsiniz.";
			link.l1.go = "clock_complete_1";
		break;
		
		case "clock_complete_1":
			dialog.text = "Ha, yaşlı bir adamla dalga geçiyorsun! Peki. Kutumu ver, açayım ve hakkınla kazandığın aleti sana vereyim.";
			link.l1 = "Lütfen, alın...";
			link.l1.go = "clock_complete_2";
		break;
		
		case "clock_complete_2":
			RemoveItems(pchar, "alexs_chest", 1);
			dialog.text = "Teşekkürler! Hadi açalım. Al, bu senin. Otomatik bir mekanik zamanlayıcı— burada kimse böyle bir alet yapmaz, önümüzdeki üç yüz yıl da kimse yapmayacak... ah, affedersin, yaşlı bir adamı bağışla. Demek istediğim, bu alet gerçekten eşsiz.\nTüm işi kendi yapıyor, o saçma kum saatlerine falan ihtiyacın kalmayacak. Hata yok! Sadece doğrudan darbelere ve suya karşı koru, yoksa kaybedersin. Bunu bir maymun bile kullanabilir.";
			link.l1 = "Şuna bak! Hayatımda böyle mucizevi bir şey görmedim! Teşekkür ederim, usta.";
			link.l1.go = "clock_complete_3";
		break;
		
		case "clock_complete_3":
			GiveItem2Character(pchar, "clock3");
			Log_Info("You've received an automatic mechanical timer");
			SetAlchemyRecipeKnown("sextant2");
			PlaySound("interface\important_item.wav");
			dialog.text = "Rica ederim. Artık saatin kaç olduğunu her zaman bileceksin. Nereden bulduğumu sorma, söylemem.";
			link.l1 = "Herkesin sırları vardır, değil mi, usta? Peki... sırlarını kendine sakla, işine karışmam. Hediye için teşekkürler!";
			link.l1.go = "clock_complete_4";
		break;
		
		case "clock_complete_4":
			dialog.text = "Yardımınız için teşekkür ederim, Kaptan. Bir ara uğrayın bana. Eski bir gemi ustasını unutmayın.";
			link.l1 = "Seni unutacakmışım gibi... Neyse, bunu kesinlikle yapacağım, Usta Alexus. Hoşça kal!";
			link.l1.go = "clock_complete_5";
		break;
		
		case "clock_complete_5":
			DialogExit();
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", false);
			LocatorReloadEnterDisable("Bermudes_Dungeon", "reload2_back", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", false);
			AddQuestRecord("alex_clock", "5");
			CloseQuestHeader("alex_clock");
			DeleteAttribute(pchar, "questTemp.AlexClock");
			// belamour legendary edition на пару с Акулой
			pchar.questTemp.SharkGoldFleet.KGBB = true;
			if(CheckAttribute(pchar,"questTemp.SharkFrigate")) SetTimerCondition("SharkGoldFleet", 0, 0, 30, false);
		break;
	// <-- хронометр Алекса
		
		// город майя
		case "tieyasal":
			dialog.text = "Aha, Miguel! Eski tanıdığım. Onu hatırlıyorum. Her ayrıntıyı tekrar tekrar sormuştu bana. Ama daha basit bir telgrafı bile görmemişken, ona bir radyonun içinin nasıl yapıldığını nasıl anlatacaktım ki?";
			link.l1 = "Ne?.. Ne diyorsunuz, usta?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Ah, affedersin delikanlı. Lafıma pek aldırma... Meraklı Michel'imiz merakını giderdi ve ortadan kayboldu. Daha üç gün önce sohbet etmiştik.";
			link.l1 = "Şu anda Miguel nerede, sormamda bir sakınca yoksa?";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Kim bilir. Belki Sharptown'da işlerinin başındadır, ya da belki de Isla Tesoro'dan çoktan ayrılmıştır.";
			link.l1 = "Anladım. Teşekkür ederim, usta!";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Калеуче
		case "FDM":
			if(CheckAttribute(npchar, "quest.FDM_secondtime"))
				dialog.text = "Yine şu 'hayalet gemi' meselesi... Şunu bil ki, onunla sadece düzgün bir şeye dönüşür ümidiyle uğraşıyorum. Yoksa elimi bile sürmezdim. Denizdeki herkesin de benzer düşündüğüne eminim. Bu sefer onunla ne yapmak istiyorsun?";
			else	
				dialog.text = "Ah, şu 'hayalet gemi'! Anneler yaramaz çocukları korkutmak için senin kalyonunu anlatıyor. Ve sen de o lanetli tekneyi batırmak yerine elinde tutmaya karar verdin! Denizciler, ufukta gemini gördüklerinde titriyor... Peki, onunla ne yapmak istiyorsun?";
			/*if (!CheckAttribute(npchar, "quest.FDM_cabin"))
			{
				link.l1 = "Korkudan ödleri patlayan küçük korkaklar fikri hoşuma gidiyor. Ama içi beni üzüyor. Kamaranın halini gördün mü? Tabut gibi hissettiriyor. Her yer küf ve toz içinde. Bunu düzeltmek istiyorum. Usta, bunu yapabilir misin?";
				link.l1.go = "FDM_cabin";
			}
			if (!CheckAttribute(npchar, "quest.FDM_sails"))
			{
				link.l2 = "Bu yırtık siyah paçavralardan bıktım artık. Kabul ediyorum, normal yelkenler kadar rüzgarı yakalıyorlar ama görüntüsü... İğrenç. Ben sıradan, bembeyaz yelkenler istiyorum. Var mısın, usta?";
				link.l2.go = "FDM_sails";
			}*/
			
			if (!CheckAttribute(npchar, "quest.FDM_hull"))
			{
				link.l3 = "Bence artık ona layık bir şey yapmanın zamanı geldi. Gemi iyi, mürettebatı da alışkın, ama saygın bir kaptanın yetişkinleri bile ödü koparacak bir gemide dolaşması hiç yakışık almaz. Onu tamamen baştan inşa ettirmek istiyorum ki, diğer kaptanlar gemimi gördüklerinde kendilerini korumaya çalışmak yerine imrenerek baksınlar. Böylesi bir iş için de, takımadaların en iyi gemi ustasından başkasına başvurmak olmazdı zaten, değil mi?";
				link.l3.go = "FDM_hull";
			}
		break;
		
		case "FDM_cabin":
			dialog.text = "Neden olmasın? Ellerim hâlâ sağlam.";
			link.l1 = "...";
			link.l1.go = "FDM_cabin_s";
			//link.l2 = "Gereksiz lükse gerek yok. Standartları koruyun.";
			//link.l2.go = "FDM_cabin_s";
		break;
		
		case "FDM_cabin_m":
			dialog.text = "Pekâlâ. On sandık dublon ve işin beş günde bitecek.";
			link.l1 = "Anlaştık!";
			link.l1.go = "FDM_cabin_m1";
			link.l2 = "On sandık mı? Bin beş yüz doblon mu? Hm, böyle bir harcamayı düşünmem için zamana ihtiyacım var...";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_s":
			dialog.text = "Yedi sandık dublon ve iş beş günde biter.";
			link.l1 = "Anlaştık!";
			link.l1.go = "FDM_cabin_s1";
			link.l2 = "Yedi sandık mı? Binlerce dublon mu? Hm, böyle bir masrafı düşünmem için zamana ihtiyacım var...";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_m1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin = 10;
			npchar.quest.FDM_cabin.type = "Cabin_Huge";
			dialog.text = "İyi, ödemeyi bekliyor olacağım.";
			if (iTemp > 0)
			{
				link.l1 = "Yanımda sandıklar var. Bakalım. Buyurun, "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "Sandıkları doldurmak için gitmem gerek.";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_s1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin.chest = 7;
			npchar.quest.FDM_cabin.type = "Cabin";
			dialog.text = "Pekala, ödemeyi bekliyor olacağım.";
			if (iTemp > 0)
			{
				link.l1 = "Yanımda sandıklar var. Bakalım. Buyurun, "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "Sandıkları doldurmak için gidip paraları koymam gerek.";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_wait":
			DialogExit();
			npchar.quest.FDM_full = "cabin";
		break;
		
		case "FDM_cabin_pay":
			iTemp = GetCharacterItem(pchar, "Chest");
			amount = sti(npchar.quest.FDM_cabin.chest)-iTemp;
			Log_Info("You have given chests to Master Alexus");
			PlaySound("interface\important_item.wav");
			if (amount <= 0) // всё принес
			{
				RemoveItems(pchar, "chest", sti(npchar.quest.FDM_cabin.chest));
				dialog.text = "Yani, beni buraya getirmek zorunda mıydın "+FindRussianQtyString(sti(npchar.quest.FDM_cabin.chest))+" sandıkları getirdiniz "+FindRussianQtyString(iTemp)+"Parayı getirdim. Şimdi sıra bende. Git biraz dolaş. Merak etme, elimden gelenin en iyisini yapacağım.";
				link.l1 = "İyi...";
				link.l1.go = "FDM_cabin_do";
			}
			else
			{
				RemoveItems(pchar, "chest", iTemp);
				dialog.text = "Demek ki, beni buraya getirmek zorunda kaldın "+FindRussianQtyString(sti(npchar.quest.FDM_cabin.chest))+" sandıkları getirdiniz "+FindRussianQtyString(iTemp)+". "+FindRussianQtyString(amount)+" sandık kaldı.";
				link.l1 = "Pekala, usta.";
				link.l1.go = "FDM_cabin_wait";
				npchar.quest.FDM_cabin.chest = amount;
			}
		break;
		
		case "FDM_cabin_do":
			DialogExit();
			SetLaunchFrameFormParam("Five days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.CabinType = npchar.quest.FDM_cabin.type;
			if (CheckAttribute(npchar, "quest.FDM_sails")) npchar.quest.FDM_full = "done";
			else DeleteAttribute(npchar, "quest.FDM_full");
			npchar.quest.FDM_cabin = "done";
		break;
		
		case "FDM_sails":
			dialog.text = "Elbette, bunu yapabilirim! Bakalım... Bu, bütün eski, kirli bezleri atıp yerine pamuktan yeni, tertemiz yelkenler takmamız gerekecek demek. Burada yapılacak çok iş var. İşçilik ve malzeme için yüz bin peso. Anlaştık mı?";
			if (sti(Pchar.money) >= 100000)
			{
				link.l1 = "Tabii, bu bana uyar. Anlaştık!";
				link.l1.go = "FDM_sails_do";
			}
			link.l2 = "Hm. Sanırım bunu biraz düşünmem gerekecek...";
			link.l2.go = "exit";
		break;
		
		case "FDM_sails_do":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "Güzel. Paralar bende, işimi yapma zamanı. Bitene kadar etrafta dolaş ve endişelenme.";
			link.l1 = "İyi...";
			link.l1.go = "FDM_sails_done";
		break;
		
		case "FDM_sails_done":
			DialogExit();
			SetLaunchFrameFormParam("Two days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//белый хлопковый парус
			npchar.quest.FDM_sails = "true";
			if (CheckAttribute(npchar, "quest.FDM_cabin")) npchar.quest.FDM_full = "done";
		break;
		//--> Xenon
		case "FDM_hull":
			dialog.text = "Nihayet bunu duyduğuma sevindim. Ve gerçekten de öyle - iyi bir insana benziyorsun ama neyle denize açıldığın Allah bilir. Fakat baştan söyleyeyim, bu iş öyle birkaç saatlik değil ve sana epey pahalıya patlayacak. ";
			link.l1 = "Peki, biraz daha ayrıntılı olabilir misiniz?";
			link.l1.go = "FDM_hull_01";
		break;

		case "FDM_hull_01":
			dialog.text = "Alright, let's do the math... For a full rebuild of the ship's hull I'll need 150 units each of bakaut, ropes, ship silk and resin — and 10,000 gold doubloons. Don't look at me like that; most of the money will go on materials. This job is equivalent to dismantling the ship and building it again from scratch.";
			link.l1 = "Hayır, sanmıyorum. Yeniden inşa için bu kadar çok kaynağı getirip bir yığın altını teslim etmeye hazır değilim. Elimdekilerle idare edeceğim.";
			link.l1.go = "FDM_hull_thinking";
			link.l2 = "Eh, gemimiz için neler yapmayız ki... Peki, anlaştık.";
			link.l2.go = "FDM_hull_02";
		break;

		case "FDM_hull_02":
			dialog.text = "Pekâlâ, lafı fazla uzatmayalım, işe bakalım. Gerekli her şeyi almaya başlayabilmem için senden parayı bekleyeceğim. Para elime geçince, malzemeleri bana getirmeye başlayabilirsin. Sonra da gemin üzerinde çalışmaya koyulurum.";
			if(PCharDublonsTotal() >= 10000)
			{
    			link.l1 = "Para sorun değil. Yanımda var. Alın, usta.";
    			link.l1.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "Şu anda o kadar param yok. Biraz bekle, sana getireceğim.";
    			link.l1.go = "FDM_hull_waitmoney";
            }
		break;

		case "FDM_hull_waitmaterials":
			RemoveDublonsFromPCharTotal(10000);
			npchar.quest.FDMsandal = 0;
			npchar.quest.FDMoil = 0;
			npchar.quest.FDMshipsilk = 0;
			npchar.quest.FDMropes = 0;
			AddQuestRecord("renovate_fdm", "1");

			npchar.quest.FDM_hull = "hull_waitmaterials";
			dialog.text = "Böyle yüklü bir parayla korsan kasabasında dolaşmaktan korkmuyor musun, hehe? Şaka yapıyorum tabii, buradakiler kendince dürüst insanlardır. Şimdi malzemeleri bekliyorum. Hatırlatmak isterim, toplamda 150 demir ağacı, 150 halat, 150 gemi ipeği ve 150 varil reçine getirmelisin.";
			link.l1 = "Dayan, malzemelerini getireceğim.";
			link.l1.go = "exit";
		break;

		case "FDM_hull_checkmaterials":
			dialog.text = "Çok güzel! Bugün bana ne getirdiniz?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && sti(npchar.quest.FDMsandal) < 150)
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "Demir ağaç miktarı olarak "+FindRussianQtyString(iSan)+".";
				link.l1.go = "FDM_sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && sti(npchar.quest.FDMoil) < 150)
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "Reçine miktarı "+FindRussianQtyString(iOil)+".";
				link.l2.go = "FDM_oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && sti(npchar.quest.FDMshipsilk) < 150)
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "Belirtilen miktarda ipek gemiye yüklensin "+FindRussianQtyString(iSil)+".";
				link.l3.go = "FDM_shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && sti(npchar.quest.FDMropes) < 150)
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "Gerekli miktarda halat "+FindRussianQtyString(iRop)+".";
				link.l4.go = "FDM_ropes";
			} 
			link.l5 = "Henüz bir şey yok. Sadece anlaşmanın hâlâ geçerli olduğundan emin olmak istedim.";
			link.l5.go = "exit";
		break;

		case "FDM_hull_checkmaterials_1":
			if (sti(npchar.quest.FDMsandal) > 149 && sti(npchar.quest.FDMoil) > 149 && sti(npchar.quest.FDMshipsilk) > 149 && sti(npchar.quest.FDMropes) > 149)
			{
				dialog.text = "Harika! Tüm malzemeler eksiksiz. Şimdi, o canavarı senden teslim alayım. Sonunda hak ettiği gibi görünecek.";
				link.l1 = "Pekala, yeterince homurdandınız usta. Sonucu sabırsızlıkla bekliyorum.";
				link.l1.go = "FDM_hull_building";
			}
			else
			{
				dialog.text = "Gününümü aydınlatacak başka bir şeyin var mı, Kaptan?";
				link.l1 = "Ne yazık ki, şimdilik bu kadar.";
				link.l1.go = "exit";
				link.l2 = "Evet, senin için başka bir şeyim daha var...";
				link.l2.go = "FDM_hull_checkmaterials";
			}
		break;

		case "FDM_sandal": // бакаут
			amount = 150 - sti(npchar.quest.FDMsandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) 
			{
				dialog.text = "Bakalım... Benim ihtiyacım olan "+FindRussianQtyString(amount)+" demir ağacından. Getirdin "+FindRussianQtyString(iSan)+". demir ağacı. Bu yüzden, bana hâlâ getirmelisin "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Teşekkürler! Kalanını yakında getireceğim.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + iSan;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ironwood");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Bakalım... Hâlâ ihtiyacım var "+FindRussianQtyString(amount)+" demir ağacından. Bana getirdin  "+FindRussianQtyString(iSan)+" .  Yani, demir ağacıyla işimiz bitti!";
				link.l1 = "Teşekkürler!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ironwood"); 
			}
		break;

		case "FDM_oil": // смолы
			amount = 150 - sti(npchar.quest.FDMoil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) 
			{
				dialog.text = "Bakalım... Benim ihtiyacım olan "+FindRussianQtyString(amount)+" reçine getirdiniz. "+FindRussianQtyString(iOil)+" . Bu yüzden, bana hâlâ getirmelisin "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Teşekkürler! Kalanını yakında getireceğim.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				npchar.quest.FDMoil = sti(npchar.quest.FDMoil) + iOil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "resin");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Bakalım... Hâlâ ihtiyacım var "+FindRussianQtyString(amount)+" reçine getirdin bana "+FindRussianQtyString(iOil)+" .  Yani, reçineyle işimiz bitti!";
				link.l1 = "Teşekkürler!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.FDMoil = makeint(npchar.quest.FDMoil) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "resin");
			}
		break;

		case "FDM_shipsilk": // шёлк
			amount = 150 - sti(npchar.quest.FDMshipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) 
			{
				dialog.text = "Bakalım... Benim ihtiyacım olan şey "+FindRussianQtyString(amount)+" gemi ipeği. Getirmişsin "+FindRussianQtyString(iSil)+" . Bu yüzden, bana hâlâ getirmelisin "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Teşekkürler! Kalanını yakında getireceğim";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + iSil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ship silk");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Bakalım... Hâlâ ihtiyacım var "+FindRussianQtyString(amount)+" gemi ipeği . Bu yüzden , bana hâlâ getirmelisin "+FindRussianQtyString(iSil)+" .  Yani, gemi ipeği işiyle işimiz bitti ";
				link.l1 = "Teşekkürler!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ship silk"); 
			}
		break;

		case "FDM_ropes": // канаты
			amount = 150 - sti(npchar.quest.FDMropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) 
			{
				dialog.text = "Bakalım... Benim ihtiyacım olan şey "+FindRussianQtyString(amount)+" halatlar. Getirdiniz "+FindRussianQtyString(iRop)+" . Bu yüzden, bana hâlâ getirmelisin "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Teşekkürler! Kalanını yakında getireceğim";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + iRop;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ropes");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Bakalım... Benim ihtiyacım olan  "+FindRussianQtyString(amount)+" halat getirdin. "+FindRussianQtyString(iRop)+" .  Yani, halatlarla işimiz bitti!";
				link.l1 = "Teşekkürler!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ropes");
			}
		break;

		case "FDM_hull_thinking":
			DialogExit();
			npchar.quest.FDM_secondtime = true;
		break;

		case "FDM_hull_waitmoney":
			DialogExit();
			npchar.quest.FDM_hull = "hull_waitmoney";
		break;

		case "FDM_hull_givemoney":
			dialog.text = "Peki, parayı getirdin mi";
			if(PCharDublonsTotal() >= 10000)
			{
    			link.l2 = "Evet, getirdim. Anlaştığımız gibi, 10.000 tam ağırlığında dublon.";
    			link.l2.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "Henüz değil, bekle usta.";
    			link.l1.go = "exit";
            }
		break;

		case "FDM_hull_building":
			DialogExit();
			SetLaunchFrameFormParam("Five days passed..."+ NewStr() +"Master Alexus completed the job", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //Pass time
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			
			shTo = &RealShips[sti(pchar.Ship.Type)];
			object newShip;
			aref arTuning;
			CopyAttributes(&newShip, shTo);
			
			pchar.Ship.Type = GenerateShipExt(SHIP_RENOVATED_FDM, 0, pchar);
			
			if(CheckAttribute(newShip, "Tuning"))
			{
				makearef(arTuning, newShip.tuning);
				for (int iQty = 0; iQty < GetAttributesNum(arTuning); iQty++)
				{
					aref realTuning = GetAttributeN(arTuning, iQty);
					string tuningName = GetAttributeName(realTuning);
					UpgradeShipParameter(pchar, tuningName);
				}
			}
			if(CheckAttribute(newShip, "Traits")) RealShips[sti(pchar.Ship.Type)].Traits = newShip.Traits;
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//White cotton sail
			pchar.ship.hp = GetCharacterShipMaxHP(pchar);
			DeleteAttribute(pchar, "ship.hulls");
			DeleteAttribute(pchar, "ship.blots");	
			CloseQuestHeader("renovate_fdm");
			Achievment_Set("ach_CL_178");
		break;
		//<-- Xenon
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
