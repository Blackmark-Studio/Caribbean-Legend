void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Şu anda bir şey yok.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//Найти помощника в магазин
		case "Storehelper":
			DelLandQuestMark(npchar);
			dialog.text = "Bir şeye ihtiyacınız var mı, monsieur?";
			link.l1 = "Sen Gralam Lavoie’sun, doğru mu?";
			link.l1.go = "Storehelper_1";
		break;
		
		case "Storehelper_1":
			dialog.text = "Kim soruyor? Romumu içerken beni rahatsız etme, beyefendi. Sohbet edecek havamda değilim.";
			link.l1 = "Zamanınızı fazla almayacağım. Saint-Pierre'den bir tüccar tarafından buraya gönderildim. Eskiden onun yanında çalışmışsınız. Sizi arıyor ve...";
			link.l1.go = "Storehelper_2";
		break;
		
		case "Storehelper_2":
			dialog.text = "Ha, beni mi arıyor!? Şuna bak, cimrinin teki! Gerçekten ömrümün tamamını o üç kuruşluk maaş için çalışarak geçireceğimi mi sandı? Karayipler'deki en paragöz, en pinti adam o! Beş yıl onun için köle gibi çalıştım, bana verebileceğinin bir kuruş fazlasını bile vermedi! Hah, bir içki almaya bile yetmezdi!\nArtık mallarını kendi saysın, ben bıraktım. Saint-Pierre'de kimse o pintiye çalışmaz, bu kesin. Onun tek derdi var – kendi cebini doldurmak, insanlarına ise mümkün olduğunca az ödemek.";
			link.l1 = "Sanırım ona tekrar çalışmaya dönmeyeceksin?";
			link.l1.go = "Storehelper_3";
		break;
		
		case "Storehelper_3":
			dialog.text = "Hayır, Tanrı şahidim olsun ki yapmadım! Burada, Le François'da bir geminin gelmesini bekleyeceğim ve eğer alırlarsa katip olarak işe gireceğim. O da olmazsa, sıradan bir tayfa olarak çalışırım. Şu paragöz adamı görmek bile istemiyorum. Madem yoksul olacağım, bari özgür bir adam olayım...";
			link.l1 = "Anladım, bilmem gereken her şey buydu. İyi şanslar, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_4":
			DelLandQuestMark(npchar);
			dialog.text = "Beyefendi, çekilin. Yolumu kapatıyorsunuz!";
			link.l1 = "Tek bir sorum var, monsieur. Siz Gralam Lavoie misiniz?";
			link.l1.go = "Storehelper_5";
		break;
		
		case "Storehelper_5":
			dialog.text = "Ha! Evet, o benim. Ne istiyorsun?";
			link.l1 = "St. Pierre'den bir tüccar tarafından aranıyorsun. Eskiden onun için çalışmıştın, değil mi?";
			link.l1.go = "Storehelper_6";
		break;
		
		case "Storehelper_6":
			dialog.text = "Ha-ha! Ne komik! Peki, Majesteleri benden ne istiyor? Son iki haftalık eksik maaşımı ödemeye mi karar verdi? Yoksa bir yandan fıçılarını sayıp bir yandan da müşterilerini kandırmakta zorlanıyor mu, ha? Ha-ha-ha!";
			link.l1 = "Beni seni bulmam ve neden artık dükkanına çalışmaya gelmediğini öğrenmem için gönderdi.";
			link.l1.go = "Storehelper_7";
		break;
		
		case "Storehelper_7":
			dialog.text = "Neden mi? Çünkü o tam bir cimri ve berbat bir işveren! Artık Kıyı Kardeşliği'nin bir üyesiyim, özgürüm ve artık kimsenin kölesi değilim! Etrafına bak, gerçekten keyfime bakıyorum!\nYakında yelken açacağım ve sandık sandık muz saymak yerine, İspanyollardan aldığım peso ve dublonları sayacağım! O pinti için ise... Yerime birini bulabileceğinden şüpheliyim. Saint-Pierre'de kimse onun için çalışacak kadar enayi değil, adadaki tüm çıraklara onun namını yaydık, ha-ha!";
			link.l1 = "Anladım. Bilmem gereken her şey buydu. İyi şanslar, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_8":
			DelLandQuestMark(npchar);
			dialog.text = "Size nasıl yardımcı olabilirim?";
			link.l1 = "İyi günler. Gralam Lavoie, sanırım?";
			link.l1.go = "Storehelper_9";
		break;
		
		case "Storehelper_9":
			dialog.text = "Evet. Ne istiyorsunuz, monsieur?";
			link.l1 = "Senin peşinde Saint-Pierre'den bir tüccar var. Daha önce onun için çalışmıştın, değil mi?";
			link.l1.go = "Storehelper_10";
		break;
		
		case "Storehelper_10":
			dialog.text = "Bırak aramaya devam etsin. Ona hiçbir borcum yok. Hâlâ bana iki haftalık maaşımı borçlu, ama paramı ondan almaya bile uğraşmayacağım. Umarım kendi bakır paralarıyla boğulur.";
			link.l1 = "Hm. Demek onu tamamen terk ettin, öyle mi?";
			link.l1.go = "Storehelper_11";
		break;
		
		case "Storehelper_11":
			dialog.text = "You got everything right, sirrah. My former employer is a rare specimen of miser, truly Biblical in scale. I'm a Brother of the Coast now and my talents are well esteemed by my new mates. I get twice as much, plus bonuses\nI doubt that our dear friend will find anyone to replace me. His greed is well-known to the people of Saint-Pierre; no one there is foolish enough to work for him.";
			link.l1 = "Anladım. Bilmem gereken buydu. İyi şanslar, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_12":
			DialogExit();
			npchar.lifeday = 0;
			AddQuestRecord("SharlieA", "2");
			pchar.questTemp.Sharlie.Storehelper = "return";
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.StorehelperOver.over = "yes"; //снять таймер
			
			pchar.quest.Sharlie_JungleBandos.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleBandos.win_condition.l1.location = "Martinique_Jungle_01";
			pchar.quest.Sharlie_JungleBandos.function = "SharlieJungleBandos";
			
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload6_back");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Newstorehelper_1":
			dialog.text = "Merhaba, monsieur. Fazla ileri gitmek istemem ama sunduğunuz pozisyon için adaylığımın oldukça uygun olacağına inanıyorum.";
			link.l1 = "İyi günler. Peki, bunu neden düşündünüz?";
			link.l1.go = "Newstorehelper_1_1";
		break;
		
		case "Newstorehelper_2":
			dialog.text = "Selamlar, efendim! Size kendimden biraz bahsetmeme izin verin.";
			link.l1 = "Dinliyorum.";
			link.l1.go = "Newstorehelper_2_1";
		break;
		
		case "Newstorehelper_3":
			dialog.text = "Size sağlıklı günler dilerim, sayın beyefendi. Bir tüccar pozisyonu mu teklif ediyorsunuz?";
			link.l1 = "Evet, öyleyim. Kendiniz hakkında ne anlatabilirsiniz?";
			link.l1.go = "Newstorehelper_3_1";
		break;
		
		case "Newstorehelper_1_1":
			dialog.text = "Kaptan Francis Dubois’un bizzat emrinde çeyrekbaşı olarak görev yaptım. Yeteneklerimden oldukça memnundu, fakat bir çatışmada yaralandım ve iyileşmek için ayrılmak zorunda kaldım. Şimdi tamamen iyiyim, vücudumda en ufak bir sorun yok, ama dalgaların sallantısını düşünmek bile midemi bulandırıyor. Hayır, artık tek isteğim sağlam toprakta kalmak. \n(fısıldayarak) Eğer beni seçerseniz, beş yüz peso ve yirmi beş altın dublon fazladan ödeyeceğim.";
			link.l1 = "Anladım. Düşüneceğim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_1":
			dialog.text = "Eskiden seyyardım, ama bazı alacaklılardan kaçmak zorunda kaldım ve bir ticaret gemisinde veznedar olarak denizlere açıldım. Kader beni bu köye getirdi. Zaten denizci hayatını pek sevmezdim, bu yüzden teklifinizi memnuniyetle kabul ederim\n(fısıldayarak) Ve eğer beni seçerseniz, size sadece beş yüz peso değil, bu ağır kehribar paketini de vereceğim.";
			link.l1 = "Anladım. Düşüneceğim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_1":
			dialog.text = "Glasgow’daki liman depolarından birinde katiptim. Karayiplere servet aramaya geldim ve yaşlılığımı onurlu bir şekilde geçirecek kadar para kazandım. Ama deniz yolculuklarından yoruldum ve artık karada sakin bir hayat sürmek istiyorum\n(fısıldayarak) Eğer beni seçerseniz, size beş yüz peso ve ayrıca iki bin beş yüz peso da prim olarak vereceğim.";
			link.l1 = "Anladım. Düşüneceğim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_2":
			dialog.text = "Monsieur, doğru seçimi yapın. Ve doblonları unutmayın...";
			link.l1 = "Senin lehine karar verdim. Kendine gel. Saint-Pierre'e gidiyoruz.";
			link.l1.go = "Newstorehelper_1_3";
			link.l2 = "Henüz karar vermedim...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_2":
			dialog.text = "Umarım beni seçersiniz, monsieur. Kehribar da oldukça değerli ve işe yarar bir şeydir...";
			link.l1 = "Senin lehine karar verdim. Kendine gel. Saint-Pierre'e gidiyoruz.";
			link.l1.go = "Newstorehelper_2_3";
			link.l2 = "Henüz karar vermedim...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_2":
			dialog.text = "Tüccar yaptığım işten memnun kalacak. Bir de, primini unutma.";
			link.l1 = "Senin lehine karar verdim. Kendine gel. Saint-Pierre'e gidiyoruz.";
			link.l1.go = "Newstorehelper_3_3";
			link.l2 = "Henüz karar vermedim...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_3":
			dialog.text = "Eşyalarımı toplamama izin ver! Seni meyhanenin girişinde bekleyeceğim.";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 0;
		break;
		
		case "Newstorehelper_2_3":
			dialog.text = "Hemen geliyorum, monsieur! Sizi meyhanenin girişinde bekliyor olacağım.";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 1;
		break;
		
		case "Newstorehelper_3_3":
			dialog.text = "Eski valizimi alıp meyhanenin girişinde sizi bekleyeceğim, efendim!";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 2;
		break;
		
		case "Newstorehelper_exit":
			DialogExit();
			pchar.questTemp.Sharlie.Storehelper.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay")
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Newstorehelper_"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			pchar.quest.storehelper4.win_condition.l1 = "location";
			pchar.quest.storehelper4.win_condition.l1.location = "FortFrance_store";
			pchar.quest.storehelper4.function = "NewstorehelperRegard";
			AddQuestRecord("SharlieA", "4");
			pchar.questTemp.Sharlie.Storehelper = "choise";
			pchar.quest.storehelper.over = "yes"; //снять прерывание
			
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			
			SetLaunchFrameFormParam("Back to Saint-Pierre...", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("FortFrance_store", "reload", "reload1", "");
			LaunchFrameForm();
		break;
		
		case "Newstorehelper_regard":
			dialog.text = "Pekala, demek bundan sonra çalışacağım yer burası? Beni seçtiğiniz için teşekkür ederim, monsieur. İşte söz verdiğiniz gibi beş yüz peso ve üstüne de priminiz.";
			link.l1 = "Teşekkür ederim... Sizi işvereninizle tanıştırmama izin verin.";
			link.l1.go = "Newstorehelper_regard_1";
		break;
		
		case "Newstorehelper_regard_1":
			DialogExit();
			npchar.lifeday = 0;
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "gold_dublon", 25);
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "jewelry8", 10);
					TakeNItems(pchar, "jewelry7", 1);
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 3000);
				break;
			}
		break;
		
		//контрабанда рома
		case "Rum_Cap_Over":
			dialog.text = "Bayım, sizden hemen gemimden ayrılmanızı rica ediyorum. Demir alıp yola çıkıyoruz!";
			link.l1 = "Pekâlâ...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rum_Cap_Over";
			chrDisableReloadToLocation = false;
			npchar.DontDeskTalk = true;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
		break;
		
		case "Rum_Cap":
			pchar.quest.Sharlie_rum2.over = "yes"; //снять таймер
			chrDisableReloadToLocation = false; // patch-4
			dialog.text = "Peki? O halde, sen kimsin?";
			//link.l1.edit = 1;			
			link.l1 = ""+pchar.questTemp.Sharlie.Rum.Pass+"!";
			link.l1.go = "Rum_Cap_1";
		break;
		
		case "Rum_Cap_1":
			dialog.text = "Bir yudum rom al, denizci! Ha-ha! Lugger’ıma hoş geldin. Mallar için mi geldin?";
			link.l1 = "Evet. Burada başka ne için olabilirdim ki?";
			link.l1.go = "Rum_Cap_2";
			/* if(GetStrSmallRegister(pchar.questTemp.Sharlie.Rum.Pass) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Bir yudum rom al, denizci! Ha-ha! Lugger’ıma hoş geldin. Mallar için mi geldin?";
				link.l1 = "Evet. Başka ne için burada olabilirdim ki?";
				link.l1.go = "Rum_Cap_2";
			}
			else
			{
				dialog.text = "Vay canına, ne toy bir piç bu! Çocuklar, bu tam bir acemiye benziyor! Hadi atalım şunu denize!";
				link.l1 = "Hup!";
				link.l1.go = "Rum_Cap_getout";
			} */
		break;
		
		case "Rum_Cap_getout":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			setCharacterShipLocation(pchar, "Shore38"));
			setWDMPointXZ("Shore38");
			DoQuestReloadToLocation("Shore38", "goto", "goto1", "Rum_RemoveBarkas");
		break;
		
		case "Rum_Cap_2":
			dialog.text = "Çocuklar! Sandıkları sandala yükleyin!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Rum_CarrierEnter");
		break;
		
		case "Rum_Cap_3":
			dialog.text = "Tüm rom sandıkları senin sandalda. Port Le Francois tam güneyde. Acele et, benim de demir almamın vakti geldi!";
			link.l1 = "Vakit kaybetmeyelim, beyler! İyi şanslar!";
			link.l1.go = "Rum_Cap_4";
		break;
		
		case "Rum_Cap_4":
			dialog.text = "Sana da, dostum...";
			link.l1 = "...";
			link.l1.go = "Rum_Cap_5";
		break;
		
		case "Rum_Cap_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			npchar.DontDeskTalk = true;
			NextDiag.CurrentNode = "Rum_Cap_Over";
			pchar.quest.Sharlie_rum4.win_condition.l1 = "Ship_location";
			pchar.quest.Sharlie_rum4.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Sharlie_rum4.function = "Rum_RemoveRum";
			AddQuestRecord("SharlieB", "4");
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 3000;
			
			DoQuestFunctionDelay("MessageRum1", 1.0);
			//NewGameTip("Transport the rum to Le Francois. Keep sailing around the island.");
			pchar.questTemp.Rum.Tip2.Reload = "l4";
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
			
			Weather.Wind.Angle = PId2;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
			
			pchar.quest.MessageRum2.win_condition.l1 = "ExitFromLocation";
			pchar.quest.MessageRum2.win_condition.l1.location = pchar.location;
			pchar.quest.MessageRum2.function = "MessageRum2";
		break;
		
		case "Rum_Carrier":
			dialog.text = "Sizi bekliyorduk, monsieur. Her şey yolunda mı geçti? Sandıklar yanında mı?";
			link.l1 = "Her şey harika gitti. Rom sandıkları sandalda.";
			link.l1.go = "Rum_Carrier_1";
		break;
		
		case "Rum_Carrier_1":
			dialog.text = "Harika. Bundan sonrasını biz hallederiz. Sen St. Pierre'e, meyhaneye git, ödemen orada. Gece ormanda dikkatli ve tetikte ol.";
			link.l1 = "En iyisi, beyler.";
			link.l1.go = "Rum_Carrier_2";
		break;
		
		case "Rum_Carrier_2":
			DialogExit();
			for (i=1; i<=3; i++)
			{
				
				sld = characterFromId("Rum_Carrier2_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			}
			pchar.questTemp.Sharlie.Rum = "regard";
			i = FindLocation("Fortfrance_town");
			setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		    setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Gigolo")) QuestPointerToLocTime("fortfrance_town", "reload", "reload9_back", 23.0, 24.0);
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		//доставить девочку из борделя
		case "GigoloMan":
			DelLandQuestMark(npchar);
			dialog.text = "İyi günler, monsieur! Şunu söylemeliyim ki, genelde kolonimizde dolaşan o perişan serserilere hiç benzemiyorsunuz. Kıyafetlerinize bakılırsa, epey uzaklardan gelmiş olmalısınız... Avrupa'dan mı geldiniz, yoksa?";
			link.l1 = "Aynen öyle, monsieur. "+GetFullName(pchar)+", hizmetinizdeyim. Ne istemiştiniz?";
			link.l1.go = "GigoloMan_1";
		break;
		
		case "GigoloMan_1":
			dialog.text = "İzin verin kendimi tanıtayım - "+GetFullName(npchar)+" . Fransa'dan birkaç yıl önce bu korkunç yere geldim. Ama bu mesele şimdi önemli değil. Sizin için çok hassas bir ricam var\nLütfen anlayın, eğer sizin gerçek bir centilmen olduğunuzdan emin olmasaydım, böyle bir iyilik istemeye asla cesaret edemezdim.";
			link.l1 = "Lütfen isteğinizi belirtin, monsieur. Eğer elimden gelirse, elbette yardımcı olmaya çalışırım.";
			link.l1.go = "GigoloMan_2";
		break;
		
		case "GigoloMan_2":
			dialog.text = "I am glad to hear that, monsieur de Maure. Now, how to put this delicately...There is a brothel in this town. A new girl appeared there recently; young, pale, blonde, stunningly beautiful! Now, I've been watching her for weeks and... got a very strong desire to spend some time with her in private\nBut my estate and status make it...inconvenient to visit such a place. Imagine the gossip!\nThat is why I am appealing to you. Plainly put, you are a newcomer to our island, people don't know you and they don't care about what you do... yet. You could do me a great favour, monsieur.";
			link.l1 = "Sanırım ne demek istediğini anlıyorum.";
			link.l1.go = "GigoloMan_3";
		break;
		
		case "GigoloMan_3":
			dialog.text = "I appreciate your discretion, monsieur. I cannot go to the girl, so the girl must come to me. At my house. I ask you to go to the brothel and make an arrangement with the madame so that she will allow you to organise a 'house call' with the blonde girl for one night.\nAurora will not refuse; she is well known for providing such services, although it always costs a bit more. After that, you shall bring the girl to my house. For payment, I will give you six thousand pesos. Aurora usually takes three thousand or three and a half thousand for one night with the girl at home. You may keep the extra as compensation for your troubles.";
			link.l1 = "Çok karmaşık gelmiyor. Bunu halledebilirim.";
			link.l1.go = "GigoloMan_4";
			link.l2 = "Monsieur, ben de sizin kadar centilmenliğime önem veririm. Lütfen beni affedin, ama isteğinizi yerine getiremeyeceğim. Reddetmek zorundayım. Muhtemelen meyhaneye gidip meyhaneci iş var mı diye bakmalıyım.";
			link.l2.go = "GigoloMan_exit";
		break;
		
		case "GigoloMan_exit":
			DialogExit();
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);// бордель open
			LocatorReloadEnterDisable("Fortfrance_town", "reload9", false);// бордель
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", false);// таверна
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
		break;
		
		case "GigoloMan_4":
			dialog.text = "I am damn glad to hear it. Now listen, the girl's name is Lucille. I ask you to deliver her to my place when it's dark, no earlier than eleven p.m., in order to avoid unwanted attention from any gawkers. Knock on the door, and I will open.\nMy house is located to the left of the governor's residence, facing away from it - a two-story mansion with a red roof. You can easily find it, and there's a shop nearby, too. Actually, I am heading to my house now; feel free to follow me to see what it looks like and where it is exactly, so you won't get lost at night.\n Regarding the matter at hand - here, take six thousand pesos. I expect you by the agreed-upon time!";
			link.l1 = "Anlaştık. Senin sarışın Lucille bu gece kapında olacak.";
			link.l1.go = "GigoloMan_5";
		break;
		
		case "GigoloMan_5":
			DialogExit();
			AddMoneyToCharacter(pchar, 6000);
			AddQuestRecord("SharlieC", "1");
			AddQuestUserData("SharlieC", "sName", GetFullName(npchar));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("Fortfrance_town", "houseSp1", true);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie.Gigolo = "start";
			pchar.questTemp.Sharlie.Gigolo.Rand1 = rand(1);
			pchar.questTemp.Sharlie.Gigolo.Rand2 = rand(1);
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);// бордель open
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", false);// бордель
			AddLandQuestMark(characterFromId("Fortfrance_hostess"), "questmarkmain");
			QuestPointerToLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerToLoc("fortfrance_brothel", "reload", "reload3");
			chrDisableReloadToLocation = false;
		break;
		
		case "GigoloGirl":
			if (npchar.quest.meeting == "0")
			{
				DelLandQuestMark(npchar);
				QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
				dialog.text = "Günaydın, monsieur. Bu gece beni tutan beyefendi siz misiniz? Aman, aman, söylemeliyim ki, böylesine yakışıklı ve bakımlı bir beyefendiye denk geldiğim için çok şanslıyım, limandan inip katran ve ter kokan kaba adamlara hiç benzemiyorsunuz...";
				link.l1 = "Affedersin Lucille, ama bu gece değil. Burada iyi bir arkadaşım adına bulunuyorum; kendisi, çok karmaşık sebeplerden ötürü evinden çıkamıyor, bu yüzden seni ona götüreceğim. Şimdi üzülme, kendisi nazik biridir ve senden oldukça hoşlanıyor. Sonunda mutlu olacağını düşünüyorum.";
				link.l1.go = "GigoloGirl_1";
				// belamour legendary edition -->
				link.l2 = "Uhm... Haklısın, sevgilim. Devam edelim mi?";
				link.l2.go = "GigoloGirl_1a";
				// <-- legendary edition
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Monsieur, umarım anlıyorsunuzdur ki sizinle gece gece öylece dolaşamam. Beni hemen arkadaşınızın evine götürmelisiniz, yoksa doğruca Madame'ın yanına dönerim ve paranız boşa gider.";
				link.l1 = "Pekala, anladım. Beni takip et!";
				link.l1.go = "GigoloGirl_2";
			}
		break;
		// belamour legendary edition -->
		case "GigoloGirl_1a":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			chrDisableReloadToLocation = true; //закрыть локацию
			DoQuestReloadToLocation(pchar.location+"_room", "goto", "goto2", "GigoloGirl_Sex");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_room", "goto", "goto1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		case "GigoloGirl_1":
			AddCharacterExpToSkill(pchar, "Fortune", 40);
		// <-- legendary edition
			dialog.text = "Ne yazık... Sizi hemen sevdim, monsieur. Sizinle geceyi geçirmek isterdim... belki bir dahaki sefere. Gidelim mi?";
			link.l1 = "Evet. Beni takip et!";
			link.l1.go = "GigoloGirl_2";
		break;
		
		case "GigoloGirl_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_Gigolo.win_condition.l1 = "locator";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator = "houseSp1";
			pchar.quest.Sharlie_Gigolo.function = "Sharlie_GiveGigoloGirl";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.function = "Sharlie_GigoloGirlOver";
			QuestPointerToLoc("fortfrance_town", "reload", "houseSp1");
		break;
		
		case "GigoloGirl_3":
			dialog.text = "Ne kadar görkemli bir ev. Burası mı?";
			link.l1 = "Evet.   Gir içeri.   Korkma, arkadaşım iyi bir insandır.";
			link.l1.go = "GigoloGirl_4";
		break;
		
		case "GigoloGirl_4":
			dialog.text = "Beni hafife alıyorsunuz, korkmuyorum, monsieur. Kendimi korumayı bilirim. Şimdi, belki daha sonra bana bir gece ayarlamak için Madame'a ödeme yaparsınız? Söz veriyorum, hayatınızın en güzel gecesi olacak!";
			link.l1 = "Her şey mümkün, Lucille. Belki tekrar karşılaşırız. Elveda!";
			link.l1.go = "GigoloGirl_5";
		break;
		
		case "GigoloGirl_5":
			pchar.quest.Sharlie_Gigolo1.over = "yes";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "GigoloGirl_Remove", 5.0);
			QuestPointerDelLoc("fortfrance_town", "reload", "houseSp1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		//пираты с пленным испанцем
		case "CaptivePirate":
			pchar.quest.Captive_CreatePiratesOver.over = "yes";//снять таймер
			pchar.quest.Captive_CreatePiratesOver2.over = "yes";//снять таймер
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload2_back");
			dialog.text = "Bu da ne!? Sen kimsin? Burada ne istiyorsun? Hadi, defol buradan!";
			link.l1 = "Pek kibar değilsiniz, efendi.";
			link.l1.go = "CaptivePirate_1";
		break;
		
		case "CaptivePirate_1":
			dialog.text = "Dinle evlat, ben terbiyeli olmak için yetiştirilmedim, tıpkı okumayı yazmayı öğrenmediğim gibi. Ama senin kafanı bir palayla yarmak, bana bir fahişenin sırtüstü düşmesi kadar kolay. Ve ölü gözlerim üzerine yemin ederim ki, şu an buradan çıkmazsan, seni dışarı cesedini taşıyarak çıkarırlar. Anladın mı?";
			link.l1 = "Hayır, şimdi beni dinle, seni alçak. Planın ortaya çıktı. O adamı sağ istiyorum, bu yüzden silahlarını bırakıp kaç. Hemen arkamda ormanda bir grup Fransız askeri var. Yeterince hızlı kaçarsan, belki şu zavallı hayatınızı kurtarabilirsiniz.";
			link.l1.go = "CaptivePirate_3";
			link.l2 = "Pekala, pekala, sakin ol. Gidiyorum.";
			link.l2.go = "CaptivePirate_2";
		break;
		
		case "CaptivePirate_2":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetImmortal(sld, true);
				sld.lifeday = 0;
			}
			sld = characterFromId("CaptiveSpain");
			LAi_SetImmortal(sld, true);
			sld.lifeday = 0;
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";//снять прерывание
			AddQuestRecord("SharlieD", "5");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "CaptivePirate_3":
			dialog.text = "Ne-e? Blöf yapıyorsun dostum! Yakalayın onu çocuklar, silah başına!";
			link.l1 = "O zaman sorumluluğu sana ait, silahını çek!";
			link.l1.go = "CaptivePirate_4";
		break;
		
		case "CaptivePirate_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			int n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Captive_PiratesDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
			sld = characterFromId("CaptiveSpain");
			LAi_SetCitizenType(sld);
			DoQuestFunctionDelay("Ngt_CaptiveEng", 0.5);
		break;
		
		//пленный испанец
		case "CaptiveSpain":
			dialog.text = "Tanrıya şükür! Ah, sen Fransız mısın? Kahretsin, o haydutları harika savuşturdun. Ama sakın sanma ki hemen pes edeceğim, sana bir İspanyolun nasıl dövüştüğünü göstereceğim! Santiago!";
			link.l1 = "Hayır, bekle, lütfen!";
			link.l1.go = "CaptiveSpain_1";
		break;
		
		case "CaptiveSpain_1":
			dialog.text = "Fransızlara teslim olmaktansa ölmeyi tercih ederim. Sen savaşırken ölülerden birinin yanından bir pala aldım... şimdi sana İspanyolca bir kadriyi oynatacağım!";
			link.l1 = "Siz İspanyollar inatçı katırlar gibisiniz!";
			link.l1.go = "CaptiveSpain_2";
		break;
		
		case "CaptiveSpain_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			NextDiag.currentnode = "CaptiveSpain_3";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "CaptiveSpain_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "CaptiveSpain_3":
			dialog.text = "Lanet olsun... Kazandın. Pes ediyorum, kahrolası Fransız. Merhametine kaldım.";
			link.l1 = "Kılıcını indir ve beni dinle, inatçı Kastilyalı! Ölmeni istemiyorum, seni hapse de göndermeyeceğim!";
			link.l1.go = "CaptiveSpain_4";
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
		break;
		
		case "CaptiveSpain_4":
			dialog.text = "O halde ne yapıyorsun? Neden korsanları öldürdün? Peki askerlerin nerede?";
			link.l1 = "Asker yok. O alçakları kandırmaya çalıştım ama etrafa bakarsan, işe yaramadı. Burada yalnızım, eski dostunun ricasıyla geldim. Adı "+pchar.questTemp.Sharlie.Captive.Name+", o St. Pierre'de bir bankacı.";
			link.l1.go = "CaptiveSpain_5";
		break;
		
		case "CaptiveSpain_5":
			dialog.text = ""+pchar.questTemp.Sharlie.Captive.Name+"? O ismi hiç duymadım...";
			link.l1 = "Senden ya da esaretinden de hiçbir şekilde haberim yoktu. Seni bir İngiliz gemisine naklettiklerini de ondan öğrendim. Benim görevim seni ona teslim etmek ve bunu yerine getireceğime yemin ettim! Şimdi, yaşamak istiyorsan benimle gel.";
			link.l1.go = "CaptiveSpain_6";
		break;
		
		case "CaptiveSpain_6":
			dialog.text = "Zaten başka seçeneğim yok... Senin şu bankacın, İngilizler ve onların berbat yemeklerinden daha kötü olamaz herhalde...";
			link.l1 = "Sonunda akıllıca bir karar veriyorsun. Şimdilik bu kadar konuşma yeter, St. Pierre'e gidiyoruz. Yakınımda kal ve sakın ayrılma. Kaçarsan, yine yakalarım ve seni canından bezdirene kadar döverim.";
			link.l1.go = "CaptiveSpain_7";
		break;
		
		case "CaptiveSpain_7":
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.Notsearchbody"); // 170712
			DialogExit();
			AddQuestRecord("SharlieD", "6");
			LAi_group_Register("TempFriends");
			LAi_group_SetRelation("TempFriends", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "TempFriends");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
			pchar.quest.Sharlie_captive3.win_condition.l1 = "locator";
			pchar.quest.Sharlie_captive3.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator = "reload8_back";
			pchar.quest.Sharlie_captive3.win_condition.l2 = "Night";
			pchar.quest.Sharlie_captive3.win_condition.l3 = "Alarm";
			pchar.quest.Sharlie_captive3.win_condition.l3.value = 0;
			pchar.quest.Sharlie_captive3.win_condition.l3.operation = "=";
			pchar.quest.Sharlie_captive3.function = "CaptiveSpain_reload";//вход ночью
			pchar.questTemp.Sharlie = "bankskipercaptive";
			SetFunctionLocationCondition("CaptiveSpain_removeGuard", "fortfrance_town", 0);
			SetFunctionLocationCondition("CaptiveSpain_saveTip", "fortfrance_exittown", 0);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			// Rebbebion, новые марки до места назначения. belamour поправил - были не в ту сторону
			QuestPointerToLoc("shore39", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload8_back");
			AddLandQuestMark(characterFromId("FortFrance_Usurer"), "questmarkmain");
		break;
		
		//горожанин с пропавшей дочерью
		case "Prosper":
			DelLandQuestMark(npchar);
			pchar.quest.Sharlie_RescueDaughter.over = "yes"; //снять прерывание
			dialog.text = "Ne istiyorsunuz, monsieur? Sohbet edecek vaktim yok, o yüzden kısa kesin.";
			link.l1 = "Sen Prosper Trubal'sın, değil mi?";
			link.l1.go = "Prosper_1";
		break;
		
		case "Prosper_1":
			dialog.text = "Evet, o benim. Ama siz benden daha avantajlısınız. Lütfen kim olduğunuzu ve ne istediğinizi bana söyleyin.";
			link.l1 = "Benim adım "+GetFullName(pchar)+".   Size   gönderildim  "+GetFullName(characterFromId("Fortfrance_portman"))+", liman müdürü. Acil yardıma ihtiyacınız olduğunu söyledi...";
			link.l1.go = "Prosper_2";
		break;
		
		case "Prosper_2":
			dialog.text = "Aman Tanrım, evet! Şu alçak komutan şikayetimi dinleme zahmetine bile girmedi! Ya çok tembel ya da yardım etmeye korkuyor. Gerçekten bana yardım etmeye mi geldin? Eğer öyleyse, seni karşılıksız bırakmam!";
			link.l1 = "Evet, Prosper. Bana ne olduğunu ve sana nasıl yardımcı olabileceğimi anlat. Kızının kaybolduğunu duydum...";
			link.l1.go = "Prosper_3";
		break;
		
		case "Prosper_3":
			dialog.text = "Evet, sevgili kızım Celene iki gündür kayıp. Buradan çok uzakta olmayan kaleye yürüyüşe gitmişti. Ama geri dönmedi, ben de kaleye kendim gittim ve askerler bana onun oraya hiç gelmediğini söylediler!\nAma dönüşte iki vahşi Kızılderili tarafından saldırıya uğradım! Sopalarla üzerime atıldılar ve beni dövmeye çalıştılar.\nAma ben öyle kolay lokma değilim, birine yumruk attım, bu da bana tabancamı çekip ateş etmeye yetecek kadar zaman kazandırdı. Iskaladım ama onları korkutup kaçırdım. Şehir kapısına kadar ulaşmayı başardım ve nöbetçilere saldırıyı anlattım. Onlar hemen ormana koştular ama vahşiler çoktan gitmişti.\nCelene'in kaybolmasından kesinlikle onların sorumlu olduğuna inanıyorum. Üstelik, geçen hafta iki kişi daha kayboldu - Cesar Blanchet ve Gilbert Courcy! Biri körfeze, diğeri Le Francois'ya gidiyordu. Bir daha geri dönmediler.";
			link.l1 = "Yani Kızılderililer şehir kapılarında kasaba halkına saldırıyorlar mı? Bu inanılmaz derecede cesurca...";
			link.l1.go = "Prosper_4";
		break;
		
		case "Prosper_4":
			dialog.text = "Bu arada, ben de onu aramak için ormana çıktım ve şehrin kuzeyinde bir mağara buldum. O alçakları orada çömelmiş halde buldum. Girişte birkaç Kızılderili gördüm ama bazıları da içeride olmalı\nBir kızın çığlığını duydum... O benim Celene’mdi, eminim, onun sesiydi! Kendimi zor tuttum, hemen içeri dalmamak için – şansım hiç yoktu ve beni oracıkta parçalarlardı. Ona ölü halde hiçbir faydam olmazdı.";
			link.l1 = "Ama Tanrı aşkına, neden saldırıp kasaba halkını esir alıyorlar?";
			link.l1.go = "Prosper_5";
		break;
		
		case "Prosper_5":
			dialog.text = "Bilmiyorum... Belki korsanlara ya da köle tacirlerine satmak için? Belki de onları diri diri yerler, sonuçta vahşiler.";
			link.l1 = "Tanrım, yoksa bunlar yamyam mı? Avrupa’da çocukları korkutmak için anlatılan hikayeler sanmıştım...";
			link.l1.go = "Prosper_6";
		break;
		
		case "Prosper_6":
			dialog.text = "Hikayeler mi? Senin gibi bazı adamlar da öyle düşünmüştü, ta ki Karayip yerlileri onları ateşte kızartıp yemeye başlayana kadar... Hemen komutana gidip Celene'imi kurtarmak için bir cezalandırma baskını talep ettim. Reddetti! Kızlar kaybolunca muhtemelen bir oğlanla kaçtıklarını, yerlilerle değil, söyledi. Onu yerel samanlıklarda aramamı önerdi.\nDiğer iki kayıp için ise... birinin kaçakçılıkla suçlandığını, diğerinin ise muhtemelen Le Francois'nin meyhanesinde kendini içkiye verdiğini söyledi. Sonuç olarak, hiçbir şey başaramadım ve kendi başıma harekete geçmeye karar verdim.";
			link.l1 = "Ne yapmayı düşünüyorsun?";
			link.l1.go = "Prosper_7";
		break;
		
		case "Prosper_7":
			dialog.text = "Oraya gideceğim ve o kızıl alçakların hepsini geberteceğim. Yeter ki Celene hâlâ hayatta olsun. Gördüğün gibi bir tüfek aldım - ve nasıl ateş edileceğini biliyorum. Bir yığın para verdim ama umurumda değil\nEğer bana eşlik edersen görevim çok daha kolay olacak. Sen arkamı kollarken birlikte bu vahşileri fazla zorlanmadan temizleyebiliriz. Kızımı kurtarmak için benimle gelir misin?";
			link.l1 = "Elbette! Bu bir onur meselesi! Bir kızı öyle bir vahşinin bıçağıyla ölüme terk edemem.";
			link.l1.go = "Prosper_8";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1.go = "Prosper_noweapon";
			}
			link.l2 = "Hm. Biliyor musun, bence komutanın söyledikleri mantıklı. Belki önce onun tavsiyesine uymalıyız?";
			link.l2.go = "Prosper_exit";
		break;
		
		case "Prosper_noweapon":
			dialog.text = "Monsieur, kılıcınız nerede?";
			link.l1 = "Sanırım onu kaybettim.";
			link.l1.go = "Prosper_noweapon_1";
		break;
		
		case "Prosper_noweapon_1":
			dialog.text = "That will simply not do. I will wait for you until evening; I advise you to grovel at the feet of our governor and beg for his assistance.";
			link.l1 = "Onun ayaklarına kapanmamı mı istiyorsun? Peki, nasıl istersen...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prosper_getweapon";
			SetFunctionTimerConditionParam("RescueDaughter_Over", 0, 0, 0, 22, false);
		break;
		
		case "Prosper_getweapon":
			dialog.text = "Peki, monsieur? Kendinize bir silah edindiniz mi?";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1 = "Henüz değil, lütfen biraz daha bekleyin...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Prosper_getweapon";
			} else {
				link.l1 = "Anladım. Sana yardım etmeye hazırım!";
				link.l1.go = "Prosper_8";
				DeleteQuestCondition("RescueDaughter_Over");
			}
		break;

		case "Prosper_exit":
			dialog.text = "Tanrım, kaçıyor musun? Hayır! Defol buradan! Korkak!";
			link.l1 = "Hey-hey, sakin ol, seni ahmak! En iyisi dışarı çıkıp Saint-Pierre sokaklarında yardıma ihtiyacı olan bir soylu var mı diye bakayım.";
			link.l1.go = "Prosper_exit_1";
			pchar.questTemp.Sharlie.GigoloMan.SamPodbezhit = true;
		break;
		
		case "Prosper_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			//AddTimeToCurrent(2,0);
			SetCurrentTime(17,30);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 10.0);
			CloseQuestHeader("SharlieF");
			chrDisableReloadToLocation = true;
			
			//Подбегает дворянин с квестом "девочка по вызову"
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Prosper_8":
			dialog.text = "I'm glad there's at least one courageous man in this town. Here, take these three vials. These are health-giving herbs; I bought them from our herbalist. They can be a substantial help to you in battle.";
			link.l1 = "Peki ya sen?";
			link.l1.go = "Prosper_9";
		break;
		
		case "Prosper_9":
			TakeNItems(pchar, "potion1", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "Endişelenme, daha fazlası var. Hazır mısın?";
			link.l1 = "Evet, vakit kaybetmeyelim. İleri!";
			link.l1.go = "Prosper_10";
		break;
		
		case "Prosper_10":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "fortfrance_exittown", "reload", "reload3", "OpenTheDoors", 10.0);
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1 = "location";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1.location = "FortFrance_ExitTown";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition = "RescueDaughter_ProsperGateOutReload";
			AddQuestRecord("SharlieF", "3");
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1.location = "Martinique_jungle_04";
			pchar.quest.Sharlie_RescueDaughter1.function = "RescueDaughter_NearCave";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.hour  = sti(GetTime()+2);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CaveOver";
			NextDiag.CurrentNode = "Prosper_11";
			pchar.questTemp.Sharlie.RescueDaughter = "true";
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", true);//форт
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", true);//джунгли
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", true);//джунгли
		break;
		
		case "Prosper_11":
			dialog.text = "Neredeyse pozisyondayız, "+pchar.name+".   Bu dönemeçten sonra mağaranın girişi var.   Yaklaş, sana planımızı anlatacağım.";
			link.l1 = "Tamamen seni dinliyorum, Prosper.";
			link.l1.go = "Prosper_12";
		break;
		
		case "Prosper_12":
			dialog.text = "Bu ağır tüfekle isabetli nişan almak için zamana ihtiyacım var, ama bana zaman kazandırırsan hedefi kaçırmam. Yakın dövüşe girmek zorunda kalırsam ateş desteğini unut, sadece namluyu sopa gibi kullanarak kendimi savunabilirim. Bu kavga senin kılıç becerine bağlı olacak.";
			link.l1 = "Ne demeye çalışıyorsun?";
			link.l1.go = "Prosper_13";
		break;
		
		case "Prosper_13":
			dialog.text = "Tek yapman gereken onların dikkatini dağıtmak, böylece hepsini vurabileyim. Hareket edip ateş edemem, o yüzden bir yerde sabit duracağım. Mağaranın girişinde üç herif var. Kılıcını çekip olabildiğince hızlı üzerlerine atılmalısın\nBirine vur ve peşine takılmalarını sağla. Onları benden uzaklaştır. Üçü de sana odaklanırsa, sen savuşturup kaçarken ben onları kuş gibi indirebilirim. Ama o vahşiler bana saldırırsa, işimiz biter. Hazır mısın?";
			link.l1 = "This won't be the first time I've handled a sword; these savages are no threat.";
			link.l1.go = "Prosper_14";
			// belamour legendary edition -->
			link.l2 = "Ha! Benim için endişelenme. Le Mans'ta avlanmak gibi bu! Sadece yanlışlıkla arkadan vurma beni!";
			link.l2.go = "Prosper_14a";
		break;
		
		case "Prosper_14a":
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			dialog.text = "Önden git, hemen arkandayım. Unutma: onların bana yaklaşmasına asla izin verme!";
			link.l1 = "Hatırlıyorum, hadi gidelim. İleri!";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_14":
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			// <-- legendary edition
			dialog.text = "O halde harekete geçmeye hazırlan. Önden git, hemen arkandan geliyorum. Unutma: Bana fazla yaklaşmalarına izin veremezsin!";
			link.l1 = "Hatırlıyorum. Elimden gelen her şeyi yapacağım. İleri!";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_15":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_jungle_04", "reload2_back", false);
			NextDiag.CurrentNode = "Prosper_16";
			NewGameTip("A challenging fight awaits ahead. (F6) for quick save.");
		break;
		
		case "Prosper_16":
			dialog.text = "Aferin, "+pchar.name+"! Bu putperest vahşiler artık kimseyi öldüremeyecek. Şimdi asıl meseleye geçelim - mağara. İçeride üç ya da dört kişi olduklarını düşünüyorum, ama emin değilim. Şimdi dinle\nOn yıl önce oradaydım. Mağaranın içinde dar bir tünel var. Bu tünel, ortasında bir delik olan bir duvarla ikiye ayrılmış küçük bir mağaraya açılıyor. Önceki planımızı tekrar edelim. Ben girişin yakınında duracağım, sen ise içeri dalacaksın\nOnları kışkırt, hepsiyle birden dövüşmeye çalışma, sadece bana saldırmalarını engelle. Bahsettiğim tünelde pozisyon al, orası dar, bu yüzden aynı anda en fazla bir ya da iki kişi seninle dövüşebilir\nBen de senin omzunun üzerinden onlara ateş edeceğim. Hazır mısın?";
			link.l1 = "İleri! Bu vahşilerin yuvasını tamamen temizleyelim!";
			link.l1.go = "Prosper_17";
		break;
		
		case "Prosper_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_CaveEntrance", "reload1_back", false);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.location = "Martinique_Grot";
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CreateIndiansGrot";
			NextDiag.CurrentNode = "Prosper_18";
		break;
		
		case "Prosper_18":
			dialog.text = "Kızım hayatta! Tanrıya şükür! Tam zamanında yetiştik. "+pchar.name+". Size borçlandım, efendim. Cesur bir adamsınız ve iyi bir dövüşçüsünüz!";
			link.l1 = "Mutlu sonla bittiğine sevindim, Prosper. O kadar Kızılderiliyi ortadan kaldırmak gerçekten kanlı bir işti.";
			link.l1.go = "Prosper_19";
		break;
		
		case "Prosper_19":
			DialogExit();
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
		break;
		
		case "Prosper_20":
			dialog.text = "Bir kez daha en derin teşekkürlerimi sunarım, "+pchar.name+"! Şimdi hadi kasabaya geri dönelim. Kızımın hayatı paha biçilemez, parayla ölçülemez, ama sana teşekkür etmek için kalan birikimimi vermek istiyorum. Saint-Pierre'e varır varmaz, onları memnuniyetle sana vereceğim. Sakın reddetmeyi düşünme bile!";
			link.l1 = "Reddetmem, Prosper. Sana yardım ederken amacım para değildi zaten.";
			link.l1.go = "Prosper_21";
		break;
		
		case "Prosper_21":
			dialog.text = "Sen gerçek bir Hristiyan şövalyesin, "+pchar.name+" ! Şimdi burada oyalanmayalım. Hemen evimize dönelim!";
			link.l1 = "...";
			link.l1.go = "Prosper_22";
		break;
		
		case "Prosper_22":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Tutorial_Amulet.over = "yes";
			SetLaunchFrameFormParam("Back to the town...", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("FortFrance_town", "reload", "gate_back", "");
			LaunchFrameForm();
		break;
		
		case "Prosper_23":
			SelectPresentAmulet();
			dialog.text = "İşte geldik, Charles. Yardımların için sana bir kez daha teşekkür ediyorum ve bu mütevazı miktardaki peso ile altın dublonları da sözlerime ekliyorum. Dublonları harcamamanı, özel günler için saklamanı öneririm. Bana yaptığın bu iyilik karşılığında bu para az olabilir, ama kalbimin derinliklerinden geliyor. Ayrıca, şu tılsımı da al, "+pchar.questTemp.SMQ.Text+"";
			link.l1 = "Teşekkür ederim! Elveda Prosper, sana ve sevgili kızına mutluluklar dilerim!";
			link.l1.go = "Prosper_24";
		break;
		
		case "Prosper_24":
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", false);//форт
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", false);//джунгли
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", false);//джунгли
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "gold_dublon", 15);
			TakeNItems(pchar, pchar.questTemp.SMQ.Amulet, 1);
			Log_Info("You've received 15 doubloons");
			Log_Info("You've received an amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ah, senin gibi bir koca ona iyi gelir. Zavallı kız, şehirde peşinden koşan ince bacaklı, çenesiz züppelerden başka bir şey görmüyor. Ne yazık ki, hepsi birer birer ortadan kayboldu... iyi de oldu. Bol şans, Charles!";
			link.l1 = "...";
			link.l1.go = "Prosper_25";
		break;
		
		case "Prosper_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload10_back", "none", "", "", "", 10.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 120);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 70);//скрытность
			AddQuestRecord("SharlieF", "7");
			CloseQuestHeader("SharlieF");
			DeleteAttribute(pchar, "questTemp.SMQ");
			pchar.questTemp.Prosper_fmql = "true"; // Addon-2016 Jason, французские миниквесты (ФМК)
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra Требуется для квеста "Знакомство с индейцами"
			pchar.quest.Sharlie_JungleNative.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleNative.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Sharlie_JungleNative.function = "SharlieJungleNative";
			SetCurrentTime(17,30);
			//AddTimeToCurrent(2,0);
			//QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Selina":
			dialog.text = "Ah! Tanrım yardım et! (ağlayarak) Burada neler yaşandığını hayal bile edemezsin! Bu... bu yerliler bizi buraya sürüklediler, öldürüp yemeye geldiler! Cesar Blanchet de buradaydı... Vahşiler onu aldılar... Korkunç, şeytani bir ayin yaptılar ve sonra... Tanrım, anlatmaya bile dilim varmıyor! Sıradaki ben olacaktım! Beni... yarın keseceklerdi!";
			link.l1 = "Sakin ol, Celine. Her şey bitti. O alçaklar hak ettiklerini buldu ve artık kimseye zarar veremeyecekler.";
			link.l1.go = "Selina_1";
		break;
		
		case "Selina_1":
			dialog.text = "Gilbert Coursie de burada. Şurada... o, şey... hâlâ kendine gelemedi. Onunla konuş... Sonra hemen buradan çıkalım!";
			link.l1 = "Tamam, tamam. Her şey yolunda, kızım. Ağlama artık. Her şey iyi olacak. Harika bir baban var. Sana kimsenin zarar vermesine izin vermez... Şimdi dışarı çık, ben de...  Gilbert'i buradan çıkarayım, sonra sana katılırım.";
			link.l1.go = "Selina_2";
		break;
		
		case "Selina_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			sld = characterFromId("RD_Prosper");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_1", "", 5.0);
			AddQuestRecord("SharlieF", "5");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
		break;
		
		case "Selina_3":
			dialog.text = "Tanrı ve Kutsal Meryem dualarımı işitti! Bizi kurtarmaya mı geldiniz?";
			link.l1 = "Sen... Senin adın Celine, değil mi?";
			link.l1.go = "Selina_4";
		break;
		
		case "Selina_4":
			dialog.text = "Evet... (ağlayarak) Burada neler yaşandığını hayal bile edemezsin! Bu... bu yerliler bizi buraya sürüklediler, öldürüp yiyeceklerdi! Cesar Blanchet de buradaydı... Onu aldılar... Şeytani bir ayin yaptılar ve sonra... Tanrım, anlatmaya bile dilim varmıyor! Sırada ben varmışım! Yarın beni boğazlayacaklardı...";
			link.l1 = "Sakin ol, küçük kız... Üzgünüm, ama sana kötü bir haberim var. Buraya babanla geldim. Dışarıda, sana ulaşmaya çalışırken o kırmızı derili vahşiler tarafından öldürüldü. Seni kurtarmak için hayatını verdi.";
			link.l1.go = "Selina_5";
		break;
		
		case "Selina_5":
			dialog.text = "Ne?! Babam... Tanrım! Ben... Ben... (ağlar)";
			link.l1 = "Başın sağ olsun, Celine. Burada seninle birlikte başka biri daha var, değil mi?";
			link.l1.go = "Selina_6";
		break;
		
		case "Selina_6":
			dialog.text = "(gözyaşları içinde) Evet... Gilbert Coursie. O içeride... Hâlâ kendine gelemedi. Git onunla konuş... Sonra buradan hemen çıkalım!";
			link.l1 = "Evet, tabii ki. Burada durup vakit kaybedemeyiz.";
			link.l1.go = "Selina_7";
		break;
		
		case "Selina_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			AddQuestRecord("SharlieF", "6");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
			AddComplexSelfExpToScill(20, 20, 20, 20);
		break;
		
		case "Selina_8":
			dialog.text = "Babam... Zavallı, sevgili babam! Ah, efendim, beni kurtardığınız için size henüz teşekkür bile etmedim...";
			link.l1 = "Selina, senin ve Gilbert’ın o mağaradan sağ çıkmasına gerçekten sevindim. Babanın kahramanca ölümü boşa gitmedi.";
			link.l1.go = "Selina_9";
		break;
		
		case "Selina_9":
			dialog.text = "(ağlayarak) Lütfen, monsieur, bizi de kasabaya götürün. Askerlere haber göndermemiz gerek, babamın bedenini gelip alsınlar ki, ona layıkıyla Hristiyan usulü bir cenaze töreni yapılabilsin...";
			link.l1 = "Elbette, Celine. Beni takip et!";
			link.l1.go = "Selina_10";
		break;
		
		case "Selina_10":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Selina_11":
			dialog.text = "Teşekkür ederim, monsieur, zavallı babama eşlik ettiğiniz için... Beni kesin bir ölümden kurtardığınız için teşekkür ederim. Ben... Ben... Buyurun, bu kese altını alın. Evde, babamın sandığında buldum. Lütfen, sakın reddetmeyi düşünmeyin!";
			link.l1 = "Teşekkür ederim, Celine. Seni kurtarabildiğimize sevindim. Ve babanı kaybetmenin acısını yürekten paylaşıyorum.";
			link.l1.go = "Selina_12";
		break;
		
		case "Selina_12":
			TakeNItems(pchar, "gold_dublon", 15);
			PlaySound("interface\important_item.wav");
			dialog.text = "Gerçekten asil bir insansınız, monsieur. Sizi asla unutmayacağım. Elveda!";
			link.l1 = "Elveda, Celine.";
			link.l1.go = "Selina_13";
		break;
		
		case "Selina_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			AddQuestRecord("SharlieF", "8");
			CloseQuestHeader("SharlieF");
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra Требуется для квеста "Знакомство с индейцами"
			
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Jilberte":
			PlaySound("Voice\English\other\robinzons-08.wav");
			dialog.text = "Tanrım, gerçekten her şey geride mi kaldı? Buna inanmakta zorlanıyorum... Hem beni hem de Celine'i kurtardın. Sen olmasaydın, zavallı Cesar'ın başına gelenlerin aynısı yarın onu bekliyor olacaktı, birkaç gün sonra da bana hazırlanmış olacaktı.";
			link.l1 = "Bu yerliler, gerçekten yamyam mı?!";
			link.l1.go = "Jilberte_1";
		break;
		
		case "Jilberte_1":
			dialog.text = "Şüphe mi ediyorsun? Miden sağlamsa, git yemek ateşlerinin külüne bak. Zavallı Cesar'ı orada bulacaksın. Şimdi sadece kemikleri kalmış...";
			link.l1 = "Kutsal Sakrament... Yok, ben almayayım. Daha yeni Avrupa'dan geldim ve dünyada hâlâ böyle iğrenç, şeytani şeylerin yaşandığını hayal bile edemezdim.";
			link.l1.go = "Jilberte_2";
		break;
		
		case "Jilberte_2":
			dialog.text = "Karayipler'de çok tuhaf şeyler olur, Eski Dünya'da sadece fısıltılarını duyduğun şeyler... Kızılderili şamanlar, büyü, gizli ayinler. Burada biraz daha kalırsan, her türlü şeytanlığa şahit olursun. Ama affet beni, seni kurtardığın için hâlâ teşekkür etmedim – hâlâ şoktayım\nHayatımı kurtardın ve minnettarlığımı sadece sözle değil, altınla da göstereceğim. Celine ve beni şehre kadar koru. Orada sana hak ettiğin gibi teşekkür edebileceğim, monsieur.";
			link.l1 = "Pekala. Dışarı çık. Önce burada biraz etrafa bakacağım.";
			link.l1.go = "Jilberte_3";
		break;
		
		case "Jilberte_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_3", "OpenTheDoors", 10.0);
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1.location = "Martinique_CaveEntrance";
			pchar.quest.Sharlie_RescueDaughter5.function = "RescueDaughter_GoHome";
		break;
		
		case "Jilberte_4":
			dialog.text = "Bir kez daha beni kurtardığınız için size en derin şükranlarımı sunmama izin verin, monsieur! Söz verdiğim gibi, sözlü teşekkürlerime gümüş peso ve altın dublonlardan oluşan maddi bir teşekkür de ekliyorum.";
			link.l1 = "Her şeyin en iyi şekilde sonuçlanmasına sevindim, Gilbert.";
			link.l1.go = "Jilberte_5";
		break;
		
		case "Jilberte_5":
			AddMoneyToCharacter(pchar, 3000);
			TakeNItems(pchar, "gold_dublon", 20);
			Log_Info("You've received 20 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Bunun için ne kadar mutlu olduğumu tahmin bile edemezsiniz! Bir kez daha teşekkür ederim ve müsaadenizle ayrılıyorum, monsieur.";
			link.l1 = "İyi şanslar, Gilbert! Bu arada, Saint-Pierre'de başka birinin yardıma ihtiyacı olup olmadığını biliyor musun?";
			link.l1.go = "Jilberte_6a";
		break;
		
		case "Jilberte_6a":
			dialog.text = "Bilmiyorum, ama... Sokakta dolaşan vatandaşlara sorabilirsiniz, Mösyö. Sıradan kasaba halkı, hatta hali vakti yerinde olanlar bile muhtemelen kayda değer bir şey sunmaz, ama zengin soylular... belki size bir iş verebilirler.";
			link.l1 = "Anladım Gilbert, teşekkürler. Görüşürüz!";
			link.l1.go = "Jilberte_6";
		break;
		
		case "Jilberte_6":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.RescueDaughter");
			
			//Подбегает дворянин с квестом "девочка по вызову"
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			sld.talker = 9;
			LAi_SetCitizenType(sld);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Dinle, ben bu şehrin kanunlara saygılı bir vatandaşıyım. Senden ricam, bir haydut gibi kılıcını açıkta taşımaman.","Beyefendi, lütfen, yasa açık: şehir surlarının içinde kimse silahını çekerek dolaşamaz.");
			link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ.","Nasıl istersen...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

void SelectPresentAmulet()
{
	switch (pchar.HeroParam.HeroType)
	{        
		case "HeroType_1":
			pchar.questTemp.SMQ.Amulet = "indian_7";
			pchar.questTemp.SMQ.Text = "it adds endurance and gives a second wind.";
		break;
		
		case "HeroType_2":
			pchar.questTemp.SMQ.Amulet = "amulet_7";
			pchar.questTemp.SMQ.Text = "it heightens resilience to battle wounds.";
		break;
		
		case "HeroType_3":
			pchar.questTemp.SMQ.Amulet = "indian_4";
			pchar.questTemp.SMQ.Text = "it raises the attack strength of your weapons.";
		break;
		
		case "HeroType_4":
			pchar.questTemp.SMQ.Amulet = "indian_1";
			pchar.questTemp.SMQ.Text = "it makes fire weaponry much more lethal.";
		break;
	}
}
