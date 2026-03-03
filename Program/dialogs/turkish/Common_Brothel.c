void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	string sTemp,sTemp1, str, str1;
	int	s1,s2,s3,s4,s5,p1, iColony, crewWhoreCost, charWhoreCost = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
		
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Brothel\" + NPChar.City + "_Brothel.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	crewWhoreCost = 50 + 7 * MOD_SKILL_ENEMY_RATE - hrand(40);
	charWhoreCost = 2460 + sti(pchar.rank) * 40;
	
	switch(Dialog.CurrentNode)
	{
		// ============= хозяйка борделя =============
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase(""+GetSexPhrase("Hangi kızlar, canım?! Garnizonun yarısı peşinde, sen de doğruca geneleve geliyorsun!","Kaybol, olur musun? Garnizonun yarısı peşinde!")+"","Her kasaba muhafızı seni arıyor. Şu anda sana hizmet vermek için deli değilim ...","Burada yapacak hiçbir işin yok!"),LinkRandPhrase(""+GetSexPhrase("Kızlarıma dokunmaya cüret et, seni canlı canlı yüzerim!","Defol git, pislik!")+"","Kirli"+GetSexPhrase("","")+" Katil, hemen mekânımdan defol! Muhafızlar!!!","Senden korkmuyorum, "+GetSexPhrase("serseri","sıçan")+"! Çok yakında kalemizde asılacaksın, fazla uzağa gidemezsin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, bir alarm benim için asla sorun olmaz...","Beni asla yakalayamayacaklar."),RandPhraseSimple("Sadece sus, seni aptal kocakarı.","Sorun çıkmasını istemiyorsan sus..."));
				link.l1.go = "exit";
				break;
			}
			//--> Мерзкий Божок
			if (CheckAttribute(pchar, "questTemp.ChickenGod.HostessDialog")) {
				dialog.text = "Aman Tanrım! Buraya nasıl girdiniz? Lütfen kaptan, yalvarırım, çıkın! Mekanımız şu anda kapalı!";
				link.l1 = "Seni görmek güzel, sevgili "+npchar.name+". Misafir listesinde yer alıyordum. Fakat böyle yerlerde, misafirler bile ödeme yapmak zorunda, yani... Lütfen işi zorlaştırmayın, ama bir oda için ödeme yapmak istiyorum.";
				link.l1.go = "chicken_god";
				
				DeleteAttribute(pchar, "questTemp.ChickenGod.HostessDialog");
				break;
			}
			//<-- Мерзкий Божок
			//--> туториал Мартиника
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start" && npchar.location == "FortFrance_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				link.l1 = "Dinle Aurora, bu gece için bir kız lazım bana. Onu evime götürmek istiyorum. Bunu ayarlayabilir misin?";
                link.l1.go = "Gigolo";
				break;
			}
			//<-- туториал Мартиника
			//Jason --> Заносчивый аристократ
			if (!CheckAttribute(pchar, "GenQuest.Badboy") && !CheckAttribute(npchar, "quest.Badboy") && !CheckAttribute(pchar, "questTemp.ZA.Block") && makeint(environment.time) > 15.0 && makeint(environment.time) < 21.0 && sti(pchar.questTemp.HorseQty) > 4)
			{
				dialog.text = "Ne kadar seçkin bir adamsınız. Üstelik kızlarım da sizi çok seviyor. İşletmem için sizden küçük bir ricada bulunmak isterim.";
				link.l5 = "Bunu duymak hoşuma gitti, kesinlikle. Peki, size nasıl yardımcı olabilirim?";
				link.l5.go = "Badboy";
				link.l8 = "Üzgünüm, ama şu anda meşgulüm.";
				link.l8.go = "exit";
				npchar.quest.Badboy = "true";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Badboy.Complete") || CheckAttribute(pchar, "GenQuest.Badboy.Continue"))
			{
				if (npchar.City == pchar.GenQuest.Badboy.Brothel.City)
				{
					dialog.text = "Ah, geri döndünüz! Onu hallettiniz mi "+pchar.GenQuest.Badboy.Brothel.Name+" kızlarıma dokunmamanı isterim?";
					link.l5 = "Evet. Artık burada yüzünü göstermeyecek.";
					link.l5.go = "Badboy_complete";
				break;
				}
			}
			// <-- Заносчивый аристократ
			
			//--> Jason Португалец
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (!CheckAttribute(pchar, "questTemp.Portugal") && bOk && !CheckAttribute(npchar, "quest.Portugal") && npchar.location == "Marigo_SecBrRoom" && makeint(environment.time) > 6.0 && makeint(environment.time) < 22.0 && sti(pchar.rank) >= 7)
				{
					DelMapQuestMarkCity("marigo");
					DelLandQuestMark(npchar);
					dialog.text = "Kaptan, sizden bir iyilik isteyebilir miyim?";
					link.l5 = "Sizin için, hanımefendi, ne isterseniz! Emrinizdeyim!";
					link.l5.go = "Portugal";
					link.l8 = "Üzgünüm, ama şu anda meşgulüm.";
					link.l8.go = "exit";
					npchar.quest.Portugal = "true";
					DelLandQuestMark(npchar);
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "HostressMoney" && npchar.location == "Marigo_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Hugo ile konuştunuz mu, kaptan bey?";
				if (sti(pchar.money) >= 10000)
				{
					link.l1 = "Ayrıca, hanımefendi, işte paranız. Her şey en iyi şekilde sonuçlandı...";
					link.l1.go = "Portugal_3";
				}
				else
				{
					link.l1 = "Evet, isteğinizi ona ilettim.";
					link.l1.go = "Portugal_exit";
				}
				break;
			}
			//<--Португалец
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "Aman Tanrım, şuna bakın! Ünlü korsan Charlie Prince! Kendi gözlerimizle görüyoruz!";
				link.l1 = RandSwear()+"Merhaba, Janette. Marcus Tyrex için bir görevle buradayım.";
				link.l1.go = "mtraxx_R";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel_repeat" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "Unutulmaz bir iyileştirici tedaviye hazır mısın, cesur korsanım?";
				if (sti(pchar.money) >= 31000)
				{
					link.l1 = "Benim! Charlie Prince lafı da parayı harcadığı gibi harcamaz, ha-ha!";
					link.l1.go = "mtraxx_R2";
				}
				else
				{
					link.l1 = "Az kalsın... Sanırım cüzdanımı burada, sizin mekânınızda kaybettim... Parayla geri döneceğim!";
					link.l1.go = "exit";
				}
				break;
			}
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple(TimeGreeting()+". Aşk evime hoş geldin. Benim adım "+npchar.name+", ve ben buranın sahibiyim. "+GetSexPhrase("Size nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?","Açıkçası, seni burada görmek beni biraz şaşırttı, "+GetAddress_Form(NPChar)+", ama sizi temin ederim ki hizmetlerimiz sadece erkeklere yönelik değil.")+"",TimeGreeting()+". Sizi memnuniyetle karşılıyorum, "+GetSexPhrase("yabancı","genç hanım")+", mütevazı işletmeme hoş geldiniz. Kendimi tanıtmama izin verin, ben "+NPChar.Name+" - kadın şefkatine aç erkekler için bu sığınağın koruyucusu. "+GetSexPhrase("Size nasıl yardımcı olabilirim?","Kadınlara karşı da bir zaafımız yok değil...")+"");
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple(TimeGreeting()+". Size nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?",TimeGreeting()+". Size nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?");
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))//не идёт квест девочки
			{
				if (!CheckAttribute(pchar, "GenQuest.BrothelLock"))// нет запрета от Мэри 280313
				{
					link.l2 = npchar.name+", kızlarından biriyle güzel vakit geçirmek istiyorum.";
					link.l2.go = "Hostess_1";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // не идёт старт Шарля
			{
				if (sti(pchar.ship.type) != SHIP_NOTUSED && GetCrewQuantity(pchar) > 0) // Rebbebion - а смысл, если нет как корабля, так и команды?
				{
					link.l3 = "Adamlarıma uzun zamandır bir jest yapmadım. Mürettebatım için toplu halde kız ayarlayabilir miyim?";
					link.l3.go = "ForCrew";
				}
			}
			link.l4 = "Bir sorum var.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakBrothelMadam"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l4.go = "ShipLetters_1";// генератор  "Найденные документы"
				}
				else
				{
					link.l4.go = "quests";
				}	
			}
			else
			{
				link.l4.go = "quests";//(перессылка в файл города)
			}	
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = "Dinle, "+npchar.name+", valinin yüzüğünü arıyorum. Sizin mekânınızda kaldı ve muhtemelen burada kaybetti.";
				link.l5.go = "TakeMayorsRing_H1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра

			// belamour ночной приключенец -->
			if(CheckAttribute(pchar, "GenQuest.NightAdventureVar") && pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleWhoreMoney")
			{
				link.l8 = "Bak, en güzel kızını almak istiyorum.";
				link.l8.go = "NA_Girl";
			}
			// <-- приключенец
			link.l9 = "Boşver, zaten gidiyorum.";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_1":
				pchar.questTemp.different.GiveShipLetters.speakBrothelMadam = true;
				dialog.text = RandPhraseSimple("Ne istiyorsun, yakışıklı?","Sizi dinliyorum, Kaptan.");
				link.l1 = "Dinle, "+npchar.name+",   bu belgeleri kurumunuzun özel bir odasında buldum ...";
				link.l1.go = "ShipLetters_2";				
		break;
		
		case "ShipLetters_2":
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Bir bakayım! Hmm... bir kaptan belgelerini kaybetmiş, değil mi? Bence bu konuda liman başkanına sormalısın.";
				link.l1 = "Belki, belki...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Bir bakayım! Ah! İsme bakılırsa, bunlar benim değerli müşterime ve kasabamızın saygın bir vatandaşına ait. Bu belgeleri kendim ona teslim edebilirim.";
				link.l1 = "Muhtemelen hayır...";
				link.l1.go = "exit";
				link.l2 = "Harika! İyi bir insana ve değerli bir mekâna her zaman yardım etmekten mutluluk duyarım.";
				link.l2.go = "ShipLetters_3";										
			}	
		break;
		
		case "ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "2");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "Hostess_1":
			if (!CheckAttribute(npchar, "quest.selected"))
			{
				if (CheckNPCQuestDate(npchar, "quest.date"))
				{
					dialog.text = ""+GetSexPhrase("Her zaman müşterilerimize hizmet etmekten mutluluk duyarız. Şimdi söyle bakalım, yakışıklı – gözünü kestirdiğin biri var mı, yoksa pek umursamıyor musun?","Pekâlâ, kızlarım kesinlikle sana... yardımcı olabilir. Şimdiden birini seçtin mi, yoksa pek umurunda değil mi?")+"";
					Link.l1 = ""+GetSexPhrase("Heh, şu an bir fahişeye ihtiyacım var, hem de hemen. Hangisi olduğu umurumda değil, kızların hepsi bana güzel görünüyor...","Elbette, görevlerini biliyorsa herkes uygun olur...")+"";
					Link.l1.go = "Hostess_NotChoice";	
					Link.l2 = "Evet, bir tane var, "+GetSexPhrase("gönlümü çelen biri...","en nazik o olurdu...")+"";
					Link.l2.go = "Hostess_Choice";
				}
				else
				{
					dialog.text = "Bugün sana uygun bir kızım yok, zaten çok fazla müşterimiz var. Yarın tekrar gel, pişman olmazsın!";
					Link.l1 = "Yazık, tam keyif almaya başlamıştım.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Hmm. Kız için zaten ödeme yaptınız. Lütfen, beni oyalamayın.";
				Link.l1 = "Pekala, geliyorum.";
				Link.l1.go = "exit";	
			}
		break;

        case "Hostess_NotChoice":
			sld = GetFreeHorseRef(npchar.city);
			location = &locations[FindLocation(npchar.city + "_Brothel")];
			if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > 98)
			{
				dialog.text = "Şu anda boşta hiç kızım yok, birkaç gün sonra tekrar uğraman gerekecek.";
				Link.l1 = "Peki, nasıl istersen.";
				Link.l1.go = "exit";	
			}
			else
			{
				// belamour legendary edition Орден Святого Людовика -->
				if(IsEquipTalisman9() && npchar.nation == FRANCE)
				{
					dialog.text = ""+GetSexPhrase("Pekâlâ, aygır, bu harika!","Hepsinin yetenekli olduğuna emin olabilirsin.")+"Sana güzel bir kız sunabilirim, adı "+GetFullName(sld)+", artık özgür.\nAaa, orada neyi böyle mahcupça saklıyorsun?! Bu Fransa'nın en yüksek nişanı mı? Söylentiye göre bu nişanın sahipleri sadece savaş meydanında değil, başka alanlarda da efsane olmuş... Ne demek istediğimi anladın sen, korsanım... Üstelik, herkes senin 'Nişanına' dokunmayı bir onur sayar, bu gece de mekanımda misafirim oluyorsun. Reddetmek yok, yakışıklı.";
					Link.l1 = "Elbette kabul ediyorum, bunda ne soru olabilir ki?!";
					Link.l1.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
					break;
				}
				// <-- legendary edition
				dialog.text = ""+GetSexPhrase("Pekâlâ, harika, benim aslanım!","Hepsi işlerinde gerçekten çok yetenekli, bundan hiç şüphen olmasın.")+"Sana çok güzel bir kız sunabilirim, adı "+GetFullName(sld)+", ve şu anda müsait. Bu zevkin bedeli "+FindRussianMoneyString(sti(sld.quest.price)+charWhoreCost)+". Kabul mü?";
				Link.l1 = "Hayır. Sanırım değil. Çok pahalı...";
				Link.l1.go = "exit";
				if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
				{
					Link.l2 = "Elbette, nasıl reddedebilirim ki?!";
					Link.l2.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
				}
				else
				{
					Link.l1 = "Ah kahretsin, yanımda o kadar para yok...";
					Link.l1.go = "exit";
				}
			}
		break;
		
        case "Hostess_NotChoice_agree":
			sld = &characters[sti(npchar.quest.choiceIdx)];
			if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
			{
				dialog.text = "Pekâlâ, "+GetSexPhrase("yakışıklı","güzel")+". "+sld.name+" seni ikinci kattaki özel bir odada bekliyor olacak.";
				Link.l1 = ""+GetSexPhrase("Pekâlâ, o zaman geliyorum","Pekala, geliyorum, o zaman")+"...";
				Link.l1.go = "exit";
				// belamour legendary edition деньги только без ордена или адмиральского мундира
				if(IsEquipTalisman9())
				{
					if(npchar.nation != FRANCE) AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
				}
				else
				{
					AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
				}
				sld.dialog.currentnode = "Horse_ReadyFack";			
				//--> таймер на возврат, чтобы не вечно ждали
				str = npchar.city;
				pchar.quest.(str).win_condition.l1            = "Timer";
				pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition               = "Brothel_checkVisitTime";	
				pchar.quest.(str).HorseId = sld.id;
				pchar.quest.(str).locator = sld.location.locator;
				//<-- таймер на возврат, чтобы не вечно ждали
				ChangeCharacterAddressGroup(sld, npchar.city + "_Brothel_room", "goto", "goto"+(rand(2)+1));
				LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload2_back", false); //открываем комнату
				npchar.quest.selected = true; //флаг взял девку у хозяйки
				SetNPCQuestDate(npchar, "quest.date"); //дату взятия запишем
				for(int n=0; n<MAX_CHARACTERS; n++)
				{
					makeref(sld, Characters[n]);
					if (sld.location == npchar.city+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
					{
						sld.dialog.currentnode = "Horse_4";
					}
				}
				
				// генератор найденных бумаг
				
				// belamour legendary edition не давать квесты губернатору и адмиралу
				bool MCGovernon = CheckAttribute(pchar, "questTemp.Patria.GenGovernor");
				bool MCAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4;
				
				if ((rand(4) == 1) && (pchar.questTemp.different == "free") && (!CheckCharacterItem(pchar, "CaptainBook")) && GetNpcQuestPastDayWOInit(npchar, "questShipLetters") > 10 && !MCGovernon && !MCAdmiral ) 
				{					
					pchar.questTemp.different = "GiveShipLetters";
					pchar.questTemp.different.GiveShipLetters = "toBrothel";
					pchar.questTemp.different.GiveShipLetters.Id = GetFullName(npchar);
					pchar.questTemp.different.GiveShipLetters.city = npchar.city;	
					pchar.questTemp.different.GiveShipLetters.variant = rand(2);
					p1 = rand(20 - MOD_SKILL_ENEMY_RATE) + 1; // даем хотя бы один день
					s1 = rand(80 - pchar.rank - p1) * 50 + rand(100);
					s2 = s1 * 2;
					s3 = s1 * rand(GetCharacterSPECIAL(pchar, "Luck")) + s1;
					s4 = s2 + s3;
					s5 = s4 * GetCharacterSPECIAL(pchar, "Charisma");
					pchar.questTemp.different.GiveShipLetters.price1 = s1;
					pchar.questTemp.different.GiveShipLetters.price2 = s2;
					pchar.questTemp.different.GiveShipLetters.price3 = s3;
					pchar.questTemp.different.GiveShipLetters.price4 = s4;
					pchar.questTemp.different.GiveShipLetters.price5 = s5;
										
					sld = ItemsFromID("CaptainBook");
					sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
					//ложим бумаги в итем								
					sTemp = "_Brothel_room";	
					sTemp1 = "_town";					
					sld.shown = true;
					sld.startLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp;
					sld.startLocator = "item" + (rand(4)+1);
					sld.endLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp1;
					pchar.questTemp.different.GiveShipLetters.item = true; //флаг -  бумаги валяются в итемах
					Log_QuestInfo("The papers are in location " + sld.startLocation + ", in locator " + sld.startLocator + " p1 : " + p1);
					
					pchar.quest.CheckShipLetters.win_condition.l1 = "location";
					pchar.quest.CheckShipLetters.win_condition.l1.location = sld.endLocation;
					pchar.quest.CheckShipLetters.function = "CheckShipLetters";
					
					SetTimerFunction("GiveShipLetters_null", 0, 0, p1); //освобождаем разрешалку на миниквесты 
					SaveCurrentNpcQuestDateParam(npchar, "questShipLetters");					
				}
				// генератор - "Повод для спешки"
				if((rand(5) == 2) && !CheckAttribute(pchar, "questTemp.ReasonToFast") && GetNpcQuestPastDayWOInit(npchar, "questReasonToFast") > 20 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !MCGovernon && !MCAdmiral) // Addon-2016 Jason
				{
					iColony = FindColony(npchar.city);	
					if( sti(Colonies[iColony].HeroOwn) == false && npchar.city != "Panama" && npchar.city != "Charles")
					{
						pchar.questTemp.ReasonToFast = "Begin";
						pchar.questTemp.ReasonToFast.city = npchar.city;
						sTemp1 = "_town";					
						pchar.quest.CheckReasonToFast.win_condition.l1 = "location";
						pchar.quest.CheckReasonToFast.win_condition.l1.location = npchar.city + sTemp1;
						pchar.quest.CheckReasonToFast.function = "ReasonToFast_CheckHorse";
						SaveCurrentNpcQuestDateParam(npchar, "questReasonToFast");	
					}	
				}				
			}
			else
			{
				dialog.text = "Ah, bakın, sorun şu ki "+sld.name+" ucuz bir kız değil, onun fiyatı "+FindRussianMoneyString(sti(sld.quest.price)+charWhoreCost)+". Ve görüyorum ki şu anda onu karşılayacak durumda değilsiniz. Zengin olduğunuzda tekrar gelin"+GetSexPhrase(", sevgili","")+"...";
				Link.l1 = "Benim şansım bu işte...";
				Link.l1.go = "exit";
			}
		break;

        case "Hostess_Choice":
			dialog.text = "Kızlar ve müşteriler birbirlerine karşı sıcak duygular beslediğinde her zaman mutlu olurum... Bana adını söyle.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";	
		break;
		
        case "Hostess_Choice_1":
			sld = CheckHorsesName(npchar.city, 9);
			if (sld.id == "none")
			{
				dialog.text = "Hmm... bir yanlışlık olmalı. Benim işletmemde öyle bir kız yok. Belki de adını yanlış hatırlıyorsunuzdur.";
				Link.l1 = "Hmm... ama ben az önce onunla konuştum.";
				Link.l1.go = "Hostess_Choice_2";				
				Link.l2 = "Belki de. Emin olmak için adını bir kez daha sormak daha iyi olur. Bunun hakkında seninle sonra konuşurum.";
				Link.l2.go = "exit";	
			}
			else
			{
				dialog.text = GetFullName(sld)+", onun hakkında mı konuşuyorsun?";
				Link.l1 = "Evet, onun hakkında.";
				Link.l1.go = "Hostess_NotChoice_agree";				
				Link.l2 = "Hayır, o değil.";
				Link.l2.go = "Hostess_Choice_2";
				npchar.quest.choiceIdx = sld.index;
			}
		break;
		
        case "Hostess_Choice_2":
			dialog.text = "O halde belki de bana adını bir kez daha söylemelisin, belki o zaman kimden bahsettiğini anlarım.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
			Link.l2 = "Belki. Emin olmak için adını bir kez daha sormak daha iyi olur. Bunun hakkında seninle sonra konuşacağım.";
			Link.l2.go = "exit";	
		break;
		//==> команда
		case "ForCrew":
			dialog.text = "Hmm... Adamlarının biraz 'rahatlamasına' yardım mı etmek istiyorsun? Bak, benim işletmem saygın bir yerdir ve en iyi kızlar bendedir. Ama limanda tanıdığım birkaç kadın da var, onlar bütün tayfanı memnun etmekten mutluluk duyar. Bunun sana maliyeti ise "+FindRussianMoneyString(GetCrewQuantity(pchar)*crewWhoreCost)+".";			
			link.l1 = "Peki, kabul ediyorum.";
			link.l1.go = "ForCrew_1";
			link.l2 = "Sanırım onsuz da idare edebilirler...";
			link.l2.go = "exit";
		break;
		
		case "ForCrew_1":
		    if (sti(Pchar.money) >= GetCrewQuantity(pchar)*crewWhoreCost && GetCrewQuantity(pchar)>0)
		    {
		        AddMoneyToCharacter(Pchar, -makeint(GetCrewQuantity(pchar)*crewWhoreCost));
	            AddCrewMorale(Pchar, 10);
				ChangeCharacterComplexReputation(pchar,"authority", 1);
	            LAi_Fade("", "");
                AddTimeToCurrent(5 + rand(1), rand(30));
			    DialogExit();
		    }
		    else
		    {
		        dialog.text = "Bu benim işim değil, ama bence önce bir mürettebat tutacak kadar para kazanmalısın, ancak ondan sonra onların moralini düşünmelisin.";
			    link.l1 = "Muhtemelen haklısın...";
			    link.l1.go = "exit";
		    }
		break;
		
		case "Woman_FackYou":
			dialog.text = "Sevgilim, ne yapıyorsun sen?! Oysa düzgün bir kaptana benziyordun... Bu sefer uçamayacaksın, yakışıklı. Muhafızlar kanatlarını kırpacak...";
			link.l1 = "Kapa çeneni, koca karı.";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		
		//поиски кольца губернатора
		case "TakeMayorsRing_H1":
			dialog.text = "Herhangi bir yüzük bulamadım.";
			link.l1 = "Ya kızların?";
			link.l1.go = "TakeMayorsRing_H2";
		break;
		
		case "TakeMayorsRing_H2":
			dialog.text = "Onlar da getirmedi. Eğer bir müşteri bir şeyini unutur ya da kaybederse, kızlarım bana getirir. Ama kimse bana valinin yüzüğünü getirmedi.";
			link.l1 = "Anlıyorum... Ama ya onu kendilerine saklamaya karar verdilerse?";
			link.l1.go = "TakeMayorsRing_H3";
		break;
		
		case "TakeMayorsRing_H3":
			dialog.text = "Pek mümkün değil. Kızların müşterilerden aldıkları hediyeleri saklamalarına izin veriliyor, ama hepsi bu.";
			link.l1 = "Anladım. Pekâlâ, teşekkür ederim, "+npchar.name+".";
			link.l1.go = "exit";
		break;
		
		case "Hostess_inSexRoom":
			dialog.text = "Ah, işte buradasın...";
			link.l1 = "Buradayım, hanımefendi!";
			link.l1.go = "exit";
			pchar.quest.SexWithHostess_null.over = "yes"; //нулим таймер на не пришёл
			NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
			{
				sld = CharacterFromID(pchar.RomNaTroih_Shluha);
				dialog.text = ""+sld.name+"! Kahramanım, aşağıda hiç vakit kaybetmemişsin bakıyorum!";
				link.l1 = "Bu zayıflığımı affedeceğinizi umarım, kraliçem?";
				link.l1.go = "RomNaTroih_2";
			}
			AddDialogExitQuestFunction("SexWithHostess_fack");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.RomNaTroih");
            if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 10);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 5);
		break;
		
		// ================================== рядовой состав =======================================
        case "Horse_talk":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Buradan defolup gitsen iyi edersin!","Şehirdeki tüm muhafızlar seni arıyor! En iyisi buradan git...","Ortada bir karmaşa yarattın ve şimdi buraya mı geldin?! Hayır, bu sefer olmaz..."),LinkRandPhrase("Defol!","Pis katil, defol buradan! Muhafızlar!","Senden korkmuyorum,"+GetSexPhrase("alçak","fare")+"! Yakında kalemizde asılacaksın, fazla uzağa gidemezsin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, bir alarm benim için asla sorun olmaz...","Beni asla yakalayamayacaklar."),RandPhraseSimple("Heh, ne kadar da aptal bir kadınsın...","Kes sesini, orospu, yoksa ben sustururum..."));
				link.l1.go = "exit";
				break;
			}
			dialog.text = NPCStringReactionRepeat("Merhaba, "+GetAddress_Form(NPChar)+""+GetSexPhrase("",", hihi...")+". Senyora'yı görüp siparişi doldurman gerek.","Yine mi sen? Lütfen idareciyle konuş. O, ofisinde.","Bak, "+GetAddress_Form(NPChar)+""+GetSexPhrase(", Umarım konuşmakta olduğun kadar diğer konularda da inatçısındır... Yine","Bir kez daha")+"   Mekânın sahibini görmenizi istiyorum.","Oh, "+GetAddress_Form(NPChar)+""+GetSexPhrase(", ne inatçısın sen!",", Hihi... Ne inatçısın sen, değil mi?")+" Senyora'yı görüp siparişi doldurman gerek.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Pekâlâ, "+GetSexPhrase("güzelim, ","")+"Anladım"+GetSexPhrase("","")+".","Evet, tabii...",""+GetSexPhrase("Hiç şüphen olmasın güzelim, ben de en az bir boğa kadar inatçı ve güçlü biriyim!","Evet, evet...")+"",""+GetSexPhrase("Ah kahretsin, bir şeyi kaçırmış olmalıyım... Özür dilerim, canım.","Peki, tamam.")+"",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			Link.l2 = "Ve o nerede?";
			Link.l2.go = "Horse_1";
			Link.l3 = LinkRandPhrase(""+GetSexPhrase("Ah, güzelim, o gözlerinde kaybolabilirim...","Çok güzelsin, sevgilim!")+"",""+GetSexPhrase("Biliyor musun, daha önce hiç bu kadar güzel bir kadınla karşılaşmamıştım!","Biliyor musun, daha önce hiç bu kadar zarif bir hanımefendiyle karşılaşmamıştım!")+"",""+GetSexPhrase("Sevgilim, çok güzelsin.","Lanet olsun, o köylülerden bıkmıştım... Ve sen öyle çekicisin ki!")+"");
			if (!CheckAttribute(npchar, "quest.choice"))
			{
				Link.l3.go = "Horse_2";
			}
			else
			{
				Link.l3.go = "HorseChoice_" + npchar.quest.choice;
			}
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = LinkRandPhrase("Dinle, "+GetSexPhrase("güzellik","tatlım")+", burada bir alyans bulmuş olma ihtimalin var mı? Görünüşe göre birisi kaybetmiş...","Sevgilim, buralarda bir alyans ya da ona benzer bir şey gördün mü?","Dinle, "+GetSexPhrase("kedim","tatlım")+", buralarda bir alyans görmedin mi?");
				link.l5.go = "TakeMayorsRing_S1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
			
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "santodomingo_brothel" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_1" && npchar.id == "HorseGen_"+reload_location_index+"_2")
			{
				link.l6 = "Merhaba, güzelim. Marcus Tyrex beni gönderdi, şu kehribar kolyeye bir bak...";
				link.l6.go = "mtraxx";
			}
			NextDiag.TempNode = "Horse_talk";
		break;
		
        case "Horse_1":
			dialog.text = "Ofisinde. Buradan, sokağa çıkan kapının tam karşısındaki kapıdan ya da evin öteki tarafından sokaktan ulaşabilirsin. Adı "+characters[GetCharacterIndex(npchar.city+"_Hostess")].name+".";
			Link.l1 = "Anladım. "+GetSexPhrase("tatlım","sevgilim")+", teşekkür ederim.";
			Link.l1.go = "exit";			
		break;
		
        case "Horse_2":
			if (rand(1))
			{
				dialog.text = LinkRandPhrase("Aman Tanrım, böyle şeyler duymak ne güzel! Şu an boşum, eğer beni seçersen pişman olmazsın...","Gerçekten öyle mi düşünüyorsun? Biliyor musun, bu çok hoş... Bak, şu anda boşum, istersen beni seçebilirsin."+GetSexPhrase(" Sana bir aşk denizi ve okşayışlardan oluşan bir okyanus vaat ediyorum...","")+"",""+GetSexPhrase("Öyle mi düşünüyorsun? Gerçekten çok onurlandım. Bilirsin, böyle iltifatları pek nadir duyarım...","Ah kızım... şu taşralılardan ne kadar bıktığımı bir bilsen...")+" Hey, bak, şu anda müsaitim, istersen seni mutlu edebilirim. Söz veriyorum, seni hayal kırıklığına uğratmam...");
				if (CheckAttribute(pchar, "questTemp.RomNaTroih") && !CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
				{
					link.l1 = "Sevgilim, tam da bunu yapacaktım! Ne şanslıyım ki ev sahibiniz benimle üst katta özel bir görüşme ayarlamış bile. Katılmak ister misiniz?";
					Link.l1.go = "RomNaTroih_1";
					pchar.questTemp.RomNaTroih_Pogovoril = true;
					break;
				}
				link.l1 = "O halde seni seçeceğim!";
				Link.l1.go = "Horse_3";		
				Link.l2 = ""+GetSexPhrase("Hayır, bu sadece hoş bir hanımefendiye iltifattı","Bu sadece bir iltifattı")+".";
				Link.l2.go = "exit";
				npchar.quest.choice = 0; //был базар, но ГГ потом отказался
			}
			else
			{
				dialog.text = LinkRandPhrase(""+GetSexPhrase("Ne diyorum biliyor musun, tatlım? Bu ucuz laflara ihtiyacım yok. Ya iş yap ya da git!","İhtiyacım olan tek şey buydu! Kadınlardan iltifat almak!")+"",""+GetSexPhrase("Kadınların kulaklarıyla âşık olduğunu mu sanıyorsun? Bak canım, bu hiç de doğru değil. Beni istiyorsan madama parasını öde, boş laflarla vaktimi harcama.","Kızım, kendini boş laflarla harcama. Eğer ciddiysen - o zaman öde...")+"",""+GetSexPhrase("Ah, bir zevk düşkünü daha... Sadece öde ve ben seninim. Hepsi bu kadar basit, o nazik saçmalıkların hiçbiri yok!","Ne oldu sana, canım? Eğer kendini zevklere bırakmak istiyorsan, o zaman öde ve şu saçmalıkları bırak!")+"");
				link.l1 = "Ah, ne kuvvetli bir tutuş!";
				Link.l1.go = "exit";
				npchar.quest.choice = 2; //ГГ послали
			}
		break;
		
        case "Horse_3":
			dialog.text = characters[GetCharacterIndex(npchar.city+"_Hostess")].name+" tüm resmi işlemleri ofisinde tamamlıyor. Git, onunla görüş"+GetSexPhrase(", kahramanım,","")+" ve adımı söyle - "+npchar.name+". Seni bekliyor olacağım...";
			Link.l1 = "Anladım canım, yakında dönerim...";
			Link.l1.go = "exit";
			npchar.quest.choice = 1; //она согласная
			SetNPCQuestDate(npchar, "quest.choice");
		break;
		
        case "Horse_4": 
			dialog.text = NPCStringReactionRepeat("Zaten ödediniz.","Sana yukarı çıkmanı söyledim.","Yukarıda, genç adam.","Bazı insanlar o kadar yavaş düşünüyor ki...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Evet, biliyorum.","Hatırlıyorum.","Ah, kendini tekrar etme, hatırlıyorum.","Hmm, ne demek istiyorsun?",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "Horse_4";
		break;
		
		//===>> реакция на попытки пофлиртовыть, если флирт уже был
        case "HorseChoice_0": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("Seni tam olarak anlayamıyorum."+GetSexPhrase(" Önce iltifat ediyorsun, sonra da sözünden dönüyorsun. Ne tuhaf bir insansın...","")+"","Yine iltifat mı ediyorsun?","Yönetici ofisinde. Anladın mı?","Müşterilerimize hakaret etmememiz gerekiyor, ama sen gerçekten bunu hak ediyorsun"+GetSexPhrase("","")+"...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Her şey öylece oldu...","Pekala, bunu yapacağım.","Evet, anladım.","Affedersin, sevgilim.",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "İltifatın için teşekkürler. Eğer beni almak istiyorsan, git ve madamla konuş. Her zamanki gibi iş işte.";
				Link.l1 = "Anladım.";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				if (!CheckNPCQuestDate(npchar, "quest.choice"))
				{
					dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Canım, bunların hepsini zaten konuştuk. ","")+"Beni fazla bekletme...",""+GetSexPhrase("Hmm... Dinle, canım, ben","Ben")+" Sözlerin çok hoş, ama asıl meseleye geçebilir misin...","Belki bunu madamla konuşursunuz, değil mi?","Hmm... Ne desem bilemiyorum...","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Bunu asla yapmam, beni bekle!","Elbette!","Elbette, dediğiniz gibi!","Hanımefendinizi görmek için zaten koşuyorum...",npchar,Dialog.CurrentNode);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Seni bekliyordum, ama beni almaya gelmedin... Bunu pek sevdiğimi söyleyemem...";
					Link.l1 = "Görüyorsun ya, her şey olduğu gibi oldu...";
					Link.l1.go = "exit";
					npchar.quest.choice = 0; //был базар, но ГГ потом отказался
				}
			}
			else
			{
				dialog.text = "Ah, yine sen geldin, benim "+GetSexPhrase("görkemli korsan","güzel kız")+"! Eğer beni tekrar istersen, madama uğra, pişman olmazsın..."+GetSexPhrase(" Bu arada seni tanıdım, canım, ama bize tüm müşterilere eşit davranmamız gerektiği söylendi. Kimseye ayrıcalık yapmamalıyız, kusura bakma...","")+"";
				Link.l1 = "Endişelenme, sevgilim. Sadece beni biraz daha bekle, "+GetSexPhrase("tatlım","tatlım")+", ve yakında tekrar baş başa görüşeceğiz.";
				Link.l1.go = "exit";
				Link.l2 = "Beni hatırlaman çok hoş, ama bu geceyi seninle geçiremem, üzgünüm.";
				Link.l2.go = "HorseChoice_1_Add";
			}
		break;
		
        case "HorseChoice_2": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("Yani,"+GetSexPhrase(" sevgili dostum,","")+" işinle meşgul olsan iyi edersin. Hiçbir şey yapmamaktan daha faydalı.",""+GetSexPhrase("Hmm, neden böyle davranıyorsun ","Neden sen")+" aynı şeyleri tekrar tekrar mı söylüyorsun?","Hey, bu kadar yeter artık?!","Hm, ne sürpriz, yine hiçbir şey yok"+GetSexPhrase(", yine o aptalca cilve denemelerinle geldin! Benimle yatmak istiyorsan, git madame'a sor, sersem!","...")+"","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Evet, duydum"+GetSexPhrase("","")+" sen...","Hmm, demek böyle oluyor...","Hmm, belki bu kadar yeter, ya da belki de yetmez...","Ağzını topla"+GetSexPhrase(", keçi","")+"...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ah, yine sen geldin! "+GetSexPhrase("Ve yine, o aptalca iltifatlar. Bu dünyada hiçbir şey değişmiyor... Eğer ","Sadece bir hatırlatma: eğer ")+"istemek mi istiyorsun"+GetSexPhrase("iyi eğlenceler","iyi eğlenceler")+" benimle, mekânın sahibine öde. Sözlerin umurumda bile değil.";
				Link.l1 = "Bu çok da şaşırtıcı değil...";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1_Add":
			dialog.text = "Beni mutlu ettiğini söyleyemem... Yazık.";
			Link.l1 = "Üzgünüm...";
			Link.l1.go = "exit";
			npchar.quest.choice = 0;
		break;
		
		//===>> секс
        case "Horse_ReadyFack":
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "SantoDomingo_Brothel_room" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_2" && npchar.name == "Gabriela")
			{
				dialog.text = "Ah, sonunda geldiniz! Harika! Rahatça konuşabiliriz, kimse dinlemiyor...";
				Link.l1 = "Yani, mavi kehribarı sana veren İspanyol muydu?";
				Link.l1.go = "mtraxx_2";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SantoDomingo");
				break;
			}
			if (!CheckAttribute(npchar, "quest.choice")) npchar.quest.choice = 0;
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = RandPhraseSimple("Seni gördüğüme çok sevindim. "+GetSexPhrase("Peki, şimdi ne yapacağız?","Biraz keyfimize bakalım mı?")+"","Çekinme"+GetSexPhrase(", en az iki saat boyunca kendini evinde hisset.",". Sizi eğlendirebileceğimden hiç şüpheniz olmasın.")+"");
					Link.l1 = RandPhraseSimple("Sıkıcı olacağını sanmıyorum...",""+GetSexPhrase("Hadi güzel vakit geçirelim, bebeğim!","Hiç vakit kaybetmeyelim!")+"");
				break;
				case "1":
					dialog.text = "Ah, yine sensin, benim "+GetSexPhrase("Şanlı korsan! Sana bir şey söz vermiştim ve şimdi sözümü tutmaya hazırım","Güzel kız! Önümüzdeki iki saati asla unutamayacaksın")+"...";
					Link.l1 = "Şimdi bu kulağa cazip geliyor...";	
				break;
				case "2":
					dialog.text = "Ah, sonunda geldiniz. Hadi vakit kaybetmeyelim!";
					Link.l1 = ""+GetSexPhrase("Hadi yapmayalım, korkak...","Şimdi bana neler yapabileceğini göster...")+"";
				break;
			}
			if (pchar.sex == "woman")
			{
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex";
				AddDialogExitQuest("PlaySex_1");
				// кач от борделя
				if (CheckNPCQuestDate(pchar, "BrothelSex"))
				{
					if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	AddCharacterHealth(pchar, 10);
					else 												AddCharacterHealth(pchar, 5);
					SetNPCQuestDate(pchar, "BrothelSex");
				}
				// изменение статусов
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "FencingS", -15);
				AddCharacterExpToSkill(pchar, "Pistol", -15);
			}
			else
			{
				pchar.horsekiss = npchar.id;
				Link.l1.go = "Horse_Kiss";
			}
			//--> кол-во посещений
			if (!CheckAttribute(npchar, "quest.sexHappend")) npchar.quest.sexHappend = 1;
			else npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(23, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
		break;
		
		case "Horse_Kiss":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("Horse_Kiss", "");
		break;

        case "Horse_AfterSex":
			if (CheckAttribute(pchar, "questTemp.ReasonToFast") && pchar.questTemp.ReasonToFast == "Begin")
			{
				dialog.text = "Kaptan, neden bu kadar sessizsiniz?";
				link.l1 = LinkRandPhrase("Pekala, işte ben.","Bir dahaki sefere konuşuruz.",RandPhraseSimple("Ben sana konuşman için para vermiyorum.","Ama sen, "+GetSexPhrase("güzellik","tatlım")+",   o kadar zaman boyunca hiç de sessiz değildiniz."));
				link.l1.go = "exit";
				link.l2 = ""+GetSexPhrase("Sen gerçekten harikaydın, neredeyse aklımı kaybediyordum! Hem bu kadar güzel hem de bu kadar çekici bir kadın bulmak çok nadir bir şey","Ah, bir kadını nasıl mutlu edeceğini gerçekten biliyorsun... Çok heyecanlıyım.")+".";
				link.l2.go = "Horse_ReasonToFast_1";
			}
			else
			{
				switch(npchar.quest.choice)
				{
					case "0":
						dialog.text = LinkRandPhrase("Beğendin mi?","Peki, ne düşünüyorsun? Her şey yolunda mıydı?","Yani,"+GetSexPhrase(" korsan, her şey"," her şey")+" İyi mi?");
						Link.l1 = RandPhraseSimple(""+GetSexPhrase("Tabii ki, her şey yolunda","Görevlerini gerçekten iyi biliyorsun")+".",""+GetSexPhrase("Her şey yolunda, canım","Biliyor musun, oldukça memnun kaldım")+".");
						Link.l1.go = "exit";
					break;
					case "1":
						dialog.text = LinkRandPhrase("Sözümü tuttum mu peki?","Yani,"+GetSexPhrase(" beni beğendin mi",", beğendin mi")+"?","Umarım, "+GetSexPhrase("sen memnun oldun, çünkü ben çooook memnunum","Sen memnundun, çünkü elimden gelenin en iyisini yaptım")+"...");
						Link.l1 = RandPhraseSimple("Evet, çok beğendim.",""+GetSexPhrase("Harika vakit geçirdik, muhteşem görünüyordun!","Her şey gerçekten harikaydı!")+"");	
						Link.l1.go = "exit";
					break;
					
					case "2":
						dialog.text = RandPhraseSimple("Pekala, işte bu kadar, gitmen gerekiyor.","Senin zamanın doldu,"+GetSexPhrase(" Kaptan,","")+".");
						Link.l1 = RandPhraseSimple("Evet, görüşürüz...","Hoşça kal ve teşekkür ederim...");
						Link.l1.go = "exit";
					break;
				}
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
        case "Horse_AfterSex_2":
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "Bag_BrothelRoom" && !CheckCharacterItem(pchar, "leather_bag"))
			{
				dialog.text = "Peki, burayı nasıl buldun?";
				link.l1 = "Söyle bakalım güzelim, buralarda bir çanta gördün mü hiç?";
				link.l1.go = "EncGirl_GetBag";
			}
			else
			{
				dialog.text = LinkRandPhrase("Bir ara yine uğra...","Hoşça kal. Seni her zaman bekliyor olacağız...","Sizi burada tekrar görmekten memnuniyet duyarız...");
				Link.l1 = "Pekala...";
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
		case "EncGirl_GetBag":
			dialog.text = " Saplı o kahverengi sandık mıydı?";
			link.l1 = "Evet, öyle bir şey...";
			link.l1.go = "EncGirl_GetBag1";	
		break;
		
		case "EncGirl_GetBag1":
			dialog.text = "O sandığın sahibi ortaya çıkmadığı için, hanımefendi onu odasına götürdü.";
			link.l1 = "Teşekkürler, canım. Hoşça kal.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "Bag_BrothelHostess";
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
		
		// --> генератор - "A reason to hurry"
		case "Horse_ReasonToFast_1":
			dialog.text = "O zaman istediğin zaman uğra, seni her zaman görmekten mutluluk duyarım. Sen öyle "+GetSexPhrase("nazik, diğerleri gibi değil","nazik, o kabadayılar gibi değil")+" ne merhaba, ne elveda, çoğu zaman da zarar vermeye çalışıyorlar...";
			link.l1 = "Ne demek istiyorsun?";
			link.l1.go = "Horse_ReasonToFast_2";
		break;
		
		case "Horse_ReasonToFast_2":
			pchar.questTemp.ReasonToFast.speakHorse = true;
			dialog.text = "Senden hemen önce bir başçavuş vardı. Genelde bizi ziyarete gelmez, ama bu sefer bir şeytan onu buraya getirdi. Üstelik beni seçti... Birkaç dakika boyunca başımda homurdandı, sonra bana beceriksiz dedi ve bir koya doğru koşarak gitti. O kadar aceleyle çıktı ki, neredeyse pantolonunu aşağıda unutuyordu, ha-ha-ha...";
			link.l1 = "Bilmiyor musun, "+GetSexPhrase("güzellik","sevgilim")+", erkekler gerçekten kimdir? Karısına geneleve 'denetim' için gittiğini söyledi, metresine ise karısına dönmek için acele ettiğini anlattı, ama aslında tek istediği o koyda devriye gezmekti. "+GetSexPhrase("Ha-ha-ah!..","Ha-ha-ha!")+"";
			link.l1.go = "Horse_ReasonToFast_3";
		break;
		
		case "Horse_ReasonToFast_3":
			NextDiag.TempNode = "Horse_AfterSex_2";			
			ReOpenQuestHeader("ReasonToFast");
			AddQuestRecord("ReasonToFast", "1");
			pchar.questTemp.ReasonToFast = "SpeakHorse";
			pchar.questTemp.ReasonToFast.GuardNation = npchar.nation;
			pchar.questTemp.ReasonToFast.cantSpeakOther = true;
			ReasonToFast_InitVariables();
			string TargetLocation = SelectQuestShoreLocation();
			if(TargetLocation != "")
			{ 
				Locations[FindLocation(TargetLocation)].DisableEncounters = true;
				LAi_LocationDisableOfficersGen(TargetLocation, true);
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1 = "location";
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1.location = TargetLocation;
				pchar.quest.ReasonToFast_MeetPatrol.function = "ReasonToFast_MeetPatrolShore";
				pchar.questTemp.ReasonToFast.PatrolLocation = TargetLocation;
			}	
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		// <-- генератор "A reason to hurry"
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//поиски кольца мэра
		case "TakeMayorsRing_S1":
			if (CheckAttribute(pchar, "questTemp.different.TakeMayorsRing.item")) //если валяется в итемах
			{
				dialog.text = LinkRandPhrase("Hayır, canım, üzgünüm ama olmaz. Sana seve seve yardım ederdim, ama yapamam.","Hayır, "+GetSexPhrase("yakışıklı","genç hanım")+",   hiçbir yüzük görmedim...","Üzgünüm, ama hayır. Hiçbir yüzük görmedim.");
				link.l1 = "Yazık... Neyse, yine de teşekkür ederim.";
				link.l1.go = "exit";
			}
			else
			{
				if (npchar.id == "HorseGen_"+reload_location_index+"_1")
				{
					dialog.text = "Valinin yüzüğünü mü kastediyorsun?";
					link.l1 = "Aynen öyle, canım!";
					link.l1.go = "TakeMayorsRing_S2";
				}
				else
				{
					dialog.text = LinkRandPhrase("Hayır, canım, üzgünüm ama hayır. Sana seve seve yardım ederdim – ama yapamam.","Hayır, "+GetSexPhrase("yakışıklı","genç hanım")+", hiçbir yüzük görmedim...","Üzgünüm, ama hayır. Hiçbir yüzük görmedim.");
					link.l1 = "Yazık... Neyse, yine de teşekkürler.";
					link.l1.go = "exit";
				}
			}
		break;

		case "TakeMayorsRing_S2":
			dialog.text = "Üzgünüm, ama yüzük bana hediye olarak verildi, bu yüzden geri vermek zorunda değilim.";
			link.l1 = "Bir hediye mi?! Ve bunu sana kim verdi?";
			link.l1.go = "TakeMayorsRing_S3";
		break;
		
		case "TakeMayorsRing_S3":
			dialog.text = "Elbette, bizzat vali!";
			link.l1 = "Ama o... en azından biraz sarhoştu. Hiçbir şeyi hatırlamıyor.";
			link.l1.go = "TakeMayorsRing_S4";
		break;
		
		case "TakeMayorsRing_S4":
			dialog.text = "Ve bunun benimle ne ilgisi var? Sarhoşsa, bu onun sorunu, benim değil!";
			link.l1 = "Onunla gerçekten kavga etmen gerekiyor mu? Bu bir alyans ve sen de bunu biliyorsun... Hadi geri ver, böyle küçük bir şey için sorun çıkarmaya değmez.";
			link.l1.go = "TakeMayorsRing_S5";
		break;
		
		case "TakeMayorsRing_S5":
			if (rand(1) && sti(pchar.money)>5000)
			{
				dialog.text = "Pekâlâ, yüzüğü geri vereceğim, ama bana beş bin peso ödeyeceksin.";
				link.l1 = "Pekâlâ, al paranı ve bana yüzüğü ver.";
				link.l1.go = "TakeMayorsRing_S6";
			}
			else
			{
				dialog.text = "Eh, peki. Bırak onun olsun!";
				link.l1 = "Kesinlikle öyle, canım!";
				link.l1.go = "exit";
				GiveItem2Character(pchar, "MayorsRing");
				pchar.questTemp.different.TakeMayorsRing = "HorseTakenRing";
				AddQuestRecord("SeekMayorsRing", "3");
				AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
			}
		break;
		
		case "TakeMayorsRing_S6":
			dialog.text = "Buyurun...";
			link.l1 = "Pekâlâ, o zaman. Yardımın için teşekkürler, canım.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -5000);
			GiveItem2Character(pchar, "MayorsRing");
			pchar.questTemp.different.TakeMayorsRing = "HorseTakenRingMoney";
			AddQuestRecord("SeekMayorsRing", "2");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
		break;
		
		//Jason --> Заносчивый аристократ
		case "Badboy":
			pchar.GenQuest.Badboy.Brothel.City = npchar.city; //город квестодателя
			//log_info(pchar.GenQuest.Badboy.Brothel.City); // patch-6
			pchar.GenQuest.Badboy.Brothel.nation = npchar.nation;
			pchar.GenQuest.Badboy.Brothel.Name = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "Bakın, bizim bir baş belası müşterimiz var - "+pchar.GenQuest.Badboy.Brothel.Name+"Ve her geldiğinde gerçekten de bizi sinir ediyor! Önce meyhanede sarhoş oluyor, sonra buraya geliyor, bir kızla takılıyor ve ortalığı birbirine katıyor.\nEn kötüsü de, soylu bir aileden geliyor olması! Valimizin uzak bir akrabası, bu yüzden tüm bu taşkınlıklarına katlanmak zorunda kalıyoruz. Belki sen o genç, arsız adamı... yani... biraz yatıştırabilirsin... böylece artık mekanımı ziyaret etmeyi bırakır?";
			link.l1 = "Valinin akrabası mı dediniz? Hmmm... Yetkililerle karşı karşıya gelmek istemem. Gerçekten üzgünüm.";
			link.l1.go = "exit";
			link.l2 = "Bunu ayarlayabilirim sanırım. Söylesene, o serseriyi nerede bulabilirim?";
			link.l2.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "Bu saatlerde, genellikle çoktan meyhanede olur. Orada sarhoş olur, sonra da ziyarete gelir.";
			link.l1 = "Anladım. Muhtemelen onu orada göreceğim.";
			link.l1.go = "exit";
			//создаем дебошира
			int iRank, iType, b;
			string sBlade, sPistol;
			if (sti(pchar.rank) < 6) iType = 0;
			if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 16) iType = 1;
			if (sti(pchar.rank) >= 16) iType = 2;
			switch (iType)
			{
				case 0:
					iRank = 6;
					sBlade = "blade_12";
					sPistol = "pistol1";
					b = 25;
				break;
				case 1:
					iRank = sti(pchar.rank)+10;
					sBlade = "blade_09";
					sPistol = "pistol1";
					b = 65;
				break;
				case 2:
					iRank = sti(pchar.rank)+5;
					sBlade = "blade_14";
					sPistol = "pistol1";
					b = 40;
				break;
			}
			sld = GetCharacter(NPC_GenerateCharacter("Badboy", "citiz_"+(7+rand(1)), "man", "man", iRank, HOLLAND, -1, true, "citizen"));
			FantomMakeCoolFighter(sld, iRank, b, b, sBlade, sPistol, "bullet", makeint(iRank*5));
			sld.name = pchar.GenQuest.Badboy.Brothel.Name;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Badboy";
			sld.greeting = "noble_male"; // patch-6
			LAi_SetLoginTime(sld, 15, 22);
			LAi_SetSitType(sld);
			FreeSitLocator(pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit", "sit1");
			pchar.GenQuest.Badboy.Brothel.Type = iType; //запомним тип
			pchar.GenQuest.Badboy.Brothel = "true";
		break;
		
		case "Badboy_complete":
			dialog.text = "Ah, sen gerçek bir adamsın, değil mi? Sana her zaman güvenebileceğimi biliyordum.";
			link.l1 = "Böylesine hoş bir hanımefendiye ve onun... koruması altındakilere her zaman yardımcı olmaktan mutluluk duyarım.";
			link.l1.go = "Badboy_complete_1";
		break;
		
		case "Badboy_complete_1":
			dialog.text = "Sen sadece cesur değil, aynı zamanda çok da centilmen birisin. Sana özel bir şekilde teşekkür etmek istiyorum – bir kadının bir erkeğe teşekkür edebileceği bir şekilde. Bunu asla unutmayacaksın, söz veriyorum. Yukarı gel, cesur denizci...";
			link.l1 = "...";
			link.l1.go = "Badboy_complete_2";
		break;
		
		case "Badboy_complete_2":
			pchar.questTemp.different.HostessSex.city = pchar.GenQuest.Badboy.Brothel.City;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); 
			DialogExit();
			if (sti(pchar.GenQuest.Badboy.Brothel.Type) != 2)
			{
				DeleteAttribute(pchar, "GenQuest.Badboy");
			}
			else
			{
				pchar.quest.Badboy_Brothel.win_condition.l1 = "location";
				pchar.quest.Badboy_Brothel.win_condition.l1.location = pchar.GenQuest.Badboy.Brothel.City +"_town";
				pchar.quest.Badboy_Brothel.function = "Badboy_friends";
				DeleteAttribute(pchar, "GenQuest.Badboy.Continue"); // patch-6
			}
			SaveCurrentQuestDateParam("questTemp.Badboy");
			if (!CheckAttribute(pchar, "questTemp.RomNaTroih"))
			{
				pchar.questTemp.RomNaTroih = true;
			}
		break;
		// <-- Заносчивый аристократ
		
		//Португалец
		case "Portugal":
			dialog.text = "Bana borcu olan bir adam var... Nasıl desem bilemiyorum...";
			link.l1 = "Kelimeye gerek yok! Onu bulup, tek bir bakışın için son kuruşuna kadar sarsacağım! Sadece adını söyle bana!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Hayır, hayır, beni yanlış anladınız Kaptan! Bu adama... ona kötü bir şey yapmayın. Sadece borçlarını hatırlatın. Adı Hugo Avendell, ve sanırım onu en ucuz içkinin satıldığı yerde bulabilirsiniz. Allah aşkına, ona karşı güç kullanmayın!\nSadece deyin ki... borcunu ödeyeceğine dair söz verdiğini hatırlatın. Muhafızları işin içine katmak istemiyorum ama subaylar arasında dostlarım var, ona söyleyin ki bekliyorum ve ona tüm saygımla, en geç yarına kadar harekete geçmek zorunda kalacağım. Sadece sözünü hatırlatın.";
			link.l1 = "Sözünüz benim için kanun, hanımefendi. İsteğinizi memnuniyetle yerine getireceğim.";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			sld = InitHugo("Hugo","Avendell");
			FreeSitLocator("Marigo_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, "Marigo_tavern", "sit", "sit_front1");
			AddLandQuestMark(sld, "questmarkmain");
			SetFunctionTimerCondition("Portugal_BeginOver", 0, 0, 2, false);
			pchar.questTemp.Portugal = "begin";
		break;
		
		case "Portugal_exit":
			dialog.text = "Teşekkür ederim, kaptan. Umarım gereken tedbiri gösterir.";
			link.l1 = "Bundan eminim, hanımefendi. Şimdi müsaadenizle ayrılmak isterim.";
			link.l1.go = "exit";
			sld = characterFromId("Avendel");
			sld.lifeday = 0;
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = "Aman Tanrım! Ona korkunç bir şey yaptığını söyleme... Parası yoktu, bunu biliyordum! Sadece aynı küçük kasabada büyüdük, asla muhafızlara gitmezdim! Sadece onu biraz korkutmak istedim... şişenin dibine vurmadan önce kendine gelsin diye!";
			link.l1 = "Hmm... Yine de, işte paran. Hugo için endişelenme, o iyi... En azından ayılırsa iyi olacak.";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "Ah kaptan, anlamıyorsunuz! O, şey... biliyorsunuz, onlara ödül avcısı derler - paralı askerler, korsanları ve haydutları izleyip ortadan kaldırırlar. Ama o, en şanslısı değildi, en hafif tabirle\nÇok uzun zaman önce değil, sonunda her şeyini harcadı, tayfasını ve gemisini kaybetti, o zamandan beri de günlerini kupasının dibinde boğularak geçiriyor. Eski dostluğumuzdan dolayı, arada sırada buraya gelmesine izin veriyorum. Şimdi o kadar... o kadar zavallı ki. Eskiden La Manche kıyısındaki kasabamızın en yakışıklı adamıydı, şimdi haline bakın\nBiliyorum, size bir şeyler vaat etti ve siz de cebinizden para verdiniz! Bu parayı size ben vereceğim, yeter ki ona bir kötülük yapmayın, yalvarırım kaptan!";
			link.l1 = "Pekala, tamam hanımefendi, anladım. Parayı alın, sizin olsun. Arkadaşınıza gelince, ona zarar vermeyeceğime söz veriyorum. Şimdi müsaadenizle ayrılmam gerekiyor, halletmem gereken işlerim var. Ayrıca, böyle güzel bir hanımefendiye yardımcı olmak beni mutlu etti.";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_tavern_7";
			AddLandQuestMark(sld, "questmarkmain");
			pchar.questTemp.Portugal = "AvendelTavern";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
            dialog.text = "Sessiz ol, sesini alçalt... Git, Madame Lolita'dan benimle buluşmasını iste. Sonra yukarı çık, orada rahatça konuşabiliriz. O zamana kadar tek kelime yok... Hey denizci, bana dokunmadan önce Madame'a ödeme yap! (kıkırdar)";
			link.l1 = "Yoldayım, tatlım...";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
           DialogExit();
		   chrDisableReloadToLocation = false;
		   pchar.questTemp.Mtraxx = "jewelry_2";
		break;
		
		case "mtraxx_2":
			pchar.quest.Mtraxx_JewelrySDMOver.over = "yes"; //снять таймер
            dialog.text = "Yok, ben değilim. Sana her şeyi anlatacağım, yeter ki sözümü kesme.";
			link.l1 = "Tamamen kulak kesildim!";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Pekala o zaman. Yaklaşık bir hafta önce, askeri bir gemi Santo Domingo'ya geldi. Ya fırtınada ya da bir çatışmada hasar görmüş, bu yüzden hemen tamire başladılar ve mürettebat kaleye taşındı. Ama kaptanları, tüm boş zamanını burada geçirdi. İki gün boyunca aralıksız içip dinlendi, yanına da kızlarımızdan biri eşlik etti. Mücevheri alan da oydu, hem de bir tane değil. Sürekli bununla övündü – Lolita müşterilerin hediyelerini kendimize saklamamıza izin verir.\nAptal kız, hediyenin gerçek değerini bile bilmiyordu, oysa ben hemen anladım. Sarhoş kaptanın kehribar dolu bir dağdan bahsettiğini anlatınca, hemen Tyrex'e bir mektup gönderdim...";
			link.l1 = "";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "Kaptan bir dahaki sefere geldiğinde her şeyi öyle ayarlamıştım ki, en sevdiği kız başka bir müşteriyle meşguldü ve 'işi' ben aldım. Ondan koordinatları almaya çalıştım ama ne yazık ki başaramadım. Sadece Crassus kadar zengin olacağını ve Eski Dünya'ya döneceğini övünerek anlatıp durdu.\nYer hakkında tek kelime etmedi. Sadece öğrendiğim şey, gemisinin tamir edildiği ve Havana'ya doğru yelken açmak üzere olduğu, orada da doğru yönde bir görev ayarlamaya çalışacağıydı. Sonuçta geminin sahibi o değil.";
			link.l1 = "Yani, şimdi Havana'da mı?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "İki gün önce şafakta denize açıldı. Burada denizci sensin, hesabı sen yap.";
			link.l1 = "Kaptanın adı, gemisinin türü ve adı, başka bir şey?";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            dialog.text = "Ne, beni aptal mı sandın? Adı Esberdo Cabanas, Cantavro'nun kaptanı. Sanırım denizciler ona bir şalopa diyordu.";
			link.l1 = "Ve bildiğin her şey bu mu?";
			link.l1.go = "mtraxx_7";
		break;
		
		case "mtraxx_7":
            dialog.text = "Daha ne istiyorsun? Eminim Havana'ya varmadan ona yetişebilirsin. Ama vakit kaybetme, sanmıyorum ki Küba'dan hazinesine gitmeden önce uzun süre dinlensin, yoksa iş işten geçer. Gerçi, tekrar düşününce, bir iki saat kalabilirsin, sonuçta bunun için para ödedin.";
			link.l1 = "Güzel söyledin, canım. İki saat fazla bir şey değiştirmez...";
			// belamour legendary edition -->
			link.l1.go = "mtraxx_7S";
			link.l2 = "Başka bir zaman, canım. Kendine bir öğle arası vermeyi düşün. Kiliseye git, ya da başka bir şey yap.";
			link.l2.go = "mtraxx_7NS";
			sTotalTemp = npchar.id;
			AddMapQuestMarkCity("Havana", false);
			AddLandQuestMark(characterFromId("Havana_PortMan"), "questmarkmain");
		break;
		
		case "mtraxx_7S":
            DialogExit();
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(23, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
			AddDialogExitQuest("PlaySex_1");
			// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
				{
					AddCharacterHealth(pchar, 10);
					AddCharacterMaxHealth(pchar, 1.0);
				}
				else AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "FencingS", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;
		
		case "mtraxx_7NS":
            DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			AddQuestRecord("Roger_1", "3");
			pchar.questTemp.Mtraxx = "jewelry_3";
			SetFunctionTimerCondition("Mtraxx_JewelryHavanaOver", 0, 0, 7, false); // таймер
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			pchar.quest.mtr_jewelry_havana.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_havana.win_condition.l1.location = "Cuba2";
			pchar.quest.mtr_jewelry_havana.function = "Mtraxx_HavanaInfo";
			DeleteAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor");
			DeleteAttribute(pchar, "questTemp.ZA.Block");
		break;
		// <-- legendary edition
		case "mtraxx_R":
            dialog.text = "O-oh... Ne yazık. Ben de tatil için geldiğini sanmıştım. Kızlarım cesur korsanları çok özlüyor. Peki, söyle bakalım, ne istiyorsun?..";
			link.l1 = "Marcus bana iki gün boyunca senin mekânında muazzam bir eğlence düzenlememi, bütün şarabı içmemi ve her kızla birlikte olmamı söyledi. Ne zaman başlıyoruz?";
			link.l1.go = "mtraxx_R1";
		break;
		
		case "mtraxx_R1":
            dialog.text = "Ah, Charlie Prince, esprinin keskinliği kılıcınla yarışıyor! Az kalsın beni gücendirecektin... Kızlar! Misafirimiz var, hem de özel bir misafir! Şarap ve yemek getirin!";
			if (sti(pchar.money) >= 31000)
			{
				link.l1 = "Buradaki bütün güzel kızları çağırın! Dinleneceğiz ve biraz eğleneceğiz! Yo-ho-ho!..";
				link.l1.go = "mtraxx_R2";
			}
			else
			{
				link.l1 = "Bir dakika bekle, Janette. Senin ve hanımların için altını gemimden almam lazım. Birazdan görüşürüz!";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.Retribution = "brothel_repeat";
				chrDisableReloadToLocation = false;
			}
		break;
		
		case "mtraxx_R2":
			AddMoneyToCharacter(pchar, -30000);
            dialog.text = "Keşke tüm müşterilerimiz senin kadar tatlı, yakışıklı ve cömert olsa... Sana kusursuz bir rahatlık sunacağız. Kızlar!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionInBrothel");
		break;
		// belamour ночной приключенец
		case "NA_Girl":
            dialog.text = "Oo, demek burada bir uzmanımız var, hı hı ... Pekâlâ, tam sana göre bir kızım var. Ama ucuz değildir: "+makeint(pchar.GenQuest.NightAdventure_money)+" peso."; 
			link.l1 = "Anlaştık.";
			link.l1.go = "NA_Girl_1";
		break;
		
		case "NA_Girl_1":
			AddMoneyToCharacter(pchar, -makeint(pchar.GenQuest.NightAdventure_money));
            dialog.text = "Harika, canım. Aşk Rahibesi yukarıda seni bekliyor olacak. Bana güven, pişman olmayacaksın."; 
			link.l1 = "Zaten istemiyorum.";
			link.l1.go = "NA_Girl_2";
		break;
		
		case "NA_Girl_2":
			DialogExit();
			pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhore"; 
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_NobleWhore_7";
		break;
		// <-- приключенец
		
		case "chicken_god":
			dialog.text = "Siz ve lordum Agüeybana için mi? Elbette yaparsınız. On bin tutar, kaptan.";
			if (sti(pchar.money) >= 10000) {
				link.l1 = "Dur, öyle değil!.. Kahretsin! Neyse, al paranı.";
				link.l1.go = "chicken_god_pay";
			} else {
				link.l2 = "Borç alabilir miyim?";
				link.l2.go = "chicken_god_notpay";
			}
		break;
		
		case "chicken_god_pay":
			dialog.text = "Keyfinize bakın, kaptan. Lütfen tekrar açık olduğumuzda uğrayın. Mekanımız, asil kadın ve erkekler için her türlü eğlenceyi sunar.";
			link.l1 = "...";
			link.l1.go = "chicken_god_pay_1";
		break;
		
		case "chicken_god_pay_1":
			dialog.text = "";
			link.l1 = "Hanımefendi "+npchar.name+", en azından burada neler olduğunu açıklayabilir misin? Vali, bir aydır burayı bir yerlinin yönettiğinden haberdar mı? Bir genelevin bir günlüğüne bile kapanmasıyla hiçbir yerleşim ayakta kalamaz, sana bunu söyleyeyim!";
			link.l1.go = "chicken_god_pay_2";
		break;
		
		case "chicken_god_pay_2":
			dialog.text = "Oda sizin, kaptan. Şimdi, müsaadenizle.";
			link.l1 = "Büyüleyici. Hoşça kalın, hanımefendi.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_PayForRoom");
		break;
		
		case "chicken_god_notpay":
			dialog.text = "Neden, Tanrım, neden? Çık git buradan! Git, git, artık dayanamıyorum! Alçak!";
			link.l1 = "Bu iyi geçti.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotPayForRoom");
		break;
		
		//-->> Sinistra Ром на троих
		case "RomNaTroih_1":
			dialog.text = "Mhm... Bunu genelde yapmam... ama senin için riske girmeye hazırım. Şanslı günündesin, Kaptan!";
			link.l1 = "Hadi gidelim!";
			link.l1.go = "exit";
			pchar.RomNaTroih_Shluha = npchar.id;
		break;
		
		case "RomNaTroih_2":
			dialog.text = "Sana kızgınım, Kaptan... Ama yeterince çabalarsan sana merhamet göstereceğim.";
			link.l1 = "Elbette, açalım mı biraz şarap?";
			link.l1.go = "exit";
			Achievment_Set("ach_CL_105");
		break;
		//<<-- Sinistra Ром на троих
	}
}

ref GetFreeHorseRef(string City)
{
	ref rCharacter;
    int storeArray[8];
	int howStore = 0;
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse" && rCharacter.horse == "HorseStay")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return &NullCharacter;
	return &characters[storeArray[rand(howStore-1)]];
}

ref CheckHorsesName(string City, int num)
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[num]);
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			sTemp = GetStrSmallRegister(rCharacter.lastname + " " + rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;			
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
		}
	}
	return &NullCharacter;
}
