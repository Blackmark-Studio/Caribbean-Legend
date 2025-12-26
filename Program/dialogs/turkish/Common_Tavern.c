#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
#include "interface\ship.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Tavern.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	int iTest, iTemp;
	string sTemp;
	string NPCCity = NPChar.City;
    iTest = FindColony(NPChar.City); // город 
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;
	
	if(!CheckAttribute(pchar, "questTemp.TavernVisit."+(NPCCity) )) 
	{
		pchar.questTemp.TavernVisit.(NPCCity) = true;
		pchar.questTemp.TavernVisit.counter = sti(pchar.questTemp.TavernVisit.counter) + 1;
		notification("First Tavern Visit " + XI_ConvertString(NPCCity + "TavernName"), "Drunk");
		AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 10.0);
	}	
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Kasabada alarm verildi, herkes seni arıyor. Ben olsam burada kalmazdım.","Tüm şehir muhafızları seni aramak için kasabayı didik didik ediyor. Ben aptal değilim ve seninle konuşmayacağım!","Kaç, "+GetSexPhrase("dostum","kız")+", askerler seni kıyma haline getirmeden önce..."),LinkRandPhrase("Ne istiyorsun, "+GetSexPhrase("alçak","pislik")+"?! Şehir muhafızları peşinde, fazla uzağa gidemezsin"+GetSexPhrase(", pis kirli korsan!","")+"","Katil, hemen buradan defol! Muhafızlar!","Senden korkmuyorum, "+GetSexPhrase("serseri","fare")+"! Yakında kalemizde asılacaksın, fazla uzağa gidemezsin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, bir alarm benim için asla sorun olmaz...","Beni asla yakalayamazlar."),RandPhraseSimple("Çeneni kapa, "+GetWorkTypeOfMan(npchar,"")+", yoksa dilini koparırım!","Heh, "+GetWorkTypeOfMan(npchar,"")+", ve hepsi orada - korsanları yakalamak için! Sana söylüyorum dostum: sessiz otur, ölmezsin..."));
				link.l1.go = "exit";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("Ve işte sen, alçak! Burada sana rom mu sunuyoruz sanıyorsun? Kesinlikle hayır! Çocuklar! Silah başına! Bu herifi öldürün!","Bir içki ister misin, korsan? Ha! Yok! Şimdi sana gününü göstereceğiz! Çocuklar, kılıçlarınızı çekin!");
				link.l1 = RandPhraseSimple("Ha? Ne?","Dur!");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//Jason, Бремя гасконца
			if(NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
				{
					link.l1 = "Monsieur, iş arıyorum. Bir işiniz var mı?";
					link.l1.go = "Sharlie_rum";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
				{
					link.l1 = "Görevinizi tamamladım. Rom yüklü sandal Le François Körfezi'ne teslim edildi ve adamlarınıza verildi.";
					link.l1.go = "Sharlie_rum_5";
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "crew" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				FreeSitLocator("FortFrance_tavern", "sit7");
				dialog.text = "Bir şey mi istediniz, monsieur?";
				Link.l1 = "Merhaba meyhaneci, gemim için bir mürettebat tutmam gerekiyor. Bu konuda bana yardımcı olabilir misin?";
				Link.l1.go = "Sharlie_crew";
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "skiper" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Yeniden merhaba. Bu sefer ne var, monsieur?";
				Link.l1 = ""+npchar.name+", farkındayım sizi rahatsız ediyorum, ama sadece bir soru daha. Bir seyirciye ihtiyacım var - nerede bulabileceğime dair bir fikriniz var mı?";
				Link.l1.go = "Sharlie_skiper";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
    			dialog.text = "Ne istiyorsunuz, monsieur?";
				Link.l1 = "Birkaç soruma cevap verebilir misiniz diye umuyordum.";
				Link.l1.go = "quests";
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l2 = "Bir oda kiralamak istiyorum.";
					link.l2.go = "room";
				}
				break;
			}			
			//Бремя гасконца
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "tavern" && npchar.city == "Tortuga")
			{
				dialog.text = "Sizi görmek büyük bir mutluluk, efendim! Size nasıl yardımcı olabilirim? Rom, brendi, İskoç viskisi?";
				Link.l1 = "En iyi Fransız şarabınızdan bir şişe ve bir oda anahtarı istiyorum.";
				Link.l1.go = "mtraxx_tortuga";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "room" && npchar.city == "Tortuga")
			{
				dialog.text = "Zaten ödediniz, monsieur, odanız yukarıda.";
				Link.l1 = "Merci.";
				Link.l1.go = "exit";
				break;
			}
			
			// Sinistra - Квест "Длинные тени старых грехов" ==>	
			if (CheckAttribute(pchar, "questTemp.DTSG_BasTerTavern") && npchar.city == "BasTer")
			{
				dialog.text = "Sana nasıl yardımcı olabilirim, Kaptan? Olanlardan sonra muhtemelen bir içki istersin.";
				Link.l1 = "Bu bekleyebilir. Aslında olanları konuşmak istiyorum.";
				Link.l1.go = "DTSG_BasTerTavern_1";
				DelLandQuestMark(npchar);
				break;
			}
			// <== Квест "Длинные тени старых грехов" - Sinistra
			
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Start") && !CheckAttribute(pchar, "questTemp.TPZ_Tavern_1") && npchar.city == "BasTer")
			{
				dialog.text = "Affedersiniz, "+GetAddress_Form(NPChar)+", ama bugün size bir damla içki bile sunamam.";
				Link.l1 = "Ne? Ne biçim meyhanede bir damla rom bile kalmaz? Yoksa tüm stoklarını tüketen büyük bir kutlamayı mı kaçırdım?";
				Link.l1.go = "TPZ_Tavern_1";
				pchar.questTemp.TPZ_Tavern_1 = true;
				DelLandQuestMark(npchar);
				break;
			}
			//<-- Торговля по закону

			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("Mütevazı meyhaneme hoş geldiniz '"+XI_ConvertString(NPChar.City+"TavernName")+"', efendim. Sizi gördüğüme sevindim.","Emrinizdeyim, efendim! Bizim meyhanemizde '"+XI_ConvertString(NPChar.City+"TavernName")+" yeni ziyaretçileri ağırlamaktan her zaman memnuniyet duyarız.","İlk defa mı geldiniz, efendim? Çekinmeyin, burada '"+XI_ConvertString(NPChar.City+"TavernName")+"’ burada her zaman kendini evinde hissedersin!"),LinkRandPhrase("Buyurun, monsieur kaptan. Sizi tanımıyorum, demek ki buraya ilk gelişiniz."+XI_ConvertString(NPChar.City+"TavernName")+"'.","Sizi daha önce hiç görmedim, monsieur. Tanışalım: Ben "+GetFullName(npchar)+",   '   hanın   sahibi "+XI_ConvertString(NPChar.City+"TavernName")+"'.","Yeni misafirimiz, Mösyö Kaptan, hoş geldiniz! Benim meyhanemde '"+XI_ConvertString(NPChar.City+"TavernName")+"İlk içki her zaman bizden! Buranın sahibi benim, "+GetFullName(npchar)+", sizi karşılıyor."),LinkRandPhrase("Señor Kaptan! Tavernamıza hoş geldiniz '"+XI_ConvertString(NPChar.City+"TavernName")+"'!","Ah, ne parlak bir hidalgo taverna'mızı ziyaret etmiş '"+XI_ConvertString(NPChar.City+"TavernName")+"'! Buraya ilk kez mi geliyorsunuz, efendim?","Buenos días, señor! Ben "+GetFullName(npchar)+",   '  nın mütevazı sahibi"+XI_ConvertString(NPChar.City+"TavernName")+"', burada sizi ağırlamaktan memnuniyet duyuyoruz!"),LinkRandPhrase("Merhaba, mynheer kaptan. Ben bu meyhanenin sahibiyim '"+XI_ConvertString(NPChar.City+"TavernName")+"'. Bizde ilk kez mi kalıyorsunuz?","İyi günler, efendim. Tavernamıza hoş geldiniz '"+XI_ConvertString(NPChar.City+"TavernName")+"'.","Sizi görmek çok güzel, mynheer kaptan! Kendi meyhanemiz '"+XI_ConvertString(NPChar.City+"TavernName")+"'  sizi selamlıyor! Rom, şarap, ya da izin verirseniz, sizi baştan çıkaracak yeni bir Hollanda içkimiz var: cin?"));
				Link.l1 = LinkRandPhrase("Ne hoş bir yeriniz varmış... Kendimi tanıtmama izin verin - "+GetFullName(pchar)+", sizinle tanışmak bir zevk.",""+GetFullName(pchar)+", sizinle tanışmak bir zevk. Peki, bana ne sunabilirsiniz?","Benim adım "+GetFullName(pchar)+" ve bu limana yeniyim. Söylesene, bu meyhanenin en meşhur olduğu şey nedir?");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_tavern")
				{
					dialog.text = "Selam, Rumba! Bir yolculuktan mı döndün, yoksa yeni bir maceraya mı çıkıyorsun?";
					link.l1 = "Merhaba, "+npchar.name+". Sadece uğramak istedim.";
					Link.l1.go = "Helen_meeting";
					NPChar.quest.meeting = "1";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				// Квестовый генератор священника. Квест №1. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
		        {
		            if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToBarmen"))
		            {
		            	iTemp = sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen);
		            	dialog.Text = "Peki, kaptan, bana getirdin mi "+FindRussianMoneyString(iTemp)+".";
		            	if(sti(PChar.Money) >= iTemp)
		            	{
							link.l1 = "Evet, buldum. İşte burada...";
							link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
						}
						else
						{
							link.l1 = "Hayır, henüz yapmadım...";
							link.l1.go = "exit";
						}
		            }
		            else
		            {
		            	dialog.Text = "Ne isterdiniz, iyi  "+GetSexPhrase("efendim","hanımefendi")+"?";
						link.l1 = "Şuradaki masada oturan arkadaşıma bir şişe rom.";
						link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
					}
					break;
				}
				// <-- Квестовый генератор священника. Квест №1.
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh, değerli misafirler! Hey, sen - çekil şöyle ve cesur bir kaptana yer aç! Hadi çabuk ol, yoksa seni dışarı atarım, haha!","Yüce Tanrı aşkına! Bu da ne "+GetFullName(pchar)+"! En kaliteli şaraplardan yeni bir parti aldım, lütfen buyurun!","Oh, "+GetAddress_Form(NPChar)+", bir sorun mu yaşıyorsunuz? Size yardımcı olmama izin verin. Bu şişe bizden olsun. Bana güvenin, buraların en iyi şarabıdır..."),LinkRandPhrase("Ah, Kaptan geldi "+GetFullName(pchar)+"! Hey, sen! İyi kaptana biraz saygı göster! Burası ahır değil! Lütfen beni affedin kaptan, belli ki anneleri onlara hiç terbiye öğretmemiş.","Pekala, pekala, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Uzun bir gece bizi bekliyor, haha! Kızlar, en güzel elbiselerinizi giyin!","İyi günler, "+GetFullName(pchar)+",   sizi gördüğüme çok sevindim! Lütfen, efendim, bir ricam var. Yeni masalar aldım, bu yüzden bu gece kavga çıkmasın."),LinkRandPhrase("Merhaba, kaptan. Rahatınıza bakın, ama unutmayın ki, Kaptan Sharp bile benim mekânımda nezaket kurallarına uyar.","O-ho-ho! Bakın kim gelmiş! Bu "+GetFullName(pchar)+" kendisi! Ve yokluğunda sıkılmaya başlamıştık! Ben yeni bir fıçı rom açarken, sen de arkadaşlara bir maceranı anlatsan nasıl olur, kaptan?","O-ho-ho! Bu "+GetFullName(pchar)+" kendin! Umarım yine o büyük maceralarını anlatarak müşterilerimi açık denizlere çekmeye kalkmazsın?")),LinkRandPhrase(LinkRandPhrase(""+GetFullName(pchar)+"! Bu eski deniz kurdu sizi mekanında görmekten her zaman mutluluk duyar! Lütfen, efendim, buyurun oturun, kızlar sizinle ilgilenecek!","Lütfen, kaptan, buyurun rahatınıza bakın! En sevdiğim misafiri ağırlamak her zaman mutluluk. Ne içersiniz?","Seni tekrar gördüğüme sevindim, "+GetFullName(pchar)+"! Kendi masanızda mı oturmak istersiniz? Yoksa barda mı oturmayı tercih edersiniz?"),LinkRandPhrase("İyi günler, kaptan. Havada bir serinlik var, size yeni yaptığım nefis sıcak şarap ikram edeyim, benden olsun!","Merhaba, Kaptan "+GetFullName(pchar)+"! Yine ziyarete geldiğine sevindim. Ne isterdin?","Seni yanımda görmekten mutluyum, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Mütevazı işletmemizi tercih ettiğiniz için memnun oldum! Sizi memnun etmek için elimizden geleni yapıyoruz."),LinkRandPhrase("Kaptan! Hoş geldiniz, hoş geldiniz! Kral Louis'nin bile layık göreceği muhteşem bir d'Anjou'm var, üstelik onu özellikle sizin için sakladım!",""+GetFullName(pchar)+"! Geldiğine çok sevindim. İstersem şu deniz farelerini hemen kovabilirim, yoksa kalmalarını mı istersin? İnan bana, senin için bütün meyhaneyi boşaltmaktan memnuniyet duyarım!","Aman Tanrım, işte Kaptan "+GetFullName(pchar)+"! Hey, cilveler - kaptanın masasına en güzel masa örtüsünü getirin!")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Ah, demek burada hâlâ hatırlanıyorum... Haydi, bardağımı doldur dostum, ben de etrafa bir göz atayım...","Sakin ol dostum, bugün keyfim yerinde. Romla başlayalım, ne dersin?..."),RandPhraseSimple("Ah... burada olmamdan pek memnun değil misin yoksa? Umarım yanlış duymuşumdur, ha!","Selam. Umarım şarabın, selamlamandan daha iyidir. Yoksa, kızabilirim, biliyorsun...")),RandPhraseSimple(RandPhraseSimple("Seni ziyaret etmek her zaman keyif, dostum. Şu deniz kurdunu ısıtacak neyin var?","Ah, işletmeniz her geçen gün daha da güzelleşiyor! Buraya gelmek her zaman bir zevk..."),RandPhraseSimple("Beni unutmamışsın, eski bir gezgini? Gururlandım doğrusu, dostum.","Eski bir dostu tekrar görmek güzel... Hâlâ biraz romun kaldı mı?")));
				Link.l1.go = "step_node";
			}
			break;
				
			case "step_node":
				dialog.Text = LinkRandPhrase("Dinliyorum, kaptan.","Meyhanem '"+XI_ConvertString(NPChar.City+"TavernName")+" emrinizdeyim, Kaptan!","Dinliyorum, Kaptan! Bugün ne arzu edersiniz?");
				Link.l1 = "Adada denizde şansını denemeye hazır gençler var mı?";
				Link.l1.go = "crew hire";
				Link.l2 = "Birkaç soruma cevap verebilir misiniz diye ummuştum.";
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "Mali konuları konuşmak istiyorum.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
		            	{
					link.l10 = LinkRandPhrase("Bana kilisedeki son soygun hakkında bir şey söyleyebilir misin?","Son zamanlarda kilisede yaşanan soygun hakkında ne biliyorsun?","Kilisede yakın zamanda yaşanan soygun hakkında bir şey duydun mu?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Bu kolonide neredeyse her şeyi bildiğin söyleniyor. Satın almak istiyorum "+pchar.GenQuest.Device.Shipyarder.Type+", ve bana kasabanızda satıldığı söylendi. Birisi sokak pazarında satıyormuş. Bunun hakkında bana bir şey söyleyebilir misiniz?";
					link.l16.go = "Device_Tavern";
				}
				// <-- генератор Неудачливый вор
			
				//Jason --> генератор Место под солнцем
				if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
				{
					link.l17 = "   Bir tefeci arıyorum, adı   "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Onu nerede bulabilirim?";
					link.l17.go = "Sunplace_Tavern";
				}
				// <-- генератор Место под солнцем
			
				// --> Голландский гамбит
				if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Merhaba, "+npchar.name+". Jacob van Berg'i bulmam lazım - nerede? Onu meyhanende göremiyorum...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Merhaba, "+npchar.name+". Fernando Rodriguez adında bir caballero arıyorum. Kasabanıza geldi mi?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				// <-- Голландский гамбит
			
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "Kazancımı almaya geldim, benim için sakladığın parayı. "+npchar.name+".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
			
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "Ben de merak ediyordum,   şu isimde bir adamı nerede bulabilirim acaba: "+pchar.GenQuest.Marginpassenger.q2Name+"? O senin kasabanda yaşıyor.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l3 = pcharrepphrase("Bedava bir odan var mı, dostum?","Boş bir odanız var mı? Bir süre burada kalmak istiyorum.");
					link.l3.go = "room";
				}
				Link.l4 = "Ne yazık ki, ben zaten gidiyorum, "+NPChar.name+". Görüşürüz.";
				Link.l4.go = "exit";
		break;
		
		case "Helen_meeting":
			dialog.Text = "Ah, buyur, buyur içeri. Burada her zaman hoş karşılanırsın.";
			link.l1 = "Evet, teşekkür ederim. Seni görmek güzeldi. Hoşça kal.";
			link.l1.go = "exit";
			Link.l2 = "Yeni adamlara ihtiyacım var. Sadece işlerini bildiklerinden emin ol, tamam mı?";
			Link.l2.go = "crew hire";
			link.l3 = "Karada dinlenip düşüncelerimi toparlamak isterim, ama annem evde koşturup dururken olmaz.";
			link.l3.go = "Helen_room";
			Link.l4 = "Sana bir şey sorabilir miyim? ";
			Link.l4.go = "quests";
			link.l5 = " Sizinle konuşmam gereken bir mesele var, "+NPChar.name+".";
			link.l5.go = "Helen_rumours_tavern";
		break;
		
		case "Meeting":
			// Квестовый генератор священника. Квест №1. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
	        {
	            dialog.Text = "Ne arzu edersiniz, nazik "+GetSexPhrase("efendim","hanımefendi")+"?";
				link.l1 = "Şuradaki masada oturan dostuma bir şişe rom.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
				break;
			}
			// <-- Квестовый генератор священника. Квест №1.
			dialog.Text = LinkRandPhrase("Dinliyorum, kaptan.","Sana ne sunabilirim, kaptan?","Peki, kaptan, ne olacak?");
			Link.l1 = "Bir mürettebata ihtiyacım var, "+NPChar.name+".";
			Link.l1.go = "crew hire";
			Link.l2 = NPChar.name+", hadi konuşalım...";
			Link.l2.go = "int_quests";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l21 = "Mali konuları görüşmek istiyorum.";
				link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
			}
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	        {
				link.l10 = LinkRandPhrase("Bana kilisedeki son soygun hakkında bir şey söyleyebilir misin?","Son zamanlarda kilisede yaşanan soygun hakkında ne biliyorsun?","Kilisede yakın zamanda yaşanan soygun hakkında bir şey duydun mu?");
				link.l10.go = "Tavern_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Bu kolonide neredeyse her şeyi bildiğin söyleniyor. Satın almak istiyorum "+pchar.GenQuest.Device.Shipyarder.Type+", ve bana kasabanızda satıldığı söylendi. Biri sokaklarda satıyormuş. Bu konuda bana bir şey söyleyebilir misiniz?";
				link.l16.go = "Device_Tavern";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
			{
   				link.l17 = "Bana  şu isimdeki bir dolandırıcıdan bahset "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Onu nerede bulabilirim?";
				link.l17.go = "Sunplace_Tavern";
			}
			// <-- генератор Место под солнцем
			
			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Merhaba, "+npchar.name+". Jacob van Berg'i bulmam gerekiyor - nerede? Onu meyhanende göremiyorum...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Merhaba, "+npchar.name+". Fernando Rodriguez adında bir caballero arıyorum. Şehrinize geldi mi?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				//<-- Голландский гамбит
				
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "Kazancımı almaya geldim, benim için sakladığın parayı istiyorum. "+npchar.name+".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "Ben de   adında bir adamı nerede bulabileceğimi merak ediyordum "+pchar.GenQuest.Marginpassenger.q2Name+"? O senin kasabanda yaşıyor.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
			if(!CheckAttribute(pchar,"questTemp.TimeLock"))
			{
				link.l3 = pcharrepphrase("Bedava bir odan var mı, dostum?","Boş bir odanız var mı? Bir süre burada kalmak istiyorum.");
				link.l3.go = "room";
			}
			Link.l4 = "Sanırım daha sonra geri geleceğim.";
			Link.l4.go = "exit";
		break;
		
		case "crew hire":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			ok = sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok;
			
			if (!ok)
			{
				Dialog.text = "Peki, denizcilere neden ihtiyacınız var kaptan? Limanda geminizi göremiyorum.";
				link.l1 = RandPhraseSimple("Kesinlikle... Yanlış yere demirlemiştim.","Limanı girmeyi unuttum...");
				link.l1.go = "exit";
				break;
			}
			
            if (makeint(environment.time) > 22.0 || makeint(environment.time) < 7.0)
			{
				Dialog.text = "Genellikle denizci olmak isteyen çok adam bulunur, ama şu anda çok geç - sabah olunca gelmeye başlarlar. Belki bir oda kiralayıp onları beklemek istersiniz?";
				link.l1 = "Peki. Boş odanız var mı?";
				link.l1.go = "room";
				link.l2 = "Şu anda bir odayla ilgilenmiyorum. Görüşürüz.";
				link.l2.go = "exit";
			}
			else
			{
                if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
                {
                    Dialog.text = "Burada aranan suçlulara hizmet ettiğimizi mi sanıyorsun? Muhafızları çağırmadığıma şükret.";
					link.l1 = "Teşekkürler.";
					link.l1.go = "exit";
                }
                else
                {
					if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
					{
						Dialog.text = "Kaptan, bugün handa tek bir canlı yok. Gitmek isteyen herkes Kaptan Blackwood'la gitti.";
						link.l1 = "Ne yazık!";
						link.l1.go = "exit";
						break;
					}
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 3 && GetCrewQuantity(rColony) == 0)
					{
						Dialog.text = "Ah, üzgünüm kaptan, biraz geç kaldınız. Denize açılmak isteyen herkes cesur bir kaptanla çoktan yola çıktı "+GetFullName(CharacterFromID(NPChar.CrewHired.PGGId))+".";
						link.l1 = "Ne yazık!";
						link.l1.go = "exit_crew";
					}
					else
					{						
						if(bPartitionSet)
						{		
							if(GetPartitionAmount("CrewPayment") > 0)
							{
								if(IsEquipCharacterByArtefact(pchar, "totem_07"))
								{
									DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
									NextDiag.CurrentNode =  NextDiag.TempNode;
									DialogExit();
									LaunchHireCrew();							
								}
								else
								{
									dialog.text = "Kaptan, insanlar senin biraz cimri olduğunu söylüyor. Burada kimse tayfana katılmak istemiyor.";
									link.l1 = "Anladım...";
									link.l1.go = "exit";
								}
							}
							else
							{
								DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
								NextDiag.CurrentNode =  NextDiag.TempNode;
								DialogExit();
								LaunchHireCrew();	
							}
						}	
						else
						{
							DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
							NextDiag.CurrentNode =  NextDiag.TempNode;
							DialogExit();
							LaunchHireCrew();							
						}						
					}
				}
			}
		break;
		
		case "exit_crew" :
			DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
			NextDiag.CurrentNode =  NextDiag.TempNode;
			DialogExit();
			LaunchHireCrew();
		break;
	////////////////////////////////////////////////////////=============================================///////////////////////////////////////////////////////	
        case "int_quests":
			dialog.text = "Tamamen dinliyorum.";
			//link.l1 = "Bir iş arıyorum. Bana yardımcı olabilir misiniz?";
			//link.l1.go = "work";
			//homo 15/06/06 слухи
			link.l2 = LinkRandPhrase("Bana en son haberleri anlatabilir misin?","Bu topraklarda neler oluyor?","Karada neler var, ne yok?");
			link.l2.go = "rumours_tavern";
			//homo
			link.l3 = "Başka bir iş için geldim.";
			link.l3.go = "quests";
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "EncGirlFack_fighted")
				{
					link.l5 = " Nerede bulabileceğimi biliyor musun "+pchar.GenQuest.EncGirl.name+"?";
					link.l5.go = "EncGirl_1";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					link.l6 = "Bana nerede arayabileceğimi söyleyebilir misin "+pchar.GenQuest.EncGirl.sLoverId+"?";
					link.l6.go = "EncGirl_3";
				}
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "tavern_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l7 = "Merhaba, oğlunuzun davetiyle geldim."; 
					link.l7.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.City && CheckAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern"))
			{
				if(pchar.GenQuest.CaptainComission.variant == "A0")
				{												
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Ee, gördün mü  "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = "Bana   nerede aramam gerektiğini söyleyebilir misin  "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_1";
					}
				}	

				if(pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					link.l9 = "Bir devriye kaptanını nerede bulabileceğimi biliyor musun "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"?";
					link.l9.go = "CaptainComission_Tavern7";					
				}				
				if(pchar.GenQuest.CaptainComission.variant == "A3" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Peki, gördün mü "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.CanoneerName,NAME_NOM)+"?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{					
						link.l9 = "Devriye kaptanı hakkında bir şey biliyor musun "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_Tavern1";
						if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
						{
							pchar.GenQuest.CaptainComission.GetRumour = true;
							SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
						}	
					}	
				}					
			}
			if(CheckAttribute(pchar,"GenQuest.Hold_GenQuest") && NPChar.city == pchar.GenQuest.Hold_GenQuest.City && pchar.GenQuest.Hold_GenQuest.Speak_Tavern == false )
			{
				link.l10 = "Bana   adında   bir adamı   nerede bulabileceğimi   söyleyebilir misiniz "+pchar.GenQuest.Hold_GenQuest.Name+"?";
				link.l10.go = "hold_genquest1";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakTavern") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l11 = "Buradan çok uzakta olmayan bir yerde bazı gemi belgelerine rastladım....";
				link.l11.go = "ShipLetters_4";			
			}

			// Jason --> квест губера на поиск дезертира
			if(CheckAttribute(pchar, "GenQuest.FindFugitive") && pchar.GenQuest.FindFugitive != "Late" && sti(NPChar.nation) == PIRATE)
			{
				link.l12 = "Dinle, eski bir arkadaşımı arıyorum, "+pchar.GenQuest.FindFugitive.Name+" onun adı. Bir başka kaptan, senin yerleşimine doğru gittiğini söyledi. Onunla karşılaştın mı, tesadüfen?";
				link.l12.go = "FindFugitiveTav";
			}
			//<-- поиск дезертира

			link.l15 = "Hayır, teşekkürler.";
			link.l15.go = "exit";
		break;
		
		case "hold_genquest1":
			switch(sti(pchar.GenQuest.Hold_GenQuest.TavernVariant))
			{
				case 0:
					dialog.text = LinkRandPhrase("Ne dedin? "+pchar.GenQuest.Hold_GenQuest.Name+"? Hmm... Hiç duymadım onu.","Bu kişinin bizim kasabadan olduğuna emin misin? Böyle birini hiç duymadım.","Bizim küçük kolonimizde öyle biri hiç olmadı. Burada geçirdiğim onca zamanda adını bile duymadım.");
					link.l1 = "Emin misin?";
					link.l1.go = "hold_genquest2";					
				break;
				
				case 1: 
					switch (hrand(3))
					{
						case 0:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
							pchar.GenQuest.Hold_GenQuest.found = "church";
						break;
						case 1:
							if (npchar.city != "Panama")
							{
							pchar.GenQuest.Hold_GenQuest.foundStr = "the shipyard";						
							pchar.GenQuest.Hold_GenQuest.found = "shipyard";
							}
							else
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
								pchar.GenQuest.Hold_GenQuest.found = "church";
							}
						break;
						case 2:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the usurer";												
							pchar.GenQuest.Hold_GenQuest.found = "bank";
						break;
						case 3:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the shop";						
							pchar.GenQuest.Hold_GenQuest.found = "store";
						break;
					} 
					dialog.text = "Bir göz at "+pchar.GenQuest.Hold_GenQuest.foundStr+", onu orada sık sık bulabilirsin.";
					link.l1 = "Teşekkür ederim, aynen öyle yapacağım.";
					link.l1.go = "hold_genquest3";				
				break;
				
				case 2:
					dialog.text = LinkRandPhrase(RandPhraseSimple("Ne dedin? "+pchar.GenQuest.Hold_GenQuest.Name+"? Hmm... Hiç duymadım. Emin misin, bizim köyden miymiş? Böyle birini hiç duymadım.","Heh-heh... Şimdi artık onu nerede arayacağını yalnızca Tanrı bilir - cehennemde mi, cennette mi. Bir yıldan fazla oldu öleli, ama hâlâ onu soran var... Zavallı adamın huzuru yok..."),RandPhraseSimple("Onu orada bulamazsınız - en azından yaşayanlar arasında. Çok da uzun zaman önce değil, sarı hummadan öldü... Tanrı ruhunu şad etsin... Ne kadar da güçlü bir adamdı! Gençliğinde büyük bir maceraperestti! Ama ölüm kapını çaldığında, yapacak pek bir şey kalmıyor...","Onu mu özlediniz? Buralardan çoktan ayrıldı. Kimse nereye gittiğini bilmiyor — belki Kuzey Amerika kolonilerine, belki de Avrupa'ya döndü. Eşyalarını topladı ve sessizce ortadan kayboldu."),"Ah, onu mu arıyorsun "+pchar.GenQuest.Hold_GenQuest.Name+" kim zengin olup New England'da kendine bir ev aldı? Biliyor musun, ona zamanında veresiye rom sattığım günler oldu - hâlâ borcunu ödemedi. İnsanlar ne kadar nankör, biliyor musun.");
					link.l1 = "Anladım. Yine de teşekkür ederim.";	
					link.l1.go = "hold_genquest4";
				break;
				
				case 3:
					dialog.text = "E, onu başka nerede arayacaksın ki, meyhaneden başka? Oranın müdavimidir – günahlarını şarapta boğar, heh-heh. Biraz sonra tekrar gel – eğer uğrarsa, seni beklemesini söylerim.";	
					link.l1 = "Teşekkür ederim, öyle yapacağım.";
					link.l1.go = "hold_genquest5";
				break;
			}
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;
		break;
		
		case "hold_genquest2":
			dialog.text = "Buradaki herkesi şahsen tanıyorsam nasıl emin olmayabilirim ki. Bu handa ilk yılım değil, uzun zamandır işletiyorum burayı. "+"Hepsini her türlü halde gördüm. Bazen bir kadın kocasını almaya gelirdi, bazen de kendileri çıkıp giderdi, ama bazen de onları dışarı atmak zorunda kalırdım. 'Emin miyim?!' Tabii ki eminim!";
			link.l1 = "Pekala, yine de teşekkürler...";	
			link.l1.go = "exit";
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			AddQuestRecord("HoldQuest", "7");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "hold_genquest3":
			Hold_GenQuest_GenerateChar();		
			AddQuestRecord("HoldQuest", "8");
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Gen")); 			
			AddQuestUserData("HoldQuest", "sFoundChar", pchar.GenQuest.Hold_GenQuest.foundStr);
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			SetFunctionTimerConditionParam("Hold_GenQuest_FindCharTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
		break;
		
		case "hold_genquest4":
			AddQuestRecord("HoldQuest", "13");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");			
			DialogExit();
		break;
		
		case "hold_genquest5":
			SetFunctionTimerConditionParam("Hold_GenQuest_GetMapTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_GenerateMapChar");			
		break;
		
		case "CaptainComission_1":
			dialog.text = LinkRandPhrase("Buraya sık sık gelir, ama şu anda burada değil. Ara sıra tekrar uğra - eğer gelirse, burada seni beklemesini söylerim.","Buraya sık sık gelir. Sonra tekrar gelirseniz, onu burada bulacağınızdan emin olabilirsiniz.","Zaman zaman tekrar uğra - buraya sık sık gelir. Onu aradığını kendisine ileteceğim.");
			link.l1 = "Teşekkürler, sonra tekrar geleceğim...";
			link.l1.go = "CaptainComission_2";
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
		break;
		
		case "CaptainComission_2":
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_ExitFromTavern.function = "CaptainComission_GenerateChar";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_3":
			dialog.text = "Zaten buraya geldi, o yüzden bir yerlerde olmalı...";
			link.l1 = "Teşekkürler.";
			link.l1.go = "exit";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
		break;
		
		case "CaptainComission_Tavern1":
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
			dialog.text = "Onu bilmeyen var mı? Bütün yerleşim yeri günlerdir ondan bahsediyor zaten.";
			link.l1 = "Bana biraz daha anlatır mısın?";
			link.l1.go = "CaptainComission_Tavern2";
		break;
		
		case "CaptainComission_Tavern2":
			dialog.text = "Biraz. Kaptan idam edildi, bazı tayfası da aynı akıbete uğradı. Geri kalanlar ise rütbe ve mevkilerinden mahrum bırakılıp Karayipler'e dağıtıldı... Peki neden? Hakime göre, devriye sırasında bir korsan gemisini batırıp ganimeti kendine saklamış."+"Bakın, durum şu: Ne bu geminin sahibi ne de mallar bulunabildi ... yerel koyları ve girintileri didik didik arıyorlar, ama nafile.";
			link.l1 = "Ne, mürettebattan hiçbiri gizli yerin yerini söylemedi mi?";	
			link.l1.go = "CaptainComission_Tavern3";	
		break;
		
		case "CaptainComission_Tavern3":
			dialog.text = "Bir tekini bile söylemedim! İşkence altında bile! Hâlâ valinin o iftiraya bu kadar kolay inanmasını anlayamıyorum. Kaptan "+pchar.GenQuest.CaptainComission.Name+" iyi bir itibara sahipti ve mürettebatı iyi eğitimli ve disiplinliydi, bu da herhangi bir amiralin imreneceği bir şeydi.";
			link.l1 = "Ve hayatta kalan mürettebat üyelerini nerede aramalıyım?";
			link.l1.go = "CaptainComission_Tavern4";
		break;
		
		case "CaptainComission_Tavern4":
			dialog.text = "Bunu bilmiyorum - dört bir yana dağıldılar... Gerçi... içlerinden biri hâlâ buralarda, ama ondan pek bir şey öğrenebileceğini sanmam. Kafasına fena darbe aldı. Biliyor musun, o topçu olarak görev yapıyordu "+pchar.GenQuest.CaptainComission.Name+". O kazadan iki gün sonra bir koyda baygın halde bulundu. Önce hastaneye gönderildi ve bir kahraman gibi tedavi edildi, ama işler karışınca onu zindana attılar ve sorgulamaya çalıştılar, fakat sonra yine de önce tıbbi olarak tedavi edilmesi gerektiğine karar verdiler.";
			link.l1 = "Şu anda hâlâ burada mı?";
			link.l1.go = "CaptainComission_Tavern5";
		break;
		
		case "CaptainComission_Tavern5":
			pchar.GenQuest.CaptainComission.CanoneerName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Evet, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.CanoneerName,NAME_NOM)+" onun adı. Ara sıra uğrar, dilencilikten kazandığı üç beş kuruşu romda harcar. Zavallı adam. Onu görürsem, burada seni beklemesini söylerim.";
			link.l1 = "Teşekkürler, sonra tekrar geleceğim.";
			link.l1.go = "CaptainComission_Tavern6";
		break;
		
		case "CaptainComission_Tavern6":
			AddQuestRecord("CaptainComission2", "39");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			SetFunctionExitFromLocationCondition("CaptainComission_GenerateCanoneer", pchar.location, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_Tavern7":
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
			dialog.text = "Onu tanıyor muyum? Tabii ki tanıyorum. Peki, ona neden ihtiyacın var?";
			link.l1 = "Onunla bir işim var...";
			link.l1.go = "CaptainComission_Tavern8";
		break;
		
		case "CaptainComission_Tavern8":
			dialog.text = ""+GetAddress_Form(pchar)+", o 'iş' konusunda dikkatli olmalısın. "+pchar.GenQuest.CaptainComission.Name+" korsanlık şüphesiyle tutuklandı ve valinin adamları şimdi adada dolaşıp onun suç ortaklarını arıyorlar.";
			link.l1 = "Yok artık! Peki, sonra ne yaptı?";
			link.l1.go = "CaptainComission_Tavern9";
		break;
		
		case "CaptainComission_Tavern9":
			dialog.text = "Doğru mu, yanlış mı bilmiyorum ama, geçenlerde bir korsan gemisinden el konulan yükü saklayıp teslim etmediğini söylüyorlar. Hâlâ ne o korsanı ne de yükü bulan oldu. Valinin bu iftiraya bu kadar kolay inanmasını hâlâ anlayamıyorum. Kaptan "+pchar.GenQuest.CaptainComission.CapName+"  iyi bir itibarı vardı ve harika bir askerdi. Sözüme güvenebilirsin, "+GetAddress_Form(pchar)+".";
			link.l1 = "Peki, uyardığın için sağ ol. Görüşürüz.";
			link.l1.go = "CaptainComission_Tavern10";
		break;
		
		case "CaptainComission_Tavern10":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				pchar.GenQuest.CaptainComission.GetRumour = true;
				SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
				SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
				AddQuestRecord("CaptainComission2", "19");
				AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
				AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			}			
			DialogExit();
		break;
				
		case "EncGirl_1":
			dialog.text = "Ve ona neden ihtiyacın var?";
			link.l1 = "Onunla bir işim var...";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Yerleşkemizdeki erkeklerin yarısı onunla işi var gibi görünüyor. Kadınlarımız onu yakalasa, şehrin kapılarının dışına, çıplak olarak atarlardı.";
			link.l1 = "Eh, neyse... "+GetSexPhrase("Demek uzun bir sıraya katılmışım. Peki, eğer başka biri daha gelip onu sorarsa, onlara benden sonra sıraya girmelerini söyle.","Anladım")+"...";
			link.l1.go = "exit";
			pchar.quest.EncGirl_SpeakTavernKeeper.over = "yes";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;
		
		case "EncGirl_3":
			dialog.text = "Buraya sık sık gelir - genelde iş aramaya uğrar, ama şu anda burada değil. Ara sıra tekrar uğra - gelirse ona burada seni beklemesini söylerim.";
			link.l1 = "Teşekkürler, sonra tekrar geleceğim...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "FindingLover";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitTavern.function = "EncGirl_GenerateLover";
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Demek sen   "+GetSexPhrase("o kaptan ki getiren","o kızı getiren")+"   hovardalık yapan oğlum genç bir gelinle mi?";
				link.l1 = "Evet, yardım eden bendim.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, orada "+GetSexPhrase("o bizim iyilikseverimiz","o, bizim hamimiz")+"Ödül bekliyorsun, öyle mi?";
				link.l1 = "Pekâlâ, ödül olmadan da iyiyim, ama sadece teşekkürünüz yeterli olurdu.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Oğlumu zor zamanında yalnız bırakmadığınız ve onu hassas bir durumdan kurtarmasına yardımcı olduğunuz için size minnettarım. Size teşekkür etmeme izin verin, lütfen bu mütevazı meblağı ve şahsen benden bir hediyeyi kabul edin.";
			link.l1 = "Teşekkür ederim. Bu genç çifte yardım etmek benim için bir zevkti.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Teşekkür mü? Ne teşekkürü?! O aptal yarım yıldır işsiz güçsüz dolaşıyor – bir de bak, gönül eğlendirmeye vakti var! Ben onun yaşındayken kendi işimi kurmuştum! Hah! Vali evlenme çağına gelmiş bir kız babası – ama o sersem, kökü olmayan bir kadını evime getirmiş, üstüne üstlük bir de benden hayır duası istemeye cüret etmiş!";
			link.l1 = "İlk görüşte aşka inanmadığını mı düşünmeliyim?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "Aşk mı? Aşk mı!? Benimle alay mı ediyorsun, yoksa aptal mısın? Gençlerin heveslerine göz yumup bir de pezevenklik yapmaya kalkışmak sana hiç yakışmadı! Sadece bir kızı evinden alıp götürmekle kalmadın, oğlumun hayatını da mahvettin. Senden bir teşekkür bekleme. Elveda.";
			link.l1 = "Sana da aynı şekilde.";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
				
		case "ShipLetters_4":
			pchar.questTemp.different.GiveShipLetters.speakTavern = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Bir bakayım! Hmm... Ama siz zaten kaptansınız. Bence bu konuda liman başkanıyla görüşmelisiniz.";
				link.l1 = " Tavsiyeniz için teşekkür ederim. ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Bir bakayım! Aa! İsme bakılırsa, bu belgeler benim müşterilerimden birine ait, oldukça saygın bir beyefendi. Bu evrakları bizzat sahibine teslim edebilirim. Bana verir misiniz?";
				link.l1 = "Tekrar düşündüm de...";
				link.l1.go = "exit";
				link.l2 = "Al onları. Yardımcı olabildiğim için memnunum.";
				link.l2.go = "ShipLetters_end";				
			}	
		break;
		
		case "ShipLetters_end":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "3");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//zagolski. переделка
		case "work":
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple("Kime hizmet ettiğim umurumda değil, çünkü paranın milliyeti yoktur. Ama sana yardım etmeyeceğim, çünkü senin geldiğin bayrak altında geldin "+NationNameGenitive(sti(pchar.nation))+".","Ben sadece basit bir meyhane sahibiyim, ama birlikte çalışmak "+NationNameAblative(sti(pchar.nation))+" bana cazip gelmiyor.");
				link.l1 = RandPhraseSimple("Peki, nasıl istersen...","Peki, nasıl istersen...");
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("We usually have a lot of passengers here. Still, I don't think there would be even one duffer among them who might agree to travel on your ship. Your ill repute precedes you; only a fool would sail with such a scoundrel.","I am quite frequently approached by merchants who need escorting. But your ill repute precedes you, and I will not recommend you to anyone. I care for my own reputation, you know. No one wants to hire a wolf to guard their sheep.");
				link.l1 = RandPhraseSimple("Ah, gerçekten, o dedikoduların hepsine inanmamalısın...","Anladım. Herkesin sessiz kalmasını sağlamak zor.","Şu aralar insanlar çok yumuşak oldu...");
				link.l1.go = "exit";
				break;
			}
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
        	{
				dialog.text = "Ve gemin nerede? Yoksa yolcuları sırtına alıp yüzerek mi götüreceksin?";
				link.l1 = "Hey, haklısın...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Eğer korsan yerleşimlerine ya da düşman ülkelerin limanlarına gitmekten korkmuyorsan, sana verebileceğim bir iş olabilir. Özellikle aradığın bir şey var mı?";
			link.l1 = "Bu sorun olmamalı. Sanırım size eşlik edebilirim.";
			link.l1.go = "work_1";
			link.l2 = "Yolcunuz var mı? Onları istedikleri yere götürebilirim, tabii ücretini öderlerse.";
			link.l2.go = "work_2";
			link.l3 = "Hayır, böyle bir iş bana göre değil. Teşekkür ederim.";
			link.l3.go = "exit";
		break;

		case "work_1":
				dialog.text = "Genellikle bana koruma göreviyle ilgili bir şey sormazlar. Meyhanedeki tüccarlara sor – belki senin hizmetine ihtiyaçları vardır.";
				link.l1 = "Peki, nasıl istersen.";
                link.l1.go = "exit";
		break;

		case "work_2":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2 || bBettaTestMode)
    		{					
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
				{
					dialog.text = "Üzgünüm, ama seninle yolculuk etmeye istekli kimsem yok.";
					link.l1 = "Anladım.";
					link.l1.go = "exit";
					break;
				}
		         // пассажир
				if (hrand(6) > 1)
				{
					dialog.Text = "Az önce içeri giren bir adam var – geçen bir gemi hakkında sorular soruyordu. İstersen onunla konuşabilirsin.";
					link.l1 = RandPhraseSimple("O kim? Belki de bir alçaktır? Ya da daha da kötüsü, aranan bir korsan mı?","Peki o kim? Onunla bir sorun çıkacak mı?");
					Link.l1.go = "PassangerAreYouSure";
				}
				else
				{
					dialog.text = "Hayır, bugün kimse bunun hakkında sormadı. Belki başka bir gün.";
					link.l1 = RandPhraseSimple("Eğer orada yoksa, yok demektir...","Şansım işte... Neyse, görüşürüz o zaman.");
					link.l1.go = "exit";
				}
            }
    		else
    		{
				dialog.text = "Bugün kimse yok. Birkaç gün sonra tekrar gel.";
				link.l1 = "Peki, nasıl istersen.";
                link.l1.go = "exit";
    		}
        break;

        case "ConvoyAreYouSure":
		    dialog.text = LinkRandPhrase("Kim bilebilir? Sordun - cevapladım.","Bu, senin çözmen gereken bir mesele. Oradaki kimseye kefil olmam.","Her çeşit insan buraya gelir. Burası bir meyhane, kaptan, vali konağı değil.");
			Link.l1 = "Teşekkürler, o zaman pazarlık yaparız.";
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

        case "PassangerAreYouSure":
		    dialog.text = LinkRandPhrase("Kim bilebilir? Sordun - cevapladım.","Bu işi sen çözmelisin. Oradakilerden hiçbiri için kefil olmam.","Her çeşit insan buraya gelir. Burası bir meyhane, kaptan, valinin konağı değil.");
			Link.l1 = "Anladım. Hadi bu adamın kim olduğunu öğrenelim...";
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

		 case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Helen_room":
			dialog.text = "Tabii ki, Helen. Ne kadar kalacaksın? Ve ne oldu, yaşlı Gladys'le yine mi tartıştınız?";
			if(!isDay())
			{
				link.l1 = "Sadece sabaha kadar uyumak istiyorum. Şimdi eve gidersem, onu kesinlikle uyandırırım.";
				link.l1.go = "Helen_room_day";
			}
			else
			{
				link.l1 = "Hayır, hayır, sadece gece yelken açmam gerek, onu uyandırmak istemiyorum.";
				link.l1.go = "Helen_room_night";
				link.l2 = "Uzun, güzel bir uyku çekmek ve acele etmeden uyanmak istiyorum. Bir oda alacağım, bütün günü burada geçireceğim.";
				link.l2.go = "Helen_room_day_next";
			}
		break;

		case "room":
   			if (chrDisableReloadToLocation || CheckAttribute(pchar, "GenQuest.TavernClose")) //кто-то должен подойти к ГГ.
			{
				dialog.text = "Oda dolu, "+GetAddress_Form(NPChar)+", senin için yapabileceğim bir şey yok.";
				link.l1 = "Eh, bu gerçekten yazık...";
				link.l1.go = "exit";
				break;
			}
			// суп из черепахи
			if (CheckAttribute(pchar, "questTemp.Terrapin.Room_close") && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "Monsieur Henri Thibaut şu anda odayı kiraladı ve bir ay peşin ödeme yaptı, bu yüzden size yardımcı olamam, kaptan.";
				link.l1 = "Eh, bu gerçekten yazık...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "cave" && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "Oda dolu, "+GetAddress_Form(NPChar)+", senin için yapabileceğim hiçbir şey yok.";
				link.l1 = "Eh, bu gerçekten yazık...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore" && npchar.location == "Baster_tavern") // 070712
			{
				dialog.text = "Oda dolu, "+GetAddress_Form(NPChar)+", senin için yapabileceğim hiçbir şey yok.";
				link.l1 = "Eh, bu gerçekten yazık...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
			{
				Dialog.text = "Maalesef hayır, Kaptan. Tüm odalar Blackwood ve adamları tarafından tutuldu.";
				if (CheckAttribute(pchar, "questTemp.LadyBeth_TavernRoomDialog"))
				{
					link.l1 = "Ah, ne yazık!";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Tüm odalar mı? Burada birden fazla oda mı var?";
					link.l1.go = "LadyBeth_Room";
				}
				break;
			}
			//-->> квест официантки
			if (pchar.questTemp.different == "FackWaitress_toRoom")
			{
				dialog.text = "Bir oda kiralamak mı istiyorsun? Sorun değil. 100 sekizlik altın ve oda senin.";
				if (sti(pchar.money) >= 100)
				{
					link.l1 = "Paran burada.";
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -100);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
					pchar.questTemp.different = "FackWaitress_toRoomUp";
				}
				else
				{
					link.l1 = "Hmm... Sanırım daha sonra tekrar geleceğim...";
					link.l1.go = "exit";
				}
				break;
			}
			if (pchar.questTemp.different == "FackWaitress_toRoomUp")//квест официантки
			{
				dialog.text = "Oda tamamen sizin. Buyurun, rahatınıza bakın.";
				link.l1 = "Sağ ol, dostum.";
				link.l1.go = "exit";
				break;
			}
			//<<-- квест официантки
			// --> квест "A damsel in the jungle"
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && npchar.city == pchar.GenQuest.EncGirl.city)
			{
				if(pchar.GenQuest.EncGirl == "EncGirl_ToTavern")
				{
					dialog.text = "Bir oda kiralamak mı istiyorsun? Sorun değil. 100 sekizlik ver, oda senin.";
					if (sti(pchar.money) >= 100)
					{
						link.l1 = "Al paran burada.";
						link.l1.go = "exit";
						AddMoneyToCharacter(pchar, -100);
						LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
						pchar.GenQuest.EncGirl = "EncGirl_toRoomUp";
					}
					else
					{
						link.l1 = "Hmm... Sanırım sonra tekrar geleceğim...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.GenQuest.EncGirl == "EncGirl_toRoomUp")//квест  по спасению тетки в пампасах
				{
					dialog.text = "Oda tamamen sizin. İçeri gelin ve rahatlayın.";
					link.l1 = "Sağ ol, dostum.";
					link.l1.go = "exit";
					break;
				}
			}
			// <-- квест "A damsel in the jungle"

			// belamour постоялец -->
			if (CheckAttribute(pchar, "GenQuest.Unwantedpostor") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && abs(50-sti(pchar.reputation.nobility)) > 20)
			{
				if(pchar.GenQuest.Unwantedpostor == "start")
				{
					SetFunctionTimerCondition("Unwantedpostor_OneDay", 0, 0, 1, false);
					pchar.GenQuest.Unwantedpostor = "timer";
				}
				dialog.text = "Affedersiniz kaptan, maalesef boş oda yok. Misafir gitmiyor. Hâlâ da bana ödeme yapmadı...";
				link.l1 = "Galiba geceyi ortak salonda geçirmek zorunda kalacağız...";
				link.l1.go = "Unwantedpostor_hall_day_wait";
				link.l2 = "Üzgünüm. Hadi başka bir şeyden bahsedelim.";
				link.l2.go = "int_quests";
				if(pchar.GenQuest.Unwantedpostor != "Lose")
				{
					link.l3 = "O zaman muhafızları çağırın. Ne biçim misafir bu? Ne ödeme yapıyor, ne de çıkmak istiyor...";
					link.l3.go = "Unwantedpostor";
				}
				break;
			}
			//<-- постоялец

			dialog.text = "Burada ne kadar kalmayı düşünüyorsun?";
			if(!isDay())
			{
				link.l1 = "Sabahta kadar.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "Geceye kadar.";
				link.l1.go = "room_night";
				link.l2 = "Yarına kadar.";
				link.l2.go = "room_day_next";
			}
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.MarySexBlock"))
			{
				pchar.questTemp.MarySexBlock = true;
				SetTimerFunction("Mary_DeleteSexBlock", 0, 0, 1);
			}
		break;

		case "room_day":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
				dialog.text = "Oda sizin emrinizde, kaptan. Tamamen ücretsiz.";
				link.l1 = "Sağ ol dostum.";
				link.l1.go = "room_day_wait";
				link.l3 = "Şimdi değil. Başka bir şey konuşalım.";
				link.l3.go = "int_quests";
				break;
			}
			dialog.text = "Bu sana sekizli beş akçeye mal olacak.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Anlaştık. Al bakalım.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase("Bu fiyata mı? Kraliyet odası mı kiralıyorsunuz? Ben bedavaya ortak salonda kalırım daha iyi.","Ne yazık ki, şu an bir yatakta uyumak benim için lüks sayılır. Görünen o ki, ortak salonda bir sıranın üstünde uyuyacağım.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Şu anda değil. Konuyu değiştirelim.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_day_next":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
				dialog.text = "Oda emrinizde, kaptan. Tamamen ücretsiz.";
				link.l1 = "Sağ ol dostum.";
				link.l1.go = "room_day_wait_next";
				link.l3 = "Şimdi değil. Başka bir şey konuşalım.";
				link.l3.go = "int_quests";
				break;
			}
			dialog.text = "Bu sana 10 sekizlik madeni para tutar.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Anlaştık. Al bakalım.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase("Bu fiyata mı? Kraliyet odalarını mı kiralıyorsunuz? Ben bedavaya ortak salonda kalırım daha iyi.","Ne yazık ki, bir yatakta uyuma lüksü şu an bana göre değil gibi görünüyor. Sanırım ortak salonda bir sırada uyumam gerekecek.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Şu anda değil. Konuyu değiştirelim.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
				dialog.text = "Oda emrinizde, kaptan. Tamamen ücretsiz.";
				link.l1 = "Sağ ol, dostum.";
				link.l1.go = "room_night_wait";
				link.l3 = "Şimdi değil. Hadi başka bir şey konuşalım.";
				link.l3.go = "int_quests";
				break;
			}
			dialog.text = "Bu sana 5 sekizlik parçaya mal olacak.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Anlaştık. Al bakalım.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase("Bu fiyata mı? Kraliyet odası mı kiralıyorsunuz? Ben bedavaya ortak salonda kalırım daha iyi.","Ne yazık ki, şu an bir yatakta uyumak benim için lüks sayılır gibi görünüyor. Sanırım ortak salonda bir sıranın üstünde uyumam gerekecek.");
			link.l2.go = "hall_night_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Şu anda değil. Konuyu değiştirelim.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night_wait":
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (hRand(3) == 1)
            {
                Dialog.text = "Defol buradan, seni alçak! Ortak salon bedava olabilir, ama düzgün davranış bekliyoruz!";
				link.l1 = "Pekala, pekala, gidiyorum.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "Defol git buradan, seni alçak! Ortak salon bedava olabilir, ama düzgün bir davranış bekliyoruz!";
				link.l1 = "Pekala, pekala, gidiyorum.";
				link.l1.go = "exit";
            }
            else
            {
				// belamour прерывание ночной приключенец -->
				if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
					SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
				}
				// <-- прерывание ночного приключенца
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = "Bu rezil davranışa derhal son verin yoksa muhafızları çağırırım!";
			link.l1 = "Pekala, pekala, gidiyorum.";
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		
		//******************* ноды квеста священника. поиск грабителей (квест № 2)**********************
		case "Tavern_GenQuest_Church_2_1":
			dialog.text = "Bu konuda pek bir şey bilmiyorum... En iyisi müşterilere sor.";
			link.l1 = "Anladım, teşekkür ederim.";
			link.l1.go = "exit";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
		break;
			
		//******************* ноды квеста священника. вернуть рукописи (квест № 1)**********************
		case "Tavern_ChurchGenQuest1_Node_1":
			dialog.text = "Biz veresiye hizmet vermiyoruz, "+GetSexPhrase("bayım","miss")+".";
			link.l1 = "Ben paramı altınla öderim. Artık altın ya da gümüş kabul etmiyor musun?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_2":
			dialog.text = "Üzgünüm, "+GetSexPhrase("bayım","miss")+" Kaptan, ama arkadaşınızın bir borcu vardı, ben de...";
			link.l1 = "Daha az düşün, daha hızlı çalış. Şimdi, cesur dostumun sana ne kadar borcu var?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_3":
			iTemp = (rand(3)+1)*100;
			PChar.GenQuest.ChurchQuest_1.MoneyToBarmen = iTemp;
			if(rand(1) == 0) // "If he's a simple one and pays right away"
			{
				dialog.text = FindRussianMoneyString(iTemp)+", hanımefendi"+GetSexPhrase("ter","s")+" kaptan, ayrıca yanında sadece birkaç kilise kitabı vardı - sahip olduğu tek şey buydu, biraz değeri olan.";
				if(sti(PChar.money) >= iTemp)
				{
					link.l1 = "Al işte paraların. El yazmalarını ver. Onlara dikkat et – bu sıradan bir resimli kitap değil, Kutsal Kitap!";
					link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
				}
				else
				{
					link.l1 = "Biraz bekle... Parayla geri döneceğim";
					link.l1.go = "exit";
					PChar.GenQuest.ChurchQuest_1.NoMoneyToBarmen = true;
				}
			}
			else // "If he's not a simple one"
			{
				dialog.text = FindRussianMoneyString(iTemp)+", hanımefendi"+GetSexPhrase("ter","s")+" kaptan.";
				link.l1 = "Onun borcunu ödeyeceğim ve rehin bıraktığı her ne varsa alacağım.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2";
			}
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_1":
			DialogExit();
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "8");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", GetFullName(CharacterFromID("ChurchGenQuest1_Cap")));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2":
			dialog.text = "Hayır, hanımefendi"+GetSexPhrase("ter","s")+", bu öyle olmaz.";
			link.l1 = "Ne demek - 'öyle olmaz'? Kaptanın borcu ödendi - o tamam. Paranı geri aldın - sen de tamam. Onun sözünü aldım - ben de tamamım. Herkes tamam - o zaman neden 'öyle olmaz' diyorsun?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_1";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_1":
			dialog.text = "Çünkü, hanımefendi"+GetSexPhrase("ter","s")+" Kaptan, paraya ihtiyacım yok. O kaptanı çok iyi tanıyorum, bu yüzden bana borcunu ödeyeceğini ya da bu el yazmalarını benden alacağını hiç beklemedim.";
			link.l1 = "Ne demek - paraya ihtiyacın yok? Yani bu defterleri en başından beri kendine saklamayı mı planladın? Ama neden, Allah aşkına?!";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_2":
			dialog.text = "Tanrı aşkına - aynen öyle, işte bu yüzden, hanımefendi"+GetSexPhrase("ter","s")+". Küçük oğlum çok hastaydı, ve karımla birlikte, Yüce Rabbimiz çocuğumuzu ateşten kurtarırsa kiliseye bağış yapacağımıza dair bir adak adadık. Rabbimizin merhameti sonsuzdur, oğlum hayatta ve sağlıklı, şimdi de sözümüzü tutmamız gerek. Zamanı geldi kaptan "+PChar.GenQuest.ChurchQuest_1.CapFullName+" çıkageldi ve bu kilise kitaplarını rehin bıraktı. Böyle bir edepsizliğe izin veremezdim - Tanrı'nın Sözüyle içki parası ödemek - bu yüzden kitapları mahallemizin papazına teslim etmeye karar verdim.";
			link.l1 = "Elbette, bu iyi bir davranış, ama bilmelisiniz ki bu kitaplar aslında başka bir rahibe ait – hatta sadece bir rahip değil, bir piskopos ve benim manevi rehberim. O, çalınan Kilise malını bağışlamaya cüret edenlere kızabilir, hatta onları lanetleyebilir. Bu kitapları sizden satın almak ve güvenle evine götürmek isterim. Parayı kendi cemaatinize bağışlayabilirsiniz, eminim Tanrı bunu da aynı şekilde takdir edecektir.";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_3":
			dialog.text = "Mis"+GetSexPhrase("ter","s")+"... Hanımefendi"+GetSexPhrase("ter","s")+" Kaptan... Elbette, hiçbir fikrim yoktu! Onları hemen geri vereceğim, karşılığında da para istemem. Sadece piskoposa bizim için bir iki güzel söz ederseniz... Belki bizi kutsar ve yeminimizden kurtarır...";
			link.l1 = "Elbette yeminini yerine getirmiş sayılacaksın! Sonuçta, kitapları gerçek sahibine iade etmek için kazancından vazgeçtin. Hangi kilise olduğu önemli değil, çünkü tek bir Tanrı ve tek bir Kutsal Katolik Apostolik Kilisesi var, değil mi? Peki, onları bana ver, sana da bol şans...";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_4";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_4":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "9");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Tavern":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Daha önce hiç duymadım... Aslında bu nedir? Bunca zamandır böyle bir şey duymamıştım.";
			link.l1 = "Eh, bu bir gemi ustasının aleti, "+pchar.GenQuest.Device.Shipyarder.Describe+". Sana böyle bir şey teklif eden oldu mu?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 6)
			{
				dialog.text = "Hmm... Evet, gerçekten de tuhaf bir adam o şeyi bana getirdi. Ne olduğunu söylemedi gerçi – sadece içkiyle takas etmeye çalıştı. Tabii ki reddettim – o zımbırtıya ihtiyacım yoktu.";
				link.l1 = "Peki, nasıl biriydi ve nereye gitti? O alete gerçekten ihtiyacım var.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Hayır, öyle bir şey yok. Üzgünüm, sana yardımcı olamam. Etrafta başkalarına sor.";
				link.l1 = "Anladım. Pekâlâ, biraz soruşturmanın zamanı geldi!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		//Jason --> генератор Место под солнцем
		case "Sunplace_Tavern":
			if (makeint(environment.time) > 12.0 && makeint(environment.time) < 17.0)//в магазине
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? O, yakın zamanda oradaydı ve şimdiye kadar yoldaşı olan dükkâncıya gitmiş olmalı. Onu dükkânda aramayı dene - büyük ihtimalle oradadır.";
				link.l1 = "Teşekkürler! Bana çok yardımcı oldun!";
				link.l1.go = "Sunplace_Tavern_1";
			}
			else//ушел на рыбалку
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Bugün sabahın erken saatlerinde, lügeriyle denize açıldı. Şu anda muhtemelen küpeştede durup manzarayı seyrediyordur. Ona ihtiyacınız varsa, denizde bulmayı deneyebilir ya da birkaç gün içinde dönmesini bekleyebilirsiniz...";
				link.l1 = "Teşekkürler! Sanırım beklemeyeceğim - onu denizde bulmak daha kolay olacak. İyi şanslar!";
				link.l1.go = "Sunplace_Tavern_2";
			}
		break;
		
		case "Sunplace_Tavern_1"://магазин
			pchar.quest.Sunplace_Store.win_condition.l1 = "location";
			pchar.quest.Sunplace_Store.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.CityT + "_store";
			pchar.quest.Sunplace_Store.function = "Sunplace_CreateTrader";
			AddQuestRecord("Sunplace", "6");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		
		case "Sunplace_Tavern_2"://рыбалка
			pchar.GenQuest.Sunplace.Trader.IslandID = GetCharacterCurrentIslandId(npchar);
			pchar.GenQuest.Sunplace.Trader.EnemyNation = npchar.nation;
			pchar.quest.Sunplace_Sea.win_condition.l1 = "location";
			pchar.quest.Sunplace_Sea.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.IslandID;
			pchar.quest.Sunplace_Sea.function = "Sunplace_CreateTraderLugger";
			AddQuestRecord("Sunplace", "7");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		// <-- генератор Место под солнцем	
		
		// Jason --> Голландский гамбит
		case "HWICHollJacob_Tavern":
			dialog.text = "Psssst... Neden bağırıyorsun? Seni epeydir bekliyor. Şimdiden bir şişe romu bitirdi. Yukarı çık, odada bulacaksın onu.";
			link.l1 = "Anladım. Umarım hâlâ uyanıktır.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern", "reload2_back", false);
			pchar.questTemp.HWIC.Holl = "JacobInRoom";
			AddDialogExitQuestFunction("Create_JacobVanBerg");
			DelLandQuestMark(npchar);
		break;
		
		case "HWICSelfFernando_Tavern":
			if (NPChar.location == pchar.questTemp.HWIC.Self.SpainCity +"_tavern")
			{
				//DelMapTonzagAllQM();
				dialog.text = "Evet, o beyefendiyi tanıyorum. Şu anda kasabada bir yerde olmalı - onu daha yeni penceremin önünden geçerken gördüm.";
				link.l1 = "Teşekkürler! Onu bulmaya gideceğim!";
				link.l1.go = "Fernando_Land";
				/* if (makeint(environment.time) > 10.0 && makeint(environment.time) < 18.0)//на улице
				{
					dialog.text = "Evet, o beyefendiyi tanıyorum. Şu anda kasabada bir yerde olmalı - onu daha yeni penceremin önünden geçerken gördüm.";
					link.l1 = "Teşekkürler! Onu bulmaya gideceğim!";
					link.l1.go = "Fernando_Land";
				}
				else //в море
				{
					dialog.text = "Evet, şu anda kasabamızı ziyaret ediyor. Şu an burada değil - brigantinle denize açıldı. Muhtemelen buradan çok uzakta değildir, adamızın çevresindeki sularda bir yerdedir.";
					link.l1 = "Teşekkürler dostum! Bana gerçekten çok yardımcı oldun!";
					link.l1.go = "Fernando_Sea";
				} */
				pchar.questTemp.HWIC.Self = "KillFernando";
			}
			else
			{
				dialog.text = "Fernando Rodriguez mi? Hiç duymadım. Hayır, bu adam hakkında hiçbir şey bilmiyorum.";
				link.l1 = "Anladım... O halde arayış devam ediyor...";
				link.l1.go = "exit";
			}
			npchar.quest.HWICTalked = "true";
		break;
		
		case "Fernando_Land":
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.SpainCity +"_town";
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnLand";
			AddQuestRecord("Holl_Gambit", "3-2");
			DialogExit();
		break;
		
		case "Fernando_Sea":
			pchar.questTemp.HWIC.Self.FernandoIslandID = GetCharacterCurrentIslandId(npchar);
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.FernandoIslandID;
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnSea";
			AddQuestRecord("Holl_Gambit", "3-3");
			DialogExit();
		break;
		//<-- Голландский гамбит
		
		//Jason --> гонки на гидропланах
		case "Race_Advantage":
			dialog.text = "Evet, elbette. Tebrikler, kaptan. Zaferinizden zaten haberdarım. İşte paranız.";
			link.l1 = "Teşekkür ederim, "+npchar.name+".";
			link.l1.go = "Race_Advantage_1";
		break;
		
		case "Race_Advantage_1":
			DialogExit();
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Racing.Go.Money)*2);
			AddQuestRecord("Racing", "4");
			AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Gen"));
			CloseQuestHeader("Racing");
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
		break;
		//<-- гонки на гидропланах
		
		//Jason --> захват пассажиров
		case "Marginpassenger":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.lose"))
			{
				dialog.text = "Şey, beyefendi, "+pchar.GenQuest.Marginpassenger.q2Name+" yaklaşık  öldü "+LinkRandPhrase("bir ay","üç hafta","iki ay")+" ago. "+LinkRandPhrase("Aniden ateşe yenik düştü","Kasaba kapılarında bıçaklanmış - haydutlar ya da o kızıl derili vahşiler","Bir düelloda vuruldu")+"… Allah rahmet eylesin...";
				link.l1 = "Lanet olsun!.. Peki, onunla ne yapmamı bekliyorsun... Neyse, her neyse. Bilgi için sağ ol. Görüşürüz, "+npchar.name+".";
				link.l1.go = "Marginpassenger_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.Marginpassenger.q2Name+"Evet, şehirde bir yerde olmalı. Onu sokaklarda ara. Ama unutma, her gün öğlene kadar valinin ofisinde olur, akşam dokuzdan sonra ise evine kapanır.";
				link.l1 = "Teşekkürler! Onu bulmaya gideceğim...";
				link.l1.go = "Marginpassenger_2";
			}
		break;
		
		case "Marginpassenger_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "7");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: Добряку недолго осталось -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Puerto Principe, to the Black Pastor");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Le Francois, to Kindly Jacques");
			}
			// <-- belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "Marginpassenger_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "8");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			pchar.GenQuest.Marginpassenger = "street";
		break;
		//<-- захват пассажиров
		
		//Jason --> поиск дезертира
		case "FindFugitiveTav":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 0)
			{
				dialog.text = NPCStringReactionRepeat("Görünüşe göre kaptanınız doğruyu söylüyormuş. "+pchar.GenQuest.FindFugitive.Name+" gerçekten de yakın zamanda yerleşkemize geldi. Onu gündüz saatlerinde sokaklarda arayın - genellikle vaktini boşa harcıyor olur.","Bu adamı bana zaten sordun, bildiğim her şeyi anlattım!","Benimle dalga mı geçiyorsun, yoksa gerçekten aptal mısın?! Aynı şeyi üçüncü kez soruyorsun zaten!","Bir düşün, böyle bir aptal nasıl kaptan olabildi...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Teşekkür ederim dostum, bana çok yardımcı oldun!","Evet, evet, tamam.","Vay canına, sakin ol biraz. Sadece unuttum.","Eh, gördüğün gibi yaptı...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveTav_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("Hayır dostum, o ismi daha önce hiç duymadım. Etrafta sor - belki birileri onu tanıyordur...","Bu adamı bana zaten sordun, ve sana söyledim: Bilmiyorum!","Benimle dalga mı geçiyorsun, yoksa gerçekten aptal mısın?! Aynı şeyi üçüncü kez soruyorsun zaten!","Bir düşün, böyle bir aptal nasıl kaptan olabildi...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Anladım. Yine de teşekkür ederim.","Evet, evet, tamam.","Vay canına, sakin ol biraz. Sadece unuttum.","Eh, gördüğün gibi yaptı...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveTav_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-1");
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_city";
			LAi_SetLoginTime(sld, 11.0, 18.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_town", "goto", "goto"+(rand(9)+1));
		break;
		//<-- поиск дезертира
		
		//--> Бремя гасконца
		case "Sharlie_crew":
			dialog.text = "Maalesef, şu anda sana yardımcı olamam - tanıdığım hiç kimse senin emrine girmek istemez. Ama sana bir tavsiye verebilirim - hemen arkandaki masaya oturan denizciyle konuş. O ve arkadaşları az önce bir ticaret gemisinden ayrıldılar. Belki seninle gitmeyi kabul ederler.";
			link.l1 = "Pekala, tam olarak öyle yapacağım! Çok teşekkür ederim!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "sailor";
			//усадим матроса Алонсо
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSailor" , "Alonso", "man", "man", 10, FRANCE, -1, true, "quest"));
			sld.name = GetCharacterName("Alonso");
			sld.lastname = "";
			FantomMakeCoolFighter(sld, 10, 20, 20, "blade_05", "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Sharlie_sailor";
			sld.greeting = "town_sailor";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator("FortFrance_tavern", "sit7");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");
			AddQuestRecord("Sharlie", "6-1"); // mitrokosta
		break;
		
		case "Sharlie_skiper":
			dialog.text = "Sana özel bir şey söyleyemem, dostum. Şu anda mekânıma uğrayan bir gemi kılavuzu yok. Limanda biraz soruştur istersen – belki oradaki insanlar daha fazlasını biliyordur.";
			link.l1 = "Anladım. Peki, gidip insanlarla konuşacağım.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "findskiper";
			//сгенерим наводчика
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSkiperTalker", "citiz_"+(rand(19)+21), "man", "man", 10, FRANCE, -1, true, "marginal"));
			FantomMakeCoolFighter(sld, 10, 20, 20, RandPhraseSimple("blade_04","blade_06"), "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "skipertalker";
			sld.greeting = "marginal";
			LAi_SetWarriorType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "FortFrance_town", "patrol", "patrol"+(rand(13)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Бремя гасконца
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_tortuga":
			sld = characterFromId("Tortuga_waitress");
            dialog.text = "Hemen, monsieur!.. En iyi Fransız şarabı! "+sld.name+"! En iyi misafir odasını hemen hazırla! Bunun ücreti 1000 peso, monsieur.";
			link.l1 = "Al bakalım.";
			link.l1.go = "mtraxx_tortuga_1";
		break;
		
		case "mtraxx_tortuga_1":
			AddMoneyToCharacter(pchar, -1000);
            DialogExit();
			pchar.questTemp.Mtraxx.Retribution = "room";
			pchar.quest.mtraxx_retribution_room.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.location = "Tortuga_tavern";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.mtraxx_retribution_room.function = "Mtraxx_RetributionToRoom";
		break;
		// belamour постоялец -->
		case "Unwantedpostor_hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "Defol, alçak! Burada para ödeyen müşteriler için değerli yeri işgal ediyorsun!";
				link.l1 = "Peki, tamam... Gidiyorum.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "Unwantedpostor":
				dialog.text = "Evet - ve korumalarımın insanları meyhaneden sürüklediğini görüp tüm müşterilerimi korkutmak mı? Ayrıca bazı müşterilerim askerlerin yanında olmayı sevmez. Onları tedirgin ediyor, anlıyor musun? İtibarımı zedelemek istemem...";
				link.l1 = "Hmm, ya senin sorununu ben çözersem?";
				link.l1.go = "Unwantedpostor_1";
		break;
		
		case "Unwantedpostor_1":
				dialog.text = "Kararını verdin mi? Silahlı, belli ki profesyonel bir paralı asker...";
				link.l1 = "Hmm, haklısın, silahlı bir paralı askerle tartışmak istemiyorum...";
				link.l1.go = "Exit";
				link.l2 = "Ben de manastıra kapanmış bir rahibe değilim... Ve hâlâ bir oda kiralamak istiyorum.";
				link.l2.go = "Unwantedpostor_2";
		break;
		
		case "Unwantedpostor_2":
				dialog.text = "Eğer onu, hımm... buradan çıkmaya ikna edebilirsen, oda sabaha kadar senin. Üstelik ücretsiz, tabii ki.";
				link.l1 = "Biliyor musun, fikrimi değiştirdim. Kimseyi ikna etmek istemiyorum.";
				link.l1.go = "Exit";
				link.l2 = "Bunu izlemek isteyeceksin. İstenmeyen misafirin, dev bir martı gibi meyhanenden fırlayıp gidecek.";
				link.l2.go = "Unwantedpostor_kikcoff";
		break;
		
		case "Unwantedpostor_kikcoff":
				DialogExit();
				chrDisableReloadToLocation = true; //закрыть локацию
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location+"_upstairs")], true); //запретить драться
				iTemp = sti(pchar.rank) + rand(5);
				sld = GetCharacter(NPC_GenerateCharacter("Berglar_Unwantedpostor", "citiz_5"+(rand(3)+1), "man", "man", iTemp, PIRATE, -1, true, "quest")); // "mercen_"+(rand(14)+14)
				FantomMakeCoolFighter(sld, iTemp, 50 + rand(30), 50 + rand(30), "topor_04", "", "bullet", 50);
				sld.dialog.filename = "GenQuests_Dialog.c";
				sld.dialog.currentnode = "Unwantedpostor_room";	
				sld.greeting = "Enc_Raiders"; 
				if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
				{
					DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
					ChangeCharacterAddressGroup(sld, pchar.location+"_upstairs", "quest", "quest3");
				} 
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		// <-- belamour постоялец
		
		case "Helen_room_night":
			dialog.text = "Anladım. Beş gümüş olacak.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Tabii ki, buyurun.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = "Aslında, biliyor musun... Belki başka bir zaman. Bugünün geri kalanını ayakta geçireceğim.";
			link.l2.go = "Helen_night_exit";
		break;
		
		case "Helen_room_day":
			dialog.text = "Akıllıca bir karar. Beş gümüş alırım, sana da iyi geceler.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Buyurun, teşekkür ederim - iyi geceler.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = "Bir daha düşündüm de, uyumak istemiyorum. Şehirde dolaşacağım, gece havası alacağım.";
			link.l2.go = "Helen_day_exit";
		break;
		
		case "Helen_room_day_next":
			dialog.text = "Elbette, Helen. On peso tutar.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Tabii, buyurun.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = "Aslında... Bütün bir günü faydalı bir şeyle geçirebilirim. Belki başka bir zaman.";
			link.l2.go = "Helen_Next_day_exit";
		break;
		
		case "Helen_night_exit":
			dialog.text = "Dediğin gibi olsun, Helen.";
			link.l1 = "Mhm.";
			link.l1.go = "exit";
		break;
		
		case "Helen_day_exit":
			dialog.text = "İyi bir yürüyüşten sonra kendini uykulu bile hissedebilirsin.";
			link.l1 = "Ha-ha, belki.";
			link.l1.go = "exit";
		break;
		
		case "Helen_next_day_exit":
			dialog.text = "Nasıl istersen.";
			link.l1 = "Pekala, bir dahaki sefere kadar.";
			link.l1.go = "exit";
		break;
		
		case "Helen_rumours_tavern":
			dialog.text = "Tabii ki, Helen, seni dinliyorum.";
			link.l1 = "Şehirdeki en son haberler ya da ilginç dedikodular neler?";
			link.l1.go = "rumours_tavern";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Room":
			dialog.text = "Normalin üç katı para ödüyor, yani... anlıyorsun. Ve ona hayır demeni tavsiye etmem – huysuz biridir. Özellikle son zamanlarda.";
			link.l1 = "Ona ne oldu?";
			link.l1.go = "LadyBeth_Room_2";
		break;
		
		case "LadyBeth_Room_2":
			dialog.text = "Takıntı, işte tam olarak bu. Başlarda cömert, iyi kalpli bir adamdı. Tayfası meyhanelerde para saçar, kızlara hediyeler alırdı. 'Lady Beth' limana yanaştığında gerçek bir şenlik başlardı. Peki ya şimdi? Şimdi sadece erzak alıyorlar ve rastgele adam topluyorlar. Sanki denizci değil, sadece çalışacak el arıyorlar. Neyse, kendisiyle konuşabilirsin.";
			link.l1 = "Belki yaparım. Teşekkürler.";
			link.l1.go = "exit";
			pchar.questTemp.LadyBeth_TavernRoomDialog = true;
		break;
		// Леди Бет <--
	}
}

string findTraderCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}
