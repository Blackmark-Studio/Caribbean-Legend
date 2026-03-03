//Jason общий диалог мещанок
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

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
    int iTest, iTemp;
    iTest = FindColony(NPChar.City);
    ref rColony;
    string sTemp, sCity;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	String attrLoc = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "RumourAboutOwners_"))
	{
		NPChar.RumourOwnerType = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "RumourAboutOwners_TakeRumour";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("Bu kasabanın sahibi olduğun söyleniyor, "+GetSexPhrase("efendim","kaçırmak")+".","Ne hoş bir buluşma! Ne hoş bir buluşma! Vali bizzat benimle konuşuyor!");
					link.l1 = RandPhraseSimple("Fikrimi değiştirdim. İyi şanslar!","Sadece şehirde dolaşıyorum. Hoşça kal.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Sana bir sorum var.","Bazı bilgilere ihtiyacım var.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Mali konuları konuşmak istiyorum.","Paradan bahsetmek istiyorum...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
				    dialog.text = RandPhraseSimple("Ne istiyorsun? Yürümeye devam et.","Yolumu kesmeyi bırak, defol.");
					link.l1 = RandPhraseSimple("Ne yapıyorsun?","Sakin ol. Yoksa ben seni sakinleştiririm.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Sana bir şey sormak istiyorum.","Bir dakikanızı rica ediyorum, lütfen. Bir sorum olacak.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Mali konuları konuşmak istiyorum.","Finanslar hakkında...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Benim","Benim adım ","Bana   diyebilirsin ")+GetFullName(npchar)+LinkRandPhrase(". Ne istiyorsun?",".   Sizi daha önce görmemiştim "+", sen kimsin?"," . Sen kimsin ve benden ne istiyorsun?"),LinkRandPhrase("Selamlar, "+GetAddress_Form(NPChar)+" . Benim adım "+GetFullName(npchar)+". Peki senin adın ne?","Merhaba "+GetAddress_Form(NPChar)+"! Ben "+GetFullName(npchar)+". İsminizi öğrenebilir miyim?","Evet, "+GetAddress_Form(NPChar)+". Ne istiyorsun? Bu arada, adım "+GetFullName(npchar)+". Peki senin adın ne?"));
				Link.l1 = pcharrepphrase(LinkRandPhrase("Kahretsin! ","Lanet olsun! ","Kahrolası! ")+"Evet, ben kaptanım "+GetFullName(Pchar)+LinkRandPhrase(", benim adımı hiç duymadın mı, alçak?"," ve "+GetSexPhrase("en ünlü korsan","en ünlü kadın korsan")+" denizde!"," ve yanılıyorsam kahrolayım!"),LinkRandPhrase("Ben "+GetFullName(Pchar)+", kaptan.","Benim adım "+GetFullName(Pchar)+".","Bana Kaptan diyebilirsin "+GetFullName(Pchar)+"."));
				Link.l1.go = "Meeting";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("Tüm şehir diken üstünde - kraliyet müfettişi don Fernando de Alamida geldi. Bilirsin, burada çok şey gördüm ama bu... İnsanları değiştiren yas değil, onunla nasıl başa çıktıklarıdır. Söylenene göre, babasının ölümünden sonra bambaşka biri olmuş. Şimdi tüm Takımadalar'da ondan daha dürüst ve... acımasız bir Taç hizmetkarı bulamazsın.","Şu 'Kutsal Merhamet'e bir bak! Kralın bizzat özel tasarımlarla yaptırdığı söyleniyor. Ve bak - üstünde tek bir çizik yok. Sanki Meryem Ana'nın kendisi koruyor gibi. Ama bazı söylentiler duydum... Belki de koruyan Meryem değildir.","Don Fernando'yu öldürmeye kaç kez çalıştıklarını biliyor musun? Sadece geçen yıl açık denizlerde ona on iki kez saldırdılar! Ama böylesine sadık ve eğitimli bir mürettebatla, üstelik Tanrı'nın koruması altındayken - on üçüncüsünden de sağ çıkacaktır!"),LinkRandPhrase("Düydün mü? Don Fernando de Alamida şehrimize gelmiş, şu anda sokaklarda bir yerlerdeymiş diyorlar. Onu kendi gözlerimle görmek isterdim...","Don Fernando karmaşık bir adam. Kimileri onun anavatanı pislikten arındıran bir kurtarıcı olduğunu söylüyor. Diğerleri ise, babasının ölümünden sonra içinde bir şeylerin kırıldığını ve yakında hepimizin gözyaşı dökeceğini fısıldıyor. Ama sana şunu söyleyeyim: Ondan korkma. Onu böyle yapanlardan kork.","Ne kadar yakışıklı bir adam, şu don Fernando! Ama tuhaf olan ne biliyor musun? Sanki kimseyi fark etmiyor. Hep görev, hep hizmet. Bir kız olduğunu duymuştum... ama bir rahiple görüştükten sonra, dünyadaki zevklerden tamamen vazgeçmiş. Sanki yemin etmiş gibi."),RandPhraseSimple(RandPhraseSimple("Lanet müfettiş! O buradayken şehir ölü gibi. Ne ticaret var, ne eğlence. Hatta nefes almak bile sanki daha sessiz olmalı. Ve en korkuncu ne biliyor musun? Her limanda aynı bu. Tıkır tıkır işliyor. Majesteleri sanki hepimize işkence olsun diye bunu özellikle icat etmiş gibi!","Don Fernando yetimhaneyi yine ziyaret etti. Cömertçe bağış yapıyor, saatlerce dua ediyor. Böyle değerli bir adam, o lanetli zimmetçilere örnek gösterilmeli!"),RandPhraseSimple("Ha! 'Aziz' Fernando gene bütün genelevleri kapattı. Neyse, yakında buradan ayrılır, onlar da hemen tekrar açılır.","Müf... müfettiş geldi, işte olan bu! Don Fernando de Almeyda, ya da adı neydi, Alamida! O kadar önemli ki, vali bile onun etrafında parmak uçlarında dolaşıyor. Söylentilere göre gözlerinin içine bakınca bütün günahlarını bir anda görüyormuş. Korkunç!")));
					link.l1 = "...";
					link.l1.go = "exit";
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
				}
				//<== Леди Бет в порту города
			}
			else
			{
				link.l1 = "Sadece bu kasaba hakkında konuşmak istedim.";
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("Sana bir sorum var.","Biraz bilgiye ihtiyacım var.");
				if (CheckCharacterItem(pchar, "CaptainBook"))				
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
					}
					else
					{
						link.l2.go = "quests";
					}	
				}
				else
				{
					link.l2.go = "quests";//(перессылка в файл города)
				}	
				if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
	            {
	                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
	                {
						link.l3 = RandPhraseSimple("Mali konuları konuşmak istiyorum.","Finanslar hakkında...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Dinle, umarım bana yardım edebilirsin. Bir  satın almak istiyorum "+pchar.GenQuest.Device.Shipyarder.Type+", ve bana bu eşyanın sizin kasabada satıldığı söylendi. Sokak pazarında birisi bunu satıyormuş. Bununla ilgili bir bilginiz var mı?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Biliyor musun ","Farkında mısın ","Duymuş muydun ")+"yakın zamanda yerel kilisenin soyulduğunu duydun mu?");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
                dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Ah, demek sensin "+GetFullName(Pchar)+" "+GetSexPhrase("- eski dostum!","- güzelim!")+"","Seni gördüğüme sevindim, "+GetSexPhrase("eski dostum!","güzelim!")+" "+Pchar.name,"Ah, bu işte "+GetSexPhrase("bizzat kaptan","kaptanın kendisi")+" "+GetFullName(Pchar))+RandPhraseSimple(". Seni öldü sanmıştım!",". Ve belki de "+GetSexPhrase("her zamanki gibi sarhoş.","biraz sarhoş."))+LinkRandPhrase(" Devam et, neye ihtiyacın var?"," Bu sefer ne oldu?"," Yine mi rahatsız ediyorsun?"),LinkRandPhrase(TimeGreeting()+", kaptan ","Güzel bir gün dilerim, "+GetAddress_Form(NPChar)+" ","Selam, kaptan ")+GetFullName(Pchar)+LinkRandPhrase(". Size nasıl yardımcı olabilirim "+GetSexPhrase("böylesine değerli bir adam","böylesine değerli bir kız")+", senin gibi mi?",". Neden buradasın?",". Bu sefer ne öğrenmek istiyorsun?")),PCharRepPhrase(LinkRandPhrase("Merhaba, Kaptan ","Selamlar, ah, sensin demek "+GetAddress_Form(NPChar)+" ","Ah, kaptan ")+GetFullName(Pchar)+LinkRandPhrase(", bir daha asla karşılaşmayacağımızı sanmıştım, ve",", seni gördüğüme sevindim diyemem, ama",",   hâlâ hayatta olduğunu görüyorum, ne yazık ve ")+LinkRandPhrase(" Ne istiyorsun?"," neden buradasın?"," Size nasıl yardımcı olabilirim?"),LinkRandPhrase(TimeGreeting()+", kaptan "+GetFullName(Pchar)+". Size nasıl yardımcı olabilirim?","Ah, kaptan bu demek "+GetFullName(Pchar)+"! Size nasıl yardımcı olabilirim?","Selamlar, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+" . Bir şeye ihtiyacın var mı?")));  
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("Kulakların seni yanıltıyor. Gitmem gerek.","Hayır, bir şey değil, ben meyhaneye gidiyordum."),RandPhraseSimple("Pekâlâ, neyse. Bol şans!","Şehirde biraz dolaşıyorum. Hoşça kal."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "Sorular?";
			link.l1 = "Bu belgelerdeki isim sana bir şey ifade ediyor mu?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("Benim için o bilinmeyen kağıdın hiçbir önemi yok, hem okumayı da bilmem. Tefeciye git, diyorlar ki o şeytanın yazılarını okuyabiliyormuş.","Ne hakkında konuştuğunuzu bilmiyorum, kasabanın diğer sakinlerine sorun, kaptan"+GetFullName(Pchar)+".","Sana nasıl yardımcı olacağımı bile bilmiyorum, Kaptan "+GetFullName(Pchar)+"   Tefeciyle konuşmayı dene, belki bir şeyler biliyordur.");
			link.l1 = "Önerinizi büyük bir memnuniyetle takip edeceğim!";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Yalan söylemiyor musun, kaptan "+GetFullName(Pchar)+"?","Ne olmuş yani"+PChar.name+"?","Seni hatırlayacağım, "+GetFullName(Pchar)+".")+" Şimdi söyle bakalım, ne istiyorsun?",LinkRandPhrase("Sizi tanıdığıma memnun oldum, Kaptan "+PChar.name,"Sizinle tanıştığıma memnun oldum,"+GetAddress_Form(NPChar)+" "+PChar.lastname,"Memnun oldum, Kaptan "+PChar.name)+". Ama adımı öğrenmekle yetinmek istemediğine şüphem yok, değil mi?");
            link.l1 = PCharRepPhrase("Şu sizin 'kasaba' dediğiniz delikle ilgili bir şey sormak istiyorum.","Bu kasaba hakkında sana bir şey sormak istiyorum.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("Sana bir sorum var.","Biraz bilgiye ihtiyacım var.");
			if (CheckCharacterItem(pchar, "CaptainBook"))				
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
				}
				else
				{
					Link.l2.go = "quests";
				}	
			}
			else
			{
					link.l2.go = "quests";//(перессылка в файл города)
			}			
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
					link.l3 = RandPhraseSimple("Mali konuları konuşmak istiyorum.","Mali durumlar hakkında...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Dinle, umarım bana yardımcı olabilirsin. Bir tane satın almak istiyorum "+pchar.GenQuest.Device.Shipyarder.Type+" ve bana bu şeyin sizin kasabada satıldığı söylendi. Birisi sokaklarda satıyormuş. Bu konuda bir bilginiz var mı?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор

			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = RandPhraseSimple("Biliyor musun ","Farkında mısın ","Duymuş muydun ")+" yakın zamanda yerel kilisenin soyulduğunu duydun mu?");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			Link.l6 = PCharRepPhrase(RandPhraseSimple("Kulakların seni yanıltıyor. Gitmem gerek.","Hayır, önemli bir şey değil, ben meyhaneye gidiyordum."),RandPhraseSimple("Pekala, önemli bir şey değil. İyi şanslar!","Şehirde biraz dolaşıyorum. Hoşça kal."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Ah, seni gördüğüme de, bir içki içeceğim için de çok sevindim, ne istersen sor.","Konuşmayı seviyorsun, kaptan? Ben de... Özellikle bir bardak rom eşliğinde.","Evet, "+PChar.name+"?"),RandPhraseSimple("Daha ne istiyorsun?","Alırım, kaptan "+PChar.name+", sohbet etmekten hoşlandığını mı düşünüyorsun?")),PCharRepPhrase(LinkRandPhrase("Daha ne istiyorsun "+GetAddress_Form(NPChar)+"?","Dinliyorum, kaptan.","Gitmem gerek, o yüzden çabuk sor, Kaptan."),LinkRandPhrase("Hoş sohbet birine her zaman memnun olurum, "+GetAddress_Form(NPChar)+" "+PChar.lastname+" . Konuş.","Evet, "+GetAddress_Form(NPChar)+"?","Konuşmayı seviyor musun, kaptan? Ben de... ")));
			link.l1 = LinkRandPhrase("Bu kasabada hangi dedikodular dolaşıyor?","Bu taraflarda yeni bir haber var mı?","Karada hayat nasıl gidiyor?");
			link.l1.go = "rumours_towngirl";
			link.l2 = LinkRandPhrase("Bana yolu gösterebilir misiniz?","Bir yere giden yolu bulamıyorum...","Beni bir yere götürmeme yardım et...");
			link.l2.go = "town";  //(перессылка в файл города)
			link.l3 = RandPhraseSimple("Bir kişi hakkında insanların ne söylediğini bilmek istiyorum.","Bir kişi hakkında insanların ne söylediğini biliyor musun?");
			link.l3.go = "info"; //(перессылка в файл города)
			link.l4 = RandPhraseSimple("Buradaki yerliler hakkında daha fazla bilgi almak istiyorum.","Buralılar hakkında bana bir şeyler anlatabilir misin?");
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple("Kulakların seni yanıltıyor. Gitmem gerek.","Hayır, bir şey değil, meyhaneye gidiyordum."),RandPhraseSimple("Pekala, önemli bir şey değil. İyi şanslar!","Şehirde dolaşıyorum sadece. Hoşça kal."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "Kiminle ilgileniyorsun?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "Valinin hakkında daha fazla bilgi almak istiyorum.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "Yerel meyhanenin sahibi hakkında daha fazla bilgi almak istiyorum.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "Limandaki ustabaşı hakkında daha fazla bilgi almak istiyorum.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "Yerel dükkân sahibini daha yakından tanımak istiyorum.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "Önemli değil. Boşver gitsin.";
			link.l9.go = "exit";
		break;
			
		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "Teşekkürler.";
			link.l1.go = "exit";
			// Здесь можно делать проверка по квестам, какой слух выпал
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "Hm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Hiç duymadım... Uzun zamandır burada yaşıyorum, ama öyle bir şey hiç görmedim.";
			link.l1 = "Eh, bu bir gemi yapım aracı, "+pchar.GenQuest.Device.Shipyarder.Describe+"Kasabada böyle bir şeyi satan ya da yanında taşıyan birini gördünüz mü, dikkatinizi çeken oldu mu?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Hm... Evet, o aletle dolaşan bir adamı birkaç saat önce gördüm. Sokaklarda yürüyordu. İlginç bir aletmiş.";
				link.l1 = "Neye benziyordu ve nereye gidiyordu? Gerçekten böyle bir bilgiye ihtiyacım var.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Hayır, öyle bir şey görmedim.";
				link.l1 = "Anladım. O zaman sormaya devam edeceğim.";
				link.l1.go = "exit";
			}
		break;
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("Hayır, bununla ilgili hiçbir şey bilmiyorum.","Hayır, gitmeliyim.","Hiçbir şey bilmiyorum.");
					link.l1 = LinkRandPhrase("İyiyim, sağ ol.","Anladım, teşekkür ederim.","Pekala, affedersiniz.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("Bu konuda hiçbir şey bilmiyorum, ama meyhanedeki müdavimlere sorabilirsin, sana kesinlikle daha fazlasını anlatacaklardır.","Sana hiçbir şey söyleyemem, meyhanedekilere sor.");
				link.l1 = "Bunun için teşekkürler.";
				link.l1.go = "exit";
			}
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dinle, bu kasabanın bir vatandaşı olarak senden kılıcını kınına sokmanı rica ediyorum.","Dinle, bu kasabanın bir vatandaşı olarak senden kılıcını kınına koymanı rica ediyorum.");
				link.l1 = LinkRandPhrase("Pekâlâ.","Nasıl isterseniz.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Silahla koşarken dikkatli ol. Bu beni tedirgin ediyor...","Tanımadığım bir adam önümden kınasız bir silahla yürüyünce hoşlanmıyorum. Bu beni korkutuyor...");
				link.l1 = RandPhraseSimple("Anladım.","Endişelenme.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}
