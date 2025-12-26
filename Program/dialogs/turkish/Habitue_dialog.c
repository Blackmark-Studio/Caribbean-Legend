#include "DIALOGS\%language%\Common_Duel.c" //navy
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
    ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting, TempInfoCharacterID_1, TempInfoCharacterID_2, sQuestTitle, sStr;
	int DonationSize;
    	
	// Warship 18.05.08
	int iLa_Puesta; // La puesta - это ставка по-испански
    	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
    ProcessCommonDialogRumors(NPChar, Link, Diag);//homo 25/06/06
    ProcessDuelDialog(NPChar, Link, Diag); //navy

	int iEnemyDice, iPCDice;
	int d1,d2,d3,d4;
	bool ok;
    ref sld;
    
	if (npchar.quest.Meeting != LastSpeakDate())
	{
		npchar.quest.Meeting = LastSpeakDate();
		npchar.money = 100 + rand(10) * makeint(50 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
		if (sti(npchar.money) < 150) npchar.money = 150;
        if (bBettaTestMode)
        {
            Dialog.CurrentNode = "Beta_test";
        }
	}
	switch (Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

        case "Beta_test":
            dialog.text = "Sarhoş tipi seçimi (beta)";
			link.l1 = "Sarhoş";
			link.l1.go = "Beta_test_alc";
            link.l2 = "Kumarbaz";
			link.l2.go = "Beta_test_card";
			link.l3 = "Zar kumarbazı";
			link.l3.go = "Beta_test_dice";
		break;
		
		case "Beta_test_alc":
            dialog.text = "Sarhoş seçildi";
			link.l1 = "Devam Et";
			link.l1.go = "First time";
			npchar.quest.last_theme = 0;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_card":
            dialog.text = "Kumarbaz (hemen alınma ihtimali %30)";
			link.l1 = "Devam Et";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_dice":
            dialog.text = "Zar kumarbazı (hemen alınma olasılığı %30)";
			link.l1 = "Devam Et";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 1;
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = LinkRandPhrase("Belki sarhoşum ama aptal değilim. Şimdi seninle içersem, ertesi gün askerler beni yakalar. Asla olmaz!","Ben kendi şehrimin düşmanı değilim. Seninle içmem!",""+GetSexPhrase("dostum","kız")+", buradan hâlâ gidebiliyorken gitmen senin için daha iyi olur...");
				link.l1 = RandPhraseSimple("Peki, nasıl istersen...","Heh, biliyor musun, o kadar sarhoş olmama gerek yok. Şu an bunun zamanı değil."); 
				link.l1.go = "exit";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.HabitueSpeakDisable") && rand(1) == 0) // если дуэлянт то каждый второй посылает нафик
			{
				dialog.text = "Ha, hanımefendi"+GetSexPhrase("ter","s")+"Elbette, senin adını duydum, hehe. Meyhanelerde senin baş belası ve düellocu olduğunu söylüyorlar. Bizim buraların insanı kolay kolay korkmaz ama kimse bir bardak rom için canından olmak istemez. Yanında oturmak bile huzurumu kaçırıyor, o yüzden ben pas geçeyim.";
				link.l1 = LinkRandPhrase("İyi ki defolup gittin, o zaman!","Defol git, hâlâ keyfim yerindeyken...","Yürü git! Kaybol, balık yemi!");
				link.l1.go = "exit";
				link.l2 = "Bekle, bir soru sormak istemiştim...";
				link.l2.go = "talk_habitue_duel";
				break;
			}
			
            ok = CheckFreeSitFront(npchar);
            
            dialog.text = "Işığımı kesme, kupadaki sinekleri göremiyorum!";
            link.l1 = "Ben ayakta durmuyorum...";
		    link.l1.go = "exit";
		    if (!chrDisableReloadToLocation)
		    {
	            switch (npchar.quest.last_theme)
				{
					case "0": //пьяный.
						dialog.text = "Hik! Ah, "+GetSexPhrase("dostum, kesinlikle deneyimli bir deniz kurdu gibi görünüyorsun"," kızım, sen kesinlikle tecrübeli bir deniz kurdu gibi görünüyorsun")+" ! Belki bana bir kadeh rom ısmarlarsın? ";
						link.l1 = "Belki yaşlı bir deniz kurdu olabilirim, ama bu, ayaktakımına içki ısmarlayacağım anlamına gelmez...";
						link.l1.go = "exit";

						if (makeint(pchar.money) >= 100 && ok) // только старые острова окучены на сесть
						{
							link.l2 = "Sizinle birlikte olmaktan memnuniyet duyarım.";
							link.l2.go = "talk_with_alchogol";
						}
						else
						{
	                        link.l2 = "Ve neden böyle?";
							link.l2.go = "talk_with_alchogol_song";
						}
					break;

					case "1":
	                    if (rand(3) != 1 && ok)
	                    {
							switch (sti(npchar.quest.last_theme_game))
							{
							    case 0 :
									// Игра в карты boal 20/05/05 -->
	                                if (CheckNPCQuestDate(npchar, "Card_date_begin"))
									{
										Dialog.text = RandPhraseSimple("Belki bir kart oyunu? Oldukça ilginç bir oyun!","Biraz kart oynayalım derim. Ne dersin?");
										link.l1 = "Ve neden olmasın? Tabii, oynayalım.";
										link.l1.go = "Cards_begin";
										link.l2 = "Peki oyununuzun kuralları neler?";
										link.l2.go = "Cards_Rule";
										link.l3 = "Şimdi değil.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "Hayır, artık seninle kart oynamıyorum.";
						    			link.l1 = "Dediğiniz gibi.";
						    			link.l1.go = "exit";
									}
			                        // Игра в карты boal 20/05/05 <--
		                        break;

								case 1:
								// кости
		    						// Игра в кости boal 13/07/05 -->
	                                if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
									{
										Dialog.text = RandPhraseSimple("Belki bir zar oyunu? Çok ilginç bir oyun!","Biraz zar atalım derim. Ne dersin?");
										link.l1 = "Ve neden olmasın? Tabii, oynayalım.";
										link.l1.go = "Dice_begin";
										link.l2 = "Peki oyununuzun kuralları nedir?";
										link.l2.go = "Dice_Rule";
										link.l3 = "Şimdi değil.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "Hayır, artık seninle zar oynamıyorum.";
					    				link.l1 = "Dediğiniz gibi.";
					    				link.l1.go = "exit";
									}
			                        // Игра в кости boal 13/07/05 <--
			                        //navy --> Дуэли
									if (CheckAttribute(NPchar, "Quest.DiceCheats") && sti(NPchar.Quest.DiceCheats) >= 1) 
									{
					    				link.l9 = RandSwear()+" Hile yapıyordun!!!";
					    				link.l9.go = "outraged";
									}
									//navy <--
			    				break;
	    					} 
						}
	        			else
	        			{
	                        dialog.text = RandPhraseSimple("Masamdan uzak dur! Hemen!"," Ha? Ne? Kim o? Hık... Defol git!");
	                        link.l1 = RandPhraseSimple("İçki, günahkâr ruhunu mahveder! Kendine gel!","Bana kaba davranma.");
	        			    link.l1.go = "exit";
	        			    link.l2 = RandPhraseSimple("Diline dikkat et, köpek herif! Yoksa sana biraz edep öğretirim.","Şimdi kafana bir tane indirsem, ayılmana yardımcı olur herhalde.");
	        	            link.l2.go = "tavern_keeper";
	        			}
					break;
				}
			}
			Diag.TempNode = "First time";
	    break;
	    
		case "talk_habitue_duel":
			dialog.text = "Sana hiçbir şey söylemeyeceğim, hanımefendi"+GetSexPhrase("ter","s")+"!   Ve sanmıyorum ki başkası da seninle konuşmak isteyecek, çünkü bu her zaman bela demek. Ama biliyorsun, insanların hafızası kısa olur, bir iki aya maceranı unutabilirler, tabii sen tekrar hatırlatmazsan, he-he! Hoşça kal, mis"+GetSexPhrase("ter","s")+". ";
			link.l1 = "Pekala...";
			link.l1.go = "exit";
		break;
		
	    // карты -->
	    case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Pekâlâ, o zaman başlayalım...";
			link.l1.go = "Cards_begin";
			link.l3 = "Hayır, bu bana göre değil...";
			link.l3.go = "exit";
		break;
		
		case "Cards_begin":
			Diag.tempnode = "Cards_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Cards_Node":
			Diag.tempNode = "first time";

			Dialog.text = "Önce bahsi belirleyelim o zaman (bahsi girin).";
			link.l1 = "100";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l3 = "Sanırım gitmem gerekiyor.";
			link.l3.go = "exit_sit";
		break;
		
		case "Cards_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "Sen namlı bir hilesincisin. Seninle kumar oynamam.";
                link.l1 = "Hepsi yalan! Neyse, her neyse.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		    
			if (sti(PCHar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "Parasız olduğunu görüyorum, "+GetSexPhrase("arkadaş","sevgilim")+". Zengin olduğunda geri gel.";
                link.l1 = "Pekâlâ.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		
			if (sti(NPChar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "Zaten sahip olduğum her şeyi kaybettim. Bugün şanslı günüm değil.";
                link.l1 = "Pekâlâ.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Benimle dalga mı geçiyorsun yoksa ne?! Oynuyor musun "+iLa_Puesta+" pesos mu? Makul bir miktar için oynayalım, yoksa ben yokum!";
				link.l1 = "Evet, haklısın. Biraz daha büyük oynamamız lazım.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "Fikrimi değiştirdim, oynamıyorum.";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Bu kadar büyük meblağlar için mi oynuyorsun? Hayır, ben yokum, ancak bahsi değiştirirsek belki.";
				link.l1 = "Evet, haklısın. Bahsi biraz düşürmemiz lazım.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "Aslında, hiç oynamamaya karar verdim.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Pekala, o zaman oynayalım "+iLa_Puesta+" madeni paralar.";
			link.l1 = "Kartları dağıt!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Cards.SitType   = true;
		}
		break;
		
		case "Cards_begin_2":
			dialog.text = "Peki, bahis ne? (Bahsi girin)";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l2 = "Sanırım sonunda oynamayacağım...";
			link.l2.go = "exit_sit";
		break;
							
		case "Cards_begin_go":
            // анлим игры в день SetNPCQuestDate(npchar, "Card_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--
	    // КОСТИ -->
	    case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "Pekala, o zaman başlayalım...";
			link.l1.go = "Dice_begin";
			link.l3 = "Hayır, bu bana göre değil...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Diag.tempnode = "Dice_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Dice_Node":
		    Diag.tempNode = "first time";		    
			Dialog.text = "Bahsi koyalım (bahsi girin).";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l3 = "Sanırım gitmem gerekiyor.";
			link.l3.go = "exit_sit";
		break;

		case "Dice_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckDiceGameSmallRate())
		    {
				dialog.text = "Sen nam salmış bir hilesin. Seninle zar atmam.";
                link.l1 = "Hepsi yalan! Neyse, boşver.";
			    link.l1.go = "exit_sit";
			    break;
		    }

			if (sti(pchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "Parasız kaldığını görüyorum, "+GetSexPhrase("arkadaş","sevgilim")+". Zengin olduğunda geri gel.";
                link.l1 = "Pekala.";
			    link.l1.go = "exit_sit";
			    break;
		    }
			
			if (sti(npchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "Zaten sahip olduğum her şeyi kaybettim. Bugün şanslı günüm değil.";
                link.l1 = "Pekala.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Benimle dalga mı geçiyorsun yoksa ne?! Oynuyor musun "+iLa_Puesta+" peso mu günde?! Makul bir bahiste oynayalım, yoksa ben yokum!";
				link.l1 = "Evet, haklısın. Bahisleri biraz yükseltmemiz lazım.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "Fikrimi değiştirdim, oynamıyorum.";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Böylesine büyük bir meblağ için zar atmak mı? Hayır, ben yokum, ancak bahsi değiştirirsek belki.";
				link.l1 = "Evet, haklısın. Bahsi biraz düşürmemiz lazım.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "Aslında, hiç oynamamaya karar verdim.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Pekala, o zaman oynayalım "+iLa_Puesta+" zar başına madeni para.";
			link.l1 = "Hadi başlayalım!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Dice.SitType   = true;
		}
		break;
		
		case "Dice_begin_2":
			dialog.text = "Peki, bahis ne? (Bahsi girin)";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l2 = "Sanırım sonunda oynamayacağım...";
			link.l2.go = "exit_sit";
			break;

		case "Dice_begin_go":
            // анлим игры в день SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // КОСТИ <--

		/////////////////////////////////////////////
        case "talk_with_alchogol_song":
			dialog.text = "Şey, h-hıç! Her şey yolunda. Hıç! Hiç beklemezsin. Hı-ıç! Bu rom harika. Jamaika siyah romu. hıç!\nAl, kendine de bir kadeh doldur!";
			link.l1 = "Pekâlâ, neden olmasın.";
			link.l1.go = "talk_with_alchogol_song_2";
			link.l2 = "Üzgünüm dostum, gitmem gerek.";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_2":
			dialog.text = "Bardaklar ve yüzler gelip geçiyor... Hık... Ta ki yere düşene kadar. Sürekli içiyorum... Hık! Nerede bu içki... Ve bunun anlamı ne...";
			link.l1 = "İçki burada, kızlar güzel, hepsi bir korsan ister ama bana kalan sadece rom gibi görünüyor.";
			link.l1.go = "talk_with_alchogol_song_3";
			link.l2 = "Bunun için vaktim yok.";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_3":
			dialog.text = "Ne zaman üzgün olsan, düşünmeye çalışma, bize katıl, birlikte içelim! Her şey elbet yoluna girecek, ben senin dostunum, sen de benim!";
			link.l1 = "Bir dosta sahip olmak gerçekten harika, sen yokken o seni bekler, dostlukta kin olmaz, ama rom bitti mi geriye sadece tartışma kalır. O yüzden hadi içelim dostum, yoksa geç kalacağım... ";
			link.l1.go = "exit";
		break;
		
		case "talk_with_alchogol":
			Diag.TempNode = "begin_sit";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "begin_sit":
			Diag.TempNode = "first time";
			dialog.snd = "Voice\HADI\HADI028";
			dialog.text = LinkRandPhrase("Hıç! İşte şimdi oldu! Çok daha iyi oldu! Ee? Bana biraz rom alacak mısın, yoksa ne?","Otur, "+GetAddress_Form(npchar)+", hadi gel, eski güzel Jamaika romundan bir bardak yuvarlayalım. Sağlığa hiçbir zararı olmaz. Eğer buralarda neler olup bittiğini merak ediyorsan - bundan iyi bir yer bulamazsın, sana garanti ederim. Biraz para, birkaç kadeh düzgün rom - bilmek istediğin her şeyi, hatta fazlasını öğrenirsin, yaşlı bir müdavime güven...","Heh, lütfen, oturun, "+GetSexPhrase("canım dostum","özlemek")+", hadi bir içki içelim... Neden iyi bir sohbet eşliğinde bir içkiyle keyif yapmayalım? Eğer sabırlı olur ve yavaş yavaş, küçük yudumlarla içersen, çok ilginç şeyler duyabilirsin... Maceralarını ballandıra ballandıra anlatan kaptanlar var, bir de kendini kaybedince ağzından önemli şeyler kaçıranlar... Orada vakit geçiren çok insan var, ve çoğunun anlatacak bir hikayesi var, bana güven, "+GetSexPhrase("canım dostum","Hanımefendi")+".");
			link.l1 = "Ve neden olmasın! Barmen! İkimize de rom getir!";
			link.l1.go = "sit_2";
		break;

		// Церковный генератор. Квест №2 -->
		case "Alcogol_GenQuest_Church_2_1":
			dialog.text = "Tabii! Duydun mu... haydutlar kiliseleri bile yağmalıyormuş!";
				link.l1 = "Eh, bu korsanlardan başkası olamaz...";
				link.l1.go = "Alcogol_GenQuest_Church_2_2";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash");
			break;
			
		case "Alcogol_GenQuest_Church_2_2":
			dialog.text = "Hangi korsanlar? Bildiğin karacılar işte, kesin yine şu lanet yerel tipler... Dışarıdan olsalar, kilisenin kasasının ne zaman dolu olduğunu bilmezlerdi. Zaten o belaya da kolay kolay bulaşmazlardı.";
				link.l1 = "Cesur adamlar, orası kesin. O kadar yiğitçe incecik bir kapı sürgüsünü açtılar ki...";
				link.l1.go = "Alcogol_GenQuest_Church_2_3";
			break;
			
		case "Alcogol_GenQuest_Church_2_3":
			dialog.text = "A-ha. Hem de akıllı olanlar. Kim kendini böyle açığa çıkarır ki?";
				link.l1 = "Doğru. Tüm mahalle kiliseye bağış yapmak için para biriktiriyordu, şimdi bu akıllı adamlar bundan servet mi yaptı? Eminim yakalanacaklar. Artık herkes onları arayacak.";
				link.l1.go = "Alcogol_GenQuest_Church_2_4";
			break;
			
		case "Alcogol_GenQuest_Church_2_4":
			dialog.text = "Pek sayılmaz. Kim onları arayacak ki? Kiliseyi soydular, kasabadan çıktılar, rüzgar gibi kayboldular. Orman kocaman, hem de çok kocaman, onları orada kıyamete kadar ararsın. Birkaç ay sonra da kimse hatırlamaz bile, demedi deme!";
				link.l1 = "Bence hayır. Böyle şeyler affedilemez.";
				link.l1.go = "Alcogol_GenQuest_Church_2_5";
			break;
			
		case "Alcogol_GenQuest_Church_2_5":
			dialog.text = "Bir adamın hafızası sızdıran bir kayık gibidir. İnsanlar unutur ve affeder. Ama Tanrı mı?! O her şeyi görür. Ondan korkman gerekir. Bak, on yıl önce eski bir dostumun başına korkunç bir şey geldi. O da Yaratıcı'ya saygı göstermezdi ve neredeyse doğrudan deniz şeytanına gidecekti...";
				link.l1 = "Üzgünüm dostum, gitmem gerek. O arkadaşını başka bir zaman konuşuruz. Görüşürüz.";
				link.l1.go = "Alcogol_GenQuest_Church_2_6";
			break;
			
		case "Alcogol_GenQuest_Church_2_6":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");			
			string sGenLocation = QuestGetGangLocation(PChar.GenQuest.ChurchQuest_2.QuestTown);
			PChar.GenQuest.ChurchQuest_2.QuestGangJungle = sGenLocation;
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			PChar.GenQuest.ChurchQuest_2.WayOfShortVariant = true; // Нужно для проверки при убийстве банды
			SetFunctionTimerConditionParam("Church_GenQuest2_TimeIsLeft", 0, 0, 1, MakeInt(24 - GetHour()), false);
			Log_TestInfo("The bandits who raided the church shall be in location - " + sGenLocation + " Time to search for them - 1 day");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "2");
			break;
		// <-- Церковный генератор. Квест №2
		//--> работорговец
			case "Jamaica_ratH_1":
				dialog.text = "Oh Francois! Tabii, o adamı hatırlıyorum... Hayır, bilmiyorum. Ama biliyorsun, garsonumuza sorabilirsin onun hakkında. Burada yaşadığı sürece, her geceyi onunla geçirdi. O tam bir kaltak, orası kesin. Belki ona bir şeyler gevezelik etmiştir.";
				link.l1 = " Tavsiyen için sağ ol, dostum. Gidip onunla konuşacağım. ";
				link.l1.go = "exit_sit";
				pchar.questTemp.Slavetrader = "FindRatJamaica_W";
			break;
			
			case "EscapeSlave_Villemstad_H1":
				dialog.text = "Evet, açık denizde bazen gerçekten tuhaf şeyler olabiliyor. Son seferimde öyle bir şey gördüm ki, hakikaten...";
				link.l1 = "Devam et, anlat bakalım, ama çok da abartma. Bu arada sana biraz daha rom getireceğim.";
				link.l1.go = "EscapeSlave_Villemstad_H2";
			break;
			
			case "EscapeSlave_Villemstad_H2":
				dialog.text = "Yemin ederim Tanrı aşkına, asilzade"+GetSexPhrase("efendim","hanımefendi")+" - Kendi gözlerimle gördüm... Bir gemi gidiyordu, ama tayfalar yerine kocaman maymunlar vardı... ya da makaklar... maymun işte, anladın mı.";
				link.l1 = "Ne?! Söylesene dostum, sen de nöbette içiyor musun?";
				link.l1.go = "EscapeSlave_Villemstad_H3";
			break;
			
			case "EscapeSlave_Villemstad_H3":
				dialog.text = "Yalan söylüyorsam gözlerim kör olsun! Hiç maymun karidesini duymadın mı? Kahretsin, karides ha-ha! ... Maymun gemisi.";
				link.l1 = "Hangi maymun gemisi?";
				link.l1.go = "EscapeSlave_Villemstad_H4";
			break;
			
			case "EscapeSlave_Villemstad_H4":
				dialog.text = "Oh-ho, sana söylüyorum, kendi gözlerimle gördüm. Bir fırtına vardı. Hiçbir şey göremiyordum, sonra gemi birdenbire ortaya çıktı. Yırtık yelkenler. Ön yelkeni de, ana yelkeni de kopmuştu, Tanrı şahidim olsun, her şey paramparçaydı! Ama yine de rüzgara karşı ilerliyordu!\nVe güvertesinde maymunlar vardı... hem de bir sürü, fok sürüsü gibi! Ve gerçek bir goril dümenin başında duruyordu! Dokuz ayak boyunda, kırmızı gömlekli, göğsünde haç yerine köpekbalığı dişleri... Gözleri kıpkırmızı parlıyordu, dişleri ışıldıyordu, bizi gördü ve bir şeyler bağırdı...";
				link.l1 = "Yalan söylüyorsun dostum. Sarhoşken insanın gözüne neler neler görünür. Birazdan bana onun Uçan Hollandalı olduğunu da anlatırsın artık.";
				link.l1.go = "EscapeSlave_Villemstad_H5";
			break;
			
			case "EscapeSlave_Villemstad_H5":
				dialog.text = "Hayır, Hollandalı değildi. Sana doğruyu söylüyorum! Bir barçaydı ve kıç tarafında bir yazı vardı - "+pchar.questTemp.Slavetrader.ShipName+".";
				link.l1 = "Kahretsin! Sanırım hangi 'maymunlardan' bahsettiğini şimdi anladım. Gerçekten de, rom insanın dilini çözüyor - sadece dinlemek yeterli...";
				link.l1.go = "EscapeSlave_Villemstad_H6";
			break;
			
			case "EscapeSlave_Villemstad_H6":
				dialog.text = "Bak - sana söylemiştim! Ama bana inanmadın!.. Tamam, hadi son bir kadeh daha içelim, sonra ben hazırım.";
				link.l1 = "Pekala, ilginç hikayen için teşekkürler. Gitmem gerek. Sana bol şans, dostum.";
				link.l1.go = "exit_sit";
				Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1 = "location";
				Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1.location = pchar.questTemp.Slavetrader.Island.Shore;
				Pchar.quest.Slavetrader_EscapeSlave.function = "Slavetrader_EscapeSlaveInShore";
				AddQuestRecord("Slavetrader", "22_4");
				AddQuestUserData("Slavetrader", "sAreal", pchar.questTemp.SlavetraderAreal.add);
				pchar.questTemp.Slavetrader = "FindMayak";
			break;
		
		//Голландский Гамбит, против всех
		case "Lucas_Tavern":
			DelMarkInTavernHWIC();
			dialog.text = "Hayır, kaptan. Denizci hayatı bana göre değil. Bilirsin, benim de bir zamanlar bir gemim vardı, ama... gerçekten çok kötü bir talihsizlik yaşadım.";
			link.l1 = "Dinle - kıyıda alışılmadık bir gemi gördüm, adı 'Meifeng'. Daha önce böyle bir gemi hiç görmedim. Kimin bu gemi? Belki satılıktır? Bir göz atmak isterim.";
			link.l1.go = "Lucas_Tavern_1";
		break;
		
		case "Lucas_Tavern_1":
			dialog.text = "Ha! Hiç sanmam, kaptan. O Çinli adam ne sana ne de başkasına gemisini satar.";
			link.l1 = "Çinli mi? Curacao'da Çinliler var mı? Hem de kendi gemisinin kaptanı olan biri?";
			link.l1.go = "Lucas_Tavern_2";
		break;
		
		case "Lucas_Tavern_2":
			dialog.text = "Gördüğünüz gibi, var. Ama aslında bu onun gemisi değil – Ticaret Şirketi'ne ait. Söylenenlere göre, müdür yardımcısı ve şu anki vali vekili olan mynheer Rodenburg'un gemisiymiş.";
			link.l1 = "Yani, Matthias Beck emekli mi olmuş?";
			link.l1.go = "Lucas_Tavern_3";
		break;
		
		case "Lucas_Tavern_3":
			dialog.text = "Ha! Bayım, gerçekten de arada bir karaya çıkmalı – ya da en azından haberleri takip etmelisiniz. Matthias Beck görevden alındı ve tüm durum netleşene kadar hapse atıldı.";
			link.l1 = "Yok artık! Gerçekten de çok fazla zamanımı denizde geçiriyorum. Peki, bu ne zaman oldu?";
			link.l1.go = "Lucas_Tavern_4";
		break;
		
		case "Lucas_Tavern_4":
			dialog.text = "Actually, just a couple of days ago. A courier brigantine arrived in port. It was not in the best shape; clearly, it had participated in fierce combat. The captain went straight to mynheer Rodenburg with his report, and in just a few hours Matthias Beck was arrested by mynheer Rodenburg and the commandant on suspicion of collaborating with English intelligence.";
			link.l1 = "Korkunç şeyler söylüyorsun. Curacao valisi nasıl İngiliz casusu olabilir?";
			link.l1.go = "Lucas_Tavern_5";
		break;
		
		case "Lucas_Tavern_5":
			dialog.text = "Açıkçası, ben bile buna zor inanıyorum. Yakında Şirket’in direktörü Peter Stuyvesant’ın bizzat buraya geleceğini duydum. Görünüşe göre soruşturmayı kendisi yürütecekmiş.";
			link.l1 = "O zaman haklısınız. Şu anda Mynheer Rodenburg'u rahatsız etmek riskli olabilir.";
			link.l1.go = "Lucas_Tavern_6";
		break;
		
		case "Lucas_Tavern_6":
			dialog.text = "İyi düşündün, kaptan! Özellikle de 'Meifeng' şu anda yükleniyor olduğu için. Güney kıyısına yaptığı yolculuktan yeni döndü ve yakında tekrar denize açılacak. Sana söyleyeyim, orada tuhaf şeyler oluyor. Hollandalı denizciler ve Şirket muhafızları görevden alındı, yerine yeni bir mürettebat toplanıyor. Ve hayatımda içtiğim tüm romlar adına yemin ederim, o yeni gönüllüler bambaşka insanlar, hepsi korsan, haydut ve katil!";
			link.l1 = "Gerçekten bir mucize! Ne yazık ki! Ne güzel bir gemiydi... Kader başka türlü yazılmış demek ki... İlginç hikayen ve haberler için teşekkürler! Seninle konuşmak keyifliydi!";
			link.l1.go = "Lucas_Tavern_7";
		break;
		
		case "Lucas_Tavern_7":
			dialog.text = "Sağ ol kaptan, hem sohbetin hem de romun için! Yine beklerim, uğra mutlaka!";
			link.l1 = "Elbette yapacağım!";
			link.l1.go = "exit_sit";
			AddQuestRecord("Holl_Gambit", "3-44");
			pchar.questTemp.HWIC.Self = "AttackMeifeng";
			//ставим прерывание на выход в море Мейфенг
			pchar.quest.HWIC_Meifeng.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Meifeng.function = "CreateMeifengOnMap";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 12, false); // таймер
			pchar.quest.Meifeng_fail.over = "yes"; //снять прерывание
			Group_DelCharacter("Meifeng_Empty", "Longway");
			Group_DeleteGroup("Meifeng_Empty");//удалить Мейфенг из порта
		break;
		
			//Jason --> поиск дезертира
		case "FindFugitiveHb":
			npchar.quest.fugitive = "true";
			if (npchar.location == pchar.GenQuest.FindFugitive.City+"_tavern" && sti(pchar.GenQuest.FindFugitive.Chance) == 2)
			{
				pchar.GenQuest.FindFugitive.Shore = SelectQuestShoreLocation();
				dialog.text = "Ha! "+pchar.GenQuest.FindFugitive.Name+"? Biliyorum, biliyorum... O meslektaşın pek de sosyal biri değil. Tam bir yalnız kurt, öyle diyelim. Gün boyu adanın kıyısında uzun sandalını sürer, ta ki gece olana kadar. İnsanlar onu balıkçı sanıyor ama aslında inci dalgıcı... Heh! Buna kesinlikle eminim!";
				link.l1 = "Heh! Ee... bana onun nerede olduğunu söyleyebilir misin?";
				link.l1.go = "FindFugitiveHb_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.FindFugitive.Name+"? Hayır, yemin ederim ondan hiç duymadım... Ama sen - Hik! Bizim barmene sorabilirsin, o kesin biliyordur!";
				link.l1 = "Hmm... Peki, biraz daha soruşturacağım. Neyse dostum, eşlik ettiğin için sağ ol. Görüşürüz!";
				link.l1.go = "exit_sit";
			}
		break;
		
		case "FindFugitiveHb_1":
			dialog.text = "Elbette, yapabilirim! Her sabah onu kıyıda bulabilirsin, "+XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen")+".  Mümkün olduğunca erken gel, yoksa yelken açar ve bir sonraki sabaha kadar beklemek zorunda kalırsın.";
			link.l1 = "Teşekkürler! Bana çok yardımcı oldun, dostum! Görüşürüz!";
			link.l1.go = "exit_sit";
			pchar.GenQuest.FindFugitive.Chance = 3; // чтобы никто больше не говорил
			AddQuestRecord("MayorsQuestsList", "12-3");
			AddQuestUserData("MayorsQuestsList", "sShore", XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen"));
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_shore";
			LAi_SetLoginTime(sld, 4.0, 6.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.Shore, "goto", "goto1");
		break;
		//<-- поиск дезертира
		
		// Карибские нравы
		case "trial_spy":
			dialog.text = "Tersanemizde dolaşıp duruyordu, ustalara şunu bunu soruyordu. İşte bu ona pahalıya patladı. Bazı insanlar kasabada şüpheli tiplerin dolaştığını komutana bildirmiş, o da onu gözaltına aldı, sonra da anlaşıldı ki aslında hiç tüccar falan değilmiş.";
			link.l1 = "Sanırım gemi ustanızdan gizli bir projeyi çalmayı planlıyordu?";
			link.l1.go = "trial_spy_1";
		break;
		
		case "trial_spy_1":
			dialog.text = "Kim bilir? Ama eminim ki, o her şeyden önce 'Alacantara' adlı kalyonla ilgileniyordu! Hık! Buna yemin edebilirim! Bu gemiyi bizzat Sayın Vali donatıyor, o yüzden o alçağın onun hakkında bir şeyler öğrenmeye çalıştığına bahse girerim.";
			link.l1 = "Ha! Bu çok olası. Eminim vali ona değerli bir şeyler yükleyecektir...";
			link.l1.go = "trial_spy_2";
		break;
		
		case "trial_spy_2":
			dialog.text = "Bunu söylemeye bile gerek yok! Sana söylüyorum, bu gerçekten dikkate değer bir şey olmalı! Ha, bir de insanlar balıkçıların bu sularda yabancı bir askeri gemi gördüğünü söylüyorlardı... muhtemelen bir fırkateyn. Belki de o casus oradan gelmiştir?";
			link.l1 = "Evet, olabilir... Peki dostum, sohbet için sağ ol ama gitmem gerek!";
			link.l1.go = "exit_sit";
			Trial_Habitue_DlgExit();
		break;
		
		case "sit_2":
			Statistic_AddValue(pchar, "TavernDrink", 1);
			AddMoneyToCharacter(pchar, -2);
			//navy --> Alcohol - rum count;
			if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
			{
				if (CheckAttribute(pchar, "questTemp.Rum"))
				{
					pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
				}
				else pchar.questTemp.Rum = 1;
			}
			else 
			{
				if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
			}				
			//<-- navy
			if(!CheckAttribute(pchar, "questTemp.TimeLock")) WaitDate("",0,0,0, 0, 30);
			
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
			
			// Sinistra - Квест "Путеводная звезда" ==>
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerAlkash") && npchar.city == "baster")
			{
				dialog.text = "Sağlığınıza ve cömertliğinize!";
				link.l1 = "Dostum, kasabada Çinli bir adam gördün mü?";
				link.l1.go = "PZ_BasTerAlkash_1";
				break;
			}
			// <== Квест "Путеводная звезда" - Sinistra
			
			dialog.text = LinkRandPhrase("Sen bir "+GetSexPhrase("gerçek dost","harika kız")+"! Tanıştığımıza memnun oldum! Şerefe!","Hik! Bu harika bir rom! Hik... Şerefe!","Sağlığınıza ve cömertliğinize!");
			link.l1 = "Heh, bu gerçekten sert bir rom. Peki, gitmem gerek. Keyfine bak!";
			link.l1.go = "exit_sit";
			if (makeint(pchar.money) >=2)
			{
				link.l2 = "Bir bardak daha alabilir miyim, sakıncası var mı?";
				link.l2.go = "sit_3";
			}

			link.l4 = LinkRandPhrase("Denizde bir ömür geçirmişim gibi hissediyorum. Yeni bir haber var mı?","Ne diyorlar? Elbette sana içki ısmarlayacağım.","Söyle bakalım dostum, bugünlerde meyhanelerde hangi hikâyeler dilden dile dolaşıyor?");
			link.l4.go = "rumours_habitue";
		break;

		case "sit_3":
			int iSituation;
			if(IsEquipCharacterByArtefact(pchar, "totem_01")) iSituation = makeint(rand(3));
			else iSituation = makeint(rand(5));
			switch (iSituation)
			{
				case 0:
					dialog.text = "Ah! Harika bir fikir!";
					link.l1 = "Barmen! Daha fazla rom!";
					link.l1.go = "sit_2";
				break;

				case 1:
					dialog.text = "Sana! Kahretsin! Kim o?";
					link.l1 = "Ha? Ne? Nerede? Herhalde hayal görüyorum.";
					link.l1.go = "sit_2";// to_do "sit_case_5_exit";
				break;
				
                case 2:
	         		dialog.text = "Hadi içelim, o zaman! Bir tane daha?";
					link.l1 = "Devam et!";
					link.l1.go = "sit_2";
                break;				
				
				case 3:
					if(rand(1) == 0)
					{
						dialog.text = RandPhraseSimple("Hey, sen, "+GetAddress_Form(NPChar)+", eminim herkesin sana hayran olduğunu düşünüyorsun, değil mi? Ama bana sorarsan, sen sıradan bir hayduttan ibaretsin!.. Hem de bir katil! 'Asil korsan'! Ha! Haydut hayduttur... Hık... Karada da olsa, denizde de olsa...","Hik! "+GetSexPhrase("Pi... Pislik","Pi... Pislik")+"! Beni sarhoş olana kadar içirmeye çalışıyorsun - hık - sonra da bütün paramı çalacaksın!");
						link.l1 = "Bakıyorum, zaten yeterince içmişsin... Git biraz uyu, ayıl... Benim de gitmem gerek...";
						link.l1.go = "exit_sit";						
						link.l2 = "Senin konuşma tarzını beğenmiyorum, dostum. Diline dikkat et, tamam mı?";
						link.l2.go = "sit_case_2_enemy";
						link.l3 = "Kime haydut dedin sen, kara fare?! Karnında bir delikle bakalım ne diyeceksin!";
						link.l3.go = "sit_case_2_enemy2";
					link.l4 = "Sakin ol! Unuttun mu? Ben senin tek gerçek arkadaşınım!";
					link.l4.go = "sit_case_2_friend";		
					}
					else
					{
						// Captain Beltrop, 27.06.21, новый вариант
						/* if (rand(1) == 0)
						{
							Diag.CurrentNode = Diag.TempNode;
							AddDialogExitQuestFunction("Tavern_SetBadHabitue");
							DialogExit();
						}
						else
						{ */
							dialog.text = RandPhraseSimple("Neden bana bakıp duruyorsun? Ben bayılana kadar bekleyeceksin - hık - sonra da bütün paramı çalacaksın! Bu ayaktakımı da nereden çıktı?! Hık... Bu meyhanede düzgün bir insana yer yok mu?","Bana saygı duyuyor musun?.. Evet, sen! Bana saygı duyuyor musun?! Kendine dikkat et... Benle oyun olmaz... Alnının ortasına bir yumruk... Ve sen ölmüş kadar olursun...");
							link.l1 = "Dostum, domuz gibi sarhoşsun. Git evine, biraz uyu... Benim de gitmem lazım...";	
							link.l1.go = "exit_sit";
							link.l2 = "Acele etme dostum. Kiminle konuştuğuna dikkat et.";
							link.l2.go = "sit_case_2_enemy1";
							link.l3 = "Ne dedin sen az önce?! Sana haddini bildireceğim!";
							link.l3.go = "sit_case_2_enemy2";
							link.l4 = "Sakin ol! Beni unuttun mu? Ben senin tek gerçek arkadaşınım!";
							link.l4.go = "sit_case_2_friend";	
						//}
					}
				break;

				case 4:
					dialog.text = "Dinle! Sen iyi bir adamsın! Belki bana... bir konuda yardımcı olursun?";
					link.l1 = "Hayır, sanırım şimdi gitmem gerekiyor.";
					link.l1.go = "exit_sit";
					link.l2 = "Tabii! Hık! Biz dostuz... değil mi? Hık!";
					link.l2.go = "sit_case_3";
				break;

				case 5:
					if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(110) || CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
					{
						dialog.text = "...Sonra k-kılıcının bıçağını t-tuttum...";
						link.l1 = "...ve sonra o dedi ki...";
						link.l1.go = "sit_2";
					}
					else
					{
						dialog.text = "...Sonra k-kılıcının bıçağını t-tuttum...";
						link.l1 = "...hik! ...ve sonra dedi ki...";
						link.l1.go = "sit_case_4_exit";
					}
				break;
			}
		break;

		case "sit_case_5_exit": // дуэль
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("fighting");
		break;

		case "sit_case_4_exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("without_memory");
		break;

		case "sit_case_3":
			dialog.snd = "Voice\HADI\HADI037";
			dialog.text = "M-mesele şu ki, a-askerlerden biri bana hakaret etti. H-Hepsi bu!";
			link.l1 = "Bir a-asker mi? H-Hayır, sanırım vazgeçeceğim.";
			link.l1.go = "exit_sit";
			link.l2 = "Sakin ol! Beni unuttun mu? Ben senin tek gerçek dostunum!";
			link.l2.go = "sit_2";
		break;

		case "sit_case_2_friend":
			dialog.snd = "Voice\HADI\HADI038";
			dialog.text = "Sen mi? Ne biçim arkadaşsın sen? H-hayır! Sen... beni öldürmek istiyorsun! T-tamam, bu kadar!";
			link.l1 = "Eh, kesinlikle zaten yeterince içtin. Hoşça kal.";
			link.l1.go = "exit_sit";
			link.l2 = "Ne? Sana kanıtlayacağım, s-seni öldürmeyeceğim! Ben... elini keseceğim!... O olmadan... öldürülemezsin!... Hık!";
			link.l2.go = "sit_case_2_friend_2";
		break;

		case "sit_case_2_friend_2":
			dialog.snd = "Voice\HADI\HADI039";
			dialog.text = "Aaaah! Al "+GetSexPhrase("onu","onu")+" benden uzak dur!";
			link.l1 = "Sakin ol... hık... Canını acıtmayacak!... Tıraştan bile daha az acır!";
			link.l1.go = "tavern_keeper";
		break;

		case "sit_case_2_enemy":
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "Beni korkutmaya çalışma! Hık! Ben öyle kolay kolay korkmam!.. Ve sen - sen darağacında sallanmalısın... Tüm senin gibilerle birlikte - hık! İstersen tüylerini kabart, ne yaparsan yap - ama yine de çürük balık gibi kokuyorsun! Ve ben dilimi tutacak değilim - hık! - senin gibilerle konuşurken! Hepinizden tiksiniyorum!";
			link.l1 = "Ah, neden böyle bir sarhoşla konuşuyorum ki... Sanırım biraz temiz hava almaya gideceğim...";
			link.l1.go = "exit_sit1";
			link.l2 = "Çok cesursun, dostum. Laflarını sana yutturacağım!";
			link.l2.go = "sit_case_2_enemy3";
		break;

		case "sit_case_2_enemy1":		
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "Ne-e?! Seni kendi ellerimle boğarım! Hık... Şimdiye kadar benden kimse kaçamadı - hık! - henüz!";
			link.l1 = "Sen tam bir ayyaş domuz değil misin? Böyle güzel bir akşamı mahvetmek... Peki, git böceklerini yakala - ben de buradan gidiyorum.";
			link.l1.go = "exit_sit1";
			link.l2 = RandSwear()+"Susmayacağın belli oldu. O zaman sana biraz görgü dersi vermek gerek.";
			link.l2.go = "sit_case_2_enemy3";
		break;
		
		case "sit_case_2_enemy2":	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Yaklaş buraya, seni serseri! Hak ettiğini alacaksın!",RandSwear()+"Sana hak ettiğini vereceğim!","Ha! Pekâlâ, deniz kurdu - bakalım karada nasıl iş çıkaracaksın!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Sana yemin ederim, bunu pişman olacaksın!","Dilini kulaklar için kısaltacağım!"),RandPhraseSimple("Seni bir domuz gibi deşeceğim, kıçından başlayıp bazıları ağız dediği o bok deliğine kadar!","Sana yemin ederim, seni susturacağım!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Hey, çocuklar! Hadi şu pisliği kasabamızdan süpürelim!";
				link.l1 = RandPhraseSimple(RandSwear()+"Duanızı edin, alçaklar!","Demek yalnız değilsin ha?! Güzel, cehennemde de yanında biri olacak!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "sit_case_2_enemy3":	
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Yaklaş buraya, seni serseri! Hak ettiğini alacaksın!",RandSwear()+"Sana hak ettiğini vereceğim!","Ha! Pekâlâ, deniz kurdu - bakalım karada nasıl iş çıkaracaksın!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Sana yemin ederim, pişman olacaksın!","Dilini kulağından kısacağım!"),RandPhraseSimple("Seni bir domuz gibi deşerim, kıçından başlayıp bazıların ağız dediği o bok çukuruna kadar!","Sana yemin ederim, seni susturacağım!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Hey, çocuklar! Hadi bu pisliği kasabamızdan temizleyelim!";
				link.l1 = RandPhraseSimple(RandSwear()+"Duanızı edin, alçaklar!","Demek yalnız değilsin ha?! Güzel, cehennemde de arkadaşların olacak!");
				link.l1.go = "fight_right_now_1";
			}
		break;		
		
		case "exit_sit":			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;

		case "exit_sit1":
			ChangeCharacterComplexReputationToNeutral(pchar,"nobility", 2.0);			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
				
		case "tavern_keeper":			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;
		
		// Captain Beltrop, 27.06.21, новый вариант
		case "bad_habitue":
			dialog.text = "Hey, anlamıyorum! Köşeyi döner dönmez, yeni bir acemi yerimi aldı. Çekil şuradan!";
			link.l1 = "Her zaman aynı: masaya oturursun, meğer çoktan başkası kapmış... Yerinde kal, zaten kalkacaktım.";
			link.l1.go = "bad_habitue1";
			link.l2 = "Ağzından bir cümle daha böyle pislik çıkarsa, bu söylediğin son sözün olur, anladın mı?";
			link.l2.go = "bad_habitue2";
			link.l3 = "Burası gerçekten senin yerin miydi bilmiyorum, ama benimle böyle konuşmana izin vermem. Ağzını topla.";
			link.l3.go = "bad_habitue3";
		break;
		
		case "bad_habitue1":
			DialogExit();
			pchar.questTemp.BadHabitueSit = true; // атрибут усаживания
			AddDialogExitQuest("exit_sit");
		break;
		
		case "bad_habitue2":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Haydi, alçaklar! Az sonra nasibinizi alacaksınız!",RandSwear()+"Şimdi seni adam akıllı soymaya başlayacağım!","Ha! Hadi bakalım denizci - karada neler yapabileceğini görelim!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Sana yemin ederim, bunu pişman olacaksın!","Kanlı dilini koparırım!"),RandPhraseSimple("Seni bir domuz gibi deşerim, kıçından o bazıların ağız dediği pisliğe kadar!","Sana yemin ederim, sesini keseceğim!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Hadi çocuklar! Şu pisliği kasabamızdan defedelim!";
				link.l1 = RandPhraseSimple(RandSwear()+"Dua edin, kahrolasılar!","Ah, yalnız değilsin! Pekâlâ, cehennemde de arkadaşların olacak!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "bad_habitue3":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Haydi, alçaklar! Şimdi doya doya alacaksınız payınızı!",RandSwear()+"Şimdi seni adam akıllı soymaya başlayacağım!","Ha! Hadi bakalım denizci - karada neler yapabileceğini görelim!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Yemin ederim, bunu pişman olacaksın!","Kanlı dilini koparırım!"),RandPhraseSimple("Seni bir domuz gibi deşerim, kıçından ağzın dedikleri o lağım deliğine kadar!","Sana yemin ederim, seni susturacağım!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Hadi çocuklar! Bu pisliği kasabamızdan atalım!";
				link.l1 = RandPhraseSimple(RandSwear()+"Dua edin, alçaklar!","Ah, yalnız değilsin demek! O zaman cehennemde de arkadaşların olacak!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		//--> Sinistra Длинные тени старых грехов
		case "DTSG_NightIskat":
			dialog.text = "E-elbette, hepimiz birbirimizi tanırız! Neden soruyorsun?";
            link.l1 = "Paracıya uğramak istedim, ama eski evini sattığını öğrendim. Şimdi nerede oturduğunu biliyor musun?";
            link.l1.go = "DTSG_NightIskat_2";
		break;
		
		case "DTSG_NightIskat_2":
			dialog.text = "Bu saatte ona neden ihtiyacın var, hık? Sabah bankaya uğrasana!";
            link.l1 = "Acilen paraya ihtiyacım var. Bir kerelik de olsa, zenginler çalışsın bakalım! Onların tayfası hep bizi dilenci, sızlanan ve borcunu asla ödemeyen insanlar olarak görür.";
            link.l1.go = "DTSG_NightIskat_3";
		break;
		
		case "DTSG_NightIskat_3":
			dialog.text = "Ha-ha-ha, hık, evet, bırak çalışsın! Bizim meşhur kaptan Fleetwood'un nerede yaşadığını biliyor musun?";
            link.l1 = "Tabii ki, Richard'ı kim tanımaz ki. Şimdi orada bankacı mı yaşıyor?";
            link.l1.go = "DTSG_NightIskat_4";
		break;
		
		case "DTSG_NightIskat_4":
			dialog.text = "Haklısın. Oraya vardığında, dostum - ona haddini aştığını söyle.";
            link.l1 = "Heh-heh, bunu mutlaka yapacağım. Hoşça kal.";
            link.l1.go = "DTSG_NightIskat_5";
		break;
		
		case "DTSG_NightIskat_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_NightIskat");
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuest("exit_sit");
			
			chrDisableReloadToLocation = true;
			sld = CharacterFromID("Knippel");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Knippel_SluhSmertFleetWood";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//<-- Длинные тени старых грехов
		
		//--> Путеводная звезда
		case "PZ_BasTerAlkash_1":
			dialog.text = "Ha-ha-ha, Çinliyi mi gördüm? Hepimiz onu gördük!";
			link.l1 = "Ne gülüyorsun? Seyyar bir sirkten bahsetmiyorum, eğer kastettiğin buysa. Ben bir dövüşçüden, bir deniz subayından söz ediyorum.";
			link.l1.go = "PZ_BasTerAlkash_2";
		break;
		
		case "PZ_BasTerAlkash_2":
			dialog.text = "Ah, ne demek istediğini anlıyorum! Evet, onu gördüm. Ayıldıktan sonra bile onu görmeyi bırakamadım...  Unutamıyorum!";
			link.l1 = "Bu ilginç. Devam et. Bir içki daha içelim – muhtemelen şimdi içiyorsun, her şeyi unutmak için. Bana ne gördüğünü anlat, ondan önce.";
			link.l1.go = "PZ_BasTerAlkash_3";
		break;
		
		case "PZ_BasTerAlkash_3":
			dialog.text = "Gezen bir sirkmiş, hadi oradan! Adam zıplıyor, dönüyor, o kılıcı havada döndürüyordu – bir silahla bu kadar yetenekli ve korkutucu birini hiç görmedim.";
			link.l1 = "Tam da onun tarzı. Kiminle dövüşüyordu? Hatırlıyor musun?";
			link.l1.go = "PZ_BasTerAlkash_4";
		break;
		
		case "PZ_BasTerAlkash_4":
			dialog.text = " Muhafızlar, dostum! Onlara da gözlerini kısarak bakıyor! Gerçi, sanırım hep öyle bakıyor. Sence nasıl?";
			link.l1 = "Bilmiyorum, dostum. Devam et. Onu casus mu sandılar? Neden muhafızlar ona saldırdı?";
			link.l1.go = "PZ_BasTerAlkash_5";
		break;
		
		case "PZ_BasTerAlkash_5":
			dialog.text = "Kim bilir? Kasabada ne yaptığını anlamaya çalışıyorlardı...";
			link.l1 = "Peki, onu tutukladılar mı? Yoksa...";
			link.l1.go = "PZ_BasTerAlkash_6";
		break;
		
		case "PZ_BasTerAlkash_6":
			dialog.text = "Ha, hiç şansı yok! Onu yakalayamadılar. Şehirdeki muhafızları kılıçtan geçirdi ve ormana kaçtı. Peşine birkaç grup gönderdiler ama hiçbiri geri dönmedi. Düşünebiliyor musun? O mağarayı tam bir kaleye çevirmiş!";
			link.l1 = "Bu da bir şey. Biraz dinlen ve unutmaya çalış. Sanırım artık gitmeliyim - başım dönüyor.";
			link.l1.go = "PZ_BasTerAlkash_7";
		break;
		
		case "PZ_BasTerAlkash_7":
			DialogExit();
			bDisableLandEncounters = true;
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
			DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
			pchar.questTemp.PZ_BasTerAlkash2 = true;
			DeleteQuestCondition("PZ_BasTer_Opozdal");
			pchar.questTemp.PZ_BasTerTurma = true;
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
			DelMapQuestMarkIsland("Guadeloupe");
			AddQuestRecord("PZ", "3");
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuest("exit_sit");
			
			PChar.quest.PZ_BasTerPeshera.win_condition.l1 = "location";
			PChar.quest.PZ_BasTerPeshera.win_condition.l1.location = "Guadeloupe_CaveEntrance";
			PChar.quest.PZ_BasTerPeshera.win_condition = "PZ_BasTerPeshera";
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
		break;
		
		case "Sotta1":
			dialog.text = "Ben kendim görmedim - vali konağının etrafında dolanıyormuş, ha! Ama tayfası burada büyük bir eğlence yaptı.";
			link.l1 = "Öyle mi?";
			link.l1.go = "Sotta2";
		break;
		
		case "Sotta2":
			dialog.text = "Herkes onun bir tüccar olduğunu söylüyor. Ama tayfası meyhanedeki ayaktakımı gibi değildi, sana söylüyorum! Sanki... sanki... neydi o kelime...?";
			link.l1 = "Anladım. Sohbet için sağ ol dostum. Kendine iyi bak.";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "Kutlama yapıyorum! Hem kim demiş yalnızım diye? Sen buradasın, dostum! Matt'e gelince, er ya da geç olacağı belliydi.";
			link.l1 = "Bunu neden söylüyorsun? Onun yıllarca Şans'ın gözdesi, olağanüstü talihli bir korsan olduğunu duymuştum!";
			link.l1.go = "Lutter2";
		break;
		
		case "Lutter2":
			dialog.text = "Heh, sadece Şans değildi, ha! O tek başına bir korsandı, Kardeşliğin üyesi değildi! Ve böyleleri fazla yaşamaz... Yine de, bir zamanlar Levasseur'un himayesinde olduğunu dedikodu edenler varmış, duydum.";
			link.l1 = "Evet, yalnızlar uzun süre dayanamaz. Hadi, kutla. Benim gitmem gerek, dostum.";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sepp1":
			dialog.text = "Hayır, h-hayır, onu hiç görmedim. Kim o?";
			link.l1 = "Takımadalar'daki en hızlı gemilerden birinin, 'Banten' adlı brigantin kaptanı o. Onu duydun mu?";
			link.l1.go = "Sepp2";
		break;
		
		case "Sepp2":
			pchar.questTemp.PZ.TortugaHabitueBlock = true;
			
			dialog.text = "Ee, hayır, gemilerle ilgilenmiyorum dostum, ıyy! Bir fincan daha içelim mi?";
			link.l1 = "Benim için değil. Zaten burada istediğimi bulamadım.";
			link.l1.go = "exit_sit";
		break;
		//<-- Путеводная звезда
		
	}
}

bool CheckFreeSitFront(ref _npchar)
{
 	ref rCharacter; //ищем
	int n;

	if (!CheckAttribute(_npchar, "Default.ToLocator")) return false;
	
	for (n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "location") && rCharacter.location == _npchar.location)
		{
            if (rCharacter.location.locator == _npchar.Default.ToLocator)
                return  false;
		}
    }
    return  true;
}
