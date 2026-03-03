// Чарли Книппель - старый артиллерист
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, iTemp, amount;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		//ветка на взятие 2 варианта прохождения - за Англию
		if(CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Eng") && !CheckAttribute(npchar, "quest.HWICTake") && !CheckAttribute(pchar, "questTemp.HWIC.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
		{
			dialog.text = "Ah be oğlum, zincirli topmuş! Seni buraya ne getirdi?";
			link.l1 = "Zincirli mermiyle... ne? Neyse, sadece merhaba demek istemiştim.";
			link.l1.go = "exit";
			link.l2 = "Selamlar, Bay Knippel. Ha, neden size Knippel dediklerini şimdi anlıyorum. Her neyse, eskiden İngiliz Donanması'nda görev yaptığınıza dair söylentiler var. Elimde iyi bir gemi ve yetenekli bir mürettebat var. Kendimi ve gemimi İngiliz Tacı'nın... yani... İngiliz Milletler Topluluğu'nun hizmetine sunmak istiyorum. Bana bir tavsiye verebilir misiniz, birini önerebilir misiniz ya da bu konuda bana yardımcı olabilir misiniz?";
			link.l2.go = "Knippel_check";
			break;
		}
		//за Голландию
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "toKnippel")
			{
				dialog.text = "Ah, zincirli gülle miymiş! Seni buraya ne getirdi?";
				link.l1 = "Selamlar, Bay Knippel. Ha, neden size Knippel dediklerini şimdi anlıyorum. İngiliz Donanması'nda görev yaptığınıza dair söylentiler var, bu yüzden sizden yardım istemek istiyorum...";
				link.l1.go = "Dominica";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Zincirli gülle miymiş! Ne istiyorsun, dostum?";
			link.l1 = "Hayır, bir şey yok. Gidiyorum.";
			link.l1.go = "exit";
			break;
		}
		//за Англию
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
		{
			if (pchar.questTemp.HWIC.Eng == "TakeHollConvoy")
			{
				dialog.text = "Kaptan, bir gümüş konvoyunun yakalandığına dair bazı söylentiler duydum...";
				link.l1 = "İyi bilgilendirilmişsiniz, Bay Knippel.";
				link.l1.go = "HollConvoy_Check";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SentJons");
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Wait")
			{
				dialog.text = "Bir sorunuz var mı, kaptan?";
				link.l1 = "Hayır, önemli bir şey yok. Gidiyorum.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Start_main")
			{
				dialog.text = "Seni gördüğüme sevindim, kaptan! Komutanım Richard Fleetwood aslında seni şahsen tanımak için buraya gelecekti, ama dün akşam bir kaza oldu... Birisi onu tam caddenin ortasında öldürmeye kalktı, zincir gülle mi ne, az daha canından oluyordu!";
				link.l1 = "İmkansız! Muhafızlar ne yapıyordu?";
				link.l1.go = "Fleetwood_house";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Sorularınız var mı, kaptan?";
			link.l1 = "Hayır, bir şey değil. Gidiyorum.";
			link.l1.go = "exit";
		break;
		}
			dialog.text = "Ah, zincirli gülle miymiş! Seni buraya ne getirdi?";
			link.l1 = "Merhaba, sadece uğradım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------за Голландию--------------------------------------------------	
		case "Dominica":
			dialog.text = "Öyle mi? Peki, yıllar önce karaya oturmuş yaşlı bir denizci sana nasıl yardımcı olabilir, dostum?";
			link.l1 = "Bakın... Ben sıradan bir kaptanım ve Martinique ile Curacao arasında düzenli seferler yapıyorum. Martinique yakınlarında hayalet gemi tarafından iki kez saldırıya uğradım... Ama işin aslı şu ki, o ne Fata Morgana ne de Uçan Hollandalı. Onun yelkenlerini sıradan güllelerle parçalayabildim!";
			link.l1.go = "Dominica_1";			
		break;
		
		case "Dominica_1":
			dialog.text = "Öyle mi? Bir hayalet geminin top atışına yelken kaybetmesi pek alışılmış bir şey değil, şaşırtıcı doğrusu...";
			link.l1 = "Sadece gemim o canavarı geride bırakabildiği, rüzgâra karşı keskin seyir yapabildiği için hayatta kaldık. Geçen sefer, kaçabilmek için tüm yükümü denize atmak zorunda kaldım... kaybı hayal edebiliyor musun? İnsanın içi parçalanıyor!";
			link.l1.go = "Dominica_2";			
		break;
		
		case "Dominica_2":
			dialog.text = "Beni gafil avladınız, kaptan...";
			link.l1 = "Curacao Valisi Mathias Beck, şikayetlerimi hemen geçiştirdi. Hayalet gemiyle ilgili hikâyelerin saçmalık olduğunu, nöbetçilerimin ise romdan sarhoş olduklarını söyledi. Martinique valisi oraya bir devriye göndereceğine söz verdi ama gözlerinden hiçbir şey yapmaya niyeti olmadığını anladım. O lanet korsan 'hayalet' buralarda dolaşırken Martinique'e dönemem. Gemim de mürettebatım da küçük, onunla üçüncü kez karşılaşırsak sağ çıkmamız pek mümkün değil...";
			link.l1.go = "Dominica_3";			
		break;
		
		case "Dominica_3":
			dialog.text = "Bu gerçekten büyük bir talihsizlik, dostum. Ama sana nasıl yardımcı olabilirim?";
			link.l1 = "I heard from the sailors around here that there was a captain in St. John's named Richard Fleetwood who has hunted this same ghost ship. I don't know him personally, which is why I tell this story to you; perhaps you could pass on to him the tale of my misfortunes? I am sure that the filthy pirate is hiding somewhere near the wild shores of Dominica and raiding between Barbados and Martinique.";
			link.l1.go = "Dominica_4";			
		break;
		
		case "Dominica_4":
			dialog.text = "Barbados ile Martinique arasında mı? Ha! Şişman ve zengin bir ticaret yolu. Bu tam da o pisliğin yapacağı bir şey gibi geliyor kulağa.";
			link.l1 = "Ben ne zenginim ne de şişmanım, ayrıca bir donanma kaptanına askeri koruma için rüşvet verecek param da yok. Ama Sir Fleetwood bu lağım faresinin peşine düştüyse, ona bu 'Uçan Hollandalı'nın nerede bulunabileceğini söyler misiniz?";
			link.l1.go = "Dominica_5";			
		break;
		
		case "Dominica_5":
			dialog.text = "Buraya gelmekle iyi bir iş yaptın. Hikayeni doğru adamlara anlatacağım, lanet olsun ciğerime! Yakında Martinique ile tekrar ticaret yapabileceksin.";
			link.l1 = "Tanrı dualarını işitir umarım! Beni dinlediğin için teşekkürler, Charlie. En iyisini umut ediyorum. Hoşça kal, zincir güllelerinden sakın!";
			link.l1.go = "Dominica_6";			
		break;
		
		case "Dominica_6":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toDominica";
			AddQuestRecord("Holl_Gambit", "1-17");
			pchar.quest.toDominica.win_condition.l1 = "location";
			pchar.quest.toDominica.win_condition.l1.location = "Dominica";
			pchar.quest.toDominica.function = "PrepareToFleetwoodAttack";
			DelMapQuestMarkShore("Shore1");
			DelMapQuestMarkShore("Shore2");
			AddMapQuestMarkIsland("Dominica", true);
		break;

//----------------------------------------------за Англию--------------------------------------------------	
		case "Knippel_check"://начинаем проверять нашего ГГ по всем статьям
			if(makeint(PChar.reputation.nobility) < 48)//низкая репа
			{
				Notification_Reputation(false, 48, "low");
				PlaySound("Voice\English\hambit\Charlie Knippel-04.wav");
				dialog.text = "Neşeli Eski İngiltere'nin haydutların hizmetine ihtiyacı yok, zincir gülle miymiş, hadi oradan! Kusura bakma ama defolup gidebilirsin.";
				link.l1 = "Hey, hey, dostum, ağzını topla yoksa dikerim!";
				link.l1.go = "exit";
				break;
			}
			else
			{
				Notification_Reputation(true, 48, "low");
			}
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 30)//низкая навигация
			{
				dialog.text = "Kaptan, açık konuşacağım. Islak bir çuvaldan bile çıkamazsın. Seyir konusunda biraz daha ustalaştığında tekrar gel, anlaştık mı?";
				// belamour legendary edition покажем критерии  -->
				notification("Skill Check Failed (30)", SKILL_SAILING);
				//<--
				dialog.text = "Cao'n, filomuzun acemi tayfalara değil, deneyimli kaptanlara ihtiyacı var. Seyir sanatını gerçekten öğrendiğinde tekrar gel.";							 
				link.l1 = "Anladım... O zaman sonra görüşürüz.";
				link.l1.go = "exit";
				break;
			}
			else
			{
				notification("Skill Check Passed", SKILL_SAILING);
			}
			dialog.text = "Tam zamanında geldin kaptan, zincirli gülle miymiş! Richard bu tehlikeli işte kime güvenebileceğini bilmiyordu, hatta işi reddetmeyi bile düşünüyordu... Demek ki bugün fırsat kuşları kulağında tatlı tatlı ötüyor. Eğer beklentilerimizi karşılarsan, seni çok önemli birine tavsiye edeceğim. Bu işin altından kalkacak cesaretin var mı bakalım?";
			link.l1 = "Üzüm saçmasıyla doluyum, Bay Knippel.";
			link.l1.go = "Knippel_task";
		break;
		
		case "Knippel_task"://первое задание
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Lucas"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Ah ha! Görüyorum ki moraliniz yerinde, kaptan! Yakında ateş de peşinden gelecek! Şimdi iyi dinleyin. Hollanda Batı Hint Şirketi'nin gümüş filosu bir iki gün önce Curaçao'daki Willemstad'dan ayrıldı. Philipsburg'a doğru gidiyorlar. Bu sefer filoda sadece birkaç gemi var. Gümüş yüklü tek bir kalyon ve yanında iki refakatçi. Gümüş filosunu yakalayın, gümüş yüklü Doğu Kalyonu'nu ele geçirip Antigua'ya getirin. Refakatçileri batırabilirsiniz, onlar gözden çıkarılabilir. Zincir gülleyle ciğerlerini dağıtın, yar!";
			link.l1 = "Günleri sayılı.";
			link.l1.go = "Knippel_task_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_task_1":
			dialog.text = "Bir tavsiye, kaptan. Curacao'dan Sint Maarten'a giden ticaret yolu, St. Christopher kıyılarının pek uzağında değil. Orada pusu kurmanı öneririm. Bu işe girişmeden önce hem kendini hem de gemini iyi hazırla. Batı Hint Şirketi'yle uğraşmak, güzel bir kızla parkta yürüyüşe benzemez.";
			link.l1 = "Ne işe bulaştığımı biliyorum, ama açık sözlülüğünüz için teşekkür ederim, Bay Knippel. Hollanda gümüşüyle geri döneceğim.";
			link.l1.go = "Knippel_task_2";			
		break;
		
		case "Knippel_task_2":
			DialogExit();
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Eng = "true";//признак, что английка уже бралась
			HWICSilverConvoyInWorld();
			AddQuestRecord("Holl_Gambit", "2-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила ,чтобы вышел из архива. 																				   
			pchar.questTemp.HWIC.Eng = "begin";
			SetFunctionTimerCondition("HollConvoy_Over", 0, 0, 15, false);
		break;
		
		case "HollConvoy_Check"://начинаем проверять
			int iHal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_GALEON_L) iHal++;
				}
			}//признак наличия ТГ в компаньонах
			if (iHal > 0)
			{
				amount = sti(pchar.questTemp.HWIC.Eng.SlvQty) - GetSquadronGoods(pchar, GOOD_SILVER);
				if (amount <= 0)
				{
					dialog.text = "Ne olduğunu anlatmana gerek yok, kaptan. Gümrük memuru gemini incelerken bana her şey bildirildi... Oldukça iyi iş çıkardın, kaptan. Gerçekten harika! Hiç de kolay gelmedi kulağa, zincir güllemiş, ha!";
					link.l1 = "Takdir edilmek güzel.";
					link.l1.go = "HollConvoy_complete";
				}
				else
				{
					dialog.text = "Bana ne olduğunu anlatmana gerek yok. Gümrük memuru gemini incelerken bana her şey bildirildi... Tüm gümüşü geri getiremedin, zincir gülleymiş, hadi oradan! O Doğu Hindistan gemisinde ne kadar gümüş olduğunu, son pesoya kadar biliyorum. Bu görevin amacı sadece savaş becerilerini değil, aynı zamanda dürüstlüğünü de sınamaktı. İkincisinde sınıfta kaldın. Defol evimden, pis çömez!";
					link.l1 = "O zaman cehenneme git, ahmak!";
					link.l1.go = "HollConvoy_fail";
				}
			}
			else
			{
				dialog.text = "Bakıyorum da, filonda Hollanda Doğu Hindistan gemisi yok. Onu buraya ganimet olarak getirmeni söylemiştim. Satıp parayı kendine mi saklamaya çalıştın, ha?";
				link.l1 = "Bekle, gemiyi de mi getirmem gerekiyordu? Sadece gümüşü istediğini sanmıştım.";
				link.l1.go = "HollConvoy_noShip";
			}
		break;
		
		case "HollConvoy_noShip":
			dialog.text = "Charlie Knippel'ı kimse aptal yerine koyamaz! Sana ne dediğimi, ne demediğimi gayet iyi hatırlıyorum. Anlaşmamızın şartlarını çiğnedin, artık hiçbir namuslu İngiliz seninle iş yapmaz. Burada alçaklara yer yok. Defol evimden, pislik!";
			link.l1 = "O zaman cehenneme git, ahmak!";
			link.l1.go = "HollConvoy_fail";
		break;
		
		case "HollConvoy_fail":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-3");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Eng");//зачищаем для возможности отката к голландскому варианту
			pchar.questTemp.HWIC.Fail2 = "true";
		break;
		
		case "HollConvoy_complete":
			dialog.text = "Yarın yanıma uğra, seni hamimle tanıştırayım. Sana yeteneklerine layık işler teklif edecek. Üstelik... maddi teşviğini de bizzat halledecek. Hadi, yolun açık olsun!";
			link.l1 = "Pekâlâ, Bay Knippel. Yarın burada olacağım.";
			link.l1.go = "exit";
			npchar.greeting = "knippel_2";
			AddDialogExitQuestFunction("HollConvoy_Remove");
			AddQuestRecord("Holl_Gambit", "2-4");
			SetTimerFunction("EnglandGambit_2_ZadanieStart", 0, 0, 1);
			pchar.questTemp.HWIC.Eng = "Wait";
			AddSimpleRumourCity("They say that you captured a Dutch ship filled with silver. Well done! You are a valiant sailor, captain! Godspeed!", "SentJons", 10, 3, "");
		break;
		
		case "Fleetwood_house":
			dialog.text = "Ben de kendime aynı soruyu soruyorum... Bir alçak, Kaptan Fleetwood'un gözüne kararbiber attı ve Richard kılıcını çekemeden göğsüne bıçağı sapladı. Katil, kaptanı tek hamlede öldürmeyi umuyordu, çünkü bir daha vurmaya vakti yoktu, ama başaramadı. Kaptan Fleetwood her zaman ceketinin altında bir zırh taşır\nO pislik, zincirli mermiyle karaciğerini parçaladı, kaçmayı başardı ve yeraltına saklandı. Görünüşe göre şehirde dostları var. Kaptanın hatırladığı tek ayrıntı, suikastçinin tek gözlü olduğu. Ama bu da pek işimize yaramaz, çünkü bu aralar rıhtımlarda onun gibi bir sürü Kiklop dolaşıyor\nRichard çok kan kaybetti ve biber gözlerini öyle fena yakmış ki, şimdi neredeyse kör...";
			link.l1 = "Karabiber mi? Birini kör etmek için pahalı bir yol. Fleetwood biriyle fena halde ters düşmüş olmalı. Kaptanınıza üzüldüm. Saldırganı ararken bir iz bulabildiniz mi?";
			link.l1.go = "Fleetwood_house_1";
		break;
		
		case "Fleetwood_house_1":
			dialog.text = "Filo Komutanı Fleetwood'un denizcileri bütün kasabayı ve civardaki koyları aradı ama hiçbir şey bulamadılar, boyunlarına zincir topu değsin! Saldırıdan hemen sonra onu bulamadıysak, şimdi o alçağı bulmanın imkânı yok. Komutan Fleetwood'un çok düşmanı var... Ama kaptan, komutanım yine de olaydan sonra sizi görmek istiyor. Şu anda evinde dinleniyor, hadi ona gidelim. Beni takip edin!";
			link.l1 = "Önden buyurun, Bay Knippel.";
			link.l1.go = "Fleetwood_house_2";
		break;
		
		case "Fleetwood_house_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			bDisableFastReload = true;//закроем быстрый переход
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_town", "reload", "houseH1", "OpenTheDoors", -1);
			pchar.quest.Knippel_Outside.win_condition.l1 = "location";
			pchar.quest.Knippel_Outside.win_condition.l1.location = "SentJons_town";
			pchar.quest.Knippel_Outside.function = "Knippel_GoTown";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);
			sld = characterFromId("Fleetwood");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
			AddLandQuestMark(sld, "questmarkmain");
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.money = 110000;
		break;
		
		case "InFleetwoodHouse":
			dialog.text = "Fleetwood Kaptan yukarıda, odasında. Ona git, seni bekliyor. Ben burada kalacağım.";
			link.l1 = "Anlaşıldı, Bay Knippel. Hemen geliyorum.";
			link.l1.go = "exit";	
		break;
		
		case "Knippel_ToOfficer":
			dialog.text = "Dinle, Kaptan... Kaptan Fleetwood artık güvende ve emin ellerde. Ona saldıran o alçağa karşı intikamını almanda sana yardım etmek istiyorum. Topçu subayı olarak hizmetimi sunuyorum. Kılıç kullanmakta pek iyi değilim, artık yaşlandım, ama bir tüccar gemisinin seren direğini bin adım öteden indirebilirim.";
			link.l1 = "Bunu gerçekten görmek isterim. Gemimize hoş geldiniz, Bay Knippel!";
			link.l1.go = "Knippel_ToOfficer_1";	
		break;
		
		case "Knippel_ToOfficer_1":
			ForceHeroAutolevel(npchar);
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", false);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", false);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", false);//откроем локаторы
			//Книппеля - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 20;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			SetFunctionTimerCondition("GotoBridgetownOver", 0, 0, 30, false);//на все дела - 1 месяц
			AddSimpleRumourCity("They say that Sir Richard Fleetwood himself is indebted in you. You are a very important man in our town, sir", "SentJons", 10, 3, "");
		break;
		
		case "hired":
			dialog.text = "Selam, kaptan! Bir şeye mi ihtiyacınız var?";
			link.l1 = "Hayır, hiçbir şey.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			if (pchar.questTemp.HWIC.Eng == "MirageFail")
			{
				dialog.text = "Sen tam bir ahmaksın, zincirli gülle miymiş! En basit işi bile beceremedin – 'Mirage'ı ele geçirirken 'Valkyrie'yi kaybetmemeliydin.\nMürettebatımız artık senin komutanlığında hizmet etmeyecek. Eminiz ki Sir Fleetwood da kararımızı onaylayacak, çünkü o da bizim kadar aptallardan hoşlanmaz.";
				link.l1 = "Cehenneme git sen de efendin de!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "GotoBridgetown" || pchar.questTemp.HWIC.Eng == "SeekVanBerg")
			{
				dialog.text = "Sen tam bir aptalsın, zincir gülle miymiş! Kendi dertlerini çözmekle çok fazla zaman kaybettik\nMürettebatımız artık sana hizmet etmeyecek. Eminiz ki Sir Fleetwood da kararımızı onaylayacaktır, o da bizim kadar aptallardan hoşlanmaz.";
				link.l1 = "Sen de efendin de cehenneme gitsin!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "VanBergFailInWorld")
			{
				dialog.text = "Sen tam bir aptalsın, zincir gülle miymiş! Sana 'Valkyrie'de yalnız bir tüccarı oynayacaksın dedik, peki sen ne yaptın? Filonla korsanı korkutup kaçırdın!\nEminiz ki Sir Fleetwood da kararımızı onaylayacaktır, o da bizim kadar aptallardan hoşlanmaz.";
				link.l1 = "Senin de efendinin de canı cehenneme!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "MirageTake")
			{
				dialog.text = "Sen tam bir aptalsın, zincir gülle miymiş! 'Mirage'ı ele geçirip Antigua'ya gitmek dışında her şeyi yapmaya mı karar verdin?\nMürettebatımız artık sana hizmet etmeyecek. Eminiz ki Sir Fleetwood da kararımızı onaylayacaktır, o da bizim kadar aptallardan hoşlanmaz.";
			link.l1 = "Cehenneme git sen de, efendin de!";
			link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_VALCIRIA)//если сам на Валькирии
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "Boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA)
						{
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Eng.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			pchar.questTemp.HWIC.Detector = "eng_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "OnCuracao":
			pchar.quest.HWICEng_toBarbadosOver.over = "yes";//снять прерывание
			dialog.text = "Selamlar, kaptan. Sizi gördüğüme sevindim!";
			link.l1 = "Selam, Bay Knippel. Paran var mı? Ver bana, sonra Willemstad'a gidip Abigail'i alalım. Benimle gelir misin?";
			link.l1.go = "OnCuracao_1";	
		break;
		
		case "OnCuracao_1":
			dialog.text = "Kaptan, dinle... Şimdi bir yere gitmene gerek yok.";
			link.l1 = "Ne diyorsun? Bu saçmalık!";
			link.l1.go = "OnCuracao_2";	
		break;
		
		case "OnCuracao_2":
			dialog.text = "Fleetwood Kaptan'dan sana bir mektup getirdim. Ve parayı da. Ama bu para Abigail'in babası için değil, senin için. İki yüz bin peso. Mektubu oku ve onu fazla sert yargılamamaya çalış...";
			link.l1 = "Bu günlerde neler oluyor böyle?! Yine tatsız bir sürpriz mi? Mektubu ver!";
			link.l1.go = "OnCuracao_3";	
		break;
		
		case "OnCuracao_3":
			DialogExit();
			NextDiag.CurrentNode = "OnCuracao_4";
			AddMoneyToCharacter(pchar, 200000);
			LAi_SetCitizenType(npchar);
			npchar.lifeday = 1;//ещё денек пусть погуляет по пляжу
			pchar.quest.Holland_ShoreAttack.win_condition.l1 = "location";
			pchar.quest.Holland_ShoreAttack.win_condition.l1.location = "Curacao";
			pchar.quest.Holland_ShoreAttack.function = "CreateHollandShorePatrol";//патруль в прибрежных водах
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", false);//открыть подземелье
			pchar.questTemp.HWIC.Eng = "MerdokMeeteng";
			AddQuestRecordInfo("LetterFromFleetwood", "1");
			AddQuestRecord("Holl_Gambit", "2-23");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "OnCuracao_4":
			dialog.text = "Okudun mu, kaptan? Açık konuşacağım. Kaptan Fleetwood'dan ve yaptıklarından utanıyorum, zincir gülleyle... ah, kahretsin. Rodenburg, Abigail'in Richard'la ilişkisini öğrenince öfkelendi. Curacao'da devriyeler dolaşıyor, Şirketin askeri gemileri de civar sularda devriye geziyor. Buradan bir an önce defolmamız lazım.\n Kaptan, topçuya ihtiyacın var mı? Lükse ihtiyacım yok – bana düzenli bir denizci tayını yeter. Eskisi gibi kılıç sallayamam, yaşlandım artık, ama bin adım öteden bir tüccar gemisinin serenini indirebilirim.";
			link.l1 = "Vay canına, bunu gerçekten başarabileceğini görmek isterim, Bay Knippel. Ekibe hoş geldin!";
			link.l1.go = "Knippel_hire";
			link.l2 = "Başta size, İngiliz alçaklarına yardım ettiğime pişmanım. Şimdi bu beladan nasıl kurtulacağımı bilmiyorum. Kendi yolunuza gidin, sürprizlerden bıktım artık.";
			link.l2.go = "Knippel_exit";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*200;
			npchar.OfficerWantToGo.DontGo = true;
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
		
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 120, 120);
			LAi_SetOfficerType(npchar);
			npchar.greeting = "knippel_hire";
			NextDiag.CurrentNode = "Knippel_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			ForceHeroAutolevel(npchar);
			
			//Sinistra - через 2 месяца стартует личный квест Чарли Книппеля "Длинные тени старых грехов"
			SetTimerCondition("DTSG_Start", 0, 0, 60, false);
		break;
		
		case "Knippel_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
		break;
		
//------------------------------------------------против всех-----------------------------------------------
		case "Knippel_abordage":
			dialog.text = "Defol, seni pislik! Neden bu sakin Hollanda gemisine saldırdın? Değerli bir malım da yok, altınım da, zincir gülle mi atacaksın bana!";
			link.l1 = "Hollanda gemisi mi? Hahaha! Güldürme beni, 'Hollandalı'. Senin brigantinine seni ele geçirmek için saldırdım, sevgili Charlie. Kargo ambarıma hoş geldin. Şimdi nereye ve neden gittiğini konuşacağız...";
			link.l1.go = "Knippel_abordage_1";	
		break;
		
		case "Knippel_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-20");
            pchar.quest.Knippel_DieHard.over = "yes";
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "KnippelPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveKnippelOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Knippel_prisoner":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			dialog.text = "Sen bir şeytansın, korsan... Tüm günahların için cehennemde yanacaksın! Scre...";
			link.l1 = "Sakin ol, vaiz. Bir Püriten gibi vaaz veriyorsun. Önce kendi ruhunun haline bak istersen.";
			link.l1.go = "Knippel_prisoner_1";
		break;
		
		case "Knippel_prisoner_1":
			dialog.text = "Ne planlıyorsun, alçak? Komutanımdan ve o zavallı Hollandalı kızdan ne istiyorsun?";
			link.l1 = "Bu seni ilgilendirmez, Charlie. Artık sana ihtiyacım yok. Kalk.";
			link.l1.go = "Knippel_prisoner_2";	
		break;
		
		case "Knippel_prisoner_2":
			dialog.text = "Beni öldürmek mi istiyorsun? Senin gibi bir piçe de bu yakışır. *tükürür* Kahrolası herif!";
			link.l1 = "Kalk, Charlie. Son dualarını et.";
			link.l1.go = "Knippel_prisoner_3";	
		break;
		
		case "Knippel_prisoner_3":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_StandUp", "Kill_Knippel", 3.5);
			pchar.quest.RemoveKnippelOver.over = "yes";//снять таймер
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Knippel_officer":
			dialog.text = "Kaptan, zincirli gülle miymiş o!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "Ciğerime top mermisi, kaptan! Bir daha kara ayak basmayacağım. Geçen sefer handa zar atarken, bir alçak cebimi son kuruşa kadar boşalttı.";
				Link.l1 = "Ha‑ha, her şeyi kumarda kaybetmediğinden emin misin, "+npchar.name+"? Ne olursa olsun… seninle konuşmak istedim. Avrupa’ya yelken açmaya karar verdim — başka birinin gemisinde yolcu olarak. Ne zaman döneceğimi bilmiyorum. Burada beni beklemeni istemeyeceğim. Ve seni de yanıma sürüklemeyeceğim.";
				Link.l1.go = "SharlieEpilog_Knippel_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Bay Knippel, antik ve kayıp Tayasal adlı bir Kızılderili şehrine gidiyorum. Açık konuşayım, bu yolculuk hem çok tehlikeli olacak hem de alışılmadık – oraya bu... sihirli put aracılığıyla gitmemiz gerekiyor. Bana katılır mısınız?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Bay Knippel, bana gemiyle ilgili tam bir rapor ver.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Her limana yanaştığımızda belirli malları satın almanı istiyorum.";
				Link.l12.go = "QMASTER_2";
			}
			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Emriniz üzerine geldim, Kaptan.";
				Link.l2 = "Sana birkaç emir vermem gerekiyor.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Knippel_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Emirlerimi dinleyin!";
            Link.l1.go = "stay_follow";
			link.l2 = "Önemli değil. Dağılın!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Knippel_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Vay canına... Toplarımız sağlam, patlayanları değiştiriyoruz ve barutumuzu kuru ve güvende tutuyoruz. Ne tür bir rapor bekliyordunuz, Kaptan? Ben eski bir topçuyum, muhasebeci değilim. Zincir gülle miymiş, boş laf, yine de Karayipler'in en iyi topçusu benim, aklınızda bulunsun!";
			Link.l1 = "Burada tartışacak bir şey yok, Bay Knippel, işinizi gerçekten biliyorsunuz. Bir kambiyocu bulurum ben, merak etmeyin.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Eski Charlie'nin top güvertesini kaptan köşküne mi değiştirmesini istiyorsun? Kaptan, ben gemi batırırım, her peso için pazarlık yapmam. Üstelik, denediğimiz ilk kolonide beni kesinlikle kazıklayacaklarından eminim.";
			link.l1 = "Elbette, Bay Knippel. Uygun bir kambiyeci aramaya başlamalıyım.";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Seni dinliyorum.";
			Link.l1 = "Bu, gemiye çıkmakla ilgili.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Bu senin geminle ilgili.";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
			{
				Link.l3 = "Bir süreliğine filomdan ayrılmanı ve kendi başına şansını denemeni istiyorum.";
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
			Link.l1 = "Gemini değiştirdikten sonra gemini başka bir gemiyle değiştirmeni istemem. Senin gemin çok değerli.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Düşman gemilerine bindiğinde, eğer düzgünlerse onları kendine alabilirsin.";
			Link.l2.go = "Companion_TaskChangeYes";
			break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Aye aye!";
			Link.l1 = "Rahat ol.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
			break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "Yapılacak.";
			Link.l1 = "Rahat ol.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
			break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Aynen öyle!";
			Link.l1 = "Yapılacak.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
			break;

		case "Companion_TaskChangeYes":
			dialog.Text = "Yapılacak.";
			Link.l1 = "Rahat ol.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
			break;
			//	<========////////////////////////////////////////

		case "stay_follow":
            dialog.Text = "Emirleriniz?";
            Link.l1 = "Burada dur!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Beni takip et ve yetiş!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Ateşli silahlarınız için mühimmat türünü değiştirin.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Mermi türünü seçmek:";
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
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Bir tutum değişikliği var!";
            Link.l1 = "Serbestsiniz.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Bir değişiklik var!";
            Link.l1 = "Serbestsin.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Sana hizmetim sırasında gerçekten çok bağlandım, "+pchar.name+", ve ben kaptanımı asla yarı yolda bırakmam. Gerekirse cehenneme kadar peşinden gelirim. Seninleyim!";
			link.l1 = "Teşekkür ederim, Bay Knippel! Senin hakkında yanılmadığıma sevindim.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Ne zaman başlayacağız, kahrolası gözlerim?";
			link.l1 = "Biraz sonra. Buna hazırlanmamız gerek.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "22");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// Эпилог
		case "SharlieEpilog_Knippel_1":
			dialog.text = "Eh, gerçekten yazık… donanmama top mermisi isabet etti. Doğruyu söylemek gerekirse, Avrupa’yı görmek de kötü olmazdı.";
			link.l1 = "Bunu senden duyacağını tahmin etmemiştim. Öyleyse, '"+GetShipName("Ulysse")+"' pìnasegemisine hoş geldin! İstersen, eski dostumuz Richard Fleetwood’u ziyaret edebiliriz. Ona söyleyeceklerin vardır eminim.";
			link.l1.go = "SharlieEpilog_Knippel_2";
		break;

		case "SharlieEpilog_Knippel_2":
			dialog.text = "Hayır efendim. Richard’ın cehenneme gitmesini isterim. Onun adını duymak istemiyorum, yüzünü görmek ise hiç istemem.";
			link.l1 = "Senin istediğin gibi, "+npchar.name+", senin istediğin gibi. İki hafta içinde yelken açıyoruz. Güzel bir veda partisi planlıyorum. Umarım bize katılırsın.";
			link.l1.go = "SharlieEpilog_Knippel_3";
		break;

		case "SharlieEpilog_Knippel_3":
			dialog.text = "Hayır dersem, top mermisi boynumu kırsın, kaptan!";
			link.l1 = "Mükemmel. O zaman her şeyi hallettikten sonra tavernada görüşürüz.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Knippel_officer";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			pchar.questTemp.SharlieEpilog_Knippel = true;
			pchar.questTemp.SharlieEpilog_Friends = sti(pchar.questTemp.SharlieEpilog_Friends) + 1;
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Sen bir "+GetSexPhrase("Hırsız, beyefendi! Muhafızlar, yakalayın onu","Hırsız, kız! Muhafızlar, yakalayın onu")+"!!!","Şuna bak! Sırtımı döner dönmez sandığımı karıştırmaya kalktın! Yakalayın şu hırsızı!!!","Gardiyanlar! Soygun! Hırsızı yakalayın!!!");
			link.l1 = "Lanet olsun!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
