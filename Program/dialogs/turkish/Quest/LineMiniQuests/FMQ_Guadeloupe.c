// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Açık bir hata. Bunu geliştiricilere bildir.";
			link.l1 = "Ah, yapacağım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестодатель
		case "citizen":
			DelMapQuestMarkCity("Baster");
			LAi_SetImmortal(npchar, false);
			LAi_RemoveLoginTime(npchar);
			dialog.text = "Selamlar, kaptan! Sizi oldukça ilgilendirecek bir iş teklifim var.";
			link.l1 = "Devam et, monsieur.";
			link.l1.go = "citizen_1";
			DelLandQuestMark(npchar);
		break;
		
		case "citizen_1":
			dialog.text = "Guadeloupe'dan İspanyol Ana Karası'na bir nakliye işi için geminizi kiralamak istiyorum.";
			link.l1 = "Oraya yolcu olarak gitmek mi istiyorsun?";
			link.l1.go = "citizen_2";
			link.l2 = "İspanyol Ana Karası mı? Ben almayayım. İspanyollarla pek dost sayılmayız. Sana başka bir enayi bulmanı öneririm.";
			link.l2.go = "citizen_no";
		break;
		
		case "citizen_no":
			dialog.text = "Dediğiniz gibi, kaptan, gerçi bu yolculuk pek tehlikeli sayılmaz. Hoşça kalın.";
			link.l1 = "Elveda.";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_no_1":
			dialog.text = "Dediğiniz gibi, kaptan. Elveda!";
			link.l1 = "Elveda.";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
		break;
		
		case "citizen_2":
			dialog.text = "Tam olarak öyle değil, monsieur. Bir yolcu, kaptanın iradesine bağlı bir adamdır. Sizi, mürettebatınızı ve geminizi kiralamak istiyorum; kendimi ve iki arkadaşımı Panama'ya götürmeniz için.";
			link.l1 = "Panama'ya mı? Nasıl? Tüm kıtanın etrafından dolaşmak mı istiyorsun?";
			link.l1.go = "citizen_3";
		break;
		
		case "citizen_3":
			dialog.text = "Ha-ha-ha! Good joke, captain. Of course not. All you have to do is deliver us to Mosquito Bay, which is not far from Portobello. We'll make our way to Panama on our own; it won't be our first journey through the jungle.";
			link.l1 = "Ödeme ne olacak?";
			link.l1.go = "citizen_4";
		break;
		
		case "citizen_4":
			dialog.text = "İki sandık altın. Üç yüz adet. Gemiye bindiğimizde birini peşin alırsın. İkinci sandık ise varış noktamıza ulaştığımızda senin olacak.";
			link.l1 = "Böylesine kolay bir iş için cömert bir ödül. İşin içinde bir bit yeniği mi var, dostum?";
			link.l1.go = "citizen_5";
		break;
		
		case "citizen_5":
			dialog.text = "Kaptan, zaman para demektir, benim ve arkadaşlarımın ise hiç yok. Bu gece buradan yelken açmamız gerekiyor ve on gün içinde orada olmalıyız. Bu bizim ikinci seferimiz olacak. Peki, var mısın?";
			link.l1 = "Anlaştık!";
			link.l1.go = "citizen_6";
			link.l2 = "Üzgünüm, monsieur, ama teklifiniz bana fazlasıyla şüpheli geliyor. Kendinize başka bir enayi bulun.";
			link.l2.go = "citizen_no_1";
		break;
		
		case "citizen_6":
			dialog.text = "Harika. Şu anda arkadaşlarım ormanda, anlaşmamızı onlara bildireceğim. Bizi bu gece saat onda Capster Plajı'nda bulacaksınız. Geç kalma, Kaptan!";
			link.l1 = "Pekâlâ. Capster Beach, bu gece, saat onda.";
			link.l1.go = "citizen_7";
		break;
		
		case "citizen_7":
			dialog.text = "Bir dakika, kaptan, henüz birbirimize kendimizi tanıtmadık. Benim adım Bertrand Pinette. Peki ya siz...";
			link.l1 = ""+GetFullName(pchar)+". Kaptan "+GetFullName(pchar)+". Görüşürüz, Mösyö Pinette.";
			link.l1.go = "citizen_8";
		break;
		
		case "citizen_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "OpenTheDoors", 20.0);
			npchar.location = "None";
			AddQuestRecord("FMQ_Guadeloupe", "1");
			pchar.quest.FMQG_Capster.win_condition.l1 = "Hour";
			pchar.quest.FMQG_Capster.win_condition.l1.start.hour = 22.00;
			pchar.quest.FMQG_Capster.win_condition.l1.finish.hour = 23.99;
			pchar.quest.FMQG_Capster.win_condition.l2 = "Ship_location";
			pchar.quest.FMQG_Capster.win_condition.l2.location = "Shore29";
			pchar.quest.FMQG_Capster.win_condition.l3 = "location";
			pchar.quest.FMQG_Capster.win_condition.l3.location = "Shore29";
			pchar.quest.FMQG_Capster.function = "FMQG_CapsterBeach";
			SetFunctionTimerCondition("FMQG_StartLate", 0, 0, 1, false);
			pchar.questTemp.FMQG = "begin";
			pchar.GenQuest.SmugglersBlock = "baster_tavern";
		break;
		
		case "citizen_9":
			DelLandQuestMark(npchar);
			dialog.text = "Kaptan "+GetFullName(pchar)+", işte buradasın. Hazır mıyız?";
			link.l1 = "Evet. Hoş geldin gemiye.";
			link.l1.go = "citizen_10";
		break;
		
		case "citizen_10":
			dialog.text = "Pekâlâ. Avansını al - bir sandık dolusu dublon. Ve unutma - bizi varış noktamıza götürmek için sadece on günün var. Bir gün bile fazlası yok!";
			link.l1 = "Şartları hatırlıyorum. Merak etme, zamanında yetişeceğiz. Yerlerinize oturun.";
			link.l1.go = "citizen_11";
		break;
		
		case "citizen_11":
			DialogExit();
			GiveItem2Character(pchar, "chest");
			log_info("You have received a chest full of doubloons");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "officers", "sea_1", "none", "", "", "FMQG_OnBoard", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "officers", "sea_"+i, "none", "", "", "", 10.0);
			}
			pchar.quest.FMQG_SailStart.win_condition.l1 = "location";
			pchar.quest.FMQG_SailStart.win_condition.l1.location = "Guadeloupe";
			pchar.quest.FMQG_SailStart.function = "FMQG_SailingStart";
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 20, false);
				SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 40, false);
			}
			else
			{
				SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 10, false);
				SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 20, false);
			}
			pchar.questTemp.FMQG = "sail";
			DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
		break;
		
		case "citizen_12":
			dialog.text = "Yani, Kaptan, anlaşmanın kendi payınıza düşen kısmını tamamen yerine getirdiniz. Şimdi sıra bende. Bu sandığı ve en derin şükranlarımızı kabul edin.";
			link.l1 = "Sizinle iş yapmak bir zevkti, monsieur.";
			link.l1.go = "citizen_13";
		break;
		
		case "citizen_13":
			GiveItem2Character(pchar, "chest");
			log_info("You have received a chest full of doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Sailing", 200);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			dialog.text = "Aynı şekilde. Hoşça kal, Kaptan "+GetFullName(pchar)+".";
			link.l1 = "Elveda!";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
				sld.lifeday = 0;
			}
			AddQuestRecord("FMQ_Guadeloupe", "6");
			CloseQuestHeader("FMQ_Guadeloupe");
			pchar.questTemp.FMQG = "pause";
			pchar.quest.FMQG_Continue.win_condition.l1 = "Ship_location";
			pchar.quest.FMQG_Continue.win_condition.l1.location = "Baster_town";
			pchar.quest.FMQG_Continue.win_condition.l2 = "location";
			pchar.quest.FMQG_Continue.win_condition.l2.location = "Baster_town";
			pchar.quest.FMQG_Continue.function = "FMQG_BasterContinue";
			/* pchar.quest.FMQG_Block1.win_condition.l1 = "Rank";
			pchar.quest.FMQG_Block1.win_condition.l1.value = 13;
			pchar.quest.FMQG_Block1.win_condition.l1.operation = ">=";
			pchar.quest.FMQG_Block1.function = "FMQG_Block"; */
			//SetFunctionTimerCondition("FMQG_Block", 0, 0, 90, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	// лесник - открыть оружие снова.
			AddMapQuestMarkCity("baster", false);
		break;
		
		case "citizen_12a":
			dialog.text = "So, Captain, here we are. You have fulfilled only half of your part of the bargain, so I will do the same. Keep your advance as full pay. I hope you won't object; it was your fault, after all.";
			link.l1 = "Bunu pek sevdiğim söylenemez, ama haklı olduğunu kabul ediyorum. Şimdi yollarımızı ayıralım.";
			link.l1.go = "citizen_13a";
		break;
		
		case "citizen_13a":
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			dialog.text = "Her neyse, hizmetiniz için teşekkürler, kaptan "+GetFullName(pchar)+" . Elveda!";
			link.l1 = "Elveda.";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_15":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("bridgetown");
			dialog.text = "Ah! Ne karşılaşma ama! "+TimeGreeting()+", "+GetFullName(pchar)+"! Ama nasıl?";
			link.l1 = TimeGreeting()+", Monsieur Pinette. Sizi bulmak hiç de kolay olmadı.";
			link.l1.go = "citizen_16";
		break;
		
		case "citizen_16":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Peki sebebi nedir, kaptan?";
			link.l1 = "İyi efendim, burada bir adam var, adı "+GetFullName(sld)+" ve seni görmek için çok hevesli. Nedenini bildiğini varsayıyorum.";
			link.l1.go = "citizen_17";
		break;
		
		case "citizen_17":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Elbette biliyorum, ama sevgili Kaptanım, sizin de bilmeniz gerekir ki ben de monsieur'u görmeye hevesli değilim "+GetFullName(sld)+" hiç mi? Onun ödül avcısı mısın? Gerçekten anlamıyorum.";
			link.l1 = "Ne yazık ki, şu anda olduğum kişi buyum ve bundan hiç memnun değilim. Bir hata yaptım ve şimdi monsieur "+GetFullName(sld)+", kahretsin onu, bana bir seçim sundu. Ya senin Guadeloupe'a görkemli dönüşün ya da don Carlos de Milyar'ı kurtarma işinde sana yardım ettiğim için benim kafam gidecek. Bu bana çok dokunur, biliyorsun.";
			link.l1.go = "citizen_18";
		break;
		
		case "citizen_18":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Ah, o alçak! İnsanları böyle şantajla köşeye sıkıştırmak gerçekten de şeytanca bir yol!.. Peki Kaptan, ne yapacaksınız, bir seçim mi yapacaksınız yoksa böyle birinin sizi şantajla yönetmesine izin mi vereceksiniz?";
			link.l1 = "Ve sen ne düşünüyorsun? Bence benimle birlikte Basse-Terre'e geliyorsun.";
			link.l1.go = "citizen_19";
			link.l2 = "Burada bir seçeneğim var mı?";
			link.l2.go = "citizen_25";
		break;
		
		case "citizen_19":
			dialog.text = "Ah, sizi hayal kırıklığına uğratmalıyım, Kaptan. Güzel geminize binmek gibi bir niyetim yok. Burada zorbalıkla hiçbir şey elde edemezsiniz, etraf korumalarla çevrili ve en ufak bir şiddet belirtisi gösterirseniz yardım için bağırırım. Elbette, beni bıçaklamayı deneyebilirsiniz, ama iyi dostumuz soğuk bir cesetten tek kuruş alamaz. Yani, şu anda yapabileceğiniz en akıllıca şey beni rahat bırakmak. Size zarar vermeden gitmenize izin vereceğim.";
			link.l1 = "Gerçekten de tüm olanlardan sonra öylece çekip gideceğime inanıyor musun? Beni bu belanın içine sen sürükledin, alçağın teki, şimdi bedelini ödeme zamanı!";
			link.l1.go = "citizen_20";
			link.l2 = "Sanırım haklısın. Seni bıçaklama fikri hoşuma gidiyor ama hiçbir anlamı yok. Bunun son olduğunu bile düşünme. Şimdi Basse-Terre'e gidiyorum ve orada iyi dostumuza nerede olduğunu haber vereceğim. Sonra da peşine maskeli adamlar gönderecek.";
			link.l2.go = "citizen_21";
		break;
		
		case "citizen_20":
			dialog.text = "A-ah! Askerler! Yardım edin!!!";
			link.l1 = "...";
			link.l1.go = "citizen_fight";
		break;
		
		case "citizen_21":
			dialog.text = "Elbette. Patronuna söyle, maskeli adamlarını dizginlesin – son zamanlarda bayağı popüler oldum. Hoşça kal, Kaptan.";
			link.l1 = "...";
			link.l1.go = "citizen_22";
		break;
		
		case "citizen_22":
			DialogExit();
			LAi_SetActorType(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "19");
			pchar.quest.FMQG_Mayak.win_condition.l1 = "location";
			pchar.quest.FMQG_Mayak.win_condition.l1.location = "Mayak2";
			pchar.quest.FMQG_Mayak.function = "FMQG_Lighthouse";
		break;
		
		case "citizen_23":
			DelLandQuestMark(npchar);
			dialog.text = "Dur! Teslim oluyorum! Teslim oluyorum!";
			link.l1 = "Pekâlâ! Şimdi silahını bırak ve gemiye doğru yürü!";
			link.l1.go = "citizen_24";
		break;
		
		case "citizen_24":
			DialogExit();
			chrDisableReloadToLocation = false;
			RemoveAllCharacterItems(npchar, true);
			DoQuestReloadToLocation("Mayak2", "goto", "goto1", "FMQG_OnLighthouse");
		break;
		
		case "citizen_25":
			dialog.text = "Her zaman bir seçenek vardır, kaptan. Anladığım kadarıyla, o bankerden gelen tehditler olmasa peşime düşmezdiniz, değil mi?";
			link.l1 = "Aynen öyle.";
			link.l1.go = "citizen_26";
		break;
		
		case "citizen_26":
			dialog.text = "Güzel. O zaman onun ağzını kapatmanın sağlam bir yolunu ayarlayacağım. İşverenine götürmen için bir mektup yazalım. Ona söyle ki, eğer bir gün konuşmaya kalkarsa, Guadeloupe valisi Courage adlı kurye luggerinin – büyük bir elmas sevkiyatını taşımakla görevli olan geminin – kaybolmasını planlayan ve finanse eden adamı öğrenecek.";
			link.l1 = "Hm. Sanırım anlamaya başlıyorum, Mösyö Pinette.";
			link.l1.go = "citizen_27";
		break;
		
		case "citizen_27":
			dialog.text = "Akıllı biri olman iyi, Kaptan. Eğer De Lion Courage'ın kayboluşunun ardındaki gerçeği öğrenirse, o kurnaz cimrinin kafasını bizzat şehir kapılarına çakar. Şimdi yazacağım mektupta, şantajcıyı sakinleştirecek kanıtları bulacaksın. Kalemimi almam için bana bir dakika ver.";
			link.l1 = "Pekala...";
			link.l1.go = "citizen_28";
		break;
		
		case "citizen_28":
			LAi_Fade("", "");
			GiveItem2Character(pchar, "letter_baker");
			ChangeItemDescribe("letter_baker", "itmdescr_letter_pinett");
			dialog.text = "(yazıyor) Al, bunu al. Bu pakette iki benzer mektup var. Birini bankacıya ver, keyfini çıkarsın. Diğerini kendine sakla ve gizli tut.";
			link.l1 = " Bilgi güvenilir mi? ";
			link.l1.go = "citizen_29";
		break;
		
		case "citizen_29":
			sld = characterFromId("Baster_usurer");
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Baster", false);
			dialog.text = "Söz veriyorum, bana yardım ettin ve şimdi ben de sana yardım edeceğim. İçin rahat olsun, bu vasiyeti okuduğunda şantajcı seni rahat bırakacak. Ah, evet... Bir şey daha, kaptan. Bunu barışçıl bir şekilde çözdüğümüze göre... Bir gizli birikimim var, ve eğer gelecekte işlerime karışmayacağına söz verirsen, sana nerede bulacağını söyleyeceğim. Zaten Guadeloupe'a adım atmamı asla istemeyecekler.";
			link.l1 = "Eğer mektup beklediğimiz gibi işe yararsa, sana bunu kesinlikle garanti edebilirim.";
			link.l1.go = "citizen_30";
		break;
		
		case "citizen_30":
			dialog.text = "O halde anlaştık. Guadeloupe mağarasının içindeki kayalar arasında ara. Bu, yaşadığın sıkıntılar için küçük bir karşılık olsun. Yolun açık olsun, kaptan.";
			link.l1 = "Sana da aynısı, Mösyö Pinette.";
			link.l1.go = "citizen_31";
		break;
		
		case "citizen_31":
			DialogExit();
			pchar.questTemp.FMQG = "letter";
			AddQuestRecord("FMQ_Guadeloupe", "24");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 1;
		break;
		
		case "citizen_fight":
			chrDisableReloadToLocation = true;
			LAi_group_Delete("EnemyFight");
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("FMQG_PlantationGuards", 3.0);
			pchar.questTemp.FMQG = "fail";
			AddQuestRecord("FMQ_Guadeloupe", "18");
			CloseQuestHeader("FMQ_Guadeloupe");
		break;
		
		// вестовой к ростовщику
		case "cureer":
			DelMapQuestMarkCity("baster");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			dialog.text = "Selamlar, monsieur! Siz kaptansınız "+GetFullName(pchar)+", doğru mu?";
			link.l1 = "Doğru. Sizin için ne yapabilirim?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			sld = characterFromId("BasTer_usurer");
			dialog.text = "Monsieur "+GetFullName(pchar)+", Basse-Terre bankasının sahibi sizi en kısa zamanda ziyaretine bekliyor. Liman ofisimizi her gün kontrol etmemi emretti, böylece gelişinizi kaçırmayacağız.";
			link.l1 = "İlginç, peki beni görmeye bu kadar hevesli olmasının sebebi ne?";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "Monsieur "+GetFullName(sld)+"Sana   şahsen nedenini   anlatacağım.   Umarım   davetini   geri   çevirmezsin.";
			link.l1 = "Hm... Peki. Bu bankerler güçlü adamlardır ve küçük balıklarla vakit kaybetmezler. Adamla en kısa zamanda görüşeceğim.";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "Teşekkür ederim, Kaptan. Hoşça kalın!";
			link.l1 = "Elveda.";
			link.l1.go = "cureer_4";
		break;
		
		case "cureer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Baster_town", "reload1_back", true);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", true);
			LocatorReloadEnterDisable("Baster_town", "gate_back", true);//закрыть выходы из города
			pchar.questTemp.FMQG = "continue";
			pchar.quest.FMQG_Block.over = "yes";
			pchar.quest.FMQG_Block1.over = "yes";
			AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
		break;
		
		// Жан Дено
		case "Juan":
			dialog.text = "Argh! Seni pislik! Bunun rastgele bir karşılaşma olduğuna inanmam...";
			link.l1 = "Doğru dedin, Jean... affedersin, Juan demek istedim. Seni buldum. Şimdi lütfen kendini yük ambarıma atar mısın? Biraz rahatla, sonra konuşuruz.";
			link.l1.go = "Juan_1";			
		break;
		
		case "Juan_1":
			DialogExit();
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			pchar.questTemp.FMQG.Prisoner = GetFullName(npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "14");
			pchar.questTemp.FMQG = "juan_capture";
			DoQuestCheckDelay("LAi_ReloadBoarding", 3.5);
		break;
		
		case "Juan_2":
			dialog.text = "";
			link.l1 = "Ben anlaşmanın kendi payıma düşen kısmını yerine getirdim. Şimdi sıra sende. Yap, ama yalan söylemenin sonuçlarını aklında tut.";
			link.l1.go = "Juan_3";
		break;
		
		case "Juan_3":
			dialog.text = "Bertrand Pinette'i Barbados'ta, daha doğrusu ana plantasyonda bulacaksın. Orada işlerini sürdürmeyi planlıyordu. Plantasyonun yöneticisi de onun arkadaşıdır.";
			link.l1 = "Ne tür işler?";
			link.l1.go = "Juan_4";
		break;
		
		case "Juan_4":
			dialog.text = "Guadeloupe'ta yaptığı gibi. Yarı yasal ticaret, kaçakçılık, köleler. Bence köle ve şeker işi yapmayı planlıyor, yoksa neden bir plantasyona taşınsın ki?";
			link.l1 = "Anladım. İngiliz yetkilileri arasında ona arka çıkan biri var mı?";
			link.l1.go = "Juan_5";
		break;
		
		case "Juan_5":
			dialog.text = "Sanırım öyle. O tuhaf bir adam. Her yerde dostları var hep.";
			link.l1 = "Başka bir şey var mı?";
			link.l1.go = "Juan_6";
		break;
		
		case "Juan_6":
			dialog.text = "Ne gibi? Kurnaz ve zeki, her şeyi bilir, her zaman bir koz saklar. Onu daha yakından tanımaya pek vaktim olmadı.";
			link.l1 = "Anladım. Peki, Bridgetown'a yelken açmam gerekiyor. Serbestsin, don Juan. Sakın Pinette'i uyarmayı aklından bile geçirme. Onu orada bulamazsam, yine senin başın belada olacak.";
			link.l1.go = "Juan_7";
		break;
		
		case "Juan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.questTemp.FMQG = "headhunter_pinett";
			AddQuestRecord("FMQ_Guadeloupe", "17");
			// Пинетта - в Бриджтаун
			sld = characterFromId("FMQG_pass_1");
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation_F2", "goto", "goto1");
			sld.Dialog.currentnode = "citizen_15";
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("bridgetown", false);
		break;
		
		case "killer":
			dialog.text = "Üzgünüm dostum. Kişisel bir şey değil. Fazla şey biliyorsun, işte sorun bu.";
			link.l1 = "...";
			link.l1.go = "killer_1";
		break;
		
		case "killer_1":
			DialogExit();
			AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // правки релиза								  
			LAi_group_Delete("EnemyFight");
			int n = 2;
			if (MOD_SKILL_ENEMY_RATE > 6) n = 3;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("FMQG_killer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQG_KillersDestroy");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
