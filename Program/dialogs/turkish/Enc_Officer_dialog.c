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
       			dialog.text = RandPhraseSimple("Heh, kaptan, şu anda garnizonun yarısı peşinizde. Eminim ki, tayfanıza katılmak için en uygun zaman değildir!","Ve gemiye kadar dövüşerek gitmek mi? Hayır, Kaptan, başka bir zaman...");
				link.l1 = RandPhraseSimple("Nasıl istersen...","Aslında, seni işe almayı düşünmüyordum."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "Bir subaya ihtiyacınız var mı, kaptan?";
			if (FindFreeRandomOfficer() > 0)
			{
    			Link.l1 = "Bir subay mı? Peki, hangi konuda iyisin?";
    			Link.l1.go = "Node_2";
			}
			Link.l2 = "Hayır, zaten tam takımım var.";
			Link.l2.go = "Exit";			
		break;
		
		case "CitizenNotBlade":
			dialog.text = "Kaptan, ne yapıyorsunuz? Silahınızı indirin, yoksa başımıza büyük bela açacaksınız!";
			link.l1 = LinkRandPhrase("Pekala.","Pekâlâ.","Merak etme, kaldırıyorum...");
			link.l1.go = "exit";
		break;
		
		case "hired":
			Diag.TempNode = "Hired";
			// только наняли -->
			if (IsCompanion(NPChar))
			{
				Dialog.text = "Bugün nihayet denize açılıyoruz!";
				link.l2 = "Evet... Sevindim.";
				link.l2.go = "Exit";
				break;
			}
			if (Npchar.location.group == "sit" && !isShipInside(pchar.location))
			{
				dialog.text = "İçkimi bitireceğim kaptan, sonra gemiye geçerim. Merak etmeyin – zamanında orada olacağım.";
				Link.l1 = "Pekala. Eğer geç kalırsan, güverteyi temizleteceğim sana!";
				Link.l1.go = "Exit";
				break;
			}
			// только наняли <--
   			dialog.text = "Ne istiyorsun, kaptan?";
			// эпилог -->
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers") && npchar.id == "Folke")
			{
				dialog.text = "Bu hava hiç hoşuma gitmiyor, kaptan. Fırtınanın ilk işaretlerini gördüm.";
				Link.l1 = ""+npchar.name+", seninle konuşmam gerek. Açık konuşacağım: Avrupa’ya, belirsiz bir süreliğine gidiyorum. Seni burada bırakıp beni beklemeye zorlamak saçma olurdu ama herkesi de yanımda götüremem. Başkasının gemisiyle, yolcu olarak gidiyorum.";
				Link.l1.go = "SharlieEpilog_Folke_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers") && npchar.id == "Duran")
			{
				dialog.text = "(esner) Sıkıcı...";
				Link.l1 = "Uzun zamandır canın hiç eğlenmedi, değil mi, "+npchar.name+"?";
				Link.l1.go = "SharlieEpilog_Duran_1";
				break;
			}
			// эпилог <--
			// диалог компаньона на корабле.
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				Link.l2 = "Sana birkaç emir vermem gerekiyor.";
				Link.l2.go = "Companion_Tasks";
				break;
			}
			
			// на Тайясаль
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l66 = ""+npchar.name+", Tayasal adlı eski bir Kızılderili kasabasına gidiyorum. Bu tehlikeli ve alışılmadık bir yolculuk olacak - bir teleportasyon putu aracılığıyla. Benimle gelir misin?";
				if(npchar.id == "Folke")
				{
					Link.l66 = ""+npchar.name+", senden ciddi bir ricam var - gerçek bir iş, intihar gibi ama lanet olasıca kârlı. Kadim bir Hint şehrine gitmek için sadık bir adama ihtiyacım var. Var mısın?";
				}
				if(npchar.id == "Duran")
				{
					Link.l66 = "Claude, bir zamanlar paralı askerlerin az ücret aldığından şikayet etmiştin.";
				}
				Link.l66.go = "tieyasal";
			}
			
			if (isOfficer(Npchar)) // проверка для кампуса, где слотовые офы
			{
				Link.l2 = "Şimdi emrimi dinleyin!";
				Link.l2.go = "stay_follow";
			}

           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l8 = "Bana gemiyle ilgili kapsamlı bir rapor ver, "+GetStrSmallRegister(XI_ConvertString("veznedar"))+".";
			    Link.l8.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
			    if(!CheckAttribute(PChar, "TransferGoods.Enable"))
			    {
				    Link.l11 = "Kolonide kaldığımız süre boyunca mal satın almanı istiyorum.";
				    Link.l11.go = "TransferGoodsEnable";
			    }
			    else
			    {
				    Link.l11 = "Biliyor musun, artık kolonilerden mal almak zorunda değiliz.";
				    Link.l11.go = "TransferGoodsDisable";
			    }
			}
			
			if (pchar.location != "My_Campus") // patch-5
			{
			Link.l4 = "Subay, artık hizmetine ihtiyacımız yok.";
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
							Link.l7 = "Bu kasabanın vekili olarak seni atıyorum!";
							Link.l7.go = "Gover_Hire";
						}
					}
				}
			}
			
			Link.l9 = "Hiçbir şey. Rahat ol!";
			Link.l9.go = "Exit";
		break;
		
		// Тайясаль
		case "tieyasal":
			if(npchar.id == "Folke")
			{
				dialog.text = "Lanet olsun, Kaptan! İlk fırsatta beni başından atarsın sanmıştım ama yine şaşırttın beni. Tabii ki yanındayım, ve bu aptala gerçek bir deniz kurdu hayatı yaşattığın için teşekkürler!";
				Link.l1 = "Aferin, "+npchar.name+"!";
				Link.l1.go = "folke_tieyasal";
				break;
			}
			if(npchar.id == "Duran")
			{
				dialog.text = "Ha? Gerçekten öyle mi dedim?";
				Link.l1 = "Yaptın. O zaman seni dikkatle dinledim ve şimdi haksızlığı düzeltmeye hazırım.";
				Link.l1.go = "Duran_tieyasal";
				break;
			}
			dialog.text = LinkRandPhrase("Üzgünüm Kaptan, ama ben bunun için burada değilim. Beni korkak sanma, ama kesin ölüme gitmeye niyetim yok. Yaşamaktan henüz bıkmadım – en azından şimdilik. İstersen beni kovabilirsin.","Kaptan, affınıza sığınırım ama - hayır. Deniz, gemi baskınları, düşman şehirleri - bunlar sorun değil, ama o Hint büyücülüğüne bulaşmak istemiyorum. Cevabımdan rahatsız olduysanız, sözleşmemizi iptal edebilirsiniz.","İmkânsızı istiyorsun kaptan, ve bunu sen de biliyorsun. Hiç kimse, sen de dahil, sağ dönmeyecek; bu yüzden ben yokum. Reddimi sözleşmenin şartlarının ihlali olarak görüyorsan, iptal edebilirsin.");
			link.l1 = LinkRandPhrase("Sizi suçlamıyorum, subay. Tam olarak anlıyorum.","Yazık, ama seni anlıyorum. Bu yüzden sana önceden söyledim.","Sana güveniyordum... Ama durumunu anlıyorum, subay.");
			link.l1.go = "tieyasal_1";
		break;
		
		case "Duran_tieyasal":
			dialog.text = "Heh! O zaman maaşımı artıracak mısın?";
			Link.l1 = "Olmaz! Eski bir Hint şehrine gidiyorum. İş intihar gibi, ama orada altın olacak...";
			Link.l1.go = "Duran_tieyasal_2";
		break;
		
		case "Duran_tieyasal_2":
			dialog.text = "Altınla ilgilenmiyorum. Sana yardım etmek benim için bir onur olur, Kaptan, tıpkı bir zamanlar senin bana yardım ettiğin gibi. Ne zaman yola çıkıyoruz?";
			Link.l1 = "Güzel söyledin, Claude! Tam anlamıyla hazır ol - artık çok az kaldı.";
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
				dialog.text = "Kaptan, hangi mallar? Önce kendimize bir gemi bulmamız lazım!";
				Link.l1 = "Evet, haklısın.";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
	        }
	        	
			PChar.TransferGoods.Enable = true;
		//	PChar.TransferGoods.TreasurerID = NPChar.id;
			Dialog.text = "Yapılacak, "+GetSexPhrase("efendim","özlemek")+" kaptan!";
			Link.l1 = "Rahat ol.";
			Link.l1.go = "TransferGoodsEnable_2";
        break;
        	
		case "TransferGoodsEnable_2":
			Diag.CurrentNode = "Hired";
			DialogExit();
			LaunchTransferGoodsScreen(); // Интерфейс автозакупки товаров
		break;
		
		case "TransferGoodsDisable":
			DeleteAttribute(PChar, "TransferGoods.Enable");
			Dialog.text = "Olacak, "+GetSexPhrase("efendim","miss")+" kaptan!";
			Link.l1 = "Rahat ol.";
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
			dialog.text = LinkRandPhrase(LinkRandPhrase("Captain, you know, I... Well, I'd like to ask you to relieve me. It's time for me to settle down, get married, and have some children. I still have no home of my own; when I grow old, there will be no one to bring me a glass of water.","Captain, please, let me resign. For all these years I've been wandering all around the world, and I still haven't really seen anything. I just want to live a new life, drop anchor and see the world from a different perspective.","Captain, the naval service is surely a fine thing, there's good profit and adventure, but the time has come for me to think about myself. You know, cast anchor in a quiet harbour, buy a home, have children. Please, let me go."),LinkRandPhrase("Captain, you know, I am truly sorry, but I am fed up with all these duties, watches and discipline. You see, I just want to live a free life, at least for a while, but I realise that you will not be waiting for me, so... Could you discharge me?","Captain, you know... There is a small vessel I can afford, so... I think it's probably time for me to start my own business. Please, could you let me go?","Captain, I was just offered a position at the port. Actually, I've been longing to cast anchor and settle down to married life for quite some time already. Please, allow me to go. I really can't miss such an opportunity."),LinkRandPhrase("Captain, I'm really seasick. The doctors keep telling me it's an idiosyncrasy. Please, for God's sake, let me go, or I'll just jump overboard at some point.","Captain, I think it's time for me to settle down and find myself a quieter place. You know, I'm afraid. Afraid of stray bullets, afraid of dying during a boarding. I pray to the Lord to keep me alive, and when I close my eyes, I see all the innocent souls I've killed. They are begging me to spare them... Please, show some compassion, and let me go.","Captain, my old wounds are aching, and this recent contusion reminds me of itself every single day. Soon you will dismiss me, and who will hire me after that? Please let me go, I'll patch myself up and find a quieter place."));
			Link.l1 = RandPhraseSimple(LinkRandPhrase("Hepsi eninde sonunda gider. Peki, gitmekte özgürsün.","Sebebini anlayabiliyorum. Er ya da geç, her şeyin bir sonu var. Peki, git o zaman... ve eğer seni bir gün kırdıysam bana kin tutma.","Yine mi bu? Beni terk etmek için özellikle en uygunsuz anı seçtin, değil mi? Her neyse. Elveda."),LinkRandPhrase("Söylediklerine inanmak zor... Peki, eşyalarını topla ve git.","Sen mi? Bunu beklemiyordum... Onca zamandır omuz omuza savaştıktan sonra... Neyse, seni durdurmayacağım. Yolun açık olsun.","Ciddi konuşuyorsun. Neyse, sana bol şans diliyorum ve bil ki seni özleyeceğim."));				
			Link.l1.go = "WantToGo_free";
			if (sti(Pchar.money) >= sti(NPChar.rank)*250)
			{
				Link.l2 = LinkRandPhrase("Anladım... Demek mesele böyle, öyle mi? Oysa sana güveniyordum... Madem kararını verdin, o zaman yollarımızı ayıralım. Al "+sti(NPChar.rank)*250+" sadık hizmetin için pesos. Ve eğer seni bir şekilde kırdıysam, bana kin tutma.","Pekâlâ, kin tutmam ve yapılanı unuturum. Eğer kararın buysa, git. Ve al götür "+sti(NPChar.rank)*250+" yeni bir başlangıç yapmak için pesoya ihtiyacım var, kesinlikle işe yarayacak.","Anladım... Eh, er ya da geç bunun olacağı belliydi. Sana vereceğim "+sti(NPChar.rank)*250+"  hayatını kurtarmak için peso. Sağlığına da dikkat et, denizcilik hayatı zorluklarla doludur..."); 
				Link.l2.go = "Im_kind_A2_1";
			}
			Link.l3 = LinkRandPhrase("Öyle diyorsun... Şimdi gidersen beni arkamdan bıçaklamış oluyorsun, farkında değil misin? Şu anda gitmene izin veremem, aklından bile geçirme.","Bu gerçekten haber! Biliyor musun, insanlar bana böyle şeyleri önceden bildirmek zorunda! O yüzden bir süreliğine özel hayatını unut. Zamanı gelince, emekli olmanı ben sana söylerim.","İstifa eden yok. Herkesi hesaba kattım. Sırf kişisel istekleri yüzünden kimseyi bırakamam. Hizmet etmeye devam et, izni hak edip etmediğine karar verene kadar.");	
			Link.l3.go = "WantToGo_Stay";
		break;
		
		case "Im_kind_A2_1":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*250)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Teşekkür ederim, kaptan! Böyle beklenmedik bir cömertlik... Biliyor musunuz, hâlâ bazı eşyalarınız bende, belki geri almak istersiniz?";
			Link.l1 = "Belki de... İyi bir kılıç bulmak artık o kadar kolay değil.";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "Ah, boşverin. Onları hizmetinizin bir hatırası olarak saklayın.";
			Link.l2.go = "WantToGo_free";
		break;
		
		case "WantToGo_Stay":
			dialog.text = RandPhraseSimple("Ama nasıl olur, kaptan? Köleler bile eninde sonunda karaya çıkarılıyor. Hem ben köle değilim, kendi kaderime kendim karar verebilirim!","Kaptan, bunca zamandır sana sadakatle hizmet ettim. Kendi kaderimi kendim belirlemeye hakkım yok mu?");
			Link.l1 = LinkRandPhrase("I see that I cannot keep you as it stands. Alright, how about some financial support? That will never hurt; you can use the money to build yourself a cosy home in a quiet harbour or take care of your health.","Alright, let's put it this way. What sum could possibly make you reconsider your decision?","You're right. But what about a one-time monetary allowance, would that change your mind?");
			Link.l1.go = "WantToGo_Stay_2";
			Link.l2 = PCharRepPhrase(RandPhraseSimple("Ah, hayır, dostum, burada yanılıyorsun... Meyhanelerde kadehlerin peşinde etek kovalamakla oyalanırken kendi kararını verebilirdin, ama bir kez gemime adım attığında, kaderini bana teslim etmiş oldun.","Hmm. Şimdi, bu ciddi bir laf. Görünen o ki, seni nasıl bulduğumu unuttun; cebinde beş kuruş olmadan, pis bir meyhanede. Sana bir altın bile gösterilmez, çünkü anında roma çevirirsin. 'Kaderime karar ver...' Pfff! Ne komik!"),LinkRandPhrase("Hizmetimde olduğun sürece, kararları ben veririm. Ve şimdi, lütfen beni daha fazla kızdırmadan görevine geri dön!","Hmm. Şimdi, bu ciddi bir söz. Ama sana peşin ödenen tüm parayı henüz hak etmedin. Yani bu çıkışın bir tür şantaj girişimi sayılabilir, değil mi?","Anladım... Gemi kuralları ne diyordu tekrar? Bak, ikinci madde: 'İzinsiz ayrılmaya kalkışan, ıssız bir kıyıya bir torba barut, bir matara su, bir tabanca ve bir tek kurşunla bırakılır.' Peki, bunu ister miydin?"));	
			Link.l2.go = "WantToGo_Stay_force";
		break;
		
	case "WantToGo_Stay_2":
		dialog.text = LinkRandPhrase("Eh, bu başka bir hikaye. "+sti(NPChar.rank)*500+" parayı peşin ver, yanında kalırım.","Pekâlâ, belki de "+sti(NPChar.rank)*500+" peso karşılığında kalabilirim, sanırım.","Pekâlâ, madem öyle diyorsun, o zaman "+sti(NPChar.rank)*500+" peso, hizmetime devam edebilirim.");
		if (sti(Pchar.money) >= sti(NPChar.rank)*500)
		{
			Link.l1 = RandPhraseSimple("Pekala, anlaştık.","Pekâlâ. Ama daha azını da isteyebilirdin.","İştahın bayağı yerinde, görüyorum! Ama sana bir söz verdim, değil mi, ve sözümde duracağım.");	
			Link.l1.go = "WantToGo_Stay_ForMoney";
		}
		Link.l2 = LinkRandPhrase("Bu gerçekten fazla. O paraya iki subay tutabilirim. Belki de seni serbest bırakmak daha kolay olur.","Pekâlâ, kendini bayağı bir şey sanıyorsun anlaşılan. Tamam, seni bırakacağım. Ama özgürlüğüne kavuştuğunda, hayatının beklediğin kadar sorunsuz olmayacağını kendin göreceksin.","Bu kadar para ödemeyeceğim. Gidebilirsin, ama geri dönmeyi aklından bile geçirme. İhaneti affetmem.");				
		Link.l2.go = "WantToGo_free";
	break;
	
	case "WantToGo_Stay_force":
		Npchar.loyality = makeint(Npchar.loyality) - 2;
		dialog.text = "Pekala, madem böyle diyorsun, kalacağım. Ama bil ki bunu yaparak kendi isteğime karşı geliyorum.";
		Link.l1 = LinkRandPhrase("Çok iyi. Görevine dön, bu konuşmayı sonra sürdüreceğiz.","Gemiye dön. Ve bir dahaki sefere, emeklilik istemeden önce iki kere düşün.","Elbette. Görev görevdir, ve hayallere dalmak için henüz erken.");
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
		dialog.text = LinkRandPhrase("İnanamıyorum! Teşekkür ederim Kaptan, bu gerçekten içimi rahatlattı.","Teşekkür ederim kaptan, beni engellemeye çalışmadığın için. Biliyor musun, hayatta başka şeyler de denemek istiyorum.","Heh, şimdi yeni kazandığım özgürlüğüme alışmam gerekecek. Ancak şimdi, o filoda hizmet etmekten ne kadar bıkmış olduğumu fark etmeye başladım.");	
		Link.l1 = RandPhraseSimple("Eh, sana bol şans.","Artık özgürsün. Hizmetin sona erdi.");
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
			dialog.text = RandPhraseSimple(LinkRandPhrase("Kaptan, vicdanıma karşı gelmek ve haydutluğa karışmak istemiyorum.","Kaptan, artık isyanlarınıza katılmak istemiyorum. Ben bir subayım, cellat değilim.","Kaptan, iş yapma tarzınızdaki haydutluk, mürettebatınızda kalmamı imkânsız kılıyor."),LinkRandPhrase("Kaptan, itiraf etmeliyim ki sizinle çalışmak büyük bir hayal kırıklığıydı. Hiçbir para karşılığında itibarımı feda etmeye niyetim yok.","Kaptan, geminizde Yeni Dünya'nın en azılı haydutlarını topladınız. Düzgün bir adamın onlara bakması bile tiksindirici. Böyle bir mürettebatla artık hizmet etmek istemiyorum.","Kaptan, tam bir serseri tayfası tuttunuz, sohbet edecek düzgün bir adam yok. Böyle bir hizmetten nefret ediyorum."))+" Elveda.";
			Link.l1 = "Ne?! Burası askeri bir gemi, yatılı okul değil! O zaman defol git cehenneme!";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Senin yakında ayrılacağını biliyordum... bu iş sana göre değil. Ama beni hiçbir şeyle suçlama. İşte "+sti(NPChar.rank)*500+" peso, işine uygun bir iş ararken işine yarayacaklar.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = LinkRandPhrase("Demek şimdi böyle bir şarkı söylüyorsun. Peki ya her soygundan aldığın pay, o da mı elini yakıyor? Yoksa günahlarının affı için bir manastıra çekilip dua etmeyi mi düşünüyorsun? Bizim için de bir iki iyi söz et bari! Ha-ha-ha-ha-ha!","Hmm. Şimdi, bu ciddi bir laf. Peki biz tüccarları birlikte soyarken senin masum vicdanın nereye bakıyordu? Onu nasıl temizleyeceksin? Yoksa bizi ele verip, düzgün bir toplulukta darağacında sallanmamızı mı sağlayacaksın?","Oh, bravo! Görünen o ki, seni nasıl bulduğumu unuttun; cebinde beş kuruş olmadan, pis bir meyhanede yatıyordun. Bilmiş ol, bir subay olarak beş para etmezsin. Hiçbir değerin yok!");
			Link.l3.go = "WantToGo_stop";
		}
		else
		{
            dialog.text = RandPhraseSimple(LinkRandPhrase("Kaptan, soylu oyunlarınızı gerçekten hiç sevmiyorum ve sizin huzurunuz için alışkanlıklarımdan vazgeçecek değilim. Elveda.","Kaptan, artık hizmetinizde kalamam. Zaten çok zaman kaybettim. Sıradan bir korsan olsaydım şimdiye kadar servet kazanmıştım. Gidiyorum.","Kaptan, adamlarınızdan tiksiniyorum. İçlerinde düzgün tek bir adam yok, hepsi gösteriş meraklısı, bir kadeh bile paylaşmaya değmezler. Gidiyorum."),LinkRandPhrase("Kaptan, ben deneyimli bir subayım ve geminiz daha çok bir yük mavnasına benziyor. Böyle bir hizmetten hoşlanmam. Elveda.","Kaptan, tayfanın tamamı çok şık, içip sohbet edecek tek bir adam yok. Böyle bir hizmetten hiç hoşlanmam. Elveda.","Kaptan, eskiden gerçek bir korsanın emrinde olduğumu sanıyordum, ama yaptığımız tek şey hayır işi! Zamanımı daha fazla boşa harcamak istemiyorum. Gidiyorum."));
			Link.l1 = RandPhraseSimple("Anladım. Senin bu tavrınla, er ya da geç böyle olacağı belliydi. Peki, seni tutmayacağım.","Sözlerin beni şaşırtmadı. Açıkçası, tavrından uzun zamandır memnun değilim.")+" Bol şanslar.";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Biliyordum yakında ayrılacağını... bu iş sana göre değil. Ama beni hiçbir şeyle suçlama. İşte "+sti(NPChar.rank)*500+" peso, yeni bir iş ararken işine yarar.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = RandPhraseSimple("Hmm. Şimdi, bu ciddi bir söz. Ama sana peşin ödenen tüm parayı henüz hak etmedin. Yani bu çıkışın bir çeşit şantaj girişimi sayılabilir, değil mi?","Anladım... Peki, geminin kuralları ne diyor? Bak, ikinci madde: 'İzinsiz ayrılmaya kalkışan, ıssız bir kıyıya bir torba barut, bir matara su, bir tabanca ve tek bir kurşunla bırakılır.' Şimdi, bu sana nasıl geliyor?");
			Link.l3.go = "WantToGo_stop";
		}
		break;
		
		case "WantToGo_stop":
			if (Npchar.alignment == "good")
			{
				dialog.text = LinkRandPhrase("Beni aşağılamaya bile kalkma! Para için çalışıyorum, ama yine de hoşuma giden işi seçme hakkım var!","Ben özgür bir adamım! Ve istediğim zaman yeni bir iş seçme hakkım var!","Yemek için çalışacak bir köle değilim, bu yüzden vicdanım rahat! Ama artık soygunlara katılmayacağım!");
				Link.l1 = "Aslında, yanılıyorsun... Mehanede içerken istediğin işi seçebilirdin... Ama bir kez gemime adım attığında, geri dönüş yolun sadece boynunu parçalayan bir top güllesi oldu... Ve dilin de kopacak, ki öteki dünyada ağzından bir şey kaçırmayasın...";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "Pekâlâ. Gidebilirsin... Ama Tanrı korusun, açık denizde karşılaşırsak. Yemin ederim, yanımda kalmamaya karar verdiğin o anı pişmanlıkla anacaksın.";
				Link.l2.go = "exit_fire_5";
			}
			else
			{
				dialog.text = LinkRandPhrase("Beni korkutmaya bile çalışma! Para için çalışıyorum, ama yine de sevdiğim işi seçme hakkım var!","Ben özgür bir adamım! Ve istediğim zaman yeni bir işe girme hakkım var!","Ben senin kölen değilim! Ve senin eski tenekende sefil bir hayat sürmeye devam etmeyeceğim!");
				Link.l1 = "Aslında, yanılıyorsun... Meyhanede içerken istediğin işi seçebilirdin... Ama bir kez gemime ayak bastın mı, geri dönmenin tek yolu boynunu parçalayan bir top güllesi olur... Ve dilin de koparılır, öbür dünyada bir şeyler gevelemeyesin diye...";
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
				Link.l2 = "Pekala. Gidebilirsin... Ama Tanrı korusun, açık denizde karşılaşırsak. Yemin ederim, yanımda kalmamaya karar verdiğin o anı pişmanlıkla hatırlayacaksın.";
				Link.l2.go = "exit_fire_5";
			}
		break;
		
		case "WantToGo_stop_stay":
			dialog.text = RandPhraseSimple("Eğer böyle diyorsan, kalacağım, çünkü başka bir seçeneğim yok. Ama unutma, bunu kendi isteğimle yapmıyorum...","Pekala, madem böyle diyorsun, kalacağım. Ama bil ki bunu yaparak kendi irademe karşı geliyorum.");
			Link.l1 = RandPhraseSimple("Tamam... Seni bırakmaya karar verene kadar hizmet etmeye devam et.","İyi. Hizmet etmeye devam et... Ne zaman gideceğine ben karar vereceğim.");
			Link.l1.go = "WantToGo_Munity"; //этот линк ведет к бегству
		break;
		
		case "WantToGo_stop_fight":
			dialog.text = NPCharRepPhrase(NPChar,"Beni fikrimi değiştirmeye asla zorlayamazsın! Beni köle gibi tutmaya hakkın yok! Gideceğim, uzak dur yoksa sonun gelir.","Bir veteran subayı korkutabileceğini mi sanıyorsun?! Ölümün eşiğinden defalarca döndüm. Madem öyle diyorsun, kanlı bir yağmada ölmektense adil bir savaşta ölmek çok daha iyidir!");
			Link.l1 = NPCharRepPhrase(NPChar,"Pekâlâ... herkes kendi kaderini seçer. Umarım bana gelmeden önce dualarını ettin.","Eğer seni meyhaneden aldığımda bunların olacağını bilseydim, seni darağacında sallanmaya bırakırdım. Ve bunu ayarlamak için hâlâ geç değil...");
			Link.l1.go = "WantToGo_stop_fight_1";
			Link.l2 = NPCharRepPhrase(NPChar,"Pekâlâ, özgürlüğüne bu kadar düşkünsen gidebilirsin. Ama sana hiçbir tavsiye vermeyeceğim.","Pekâlâ. Gidebilirsin... Ama açık denizde karşıma çıkarsan, Tanrı yardımcın olsun. Yemin ederim, yanımda kalmamaya karar verdiğin o anı pişmanlıkla hatırlayacaksın.");
			Link.l2.go = "exit_fire_5";	
		break;
		
		case "WantToGo_stop_fight_1":
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			dialog.text = NPCharRepPhrase(NPChar,"Artık beni korkutmaktan vazgeç! Senin adamlarından hangisi bana karşı çıkmaya cesaret edebilir ki? Eğer kaptan ben olsaydım, şimdiye kadar paraya para demezlerdi! Bunca cömertliğinden sonra hâlâ tayfanın benim tarafımı tutmasından mı korkuyorsun?!","Yolundan vazgeç, beni korkutamazsın! Elveda.");
			Link.l1 = NPCharRepPhrase(NPChar,"Hayır dostum, darağacına ulaşacak kadar uzun yaşamayacaksın. Böyle bir lüks sana göre değil...","O kadar da acele etme, dostum, henüz hesabımız kapanmadı. Bana borcun var.");
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
			dialog.text = NPCharRepPhrase(Npchar,RandSwear()+"Ben en iyisiyim "+XI_ConvertString(Npchar.quest.officertype)+" bu sularda. "+Npchar.quest.officertype_2+"Ve ben de sana bir iyilik yapmaya ve emrinde hizmet etmeye hazırım.","Pek fena olmadığımı söylüyorlar "+XI_ConvertString(Npchar.quest.officertype)+". "+Npchar.quest.officertype_2+"Beni gemine alabilirsin, kaptan, ve kendin görebilirsin.");
			Link.l1 = "Ve ne kadar istiyorsun?";
			Link.l1.go = "price";
			Link.l2 = "Sen ne tür bir uzmansın?";
			Link.l2.go = "ShowParam_exit";
			Link.l3 = "Ne yazık ki, zaten bir "+XI_ConvertString(Npchar.quest.officertype)+".";
			Link.l3.go = "Exit";
		break;

		case "OnceAgain":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Heh, kaptan, şu anda garnizonun yarısı peşinizde. Eminim ki ekibinize katılmak için en uygun zaman değildir!","Ve gemiye kadar dövüşerek yolumuzu açmak mı? Hayır, Kaptan, başka bir zaman...");
				link.l1 = RandPhraseSimple("Nasıl istersen...","Aslında, seni işe almayı düşünmüyordum."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "Fikrini değiştirdin mi, kaptan? Yeni bir karar mı verdin "+XI_ConvertString(Npchar.quest.officertype)+" zarar gelmezdi, değil mi?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "Öyle bir şey. Ne kadar istiyorsun?";
                Link.l1.go = "price";
			}
			Link.l2 = "Peki, sen neler yapabilirsin?";
			Link.l2.go = "ShowParam_exit";
			// boal <--
			Link.l3 = "Takımım tamam. Görüşürüz.";
			Link.l3.go = "exit";
		break;

		case "price":
			dialog.text = "Bence bu konuda anlaşabiliriz "+Npchar.quest.OfficerPrice+" pesos.";
			if(Npchar.rank >= 15)
			{
				dialog.text = "Bence bu konuda anlaşabiliriz "+(makeint(Npchar.quest.OfficerPrice)/ 100+30)+" doblon.";
			}	
			Link.l1 = "Bu biraz fazla değil mi?";
			Link.l1.go = "trade";
			Link.l2 = "Kabul ediyorum. Artık mürettebatın bir parçasısın.";
			Link.l2.go = "hire";
			Link.l3 = "Bu parayı hak etmiyorsun.";
			Link.l3.go = "exit";
		break;

		case "trade":
			if (GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) >= Rand(12) && (sti(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100) >= sti(Npchar.quest.OfficerLowPrice))// bug fix
			{
				Npchar.quest.OfficerPrice = makeint(makeint(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100); // пусть будет коммерция перса голой
				dialog.text = "Pekala... Sanırım buna bile razı olabilirim "+Npchar.quest.OfficerPrice+" peso. Ne dersin?";
				if(Npchar.rank >= 15)
				{
					dialog.text = "Sanırım buna bile razı olabilirim "+(makeint(Npchar.quest.OfficerPrice)/ 100+30)+" dublon. Ne dersin?";
				}
				Link.l1 = "Şimdi oldu. Katıldın.";
				Link.l1.go = "hire";				
				Link.l2 = "Bence hâlâ biraz fazla. Hoşça kal.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = "Üzgünüm kaptan, ama tam olarak istediğim kadar ederim. Eğer bu sana fazla geliyorsa, başka birini bulabilirsin.";
				Link.l1 = "Pekala, kabul ediyorum. Seni götüreceğim.";
				Link.l1.go = "hire";				
				Link.l2 = "Bunu yapacağım. Elveda.";
				Link.l2.go = "exit";
			}
		break;

		case "hire":
			dialog.text = "Paranız az görünüyor, kaptan! Üzgünüm, ama veresiye çalışmam.";
			Link.l1 = "Vay canına!";
			Link.l1.go = "Exit";
			if(Npchar.rank < 15 && makeint(Pchar.money) >= makeint(Npchar.quest.OfficerPrice))
			{
				AddMoneyToCharacter(Pchar, -(makeint(Npchar.quest.OfficerPrice)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "Teşekkür ederim, kaptan. Seçiminizden pişman olmayacaksınız.";
				Link.l1 = "Umarım öyle olur.";
				Link.l1.go = "Exit_hire";								
			}
			if(Npchar.rank >= 15 && PCharDublonsTotal() >= makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)))
			{
				RemoveDublonsFromPCharTotal(makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "Teşekkür ederim, kaptan. Seçiminizden pişman olmayacaksınız.";
				Link.l1 = "Umarım öyle olur.";
				Link.l1.go = "Exit_hire";								
			}
		break;

		case "OnboardSoon":			
			Diag.TempNode = "OnboardSoon";
			dialog.text = "İçeceğimi bitireyim kaptan, sonra gemiye gelirim. Merak etme, zamanında orada olacağım.";
			Link.l1 = "Pekala. Geç kalırsan, güverteyi temizleteceğim sana!";
			Link.l1.go = "Exit";											
		break;
        
		case "QMASTER_1":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = "Kaptan, ama sizin bir geminiz yok!";
				Link.l1 = "Bana hatırlattığın için teşekkür ederim...";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}
			// Rebbebion, добавил фикс отображения знака процента
			dialog.text = "Seyahat sırasında maksimum fare faaliyeti "+FloatToString(50.0 /(2.0+GetSummonSkillFromNameToOld(PChar,SKILL_REPAIR)+GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)),1)+"Toplam yük miktarının %%'si. "+GetCrewQuantity(PChar)+" denizcilere ihtiyacımız olacak "+makeint((GetCrewQuantity(PChar)+6)/ 10)+" günde yiyecek. Bu, taşınan köleleri hesaba katmaz.";
			Link.l1 = "Teşekkürler.";
			Link.l1.go = "Exit";
			Diag.TempNode = "Hired";
		break;
        
        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = "Emirleriniz nedir?";
            Link.l1 = "Burada dur!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Beni takip et ve geride kalma!";
            Link.l2.go = "Boal_Follow";
            // boal 05.09.03 offecer need to go to abordage <--
			if (npchar.id == "OffMushketer")
			{
				Link.l3 = "Hedefe belli bir mesafede durmanı istiyorum.";
				Link.l3.go = "TargetDistance";
			}
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l4 = "Ateşli silahınız için mühimmat türünü değiştirmemiz gerekiyor.";
					Link.l4.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l5 = "Tüfeğin için mühimmat türünü değiştirmemiz gerekiyor.";
					Link.l5.go = "SetMusketBullets";
				}
					Link.l6 = "Savaş için ana silahını değiştirmemiz gerekiyor.";
					Link.l6.go = "SetPriorityMode";
			}
		break;

		case "SetGunBullets":
			Dialog.Text = "Cephane türünü seç:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
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
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "Mühimmat türünü seç:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
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
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "Dövüşün başında şunları kullanacaksın:";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Tüfek";
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
			dialog.text = "Hangi mesafe tam olarak, kaptan? Adım olarak belirtin, ama 20'den fazla olmasın.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Kaptan, iyi misiniz?";
				link.l1 = "Üzgünüm, benim hatam...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Burada kımıldamadan duracağım. Bunu mu istiyorsun benden, kaptan?";
				link.l1 = "Evet. Tam olarak senden beklenen de bu.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Bence sana hedefin yirmi adım ötesine geçemeyeceğimi söylemiştim.";
				link.l1 = "Pekala, 20 metre mesafe bırakın.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Anlaşıldı ve dikkate alındı.";
			link.l1 = "Pekala.";
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
					dialog.text = "Kaptan, gerçekten mantığınızı anlamasam da, bunu karada konuşabilir miyiz? Yoksa beni doğrudan denize atmaya mı karar verdiniz?";
					Link.l1 = "Hmm... Hayır, demek istediğim bu değildi. Limana varana kadar burada kal.";
					Link.l1.go = "Exit";	
					break;	
				}
			}
			// проверка на море <--
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) < 41) //герой против злодея
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("Bu gerçekten yeni bir şey!","Neden, Tanrı aşkına?","Sebebi ne?!"),RandPhraseSimple("Kaptan, aklınızı mı kaçırdınız? Hiç yoktan böyle bir haberi söylüyorsunuz!","Vay canına! Sana ne yaptım da hoşuna gitmedim?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Mürettebata düzen getirmeye karar verdim. Ve meslektaşlarınla olan ilişkilerini onaylamıyorum","Sunduğun avantajlar işe alım sırasında konuştuğumuz kadar iyi değildi. Yani,","Mürettebatımda haydutlara ve serserilere yer yok! Yani,"),LinkRandPhrase("Rum çaldığın, gizlice tayfamı aşırı içmeye teşvik ettiğin ve böylece morallerini düşürdüğün kulağıma geldi. Bu yüzden,","Senin haydutça tavırlarından bıktım ve artık buna katlanmayacağım. Yani,","Sürekli olarak merkezi kamarada iskambil ya da zar oynayarak zaman geçiriyor, diğer subayların görevlerini yapmalarına engel oluyorsun. Bu böyle sonsuza kadar devam edemez. Yani,"))+"Eşyalarını topla ve gemiden ayrıl.";
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
				dialog.text = RandPhraseSimple(RandPhraseSimple("Böyle bir kararın sebebini öğrenebilir miyim?","Elbette, böyle bir karar iyi düşünülmüş."),RandPhraseSimple("Açıkla kendini, Kaptan","Bu oldukça beklenmedik. Ama yine de sebebini öğrenmek isterim."));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Senin görevlerine karşı tutumundan tamamen memnuniyetsizim.","Ne yazık ki, iyi bir subay olamadın ve muhtemelen asla da olamayacaksın...","Sen iyi bir subaydın ve hizmetin adildi, ama artık yollarımız ayrıldı. Nedenini sorma."),LinkRandPhrase("Sana rom tutkununun seni mahvedeceğini söylemiştim. Kılıcını kınına bile koyamayan bir adama dövüşte nasıl güvenebilirim?","Sen berbat bir denizci ve subaysın... Sanırım denizden çok karada vakit geçireceksin.","Niteliklerinden memnun değilim, ama sonunda uygun birini buldum."));
				Link.l1.go = "Get_out_A2";
				break;	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) >= 41) // злодей против героя 
			{		
				dialog.text = RandPhraseSimple(RandPhraseSimple("Hmm... Sebebini öğrenebilir miyim?","Bu ciddi bir iddia. Özellikle ne konuda memnuniyetsizsiniz, öğrenebilir miyim?"),RandPhraseSimple("Açıkla kendini, kaptan.","Elbette, böyle bir ifade mantıklı görünüyor mu?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Niteliklerinizden tamamen memnun değilim, bu yüzden","Ne yazık ki, kendini düzgün bir subay olarak kanıtlayamadın. O yüzden,","Asil tavırlarından bıktım. Sonsuza kadar katlanacak değilim, yani"),LinkRandPhrase("Mürettebatı itaatsizliğe teşvik ettiğin kulağıma geldi. Gemimde huzursuzluğa yer yok! Seni şimdiye kadar denize atmamış olmama da teşekkür etme. Yani","Asil ilkeleriniz size yakışıyor, fakat özgür bir korsanın kanunsuz yaşamına aykırı. Yani"," Görevlerine karşı tutumunu beğenmiyorum. O yüzden "))+" eşyalarını topla ve gemiden ayrıl.";
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
				dialog.text = RandPhraseSimple(LinkRandPhrase("Kaptan, gerçekten bunu hiç beklemiyordum! Belki neler olduğunu açıklayabilirsiniz?","Kaptan, sizi ne rahatsız ediyor?!","Bununla ne demek istiyorsunuz, Kaptan?!"),RandPhraseSimple("Ne oluyor kaptan?! Daha dün her şey yolundaydı, şimdi bu haldeyiz, ne oldu?","Vay canına! Belki kendini açıklamak istersin?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Sen tam bir tembelsin ve işe yaramaz bir aptalsın, kıyıdaki bir geminin miço çocuğu bile senden iyi iş çıkarırdı. Senin yüzünden çok uzun zamandır acı çekiyorum. Yeter artık","Bir süredir seni kovmayı düşünüyordum ve sonunda düzgün birini buldum. Yani","Rum çaldığın, gizlice tayfamı aşırı içmeye teşvik ettiğin ve böylece morallerini düşürdüğün kulağıma geldi. Bu yüzden"),LinkRandPhrase("Seni işe aldığımda, tüm filodaki en iyi subay olduğunu övünerek söylemiştin, ama meğerse tembelin tekiymişsin, yani","Sana içki alışkanlığının sonunun kötü olacağını söylemiştim. Neden gemimde işe yaramaz bir ayyaşı tutayım ki? O halde","Hizmet etmek yerine sürekli bir yerlere kayboluyorsun ya da iskambil ya da zar oynuyorsun. Bunun sonsuza kadar böyle devam edeceğini mi sandın? Yani"))+" eşyalarını topla ve gemiden ayrıl.";
				Link.l1.go = "Get_out_A4";
				break;
			}
		break;
	
		case "Get_out_A1_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Demek şimdi böyle konuşuyorsun! Peki, nasıl istersen. Ama bil ki: açlıktan ölsem bile sana geri dönmem!","Açıkçası, sizin soylu oyunlarınızı da pek umursamıyorum. O yüzden, hoşça kal...","Defol git cehenneme! Yalaka tayfanla kal. Sözde 'kahraman'mışsın!"),LinkRandPhrase("Aslında, sana hizmet etmekten hiç hoşlanmadım... Orada bir yük mavnan var, bu bir gemi değil. Daha çok bir kız okulu gibi...","Biliyor musun, senin tayfandan bıktım artık, hepsi süslü püslü, çocuk gibi, aralarında tek bir gerçek adam yok...","Peki kaptan, nasıl isterseniz. Ama Tanrı şahidimdir ki, işimi iyi yapıyordum..."));
			Link.l1 = "Bir dakika. Şu anda gemiden bir subay olmadan ayrılamam. Ama bu konuşmaya sonra döneceğiz.";
			Link.l1.go = "exit_bad";
			Link.l2 = "O zaman huzurla git.";
			Link.l2.go = "Exit_Fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Sinirlenme. Senin için bir tazminat hazırladım - "+sti(NPChar.rank)*500+" peso. Umarım bu, tüm soruları çözer.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife":
			dialog.text = LinkRandPhrase("Affedersiniz! 'Gemiden ayrıl' derken ne demek istiyorsunuz?! Ben boynumu misket topu ateşi altında riske attım, siz de canınız istediğinde beni gemiden atabilesiniz diye değil!","Ha! 'Gemiden ayrıl'! Beni bir kedi yavrusu gibi kenara atmana gerçekten izin vereceğimi mi sanıyorsun?!","Sakin ol kaptan, ciddi insanlar meseleleri böyle çözmez. Bana çaylakmışım gibi davranamazsın.");
			Link.l1 = "Pekâlâ, şimdilik kalabilirsin - ama sadece uygun birini bulana kadar.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Tekrar ediyorum, hizmetiniz sona erdi. Eşyalarınızı toplayabilirsiniz.";
			Link.l2.go = "Get_out_A1_strife_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Sakin ol. Hazırladım "+sti(NPChar.rank)*500+" senin için pesos. Umarım bu, tüm soruları çözer.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife_1":
			dialog.text = RandPhraseSimple("Aslında, burada kalmak için yanıp tutuşmuyorum. Ama tazminat almadan da gitmem!","Şimdi, kesinlikle senin o eski tenekende kalmayacağım, ama önce bana tazminat ödeyeceksin!")+" "+sti(NPChar.rank)*1000+" peso, ve birbirimizi unuturuz.";
			Link.l1 = "Biraz fazla tepki verdim... Lütfen özrümü kabul edin ve işinize geri dönün.";
			Link.l1.go = "exit_bad1";
			Link.l2 = "Hangi paradan bahsediyorsun, her zaman hakkını aldın zaten? Bu bana resmen şantaj gibi geliyor!";
			Link.l2.go = "Get_out_А1_strife_battle";
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l3 = "Pekala. Ekipmanı geri ver, sonra istediğini alacaksın.";
				Link.l3.go = "Get_out_А1_chang";
			}
		break;

		case "Get_out_А1_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Bu bambaşka bir hikaye. Hoşça kal!";
			Link.l1 = "Umarım yollarımız bir daha asla kesişmez.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_А1_strife_battle":
			dialog.text = LinkRandPhrase("Bunu manevi zararların tazminatı olarak kabul et. Böyle bir muameleyi asla kabul etmem, bana böyle davranmaya cüret eden herkes pişman olur!","Bu bir şantaj değil, bu aptalca zaman kaybımın karşılığı! Ve ne pahasına olursa olsun alacağım!","Senin gibi bir korkağın emrinde çalışarak çok fazla zaman kaybettim. Tüccar gemilerini yağmalayarak servet kazanabilirdim. O yüzden sadece kaybettiğim kazancı telafi etmek istiyorum.");
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l1 = "Pekala. Al paranı... Ve şimdi defol!";
				Link.l1.go = "Get_out_А1_ForMoney_angry";
			}
			Link.l2 = "Kim olduğunu unutuyor gibisin! Senin gibi yarım akıllıların bana bağırmasına izin vermem!";
			Link.l2.go = "Get_out_А1_strife_death";
		break;

		case "Get_out_А1_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("good");
			dialog.text = "Devam et, kaptan! Kendini göster!";
			Link.l1 = "Tanrı biliyor, bunu asla istemedim!";
			Link.l1.go = "Get_out_fight";
		break;
	
		case "Get_out_А1_ForMoney_angry":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			OfficersReaction("bad");
			dialog.text = "Bu bambaşka bir hikaye. Hoşça kal!";
			Link.l1 = "Umarım yollarımız bir daha asla kesişmez.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_A2":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Pekâlâ, o zaman karar verildi. Elveda kaptan, gücenme sakın...","Yazık oldu, kaptan. Ama Tanrı biliyor, denedim. Elveda.","Pekâlâ kaptan, sizi memnun etmek gerçekten zor! Tamam, size bol şans."),LinkRandPhrase("Yazık oldu, kaptan. Biliyor musunuz, sizin için çalışmaktan keyif almıştım.","Evet, olur böyle şeyler... Ama kin tutmam. Hoşça kal.","Bana haksızlık ediyorsun, kaptan. Yine de kararına saygı duyuyorum. Elveda."));
			Link.l1 = "Dur bir dakika, fikrimi değiştirdim. Bu konuşmaya sonra devam edelim.";
			Link.l1.go = "exit_good";
			Link.l2 = "Üzülme. Sana bol şans...";
			Link.l2.go = "exit_fire_2";
			Link.l3 = "Dur hele... Sana güzelce teçhizat verdim. Onları geri ver, bir orduyu donatacak değilim...";
			Link.l3.go = "Return_items_A2";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l4 = "Dur bir dakika... Seni eli boş göndermek istemem. Al, bunu da yanında götür "+sti(NPChar.rank)*500+" peso. Yeni bir iş ararken işine yarar.";
			}
			Link.l4.go = "Im_kind_A2";
		break;

		case "Return_items_A2":
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "Ah, tabii, hepsini geri al...";
			Link.l1 = "Beni anladığını biliyorum, değil mi...";
			Link.l1.go = "Get_out_А2_chang";
		break;

		case "Im_kind_A2":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Teşekkür ederim, kaptan! Böyle beklenmedik bir cömertlik... Biliyor musunuz, hâlâ bazı eşyalarınız bende, belki geri almak istersiniz?";
			Link.l1 = "Belki de... Bu devirde iyi bir kılıç bulmak o kadar kolay değil...";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "Ah, endişelenme. Onları hizmetinin bir hatırası olarak sakla.";
			Link.l2.go = "exit_fire_2";
		break;

		case "Get_out_A3_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Peki, nasıl istersen. Ama şunu bil ki: Açlıktan ölsem bile sana geri dönmem!","Kaptan, senin haydutça iş yapma tarzın bana da mide bulandırıcı geliyor. Er ya da geç, bunun olacağı belliydi. Ve bahane uydurmana hiç gerek yok.","O zaman kal o haydutlarınla. Düzgün bir adam senin geminin kamarasına adımını bile atmazdı. Burası ne biçim bir genelev olmuş, Allah affetsin!"),LinkRandPhrase("Açıkçası, sizin emrinizde çalışmaktan ben de hoşlanmadım. Bütün tayfanız serserilerden oluşuyor, konuşacak düzgün bir adam bile yok.","Evet, tayfana karşı bu tavrını sürdürürsen, yakında tamamen yalnız kalırsın ve bahane uydurmana da gerek kalmaz.","Düşmanlığımız karşılıklı, bu da bana teselli veriyor. Hoşça kal."));
			Link.l1 = "Bekle. Şu anda emekli olman için en uygun zaman değil. Ama tüm hakların saklı.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Git, git. Senin öğütlerine ihtiyacım yok, ben iyiyim.";
			Link.l2.go = "exit_fire_3";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Bekle. Sana vereceğim "+sti(NPChar.rank)*500+" peso. Seni sokakta ölüme terk etmek istemem, sonra vicdan azabı çekerim.";
				Link.l3.go = "Get_out_А3_ForMoney";
			}
		break;

		case "Get_out_А3_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("Pekala, teşekkür ederim. Hoşça kal...","Anlayışınız için teşekkür ederim. Bol şanslar.","Şimdi işimiz bitti. Bol şans...");
			Link.l1 = "Beni anladığını biliyorum, değil mi.";
			Link.l1.go = "exit_fire_3";
		break;
	
		case "Get_out_A3_strife":
			dialog.text = LinkRandPhrase("Ama kaptan, o zaman ben karada kalıyorum. Beni gerçekten gemiden doğruca kiliseye göndermeye razı mısınız?","Bana haksızlık ediyorsunuz, kaptan. Ama eğer uygun bir karşılık alırsam, size kin tutmam.","Ve tüm savaş yaralarım için minnettarlığın bu mu? Eh, sanırım maddi bir karşılık olmadan yapamam.");
			Link.l1 = "Pekâlâ, fikrimi değiştirdim. Kalabilirsin, ama bu konuşmaya tekrar döneceğiz.";
			Link.l1.go = "exit_bad";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Ah, boş ver onu. Al - "+sti(NPChar.rank)*500+" peso. Bu, gemimde geçirdiğin zamanın karşılığı olacak.";
				Link.l2.go = "Get_out_А3_ForMoney";
				Link.l3 = "Sana parayı vereceğim. Yine de, sayemde güzelce donandın ve sanırım eşyaları bana geri vermen adil olur.";
				Link.l3.go = "Return_items_A3";
			}
			Link.l4 = "Gerçekten mi? Peki ya düzenli olarak aldığın payın ne olacak?! Biliyordum, sonunda mızmızlanıp fazladan para istemeye başlayacaktın.";
			Link.l4.go = "Get_out_A3_strife_1";
		break;

		case "Return_items_A3":
			dialog.text = "Bunu söyleyeceğini biliyordum, ama ekipmanını ancak ben aldıktan sonra geri alabilirsin "+sti(NPChar.rank)*1000+" peso. Yoksa, onu ancak cesedimi çiğneyerek alabilirsin!";
			Link.l1 = "Pekâlâ, al paranı, o zaman.";
			Link.l1.go = "Get_out_А3_chang";
			Link.l2 = "Sen deli misin, ne?! Sana bedavaya verilen bir şey için böyle bir meblağ mı istiyorsun?! Şimdi anlıyorum ki, açgözlülüğün sahte iyi niyetini çoktan bastırmış.";
			Link.l2.go = "Get_out_A3_strife_1";
		break;

		case "Get_out_A3_strife_1":
			dialog.text = "Bana hakaret etmeye kalkışma! Donanmadaki en iyisi olmayabilirim, ama hâlâ bir muharebe subayıyım. Ve bana, senin gibi bir hödük bile olsa, saygı gösterilecek!";
			Link.l1 = "Eğer hâlâ anlamadıysan, bir kez daha tekrar edeyim: dilenciliği bırak, benden sana hiçbir şey çıkmaz.";
			Link.l1.go = "Get_out_А3_strife_death";
		break;

		case "Get_out_А3_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("bad");
			dialog.text = "Pekâlâ, yine de içim rahat edecek!";
			Link.l1 = "Ha, yani bu bir meydan okuma, öyle mi? Öyleyse, sen bilirsin...";
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_A4":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Şansım bu işte! Bunca yıl kalbimi ve ruhumu bu işe adadım, sonunda ise emekli maaşı bile olmadan kapı önüne konuldum!","Ne talihsizlik ama?! İşe alındım, sonra neredeyse hemen kapı dışarı edildim. Şu günlerde hangi aziz için mum yakacağımı bile bilmiyorum...","Vay canına! Bu yıl üçüncü kez kovuluyorum, hem de hepsi pazartesi günleri. Belki de kafam güzelken kaptanın karşısına çıkmamalıyım."),LinkRandPhrase("Peki, nasıl istersen. Umarım bir daha asla karşılaşmayız.","Dediğiniz gibi. Ama unutmayın, bundan daha iyi bir subay bulamazsınız.","Peki kaptan, nasıl isterseniz. Ama Tanrı biliyor ki, işimi gayet iyi yapıyordum..."));
			Link.l1 = "Dur biraz. Şimdi emekli olman için en uygun zaman değil. Ama tüm hakların saklı.";
			Link.l1.go = "exit_good";
			Link.l2 = RandPhraseSimple("Şimdi defol. Ve bugün iyi bir ruh halinde olduğuma dua et.","Defol şimdi. Senin subaylığın, bokun mermi yapmaya yaradığı kadar işe yarar.");
			Link.l2.go = "exit_fire_4";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Bekle. Sana vereceğim "+sti(NPChar.rank)*500+" peso. Seni sokakta ölüme terk etmek istemem, sonra kendimi suçlu hissederim.";
				Link.l3.go = "Get_out_А4_ForMoney";
			}
			Link.l4 = "Dur bir dakika... Sana iyi malzeme verdim, eşyalarımı geri ver.";
			Link.l4.go = "Return_items_A4";
		break;

		case "Get_out_А4_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("Ah, çok teşekkür ederim, kaptan! Bu gerçekten çok nazikçe...","Anlayışınız için teşekkür ederim. Bol şanslar.","Şimdi işimiz bitti. Bol şans...");
			Link.l1 = "İyi şanslar. Umarım hepsini ilk meyhanede harcamazsın.";
			Link.l1.go = "exit_fire_4";
		break;

		case "Return_items_A4":
			if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
			{
				dialog.text = LinkRandPhrase("Şimdi de ekipmanımı alıyorsun! Yeter artık! Gider balık tutarım, yemin ederim...","Beni tamamen soymaya karar verdiğini görüyorum. Eh, artık benim için tek bir yol kaldı, avluya doğru...","Ah, çok teşekkür ederim! Şimdi de beni soymaya karar verdin. Ah, ne acımasız bir kader... Al o zaman, al! Zaten ne yapabilirim ki...");
				Link.l1 = "Defol şimdi. Subaylıkta senin kadar işe yarayan bir boktan mermi yapılır ancak.";
				Link.l1.go = "Get_out_А4_chang_1";
			}
			else	
			{
				dialog.text = RandPhraseSimple("Dediğiniz gibi, kaptan, ama önce lütfen bana şunu verir misiniz "+sti(NPChar.rank)*1000+" peso. Bu da manevi zarar için bir tazminat olsun.","Pekâlâ. Ama yine de almak istiyorum "+sti(NPChar.rank)*1000+" zorlu ve sadık hizmetlerimin karşılığı olarak peso.");
				if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
				{
					Link.l1 = "Ne alçak adam! Peki, işte paran.";
					Link.l1.go = "Get_out_А4_chang";
				}
				Link.l2 = "Aklını mı kaçırdın?! Sana bizzat verdiğim bir şey için bu kadar para istemeye nasıl cüret edersin!";
				Link.l2.go = "Get_out_A4_strife";
				Link.l3 = "Ah-ha! Şaka yapıyordum! Eski bir dostu, delik deşik kaptan olarak, nasıl kapı dışarı edebilirim ki!";
				Link.l3.go = "exit_bad1";
			}
		break;

		case "Get_out_A4_strife":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "Pekâlâ, o zaman hiçbir şey alamazsın! Paramın şıngırtısını duymadan bir adım bile atmam!";
			Link.l1 = RandPhraseSimple("Kılıcımın şıngırtısını yakında duyacaksın!","O zaman seni ayaklarından sürüyerek götürecekler!");
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
			dialog.text = "Şimdi ne?! Zaten her şeyi konuştuk! Bir daha asla gemine adımımı atmam.";
			Link.l1 = RandPhraseSimple("Şimdi kaybol. Sonuçta pek bir kayıp sayılmaz.","Pekala, git o zaman. Seni tutmayacağım.");	
			Link.l1.go = "Exit";
		break;

		case "Fired_2":
			Diag.TempNode = "Fired_2"; 
			dialog.text = "Başka bir şey var mı, kaptan? Her şeyi zaten konuştuğumuzu sanıyordum...";
			Link.l1 = "Hayır, hiçbir şey. Sadece veda etmek istedim...";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_3":
			Diag.TempNode = "Fired_3"; 
			dialog.text = "Kaptan, her şeyi konuştuk ve taleplerimizi belirttik. Fikrini değiştirdiğini söylemeyeceksin, değil mi?";
			Link.l1 = "Pekâlâ, devam et o zaman. Sonuçta büyük bir kayıp değil.";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_4":
			Diag.TempNode = "Fired_4"; 
			dialog.text = "Kaptan, başka ne sorular olabilir ki? Bilin ki çok kırıldım ve geri dönmek gibi bir niyetim yok...";
			Link.l1 = "Pekala, git o zaman. Zaten sana o kadar da ihtiyacım yoktu.";	 
			Link.l1.go = "Exit";
		break;
		
		// boal 05.09.03 offecer need to go to abordage -->
	    case "Boal_Stay":
            //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
            //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
		    Diag.TempNode = "Hired";
		    dialog.text = "Emredersiniz, Kaptan!";
		    Link.l1 = "Rahat ol.";
		    Link.l1.go = "Exit";
		    Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	    break;
		
	    case "Boal_Follow":
		    SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		    Diag.TempNode = "Hired";
		    dialog.text = "Baş üstüne, Kaptan!";
		    Link.l1 = "Rahat ol.";
		    Link.l1.go = "Exit";
	    break;
        // boal 05.09.03 offecer need to go to abordage <--

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
            dialog.Text = "Kaptan! Bu bir onur olurdu!";
            Link.l1 = "Düzeni sağla ve şehri kalkındır, ben de zaman zaman gelip vergileri toplayacağım.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "Fikrimi değiştirdim.";
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
				dialog.Text = "Emirleriniz nedir? Son geldiğinizde bana "+FindRussianDaysString(iTemp)+" ago.";
			}
			else
			{
			    dialog.Text = "Emirleriniz nedir?";
			}

            Link.l1 = "Ne kadar vergi parası topladın "+NPCharSexPhrase(NPChar,"toplandı","toplandı")+" bu noktada?";
        	Link.l1.go = "Gover_Tax";
            Link.l8 = "Gemide sana ihtiyaç var, seni şehir görevinden alıyorum.";
            Link.l8.go = "Gover_Fire";
			Link.l9 = "Her şey gönlünce olsun.";
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
			dialog.Text = "Yeteneklerim bana toplama imkanı veriyor "+FindRussianMoneyString(iFortValue*iTax)+" Günlük. Bitti "+FindRussianDaysString(iTemp)+" Ben "+NPCharSexPhrase(NPChar,"toplandı","toplandı")+" "+FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum))+".";
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
			    Link.l1 = "Tüm toplanan vergi parasını almak istiyorum.";
            	Link.l1.go = "Gover_Tax_Get";
			}
			Link.l2 = "Hizmetiniz için teşekkürler!";
            Link.l2.go = "Exit";
        break;

        case "Gover_Tax_Get":
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "Harika! Ben karada yaşamaya alışık biri değilim, biliyorsun.";
            Link.l8 = "Bu iyi.";
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
			dialog.Text = "Seni dinliyorum.";
			Link.l1 = "Bu, gemiye çıkmakla ilgili.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Bu senin geminle ilgili.";
			Link.l2.go = "Companion_TaskChange";
			if(bBettaTestMode) // Только при бета-тесте
			{
			    Link.l3 = "Bir süreliğine filomdan ayrılmanı ve kendi şansını kendin aramanı istiyorum.";
			    Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Şimdilik bir şey yok.";
			Link.l8.go = "exit";
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "Peki, dileğin nedir?";
			Link.l1 = "Düşman gemilerine çıkma. Kendine ve mürettebata dikkat et.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Düşman gemilerine çıkmanı istiyorum.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Peki, dileğin nedir?";
			Link.l1 = "Gemini başka bir gemiyle değiştirmemeni tercih ederim. O çok değerli.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Düşman gemilerine bindiğinde, eğer düzgünlerse onları kendine alabilirsin.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Emredersiniz, Kaptan.";
			Link.l1 = "Rahat ol.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Emredersiniz, Kaptan.";
			Link.l1 = "Rahat ol.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Emredersiniz, Kaptan.";
			Link.l1 = "Rahat ol.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Emredersiniz, Kaptan.";
			Link.l1 = "Rahat ol.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--
	
		// Самостоятельное плавание компаньона -->
		case "CompanionTravel":
			if(GetAttrValue(PChar, "CompanionTravel") == 3) // Если уже троих отпустил
			{
				dialog.Text = "Kaptan, filonuzdan ayrılmayacağım, çünkü zaten üç gemiyi gönderdiniz.";
					Link.l1 = "Evet, belki de haklısın.";
					Link.l1.go = "exit";
				break;
			}
		
			dialog.Text = " Sorun değil, kaptan. Hangi kasabada buluşalım? ";
			for(iTemp=0; iTemp<MAX_COLONIES; iTemp++)
			{
				sld = &colonies[iTemp];
				attr = sld.ID;
				if(sld.nation == "none" || sld.nation == PIRATE || attr == "Panama" || attr == "FortOrange") continue;
				attrLoc = "l" + iTemp;
				Link.(attrLoc) = "In the " + XI_ConvertString("Colony" + attr + "Dat");
				Link.(attrLoc).go = "CompanionTravelToColony_" + attr;
			}
				Link.l99 = "Fikrimi değiştirdim.";
				Link.l99.go = "exit";
		break;
			
		case "CompanionTravel_EnemyColony":
			dialog.Text = "Kaptan, ama bize düşman olan kolonide seni bekleyemem!";
				Link.l1 = "Biliyor musun, bütün bu yolculukları boşver...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoCrew":
			dialog.Text = "Kaptan, mürettebatta neredeyse hiç denizcimiz yok! Hangi yolculuktan bahsediyorsun?!";
				Link.l1 = "Evet, gerçekten denizci sıkıntısı çekiyoruz...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoFood":
			dialog.Text = "Kapitan, böyle bir yolculuk için gemide yeterli erzağım yok.";
				Link.l1 = "Evet, haklısın. Yolculuk bekleyebilir...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoHP":
			dialog.Text = "Kaptan, ama gemim kötü durumda. Böyle bir durumda tek başıma denize açılmam akıllıca olmaz!";
				Link.l1 = "Evet, haklısınız. Geminizin onarıma ihtiyacı var.";
				Link.l1.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart":
			dialog.Text = "Anladım. Görüşürüz "+XI_ConvertString("Colony"+characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID+"Gen")+" gitmek "+sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days)+" gün, vardığımda ne yapmalıyım?";
				Link.l1 = "Koloninin limanında bir ay boyunca açıkta bekle.";
				Link.l1.go = "CompanionTravel_PrepareStart_2";
				Link.l2 = "Biliyor musun, bu aklımdan geçti. Benimle kal...";
				Link.l2.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart_2":
			dialog.Text = "Anladım, kaptan. Hemen yola çıkıyorum.";
				Link.l1 = "Evet, lütfen yap.";
				Link.l1.go = "CompanionTravel_Start";
		break;
			
		case "CompanionTravel_Start":
			Diag.CurrentNode = "CompanionTravel_LastNode";
			NPChar.quest.meeting = true;
			CompanionTravel_SetTraveller(NPChar);
			DialogExit();
		break;
			
		case "CompanionTravel_LastNode":
			Dialog.text = RandPhraseSimple("Bugün, yeniden yelken açacağım..."," Toplantımızı unutma "+XI_ConvertString("Colony"+characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID+"Dat")+".");
				link.l2 = "...";
				link.l2.go = "Exit";
				Diag.TempNode = "CompanionTravel_LastNode";
		break;
			
		case "CompanionTravel_ToSquadron":
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				dialog.text = "Ben de isterim. Bundan böyle, gemim tekrar senin emrinde, kaptan.";
					Link.l1 = "Pekala.";
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
				dialog.text = "Kaptan, filonda zaten beş gemi var - altıncıyla ne yapacaksın? Sanırım ben burada, kendi gemimde seni beklemeyi tercih ederim. Yeni arkadaşların bana pek güvenilir gelmiyor. Gemileri yakında batacak, sen de bana geri döneceksin.";
					Link.l1 = "Hey, ne kadar zekisin! Sadece kaptan değil, amiral olmalısın!";
					Link.l1.go = "exit";
					Diag.TempNode = "CompanionTravel_ToSquadron_2";
					NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2"; // ставим снова эту ноду
			}
		break;
			
		case "CompanionTravel_ToSquadron_2":
			dialog.text = "Ah, kaptan, dediğim gibi geri döndünüz. Peki, şimdi filonuzda boş bir yer var mı?";
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				Link.l1 = "Evet, "+NPChar.name+", bir tane var. Filoya hoş geldin.";
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
				Link.l1 = "Henüz değil, maalesef.";
				Link.l1.go = "exit";
				Diag.TempNode = "CompanionTravel_ToSquadron_2";
				NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2";
			}
		break;
		// <-- Самостоятельное плавание компаньона
		
		case "tonzag_after_boarding":
			dialog.text = "Kaptan, durum çok kötü! Düşman bizi sıkı sıkıya kıskaca aldı, ve korkarım ki bizi öldürene kadar bırakmayacaklar! Adamlarımız gerçekten büyük tehlikede, topçu ekiplerinin çoğu da saf dışı kaldı!";
			link.l1 = "Onlara yardım edeceğim. Kumandayı devral ve bizi buradan çıkar!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Evet, efendim!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Zafer, Kaptan! Çıkarma birliği yok edildi, düşman geri çekilmeye karar verip güneye yöneldi. Geminin durumu kabul edilebilir. Hayatta kalan mürettebat: "+GetCrewQuantity(pchar)+" insanlar. Rapor tamamlandı!";
			link.l1 = "Teşekkürler! Herkese rom, ve limana varana kadar nöbeti sıkı tutun!";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Yaşasın! Başüstüne!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_AlonsoBoardingDialog");
		break;
		
		// --> Эпилог
		case "SharlieEpilog_Folke_1": // Фульк
			dialog.text = "Yani… artık vedalaşma zamanı mı geldi?";
			link.l1 = "Öyle gibi. Ve doğrusu, bu kararı vermenin daha kolay olacağını düşünmüştüm.";
			link.l1.go = "SharlieEpilog_Folke_2";
		break;
		
		case "SharlieEpilog_Folke_2":
			dialog.text = "O zaman… her şey için teşekkürler, kaptan. Birçok kaptan gördüm, ama yemin ederim ki siz en iyisisiniz. Bayrağınız altında seyahat etmek bir onurdu.";
			link.l1 = "Sen sadık bir subaydın, "+npchar.name+". Hizmetin için teşekkürler. Kaderin bizi tekrar bir araya getirmesini umuyorum… ve barikatların zıt taraflarında değil.";
			link.l1.go = "SharlieEpilog_Folke_nothing";
			link.l2 = "Bunu duymak güzel dostum. Takdir ediyorum bunu. Sana bir aylık ücret karşılığı terhis verilmesini sağlayacağım. Hizmet yılların ve sadakatın için teşekkürler. Ve biliyorsun… bence artık senin de kaptan olma zamanın geldi. Bir düşün.";
			link.l2.go = "SharlieEpilog_Folke_salary";
			link.l3 = "Ve sana da teşekkürler dostum. Sen harika ve yetenekli bir subaysın. Sadakatin için minnettarlık işareti olarak üç aylık ücret almanı sağlayacağım. Ve eğer duyarım ki tekrar borç yüzünden hapse düştün… yemin ederim ki her şeyi bırakıp döneceğim, seni çıkaracağım — ve seni kişisel olarak ıssız bir adaya bırakacağım.";
			link.l3.go = "SharlieEpilog_Folke_salary_X3";
		break;
		
		case "SharlieEpilog_Folke_nothing":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Folke_exit");
		break;
		
		case "SharlieEpilog_Folke_salary":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Folke_exit");
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;
		
		case "SharlieEpilog_Folke_salary_X3":
			dialog.text = "Haha, hayır kaptan, bir daha tefeciye adımımı bile atmam. Ama kaptan olmak… ilginç bir fikir. Dürüst olmak gerekirse, bunu birden çok düşündüm. Belki gerçekten bunu yaparım.";
			link.l1 = "Bir şey daha. Meyhanede bir veda partisi düzenlemek istiyorum. Umarım gelirsin. Kendi mürettebatın için birkaç adamı kazanmak için iyi bir fırsat olur.";
			link.l1.go = "SharlieEpilog_Folke_salary_X3_2";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.OfficerPrice) * 3);
		break;
		
		case "SharlieEpilog_Folke_salary_X3_2":
			dialog.text = "Kesinlikle geleceğim, kaptan.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Folke_salary_X3_3";
		break;
		
		case "SharlieEpilog_Folke_salary_X3_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Folke_exit");
		break;
		
		case "SharlieEpilog_Duran_1":
			dialog.text = "Evet, 'uzun zaman' demek hafif kalır. O kadar uzun zaman oldu ki artık nasıl yapıldığını bile hatırlamıyorum, haha.";
			link.l1 = "O zaman belki söyleyeceklerimi beğenirsin. Bak, Eski Dünya’ya gidiyorum. Babamı uzun süredir görmedim, o endişeli — ve dürüst olmak gerekirse ben de öyleyim. Ama ben bir yolcu olarak gidiyorum. Başkasının gemisinde.";
			link.l1.go = "SharlieEpilog_Duran_2";
		break;

		case "SharlieEpilog_Duran_2":
			dialog.text = "Yolcu olarak mı? Vay canına.";
			link.l1 = "Bu şekilde devam edip etmeyeceğimi anlamak istiyorum. Kim bilir, belki şans hazır olmadan önce beni terk eder.";
			link.l1.go = "SharlieEpilog_Duran_3";
		break;

		case "SharlieEpilog_Duran_3":
			dialog.text = "Demek böyle. Hahaha. Denizden vazgeçebileceğine inanmıyorum. Sözümü unutma — gerçek bir deniz kurdu karada ya sıkıntıdan ölür ya da can sıkıntısından kendini asar.";
			link.l1 = "Bu yüzden bir yolcu olarak gidiyorum — o zaman geldiğinde böyle bir hayatı sürdürebilir miyim görmek için. Ama en önemlisi şu: Sizi yanımda götüremem — ve beklemenizi de isteyemem. Ben bile ne zaman döneceğimi bilmiyorum. Babamın kalmamı ve aile işlerini halletmemi isteyeceğinden eminim.";
			link.l1.go = "SharlieEpilog_Duran_4";
		break;

		case "SharlieEpilog_Duran_4":
			dialog.text = "Yani şimdi herkes kendi yoluna mı? Hmm… er ya da geç olması gereken bir şeydi. Ama ben veda etmeyi sevmem, o yüzden benden gözyaşı ya da sarılma bekleme.";
			link.l1 = "Hizmetin için teşekkürler. Eminim başarılı olacaksın — ama yine de, tekrar görüşene kadar hayatını kaybetmemeye çalış.";
			link.l1.go = "SharlieEpilog_Duran_nothing";
			link.l2 = "O zaman şu tavsiyemi dinle — eski mesleğinden uzak dur. Hiçbir iyi şey getirmez. İşte, biraz gümüş al — bir süre idare eder. Seni askere gitmeni tavsiye etmem, ama bir korsanın koruması olmak — kötü bir seçenek değil. Düşün bunu.";
			link.l2.go = "SharlieEpilog_Duran_salary";
			link.l3 = "Gözyaşı yok mu? O zaman gümüş var. Haha, gözlerinin parladığını görüyorum. Al, bunu tut. Üç aylık maaş — Le François’daki tüm korsanlara bir hafta içki ısmarlamak için yeter. Ya da basitçe söylemek gerekirse, altı ay yaşamak için. Umarım yapacak bir şey bulur ve geçimini sağlarsın.";
			link.l3.go = "SharlieEpilog_Duran_salary_X3";
		break;
		
		case "SharlieEpilog_Duran_nothing":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Duran_exit");
		break;
		
		case "SharlieEpilog_Duran_salary":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Duran_exit");
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;
		
		case "SharlieEpilog_Duran_salary_X3":
			dialog.text = "Zaten kararımı verdim. Hazine avcısı olacağım. Bu işte… bir şey var.";
			link.l1 = "Haha! Harika seçim! Ve bir şey daha: son kez güzelce eğlenmeyi planlıyorum. Eğer katılmak istersen — meyhaneye gel.";
			link.l1.go = "SharlieEpilog_Duran_salary_X3_2";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.OfficerPrice) * 3);
		break;
		
		case "SharlieEpilog_Duran_salary_X3_2":
			dialog.text = "Şaka mı yapıyorsun, kaptan? Haha! Bunun hiç kaçırmam!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Duran_salary_X3_3";
		break;
		
		case "SharlieEpilog_Duran_salary_X3_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Duran_exit");
		break;
		
		
		// <-- Эпилог
	}
}
