// Джон Мердок, он же Йохан ван Мерден, соратник Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		if (!CheckAttribute(pchar, "questTemp.HWIC.Self") && LAi_grp_playeralarm > 0)
		{
			dialog.text = "Beyefendi, sohbet için hiç de uygun bir zaman seçmediniz. Bütün garnizon sizi arıyor. En iyisi hemen ortadan kaybolun...";
			link.l1 = "Merak etme. Uzun süre kalmayacağım.";
			link.l1.go = "exit";
			break;
		}
		// продажа алхимического набора, если провалил гамбит
		if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && !CheckAttribute(npchar, "quest.alchemy"))
		{
			bOk = (findsubstr(pchar.questTemp.HWIC.Detector, "_fail" , 0) != -1) || (pchar.questTemp.HWIC.Detector == "eng_win_half");
			if (bOk)
			{
				dialog.text = "Hoş geldiniz, kaptan. İlginç bir teklife ilginiz olur mu? ";
				link.l1 = "Buradaki herkesin böyle teklifleri var gibi görünüyor ve ben de meraklı bir adamım. Nedir bu? ";
				link.l1.go = "alchemy";
				break;
			}
		}
		// Страж Истины
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok1")
		{
			dialog.text = "İyi günler. Eczaneme hoş geldiniz. Çoğu hastalık ve rahatsızlık için ilaçlarım var. Size ne sunabilirim?";
			link.l1 = "Dinle John, ikinci katta senin evinde birinin yaşadığına dair söylentiler var...";
			link.l1.go = "guardoftruth";
			break;
		}
//-----------------------------------------за Голландию------------------------------------------------
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.location.from_sea == "SentJons_town" && pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "İyi günler. Eczanemde sizi görmekten memnuniyet duydum. Çoğu hastalık ve rahatsızlık için ilaçlarım var. Size ne sunabilirim?";
				link.l1 = "Merhaba Bay Murdock. Lucas Rodenburg adına buradayım. Beni size Richard Fleetwood ile ilgili bir meseleyi görüşmek için gönderdi.";
				link.l1.go = "Knippel_exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "İyi günler. Ne tür bir şikayetiniz var? Hem öksürük şurubum hem de ishal tozum var!";
				link.l1 = "Merhaba Bay Murdock. Lucas Rodenburg adına buradayım. Beni size Richard Fleetwood ile ilgili bir meseleyi konuşmam için gönderdi.";
				link.l1.go = "Knippel";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "KillMerdok")
			{
				dialog.text = "Ahhh, işte Rodenburg'un tuttuğu köpek... Hercule, Longway - lütfen buraya gelir misiniz?\nŞu adamı öldürün!";
				link.l1 = "Durun, reçetem var!";
				link.l1.go = "Merdok_fight";
				break;
			}
			dialog.text = "İyi günler. Sizi eczanemde görmekten memnuniyet duydum. Çoğu hastalık ve rahatsızlık için ilaçlarım var. Size ne sunabilirim?";
			link.l1 = "Şu anda bir şey istemiyorum, teşekkürler. Kendimi gayet iyi hissediyorum.";
			link.l1.go = "exit";
			break;
		}
//----------------------------------------------за Англию---------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "MerdokMeeteng")
			{
			dialog.text = "Merhaba, davetsiz misafir. Yüzünü maske ile gizlememişsin ve bir hayduta da benzemiyorsun. O halde, zavallı bir eczacıdan başka bir şey istediğini düşünüyorum. Belki ishal için bir şeyler mi lazım?";
			link.l1 = "Sana da merhaba, Johan van Merden. Hercule Tonzag'dan selam getirdim. İsmi bildiğini görüyorum.";
			link.l1.go = "Merdok_talk";
			DelLandQuestMark(npchar);
			break;
			}
//--------------------------------------------против всех--------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "HuntFleetwood")
				{
					dialog.text = "Ah, demek buradasın. Peki, Hercule ile tanıştın mı? ";
					link.l1 = "Evet. Anlaştık. John, Hercule'e yardım edeceğim ve Richard Fleetwood hakkında sana birkaç sorum var.";
					link.l1.go = "About_Fleetwood";
					break;
				}
				if (GetQuestPastDayParam("questTemp.Wait_Fleetwood") > 6 && pchar.questTemp.HWIC.Self == "WaitFleetwood")
				{
					dialog.text = "Merhaba! Seni gördüğüme sevindim, "+pchar.name+"!";
					link.l1 = "Merhaba, John. Fleetwood hakkında bir şey öğrenebildin mi?";
					link.l1.go = "About_Fleetwood_9";
					pchar.quest.Wait_FleetwoodOver.over = "yes"; //снять таймер
					break;
				}
				if (pchar.questTemp.HWIC.Self == "HWICSelf_fail")
				{
					dialog.text = "Geç kaldın. Kuş çoktan uçtu. Charlie Knippel Willemstad'a uğradı ve oradan Richard için bir kız getirdi. Şimdi bir iki güne askeri bir filoyla İngiltere'ye doğru yelken açacaklar. Fleetwood gitti, bu hayatta onu bir daha göremezsin.";
					link.l1 = "Kahretsin. Richard'ı tamamen unutmuşum ve zamanın nasıl geçtiğini fark etmemişim. Görüşürüz.";
					link.l1.go = "About_Fleetwood_17";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileOnShip")
				{
					dialog.text = "Tekrar hoş geldin, "+pchar.name+"! Şu anda senin için bir şey yok. Fleetwood hakkında bir haber yok, Charlie Knippel ise hâlâ Curaçao'dan dönmedi...";
					link.l1 = "Ve asla da olmayacak. Ne o, ne de brigantini.";
					link.l1.go = "Abigile";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInHouse")
				{
					dialog.text = "Ah, misafirlerimiz var! Merhaba, Charlie! İyi günler, Hanımefendi!";
					link.l1 = "İyi günler, John! Sana bayan arkadaşımı tanıtayım, Richard’ın nişanlısı, zarif Abigail Shneur.";
					link.l1.go = "Abigile_7_1";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInRoom")
				{
					dialog.text = "Sessini alçalt... Bundan sonra ne yapacaksın?";
					link.l1 = "Sırada ne var? Aslında biraz uyumak isterdim, ama maalesef buna vaktim yok. Fleetwood'u saklandığı delikten çıkarıp Hercule'ün işini bitireceğim.";
					link.l1.go = "Abigile_9";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "LetterToFleetwood")
				{
					dialog.text = "Yazmayı bitirdin mi? Bakayım... Tanrım Charlie, tam bir delisin! Sence de bu biraz fazla ayrıntılı olmadı mı? Yani, Bayan Shneur'un parmakları, kulakları ve yüzüyle ilgili kısım? Kesinlikle hastalıklı bir yeteneğin var. Kahretsin, neredeyse midem bulanacak!";
					link.l1 = "Blöf yapıyorum, John. Kızı öldürmeyeceğim. Parmağını koparmasını sağlayabilirim... Ama fazlası olmaz. Sonuçta dokuz tane daha var.";
					link.l1.go = "Abigile_15";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodAgree")
				{
					dialog.text = "İyi geçti mi? Gözlerinden anlıyorum - başardın!";
					link.l1 = "Evet. Fleetwood şartlarımı kabul etti. Tuzak kapanıyor. Şimdi bekleyeceğiz.";
					link.l1.go = "Abigile_23";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodDied")
				{
					dialog.text = "Ah, tekrar hoş geldin, dostum! Bana ne anlatabilirsin?";
					link.l1 = "Fleetwood öldü. Her şey planladığım gibi gitti. Adaya geldiğinde, sahilde ona bir pusu kurmuştum. Sert bir direniş gösterdi ama nafileydi. O sahilden yalnızca birimiz sağ çıktı.";
					link.l1.go = "Abigile_27";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "MeetTonzag")
				{
					dialog.text = "Pekâlâ "+pchar.name+",   Sana ciddi bir teklifim var. Konuşacağım konu oldukça tehlikeli, ama Fleetwood'dan kurtulma şekline bakınca bunun da üstesinden gelebileceğinden eminim. Zor meseleleri çözmekte...nadir rastlanan bir yeteneğin var.";
					link.l1 = "İltifatınız için teşekkürler. Devam edin.";
					link.l1.go = "Lucas";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SeekAbiIsland")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "Tekrar hoş geldin, "+pchar.name+" ! Benim için iyi bir haber var mı?";
					link.l1 = "John, artık yastığının altına bıçak koymadan rahatça uyuyabilirsin. Lucas artık senin için bir tehdit değil. Tutuklandı ve hapse atıldı, yakında Hollanda'ya gönderilecek ve orada isyan, cinayete teşebbüs ve başka suçlardan yargılanacak.";
					link.l1.go = "Lucas_10";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "Seni gördüğüme sevindim, "+pchar.name+"! Hayattasın - bu iyi bir şey. Yeni bir haber var mı?";
					link.l1 = "Evet. Van Berg sonsuza dek gitti. Dediğin gibi, beni buldu ve en uygunsuz anda saldırdı. Van Berg zorlu biriydi, ama sonunda onu alt ettim.";
					link.l1.go = "Final";
					break;
				}
			dialog.text = "Başka bir şeye ihtiyacın var mı?";
			link.l1 = "Hayır, John, hiçbir şey yok. Gidiyorum.";
			link.l1.go = "exit";
			break;
			}
			dialog.text = "İyi günler. Eczanemde sizi görmekten mutluluk duydum. Çoğu hastalık ve rahatsızlık için ilaçlarım var. Size ne sunabilirim?";
			link.l1 = "Şu anda bir şey istemiyorum, teşekkür ederim. Kendimi gayet iyi hissediyorum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------за Голландию-----------------------------------------------------
		case "Knippel_exit":
			dialog.text = "Ne dediğiniz hakkında hiçbir fikrim yok, efendim. Lucas Rodenburg kim? Hollandalılarla hiçbir işim olmadı. Beni biriyle karıştırıyor olmalısınız.";
			link.l1 = "Ne? Bay Rodenburg beni size gönderdi!";
			link.l1.go = "Knippel_exit_1";
		break;
		
		case "Knippel_exit_1":
			dialog.text = "Sana bir kez daha söyleyeyim - Mynheer Rodenburg adında bir adamı tanımıyorum. Hollandalılarla da işim olmaz. Şu dünyada tahammül edemediğim iki şey var: başkalarının kültürlerine saygı göstermeyen insanlar ve Hollandalılar. O yüzden ilaca ihtiyacın yoksa, lütfen beni işimle baş başa bırak.";
			link.l1 = "İyice tuhaflaşıyor bu işler...";
			link.l1.go = "exit";
		break;

		case "Knippel":
			dialog.text = "Pekâlâ, pekâlâ... Mynheer Rodenburg'dan mı geliyorsun? Peki. Dinliyorum.";
			link.l1 = "Kaptan Fleetwood ile tenha bir yerde buluşmam gerekiyor. 'Mirage'ı, Bay Fleetwood'un yakalamak için can attığı Hollandalı korsan Jacob van Berg'den ödünç aldım. Ona, 'Mirage'ın yakın zamanda Dominika kıyılarında kolayca bulunabileceğini bildirmek istiyorum. ";
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			dialog.text = "Jacob sana gemisini mi verdi? Hm, demek şimdi sana 'Mirage'ın yakında Dominika kıyılarında olacağını Bay Fleetwood'a bildirecek biri lazım, çünkü bazı özel sebeplerden dolayı bunu Richard'a kendin söyleyemiyorsun...";
			link.l1 = "Aynen öyle. Bay Rodenburg bu meseleyi size iletmemi tavsiye etti.";
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			dialog.text = "Bu durumda, ihtiyacın olan adam Charlie Knippel. Fleetwood'un sadık bir dostu... ve onun casusu. Onunla konuş ve Richard'ın bilmesini istediğin her şeyi anlat. Dikkatli ol, Knippel oldukça sıradan biri gibi görünebilir, ama kesinlikle aptal değildir.\nOnu deniz kıyısından çok uzakta olmayan küçük bir kulübede bulabilirsin. Orada olmalı.";
			link.l1 = "Anladım. Teşekkür ederim, Bay Murdock. Hoşça kalın!";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "toKnippel";
			AddQuestRecord("Holl_Gambit", "1-16");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
		break;
		
		case "Merdok_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			sld = characterFromId("Tonzag");
			PlaySound("Voice\English\hambit\Ercule Tongzag-04.wav");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			//а вот и китаец нарисовался
			sld = characterFromId("Longway");
			LAi_SetWarriorType(sld);
			FantomMakeCoolFighter(sld, 18, 40, 40, "blade_08", "pistol1", "bullet", 70);
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayEnemy"))//враг
			{
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, "EnemyFight");
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayFriend"))//друг
			{
				LAi_warrior_DialogEnable(sld, true);
				sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
				sld.dialog.currentnode = "Longway_hire";
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayNeutral")) sld.lifeday = 0;//нейтрал - просто нет
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattle");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//-------------------------------------------------за Англию-----------------------------------------------------
		case "Merdok_talk":
			dialog.text = "Gerçekten mi? Zavallı Gaston'un çoktan cehennemde yanmakta olduğunu sanıyordum.";
			link.l1 = "Olabilir, ama Gaston gibi biri gerçekten yok. Kafasını gizli adadaki yaşlı bir Yahudinin hazinesinde buldum. Ama yine de sana selam göndermeyi başardı. Ayrıca ortak bir düşmanımız olduğunu söyledi: Bay Rodenburg. Tonzag, Lucas için önemli olabilecek bazı belgelerin sende olabileceğini ve bunların onu Curaçao’daki saklandığı yerden çıkarabileceğini söyledi.";
			link.l1.go = "Merdok_talk_1";			
		break;
		
		case "Merdok_talk_1":
			dialog.text = "O haklıydı. Rodenburg'u uykusuz bırakan şey benim arşivim. Görünen o ki, hâlâ burada oyalanmasının tek sebebi de bu. Mesele şu: Ona Birleşik Eyaletler'deki Şirketin Direktörler Komitesinde rahat bir iş vaat edilmişti. Lucas'ın geçmişi ve bugünüyle ilgili pek çok ilginç bilgiyi içeren bu arşivdeki bilgiler yayılırsa, kariyer hayalleri suya düşer. O durumda, umabileceği en iyi şey asılmak yerine kafasının kesilmesi olur.";
			link.l1 = "Arşivi bana ver, düşmanımızla ben ilgileneceğim.";
			link.l1.go = "Merdok_talk_2";			
		break;
		
		case "Merdok_talk_2":
			dialog.text = "Beni aptal mı sanıyorsun? Hâlâ hayattaysam, bu hâlâ yanımda olduğu içindir. Şimdi Lucas için çalışmadığından nasıl emin olabilirim?";
			link.l1 = "Sözüme güvenmek zorundasın - yoksa ölürsün.";
			link.l1.go = "Merdok_talk_3";			
		break;
		
		case "Merdok_talk_3":
			PlaySound("Voice\English\hambit\John Mardock-07.wav");
			dialog.text = "Yanlış cevap, burada ve şimdi öleceksin! Longway, gongji!";
			link.l1 = "Oh ho, Çinli gölgelerden çıkıyor! Merak etmeyin, ikinizi de doğrayacağım!";
			link.l1.go = "Merdok_fightEng";			
		break;
		
		case "Merdok_fightEng":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");	
			sld = characterFromId("Longway");
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_08", "pistol1", "bullet", 80);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
			PlaySound("Voice\English\hambit\Longway-02.wav");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattleEng");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//----------------------------------------против всех-------------------------------------------------------
		case "MC_InHouse":
			PlaySound("Voice\English\hambit\John Mardock-02.wav");
			dialog.text = "Sonunda kendine geldin. Uyanmayacaksın diye korkmuştum.";
			link.l1 = "Ne...? Sen kimsin? Ben neredeyim böyle? Buraya nasıl geldim?";
			link.l1.go = "MC_InHouse_1";	
		break;
		
		case "MC_InHouse_1":
			dialog.text = "Sakin ol, bu kadar çok soruyu bir anda sorma, fazla heyecanlanman senin için iyi olmaz. Benim adım John Murdock, St. John's'ta eczacıyım. Fleetwood'un adamlarıyla kavga ederken bayıldın. Doğrusu, seni fena benzetmişler... Seni buraya eczaneme getiren Hercule oldu ve, şey, yaralarını iksirlerimle ve ilaçlarımla tedavi ettim.";
			link.l1 = "Hercule? Kim? Sokakta bana yardım eden adam mı? ";
			link.l1.go = "MC_InHouse_2";			
		break;
		
		case "MC_InHouse_2":
			dialog.text = "Evet. O, tam da kendisi. Bu arada, seninle konuşmak istiyor. Onunla şehirde buluşman gerek. Hâlâ yürüyebiliyor musun? Güzel. Gece dışarı çık - evimin giriş katındaki kapının arkasından başlayan gizli tüneli kullan. Hava kararana kadar çıkma - Fleetwood'un adamları seni arıyor.";
			link.l1 = "Evet... Gemim nerede?";
			link.l1.go = "MC_InHouse_3";			
		break;
		
		case "MC_InHouse_3":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Geminiz el konuldu ve mürettebatınız, Fleetwood'un adamları tarafından öldürülmekten korkarak dağıldı. Üzgünüm.";
				link.l1 = "Siktir...";
			}
			else
			{
				dialog.text = "Liman’da, her zamanki yerinde.";
				link.l1 = "Oh...bunu duyduğuma sevindim. Onu kaybettim sanmıştım.";
			}
			link.l1.go = "MC_InHouse_4";			
		break;
		
		case "MC_InHouse_4":
			dialog.text = "Hercule ile tanışmalısın. Gizli tünelden geçerek gece şehre git. O sana yaklaşacak. Şimdi biraz dinlen, benim de işime dönmem gerek.";
			link.l1 = "Pekala, John. Ve... bana yardım ettiğin ve beni iyileştirdiğin için teşekkür ederim!";
			link.l1.go = "MC_InHouse_5";
		break;
		
		case "MC_InHouse_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			npchar.greeting = "merdok_2";
			AddQuestRecord("Holl_Gambit", "3-12");
			pchar.questTemp.HWIC.Self = "MainBegin";//новый флаг квеста
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.greeting = "barmen_1";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", true);//закрыть выход из аптеки через дверь
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//открыть подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//открыть дом из подземелья
			pchar.quest.Tonzag_Meeting.win_condition.l1 = "location";
			pchar.quest.Tonzag_Meeting.win_condition.l1.location = "SentJons_town";
			pchar.quest.Tonzag_Meeting.win_condition.l2 = "Night";
			pchar.quest.Tonzag_Meeting.function = "TonzagMeeting";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);	
		break;
		
		case "About_Fleetwood":
			DelLandQuestMark(npchar);
			dialog.text = "Fleetwood mu? Onun hakkında ne bilmek istiyorsun?";
			link.l1 = "Her şeyi. Bildiğin her şeyi anlat bana. Görüyorum ki, Hercule'ün Antigua'ya neden geldiği senden gizli değil. Ben onun tarafındayım.";
			link.l1.go = "About_Fleetwood_1";
		break;
		
		case "About_Fleetwood_1":
			dialog.text = "Pekala. Kraliyet— yani, Cemiyet Donanması'ndan Kaptan Richard Fleetwood... lanet olsun, şu fanatik Cromwell'in başa geçtiğini ve ismi değiştirdiğini sürekli unutuyorum. Her neyse, Fleetwood iyi bir savaşçı ve deneyimli bir denizci. 'Valkyrie' adında bir brig komuta ediyor— ayrıca harika bir gemidir, seçkin denizciler ve deniz piyadelerinden oluşan bir mürettebatı var. Birleşik Eyaletler'e genel olarak, özellikle de Hollanda Batı Hindistan Şirketi'ne karşı kendi özel savaşını yürütüyor. Sayısız Hollanda ticaret gemisini yağmaladı ve sigorta maliyetlerini fırlattı. Curaçao valisi, onun başına rekor kıran bir ödül koydu.";
			link.l1 = "Hmm... 'Ortaklık Donanması' subayının korsanlığa yönelmesi biraz tuhaf görünüyor...";
			link.l1.go = "About_Fleetwood_2";
		break;
		
		case "About_Fleetwood_2":
			dialog.text = "Evet, gerçekten de öyle. O, ince bir ipte yürüyor. İngilizler resmî olarak onun eylemlerini tanımıyor ve hiçbir şekilde ilişki kurmayı reddediyorlar, ama perde arkasında onu aslında cesaretlendiriyorlar. Karayipler’deki İngiliz casus ağıyla bir şekilde bağlantısı olduğuna dair sebeplerim var ve o alçaklarla şaka olmaz.";
			link.l1 = "Ciddi bir adam... Hepsi bu mu? Hercule bana yardımcılarından birinden bahsetmişti... başka bir Charlie... adı neydi... Canister mıydı? Cannonball?";
			link.l1.go = "About_Fleetwood_3";
		break;
		
		case "About_Fleetwood_3":
			dialog.text = "Knippel mi? Evet, öyle biri var. Charlie Knippel eskiden İngiliz Donanması'nda baş topçuydu, şimdi emekli. Şimdi kıyıda sakin bir hayat sürüyor. O, St. John's'ta Fleetwood'un gözü kulağıdır, bu yüzden ona dikkat et ve Richard hakkında ona soru sormayı aklından bile geçirme – kendini hapiste ya da daha beter bir durumda bulursun.";
			link.l1 = "Anladım. Fleetwood hakkında bahsetmeye değer başka bir şey söyleyebilir misin?";
			link.l1.go = "About_Fleetwood_4";
		break;
		
		case "About_Fleetwood_4":
			dialog.text = "Antigua'da on altıdan altmışa tüm kadınların gözdesi. Hakkında söylenecek başka bir şey yok gibi. Sanırım artık başına ne geldiğini biliyorsun. Şimdi yataktan çıkmıyor, yaralarını sarıyor.";
			link.l1 = "Onun da mutlaka bazı zayıf yönleri ya da zaafları vardır...";
			link.l1.go = "About_Fleetwood_5";
		break;
		
		case "About_Fleetwood_5":
			dialog.text = "Ne demek istiyorsun?";
			link.l1 = "Belki kumar oynamayı sever, ya da çok içer, ya da güzel kadınlara karşı koyamaz - bu tür bir şeydir. Evli mi?";
			link.l1.go = "About_Fleetwood_6";
		break;
		
		case "About_Fleetwood_6":
			dialog.text = "Hayır, bekar. Bahsettiğiniz şeylerden hiçbiriyle tanınmaz.";
			link.l1 = "Anlıyorum. Ama belki onda yine de özel bir şeyler vardır? Onun gibi birinin bile mutlaka zayıf bir noktası olmalı!";
			link.l1.go = "About_Fleetwood_7";
		break;
		
		case "About_Fleetwood_7":
			dialog.text = "Bilmiyorum. Bak, şöyle yapalım. Bir hafta sonra yanıma gel, ben de Fleetwood'un özel hayatını araştırayım. Anlaştık mı?";
			link.l1 = "Anlaştık. Teşekkürler, John! Bir hafta sonra burada olacağım.";
			link.l1.go = "About_Fleetwood_8";
		break;
		
		case "About_Fleetwood_8":
			DialogExit();
			pchar.questTemp.HWIC.Self = "WaitFleetwood";
			SaveCurrentQuestDateParam("questTemp.Wait_Fleetwood");
			SetFunctionTimerCondition("Wait_FleetwoodQM", 0, 0, 7, false);
			SetFunctionTimerCondition("Wait_FleetwoodOver", 0, 0, 12, false);//чтобы не опаздывал
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", false);//открыть выход из аптеки
			AddQuestRecord("Holl_Gambit", "3-14");
		break;
		
		case "About_Fleetwood_9":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Evet, ama maalesef pek fazla değil. Hem de sanırım pek bir işe yaramaz, ne yazık ki.";
			link.l1 = "Dökül bakalım! Fleetwood'la ilgili en ufak ayrıntı bile önemli.";
			link.l1.go = "About_Fleetwood_10";
		break;
		
		case "About_Fleetwood_10":
			dialog.text = "Kısa bir süre önce, Richard bilinmeyen bir adadan iki Yahudi mülteciyi – yaşlı bir adam ve kızını – Willemstad'a götürmek üzere aldı. Bindikleri gemi korsanlar tarafından batırılmıştı. Fleetwood onları gizlice Curaçao'ya getirdi, kendi hayatını riske atarak. O günden bu yana birkaç ay geçti. Şimdi ise sadık adamı Charlie Knippel'i Willemstad'a yolladı...";
			link.l1 = "Hmm... Bunun bağlantısı ne?";
			link.l1.go = "About_Fleetwood_11";
		break;
		
		case "About_Fleetwood_11":
			dialog.text = "Charlie'nin Willemstad'dan buraya bir kızı getirmesi için emir aldığını öğrendim, adı Abigail Shneur, Yahudi bir kız. Evet, adadaki aynı kız. Görünüşe göre Richard ona âşık olmuş, çünkü en iyi ajanını onun için gönderiyor.\nHepsi bu. Yardımcı olur mu bilmiyorum.";
			link.l1 = "Oh ho ho! Hahaha! Görünen o ki, bizim onulmaz bekarımız Yahudi kadının kurnaz cazibesine kapılmış. Bu harika bir iş, John, teşekkürler! Şimdi, dostumuz Knippel Curaçao'ya ne zaman yola çıkacak?";
			link.l1.go = "About_Fleetwood_12";
		break;
		
		case "About_Fleetwood_12":
			dialog.text = "Dün ayrıldı.";
			link.l1 = "Hangi gemide?";
			link.l1.go = "About_Fleetwood_13";
		break;
		
		case "About_Fleetwood_13":
			dialog.text = "Bunu soracağını biliyordum. O, İngiliz Milletler Topluluğu’nun hizmetindeki bir brigantinada—aman, boşver, 'Kraliyet Donanması' işte. Geminin adı 'Zeekalf'.";
			link.l1 = "'Zeekalf'? Bu, bir İngiliz gemisi için epey Hollanda işi bir isim... ahhh, anladım.";
			link.l1.go = "About_Fleetwood_14";
		break;
		
		case "About_Fleetwood_14":
			dialog.text = "Senin kafan hızlı çalışıyor... Önceki adı 'Royal Mary'ydi, ama bu seferki yolculuk için adı 'Zeekalf' oldu. Ve şu anda Hollanda bayrağı çekili.";
			link.l1 = "Yardımın paha biçilmezdi, John. Şimdi yola çıkıyorum. Yakında döneceğim ve iyileşirken beni ağırladığın ikinci kattaki odana tekrar ihtiyacım olacak.";
			link.l1.go = "About_Fleetwood_15";
		break;
		
		case "About_Fleetwood_15":
			dialog.text = "Ne yapıyorsun?";
			link.l1 = "Her şeyi döndüğümde anlatacağım. Bana şans dile, John! Hoşça kal.";
			link.l1.go = "About_Fleetwood_16";
		break;
		
		case "About_Fleetwood_16":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-16");
			pchar.questTemp.HWIC.Self = "HuntKnippel";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("HuntKnippelOver", 0, 0, 10, false);
			pchar.quest.Hunt_Knippel.win_condition.l1 = "location";
			pchar.quest.Hunt_Knippel.win_condition.l1.location = "Curacao";
			pchar.quest.Hunt_Knippel.function = "CreateKnippelShip";
			LocatorReloadEnterDisable("SentJons_town", "houseH1", true);//закрыть хижину Чарли
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		case "About_Fleetwood_17":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-15");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "Abigile":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Gerçekten mi? Bundan bu kadar emin olmanın sebebi ne?";
			link.l1 = "Çünkü Charlie şimdi denizin dibinde balıklara yem oluyor. 'Zeekalf'a çıktım ve Knippel'i cehenneme yolladım. Tabii ki önce onu sorguladım... Üzerinde bir mektup vardı, bu sayede cesur Richard'ımızın sevgilisi, Yahudi Abigail ile konuşurken Knippel gibi davranabildim.";
			link.l1.go = "Abigile_1";
		break;
		
		case "Abigile_1":
			dialog.text = "Hmm... Bu akıllıca. Yani, demek istiyorsun ki...";
			link.l1 = "Evet. Yahudi kadını Antigua'ya getirdim. Şu anda gemimde. Artık Fleetwood'la olan oyunumda elimde bir koz var! Onun için her şeyi yapar...";
			link.l1.go = "Abigile_2";
		break;
		
		case "Abigile_2":
			dialog.text = "Emin misin? Belki de her şey senin ima ettiğin kadar basit değildir...";
			link.l1 = "Evet, bundan tamamen eminim. Mektuptan anladığım kadarıyla Abigail'in babası, Richard'la evlenmesine paradan dolayı karşı çıkmış. Biliyorum, tipik Yahudi kayınpeder. Sonra Fleetwood, babasına başlık parası ödemeye karar vermiş – tam 200.000 peso! Söylesene, dünyada kaç kız bu kadar para eder?";
			link.l1.go = "Abigile_3";
		break;
		
		case "Abigile_3":
			dialog.text = "Heh! Elbette bir Yahudi kızı değil! Hayatımda hiçbir Hristiyan kızının bu kadar değerli olduğuna hiç rastlamadım, orası kesin. "+pchar.name+", sen tam bir kurnazsın. Onunla ne yapacaksın?";
			link.l1 = "Yahudi kadını buraya getireceğim ve onu senin odanda tutacağız. Ona Richard'ın denize açıldığını ve henüz dönmediğini söyleyeceğim, böylece bir hafta boyunca misafirimiz olacak. O, benim Charlie Knippel olduğumu sanıyor.";
			link.l1.go = "Abigile_4";
		break;
		
		case "Abigile_4":
			dialog.text = "İlginç. Yani kızı benim evimde tutmaya karar verdin? Hmm...";
			link.l1 = "John, o bir Yahudi. Hollanda kolonilerinden getirilmiş, vatansız bir gezgin. St. John's'ta kimse onu tanımıyor, burada hiçbir ağırlığı yok. İçin rahat olsun, ne istersek yapabiliriz, tek kelime etmeye cesaret edemez. Ne parası var, ne de bir dostu. Hem zaten, burada uzun süre kalmayacak. Onu yem olarak kullanıp Fleetwood'u ortaya çıkaracağım, ondan sonra ona artık ihtiyacımız kalmayacak.";
			link.l1.go = "Abigile_5";
		break;
		
		case "Abigile_5":
			dialog.text = "Beni korkutmaya başlıyorsun, Charles. Bu kıza kötü bir şey yapmayacaksın, değil mi? Yoksa onu da Knippel'ın başına gelenle mi karşılaştıracaksın?";
			link.l1 = "Hayır, tabii ki değilim. 'Kurnaz alçak' olabilirim, ama güzel kızların - Yahudi ya da Hristiyan - düşmanı değilim. Hatta çirkin olanların da. Eğer uslu durursa, her şey bittikten sonra onu babasına, Willemstad'a götürürüm. O yaşlı cimri muhtemelen dizlerime kapanıp, onu o hain İngilizden kurtardığım için bana teşekkür eder.";
			link.l1.go = "Abigile_6";
			// belamour legendary edition -->
			link.l2 = "Bu maskaralıkta onun da bir rolü var. Oyun bittiğinde ona ihtiyacım kalmayacak.";
			link.l2.go = "Abigile_6a";
		break;
		
		case "Abigile_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 60);
			dialog.text = "Anladım, yani şimdilik ona göz kulak olmam gerekiyor.";
			link.l1 = "Israr etmeyeceğim, dostum. Eğer buna kesinlikle karşıysan, o zaman kız benim gemimde kalabilir. Ama o zaman, güvenlik için onu zincire vurmak ve tayfamdan korumak için ambarın içinde farelerle birlikte tutmak zorunda kalırım. Kadınların gemide olması onlar için alışılmadık bir durum, biliyorsun. Böyle güzel bir kızı bu şekilde muamele etmek yazık olurdu.";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_6":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 60);
			// <-- legendary edition
			dialog.text = "Anladım, yani şimdilik ona göz kulak olmam gerekiyor.";
			link.l1 = "Israr etmeyeceğim, dostum. Eğer buna tamamen karşıysan, o zaman kız benim gemimde kalabilir. Ama o zaman güvenlik için zincire vurmam ve tayfamdan korumak için farelerle birlikte ambarın içine kapatmam gerekecek. Gemide bir kadının olması onlar için alışılmadık bir durum, biliyorsun. Böyle güzel bir kıza böyle davranmak yazık olurdu.";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_7":
			dialog.text = "Anladım. Pekâlâ, onu buraya getir. Fleetwood'a karşı verdiğin mücadelede sana yardımcı olmak benim görevim. Onu buraya getir, ben de onun için 'misafir odasını' hazırlayayım.";
			link.l1 = "Teşekkür ederim, John. Sana güvenebileceğimi biliyordum.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Self = "AbigileInCabin";
			DoQuestCheckDelay("SetAbigileToCabin", 1.0); // fix 180812
			AddQuestRecord("Holl_Gambit", "3-24");
			//поставим табурет
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "SentJons_HouseF3";
			sld.startLocator = "goto2";
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abigile_7_1":
			DelLandQuestMark(npchar);
			dialog.text = "Oh! Memnuniyetle. Böyle önemli ve... zarif bir hanımefendiyi ağırlamaktan mutluluk duyarım. Hanımefendi, lütfen ikinci kata buyurun. Sizi akşam yemeğiniz bekliyor ve yatağınız hazır. Böyle uzun bir yolculuktan sonra güzel bir uyku çekmek isteyeceğinizden eminim.";
			link.l1 = "Evet. Abigail, Willemstad'dan gelen bu uzun yolculuktan sonra yorgun olmalı.";
			link.l1.go = "Abigile_8";
		break;
		
		case "Abigile_8":
			DialogExit();
			sld = characterFromId("Abigile");
			sld.dialog.currentnode = "Abigile_kidnapping_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_9":
			dialog.text = "Şimdiden bir planın var mı?";
			link.l1 = "Evet, öyle. Abigail için fidye talebimizi içeren bir mektup yazmamız gerekiyor Richard’a. Onunla ıssız bir adada – mesela Turks’te – buluşmak için bir yer ayarla. Eğer kabul etmezse, nasıl desem, İbrani sevgilisini parça parça ona yollarız.";
			link.l1.go = "Abigile_10";
		break;
		
		case "Abigile_10":
			dialog.text = "İssiz bir ada için bu kadar karmaşaya ne gerek var?";
			link.l1 = "Tarafsız bölge. Daha güvenli. Zaten Abigail'i getirmeyeceğim. Fleetwood'a ihtiyacım var. Antigua'da kesinlikle pusu kurar, ama Turks'te böyle bir avantajı olmayacak.";
			link.l1.go = "Abigile_11";
		break;
		
		case "Abigile_11":
			dialog.text = "Makul. Mektubu kim götürecek? Bu çok tehlikeli.";
			link.l1 = "Bir yabancı. Meyhaneden güvenilir görünen bir ayyaş seç. Biraz rom parası için ne istersen yapmaya razı olur. Richard öfkesine kapılıp onu öldürürse, bir başkasını göndeririz. Ve mektuba Abi'nin parmaklarından birini ekleriz. Bu onu çok daha uysal yapacaktır.";
			link.l1.go = "Abigile_12";
		break;
		
		case "Abigile_12":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Endişelenme, John. Eminim o noktaya gelmeyecek. Sen sadece bir ulak bul, ben de hemen mektubu yazayım. Kağıdın ve mürekkebin var mı?";
			link.l1.go = "Abigile_13";
		break;
		
		case "Abigile_13":
			dialog.text = "Evet, biliyorum. Üstelik uygun bir ayyaş da tanıyorum. Jack Harrison'ı öneririm. Her akşam meyhanede, rom içerek vakit geçirir. Onu kolayca bulabilirsin.";
			link.l1 = "Güzel, bana kalem ve mürekkep getir, Richard için fidye mektubunu yazacağım.";
			link.l1.go = "Abigile_14";
		break;
		
		case "Abigile_14":
			DialogExit();
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.07, 2.57, -2.46, true, -0.08, -0.38, 1.35);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "MC_writeLetter", -1);
		break;
		
		case "Abigile_15":
			dialog.text = "Mektubu ona ne zaman vereceksin? Teslimatı bizzat izlemeyi mi düşünüyorsun?";
			link.l1 = "Tabii. Richard aptal değil, ama risk alacağını sanmıyorum. En azından, umarım öyledir. Kıza zarar vermek istemem, ama gerekirse yaparım. Neyse, bahsettiğin ayyaşı bulma vakti geldi. Jack... soyadı neydi?";
			link.l1.go = "Abigile_20";
		break;
		
		case "Abigile_20":
			dialog.text = "Adı Jack Harrison. Genellikle akşamları meyhaneye uğrar. Dikkatli ol!";
			link.l1 = "Her şey yoluna girecek. Beni bekle.";
			link.l1.go = "Abigile_22";
		break;
		
		case "Abigile_22":
			DialogExit();
			LAi_SetOwnerType(npchar);
			pchar.questTemp.HWIC.Self = "LetterToDrunkardGo";
			AddDialogExitQuestFunction("CreateDrunckardInTavern");
			AddQuestRecord("Holl_Gambit", "3-25");
		break;
		
		case "Abigile_23":
			DelLandQuestMark(npchar);
			dialog.text = "Ben öyle demezdim. Fleetwood kurnaz ve tehlikelidir. Üstelik usta bir kılıç ustası ve deneyimli bir denizci. Kolay lokma olmayacaktır.";
			link.l1 = "Karayiplere geldiğimde kolay yolu seçmeyi bıraktım. Neyse John, artık gitme vakti. Bu arada, cesur Fleetwood'un iyi bir gemisi olduğunu söylemiştin, değil mi?";
			link.l1.go = "Abigile_24";
		break;
		
		case "Abigile_24":
			dialog.text = "Şimdiye kadar gördüğüm en iyi brig ona ait. Ve ben az gemi görmedim.";
			link.l1 = "Bu iyi. Güzel gemileri severim. Demir alma vakti!";
			link.l1.go = "Abigile_26";
		break;
		
		case "Abigile_26":
			DialogExit();
			pchar.questTemp.HWIC.Self = "FleetwoodToIsland";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1 = "location";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1.location = "Shore56";
			pchar.quest.Fleetwood_meetingShore.function = "InTerksShore";
			AddQuestRecord("Holl_Gambit", "3-28");
			AddMapQuestMarkShore("Shore57", false);
		break;
		
		case "Abigile_27":
			int iVal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
				}
			}//установили признак наличия Валькирии в эскадре.
			if (iVal != 0)
			{
				dialog.text = "Nutkum tutuldu! Mükemmel bir birleşim, parlak bir fikir ve usta işi bir uygulama! Tebrik ederim, "+pchar.name+"! Ve onun brigini de ganimet olarak ele geçirmeyi başardın!";
				link.l1 = "Teşekkür ederim! Peki ya Hercule nerede? Onu görmek isterim. En son buluştuğumuzda, seni bulmamın ona ulaşmamı sağlayacağını söylemişti.";
				link.l1.go = "Abigile_28";
			}
			else
			{
				dialog.text = "Mükemmel bir kombinasyon, harika bir fikir ve ustaca bir uygulama! Tebrik ederim, "+pchar.name+"!";
				link.l1 = "Teşekkür ederim! Peki ya Hercule nerede? Onu görmek isterim. En son karşılaştığımızda, onu senin yardımla bulabileceğimi söylemişti.";
				link.l1.go = "Abigile_28";
			}
		break;
		
		case "Abigile_28":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Her an gelmesini bekliyorum. Gizli tünelden buraya gelmeli. Sen de Abigail'e kendini açıklamalısın. Richard'ın yokluğundan dolayı endişelenmeye başladı.";
			link.l1 = "Peki, ama onu eve göndermemiz gerekmiyor mu?";
			link.l1.go = "Abigile_29";
		break;
		
		case "Abigile_29":
			dialog.text = "Henüz değil... Önce seninle konuşmam gerek. Ama önce, Hercule'ün gelmesini bekle. Git, Abigail'i teselli et. Ona bir hikaye anlat, bir şeyler uydur. Sonra bodruma gel. Tamam mı?";
			link.l1 = "Aynen öyle, John.";
			link.l1.go = "Abigile_30";
		break;
		
		case "Abigile_30":
			DialogExit();
			npchar.greeting = "merdok_4";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SentJons_TownCave", "item", "berglar1", "", -1);
			pchar.questTemp.HWIC.Self = "AbigileLie";
			sld = characterFromId("Abigile");
			LAi_SetCitizenType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddQuestRecord("Holl_Gambit", "3-34");
		break;
		
		case "Lucas":
			DelLandQuestMark(npchar);
			dialog.text = "Eh, artık kartları masaya koymanın zamanı geldi. Zaten anlamışsındır, ben sıradan bir eczacı değilim. Gerçek adım Johan van Merden ve yakın zamana kadar Hollanda Batı Hindistan Şirketi'nin ajanı ve başkan yardımcısı Lucas Rodenburg'un sağ koluydum.";
			link.l1 = "Gerçekten mi! Bu ilginç...";
			link.l1.go = "Lucas_1";
		break;
		
		case "Lucas_1":
			dialog.text = "It's different now. Lucas wants to leave the game and return to the Netherlands, so he needs to bury everything and everyone connected to his past\nI think I am still breathing only because of my archives, which contain all the information about Lucas's crimes... like the story of the 'ghost ship', which is just an ordinary pirate vessel under the command of the reckless and unprincipled scoundrel Jacob van Berg. Rodenburg hired the man to plunder and sink English trade ships\nVan Berg is also responsible for sinking the fluyt with Abigail and her father aboard. Abigail is an important figure in this game; Rodenburg also wanted her hand and heart, just like Fleetwood did, so I was quite surprised when you brought her here...";
			link.l1 = "Rodenburg... bu, Abigail'in tuhaf babasının bahsettiği damat!";
			link.l1.go = "Lucas_2";
		break;
		
		case "Lucas_2":
			dialog.text = "Yes, that is why I want her to stay here for a while. She might be my last ace in the game against Rodenburg, though I would prefer not to use her any further; she is a good girl, I don't want her to suffer. I think that Lucas would choose my archive over her, if the choice were presented.\nSo, I propose that you become my ally in the game against Lucas... get rid of him, use any means necessary. The reward will be substantial.";
			link.l1 = "Hmm... Bence Fleetwood'la olduğundan daha zor olmayacak. ";
			link.l1.go = "Lucas_3";
		break;
		
		case "Lucas_3":
			dialog.text = "No, you're wrong. In the end, Fleetwood was a lone wolf, acting on his own. Rodenburg is vice president of the Company. He is a very influential man; only the governor of Curacao has more power. Jacob van Berg is his agent, a very dangerous man. Lucas sits on his arse in Willemstad under the protection of the Company's guardsmen; they are as good as Fleetwood's men.\nThis is not going to be easy.";
			link.l1 = "Oyunun kuralları aynı - kaplanı ininden çıkarmak... Zaten bir planım var. Lucas hakkında başka ne söyleyebilirsin?";
			link.l1.go = "Lucas_4";
		break;
		
		case "Lucas_4":
			dialog.text = "Pekala, sana neredeyse her şeyi anlattım. 'Meifeng' adında, yani Güzel Rüzgar, hızlı bir gemisi var. Kaptanı ise Longway adında bir Çinli - Rodenburg'un sadık adamı. O da karşılaşmak istemeyeceğin bir düşman. Lucas'ın tayfasında acemi yoktur. ";
			link.l1 = "En başından beri elimizde bir koz vardı - senin arşivin. Eğer canını Yahudi kadından daha çok düşünüyorsa, arşivdeki bilgilerin gizli kalması için her şeyi yapacaktır... Ama... arşiv gerçekten var mı, John? Yoksa blöf mü yapıyorsun?";
			link.l1.go = "Lucas_5";
		break;
		
		case "Lucas_5":
			dialog.text = "Arşiv gerçekten var. Ve Lucas bundan haberdar. Sen bir şey bulabildin mi?";
			link.l1 = "Biliyorum. John, eğer gerçekten şirketin ajanıysan, bir şeyler biliyor olmalısın.";
			link.l1.go = "Lucas_6";
		break;
		
		case "Lucas_6":
			dialog.text = "Ne tam olarak? Sor bana.";
			link.l1 = "Şirkete ait bir gemiyi yakalamam gerekiyor. Tercihen refakatsiz bir gemi — bir kurye ya da benzeri bir şey. Bu konuda bana bir şey söyleyebilir misin?";
			link.l1.go = "Lucas_7";
		break;
		
		case "Lucas_7":
			dialog.text = "Hm... Böyle bir bilgiye sahip değilim. Dur! Eminim ki, Şirket her ay Philipsburg ile Willemstad arasındaki deniz yolunda bir posta gemisi bulunduruyor. İş evraklarını taşıyor. Geminin adı 'Hoop' ve bir brigantin.\nBugün ya da yarın Philipsburg'dan ayrılacak.";
			link.l1 = "İşte bu! Şimdi tek yapmam gereken Saint Christopher kıyılarına gitmek. Curaçao'ya deniz yolu tam oradan geçiyor.";
			link.l1.go = "Lucas_8";
		break;
		
		case "Lucas_8":
			dialog.text = "İyi şanslar, "+pchar.name+". Planının ayrıntılarını sormayacağım. Dönüşünü bekliyor olacağım!";
			link.l1 = "Her şey yoluna girecek, John. Yahudi kadına iyi bak ve ona iyi davran!";
			link.l1.go = "Lucas_9";
		break;
		
		case "Lucas_9":
			DialogExit();
			RemoveItems(PChar, "MC_Letter", 1);
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter2");
			AddQuestRecordInfo("LetterToLucas", "1");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);
			pchar.questTemp.HWIC.Self = "LetterToLucas";
			sld = characterFromId("Tonzag");
			sld.dialog.currentnode = "Tonzag_hired";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddQuestRecord("Holl_Gambit", "3-36");
			//установим таймер на генерацию энкаунтера
			pchar.quest.HWIC_Cureer.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Cureer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Cureer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Cureer.function = "CreateHWICCureerOnMap";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("HWICCureerOnMapOver", 0, 0, 16, false);//таймер
		break;
		
		case "Lucas_10":
			dialog.text = "İnanılmaz! Kulaklarıma inanamıyorum! Bu nasıl oldu?";
			link.l1 = "Posta gemisini ele geçirdim ve Fleetwood adına Lucas'a bir mektup gönderdim. Mektupta, St. John's'tan bir eczacıya ait olan belli bir arşivin artık benim elimde olduğunu ve yakında onun tüm suçlarının kanıtlarının buradan Amsterdam'a ve Londra'ya kadar duyulacağını yazdım. Beni avlamaya başlayacağını sanmıştım, ama tam tersi oldu.";
			link.l1.go = "Lucas_11";
		break;
		
		case "Lucas_11":
			dialog.text = "";
			link.l1 = "Lucas, Matthias Beck’i ihanetten ve İngilizlerle iş birliği yapmaktan suçladı, onu hapse attı ve valinin sarayına yerleşti. Muhtemelen brigantin kaptanını da ortadan kaldırdı. Sonra da Meifeng’den sadık Çinlisini, Şirket’in direktörü Peter Stuyvesant gemideyken, gemiyi batırması için görevlendirdi!";
			link.l1.go = "Lucas_12";
		break;
		
		case "Lucas_12":
			dialog.text = "Rodenburg acımasız bir adam. Ama onun bu kadar ileri gidebileceğini ben bile düşünmemiştim...";
			link.l1 = "Meifeng'i ele geçirdim ve Longway'i sorguladım. Bana her şeyi anlattı. Stuyvesant'ı bulup Rodenburg'un niyetleri konusunda onu uyardım, birlikte Willemstad'a yelken açtık. Stuyvesant, Beck'i serbest bıraktı ve Lucas'ı tutukladı. Şimdi hapiste.";
			link.l1.go = "Lucas_13";
		break;
		
		case "Lucas_13":
			dialog.text = "Heh! Gerçekten yeteneklisin dostum... Şirket Donanması'nda ya da Birleşik Eyaletler'de siyasetçi olarak kariyer yapmalısın - vali olman işten bile değil! Peki Longway'e ne yaptın?";
			link.l1 = "Onu serbest bıraktım. Onurluca teslim oldu, bu yüzden ona zarar vermedim.";
			link.l1.go = "Lucas_14";
		break;
		
		case "Lucas_14":
			dialog.text = "Bu iyi. Longway iyi bir adam, eski patronunun aksine. Peki, "+pchar.name+", harika bir iş çıkardın! Ödülünü hazırlayacağım, ama biraz zamana ihtiyacım olacak... Bu arada...";
			link.l1 = "John, doğrusu söylemek gerekirse, işin içinde bir pürüz var. Önce Longway, sonra da Rodenburg bana Jacob van Berg’in peşimde olduğunu söyledi. Bu ne kadar kötü bir durum?";
			link.l1.go = "Lucas_15";
		break;
		
		case "Lucas_15":
			dialog.text = "Jacob van Berg mi? Charlie, bu iş ciddi. O acımasız bir korsan, usta bir denizci ve dövüşçüdür; Fleetwood onun yanında süt dökmüş kedi gibi kalır. Gerçek bir avcı. Rodenburg'un emriyle ticaret gemilerini batıran oydu.\nSeni bulacaktır, bu yüzden hazırlıklı olmalısın. Ben de kendi önlemlerimi almalıyım.";
			link.l1 = "Bu van Berg'i nasıl bulabilirim?";
			link.l1.go = "Lucas_16";
		break;
		
		case "Lucas_16":
			dialog.text = " Bilmiyorum. Lucas ve Longway onun nerede olduğunu bilen tek kişilerdi. O yüzden dikkatli ol ve tetikte kal\nBurayı kapatıyorum. Beni görmek istiyorsan gizli tünelden geç. Ve Yahudi kızı da götür, burada kalması onun için çok tehlikeli.";
			link.l1 = "Endişelenme, John. Bırak gelsin, ben onunla ilgilenirim. Abigail nerede?";
			link.l1.go = "Lucas_17";
		break;
		
		case "Lucas_17":
			dialog.text = "Kiliseye gitti. Onun için üzgünüm. Son zamanlarda çok üzgündü.";
			link.l1 = "Pekâlâ... Bu hoş bir sürpriz oldu. Belki de halkının uzun zamandır beklediği Mesih'in İsa olduğunu anlamıştır. Şimdi onu babasına geri götürmenin zamanı geldi.";
			link.l1.go = "Lucas_18";
		break;
		
		case "Lucas_18":
			dialog.text = "Seni görmek istedi. Eminim seni evine geri götürmeni isteyecek.";
			link.l1 = "Abi, ha?";
			link.l1.go = "Lucas_19";
		break;
		
		case "Lucas_19":
			dialog.text = "Doğrusunu söylemek gerekirse , artık arkadaş olduk. Evimde yaşamasından hiç pişman değilim, Tanrıya şükür ki buraya neden getirildiğini asla öğrenmeyecek.";
			link.l1 = "Pekala John, Abigail ile buluşmak için kiliseye gideceğim. Sonra Willemstad'a geçeceğim.";
			link.l1.go = "Lucas_20";
		break;
		
		case "Lucas_20":
			DialogExit();
			sld = characterFromId("Abigile");
			AddLandQuestMark(sld, "questmarkmain");
			ChangeCharacterAddressGroup(sld, "SentJons_church", "goto", "goto1");//Аби - в церковь
			AddQuestRecord("Holl_Gambit", "3-56");
			pchar.questTemp.HWIC.Self = "AbiReturnHome";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
		break;
		
		case "Final":
			dialog.text = "Sen... adamın cevizlerini mi kırdın? Ha - mecazmış. Neyse, cevizli ya da cevizsiz, başardın! Tebrikler!";
			link.l1 = "Sana yalan söylemem, heh. Artık rahatça nefes alabilirsin, John.";
			link.l1.go = "Final_1";
		break;
		
		case "Final_1":
			dialog.text = "Sonunda! Sanırım bu siyasi oyunlardan ve entrikalardan tamamen vazgeçmek en iyisi. Şimdi ise, yaptığın işin ödülünü konuşmanın zamanı geldi.";
			link.l1 = "Bunu gerçekten takdir ederdim.";
			link.l1.go = "Final_2";
		break;
		
		case "Final_2":
			dialog.text = "Karayipler'den sonsuza dek ayrılıyorum. Bana yardım ettiğin ve Rodenburg'un elinden kurtardığın için sana teşekkür olarak, bu evin ve eczanemin tapusunu sana veriyorum. Artık hepsi senin. Anahtarları al.";
			link.l1 = "Harika! Gerçekten çok mutluyum. Çok rahat bir evin ve keyifli bir kilerin var...";
			link.l1.go = "Final_3";
		break;
		
		case "Final_3":
			GiveItem2Character(pchar, "Drugstore_keys");//ключ
			dialog.text = "Ve ayrıca, lütfen bu mütevazı 100.000 peso ve bu tüfeği de kabul edin. Bir zamanlar bana sadakatle hizmet etti, şimdi de size iyi hizmet edecektir.";
			link.l1 = "Böyle hediyeleri asla reddetmem!";
			link.l1.go = "Final_4";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", false);//открыть аптеку
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", false); // открыть комнату
			pchar.quest.Jino_Door.win_condition.l1 = "locator";
			pchar.quest.Jino_Door.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Jino_Door.win_condition.l1.locator_group = "reload";
			pchar.quest.Jino_Door.win_condition.l1.locator = "reload4";
			pchar.quest.Jino_Door.function = "OpenRoomDoor";//на локатор комнаты Джино
			Achievment_Set("ach_10");
		break;
		
		case "Final_4":
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "mushket2");
			dialog.text = "Üst kattaki odada genç bir doğa filozofu bulacaksın. Tanıdığım en iyi eczacı odur. Seni birkaç günde toparlayan bu karışımları da o hazırladı. Ona iyi bakarsan, bilgisi tüm masraflarını fazlasıyla karşılayacaktır.";
			link.l1 = "Benim kendi kitap kurdum mu olacak? Peki, onunla ben ilgilenirim.";
			link.l1.go = "Final_5";
		break;
		
		case "Final_5":
			dialog.text = "Artık veda etmem gerekiyor. Şimdi mahzene inip eşyalarımı toplayacağım. Yarın burada olmayacağım - Antigua'dan ayrılıyorum. Seninle tanıştığıma memnunum ve yanında olduğun, düşmanlarımın tarafında olmadığın için minnettarım.";
			link.l1 = "Ben de seninle tanıştığıma memnun oldum, John. Belki yine karşılaşırız...";
			link.l1.go = "Final_6";
		break;
		
		case "Final_6":
			dialog.text = "Bu hayatta olmaz, dostum. Toparlanacağım. Hoşça kal, "+pchar.name+"!";
			link.l1 = "Hoşça kal, John! Sana bol şans!";
			link.l1.go = "Final_7";
		break;
		
		case "Final_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			npchar.lifeday = 0;
			pchar.questTemp.HWIC.Self = "final";
			AddQuestRecord("Holl_Gambit", "3-64");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "self_win";
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = "Ah, iyi beyefendi, böyle saçma sözlere kulak asmayın. Orada kimse yok. Orası benim laboratuvarım, karışımlar hazırlanıyor, bilirsiniz...";
			link.l1 = "Şaka bir yana John. Gino Gvineili ismi sana bir şey ifade ediyor mu?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Hmm...";
			link.l1 = "Aha! Gözlerinden okuyorum - haklıyım... Orada yaşıyor ve otlarını da onun için hazırlıyor!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Efendim, size bir kez daha söylüyorum - burada kimse yok.";
			link.l1 = "Bahaneleri bir kenara bırakalım, John. Senin simyacına zarar vermeyeceğim - ama Santiago'dan Peder Vincento onu bulursa, garanti veremem. Engizitör zaten 'Domini Canes'lerini Antigua'ya göndermeyi planlıyor...";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Ondan ne istiyorsun?";
			link.l1 = "Sadece konuşmak için. Bana oldukça önemli bazı bilgiler verecek. Söz veriyorum, onu Engizisyona teslim etmeyeceğim, ona hiçbir şekilde zarar vermeyeceğim.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Gino iyi bir insandır. Baba Vincenzo'nun onun hakkında söylediklerine inanma. Ve unutma - simyacım için her zaman arka çıkarım.";
			link.l1 = "Sana söz verdim. Bu yetmiyor mu?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Yukarı çık o zaman. Kapı açık. Ve umarım sözünde durursun.";
			link.l1 = "Merak etmeyin, yapacağım.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "jino1";
			AddQuestRecord("Guardoftruth", "36");
			LocatorReloadEnterDisable(pchar.location, "reload4", false);
		break;
		
		// алхимический набор
		case "alchemy":
			dialog.text = "Kaptan, hermetik sanatlarla tanışmak istemez misiniz? Bu sizin için oldukça faydalı olabilir.";
			link.l1 = "Üzgünüm, ama benim işim biraz farklı. Elimde kılıç kabzası tutmaya alışkınım – şişe ya da tüp değil.";
			link.l1.go = "alchemy_exit";
			link.l2 = "‘Senin felsefenden daha fazlası var göklerde ve yerde.’ Tabii ki, çok isterim. Ne gerekiyor?";
			link.l2.go = "alchemy_1";
			npchar.quest.alchemy = true;
		break;
		
		case "alchemy_exit":
			dialog.text = "Nasıl istersen. Sadece teklif etmiştim...";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "alchemy_1":
			dialog.text = "Kendi ellerinle otları karıştırmayı öğrenmelisin. Ama bir simyacı seti olmadan başarılı olamazsın. Şu çantaya bir bak. İçinde yeni başlayan bir simyacının ihtiyaç duyacağı her şey var – deney tüpleri, şişeler, imbik, spatulalar, cam borular, bir ocak ve buna benzer pek çok şey...";
			link.l1 = "Çok ilginç! Peki, bununla ne yapabilirim?";
			link.l1.go = "alchemy_2";
		break;
		
		case "alchemy_2":
			dialog.text = "Kurşunu altına çeviremeyeceksin belki, ama çeşitli tariflere göre malzemeleri karıştırıp iksirler ve başka faydalı şeyler elde edebileceksin.";
			link.l1 = " Tarifler mi? ";
			link.l1.go = "alchemy_3";
		break;
		
		case "alchemy_3":
			dialog.text = "True. You must know a recipe in order to make a potion or an item. Recipes can be bought from merchants or found anywhere. Once you have studied a recipe, you should collect every ingredient needed and do exactly what is written there\n Use your alchemy tools, find or buy a mortar and pestle, look for a crucible; alas, I don't possess an extra one to give you. Herbs, spirits, potions, minerals, garbage – everything will do, provided you have the right recipe and tools.";
			link.l1 = "Çok ilginç.   Peki, bu set için ne kadar istiyorsun?";
			link.l1.go = "alchemy_4";
		break;
		
		case "alchemy_4":
			dialog.text = "Yirmi bin peso. Bu çok iyi bir ekipman, kendini kısa sürede amorti eder.";
			link.l1 = "Benimle dalga mı geçiyorsun? Bir çanta cam eşyayı bir yük gemisi fiyatına mı satıyorsun? Hayır, almayacağım.";
			link.l1.go = "alchemy_exit";
			if (sti(pchar.money) >= 20000)
			{
				link.l2 = "Katılıyorum. Kendi ellerimle bir şeyler yapmayı denemek ilginç olacak diye düşünüyorum.";
				link.l2.go = "alchemy_5";
			}
		break;
		
		case "alchemy_5":
			AddMoneyToCharacter(pchar, -20000);
			Log_Info("You've got the alchemist's kit.");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "Bu alışverişten pişman olmayacaksınız, bundan tamamen eminim. İhtiyacınız oldukça iksirleri kendiniz yapmak, her seferinde aktarlardan tek tek almak yerine çok daha kârlı. Üstelik, her zaman ihtiyacınız olan her şeyi bulmak da mümkün olmayacak. ";
			link.l1 = "Hadi öğrenelim. Sanırım yapabilirim!";
			link.l1.go = "alchemy_6";
		break;
		
		case "alchemy_6":
			DialogExit();
			PlaySound("interface\notebook.wav");
			Log_Info("In order to make your own herbs and amulets you must have the Alchemy skill!");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Sen bir "+GetSexPhrase("Hırsız, beyefendi! Muhafızlar, yakalayın onu","Hırsız, kız! Muhafızlar, yakalayın onu")+"!!!","Şuna bak! Ben düşüncelere dalmışken, sen benim sandığımı karıştırmaya kalktın! Hırsız! Yakalayın şu hırsızı!!!","Gardiyanlar! Soygun! Hırsızı yakalayın!!!");
			link.l1 = "Lanet olsun!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
