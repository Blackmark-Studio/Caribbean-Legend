// boal 25/04/04 общий диалог церковь
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Church\" + NPChar.City + "_Church.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    
    string iDay, iMonth, lastspeak_date, eggStr;
    string sTemp, sTitle;

	iDay           = environment.date.day;
	iMonth         = environment.date.month;
	lastspeak_date = iday + " " + iMonth;
	int iMoneyToCharacter;

	if (!CheckAttribute(npchar, "quest.HealthMonth"))
    {
        npchar.quest.HealthMonth = "";
    }
	
    if (!CheckAttribute(npchar, "quest.BadMeeting"))
    {	
        npchar.quest.BadMeeting = "";
    }
    if (!CheckAttribute(npchar, "quest.GhostShipMonth"))
    {
        npchar.quest.GhostShipMonth = "";
    }
    
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = "";
	}
	
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = "";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase(""+GetSexPhrase("Oğlum","Kızım")+", maalesef sana sığınak sağlayamam. Kaç!","Şehir muhafızları seni bulmak için şehri didik didik arıyor, "+GetSexPhrase("oğlum","kızım")+" . Kilisemin kapıları her zaman acı çekenlere açıktır, ama sana barınak veremem...",""+GetSexPhrase("Oğlum","Kızım")+", kaçmalısın! Lütfen gecikme, yalvarıyorum!"),LinkRandPhrase("Sen burada ne yapıyorsun, kayıp ruh? Askerler seni burada bulup bir katliama yol açmadan hemen çıkmanı istiyorum!","Tapınağı derhal terk et, alaycı! Senin gibi bir kötüyü asla korumam!","Efendimizin tapınağını derhal terk et! Burada katillere ihtiyacımız yok!"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Ah, yapma ama, padre...","Sana zaten ihtiyacım yok..."),LinkRandPhrase("Sadece yoluma çıkma, baba...","Gideceğim, merak etme...","Padre, telaş yapmayı bırak - gerçekten buna hiç vaktim yok"));
				link.l1.go = "fight";
				break;
			} 
            if (npchar.quest.BadMeeting != lastspeak_date)
			{
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_2.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && NPChar.location != "LosTeques_church" && rand(5) == 1 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // 280313
				{
					dialog.text = "...onlar sonsuza dek cehennemin alevlerinde yanacaklar! Asla göremeyecekler...";
					link.l1 = RandPhraseSimple("Öhö! Rahatsız mı ediyorum, padre?","İşte konuşma bu!");
					link.l1.go = "GenQuest_Church_2_Start_1";
					NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestTown") && PChar.GenQuest.ChurchQuest_2.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete"))
				{
					Dialog.Text = ""+GetSexPhrase("Oğlum","Kızım")+", seni tekrar gördüğüme sevindim!";
					link.l1 = "Ve sizi sağlıklı görmekten memnunum, Padre "+NPChar.name+"...";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1";
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.QuestTown") && PChar.GenQuest.ChurchQuest_1.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
				{
					Dialog.Text = ""+GetSexPhrase("Oğlum","Kızım")+"! Sizi tekrar sağlıklı ve keyifli görmekten memnunum. İşimizde bize Tanrı yardım etmiş olmalı, değil mi?";
					link.l1 = "Evet, "+RandPhraseSimple("padre","Kutsal Baba")+", rüzgar her zaman arkamda olmasa da, daha fazla zaman, emek ve para harcamış olsam da - göreviniz tamamlandı.";
					link.l1.go = "GenQuest_Church_1_Complete_1";
					break;
				}
				Dialog.Text = "Kutsal yuvamıza hoş geldiniz, "+GetSexPhrase("oğlum","kızım")+".";
				link.l1 = "Merhaba, kutsal Baba.";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_church")
				{
					dialog.text = "Selam, Ellen, benim çocuğum.";
					link.l1 = "Size de, Peder.";
				}
				link.l1.go = "node_3";
				Link.l2 = "Sen benim babam değilsin, bir daha asla bana o şekilde hitap etme.";
				Link.l2.go = "node_2";
				NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}
			else
			{
				Dialog.Text = "Tanrı'nın mabedini terk et, kafir! Konuşacak hiçbir şeyimiz yok!";
				Link.l1 = "Ben aslında hiç istemedim.";
				Link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "node_2":
			dialog.text = "Ah, sen kafir! Defol git! Varlığınla Rabbimizin mabedini kirletmeye kalkma sakın!";
			link.l1 = "Burada kalmaya bile niyetim yoktu.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -0.25);
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "node_3":
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_church")
			{
				dialog.text = "Jan'la olan... meşguliyetlerine rağmen, Rabbimizi ve O'nun evini unutmamış olmana sevindim. Sana nasıl yardımcı olabilirim?";
			}
			else
			{
				dialog.text = "Tanrı seni ve işlerini kutsasın... Bana özel bir sebeple mi geldin?";
			}
    		link.l1 = RandPhraseSimple("Bağış yapmak istiyorum.","İyi bir amaç için bağış yapmak istiyorum.");
    		link.l1.go = "donation";
    		link.l2 = RandPhraseSimple("Bence bir itirafta bulunmanın zamanı geldi.","İtiraf etmek istiyorum, "+RandPhraseSimple("padre.","Kutsal Baba."));
    		link.l2.go = "ispoved";
    		link.l3 = RandPhraseSimple("Seninle bir işim var, "+RandPhraseSimple("padre.","kutsal Baba."),"Bir iş için geldim, "+RandPhraseSimple("padre.","Kutsal Baba."));
    		link.l3.go = "work";
			
			//--> Сага
			// Картахена, Чика Гонсалес
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && pchar.location == "Cartahena_church" && sti(pchar.money) >= 1000)
			{
				link.l4 = "Bir hanımefendinin ruhu için bir dua ayini düzenletmek istiyorum.";
				link.l4.go = "saga";				
			}
			// поиски исцеления от заклятий
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location != "Bridgetown_church" && !CheckAttribute(npchar, "quest.seektreatment"))
			{ // все церкви, кроме Бриджтауна
				link.l4 = "Baba, yardıma ihtiyacım var. Gerçekten hastayım. Üzerime korkunç bir putperest laneti çöktü. Lütfen, yardım et, sana yalvarıyorum!";
				link.l4.go = "seektreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location == "Bridgetown_church")
			{ // попал в Бриджтаун
				link.l4 = "Baba, yardıma ihtiyacım var. Gerçekten hastayım. Üzerime uğursuz bir putperest laneti çöktü. Lütfen, yardım et, yalvarıyorum!";
				link.l4.go = "findtreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessFindTreatment") && pchar.location == "Bridgetown_church")
			{ // пришёл в Бриджтаун по направлению
				link.l4 = "Baba, yardıma ihtiyacım var. Gerçekten hastayım. Üzerime uğursuz bir putperest laneti çökmüş. Bana yardım edebilecek tek kişinin sen olduğunu söylediler. Sana yalvarıyorum...";
				link.l4.go = "findtreatment";
			}
			// исцеление от заклятий Джесс
			if(CheckAttribute(pchar, "questTemp.Saga.JessTreatment") && pchar.location == "Bridgetown_church")
			{
				link.l4 = "Baba, yardıma ihtiyacım var. Gerçekten hastayım. Üzerime uğursuz bir putperest laneti çöktü. Beni buraya gönderen... Jessica Rose oldu. Bana, bana yardım edebileceğini söyledi.";
				link.l4.go = "treatment";
			}
			if(CheckAttribute(npchar, "quest.candle"))
			{
				link.l4 = "Mumlar hakkında...";
				link.l4.go = "candle";
			}
			if(CheckAttribute(npchar, "quest.prayer") && GetNpcQuestPastDayParam(npchar, "prayer_date") >= 1 && stf(environment.time) >= 22.0)
			{
				link.l4 = "Dua etmeye hazırım, Peder.";
				link.l4.go = "prayer";
			}
			//<-- Сага
			
			// Warship, 30.05.11. Миниквест из дел чести "Divine justice".
			if(CheckAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest") && AffairOfHonor_GetCurQuest() == "GodJudgement" &&
				NPChar.city == PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId)
			{
				link.l5 = "Korkunç şeyler oluyor, kutsal Baba.";
				link.l5.go = "AffairOfHonor_GodJudgement_1";
			}
			
			link.l6 = "Affedersiniz, ama gitmem gerekiyor.";
			link.l6.go = "exit";
		break;

		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "Endişelenme, evladım. Rab senin acılarını görüyor ve sana yardım elini uzatacak. İnancını güçlendirmek için yanında daima bir haç taşı.";
			Link.l1 = "Teşekkür ederim, kutsal Baba.";
			Link.l1.go = "exit";
			AddItems(PChar, "amulet_3", 15);
			DeleteAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest");
		break;

// Jason-------------------------------------------------Сага----------------------------------------------
		//--> Чика Гонсалес
		case "saga" :
			dialog.text = "1.000 peso karşılığında isteğinizi alçakgönüllülükle yerine getireceğim.";
			Link.l1 = "Buyurun Baba, lütfen bu paraları alın.";
			Link.l1.go = "saga_1";
		break;
		
		case "saga_1" :
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Teşekkür ederim, oğlum. Hangi hanımefendinin ruhu için dua etmemi istersin, adı nedir?";
			Link.l1 = "Adı Chica Gonzales'tı, bu dünyadan yıllar önce göçüp gitti.";
			Link.l1.go = "saga_2";
		break;
		
		case "saga_2" :
			dialog.text = "Bu garip... Alvarez'e bir şey mi oldu, yoksa sana bundan mı bahsetti?";
			Link.l1 = "Bu Alvarez de kim, ve isteğimde tuhaf olan ne var?";
			Link.l1.go = "saga_3";
		break;
		
		case "saga_3" :
			dialog.text = "Vay vay! Yirmi yıldır fenerimizi koruyan Alvarez, her ay bu hanımefendinin ruhu için bir dua ayini düzenler. Ondan başka kimse Lady Gonzales’i umursamadı. Şimdi de siz geldiniz. Öyle düşündüm. Neyse, bu benim işim değil. Tabii ki, kayıp ruhun huzur bulup cennete giden yolu bulmasına yardımcı olmanız için isteklerinizi memnuniyetle yerine getireceğim.";
			Link.l1 = "Teşekkür ederim, kutsal Baba.";
			Link.l1.go = "saga_4";
		break;
		
		case "saga_4" :
			DialogExit();
			if(CheckAttribute(pchar,"questTemp.Saga7"))
			{
				AddQuestRecord("Saga", "151");
				DeleteAttribute(pchar,"questTemp.Saga7");
			}
			else AddQuestRecord("Saga", "15");
			Saga_SetOrtega();
			pchar.questTemp.Saga = "ortega";
			pchar.quest.Saga_Gonsales1.over = "yes"; //снять возможное прерывание
			if (GetCharacterIndex("SagaGonsalesB") != -1)
			{
				sld = characterFromId("SagaGonsalesB");
				sld.lifeday = 0;
			}
		break;
		
		// belamour участвовал в событиях Картахены
		case "saga_5" :
			dialog.text = "Başka birinin ruhu için de bir ağıt istemek ister misiniz?";
			Link.l1 = "Mmm... Hayır, sanmıyorum. Başkası için sipariş vermem mi gerekiyor?";
			Link.l1.go = "saga_6";
		break;
		
		case "saga_6" :
			dialog.text = "Belki de, bu talihsiz şehri yağmalarken senin ya da tanrısız yoldaşlarının ellerinde can veren yüzlerce masum insan için?.. Yine de, alçakgönüllü bir rahibin, masum ve huzurlu vatandaşları acımadan öldüren bir adamın vicdanına ulaşmayı umması pek olası değil...";
			Link.l1 = "Baba, anlamıyorsun... Bunların hepsi geçmişte kaldı. Şu anda ve burada, kimseye zarar vermek gibi bir niyetim yok.";
			Link.l1.go = "saga_7";
		break;
		
		case "saga_7" :
			pchar.questTemp.saga7 = true;
			dialog.text = "Sana güvenebilir miyim...? Ama her halükarda, burası kanla kirletilmemesi gereken kutsal bir yer. Bu yüzden muhafızları çağırmayacağım. Huzur içinde git. Belki de Tanrı'nın huzuruna çıkmadan önce, en azından bazı günahlarının kefaretini ödeme fırsatın olur.";
			Link.l1 = "Belki. Tanrı'nın isteği olsun.";
			Link.l1.go = "saga_4";
		break;
		// <-- Чика Гонсалес
		
		// --> исцеление от заклятий
		case "treatment":
			dialog.text = "Jessica mı? Onu hatırlıyorum. Zavallı günahkâr. Ama o ölmemiş miydi?";
			link.l1 = "Öldü, kutsal Baba. Şimdi o öldü, Tanrı ruhunu huzura erdirsin. Ama bana, bana yardım edebileceğinizi söyledi.";
			link.l1.go = "treatment_1";
			DeleteAttribute(pchar, "questTemp.Saga.JessTreatment");
		break;
		
		case "treatment_1":
			dialog.text = "Bu büyüleri sana kim yaptı, oğlum? Bana dürüstçe söyle.";
			link.l1 = "O... o yaptı. Jessica.";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "Tanrı bizi korusun! Ben de öyle düşündüm. Putperest ayinlere dalmak, en güçlü ruhları bile karanlığın uçurumuna sürükleyebilir... Ama... gerçekten öldü mü? Yoksa... tamamen değil mi?";
			link.l1 = "Gerçekten çok zekisiniz, Peder. Artık o gerçekten öldü.";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			dialog.text = "Bu zavallı günahkâr bana defalarca günah çıkardı. Nefret, onu içten içe tamamen mahvetmişti. Ne peşinde olduğunu biliyordum. Onu durdurmaya çalıştım, doğru yola yönlendirmek istedim ama tüm çabalarım boşa gitti. Onu bu kutsal olmayan işlerinin korkunç tehlikeleri ve ağır sonuçları konusunda uyardım...";
			link.l1 = "Evet, kutsal Baba. Gördüklerim gerçekten korkunçtu. Ama... nasıl iyileşebilirim?";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "Duanın gücüyle, evladım. Tapınağımızda yapılan kutsal arınma duasının gücüyle. Çok uzun süre dua etmen gerekecek, hem kendin hem de onun için dua etmelisin.";
			link.l1 = "Jessica için mi?";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "Evet. Kendin ve onun ruhu için. Gece onda buraya gel, kimse seni rahatsız etmesin. Tüm gece boyunca dua etmen gerekecek. Yanında yirmi kalın mum getir, hepsini yak ve hepsi bitene kadar dua et.";
			link.l1 = "Ve sonra iyileşecek miyim?";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "Her şey Rabbin ellerinde. Sana nasıl dua edeceğini öğreteceğim ve Kutsal Kitap'ı sana bırakacağım. Kutsal duanın gücü, başına gelen kötü büyüleri yok edecek ve zavallı Jessica'nın ruhunu da arındıracak.";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "Yanımda yirmi balmumu mum var. Tapınakta kalmaya ve dua etmeye hazırım.";
				link.l1.go = "treatment_9";
			}
			else
			{
				link.l1 = "Henüz yanımda yirmi mum yok. Onları bulacağım!";
				link.l1.go = "treatment_7";
			}
		break;
		
		case "treatment_7":
			dialog.text = "Pekâlâ, oğlum. Seni bekliyor olacağım. Zaman kaybetme!";
			link.l1 = "Yakında burada olacağım...";
			link.l1.go = "treatment_8";
		break;
		
		case "treatment_8":
			DialogExit();
			npchar.quest.candle = "true";
		break;
		
		case "candle":
			dialog.text = "Yirmi mum getirdin mi, evladım?";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "Evet, Peder. Yanımda yirmi balmumu mum var. Tapınakta kalmaya ve dua etmeye hazırım.";
				link.l1.go = "treatment_9";
				DeleteAttribute(npchar, "quest.candle");
			}
			else
			{
				link.l1 = "Henüz değil - ama onları ne pahasına olursa olsun alacağım.";
				link.l1.go = "exit";
			}
		break;
		
		case "treatment_9":
			dialog.text = "Peki, oğlum. Onları bana ver ve yarın akşam saat ondan sonra tekrar gel. Sana gerekli duaları öğreteceğim ve geceyi kilisede geçirmen için seni burada bırakacağım.";
			link.l1 = "Teşekkür ederim, kutsal Baba. Yarın görüşürüz!";
			link.l1.go = "treatment_10";
		break;
		
		case "treatment_10":
			DialogExit();
			RemoveItems(pchar, "mineral3", 20);
			LAi_RemoveLoginTime(npchar);
			LAi_SetLoginTime(npchar, 6.0, 22.99);
			npchar.quest.prayer = "true";
			SaveCurrentNpcQuestDateParam(npchar, "prayer_date");
		break;
		
		case "prayer":
			dialog.text = "I have prepared the texts of the prayers for you , my son. I also left your twenty candles and the Holy Scripture. Light the candles and start praying. Pray without a stop; pray for your recovery and for the soul of this poor sinner Jessica. If you forget something or if you don't understand something - it doesn't really matter. Pray from your heart, your sincere desire is what matters to our Lord.";
			link.l1 = "Teşekkür ederim, Baba. Anladım.";
			link.l1.go = "prayer_1";
		break;
		
		case "prayer_1":
			dialog.text = "Sabah geri döneceğim. Senin için de dua edeceğim...";
			link.l1 = "Teşekkür ederim, kutsal Baba.";
			link.l1.go = "prayer_2";
		break;
		
		case "prayer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_BarbadosTreatment", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "seektreatment":
			dialog.text = "Sana hangi putperest büyüler musallat oldu, oğlum?";
			link.l1 = "I don't know how they are called. I am weak and sluggish; I cannot run around, and it is very difficult for me to fight.";
			link.l1.go = "seektreatment_1";
		break;
		
		case "seektreatment_1":
			if (sti(pchar.questTemp.Saga.JessSeekTreatment) == 3)
			{
				dialog.text = "Onlardan duydum... Bu dünyaya, o kızıl tenli putperestlerin lanetli cadıları tarafından getirildiler. Sana Bridgetown’daki kilisenin başrahibiyle konuşmanı tavsiye ederim – Hintlilerin lanetlerinin Hristiyanların bedenleri ve ruhları üzerindeki kötü etkilerini yıllardır inceliyor.";
				link.l1 = "Ve bana yardım edebilecek mi?!";
				link.l1.go = "seektreatment_4";
			}
			else
			{
				dialog.text = "Onlardan duydum... Bu kırmızı tenli putperestlerin lanetli cadıları tarafından dünyamıza getirildiler. Ne yazık ki sana verebileceğim tek tavsiye, daha çok dua etmen, evladım, ve umudunu Rabbimizin merhametine bağlamandır.";
				link.l1 = "Ama gerçekten de bunun için hiçbir şey yapılamaz mı, Baba?! Ben böyle... hayatımın sonuna kadar mı kalacağım?";
				link.l1.go = "seektreatment_2";
			}
		break;
		
		case "seektreatment_2":
			dialog.text = "Umutsuzluğa kapılma, oğlum. Rab seni duyacak ve sana yardım gönderecek. Ama sana tavsiyem, başka kutsal mekanlarda da sorup soruşturman olurdu – belki de putperest lanetleri kaldırmayı bilen rahipler vardır.";
			link.l1 = "Teşekkür ederim, Peder! İyileşeceğim – gerekirse takımadadaki her kiliseyi ziyaret ederim!";
			link.l1.go = "seektreatment_3";
		break;
		
		case "seektreatment_3":
			dialog.text = "Git oğlum, Tanrı seni korusun.";
			link.l1 = "Hoşça kal, padre.";
			link.l1.go = "exit";
			npchar.quest.seektreatment = "true";
			pchar.questTemp.Saga.JessSeekTreatment = sti(pchar.questTemp.Saga.JessSeekTreatment)+1;
		break;
		
		case "seektreatment_4":
			dialog.text = "Yalnızca Tanrı ve sen kendin yardım edebilirsin, oğlum. Bir rahip sana sadece ne yapman ve nasıl yapman gerektiğini öğretebilir. Gel, onunla konuş.";
			link.l1 = "Teşekkür ederim, padre! Beni kurtardınız! Hemen Barbados'a yelken açacağım!";
			link.l1.go = "seektreatment_5";
		break;
		
		case "seektreatment_5":
			dialog.text = "Şimdi git, Tanrı seni korusun.";
			link.l1 = "Elveda, Baba.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment");
			pchar.questTemp.Saga.JessFindTreatment = "true";
		break;
		
		case "findtreatment":
			dialog.text = "Sana hangi putperest lanetler musallat oldu, oğlum? Dur tahmin edeyim: koşamıyorsun, kılıç sana ağır geliyor ve hareketlerin yavaş, hantal mı?";
			link.l1 = "Bunu nasıl bildin, Baba?";
			link.l1.go = "findtreatment_1";
		break;
		
		case "findtreatment_1":
			dialog.text = "Bunu görmek zor olmadı, bana yaklaşırken adımlarından belliydi, oğlum. Rabbimiz günahkâr ruhlarımıza merhamet etsin... Söyle bana, oğlum, dürüst ol - bu büyüleri sana kim yaptı?";
			link.l1 = "Bir isme mi ihtiyacınız var, Peder?";
			link.l1.go = "findtreatment_2";
		break;
		
		case "findtreatment_2":
			dialog.text = "Adını biliyorsan, söyle o zaman.";
			link.l1 = "Adı... Jessica Rose'du.";
			link.l1.go = "findtreatment_3";
		break;
		
		case "findtreatment_3":
			dialog.text = "Tanrı bizi korusun! Putperest ayinlerine dalmak, en güçlü ruhları bile karanlığın uçurumuna sürükleyebilir... Ona, bu zavallı ruha ne oldu?";
			link.l1 = "Öldü, baba.";
			link.l1.go = "findtreatment_4";
		break;
		
		case "findtreatment_4":
			dialog.text = "Ama... gerçekten öldü mü? Yoksa... tamamen değil mi?";
			link.l1 = "Gerçekten çok bilge birisiniz, kutsal Baba. Artık o gerçekten öldü.";
			link.l1.go = "treatment_3";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment"); // если было
			DeleteAttribute(pchar, "questTemp.Saga.JessFindTreatment"); // если было
		break;
		//<-- Сага
		
		// Church GenQuest_2 -->	
		case "GenQuest_Church_2_Start_1":
			dialog.text = "...ve Rabbin merhameti! Evrensel karanlık, günahları için ruhlarını yutsun...";
			link.l1 = LinkRandPhrase("Kutsal Baba","Padre","Baba")+", biraz fazla mı heveslisin? Biliyorsun, inme geçirebilirsin...";
			link.l1.go = "GenQuest_Church_2_Start_2";
			link.l2 = "Pekâlâ... kahretsin. O zaman elveda.";
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_2":
			dialog.text = "Oh, "+GetSexPhrase("oğlum","kızım")+", korkunç bir kutsal saygısızlık, en iğrenç suçlardan biri az önce işlendi! Kiliseden hırsızlık!!! Bu, sanki bizzat Tanrı'nın cebine elini sokmak gibi!";
			link.l1 = "Anladım... Nasıl oldu?";
			link.l1.go = "GenQuest_Church_2_Start_3";
			link.l2 = LinkRandPhrase("Çok üzücü, anlıyorum, ama gerçekten gitmem gerekiyor...","Başınız sağ olsun, padre, ama artık gitmem gerek...","Herhalde kendini fazla Tanrı'ya emanet ettin. Daha sağlam kilitler kullansaydın iyi olurdu. Neyse, gitmem gerek...");
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_3":
			dialog.text = "Gece karanlığında bazı alçaklar, cemaatin topladığı her şeyi çaldı! Bu kafirler adak kâsesini bile götürmüş!";
			link.l1 = "O tempora, o mores... Ama umarım izler hâlâ sıcakken bir şeyler yapmaya başlamışsındır?";
			link.l1.go = "GenQuest_Church_2_Start_4";
		break;
			
		case "GenQuest_Church_2_Start_4":
			dialog.text = "Elbette! Bu küfürbaz haydutları aforoz ettim ve şimdi de üzerlerine lanet okuyorum!";
			link.l1 = "Bunun son derece etkili bir önlem olduğundan şüphem yok. Ama ben daha pratik bir şey kastetmiştim. Mesela bir takip organize etmek gibi.";
			link.l1.go = "GenQuest_Church_2_Start_5";
		break;
			
		case "GenQuest_Church_2_Start_5":
			dialog.text = "Ah, kötülüğe karşı koymamaya yemin etmiş basit bir rahip olarak ne yapabilirim ki? Bu alçaklar kesinlikle çoktan buralardan uzaklaştı, ya meyhanelerde soygundan elde ettikleri ganimetle içip âlemlere daldılar ya da düşmüş kadınların arasında sefahate ve rezilliğe kapıldılar! Umarım sonlarını orada bulurlar!";
			link.l1 = RandPhraseSimple("Böyle bir sonun asılmaktan çok daha cazip olduğuna eminim. Yine de sizi daha fazla oyalamayacağım. Her şey gönlünüzce olsun.","Pekâlâ, er ya da geç bir gün hepimiz atalarımıza kavuşacağız, ama onların işinin daha çabuk bitmesine hayır demezdim. Yine de gitmem gerek. İyi şanslar.");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Kutsal Baba","Padre","Baba")+", ama hiçbir yeminle bağlı değilim ve hazır bir şekilde Rab'bin intikam zamanını getirmesine yardımcı olacağım.";
			link.l2.go = "GenQuest_Church_2_Start_5_1";
		break;
		
		case "GenQuest_Church_2_Start_5_1": //выше - выход из диалога без подтверждения - странно, однако
			dialog.text = "Senin için dua edeceğim, oğlum! Şimdi git ve bu dolandırıcılara hak ettiklerini göster!";
			link.l1 = "Hiç şüpheniz olmasın, Padre";
			link.l1.go = "GenQuest_Church_2_Start_6";
		break;
			
		case "GenQuest_Church_2_Start_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_2.StartQuest = true;
			PChar.GenQuest.ChurchQuest_2.QuestTown = NPChar.City;	// Город, в котором спрашиваем
			PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_2.IslandId = locations[FindLocation(NPChar.location)].islandId; // На каком острове опрашиваем бандюков
			PChar.GenQuest.ChurchQuest_2.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_2.AskPeople = true;
			PChar.GenQuest.ChurchQuest_2.AskBarmen = true;
			PChar.GenQuest.ChurchQuest_2.AskAlcash = true;
			PChar.GenQuest.ChurchQuest_2.MoneyCount = (sti(pchar.rank)+8)*543+3210;
			PChar.GenQuest.ChurchQuest_2.MoneyToCharacter = makeint(sti(PChar.GenQuest.ChurchQuest_2.MoneyCount)/3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
		break;
			
		case "GenQuest_Church_2_Thief_2":
			dialog.text = "Pekâlâ, belki de her şeyi bilen Yaratıcı, aptal çocuklarına günahlarının cezası olarak veba ve açlık gönderiyordur...";
				link.l1 = "Gurur için mesela, ya da açgözlülük... Neden solgunlaştınız, padre?";
				link.l1.go = "GenQuest_Church_2_Thief_3";
			break;
			
		case "GenQuest_Church_2_Thief_3":
			if(rand(1) == 0) // Священник искренне раскаивается...
			{
				dialog.text = "İsa, Rabbim, günahkâr kuluna merhamet et... Onları... Soyguncuları buldun mu? Onları öldürdün mü?";
					link.l1 = "Her iyi Hristiyanın beşikten itibaren bildiği On Emir’i hatırlayalım: öldürmeyeceksin, çalmayacaksın, yalan yere şahitlik etmeyeceksin. Tanrı’dan korkan biri bunları çiğneyebilir mi—hele ki bir ruhani din adamı...?!";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_1";
			}
			else
			{
				dialog.text = "Burada hava çok ağır... Peki, haydutları buldun mu? Onları öldürdün mü?";
					link.l1 = "Her iyi Hristiyanın beşikten itibaren bildiği On Emir’i hatırlayalım: öldürmeyeceksin, çalmayacaksın, yalan yere şahitlik etmeyeceksin. Tanrı’dan korkan biri bunları çiğneyebilir mi – hele ki bir ruhani rahip?!..";
					link.l1.go = "GenQuest_Church_2_Thief_4_2_1";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_1_1":
			dialog.text = ""+GetSexPhrase("Oğlum","Kızım")+"... Tanrı beni affetsin... böyle bir para, böyle bir ayartı... insan zayıf, gerçekten çok zayıf! Dayanamadım... aklım başımda değildi... gece gündüz dua ettim, tövbe ettim, sıkı oruç tuttum, nefsimi kırdım... Değersiz biri olarak, yalnızca kendi açgözlülüğümle ayarttığım o zavallı adamların bağışlanması için göklere yalvardım...";
			link.l1 = LinkRandPhrase("Baba","Padre","Baba")+", sakin ol. Bu konuda hiçbir şey söylemediler... ve emin ol, söylemeyecekler de. Bu arada, bana gönüllü olarak Komünyon kadehini geri verdiler, ben de onu sana geri getirdim.";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_2":
			dialog.text = "Rabbim, Sana şükürler olsun! Tanrım, değersiz kulunun, günaha batmış, pislik ve sefahat içinde kaybolmuş dualarını duydun...";
			link.l1 = "Her insan hata yapabilir... Ama tövbenin samimi görünüyor, bu yüzden şunu söyleyebilirim: sen iyi bir adamsın ve iyi bir rahipsin. Mahkeme önüne çıkarsan, bundan iyi bir şey çıkmaz. Rabbin hizmetinde kalıp kalmamaya ise sen karar vereceksin – bunu sana ancak O söyleyebilir ve yol gösterebilir...";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_3":
			if(rand(1) == 0) // Священник хочет всучить ГГ бабло
			{
				dialog.text = ""+GetSexPhrase("Oğlum","Kızım")+"... Pişmanlık ve minnettarlık gözyaşlarıyla, bu kadehi sizden kabul edeceğim. Ruhunuzun saflığı ve asaletiniz beni derinden etkiledi. Sizi tüm kalbimle kutsuyorum ve lütfen bu küçük armağanı kabul etmenizi rica ediyorum. "+FindRussianMoneyString(iMoneyToCharacter)+"... Umarım masraflarınızı karşılamaya yeter?";
				// ГГ не берёт деньги. Плюсанем репу
				link.l1 = "Bu gereksiz, Kutsal Baba "+NPChar.name+". Ben pek de fakir sayılmam, bu yüzden bu parayı cemaatinizin iyiliği için kullanmanız daha iyi olur.";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				// ГГ берёт деньги
				link.l2 = "Teşekkür ederim, "+LinkRandPhrase("Baba","padre","Kutsal Baba")+", bu fazlasıyla yeterli.";
				link.l2.go = "GenQuest_Church_2_Thief_4_1_5";
			}
			else
			{
				dialog.text = ""+GetSexPhrase("Oğlum","Kızım")+"... Pişmanlık ve minnettarlık gözyaşlarıyla, bu kadehi Rab'bin merhameti ve affının bir işareti olarak sizden kabul edeceğim. Ruhunuzun saflığı ve asaletiniz beni gerçekten derinden etkiledi. Sizi bütün kalbimle kutsuyorum!";
				link.l1 = "Bu iyiliğiniz için teşekkür ederim, "+LinkRandPhrase("padre.","Baba.")+".";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				link.l1 = "Kutsama elbette gerekli, ama bu kadar büyük masraflara girdiğimi düşünürsek, bunu biraz daha somut bir şeyle desteklemek fena olmazdı...";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_6";
			}
			ChurchGenQuest2_RemoveCup();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_2");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6":
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = "Ah, evladım, gerçekten üzgünüm... Umarım bu küçük katkım "+FindRussianMoneyString(iMoneyToCharacter)+" masraflarını karşılamaya yeter mi?";
			link.l1 = "Evet, "+LinkRandPhrase("padre.","Baba.")+", bu kadar yeter, teşekkür ederim.";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_6_1";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_3");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_1":
			dialog.text = "İmalarınızı tam olarak anlamıyorum, "+GetSexPhrase("oğlum","kızım")+", ne diyorsun sen?!";
			link.l1 = "Açgözlülüğün bir insana neler yaptırabileceğinden ve kilisenizi soyduğu iddia edilen serserilerden bahsediyorum... Söylemek istediğiniz bir şey var mı?";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_2":
			dialog.text = "Sana şunu söyleyeyim evlat, karşında bir din adamı var ve biraz daha saygılı olmalısın, yoksa pişman olabilirsin. Bu kadehe gelince - daha önce hiç görmedim, ama bunu cemaate bağışlamaya gönüllüysen...";
			link.l1 = "Sakin ol, padre. Kendini açıklamadan bunu alamazsın.";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_3":
			if(rand(1) == 0) // Просто несколько разные варианты диалога
			{
				dialog.text = "Açıklanacak ne var ki?! Bak şimdi - sen bir "+GetSexPhrase("zeki adam","zeki kız")+", ve elbette bu haydutların sana ne anlatmış olurlarsa olsunlar – güya onları ben tutmuşum – bu apaçık bir yalan! Tanrı bu kafirleri sadece kutsala saygısızlık ettikleri için değil, aynı zamanda yalan yere şahitlik ettikleri için de cezalandıracaktır!";
				link.l1 = "Tanrı'yı rahat bırak! O zavallı insanların bana ne söylediğini sen nasıl bilebilirsin ki – hani beni onlara karşı kışkırttığın kişiler? Belki de bana seninle ilgili kötü bir şey söylemeye fırsatları olmadan onları öldürdüm?";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1";
			}
			else
			{
				dialog.text = "There's nothing for me to talk about with you! You haven't fulfilled your obligation in the face of our Lord; you're swearing at the temple; you're attempting to blackmail a priest, displaying some church utensils - and it remains yet to be seen how you got it! Thank the God that I am not calling the acolytes to catch you red-handed!";
				link.l1 = "Pekâlâ... Günah bataklığına öyle bir batmışsın ki artık insanların yargısından korkmuyorsun. Ama ilahi adalet hâlâ var ve hepimiz er ya da geç onun önünde hesap vereceğiz. Al şu 'kilise eşyalarını' ve düşün bakalım, onlara dokunmaya layık mısın, Peder "+NPChar.name+".";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_2_1";
				link.l2 = "Lütfen şüphelerimi bağışla, Baba, çünkü ölümlü bir kalp zayıftır ve ruh karmaşıktır. Lütfen kadehi al ve bana kutsamanı ver.";
				link.l2.go = "GenQuest_Church_2_Thief_4_2_4_2_2";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1":
			dialog.text = "Mmmm... "+GetSexPhrase("Oğlum... Beyefendi... Efendim...","Kızım... Hanımefendi... Bayan...")+" "+PChar.name+"... Size boyun eğmeye hazırım... ve anlaşmazlıklarımızı konuşmaya, tabiri caizse... ve masraflarınızı bu mütevazı meblağ ile telafi etmeye hazırım "+FindRussianMoneyString(iMoneyToCharacter)+"... tabii ki, eğer bu işe başkalarını karıştırmayacaksanız ...";
			// При этом варианте репу плюсуем
			link.l1 = "Kimseyi bu işe karıştırmayacağım. Al şu kadehi! Ve sakın ha, cemaatinin ceplerinden gizlice aşırdığın altınları kabul edeceğimi düşünme bile!";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1_1";
			// При этом - минусуем
			link.l2 = "Kimseyi karıştırmayacağım. Al bu kadehi! Bu altını sadece sana çok zaman ve para harcadığım için alıyorum.";
			link.l2.go = "GenQuest_Church_2_Thief_4_2_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex2", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoneyToCharacter));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1":
			// ничего не принесли священнику.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Without_All"))
			{
				link.l1 = "Kötü haberler, "+LinkRandPhrase("Baba","Padre","Baba")+": haydutlar çok kurnaz ve hain çıktılar, bu yüzden kilisenin altınlarını geri alamadım...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_1";
				break;
			}
			// Принесли священнику только чашу.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Only_With_Cup"))
			{
				link.l1 = "Kötü haberler, "+LinkRandPhrase("Baba","Padre","Baba")+": Soygunculara yetişmeyi başardım, ama tek ganimetim bu kadeh oldu.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// Принесли священнику и деньги и чашу.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.With_All"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "Eminim bu haber hoşuna gidecek – soyguncuları hak ettikleri gibi cezalandırdım ve hem cemaatin parasını hem de bu kutsal kâseyi onlardan aldım.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = LinkRandPhrase("Baba","Padre","Baba")+", Kötü haberlerim var... O alçakların peşine düşmek için çok zaman, emek ve kaynak harcadım, ama sonunda bulduğumda, her şeyi içip savurmuşlar, geriye sadece bu kadeh kalmış...";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// Священник - вор.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.PriestIsThief"))
			{
				dialog.text = "Oh, "+GetSexPhrase("oğlum","kızım")+", bana ne olmuş olabilir ki? Tehlikeler ve endişelerle dolu olan senin yolun, oysa benim huzurlu hücrem, düşünce ve dua ile geçen bir sığınak, insan tutkularının kudurmuş okyanusunda sessiz bir ada...";
					link.l1 = "Ve hiçbir şey huzurlu yalnızlığının dinginliğini bozamaz mı?";
					link.l1.go = "GenQuest_Church_2_Thief_2";
				break;
			}
			// Короткий вариант прохождения квеста.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Short_With_Mon"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "Eminim bu haber sizi mutlu edecektir - haydutları cezalandırdım ve cemaatin parasını geri getirdim.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = LinkRandPhrase("Baba","Padre","Baba")+"... Sizi hayal kırıklığına uğratmak zorundayım. Tüm takımadaları boyunca haydutların peşine düştüm, sayısız tehlike ve engeli aştım, neredeyse kendimi mahvettim ve sonunda onlara yetiştim, ama ne yazık ki... kilisenin parasını çoktan harcamışlardı.";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1": // ГГ решил заныкать деньги...
			if(rand(1) == 0)	// Священник верит ГГ но не даёт денег...
			{
				if(rand(4) == 3) // Более "мягкий" исход событий.
				{
					dialog.text = "Oh, "+GetSexPhrase("oğlum","kızım")+". Sözlerin beni derin bir kedere sürükledi - ama umutsuzluğa değil, çünkü umutsuzluk ölümcül bir günahtır! Rabbimiz, inancımızı güçlendirmek için bize yeni bir sınav verdi.";
						link.l1 = "Amin, Peder...";
						link.l1.go = "exit";
						sQuestTitle = NPChar.City + "ChurchGenQuest2";
						AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_9");
						AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
						CloseQuestHeader(sQuestTitle);
						ChangeCharacterComplexReputation(PChar,"nobility", -2);
						DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
						NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
				}
				else
				{
					dialog.text = ""+GetSexPhrase("Oğlum","Kızım")+", ruhani çobanına yalan söyleme.";
						link.l1 = "Gerçekten üzgünüm, Baba, ama yemin ederim ki doğruyu söylüyorum.";
						link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3";
				}
			}
			else
			{
				// Священник даёт деньги ГГ...
				iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
				dialog.text = "Oh, "+GetSexPhrase("oğlum","kızım")+"  Sözleriniz beni derin bir kedere sürükledi - ama umutsuzluğa değil, çünkü umutsuzluk ölümcül bir günahtır! Tanrı, inancımızı güçlendirmek için önümüze yeni bir sınav koydu. Fakat çabalarınız ve harcamalarınız, sonuçsuz da olsa, karşılıksız kalmamalı. Lütfen, bu mütevazı meblağı kabul edin - "+FindRussianMoneyString(iMoneyToCharacter)+" - ve doğru yolunda devam et!";
					link.l1 = "Hmm!... Teşekkür ederim, padre, bu parayı erdemli bir amaç için kullanacağım.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_1";
					link.l2 = LinkRandPhrase("Baba","Padre","Baba")+"... Henüz yapmadığım bir iş için ödül kabul edemem. Bu parayı sunağı onarmak için kullanmanız daha iyi olur.";
					link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1_2";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3":
			if(rand(6) == 3)
			{
				dialog.text = "Pekâlâ, sana inanıyorum, "+GetSexPhrase("oğlum","kızım")+". Tanrı, inancımızı güçlendirmek için bize bir sınav daha gönderdi.";
				link.l1 = "Amin...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_1"
				break;
			}
				dialog.text = "Alçakça! Gerçekten de Efendimizi kandırabileceğini mi sandın?! Sana lanet olsun"+GetSexPhrase(", alçak",", kadın")+"! Defol, ve unutma ki bu para sana hiçbir fayda getirmeyecek!";
				link.l1 = "Nasıl yani?! Padre!..";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_2";
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			ChangeCharacterComplexReputation(PChar,"nobility", -3);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			ChangeCharacterComplexReputation(PChar, "nobility", -6);
			AddCharacterExpToSkill(PChar, "Leadership", -50);
			AddCharacterExpToSkill(PChar, "Fortune", -70);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			npchar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1":
			if(rand(1) == 0) // Поверил.
			{
				dialog.text = "Oh, "+GetSexPhrase("oğlum","kızım")+". Sözlerin beni derin bir kedere sürükledi - ama umutsuzluğa değil, çünkü umutsuzluk büyük bir günahtır! Rabbimiz, inancımızı güçlendirmek için önümüze yeni bir sınav koydu.";
				link.l1 = "Amin, Peder...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2"; // Переход сюда, т.к. одно и тоже.
			}
			else
			{
				dialog.text = "Evet, çalınan o kadeh tam da bu işte, parayla birlikte götürülmüştü... Ama... Eğer o sende, neden parayı da geri getirmedin? Yüklü bir miktardı, o hergeleler hepsini bu kadar çabuk harcamış olamazlar... "+GetSexPhrase("Oğlum","Kızım")+", unutma ki ruhani çobanına yalan söylemek ve Tanrı'nın huzurunda tapınakta yalan yere şahitlik etmekten daha büyük bir günah yoktur!";
				link.l1 = "Kutsal Baba "+NPChar.name+", Bu vazoyu alabilmek için neredeyse canımdan oluyordum, seni mutlu etmek için. Harcadığım paradan ise hiç bahsetmiyorum bile!";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2";
			}
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2":
			dialog.text = "Dışarı çık ve bana yumuşak bir kalp verdiği için Yüce Allah’a şükret. Hâlâ hırsız ve düzenbaz olarak damgalanmamış olmanın tek sebebi bu!";
			link.l1 = "Bu nasıl yani?! "+LinkRandPhrase("Kutsal Baba","Padre","Baba")+"!..";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2_1";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -5);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_12");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, iMoneyToCharacter);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -1);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_11");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_1":
			dialog.text = "Oh, "+GetSexPhrase("oğlum","kızım")+". Sözlerin beni derin bir kedere sürükledi - ama umutsuzluğa değil, çünkü umutsuzluk büyük bir günahtır! Rabbimiz, inancımızı güçlendirmek için önümüze yeni bir sınav koydu.";
			link.l1 = "Amin, Baba...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_8");
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_1":
			dialog.text = "Tanrım, sana şükürler olsun! Gerçekten de O'nun aracı oldun, evladım! Cennetteki Babamızın sana yol göstereceğini ve ihtiyaç duyduğun her türlü yardımı sağlayacağını biliyordum. Hiç durmadan dua ediyordum ve...";
			link.l1 = "Biliyor musun, padre, böyle durumlarda silahlar dualardan çok daha işe yarar. Ama anlaşılan, duaların gerçekten de duyulmuş.";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_2":
			dialog.text = ""+GetSexPhrase("Oğlum","Kızım")+", sana layık olduğun bir ödül vermek istiyorum, sen"+GetSexPhrase(",   gerçek bir Ana Kilise şövalyesi gibi, ","")+"Tüm gücümle üstesinden gelmeye çalıştım...";
			link.l1 = "Padre, mütevazı başarılarımı gerçekten abartıyorsunuz. Şimdi sizi Rabbimizi övmeye bırakıyorum...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_3";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_2.MoneyCount));
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
		// <-- квесты церкви

		case "donation":
			dialog.Text = "Elbette, "+GetSexPhrase("oğlum","kızım")+" . Kutsal Kilise'ye ne kadar bağış yapmak istersiniz?";
			Link.l1 = "Üzgünüm, kutsal Baba, ama fikrimi değiştirdim.";
			Link.l1.go = "No donation";
			if(makeint(PChar.money)>=100)
			{
				Link.l2 = "Bağışım mütevazı olacak - sadece 100 peso.";
				Link.l2.go = "donation paid_100";
			}
			if(makeint(PChar.money)>=1000)
			{
				Link.l3 = "1000 peso. Sanırım bu yeterli olacaktır.";
				Link.l3.go = "donation paid_1000";
			}
			if(makeint(PChar.money)>=5000)
			{
				Link.l4 = "Parayla şanslıyım, bu yüzden 5.000 peso bağışlayacağım.";
				Link.l4.go = "donation paid_5000";
			}
			//-->> квест пожертвования хозяйки борделя
			if(pchar.questTemp.different == "HostessChurch_toChurch" && pchar.questTemp.different.HostessChurch.city == npchar.city && sti(pchar.money) >= sti(pchar.questTemp.different.HostessChurch.money))
			{
				Link.l5 = "Baba, bu bağışı kendi adıma değil, birinin isteği üzerine yapmak istiyorum.";
				Link.l5.go = "HostessChurch";
			}
			//<<-- квест пожертвования хозяйки борделя
		break;

		case "No donation":
			dialog.Text = "Hmm... Bu senin kararın, fikrini değiştirmekte özgürsün. Ve unutma, bunun hesabı Kıyamet Günü'nde sorulacak.";
			Link.l1 = "Birçok şey de öyle olacak. Konuyu değiştirelim.";
			Link.l1.go = "node_3";
			Link.l2 = "Üzgünüm, Baba, ama gitme vaktim geldi.";
			Link.l2.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = "Kutsal Kilise adına size teşekkür ederim, "+GetSexPhrase("oğlum","kızım")+", hediyeniz için.";
			Link.l1 = "Seninle konuşmam lazım, Baba.";
			Link.l1.go = "node_3";
			Link.l2 = "Üzgünüm, Baba, ama gitme zamanım geldi.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = "Kutsal Kilise adına size teşekkür ederim.";
            Link.l1 = "Seninle konuşmam lazım, Baba.";
			Link.l1.go = "node_3";
			Link.l2 = "Üzgünüm Baba, ama gitme vaktim geldi.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = "Kutsal Kilise adına, hediyeniz için size teşekkür ederim.";
            Link.l1 = "Seninle konuşmam gerek, Baba.";
			Link.l1.go = "node_3";
			Link.l2 = "Üzgünüm Baba, ama artık gitme zamanım geldi.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "ispoved":
			dialog.text = "Elbette, "+GetSexPhrase("oğlum","kızım")+", seni dinliyorum.";
			link.l1 = "Fikrimi değiştirdim. Belki bir dahaki sefere.";
			link.l1.go = "exit";
			link.l2 = "Günahlarım o kadar çok ki, Peder. Bütün kötülüklerimi saymaya bir gün yetmez...";
			link.l2.go = "ispoved_1";
		break;

		case "ispoved_1":
			dialog.text = "Hepimiz günahkârız, evladım...";
			link.l1 = "Evet, ama vicdanımda binlerce ölümün yükü ağır bir yük. Gemileri soydum ve batırdım...";
			link.l1.go = "ispoved_2";
		break;

		case "ispoved_2":
			dialog.text = "Umarım o bayrak altında yelken açanlar arasında kimse yoktu "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Hayır, tabii ki değil, Baba.";
			link.l1.go = "ispoved_3";
			link.l2 = "Her türlüsü var, Baba...";
			link.l2.go = "ispoved_4";
		break;

		case "ispoved_3":
			dialog.text = "O zaman Rabbimiz seni bu günahlardan arındıracak. Çünkü bu zalim bir çağ, ve hükümdarının düşmanlarını yok ederek, sadık tebaasının hayatını kurtarıyorsun.";
			link.l1 = "Teşekkür ederim, Peder, bu bana büyük bir teselli oldu... Artık gideceğim.";
			link.l1.go = "exit";
		break;

		case "ispoved_4":
			dialog.text = "Tanrı seni böyle bir günahtan affetmeyecek! Dua et ve tövbe et, tövbe et ve dua et! Artık senin için tek bir yol var – manastıra gitmek!";
			link.l1 = "Manastır beklemek zorunda kalacak. En azından bu hayatta değil. Elveda...";
			link.l1.go = "exit";
			npchar.quest.BadMeeting = lastspeak_date;
		break;

        case "work":
        	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner") && NPChar.location == PChar.GenQuest.ChurchQuest_1.ToColony + "_church")
        	{
        		dialog.text = "Üzgünüm, "+GetSexPhrase("oğlum","kızım")+", fakat şu anda tüm günah çıkarma odaları dolu. En erken yarım saat sonra günahını dinleyebilirim.";
				link.l1 = "Affedersiniz, "+RandPhraseSimple("padre","Baba")+", bu başka bir mesele. Padre "+PChar.GenQuest.ChurchQuest_1.PriestName+",  şuradan "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+", bir zamanlar sana ilahiyat kütüphanesinden paha biçilmez hazineler emanet etmişti. Onları geri getirmemi istedi.";
				link.l1.go = "GenQuest_Church_1_Dialog_1";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner");
				break;
        	}
			dialog.text = "Ne iş için buraya geldiniz, "+GetSexPhrase("oğlum","kızım")+"?";
			link.l1 = "Sana bir soru sormak istiyorum, Padre...";
			link.l1.go = "quests"; // ссылка к НПС
            link.l2 = RandPhraseSimple("  Kilise'nin iyiliği için çalışmak hakkında konuşmak istiyordum "+NationNameGenitive(sti(NPChar.nation))+".","Parişte işler nasıl gidiyor? Yardıma ihtiyacınız var mı?");
			link.l2.go = "prihod";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
	            link.l3 = RandPhraseSimple("Padre","Baba")+", seninle mali konular hakkında konuşmak istiyorum."; //(пересылка в кредиты)
	            link.l3.go = "LoanForAll";
            }
			// -->
            if (stf(pchar.Health.HP) < 60.0)
            {
                link.l4 = "İyileşmeye ihtiyacım var.";
                link.l4.go = "healthAdd_1";
            }
            
			//квест мэра - на связь с нашим шпионом
			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
			{
	            link.l7 = RandPhraseSimple("Padre","Kutsal Baba")+", bir adamın isteği üzerine buradayım. Adı Vali "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".";
	            link.l7.go = "IntelligenceForAll";
            }
			//--> Jason Церковная депеша
			if (CheckAttribute(pchar, "GenQuest.Monkletter") && npchar.city == pchar.GenQuest.Monkletter.City)
			{
	            link.l10 = "Padre, kasabada bir keşişten size bazı belgeler getirdim "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity)+".";
	            link.l10.go = "Monkletter";
            }
			//<-- Церковная депеша
			//--> Jason Доставка молитвенников
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "go" && sti(npchar.nation) == sti(pchar.GenQuest.Churchbooks.Nation) && npchar.city != pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "Padre, ben koloniden geldim: "+XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity)+". Yerel kilisenin daha fazla dua kitabına ihtiyacı varmış, ve buradaki keşiş bu konuda sizinle görüşmemi önerdi.";
	            link.l11.go = "Churchbooks";
            }
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "return" && npchar.city == pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "Baba, cemaatiniz için dua kitaplarını getirdim.";
	            link.l11.go = "Churchbooks_2";
            }
			//<-- Доставка молитвенников
			link.l99 = "Fikrimi değiştirdim, yapacak çok işim var.";
			link.l99.go = "exit";
		break;

		case "prihod":
			if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && rand(5) == 1)
		    {
		        dialog.text = "Harika. Ve yine de, bu kasvetli zamanlarda, "+GetSexPhrase("oğlum","kızım")+", tapınağa gelen her ziyaretçi Ana Kilisemiz için faydalı olacak diye bir şey yok.";
				link.l1 = LinkRandPhrase("Baba","Padre","Baba")+", Ben gerçek bir Hristiyanım ve Kutsal Ana Kilisemize hizmet etme niyetim son derece samimidir."+GetSexPhrase(" Ona, benim gibi sadık şövalyesi destek olmazsa, kim destek olacak?","")+"";
				link.l1.go = "GenQuest_Church_1_Start_1";
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
		    }
			else
			{
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}	
            dialog.text = "Şimdiye kadar bölgede her şey sakin, "+GetSexPhrase("oğlum","kızım")+". Teklifiniz için teşekkür ederim.";
    		link.l2 = "Pekâlâ, her şey yolundaysa, ben de işime bakayım o zaman.";
    		link.l2.go = "exit";
			DeleteAttribute(npchar, "quest.add");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
		break;
		
		// Church GenQuest_1 -->
		case "GenQuest_Church_1_Start_1":
			dialog.text = "Eh, hassas bir görevim var; sadece iyi niyet değil, aynı zamanda büyük cesaret ve ciddi bir gizlilik de gerektiriyor...";
			link.l1 = LinkRandPhrase("Baba","Padre","Baba")+", size seve seve her türlü hizmeti sunarım, bunun için cehennemin dibine gitmem gerekse bile! Tanrı beni bu günahkâr sözlerim için affetsin.";
			link.l1.go = "GenQuest_Church_1_Start_2";
		break;
			
		case "GenQuest_Church_1_Start_2":
			PChar.GenQuest.ChurchQuest_1.QuestTown = NPChar.City;
			Church_GenQuest1_InitStartParam(NPChar);
			dialog.text = "Oh! Güzel... Ama yine de, bu çok hassas bir mesele... Bir süre önce, başrahip "+PChar.GenQuest.ChurchQuest_1.ToName+" from "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Gen")+" on "+XI_ConvertString(PChar.GenQuest.ChurchQuest_1.ToIsland+"Voc")+"Benim için bir kilise kütüphanesinden bir süreliğine birkaç teolojik eser ve eski el yazması ödünç aldı. Başpiskoposun, bilgi ışığının yayılmasına engel olunmaması konusundaki ısrarıyla desteklenen bu talebi geri çeviremedim, deniz yolculuklarının zorluklarının el yazmalarını zamanında geri getirmesine engel olacağını tahmin etmeme rağmen... Bu sorunu çözmemde bana yardımcı olabilir misiniz?";
			link.l1 = "Korkarım, "+LinkRandPhrase("Baba","padre","Kutsal Baba")+", bunu senin için yapamam. Bu çok hassas bir mesele, ve bunu ancak gerçek bir diplomat çözebilir.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Baba","Padre","Baba")+", göreviniz bana pek karmaşık görünmüyor. Hemen oraya gideceğim.";
			link.l2.go = "GenQuest_Church_1_Start_3";
		break;
			
		case "GenQuest_Church_1_Start_3":	// Квест взят
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.StartQuest = true;
			PChar.GenQuest.ChurchQuest_1.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_1.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_1.AskOwner = true;
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sOwnerCity", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen"));
		break;
			
		case "GenQuest_Church_1_Dialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2A_Scene"))	// Сцена 2а
			{
				dialog.text = "Ah! Evet... Şimdi hatırladım... Ama, "+GetSexPhrase("oğlum","kızım")+", bu hazineler maddi olmaktan çok manevi! Şimdiden cemaatime büyük fayda sağladılar ve gelecekte de sağlayabilirler!";
				link.l1 = "Ama, "+LinkRandPhrase("Baba","Padre","Baba")+",  Baba'nın cemaatinden olanlar "+PChar.GenQuest.ChurchQuest_1.PriestName+"  aynı zamanda kurtuluşa da muhtaçtır ve bu işler olmadan, teolojinin dayanaklarından yoksun kalacak, vaazları ise ilhamdan mahrum olacaktır.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_1";
			}
			else	// Сцена 2б-а и 2б-б
			{
				dialog.text = "Ah, evet!.. Gerçekten... "+GetSexPhrase("Oğlum","Kızım")+", bu hazineler maddi olmaktan çok manevi değerde! Cemaatime çok faydası dokundu, bu yüzden utanarak söylüyorum ki, onları asıl sahibine geri 'vermeyi unuttum'...";
				link.l1 = "Gerçekten, "+RandPhraseSimple("Baba","Padre","Baba")+"Evet, gerçekten de. Bu yüzden Baba "+PChar.GenQuest.ChurchQuest_1.PriestName+" Bu kitapları ona bizzat teslim etmemi istedi.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_1": // Сцена 2а
			dialog.text = "Anlıyorum evladım, ama her gün Rabbimize şöyle dua etmiyor muyuz: 've bize karşı suç işleyenleri affettiğimiz gibi, bizim suçlarımızı da affet'? Ve kilise de "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+" benim mütevazı mahallemden daha zengin.";
			link.l1 = "Kesinlikle haklısınız, Peder, ama az önce Kutsal Kitap'tan başka bir satır aklıma geldi: 'Kolay yolu arama, çünkü şeytan orada pusuya yatar, sesi daha sinsi olur ve ayartısı daha güçlüdür, yol ne kadar kolaysa!' Ve padre "+PChar.GenQuest.ChurchQuest_1.PriestName+" Az kalsın başpiskoposa senin unutkanlığınla ilgili bir mesaj gönderecekti – onu vazgeçirmek için son anda yetiştim.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_1":
			dialog.text = "A-a-ama başpiskoposa mı?! Böyle önemsiz bir mesele için!.. Neden? Gerçekten mi? Zaten bu eserleri Mesih’teki sevgili kardeşime gönderecektim – sadece ona ulaştırmak için uygun bir fırsat çıkmamıştı. Ama sizde, "+GetSexPhrase("oğlum","kızım")+", Rabbimizin gerçekten layık bir hizmetkârını görüyorum. Al bakalım, şu kitapları ve el yazmalarını al ve lütfen bunları Baba'ya teslim et "+PChar.GenQuest.ChurchQuest_1.PriestName+" sağ salim. Ve buna, en içten şükranlarımı da ekleyin.";
			link.l1 = "Elbette, "+LinkRandPhrase("Baba","Padre","Baba")+". Tabii ki...";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.Complete.Short = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			// Предмет "рукопись" -->
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			// <-- Предмет "рукопись"
		break;
			
		case "GenQuest_Church_1_Dialog_1_2":	// Сцена 2б-а и 2б-б
			// Генерим кэпа -->
			sld = GetCharacter(NPC_GenerateCharacter("ChurchGenQuest1_Cap", "mercen_" + (rand(14)+14), "man", "man", 15, NPChar.nation, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 40, 35, "blade_13", "pistol3", "grapeshot", 30);
			FantomMakeCoolSailor(sld, 7 + rand(2), "", CANNON_TYPE_CANNON_LBS16, 75, 70, 65);
			sld.Abordage.Enable = false;
			sld.ShipEnemyDisable  = true; // флаг не обижаться на выстрелы
			LAi_SetImmortal(sld, true);
			sld.Dialog.FileName = "GenQuests_Dialog.c";
			sld.Dialog.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			Group_FindOrCreateGroup("ChurchGenQuest1_CapGroup");
			Group_AddCharacter("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetType("ChurchGenQuest1_CapGroup", "trade");
			Group_SetGroupCommander("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetTaskNone("ChurchGenQuest1_CapGroup");
			Group_LockTask("ChurchGenQuest1_CapGroup");
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = "";
			PChar.GenQuest.ChurchQuest_1.CapFullName = GetFullname(sld);
			PChar.GenQuest.ChurchQuest_1.CapShipName = sld.Ship.Name;
			PChar.GenQuest.ChurchQuest_1.NoCapColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			// <-- Генерим кэпа
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2BA_Scene")) // Сцена 2б-а
			{
				dialog.text = "Ama, "+GetSexPhrase("oğlum","kızım")+"... Bakın, mesele şu ki, geçen hafta ' gemisinin kaptanıyla tanıştım "+sld.Ship.Name+"', ölüm döşeğindeki bir denizciye komünyon vermem için çağrıldığım yerdi. Büyük bir sevinçle, kaptan "+GetFullName(sld)+" bana gideceğini söyledi "+XI_ConvertString("Colony"+GetColonyExpect2Colonies(NPChar.city,PChar.GenQuest.ChurchQuest_1.QuestTown))+". Ve her ne kadar hiçbir şartı hak etmese de, yine de yardım etmeyi kabul etti ve bana limanın "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+" elbet gelecektir. Ben de bu fırsatı değerlendirdim, kitapları o iyi kalpli adama verdim ve onların geleceğini Tanrı'ya emanet ettim.";
				link.l1 = "Hmm, bu kaptana gerçekten güvenebilir miyiz? Ona emanet edilen eserlerin değerini ve bu görevin önemini anlıyor mu?";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_1";
			}
			else // Сцена 2б-б
			{
				dialog.text = "Ah, "+GetSexPhrase("oğlum","kızım")+"! Birkaç saat geç kaldın! Babamın kitaplarını çoktan gönderdim "+PChar.GenQuest.ChurchQuest_1.PriestName+" kaptanla birlikte "+PChar.GenQuest.ChurchQuest_1.CapFullName+" . Bu sabah, o Tanrı'dan korkan adam itirafta bulunmaya geldi ve bugün gemisinin yelken açacağını söyledi "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.CapColony)+". Ve kaptan hiçbir şartı hak etmese de, yine de yardım etmeyi kabul etti ve bana limanın "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+" kesinlikle ziyaret edecek.";
				link.l1 = LinkRandPhrase("Baba","Padre","Baba")+"... bu kaptana gerçekten güvenebilir miyiz? Bir de gemisinin adını öğrenmek istiyorum.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_1";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1":	// 2б-а
			dialog.text = "İnsanlara güvenirim, "+GetSexPhrase("oğlum","kızım")+", her birimiz Rabbimizin suretinde ve benzerliğinde yaratıldık, ve O'nun kutsal ateşi her ruhun içinde yanar!";
			link.l1 = "Ah. Bu kesinlikle ağır bir gerekçe. Peki... O zaman, Baba, beni kutsayın ve o kaptanı ararken bana şans dileyin.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true; // Полная инфа о кэпе
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_1");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_1":
			dialog.text = "İnsanlara güvenmelisin, "+GetSexPhrase("oğlum","kızım")+". Gemisi hakkında ise söyleyecek bir şeyim yok.";
			link.l1 = "Ve sen, gemisinin adını öğrenmeye bile zahmet etmeden değerli el yazmalarını bir kaptana mı verdin?!!";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_2":
			dialog.text = "Bak, "+GetSexPhrase("oğlum","kızım")+", kaptan "+PChar.GenQuest.ChurchQuest_1.CapFullName+" çok Tanrı korkusu olan biri...";
			link.l1 = "Bunu zaten duymuştum.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_3";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_3":
			dialog.text = "Sakin ol, "+GetSexPhrase("genç adam","genç hanımefendi")+"! Kaptan "+PChar.GenQuest.ChurchQuest_1.CapFullName+"   çok Tanrı korkusu olan bir insandır ve bugüne kadar gemisi öyle bir isim taşıyordu ki, hiçbir din adamı bunu ne düşüncesinde ne de sesli olarak ağzına almamalı! Bugünkü günah çıkarma sırasında ona bunu söyledim. Çünkü İncil'in dediği gibi, biz günahkarlar ruhun saflığını, bedenin saflığından bile daha çok korumalıyız; zira Rabbimiz, ağzı kirli olana Krallığını nasip etmez...";
			link.l1 = "Anladım. "+LinkRandPhrase("Baba","Padre","Baba")+", anladım! "+PChar.GenQuest.ChurchQuest_1.CapFullName+", Karayipler'de kötü şöhretli bir kumarbaz ve ayyaş olarak tanınan adam, senin önerinle eski teknesine yeni bir isim vermeye karar verdi mi?";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_4";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_4":
			dialog.text = "Çok dikkatlisiniz, "+GetSexPhrase("oğlum","kızım")+". Bu geminin yeni adını bilmiyorum, ama eminim ki oldukça görkemli bir şeydir.";
			link.l1 = "Oh, "+RandPhraseSimple("Baba","Padre","Baba")+"... Her şey için teşekkür ederim. Ve günahkâr ruhum için dua et...";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_5";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_2");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
		break;
			
		case "GenQuest_Church_1_Complete_1":
			dialog.text = "Ah, evladım! Dualarım kabul oldu, her şey en iyi şekilde çözüldü! Yardımın ve inancın için, "+GetSexPhrase("oğlum","kızım")+", cennet ve meleklerin şarkıları kesinlikle seni bekliyor olacak...";
			link.l1 = RandPhraseSimple("Padre.","Baba.")+", Aziz Petrus'la buluşmaya niyetim yok, Allah korusun. Yaşayanlara gelince - onlar göksel saadet vaatlerinden fazlasını, türlü dünyevi şeyleri de isterler...";
			link.l1.go = "GenQuest_Church_1_Complete_2";
		break;
			
		case "GenQuest_Church_1_Complete_2":
			dialog.text = "Evet, evet, "+GetSexPhrase("oğlum","kızım")+" , elbette. Hak ettiğin gibi ödüllendirileceksin. Al bakalım, bunu sakın unutma: Rabbimiz, dünyevi nimetlere fazlasıyla göz diken ve sarı şeytana tapan akılsız ruhları cezalandırır!";
			link.l1 = "Teşekkür ederim, "+LinkRandPhrase("Baba","Padre","Kutsal Baba")+". Lütfen uzun zamandır beklediğiniz kitaplarınızı ve el yazmalarınızı alın ve günahkar ruhum için dua edin... Elveda!";
			link.l1.go = "GenQuest_Church_1_Complete_3";
		break;
			
		case "GenQuest_Church_1_Complete_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			RemoveItems(PChar, "Bible", 1);
			items[FindItem("Bible")].Name = "itmname_bible";
			BackItemDescribe("Bible");
			DeleteAttribute(items[FindItem("Bible")], "City");
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddCharacterExpToSkill(PChar, "Leadership", 50); // Бонус в авторитет
			AddCharacterExpToSkill(PChar, "Fortune", 50); // Бонус в удачу
			TakeNItems(pchar, "chest", 3+hrand(1));
			PlaySound("interface\important_item.wav");
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			characters[GetCharacterIndex("ChurchGenQuest1_Cap")].LifeDay = 0;
			Group_DeleteGroup("ChurchGenQuest1_CapGroup"); // Трем кэпа
			PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = true; // Завершаем, если вдруг осталось
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSumm", FindRussianMoneyString(sti(PChar.GenQuest.ChurchQuest_1.AwardSumm)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
			break;
		// <-- Church GenQuest_1

        case "healthAdd_1":
            if (stf(pchar.Health.maxHP) == 60.0) // отлично
            {
                dialog.text = "Sağlığınız "+GetHealthNameMaxSmall(pchar)+",   ve yaralar kendiliğinden iyileşecek. Sadece kan dökmekten kaçınmalı ve sağlığına dikkat etmelisin.";
    			link.l1 = "Teşekkür ederim, bu gerçekten içimi rahatlattı. Bir süre kavga etmekten kendimi alıkoymaya çalışacağım.";
    			link.l1.go = "exit";
            }
            else
            {
    			dialog.text = "Sağlığınız "+GetHealthNameMaxSmall(pchar)+", ve yaralar kendiliğinden iyileşecek olsa da, yine de ilgilenmelisin.";
    			link.l1 = "Bunun için ne gerekiyor?";
    			link.l1.go = "healthAdd_2";
			}
			link.l2 = "Ve neden sağlığım giderek kötüleşiyor?";
    		link.l2.go = "healthAdd_info";
		break;

		case "healthAdd_info":
			dialog.text = "Bu çok basit, "+GetSexPhrase("oğlum","kızım")+". Her yaralandığında hasar alırsın. Bu gözden kaçmaz. Her yara sağlığını daha da kötüleştirir ve sonuçta daha zayıf olursun. Mürettebatın, zayıflamış bir kaptan gördükçe sana olan saygısını kaybeder. Yine de, daha temkinli olursun ve kendini savunma yeteneğin geçici olarak artar. Dinlenmek ve yaralanmaktan kaçınmak güçlü kalmana yardımcı olur.";
			link.l1 = "Aydınlattığınız için teşekkür ederim.";
			link.l1.go = "exit";
		break;

		case "healthAdd_2":
			dialog.text = "Dua etmek ve şiddetten uzak durmak, "+GetSexPhrase("oğlum","kızım")+". Sonra Tanrı kaybettiklerinizi size geri verecek.";
			link.l1 = "Ama benim için dua edebilir misin?";
			link.l1.go = "healthAdd_3";
			link.l2 = "Yani başka bir yol yok mu? Hmm... Gerçekten içimi rahatlattın, sağ ol.";
			link.l2.go = "exit";
		break;

		case "healthAdd_3":
            if (npchar.quest.HealthMonth != iMonth)
            {
    			dialog.text = "Ben mi? Elbette mümkün. Ama cemaatimize bir bağış yapmanız gerekecek.";
    			link.l1 = pcharrepphrase("Ne kadar?","Memnuniyetle! Ne kadar?");
    			link.l1.go = "healthAdd_4";
    			link.l2 = "Sanırım kendi başıma idare ederim...";
    			link.l2.go = "exit";
			}
			else
			{
                dialog.text = ""+GetSexPhrase("Oğlum","Kızım")+", Senin iyiliğin için şimdiden dua ediyorum. Bu dualar ay sonuna kadar bütün vaktimi alacak.";
    			link.l1 = "Teşekkür ederim, "+RandPhraseSimple("padre.","Kutsal Baba.");
    			link.l1.go = "exit";
			}
		break;

		case "healthAdd_4":
			dialog.text = "İyileşme mucizesi için yüz bin peso yeterli bir ödeme olacaktır.";
			link.l1 = pcharrepphrase("Ne?!! Aklını mı kaçırdın sen? O kadar parayı ancak birkaç kiliseyi soyduktan sonra öderim!","Bu bana fazla. Derler ki doğruymuş - sağlık parayla satın alınamaz.");
			link.l1.go = "exit";
            if (sti(pchar.Money) >= 100000)
            {
    			link.l2 = "Kabul ediyorum!";
    			link.l2.go = "healthAdd_5";
			}
		break;

		case "healthAdd_5":
            AddMoneyToCharacter(pchar, -100000);
            AddCharacterMaxHealth(pchar, 4); // можно не проверять, тк явно меньше 51
            npchar.quest.HealthMonth = iMonth;
			dialog.text = "Pekala. Sağlığın biraz düzelecek. Ama yine de çatışmalardan uzak durmalı ve kendine iyi bakmalısın, yoksa bu etki kaybolur. Senin fanî bedenin için bir ay boyunca dua etmem gerekecek.";
			link.l1 = "Teşekkürler. Bir şey olursa, bir ay sonra tekrar seni görmeye gelirim.";
			link.l1.go = "exit";
		break;
		
		//квест пожертвования хозяйки борделя
		case "HostessChurch":
			dialog.text = "Ve o parayı bağışlayan iyi yürekli kişi kim?";
			link.l1 = "Hmm... Burası yerel genelevin patroniçesi.";
			link.l1.go = "HostessChurch_call";
			link.l2 = "İsimleri gizli tutmayı tercih ederim. İsimsiz bir bağış yapılabilir, değil mi?";
			link.l2.go = "HostessChurch_notCall";
			pchar.questTemp.different = "HostessChurch_return"; //флаг на возвращение
		break;
		
		case "HostessChurch_call":
			if (isBadReputation(pchar, 5)) 
			{
				if (rand(100) < GetCharacterSkill(pchar, "Fortune")) //рендом вешаем на удачу
				{
					dialog.text = "You are a sinner, yet you ask for a sinner? You'd better think about your soul first; in fact, all of us will appear before the Lord!";
					link.l1 = "Doğru. Umarım Rabbim bana merhametli olur... Peki, bağış meselesi ne olacak?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "Çekil önümden, şeytan!!! Al lanetli paranı ve defol git!";
					link.l1 = "Nasıl yani, Peder?! Sana açık yürekle geldik, ve sen...";
					link.l1.go = "HostessChurch_bad";
				}
			}
			else
			{
				if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma")) //рендом вешаем на харизму
				{
					dialog.text = " Günahkârların doğru yolu bulmasına yardım ettiğin için memnunum. Bunun karşılığını Cennet'te alacaksın!";
					link.l1 = "Harika olurdu! Peki, bağış meselesi ne olacak?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "Günahla elde edilen parayı kabul edemem. Onu o düşmüş kadına geri ver, "+GetSexPhrase("oğlum","kızım")+". Kimse parayla Tanrı'ya ulaşamaz.";
					link.l1 = "Onu reddetmen gerçekten yazık. Gerçekten yazık.";
					link.l1.go = "HostessChurch_bad_1";
				}
			}
		break;
		
		case "HostessChurch_notCall":
			if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				dialog.text = "Bu parayı almak, nereden geldiğini bile bilmeden...";
				link.l1 = "Evet, padre, tam olarak öyle. Lütfen, yürekten verilen bu katkıyı kabul edin!";
				link.l1.go = "HostessChurch_ok_1";
			}
			else
			{
				dialog.text = "Bu parayı almak, nereden geldiğini bile bilmeden? Aklını mı kaçırdın?! Ya bu para kana bulanmışsa!";
				link.l1 = "Baba, bütün paranın üstünde kan lekesi var...";
				link.l1.go = "HostessChurch_bad_2";
			}
		break;

		case "HostessChurch_ok":
			dialog.text = "Kabul ediyorum. "+GetSexPhrase("oğlum","kızım")+" . Git ve bunu düşmüş kadınına söyle.";
			link.l1 = "Pekala, padre. Teşekkür ederim.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_ok_1":
			dialog.text = "Kabul ediyorum. "+GetSexPhrase("oğlum","kızım")+" . Bu iyilikseverine bundan bahset.";
			link.l1 = "Pekala, padre. Teşekkür ederim.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_bad":
			dialog.text = "Defol, cehennemden gelen bela, bir daha sakın buralarda görünme!";
			link.l1 = "Heh, nasıl istersen.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_1":
			dialog.text = "Bu benim kararım. Huzurla git, "+GetSexPhrase("oğlum","kızım")+".";
			link.l1 = "Elveda, padre.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_2":
			dialog.text = "Bunu mu düşünüyorsun, kafir?! Derhal tapınaktan çık ve bir daha sakın buraya uğrama!";
			link.l1 = "Gerçekten mi? Neyse, gidiyorum...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;

		//--> Jason Церковная депеша
		case "Monkletter":
			if (CheckAttribute(pchar, "GenQuest.Monkletter.Late"))
			{
				dialog.text = "Bu belgeleri bir daha göreceğimden neredeyse umudumu kesmiştim. Neden bu kadar geciktin, oğlum?";
				link.l1 = "Beklenmedik gelişmeler oldu, Baba.";
				link.l1.go = "Monkletter_1";
			}
			else
			{
				dialog.text = "Bu evrakları bekliyordum, evlat. Hızlı teslimat için teşekkür ederim. Lütfen şu paraları kabul et ve benim hayır duamla yoluna devam et.";
				link.l1 = "Teşekkür ederim, Peder. Kutsal Kilise'ye yardım etmek benim için bir zevkti!";
				link.l1.go = "Monkletter_3";
			}
		break;
		
		case "Monkletter_1":
			dialog.text = "Hepimiz Tanrı'nın ellerindeyiz, oğlum... İnsan plan yapar, ama takdir Tanrı'ya aittir. Şu evrakları bana ver ve huzurla git.";
			link.l1 = "Buyurun, padre. Size en iyisini dilerim!";
			link.l1.go = "Monkletter_2";
		break;
		
		case "Monkletter_2":
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//заменить на нужный
			AddQuestRecord("Monkletter", "2");
			CloseQuestHeader("Monkletter");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter_3":
			dialog.text = "Tanrı'nın bereketi üzerinde olsun, evladım. Yüce Allah yolculuklarında seni korusun!";
			link.l1 = "Hoşça kal, Baba.";
			link.l1.go = "Monkletter_4";
		break;
		
		case "Monkletter_4":
			pchar.quest.Monkletter_Over.over = "yes"; //снять таймер
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//заменить на нужный
			AddQuestRecord("Monkletter", "3");
			CloseQuestHeader("Monkletter");
			TakeNItems(pchar, "gold_dublon", 10+rand(5));
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
			addLiberMisBonus();
		break;
		//<-- Церковная депеша
		
		//--> Jason Доставить молитвенники
		case "Churchbooks":
			dialog.text = "Bizi dua kitaplarını almak için göndermişler -   kilise için "+XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity+"Gen")+"? Peki. Otuz dua kitabından oluşan bir paketim var. Al bunu, evladım.";
			link.l1 = "Teşekkür ederim, padre. Hoşça kal!";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			dialog.text = "Tanrı yolculuğunda seni korusun! Huzurla git...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Churchbooks", "2");
			pchar.GenQuest.Churchbooks = "return";
			GiveItem2Character(pchar, "prayer_book");//поставить соотв.предмет
		break;
		
		case "Churchbooks_2":
			if (CheckAttribute(pchar, "GenQuest.Churchbooks.Late"))
			{
				dialog.text = "Yardımın için teşekkür ederim, evladım, gerçi biraz gecikmeli de olsa.";
				link.l1 = "Beklenmedik gelişmeler yüzünden geciktim, Baba.";
				link.l1.go = "Churchbooks_3";
			}
			else
			{
				dialog.text = "Yardımın için teşekkür ederim, evladım. Bu kitapları tam zamanında getirdin. Lütfen, ödül olarak bu kutsanmış tılsımı kabul et – en zor anında seni tehlikeden koruyacaktır.";
				link.l1 = "Teşekkür ederim, Peder. Kutsal Kilise'ye yardım etmek benim için bir zevkti!";
				link.l1.go = "Churchbooks_4";
			}
		break;
		
		case "Churchbooks_3":
			dialog.text = "Her şey Tanrı'nın ellerinde, evladım. Huzurla git!";
			link.l1 = "Hoşça kal, padre.";
			link.l1.go = "exit";
			RemoveItems(PChar, "prayer_book", 1);//заменить на нужный
			AddQuestRecord("Churchbooks", "3");
			CloseQuestHeader("Churchbooks");
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;
		
		case "Churchbooks_4":
			dialog.text = "Tanrı'nın kutsaması üzerindesin, evladım. Yüce Allah yolunda seni kötülüklerden korusun!";
			link.l1 = "Hoşça kal, Baba.";
			link.l1.go = "Churchbooks_5";
		break;
		
		case "Churchbooks_5":
			pchar.quest.Churchbooks_Over.over = "yes"; //снять таймер patch-5
			DialogExit();
			RemoveItems(PChar, "prayer_book", 1);//заменить на нужный
			GiveItem2Character(pchar, pchar.GenQuest.Churchbooks.Item);
			Log_Info("You have received '"+XI_ConvertString(pchar.GenQuest.Churchbooks.Item)+"'");
			AddQuestRecord("Churchbooks", "4");
			CloseQuestHeader("Churchbooks");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
			addLiberMisBonus();
		break;
	}
}

void ChurchGenQuest2_RemoveCup()
{
	RemoveItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	DeleteAttribute(rItem, "City");
	rItem.Weight = 2;
	rItem.Name = "itmname_Bible";
	rItem.picIndex = 6;
	rItem.picTexture = "ITEMS_9";
	BackItemDescribe("Bible");
}

void Church_GenQuest1_InitStartParam(ref chr)
{
	string sColony = SelectNotEnemyColony(chr); 
	PChar.GenQuest.ChurchQuest_1.IslandId = colonies[FindColony(PChar.GenQuest.ChurchQuest_1.QuestTown)].Island;
	PChar.GenQuest.ChurchQuest_1.ToColony = sColony;
	PChar.GenQuest.ChurchQuest_1.ToIsland = colonies[FindColony(sColony)].Island;
	PChar.GenQuest.ChurchQuest_1.ToName = characters[GetCharacterIndex(sColony + "_Priest")].Name;
	
	// Чтоб жизнь медом не казалась... Какие сцены будут в квесте, определяем в самом начале.
	int iRand = Rand(2);
	switch(iRand)
	{
		case "0":
			PChar.GenQuest.ChurchQuest_1.2A_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2A (just pick up the manuscript from the priest)."); 
		break;
		
		case "1":
			PChar.GenQuest.ChurchQuest_1.2BA_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2B-A (search for a cap. There is full information about him).");
		break;
		
		case "2": // Этот флаг уже не проверяем, т.к. если нет тех, что выше, по-любому есть этот
			PChar.GenQuest.ChurchQuest_1.2BB_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2B-B (search for a cap. The name of the ship is unknown)."); 
		break;
	}
}
