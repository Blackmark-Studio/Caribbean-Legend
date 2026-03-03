void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ref chr, sld, rShip, rItm, rItem;
    float  fTemp;
    bool bOk;
	int i, iTemp;
	string sAttr, sGun, sBullet, attrL;
	aref rType;
    
	// генератор ИДХ по кейсу -->
	sAttr = Dialog.CurrentNode;
  	if (findsubstr(sAttr, "CabinCompanionTalk_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.CabinCompanionNum = strcut(sAttr, i+1, strlen(sAttr)-1); // индекс в конце
 	    Dialog.CurrentNode = "Cabin_Companion_Talk";
 	}
	
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	if (findsubstr(sAttr, "tonzag_jail_" , 0) != -1) {
	 	pchar.questTemp.Tonzag.JailDialog.ID = strcut(sAttr, strlen("tonzag_jail_"), strlen(sAttr) - 1);
		DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog." + pchar.questTemp.Tonzag.JailDialog.ID);
		AddDialogExitQuestFunction("Tonzag_InJailDialog");
 	    Dialog.CurrentNode = "exit";
 	}
 	// генератор ИДХ по кейсу <--

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		
		case "First time":
	      	NextDiag.TempNode = "First time";

	        Dialog.Text = "Eğer bu satırı okuyorsan, kodda bir hata var";
			Link.l1 = "Çıkış";
			Link.l1.go = "exit";
			
			//--> Вступительный туториал на палубе корабля за Шарля
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1"))
			{
				dialog.text = "Heyecan verici, kahretsin! Gerçek bir deniz savaşı!\nKeşke buradan dövüşü izleyebilseydim... Neyse. Sanırım denizcilik hakkında yeterince şey öğrendim, nasıl geçtiğini gözümde canlandırabilirim.\nMuhtemelen beş korsan... Bir büyük gemi, birkaç orta boy, bir de ufak tefekler. Bizim pinalımız için tam uygun. Harika bir hikaye olacak — Lulu bayılacak!";
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1");
				pchar.wind.speed = 18.0;
				fWeatherSpeed = stf(18.0);
				//AddDialogExitQuestFunction("SharlieTutorial_StartShip");
				AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_3");
			}
			//<-- Вступительный туториал на палубе корабля за Шарля

			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC_FindIsland"))
    		{
    		    dialog.text = "Yani, haritada bu yeri bulduk. Bunu işaretlemeliyim, sonra aramaya çıkabiliriz.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuestFunction("SearchingForIslandOnMap");
    		}
			if (CheckAttribute(pchar, "questTemp.HWICMC") && pchar.questTemp.HWICMC == "Fleetwood")
    		{
    		    dialog.text = "Pekala, geldik. Gemimi güney koyuna saklamalıyım, sonra ormandan yürüyerek geri dönüp Fleetwood'a hoş olmayan bir sürpriz hazırlamalıyım.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1.location = pchar.location;
				pchar.quest.Fleetwood_repeatShore.function = "Fleetwood_repeatShore";
    		}
			//<-- Голландский гамбит
			
			//--> Ложный след
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabinWoman" && PChar.location == Get_My_Cabin()) 
	        {
				dialog.text = "Hm... Bu herife güvenmek tehlikeli, ama anlattıkları gerçek gibi görünüyor. Belki de bu sefer yalan söylemiyor. Yine de, karısıyla konuşmalıyım... Başçavuş! Şu esir kadını bana getir!";
    			link.l1 = "Baş üstüne, kaptan!";
	    		Link.l1.go = "exit";
				chr = characterFromId("FalseTraceWife");
				chr.dialog.currentnode = "FalseTrace_wife_6";
				pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
				AddDialogExitQuest("SetFalseTraceCharToCabin");
	    	}
			//<-- Ложный след
			
			//--> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "DigGems")
    		{
    		    dialog.text = "Burası olmalı. Etraftaki tek cansız ağaç bu. Burayı kazmalıyım.";
    			link.l1 = "(hazineyi kazıp çıkar)";
    			link.l1.go = "exit";
				AddDialogExitQuest("FindPortugalGems");
    		}
			//<-- Португалец
			// Сага
			if (CheckAttribute(pchar, "questTemp.Saga.JessSoul"))
    		{
    		    dialog.text = "Ne oluyor? Neredeyim ben?! Burası nasıl bir yer?";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuest("Saga_JessikaSoul_2");
    		}
            //--> приколы со стуком в дверь Диффиндура, LSC
			if (CheckAttribute(pchar, "questTemp.LSC.DiffIndoor"))
    		{
    		    dialog.text = "Bu, geminin iç bölmelerine açılan kapı. Kilitli... Hawk burada olmalı. Ole ne demişti? Gizli şifreyi kullanmalıyım.";
    			link.l1 = "İki kez tıkla.";
    			link.l1.go = "knock_2";
				link.l2 = "Üç kez kapıyı çal.";
    			link.l2.go = "knock_3";
				link.l3 = "Bir kere vur, bekle, üç kere vur.";
    			link.l3.go = "knock_1_3";
				link.l4 = "İki kez vur, durakla, iki kez vur.";
    			link.l4.go = "knock_2_2";
				link.l5 = "Üç kez vur, durakla, bir kez daha vur.";
    			link.l5.go = "knock_3_1";
    		}
			//<-- приколы со стуком в дверь Диффиндура, LSC
			
			//--> напялили водолазный скафандр, для перехода в режим шага
			if (pchar.model == "protocusto")
    		{
    		    dialog.text = "Vay canına! Bu şey gerçekten çok ağır!";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			//<-- водолазный скафандр
			// отказ от телепортации
			if (IsCharacterInLocator(pchar, "item", "dolly1") || IsCharacterInLocator(pchar, "item", "dolly2") || IsCharacterInLocator(pchar, "item", "dolly3"))
    		{
    		    dialog.text = "Hayır, hayır, hayır! Asla olmaz! Üç kere fazlasıyla yeterdi!";
    			link.l1 = "...";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "roof")
    		{
    		    dialog.text = "İş bitti. Levasseur öldü. Beklediğimden çok daha kolay oldu... Ama bir tuhaflık var. Thibaut, Martene ile hiç konuşmamış! Bu ya Robert'ın bana ihanet ettiği ya da bir kaza olduğu anlamına geliyor.\nAma o alçak Thibaut nereye kaçmış olabilir? Kesin Catherine'in peşindedir. Kızı onun elinden sağ salim almak istiyorsam hemen harekete geçmeliyim...";
    			link.l1 = "";
    			link.l1.go = "terrapin";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
    		{
    		    dialog.text = "Treasures, treasures... an Indian city... I don't believe in such coincidences... I bet my brother had something to do with the disappearance of Dichoso's frigate. He probably made sure that Dichoso would never open his mouth again\nOr maybe he was working with him; the Spanish must have had reasons to think that Dichoso was somewhere around here. This makes no sense. But I am confident that the Indian gold Michel was delivering to de Poincy, as well as Miguel Dichoso's gold, is the same gold. The prisoner's story matches what the officer told me about my brother's adventures\nFunny, Michel failed to deliver the gold, and so did Miguel! And where are the treasures now, then? Perhaps they are the reason why my brother is in such a rush\nErgo, finding the gold will mean killing two birds with one stone: I will look into my brother's insolent eyes again and... yes, gold is always good. But how the hell do I find it? It seems it's time to get real close to the Spanish\nDon Ramona Mendoza is off the table; I doubt I will be able to deal with him, but holy father Vincento, a baron's worst enemy... he will do. His kind are not scrupulous but love money and foul means\nDichoso, Dichoso... I've heard this surname before... or haven't I? Whatever, to hell with it. I should go to the officer and claim the Spanish prisoner. Then I may head to Santiago at any time.";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore")
    		{
    		    dialog.text = "Vanilya brigantinaya yüklendi ve yelkenleri çoktan ufkun ötesinde kayboldu bile - ama şu lanet kalyon açık denize açılmak yerine limana geri döndü. Limanda gemimle görünmemeliyim - Guadeloupe'tan ayrıldığımı düşünmeleri en iyisi... Sanırım ormana girip kasabaya yürüyerek sevgili Marchais hakkında bir şeyler öğrenmeye çalışacağım...";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "galeon")
    		{
    		    dialog.text = "Üst güvertede sadece birkaç muhafız var, hepsi de oldukça uykulu görünüyor. Sanırım arkalarından sessizce yaklaşıp başlarına bir muştayla vurursam, onları teker teker etkisiz hale getirebilirim... ";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth_room"))
    		{
    		    dialog.text = "İkinci katta sıcak bir odası olan, kilitsiz ve boş bir ev, üstelik Calhoun'un dairesinin yakınında... Bu tam bir genç kızın duasına cevap gibi... Eğer pencereden çıkıp çatının saçaklarından yürürsem, Archie'nin odasına kolayca sızabilirim. Ama bunu gece yapmalıyım ki yakalanmayayım...";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("GuardOT_FindWayToRoom");
    		}
			// Поиски Ксочитэма
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_pearl")
    		{
    		    dialog.text = "Sonunda! 'Belirti'nin gösterdiği yeri buldum: bir Kızılderili idolü. Yaklaştığımda, 'Yolun Oku' sallanmayı bırakıyor ve tek bir yöne işaret ediyor. Mantıklı görünüyor—Kızılderili büyüsü ve bir Kızılderili idolü. Şimdi 'Yolun Oku'nun gösterdiği yeri haritada işaretlemeliyim, sonra da Dominika'ya gideceğim.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFirstWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_dominica")
    		{
    		    dialog.text = "Sonunda! 'Görünüm'ün işaret ettiği yeri buldum: bir Kızılderili putu. Yaklaştığımda, 'Yolun Oku' titremeyi bırakıyor ve tek bir yöne işaret ediyor. Eh, mantıklı - Kızılderili büyüsü ve bir Kızılderili putu. Şimdi, 'Yolun Oku'nun gösterdiği yeri haritada işaretlemeliyim, sonra Main'e gideceğim.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindSecondWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "full")
    		{
    		    dialog.text = "Her iki tezahür de bulundu! Şimdi haritada ikinci yönü işaretlemeliyim. Bu iki yönün kesişimi bana Ksocheatem adasının yerini gösterecek.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFullWay");
    		}
			// рассуждения по Тайясалю
			if (CheckAttribute(pchar, "questTemp.Tieyasal_CabinTalk"))
    		{
				if (pchar.questTemp.Tieyasal_CabinTalk == "calendar")
				{
					dialog.text = "Alonso de Maldonado, Tayasal'a giden bir yolun Yucatan'ın kuzeyinden başladığını söyledi. Yani bölgedeki ormanın derinliklerine gitmem gerekecek. Ama Gino, aslında ışınlanma heykellerinin insanları Tayasal'a götürmek için yapıldığını söylemişti\nVe Miskito şamanı Yılan Göz, putların 'yutulanları' o yere göndermek için tasarlandığını anlattı. Peki, o zaman neden bu portal heykelleri bozuk? Hm. Ayrıca, İki Tezahür haritası Miskito heykeline yakın garip bir daire gösteriyor\nBu da ne anlama geliyor? Başka bir büyülü yer mi? Yoksa oradaki heykelin başka bir işlevi mi var? Sanırım şamanı ziyaret etmeliyim. Ya da Ana Ada'nın kuzeybatısına gidip oradaki koylardan birinde yolu arayabilirim.";
					link.l1 = "";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Alonso de Maldonado, Yucatan yarımadasının kuzeyinden Tayasal'a başka bir yol olduğunu söyledi. Bu da demek oluyor ki, selvanın derinliklerine giden bir yol aramalıyım. İhtiyacım olan yol muhtemelen kuzeybatı Anakarası'ndaki koylardan birinden başlıyor.";
					link.l1 = "";
					link.l1.go = "exit";
				}
				AddDialogExitQuest("Tieyasal_AfterCabinTalk");
    		}
			// решаем - титры или фриплей 010912
			if (CheckAttribute(pchar, "questTemp.Tieyasal_final"))
    		{
				dialog.text = "Bitti. Uzun yolculuğumun sonu. Kardeşimi hapisten kurtarmanın, sonunda ona karşı son savaşa hazırlanmak anlamına geleceğini asla hayal edemezdim! Az kalsın dünyamızı felakete sürüklüyordum. Tanrıya şükür, artık her şey bitti\nArtık Karayipler'de beni tutan hiçbir şey kalmadı. Eve, Fransa'ya dönme vakti. Ama... gerçekten bunu istiyor muyum?";
				link.l1 = "Evet, Avrupa'ya dönüyorum.";
				link.l1.go = "final_1";
				link.l2 = "Hayır, ben burada, Karayipler'de kalıyorum.";
				link.l2.go = "final_2";
    		}
			// фэйловый финал 040912
			if (CheckAttribute(pchar, "questTemp.Europe"))
    		{
				PlaySound("Voice\English\military02.wav");
				dialog.text = "Albayı duydunuz mu? İsyancılar orada saklanıyor! Her yeri arayın, evi altüst edin ve bulduğunuz herkesi yakalayın! Hadi, başlayın!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuest("Europe_SharlieFinal_2");
    		}
			// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
			/*if (CheckAttribute(pchar, "questTemp.FMQG.Info") && pchar.location == "Bridgetown_Plantation")
    		{
    		    dialog.text = "Burası pusu kurmak için en iyi yer. Pinette'in gelmesini burada beklemeliyim.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuest("FMQG_KidnappingInfo");
    		}*/
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN.Choose") && pchar.location == "shore40")
    		{
				dialog.text = "Hm. Bu hikaye pek doğru gelmiyor. Sanırım St. Jones'tan gelen o lugger aslında hiç var olmamalıydı. Teğmen beni askeri işine sürüklüyor. Benim buna ne ihtiyacım var ki? Hollandalılarla savaşta değilim... Ne yapmalıyım? Her şey berbat olmadan buradan çekip gidip onları kaderlerine mi bırakmalıyım, yoksa kalmalı mıyım?";
				link.l1 = "Git.";
				link.l1.go = "FMQN_1";
				link.l2 = "Kal.";
				link.l2.go = "FMQN_2";
    		}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Chest") && pchar.location == "shore37")
    		{
    		    dialog.text = "Sandık hazır. Gerekli malzemelerin hepsini kendim bulmayı deneyebilirim, ama bunun yerine gidip Fadey'i görmek istiyorum. O, her şeyi bulabilecek biri gibi görünüyor.";
    			link.l1 = "*MÜHİMMAT TOPLAMAYI TAMAMLAMAK İÇİN DÜŞÜNEREK KONUŞ SEÇENEĞİNİ KULLAN*";
    			link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_PlantChestReadyExit");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Boats") && pchar.location == "Maracaibo_river")
    		{
    		    dialog.text = "Yani, altı sandal yapmamız gerekiyor. Bunun için bir marangoz, 20 tahta ve 10 paket deri lazım";
    			link.l1 = "*UZUN TEKNELER YAPMAYA BAŞLAMAK İÇİN DÜŞÜNEREK KONUŞ SEÇENEĞİNİ KULLAN*";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Boats");
				AddQuestRecord("Roger_5", "11");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder") && pchar.location == "shore10")
    		{
    		    dialog.text = "Yani, bu eski tahta yığınını havaya uçurmayı düşünüyorum. Bunun için sadece emin olmak adına 300 birim baruta ihtiyacım var.";
    			link.l1 = "*Düşünerek Konuş seçeneğini kullanarak barut yerleştirmesi emri ver*";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder");
				pchar.questTemp.Mtraxx.Retribution = "powder";
				chrDisableReloadToLocation = false;
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed") && pchar.location == "Judgement_dungeon_01")
    		{
    		    dialog.text = RandSwear()+" Çıkış kapatılmış! Görünüşe göre kapıyı ağır bir şeyle engellemişler! "+RandSwear()+"\nSus... Ne oluyor lan?";
    			link.l1 = "";
    			link.l1.go = "mtraxx_dungeon";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead") && pchar.location == "Judgement_church")
    		{
    		    dialog.text = "İşte bu... Yolun sonu\n Don Enrico'nun ciddi olduğunu şimdi anladım: bu zindanlardan çıkış yok. Su seviyesinde ikinci bir kapı bulduğumda bir an umutlandım, ama şimdi... Zamanın izini kaybettim - bu karanlık tünellerde ne kadar süredir dolanıyorum? Yarım gün mü, bütün gün mü? Burası tabut kadar sessiz ve ürkütücü\nBir zamanlar burada, tam burada bir kilise varmış. Dua etmek için ne mükemmel bir yer. Çok günah işledim, fazlasıyla... Burada dua edip uyuyacağım, yaralarım ve yorgunluğum beni öldürüyor. Şansım varsa, bir daha hiç uyanmam...";
    			link.l1 = "";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead");
				AddDialogExitQuestFunction("Mtraxx_RetributionBead");
    		}
			// belamour legendary edition -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice") && pchar.questTemp.Mtraxx.Retribution.Choice == "to_choice")
			{
				dialog.text = "";
    			link.l1 = "Ben, Charles de Maure, Fransız kaptan ve soylu olarak, kendime ve vicdanıma yemin ederim ki korsan geçmişimle sonsuza dek vedalaşıyorum!";
    			link.l1.go = "Good_Choice";
				link.l2 = "Evet! Evet! Ah ha ha!! Başardım, hayatta kaldım! Al sana, Zorro! Cehenneme git, Marcus! Artık kendi başımayım! Charlie Prince ölmüş olabilir, ama Charles de Maure'u kimse öldüremez!";
    			link.l2.go = "Bad_Choice";
			}
			// <-- legendary edition
			
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog")) {
				dialog.text = "Ne yapmalıyız?";
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime")) {
					DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime");
					dialog.text = "... tabii ki, Levasseur aptal değil. Yoksa, neden tam da şu anda bizi tutuklamaları gereksin?\nVe tek kelime etmediler!\n"+dialog.text;
				}
				
				DeleteAttribute(link, "l1");
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Helena")) {
					link.l1 = "Helen, neden bu kadar sessizsin?";
					link.l1.go = "tonzag_jail_helena";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Mary")) {
					link.l2 = "Mary, neden bu kadar mutlusun?!";
					link.l2.go = "tonzag_jail_mary";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tichingitu")) {
					link.l3 = "Tichingitu? Duruma uygun bir şey söyle.";
					link.l3.go = "tonzag_jail_tichingitu";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tonzag")) {
					link.l4 = "Hercule, beni duyuyor musun? Ne yapacağız?";
					link.l4.go = "tonzag_jail_tonzag";
				}
				
				link.l5 = "Yapacak bir şey yok. Sanırım bir süre Michel’in ayakkabılarını giyeceğim.";
				link.l5.go = "tonzag_exit";
			}
			
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailPanic")) {
				dialog.text = "";
				link.l1 = "Aman Tanrım, Hercule'ü öldürdüler!";
				link.l1.go = "exit";
				link.l2 = "Kahrolası herifler!";
				link.l2.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.TonzagQuest.JailPanic");
				AddDialogExitQuestFunction("Tonzag_GFAfterShot");
			}
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.RefusedGame")) {
				dialog.text = "Ne akşamdı ama! Neden onu dinledim ki? Ağabeyim haklıydı – buradaki kızlar bambaşka. Belki de romun içine bir şey kattılar?";
				link.l1 = "Uyku vakti, sonra da – Cartagena'ya!";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.RefusedGame");

				AddDialogExitQuestFunction("HelenDrinking_LightsOut1");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk")) {
				dialog.text = "Tek bir şey bile çalınmamış, ama her şey darmadağın olmuş. Değerli eşyalar bile el sürülmeden duruyor. ";
				link.l1 = "Beni soymaya çalışmıyorlardı - belli bir şeyi arıyorlardı. Ama ne? Ve daha da önemlisi, kim...?";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk");

				AddDialogExitQuestFunction("PZ_OsmatrivaemSunduk_4");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_GotovimShlupki")) {
				dialog.text = "Gece olana kadar bekleyip saldıracağız!";
				link.l1 = "Bu arada sandal hazırlıklarına başlayacağız.";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_GotovimShlupki");

				AddDialogExitQuest("PZ_ShturmZvezdy");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_TiboUkralDevu")) {
				dialog.text = "Aman Tanrım... Hayır, hayır, hayır... ";
				link.l1 = "";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_TiboUkralDevu");
				
				LAi_SetActorType(pchar);
				LAi_ActorAnimation(pchar, "kneeling", "1", 7.5);
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_DevaMertva")) {
				dialog.text = "Aman Tanrım, aman Tanrım, aman Tanrım... Neden? Aman Tanrım, neden... ama elimden gelen her şeyi yaptım...";
				link.l1 = "Tüm suç benim, sadece benim. Zamanında yetişemedim. Çok üzgünüm... Lütfen, lütfen beni affet.";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_DevaMertva");

				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva8");
			}
		break;
		
		// boal -->
		case "TalkSelf_Main":
	   		NextDiag.TempNode = "First time";
//navy --> after duel in tavern
			if (CheckAttribute(pchar, "questTemp.LocationClone"))
			{
				Dialog.Text = RandPhraseSimple("Bu gerçekten zorlu bir dövüştü... Şimdi kaçan o korkakları ortaya çıkarabiliriz...","Ha! Bu çok kolaydı. O karadakiler de hemen dağıldı!");
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.LocationClone");
				break;
			}
//navy <--
	        Dialog.Text = RandPhraseSimple("Hmm... Şimdi ne yapmalıyım?","Şimdi ne yapmalıyız?");
	        if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
	        {
				//navy --> 13.02.08
				if (!bDisableMapEnter && GetCompanionQuantity(PChar) > 1)
				{
    				link.l3 = "Bir yoldaş çağır.";
    				link.l3.go = "Cabin_CompanionSelect";
				}
				//navy <--
			}
			else 
			{   //исп.линейка, квест №6, возможность переночевать в оплаченной комнате
				if (CheckAttribute(pchar, "questTemp.State.Open") && pchar.location == "Tortuga_tavern_upstairs")
				{
					if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
	    			{
	    				link.l1 = "Sabaha kadar dinlen.";
	    				link.l1.go = "TalkSelf_room_day";
	    			}
	    			else
	    			{
	    				link.l1 = "Geceye kadar dinlen.";
	    				link.l1.go = "TalkSelf_room_night";
	    				link.l2 = "Ertesi sabaha kadar dinlen.";
						link.l2.go = "TalkSelf_room_day";
	    			}
				}
			}
	        if (!bDisableMapEnter)//боя в море нет
	        {
	            if (GetCargoGoods(pchar, GOOD_SLAVES) > 0)
	            {
	                Link.l5 = "Köleleri mürettebata al.";
	        		Link.l5.go = "TalkSelf_SlavesToCrew";
	    		}
	        }
	        // захват города
	        if (GetCharIDXForTownAttack(pchar.location) != -1 && !CheckAttribute(Pchar, "GenQuestFort.StartAttack") && !CheckAttribute(Pchar, "questTemp.Sharlie.DefendSP"))
	        {
	            Link.l6 = "En yakın kasabayı ele geçirmeye başla.";
	    		Link.l6.go = "TalkSelf_TownAttack";
	        }
	        
			bool bSeaBattle = (bDisableMapEnter) && (bSeaActive) && (!CheckAttribute(pchar, "GenQuest.MapClosedNoBattle"));
	        if(!bSeaBattle && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar, "GenQuest.CannotWait") && !CheckAttribute(loadedLocation, "CannotWait")) 
	        {
	        	Link.l7 = "Biraz dinlenmeliyim...";
	    		Link.l7.go = "TalkSelf_StartWait";
	    	}
			
			if(CheckAttribute(pchar, "equip.gun"))
			{
				if(CheckAttribute(pchar, "chr_ai.gun.bulletNum") && sti(pchar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l8 = "Ateşli silahlar için mühimmatı değiştirmek istiyorum.";
					Link.l8.go = "SetGunBullets";
				}	
			}
			
			if(CheckAttribute(pchar, "equip.musket"))
			{
				if(CheckAttribute(pchar, "chr_ai.musket.bulletNum") && sti(pchar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l9 = "Tüfek için mühimmatı değiştirmek istiyorum.";
					Link.l9.go = "SetMusketBullets";
				}
					Link.l10 = "Çatışma için bir ana silah seçmek istiyorum.";
					Link.l10.go = "SetPriorityMode";
			}
			
			Link.l19 = "Düzenli kullanım için bir iksir seçmek istiyorum.";
			Link.l19.go = "ChoosePotion";
			
			//--> Голландский гамбит
			if(CheckAttribute(pchar, "questTemp.HWIC_Coordinates") && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l11 = "Haritadaki koordinatları kullanarak adayı bulmaya çalış.";
	    		Link.l11.go = "Seek_AbyIsland";
	    	}
			//<-- Голландский гамбит
			
			//--> Ложный след
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabin" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l13 = "Adam Rayner'ı çağır.";
	    		Link.l13.go = "FalseTrace_Cabin";
	    	}
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "CatchAdam" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l13 = "Adam Rayner'ı tutuklayın.";
	    		Link.l13.go = "FalseTrace_Cabin";
	    	}
			//<-- Ложный след
			// Addon 2016-1 Jason Пиратская линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Ammo") && PChar.location == "Shore37") // прогон 3
	        {
	        	Link.l17 = "Sandığın içindekileri say ve Picard için mühimmat toplamayı tamamlayıp tamamlamayacağına karar ver.";
	    		Link.l17.go = "mtraxx_ammo";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Mutiny") && pchar.location == "Maracaibo_Plantation" && stf(environment.time) >= 3.00 && stf(environment.time) < 4.00) 
	        {
	        	Link.l17 = "Maracaibo plantasyonuna saldırı emrini ver.";
	    		Link.l17.go = "mtraxx_mutiny";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_boats" && pchar.location == "Maracaibo_river") 
	        {
	        	Link.l17 = "Uzun sandalların inşası için emir ver.";
	    		Link.l17.go = "mtraxx_boats";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "powder" && pchar.location == "shore10") 
	        {
	        	Link.l17 = "Barutu yıkılmış abatislere teslim etme emri.";
	    		Link.l17.go = "mtraxx_powder";
	    	}
			// Jason Долго и счастливо
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "letter") 
	        {
	        	Link.l18 = "Bir düğünü düşün.";
	    		Link.l18.go = "LH_marry";
	    	}
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "marry_offer" && LongHappy_CheckShore()) // 28-03-20
	        {
	        	Link.l18 = "Evlenme teklifi et.";
	    		Link.l18.go = "LH_marry_3";
	    	}
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "toIslaTesoro" && pchar.location == "Pirates_town") 
	        {
	        	Link.l18 = "Kutlamayı hazırlayın.";
	    		Link.l18.go = "LH_marry_4";
	    	}
			//--> завершение игры
			if(CheckAttribute(pchar, "questTemp.Tieyasal_WinEnd")) // patch-9
	        {
	        	Link.l15 = "Karayipler'deki işini bitir ve Avrupa'ya yelken aç.";
	    		Link.l15.go = "final_1";
	    	}
			//<-- завершение игры
			Link.l20 = RandPhraseSimple("Şimdi değil. Zaman yok.","Buna vakit yok, yapacak çok iş var.");
			Link.l20.go = "exit";
		break;
		
		case "tonzag_exit":
			DialogExit_Self();
			AddDialogExitQuestFunction("Tonzag_CreateKiller");
		break;
		

		
		case "SetGunBullets":
			Dialog.Text = "Kullanılacak mühimmat türünü seçin:";
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.gun.bulletNum); i++)
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
			i = sti(PChar.GenQuest.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(pchar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetGunBullets");
			DialogExit_Self();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "Mühimmat türünü seç:";
			sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.musket.bulletNum); i++)
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
			i = sti(PChar.GenQuest.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, "musket", sBullet);
			LAi_GunSetUnload(pchar, "musket");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetMusketBullets");
			DialogExit_Self();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "Dövüşün başında şunu kullanacağım:";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Tüfek";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			pchar.PriorityMode = 1;
			DialogExit_Self();
		break;
		
		case "MusketPriorityMode":
			pchar.PriorityMode = 2;
			DialogExit_Self();
		break;
		
		case "ChoosePotion":
			Dialog.Text = "Bir iksir seç:";
	    	Link.l1 = "Şifa iksiri.";
	    	Link.l1.go = "ChoosePotion1";
			Link.l2 = "İksir.";
	    	Link.l2.go = "ChoosePotion2";
			Link.l3 = "Karışım.";
	    	Link.l3.go = "ChoosePotion3";
			Link.l4 = "Zencefil kökü.";
	    	Link.l4.go = "ChoosePotion4";
			Link.l5 = "Rom.";
	    	Link.l5.go = "ChoosePotion5";
			Link.l6 = "Şarap.";
	    	Link.l6.go = "ChoosePotion6";
			if (CheckAttribute(pchar, "GenQuest.Potion_choice"))
			{
				Link.l7 = "İksirleri otomatik olarak seçmek istiyorum.";
				Link.l7.go = "ChoosePotion7";
			}
			Link.l8 = "Bekle, fikrimi değiştirdim.";
	    	Link.l8.go = "ChoosePotion8";
		break;
		
		case "ChoosePotion1":
			log_info("A healing essence will be used by default.");
			pchar.GenQuest.Potion_choice = "potion1";
			DialogExit_Self();
		break;
		
		case "ChoosePotion2":
			log_info("An elixir will be used by default.");
			pchar.GenQuest.Potion_choice = "potion2";
			DialogExit_Self();
		break;
		
		case "ChoosePotion3":
			log_info("A mixture will be used by default.");
			pchar.GenQuest.Potion_choice = "potion4";
			DialogExit_Self();
		break;
		
		case "ChoosePotion4":
			log_info("A ginger root will be used by default.");
			pchar.GenQuest.Potion_choice = "potion5";
			DialogExit_Self();
		break;
		
		case "ChoosePotion5":
			log_info("Rum will be used by default.");
			pchar.GenQuest.Potion_choice = "potionrum";
			DialogExit_Self();
		break;
		
		case "ChoosePotion6":
			log_info("Wine will be used by default.");
			pchar.GenQuest.Potion_choice = "potionwine";
			DialogExit_Self();
		break;
		
		case "ChoosePotion7":
			log_info("Potions will be selected automatically.");
			DeleteAttribute(pchar, "GenQuest.Potion_choice");
			DialogExit_Self();
		break;
		
		case "ChoosePotion8":
			DialogExit_Self();
		break;
		
		case "TalkSelf_StartWait":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			PChar.GenQuest.CallFunctionParam = "LaunchTavernWaitScreen";
			DoQuestCheckDelay("CallFunctionParam", 0.1); // Нужно с задержкой, иначе - ГГ начинает крутиться
		break;
		
		case "TalkSelf_room_night":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Night");
			TavernWaitDate("wait_night");
			DialogExit_Self();
		break;

		case "TalkSelf_room_day":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Day");
			TavernWaitDate("wait_day");
			DialogExit_Self();
		break;
		//  захват города
		case "TalkSelf_TownAttack":
            int needCrew = 500;
			if(CheckOfficersPerk(pchar, "Troopers")) needCrew = 300;
            bOk = (GetPartyCrewQuantity(Pchar, true) >= needCrew) || bBettaTestMode;
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk)
	        {
	            chr = GetCharacter(GetCharIDXForTownAttack(pchar.location));
	            if (chr.from_sea == Pchar.location.from_sea)
	            {
					Dialog.Text = "Kenti ele geçirmeye başlayabiliriz, ama gemi kalenin toplarından gelen atışlara uzun süre dayanamaz ve bir çıkarma ekibi gönderemeyiz.";
	    			Link.l1 = "...";
	    			Link.l1.go = "exit";
	            }
	            else
	            {
					if (pchar.location == "Panama_ExitTown" || pchar.location == "Tortuga_ExitTown" || pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_ExitTown") // patch-5
					{
						Dialog.Text = "Hayır, henüz o kadar delirmedim...";
	    				Link.l1 = "...";
	    				Link.l1.go = "exit";
					}
					else
					{
						if (pchar.location == "LosTeques_ExitTown")
						{
							Dialog.Text = "Bu madeni altın ve gümüş hakkında bilgi toplamadan saldırmanın bir anlamı yok. Yoksa adamlarımı boşuna ölüme göndermiş olurum.";
							Link.l1 = "...";
							Link.l1.go = "exit";
						}
						else
						{
							Dialog.Text = "Saldır "+GetCityName(chr.City)+".";
							if (CheckAttribute(pchar, "questTemp.Patria.SanJoseAttack") && pchar.location == "PortSpein_ExitTown") // Jason НСО
							{
								Link.l1 = "Saçmalamayı bırak! Dur!";
								Link.l1.go = "exit";
								break;
							}
							if (CheckAttribute(pchar, "questTemp.Patria")) // Jason НСО
							{
								if (pchar.questTemp.Patria != "fail" || pchar.questTemp.Patria != "complete")
								{
									if (pchar.location == "Marigo_ExitTown" || pchar.location == "Villemstad_ExitTown")
									{
										Link.l1 = "Saçmalamayı bırak! Dur!";
										Link.l1.go = "exit";
										break;
									}
								}
							}
							Link.l1 = "Silah başına!";
							Link.l1.go = "TalkSelf_TownAttack_Start";
		    			Link.l2 = "Dur!";
							Link.l2.go = "exit";
						}
	    		}
	        }
	        }
	        else
	        {
				if(!CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
				{
					Dialog.Text = "Heh! There aren't enough people in the crew; we need at least "+needCrew+" men.";
					Link.l1 = "...";
					Link.l1.go = "exit";
				}
				else
				{
					Dialog.Text = "Dağılmayın! Saldırıya devam edin!";
					Link.l2 = "...";
					Link.l2.go = "exit";				
				}			
			}
	    break;

		case "TalkSelf_TownAttack_Start":
	        NextDiag.CurrentNode = NextDiag.TempNode;

			Pchar.GenQuestFort.StartAttack = true;
		    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
		    DeleteQuestAttribute("Union_with_Escadra");
	        chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			if (isCityHasFort(chr.City))
			{
	        	SetLocationCapturedState(chr.from_sea, true);
	        }
	        else
	        {
	            SetLocationCapturedState(chr.Default, true); // для сухопутных
	        }
	        AddDialogExitQuest("Capture_Forts");
	        Ship_NationAgressive(chr, chr);
	        DialogExit_Self();
	    break;
	    // Зачислить рабов в команду  -->
		case "TalkSelf_SlavesToCrew":
	        if (GetCurCrewEscadr() >= GetMaxCrewAble())
	        {
	            Dialog.Text = "Kölelerin hiçbiri mürettebata katılmak istemiyor.";
	            Link.l1 = "Onlar cehenneme gitsin!";
	    		Link.l1.go = "exit";
	        }
	        else
	        {
	            if (GetCrewQuantity(pchar) >= GetMaxCrewQuantity(pchar))
	            {
	                Dialog.Text = "Gemide yeni denizciler için boş yer yok.";
	                Link.l1 = "Heh! Mürettebatın bir kısmını başka bir gemiye aktarmam gerekecek.";
	        		Link.l1.go = "exit";
	            }
	            else
	            {
	                if (GetFreeCrewQuantity(pchar) <= GetCargoGoods(pchar, GOOD_SLAVES))
	                {
	                    pchar.GenQuest.SlavesToCrew = GetFreeCrewQuantity(pchar);
	                }
	                else
	                {
	                    pchar.GenQuest.SlavesToCrew = GetCargoGoods(pchar, GOOD_SLAVES);
	                }
	                Dialog.Text = "Mürettebatınız şu şekilde tamamlanabilir "+pchar.GenQuest.SlavesToCrew+" emrinizde hizmet etmek isteyen köleler var. Kabul etmek ister misiniz?";
	                Link.l1 = "Evet";
	        		Link.l1.go = "TalkSelf_SlavesToCrew_1";
	        		Link.l2 = "Hayır";
	        		Link.l2.go = "exit";
	    		}
			}
		break;

		case "TalkSelf_SlavesToCrew_1":
			bOk = ShipBonus2Artefact(pchar, SHIP_MEMENTO) && CheckAttribute(&RealShips[sti(pchar.Ship.Type)], "DeadSailors.RecruitSlaveBonus");
			if(!bOk)
			{
				// belamour legendary edition перк получил время работы, старый метод не подходит
				if (GetOfficersPerkUsing(pchar, "IronWill"))
				{
					AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 5.0))
				}
				else
				{
					AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 3.0))
				}
			}
			ChangeCharacterComplexReputation(pchar,"authority", -0.5);
	        // падение опыта -->
	        fTemp =  stf(GetCrewQuantity(pchar) + sti(pchar.GenQuest.SlavesToCrew));
	        pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Sailors)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Cannoners)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Soldiers)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			// падение опыта <-- 
			pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) + sti(pchar.GenQuest.SlavesToCrew); 
	        RemoveCharacterGoodsSelf(pchar, GOOD_SLAVES, sti(pchar.GenQuest.SlavesToCrew));       
			                            
	        NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		// Зачислить рабов в команду  <--
		// boal <--

//navy CONTRABAND METRO -->
		case "GenTravel_Main":
			NextDiag.TempNode = "First time";
			dialog.Text = "Bu güzel gemi artık benim, ve burada kaptan benim! Yine de tüm mürettebatı öldürmek zorunda kalmam yazık oldu.";
			Link.l1 = "Karaya çıkma zamanı geldi...";
			Link.l1.go = "exit";

			chr = CharacterFromID("Abracham_Gray");
			chr.location = "none";
			SeaExchangeCharactersShips(PChar, chr, false, false);
			SetCrewQuantity(PChar, 0);

			//грузим ГГ куда нужно...
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc, pchar.GenQuest.contraTravel.destination.group, pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;
            
			CloseQuestHeader("Gen_ContrabandTravel");
			setCharacterShipLocation(PChar, pchar.GenQuest.contraTravel.destination.loc);
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);

			//трем аттрибуты
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			break;
//navy CONTRABAND METRO <--

//navy --> 13.02.08
		case "Cabin_CompanionSelect":
			Dialog.Text = "Hangi yoldaşımı çağırmalıyım?";
			for (i = 1; i < GetCompanionQuantity(PChar); i++)
			{
				chr = GetCharacter(GetCompanionIndex(PChar, i));
				if (!CheckAttribute(chr, "Tasks.Clone") && sti(chr.Payment) == true)
				{
					sAttr = "l" + i;
					rShip = GetRealShip(sti(chr.Ship.Type));
					link.(sAttr) = GetFullName(chr) + " - " + xiStr(rShip.BaseName) + " '" + chr.Ship.Name + "'.";
					link.(sAttr).go = "CabinCompanionTalk_" + i;
				}
			}
			link.l9 = "Başka bir zaman.";
			link.l9.go = "exit";
			break;

		case "Cabin_Companion_Talk":
			i = sti(PChar.GenQuest.CabinCompanionNum);
			PlaceCompanionCloneNearMChr(i, false);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			break;
//navy <--

		//--> Голландский гамбит
		case "Seek_AbyIsland":
			bOk = CheckCharacterItem(pchar, "bussol") && CheckCharacterItem(pchar, "clock2");
			bool bOk1 = CheckCharacterItem(pchar, "sextant2");
			if (bOk || bOk1)
			{
				DialogExit();
				DeleteAttribute(pchar, "questTemp.HWIC_Coordinates");
				pchar.questTemp.HWIC_FindIsland = "true";
				AddDialogExitQuestFunction("PrepareSearchingFor");
			}
			else
			{
				dialog.text = "Gerekli seyrüsefer aletlerim olmadığı için enlem ve boylamı belirleyemiyorum. Adayı başka bir zaman aramam gerekecek. ";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		//<-- Голландский гамбит
		
		//--> Ложный след
		case "FalseTrace_Cabin":
			dialog.text = "Başçavuş! Adam Rayner'ı hemen bana getir!";
			link.l1 = "Emredersiniz, kaptan!";
			link.l1.go = "exit";
			chr = characterFromId("Mugger");
			if (pchar.questTemp.FalseTrace == "CatchAdam") chr.dialog.currentnode = "FalseTrace_17";
			else chr.dialog.currentnode = "FalseTrace_7";
			pchar.questTemp.FalseTrace.CharID = "Mugger";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		
		case "FalseTrace_Woman":
			DialogExit();
			chr = characterFromId("FalseTraceWife");
			chr.dialog.currentnode = "FalseTrace_wife_6";
			pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		//<-- Ложный след
		
		//--> LSC, приколы со стуком в дверь
		case "knock_2":
			PlaySound("interface\knock_2.wav");
			dialog.text = "Kapıyı çaldım, şimdi cevabı bekleyelim...";
			link.l1 = "(bekle)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3":
			PlaySound("interface\knock.wav");
			dialog.text = "Yani, kapıyı çaldım, şimdi cevabı bekleyelim...";
			link.l1 = "(bekle)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3_1":
			PlaySound("interface\knock_3_1.wav");
			dialog.text = "Kapıyı çaldım, şimdi bir cevap bekleyelim...";
			link.l1 = "(bekle)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_1_3":
			PlaySound("interface\knock_1_3.wav");
			dialog.text = "Kapıyı çaldım, şimdi bir cevap bekleyelim...";
			link.l1 = "(bekle)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_2_2":
			PlaySound("interface\knock_2_2.wav");
			dialog.text = "Kapıyı çaldım, şimdi cevabı bekleyelim...";
			link.l1 = "(bekle)";
			link.l1.go = "knock_right";
		break;
		
		case "knock_wrong":
			dialog.text = "Kapıyı açmıyor... Sanırım yanlış gizli tıklamayı kullandım. Peki, yarın tekrar gelip deneyeceğim. Bugün, kesinlikle kapıyı açmayacak.";
			link.l1 = "(leave)";
			link.l1.go = "exit";
		break;
		
		case "knock_right":
			PlaySound("interface\key.wav");
			PlaySound("Voice\English\YouFace.wav");
			dialog.text = "Vay canına! Cevap verdi ve kapıyı açtı! Artık içeri girebilirim...";
			link.l1 = "(enter)";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.DiffIndoor");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload74", false);
		break;
		//<-- LSC, приколы со стуком в дверь
		
		// суп из черепахи
		case "terrapin":
			PlaySound("Interface\Door_Kick.wav");
			PlaySound("Voice\English\EvilPirates02.wav");
			dialog.text = "Caramba! Demek Levasseur için gecikmiş takviye buymuş... Kapıdan çıkmam imkânsız... Peki, Thibaut'nun yaptığı gibi yapacağım - pencereden! Sonuçta o serseri de bir şekilde sıvışmayı başardı!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Terrapin_GoWindow");
		break;
		
		// защита Сен-Пьера
		case "SP_defend":
			PlaySound("Voice\English\military02.wav");
			dialog.text = "So, our mission is to repel an attack by the blasted Spanish and save Saint Pierre. The fort has been captured, and a battle is being fought in the streets. There is a powerful squadron in Saint Pierre's bay, and they have a ship of the line as their flagship. Attacking it now is pointless; the fort and the city are under enemy control, so they won't let us land in port\nTherefore, I have decided to move through the jungles and strike them from behind through the city gates. Once the fort and the city are cleared of the Spanish, we shall deal with the squadron. It will become much more vulnerable without the fire support of the fort\nThis won't be easy, so I have given orders for an extra hundred thousand pesos to be distributed among the crew in addition to the normal salary. Let's move!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("DefendSP_GoJungle");
		break;
		
		// финал игры
		case "final_1": // Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) // генерал-губернатор никуда не уедет
			{
				dialog.text = "Dur bir dakika, nereye gidiyorum ben? Paris’ten izin almadan Genel Vali görevimi bırakamam! Yoksa Fransa’ya döndüğümde bana emanet edilen kolonileri izinsiz terk ettiğim için kesinlikle tutuklanırım. Paris, seni özleyeceğim ...";
				link.l1 = "";
				link.l1.go = "exit";
				EndQuestMovie();
			}
			else
			{
				dialog.text = "O halde daha fazla vakit kaybetmeyelim! Sevgili Gaskonya'mın tarlalarını öyle çok özledim ki! Yelken açın!";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("Final_ReturnToEurope");
			}
		break;
		
		case "final_2":
			dialog.text = "Bunun doğru karar olduğuna inanıyorum! Artık kendimi burada bulduğuma göre, eski güzel Avrupa’da beni ne tutar ki? Hem, istersem her zaman Fransa’ya dönebilirim zaten!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Final_StayInCarribean"); // 010912
			DeleteAttribute(pchar, "questTemp.Tieyasal_final");
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN_1":
			dialog.text = "En iyisi bu. Gemine çıkıp buradan ayrılmalıyım.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseExit");
		break;
		
		case "FMQN_2":
			dialog.text = "Yok, asla, ben kalıyorum. Ama burada ne olacağı belli olmayan bir şeyi bekleyerek de kalmam. Philipsburg limanına gidip durumu araştırmalıyım. Onların elinde kör bir alet olmayacağım.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseContinue");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_ammo":
			Mtraxx_PlantCheckShoreBox(); // анализируем содержимое сундука
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.Blade") && !CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.NoBlade")) // собрали 30 сабель
			{
				dialog.text = "Sandıkta otuz parça soğuk çelik var! Şimdi durmalı mıyım, yoksa daha fazla ateşli silah, barut ve iksir mi toplamalıyım?";
				link.l1 = "Bu kadar yeter!";
				link.l1.go = "mtraxx_ammo_1";
				link.l2 = "Hayır, bu sandığı doldurmaya devam etmeliyim.";
				link.l2.go = "exit";
				// belamour legendary edition
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Full")
				{
					link.l3 = "Fadey'nin sandığının içindekileri doldur ve fazlasını al."; 
					link.l3.go = "mtraxx_ammo_1";
				}
			}
			else
			{
				dialog.text = "Otuz parça soğuk çelik henüz toplanmadı! Daha fazlasını getirmeliyim.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_ammo_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "Sandığı kilitleyip onu plantasyona gizlice sokmak için bir plan yapmak.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantShoreBoxComplete");
		break;
		
		case "mtraxx_mutiny":
            dialog.text = "İleri, saldır! Yaşasın!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantMutiny");
		break;
		
		case "mtraxx_boats":
            if (GetSquadronGoods(pchar, GOOD_PLANKS) >= 20 && GetSquadronGoods(pchar, GOOD_LEATHER) >= 10) // наличие материалов
			{
				if (Mtraxx_MeridaCheckCarpenter()) // наличие плотника
				{
					dialog.text = "Gerekli tüm malzemeler hazır, hemen sandal yapımına başlamalıyız.";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_MeridaBuildBoats");
				}
				else
				{
					dialog.text = "Bu işi yapabilecek deneyimli bir marangozum yok. Bu göreve bir subay atamalıyım.";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Yeterli malzeme yok, en az 20 paket tahta ve 10 balya deri lazım.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_powder":
            if (GetSquadronGoods(pchar, GOOD_POWDER) >= 300) // наличие пороха
			{
				if (GetCrewQuantity(pchar) >= 20) // наличие команды
				{
					dialog.text = "Her şey patlamaya hazır!";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_RetributionBarrels");
				}
				else
				{
					dialog.text = "Barutu teslim etmek için en az 20 adama ihtiyacım var.";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Barut yetmiyor, en az 300 tane lazım.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_dungeon":
			PlaySound("ambient\jail\jail_door2.wav");
            dialog.text = "Bir kapı mıydı?";
			link.l1 = "";
			link.l1.go = "mtraxx_dungeon_1";
		break;
		
		case "mtraxx_dungeon_1":
			PlaySound("ambient\jail\jail_door1.wav");
            dialog.text = "Doğru! Ziyaretçilerimiz var... Jan?.. ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionRunToEnrico");
		break;
		// belamour legendary edition -->
		case "Good_Choice":
			pchar.questTemp.Mtraxx.Retribution.Choice = "good";
			DoQuestCheckDelay("Mtraxx_RetributionFreedom", 0.5); 
			DialogExit_Self();
		break;
		
		case "Bad_Choice":
			pchar.questTemp.Mtraxx.Retribution.Choice = "bad";
			Achievment_Set("ach_CL_97");
			bNoEatNoRats = false;
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Roger_10", "18");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.mtraxx_line_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_line_complete.function = "Mtraxx_RetributionComplete";
			DialogExit_Self();
		break;
		// <-- legendary edition
		
		// Jason Долго и счастливо
		case "LH_marry":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			string sTemp = sld.name;
			dialog.text = "Sen ve "+sTemp+" uzun zamandır birlikteyiz ve aramızdaki bağ herhangi bir kilise yemininden daha güçlü, ama ikimizin de bu anı hatırlamasını istiyorum. Bu yüzden ona nerede evlenme teklif edeceğime karar vermem gerekiyor:";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Isla Tessoro - bu ada bizim hikayemizde çok önemli. Sanırım daha iyi bir yer olamazdı - Sabu Matila Koyu gün batımında büyüleyici!";
				link.l1.go = "LH_marry_1_1";
			}
			link.l2 = "Tortuga - özgürlüğün simgesi bu devirde, ve fenerden Tortu Boğazı'na bakan manzara her ressamın fırçasına layık!";
			link.l2.go = "LH_marry_1_2";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l3 = "Jamaika - burada o kadar çok şey var ki! Portland Cove'da şafakı izlemek, dünyadaki cenneti hayal ettiğim gibi.";
				link.l3.go = "LH_marry_1_3";
			}
		break;
		
		case "LH_marry_1_1":
			pchar.questTemp.LongHappy.Shore = "Shore_ship1";
			AddQuestRecord("LongHappy", "2_1");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Ama bunu kilisenin ciddiyeti olmadan yapamayız – her şey kanunlara uygun olmalı ki, babam seçimimi kabul etmek zorunda kalsın. Bu yüzden bir rahibe ihtiyacım olacak ve bu rol için Abbot Benoit'dan daha layık birini göremiyorum. O, babamın eski bir dostu ve Yeni Dünya'daki maceralarım onun sayesinde başladı. Bana bu onuru vereceğine inanıyorum.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_1_2":
			pchar.questTemp.LongHappy.Shore = "Mayak6";
			AddQuestRecord("LongHappy", "2_2");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Ama bunu kilisenin ciddiyeti olmadan yapamayız - her şey kanunlara uygun olmalı ki babam seçimimi kabul etmek zorunda kalsın. Yani, bir rahibe ihtiyacım olacak ve bu rol için Abbot Benoit'dan daha layık birini göremiyorum. O, babamın eski bir dostudur ve Yeni Dünya'daki maceralarım da onunla başladı. Sanırım bana bu onuru vermeyi kabul edecektir.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_1_3":
			pchar.questTemp.LongHappy.Shore = "Shore36";
			AddQuestRecord("LongHappy", "2_3");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Ama bunu kilisenin kutsallığı olmadan yapamayız - her şey kanunlara uygun olmalı ki babam seçimimi kabul etmek zorunda kalsın. Yani bir rahibe ihtiyacım olacak ve bu rol için Abbot Benoit'dan daha layık birini göremiyorum. O, babamın eski bir dostudur ve Yeni Dünya'daki maceralarım onun sayesinde başladı. Bana bu onuru vereceğine inanıyorum.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_2":
			AddQuestRecord("LongHappy", "3");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Pekâlâ, bu insanlığın ciddiyeti olmadan da olabilir. Yine de bunu seninle konuşmayı tercih ederdim "+sTemp+" biraz sonra.";
			link.l1 = "";
			link.l1.go = "exit";
			pchar.questTemp.LongHappy = "choose";
		break;
		
		case "LH_marry_3":
			dialog.text = "Hazırım!";
			link.l1 = "";
			link.l1.go = "exit";
			LongHappy_MarryOffer();
		break;
		
		case "LH_marry_4":
			if (LongHappy_CheckGoods())
			{
				dialog.text = "Her şey hazır!";
				link.l1 = "";
				link.l1.go = "exit";
				LongHappy_OnIslaTesoro();
			}
			else
			{
				dialog.text = "Gerekli mallar ve para henüz toplanmadı!";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
	}
}

void DialogExit_Self()
{
    SendMessage(PChar, "ls", MSG_CHARACTER_EX_MSG, "forceBlend");
    DialogExit();
	locCameraSleep(false); //boal
}
