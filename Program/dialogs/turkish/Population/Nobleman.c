//Jason общий диалог дворян
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iTest;
	string sTemp, sTitle;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	iTest = FindColony(NPChar.City); // 170712
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> проверка межнациональных отношений
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
				dialog.text = NPCStringReactionRepeat("Hm. Sen   bayrağı altında seyrediyorsun "+NationNameGenitive(sti(pchar.nation))+", dostum. Ne halt ediyorsun burada, bizim kasabamızda? Kaybol!","  Birinin dostu olduğumdan şüphelenilmek istemem  "+NationNameAblative(sti(pchar.nation))+"! Defol git yoksa seni muhafızlara şikayet ederim!","Bu senin son şansın kaçmak için. Yoksa suçlayacak başka kimsen olmayacak.","Seni uyardım. Şimdi küstahlığının bedelini ödeyeceksin, piç!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Ne vatansevermişsin, ha!","Pekala, pekala, sakin ol. Gidiyorum.","Bu kadar gürültü yapma. Gidiyorum.","Ne?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> проверка репутации - дворяне гнобят супернегодяев
			if (sti(pchar.reputation.nobility) < 10)
			{
				dialog.text = NPCStringReactionRepeat("Şuna bak! Ve bizim muhafızlarımız senin gibi bir serserinin şehirde elini kolunu sallayarak dolaşmasına nasıl izin veriyor? İnanılır gibi değil...","Defol git, seninle konuşmak bile istemiyorum! Cellat...","Bu senin son kaçış şansın. Yoksa suçlayacak başka kimsen olmayacak.","Seni uyardım. Şimdi küstahlığının bedelini ödeyeceksin, piç!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Hey hey! Biraz saygı gösterin, bayım!","Kendine bak, aziz...","Sakin ol...","Ne?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> диалог первой встречи
            if(NPChar.quest.meeting == "0")
			{
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && CheckAttribute(pchar, "questTemp.StatusCity") && pchar.questTemp.StatusCity == npchar.city)//дворянин-пассажир
				{
					dialog.text = "Selamlar, "+GetAddress_Form(NPChar)+". Güzel bir geminin kaptanı olduğunuzu görüyorum. Sizden bir şey isteyeceğim. Kabul edebilirsiniz de, etmeyebilirsiniz de.";
					link.l1 = "Dinliyorum, "+GetAddress_FormToNPC(NPChar)+". Ne demek istiyorsun?";
					link.l1.go = "passenger";
					link.l2 = "Affedersiniz, "+GetAddress_FormToNPC(NPChar)+", ama acelem var.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && or(IsUniversalShipType(pchar), IsMerchantShipType(pchar)))//дворянин-пассажир
				{
					dialog.text = "Selamlar, "+GetAddress_Form(NPChar)+". Güzel bir geminin kaptanı olduğunuzu görüyorum. Sizden bir ricam olacak. Kabul edebilirsiniz de, etmeyebilirsiniz de.";
					link.l1 = "Dinliyorum, "+GetAddress_FormToNPC(NPChar)+". Ne demek istiyorsun?";
					link.l1.go = "passenger";
					link.l2 = "Affedersiniz, "+GetAddress_FormToNPC(NPChar)+", ama acelem var.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (CheckAttribute(npchar, "quest.donation"))//клянчит деньги
				{
					dialog.text = "Aha, kasabamızda bir centilmeni görmek ne güzel! Eminim Avrupa'dan yeni geldiniz. Bakın, sizden bir ricam olacak - centilmence bir ricada bulunuyorum. Umarım beni doğru anlarsınız.";
					link.l1 = "İyi günler efendim. Sizi dinliyorum.";
					link.l1.go = "donation";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.lombard") && !CheckAttribute(pchar, "GenQuest.Noblelombard"))//семейная реликвия
				{
					dialog.text = "İyi günler, "+GetAddress_Form(NPChar)+"! Kasabamızın sokaklarında bir centilmenle karşılaşmak ne güzel! Birkaç dakikanızı ayırmanıza izin verir misiniz?";
					link.l1 = "Elbette, efendim. Sizi dinliyorum.";
					link.l1.go = "lombard";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.slaves") && !CheckAttribute(&Colonies[FindColony(npchar.city)], "questslaves"))//привезти рабов
				{
					dialog.text = "İyi günler, kaptan! Sizi görmek güzel, çünkü sorunları çözebilecek biri gibi görünüyorsunuz.";
					link.l1 = "Sorunun ne olduğuna bağlı. Ben genellikle sorunları şiddetle çözerim. Aradığın şey bu mu, "+GetAddress_FormToNPC(NPChar)+"?";
					link.l1.go = "slaves";
					npchar.quest.meeting = "1";
					break;
				}
				dialog.text = RandPhraseSimple("Merhaba, "+GetAddress_Form(NPChar)+" . Benden bir şey ister misin?","Ne istiyorsunuz, efendim?");
				link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". Vaktinizi fazla almak istemem, sadece bir şey sormak istiyorum...";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Sömürgeniz hakkında bilgiye ihtiyacım var.","Bilgiye ihtiyacım var.");
				link.l2.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("Tüm şehir diken üstünde - kraliyet müfettişi don Fernando de Alamida geldi. Bilirsin, burada çok şey gördüm ama bu... İnsanları değiştiren yas değil, onunla nasıl başa çıktıklarıdır. Söylenene göre, babasının ölümünden sonra bambaşka biri olmuş. Şimdi tüm Takımadalar'da ondan daha dürüst ve... acımasız bir Kraliyet hizmetkârı bulamazsın.","Şu 'Kutsal Merhamet'e bir bak! Kralın bizzat özel tasarımlarla inşa edilmesini emrettiğini söylüyorlar. Hem bak - üstünde tek bir çizik yok. Sanki Meryem Ana'nın kendisi koruyor gibi. Ama bazı söylentiler duydum... Belki de koruyan Meryem değildir.","Don Fernando'u öldürmeye kaç kez kalkıştıklarını biliyor musun? Sadece geçen yıl açık denizlerde on iki saldırı oldu! Ama böylesine sadık ve eğitimli bir mürettebatla, bir de Tanrı'nın korumasıyla - on üçüncüsünden de sağ çıkacaktır!"),LinkRandPhrase("Duymuş muydun? Don Fernando de Alamida şehrimize gelmiş, şu anda sokaklarda bir yerlerdeymiş diyorlar. Onu kendi gözlerimle görmeyi çok isterdim...","Zor bir adam, bu don Fernando. Kimileri onun Anavatan’ı pislikten arındıran bir kurtarıcı olduğunu söyler. Başkaları ise, babasının ölümünden sonra içinde bir şeylerin koptuğunu ve yakında hepimizin gözyaşı dökeceğini fısıldar. Ama sana şunu söyleyeyim: Ondan korkma. Onu böyle yapanlardan kork.","Ne kadar yakışıklı bir adam, şu don Fernando! Ama tuhaf olan ne biliyor musun? Sanki kimseyi fark etmiyor. Hep görev, hep hizmet. Bir kız olduğunu duymuştum... ama bir rahiple görüştükten sonra, dünyevi zevklerden tamamen vazgeçmiş. Sanki yemin etmiş gibi."),RandPhraseSimple(RandPhraseSimple("Lanet müfettiş! O buradayken şehir ölü gibi. Ne ticaret var, ne eğlence. Hatta nefes almak bile daha sessiz olmalı sanki. Ve en korkuncunu biliyor musun? Her limanda aynı şey yaşanıyor. Tıkır tıkır işliyor. Majesteleri sanki hepimize işkence olsun diye bunu özellikle icat etmiş gibi!","Don Fernando yetimhaneyi yine ziyaret etti. Cömertçe bağış yapıyor, saatlerce dua ediyor. Böyle değerli bir adam, o lanetli zimmetçilere örnek gösterilmeli!"),RandPhraseSimple("Ha! 'Aziz' Fernando gene bütün genelevleri kapattı. Neyse, yakında buradan ayrılır, onlar da hemen tekrar açılır.","Müf... müfettiş geldi, işte olan bu! Don Fernando de Almeida, ya da adı neydi, Almeida! O kadar önemli ki vali bile onun yanında dikkatli davranıyor. Söylentilere göre gözlerinin içine bakıp bütün günahlarını bir bakışta görüyor. Korkunç!")));
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
			}
			else //--> повторные обращения
			{
				dialog.text = NPCStringReactionRepeat("Ne? Yine mi? Sana ayıracak vaktim yok. Konuşacak başka birini bul. Sokaklarda dolaşan bir sürü sıradan insan var. Benimse gitmem gerek, bu akşam valinin konağında bir ziyafet olacak ve kıyafetimi hazırlamam lazım...","Hayır, bu artık gerçekten sinir bozucu! Anlamıyor musun? Yoksa biraz ağır mı anlıyorsun?","Efendim, artık sadece bir aptal değil, aynı zamanda bir taşralı ve kaba biri olduğunuzdan şüphelenmeye başlıyorum. Uyarıyorum, beni rahat bırakın yoksa pişman olursunuz.","Yeter. Sana haddini bildireceğim, terbiyesiz herif!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Anladım. Hoşça kal.","Evet, evet, ne soracağımı unuttum da...","Beni yanlış anladınız...","Ne?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = LinkRandPhrase("Devam et.","Ne istiyorsun?","Sorular mı var? Peki denizci, dinliyorum.");
			link.l1 = LinkRandPhrase("Bana kasabanızdaki son dedikoduları anlatmayacak mısınız?","Son zamanlarda burada ilginç bir şey oldu mu?","Karayipler'den bir haber var mı, efendim?");
			link.l1.go = "rumours_nobleman";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------дворянин-пассажир---------------------------------------------------
		case "passenger":
			if (hrand(19) > 9) SetPassengerParameter("Noblepassenger", false);
			else SetPassengerParameter("Noblepassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
			{
				dialog.text = ""+GetSexPhrase("Bayım","Hanımefendi")+", kolonilere gitmem gerekiyor"+XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City+"Acc")+", en kısa zamanda, üzerinde "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Voc")+", için "+FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty))+" . Geminiz buradaki şu küçük teknelerin çoğuna kıyasla sağlam ve hızlı görünüyor. Size ödeme yapabilirim "+FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money))+". Ne dersin?"; // belamour gen
			}
			else
			{
				dialog.text = "Merhaba, "+GetSexPhrase("efendim","madam")+"!  Gitmem gerekiyor "+XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City+"Acc")+"! Bu   "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Voc")+"Bu arada, evet, evet, biliyorum - o alçaklar orada ortaya çıkmamızı bekliyorlar. Ama orada çok acil ve önemli bir toplantım var! Cimri biri değilim - ödemeyi sevmem ama her zaman yaparım. Ne yapıyorsan bırak, oraya varır varmaz sana vereceğim "+FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money))+".";
			}
			link.l1 = "Hm. Ben de bu tarafa gidiyorum, bu şartlarda seni gemime alabilirim.";
			link.l1.go = "passenger_1";
			link.l2 = "Üzgünüm, "+GetAddress_FormToNPC(NPChar)+", ama ben başka bir yöne gidiyorum. Sana yardımcı olamam.";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "Ne yazık. Neyse, başka bir gemiyi bekleyeceğim. Hoşça kal.";
			link.l1 = "Görüşürüz.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Noblepassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Harika! Beklemekten yoruldum. Oraya vardığımızda ödemenizi alacaksınız.";
			link.l1 = "Gemime git, "+GetAddress_FormToNPC(NPChar)+". Yakında ayrılıyoruz.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Noblepassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "nobleman");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Noblepassenger.City+"Gen") + ", at " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Dat")+".";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Noblepassenger.win_condition.l1 = "location";
			pchar.quest.Noblepassenger.win_condition.l1.location = pchar.GenQuest.Noblepassenger.City+"_town";
			pchar.quest.Noblepassenger.function = "Noblepassenger_complete";
			SetFunctionTimerCondition("Noblepassenger_Over", 0, 0, sti(pchar.GenQuest.Noblepassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Noblepassenger_Over.over = "yes"; //снять таймер
			dialog.text = "İşte buradayız, harika! Geminizle yolculuk etmek gerçekten keyifliydi. Mürettebatınız disiplinli, güverteler tertemiz! Teşekkür ederim. Alın paranızı, efendim.";
			link.l1 = "İyi şanslar, "+GetAddress_FormToNPC(NPChar)+"! Elveda.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Noblepassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Noblepassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Noblepassenger");
		break;
//<-- дворянин-пассажир

//-------------------------------------------------помощь деньгами------------------------------------------------
		case "donation":
			sTemp = DonationText();
			dialog.text = "Oldukça hassas bir işim var..."+sTemp+" Şimdi paraya ihtiyacım var, yoksa başım büyük belada. Normalde asla başka bir centilmenden para istemem, ama durum gerçekten çok vahim.";
			link.l1 = "Ne kadar ihtiyacın var?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			iTemp = hrand(4)+1;
			pchar.GenQuest.Nobledonation.Money = iTemp*1000+rand(iTemp)*150;
			dialog.text = "Tutar oldukça küçük, bu "+FindRussianMoneyString(sti(pchar.GenQuest.Nobledonation.Money))+". Peki, bana yardım edebilir misin?";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Nobledonation.Money))
			{
				link.l1 = "Evet, tabii ki. Al.";
				link.l1.go = "donation_2";
			}
			link.l2 = "Sana yardım etmeyi isterim, ama benim de cebim bomboş – tek bir yedek peso bile yok.";
			link.l2.go = "donation_exit";
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeOfficersLoyality("bad_all", 1);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
		
		case "donation_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Nobledonation.Money));
			dialog.text = "Teşekkür ederim, "+GetAddress_Form(NPChar)+"! Beni kurtardınız! Valinin konutunda dostlarım var, cömertliğinizden onlara da bahsedeceğim. Binlerce kez teşekkürler tekrar!";
			link.l1 = "Rica ederim, efendim. Eminim siz de benim için aynısını yapardınız.";
			link.l1.go = "donation_3";
		break;
		
		case "donation_3":
			DialogExit();
			ChangeOfficersLoyality("good_all", rand(2)+1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), rand(1)+2);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
//<-- помощь деньгами

//-------------------------------------------------семейная реликвия---------------------------------------------
		case "lombard":
			LombardText();
			dialog.text = "Sana ihtiyacım var. Zenginsin ve bir beyefendisin, bu yüzden anlayış göstereceğini umuyorum. Kısa bir süre önce, paraya çok ihtiyacım vardı ve bankere gidip rehin bırakmak zorunda kaldım "+pchar.GenQuest.Noblelombard.Item+"\nİyi şartlar sundu. Aylık yüzde on, toplamda üç ay. Ama süre doldu ve talihsiz olaylar yüzünden eşyayı geri almak için param yok\nŞimdi ise ona bir alıcı bulduğunu söylüyor "+pchar.GenQuest.Noblelombard.Item+" ve borcumu ve faizini hemen ödemezsem onu satacak. Ama şu anda fazla param yok, ve rehin bıraktığım eşya çok değerli...";
			link.l1 = "Peki, bu konuda sana nasıl yardımcı olabilirim, "+GetAddress_FormToNPC(NPChar)+"?";
			link.l1.go = "lombard_1";
		break;
		
		case "lombard_1":
			dialog.text = "I'm asking you to speak with our banker. Offer him money, vouch for me... or do something else. Unfortunately, I have no one else to turn to; all of my good friends have suddenly gone 'bankrupt'. In three months "+pchar.GenQuest.Noblelombard.Text+", and I will repay all your costs, double! You have my word as a gentleman!";
			link.l1 = "Pekala, bu konuda sana yardımcı olmaya çalışacağım.";
			link.l1.go = "lombard_2";
			link.l2 = "Ne yazık ki, şu anda ben de 'beş parasızım'. O yüzden sana yardımcı olamam, çok üzgünüm!";
			link.l2.go = "lombard_exit";
		break;
		
		case "lombard_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Noblelombard");
		break;
		
		case "lombard_2":
			dialog.text = "Anlayışınız için teşekkür ederim. Sizi meyhanede bekliyor olacağım. Mümkün olan en kısa sürede oraya gelin.";
			link.l1 = "...";
			link.l1.go = "lombard_3";
		break;
		
		case "lombard_3":
			DialogExit();
			pchar.GenQuest.Noblelombard.id = npchar.id;
			AddDialogExitQuestFunction("Noblelombard_TookQuest");
		break;
		
		case "lombard_4":
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Regard"))
			{
				pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
				dialog.text = "Ne diyebilirsin, "+GetAddress_Form(NPChar)+"? Bankaya gittin mi? İyi haber mi var, kötü mü?";
				if (pchar.GenQuest.Noblelombard == "full") link.l1 = "Yaptım. Bütün borcunu kendim ödedim. Oraya gidip yadigarını geri alabilirsin.";
				if (pchar.GenQuest.Noblelombard == "maxpercent") link.l1 = "Ödedim. Son üç ayın faizini ve önümüzdeki üç ayınkini de ödedim. Paran için endişelenmene gerek yok. Sadece, ana borcunu üç ay içinde ödemeyi unutma.";
				if (pchar.GenQuest.Noblelombard == "minpercent") link.l1 = "Yaptım. Son üç ayın tüm faizini ödedim. Bankacı, tüm parayı bulana kadar üç ay daha beklemeye razı oldu.";
				link.l1.go = "lombard_5";
			break;
			}
			if (pchar.GenQuest.Noblelombard == "fail")
			{
				dialog.text = "Ne diyebilirsin, "+GetAddress_Form(NPChar)+"? Bankaya gittin mi? İyi haber mi var, kötü mü?";
				link.l1 = "Yaptım. O cimri inanılmaz bir meblağ istedi. Hiçbir şekilde indirim yapmayı kabul etmedi ve bende de gereken para yoktu. Bu yüzden sana yardımcı olamadım. Üzgünüm.";
				link.l1.go = "lombard_fail";
			}
			else
			{
				dialog.text = "Ne diyebilirsin, "+GetAddress_Form(NPChar)+"? Bankaya gittin mi? İyi haber mi var, kötü mü?";
				link.l1 = "Ben hallederim. Bekle.";
				link.l1.go = "exit";
				NextDiag.TempNode = "lombard_4";
			}
		break;
		
		case "lombard_fail":
			pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
			dialog.text = "Eh, "+GetAddress_Form(NPChar)+"... Şimdi sen de bu lanet olası kana susamış tefecilerin dizginlenemez açgözlülüğüne tanık oldun. Tanrı aşkına, efendim, Yahudilere bile taş çıkartıyorlar! Benim gibi onlardan borç almaya kalkarsan bunu unutma. En azından denediğin için teşekkür ederim...";
			link.l1 = "Hiçbir zaman sevemedim onları. Zaten kim sever tefecileri? Üzgünüm, "+GetAddress_FormToNPC(NPChar)+". Elveda.";
			link.l1.go = "lombard_fail_1";
		break;
		
		case "lombard_fail_1":
			DialogExit();
			AddDialogExitQuestFunction("Noblelombard_fail");
		break;
		
		case "lombard_5":
			dialog.text = "İnanılmaz! Beni az önce kurtardın, "+GetAddress_Form(NPChar)+"! Bunu asla unutmayacağım. Tüm masraflarınızın iki katını size geri ödeyeceğime sizi temin ederim. Üç ay sonra bankacımıza uğrayın. Adınıza bir mevduat hesabı açacağım.";
			link.l1 = "Pekala, dediğini yapacağım. Görüşürüz!";
			link.l1.go = "lombard_6";
		break;
		
		case "lombard_6":
			dialog.text = "Tekrar teşekkürler, kaptan. İyi şanslar!";
			link.l1 = "...";
			link.l1.go = "lombard_7";
		break;
		
		case "lombard_7":
			DialogExit();
			AddDialogExitQuestFunction("Noblelombard_success");
		break;
//<-- семейная реликвия

//------------------------------------------привезти рабов под заказ--------------------------------------------
		case "slaves":
			npchar.quest.slaves.price = 3+hrand(1);//цена на рабов в дублонах
			npchar.quest.slaves.qty = 50+hrand(5)*10;//количество
			npchar.quest.slaves.money = sti(npchar.quest.slaves.qty)*sti(npchar.quest.slaves.price);
			dialog.text = "Bir    "+LinkRandPhrase("factory","benim","plantasyon")+" ve her zaman taze kölelere ihtiyacım var. Bu iklim onları gerçekten mahvediyor. Şu anda ihtiyacım olan "+sti(npchar.quest.slaves.qty)+" kafa. Bir parti sipariş etmeye hazırım. Her kafa için altın ödeyeceğim, "+sti(npchar.quest.slaves.price)+" dublon\nAceleye gerek yok, ihtiyacım olanı getirdiğin sürece sana zaman konusunda bir sınır koymayacağım. Tabii makul ölçüde, işi yarım yıldan fazla uzatma yeter. Ne dersin? Anlaştık mı?";
			link.l1 = "Anlaştık! Köle ticareti pis bir iş, ama riske değer.";
			link.l1.go = "slaves_1";
			link.l2 = "Affedersiniz, ama ben köle taciri değilim. Bu benim işim değil.";
			link.l2.go = "exit_slaves";
		break;
		
		case "exit_slaves":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "slaves_1":
			dialog.text = "Pekâlâ o zaman. Yükü getirdiğinde seni bekliyor olacağım. Beni her gün sabah 11'den öğlen 1'e kadar kilisede bulabilirsin. Günün geri kalanında meşgulüm ya da işteyim.";
			link.l1 = "Pekâlâ. Bunu aklımda tutacağım. Görüşürüz, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			DialogExit();
			sGlobalTemp = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			SaveCurrentNpcQuestDateParam(npchar, "slaves_date");//запоминаем дату
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", npchar.city+"_church", "sit", "sit"+(1+rand(5)), "Nobleslaves_Place", 10.0);
			chrDisableReloadToLocation = true;//закрыть локацию
			Colonies[FindColony(npchar.city)].questslaves = true;
			sTitle = npchar.city+"Nobleslaves";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Nobleslaves", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sQty", sti(npchar.quest.slaves.qty));
			AddQuestUserData(sTitle, "sMoney", sti(npchar.quest.slaves.money));
		break;
		
		case "slaves_3":
			if (GetNpcQuestPastDayParam(npchar, "slaves_date") < 180)
			{
				dialog.text = "Getirdin mi "+sti(npchar.quest.slaves.qty)+" köleleri istediğim gibi getirdin mi, kaptan?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= sti(npchar.quest.slaves.qty))
				{
					link.l1 = "Evet. Tüm parti ambarımda. Size teslim etmeye hazırım.";
					link.l1.go = "slaves_4";
				}
				else
				{
					link.l1 = "Hayır, ben hallederim.";
					link.l1.go = "exit";
					NextDiag.TempNode = "slaves_3";
				}
			}
			else
			{
				dialog.text = "Kaptan, eğer buraya o köleler için geldiyseniz... Zaten yeterince aldım ve şu anda daha fazlasına ihtiyacım yok. Çok geç kaldınız, üzgünüm.";
				link.l1 = "Ne yazık! Ama haklısın, yeterince hızlı davranamadım. Hoşça kal!";
				link.l1.go = "slaves_8";
			}
		break;
		
		case "slaves_4":
			dialog.text = "Mükemmel. Hemen onlar için bir sandal göndereceğim.";
			link.l1 = "Benim ödemem ne olacak?";
			link.l1.go = "slaves_5";
		break;
		
		case "slaves_5":
			dialog.text = "Merak etme, hatırlıyorum. Al, işte paran, "+sti(npchar.quest.slaves.price)+" kafa başına dublon. İkimiz için de iyi bir anlaşma, değil mi?";
			link.l1 = "Teşekkürler. Sizinle iş yapmak bir zevkti.";
			link.l1.go = "slaves_6";
		break;
		
		case "slaves_6":
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(npchar.quest.slaves.qty));
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.slaves.money));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.slaves.money))+"");
			PlaySound("interface\important_item.wav");
			dialog.text = "Öyle diyebilirim... Şimdi müsaadenizi isteyeceğim, gitmem gerek. Görüşürüz!";
			link.l1 = "İyi şanslar, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_7";
		break;
		
		case "slaves_7":
			DialogExit();
			npchar.lifeday = 0;
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			LAi_SetActorType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(npchar, npchar.city+"_church", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "2");
			CloseQuestHeader(sTitle);
		break;

		case "slaves_8":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "3");
			CloseQuestHeader(sTitle);
		break;
//<-- привезти рабов под заказ

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Dinle, bu kasabanın bir vatandaşı olarak senden kılıcını kınına sokmanı istiyorum.","Dinle, bu kasabanın bir vatandaşı olarak senden kılıcını kınına sokmanı istiyorum.");
			link.l1 = LinkRandPhrase("Pekala.","Dediğiniz gibi olsun.","Pekâlâ.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetHP(NPChar, 400, 400);
			TakeNItems(NPChar, "potion2", 3);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "TempFight");
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterNationReputation(pchar, sti(npchar.nation), -3);
		break;
	}
}

string DonationText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "I've lost all my money in gambling yesterday and I don't have enough sum to wipe away the debt. Can you help me?" break;
		case 1: sText = "I had a nice time yesterday with a... certain lady of the evening, and now she is trying to blackmail me. I need to pay her first and then I will deal with her... Can you help me with some money?" break;
		case 2: sText = "I ran through a local fool with my rapier recently and now the commandant demands a bribe to hush up the event. I am short of money now. Can you help me?" break;
		case 3: sText = "I was unlucky enough to lose a bet and I don't have a trifling sum to repay the debt of honor. Can you help me?" break;
		case 4: sText = "Some bastard knows about my... indiscreet activities concerning a married woman. I don't have enough money to shut his mouth. Just a few gold coins are needed... " break;
		case 5: sText = "Some bastard has stolen important papers from my house and demanding a significant sum for their return. I've almost got it, just a few more coins needed. Can you help me?" break;
	}
	return sText;
}

void LombardText()
{
	switch (hrand(5))
	{
		case 0:
			pchar.GenQuest.Noblelombard.Item = "my mother's diamond pendant made by a jeweler from Madrid";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get my inheritance","my ship will return from Africa loaded with slaves");
		break;
		case 1: pchar.GenQuest.Noblelombard.Item = "an emerald necklace of my sister crafted by a jeweler in Paris";
				pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will inherit a county in Europe","my ship will return from India loaded with spices and silk");
		break;
		case 2:
			pchar.GenQuest.Noblelombard.Item = "family ring with an emblem of our kin";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("my expedition will return from the Spanish Main with gold ingots","I will get my inheritance");
		break;
		case 3:
			pchar.GenQuest.Noblelombard.Item = "a ruby bracelet of my wife, a gift from her mother";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get my investment with the interest from a European bank","I will get the profits from my plantation");
		break;
		case 4:
			pchar.GenQuest.Noblelombard.Item = "a necklace of gold and diamonds, piece work, a pride of my wife";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get profits from my current business","my ship will be back from Africa with the cargo hold stuffed with black ivory");
		break;
		case 5:
			pchar.GenQuest.Noblelombard.Item = "an ivory cane of semiprecious stones, a gift from my grandfather";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("my ship will be back from India with the cargo hold filled with silks and spices","I will receive my interest from a European bank");
		break;
	}
}
