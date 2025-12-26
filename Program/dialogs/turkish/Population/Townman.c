//Jason общий диалог мещан
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
    string sTemp, sCity, sTitle;
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
				    dialog.text = RandPhraseSimple("Bu kasabanın sahibi olduğun söyleniyor, "+GetSexPhrase("efendim","kaçırmak")+".","Ne hoş bir karşılaşma, "+GetSexPhrase("beyefendi","miss")+"!");
					link.l1 = RandPhraseSimple("Fikrimi değiştirdim. İyi şanslar!","Şehirde dolaşıyorum sadece. Hoşça kal.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Sana bir sorum var.","Biraz bilgiye ihtiyacım var.");
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
				else
				{ // пираты, не наши
					if (sti(pchar.GenQuest.Piratekill) > 20)
					{
						dialog.text = RandPhraseSimple("Alarm! Silahlı bir deli burada! Silah başına!","Silaha sarılın! Burada silahlı bir deli var!");
						link.l1 = RandPhraseSimple("Ne?!","Ne yapıyorsun?!");
						link.l1.go = "pirate_fight";
					}
					else
					{
						dialog.text = RandPhraseSimple("Ne istiyorsun? Yürü git.","Yolumu kesmeyi bırak, defol.");
						link.l1 = RandPhraseSimple("Biliyor musun? Havlama!","Sakin ol. Yoksa ben seni sakinleştiririm!");
						link.l1.go = "exit";
						link.l2 = RandPhraseSimple("Sana bir şey sormak istiyorum.","Bir anlığınıza ihtiyacım var, lütfen. Bir soru.");
						link.l2.go = "quests";//(перессылка в файл города)
						if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
						{
							if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
							{
								link.l3 = RandPhraseSimple("Mali konuları konuşmak istiyorum.","Paradan bahsetmek istiyorum...");
								link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
							}
						}
					}
				}
				break;
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && or(IsWarShipType(pchar), IsRaiderShipType(pchar))) ok = false;
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Townpassenger") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)//горожанин-пассажир
				{
					dialog.text = "Günaydın, "+GetAddress_Form(NPChar)+". Kendi geminizin kaptanı olduğunuzu görüyorum. Sizden bir iyilik isteyeceğim...";
					link.l1 = "Dinliyorum, "+GetAddress_FormToNPC(NPChar)+". Ne istiyorsun?";
					link.l1.go = "passenger";
					link.l2 = "Üzgünüm, "+GetAddress_FormToNPC(NPChar)+", ama acelem var.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}

                // homo 05/08/06
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Ben ","Benim adım ","Bana   diyebilirsin ")+GetFullName(npchar)+LinkRandPhrase(". Ne istiyorsun?",".   Sizi daha önce görmemiştim.   Kimsiniz?",". Sen kimsin ve benden ne istiyorsun?"),LinkRandPhrase("Selamlar, "+GetAddress_Form(NPChar)+" . Benim adım "+GetFullName(npchar)+". Peki senin adın ne?","Merhaba, "+GetAddress_Form(NPChar)+"! Ben "+GetFullName(npchar)+". İsminizi öğrenebilir miyim?","Evet, "+GetAddress_Form(NPChar)+". Ne istiyorsun? Bu arada, adım "+GetFullName(npchar)+" . Peki senin adın ne? "));

				Link.l1 = pcharrepphrase(LinkRandPhrase("Lanet olsun! ","Lanet olsun! ","Lanet olsun sana! ")+"Evet, kaptan benim "+GetFullName(Pchar)+LinkRandPhrase(", hiç duymadın mı "+NPCharSexPhrase(NPChar,", piç?","?")," ve "+GetSexPhrase("en ünlü korsan","en ünlü kadın korsan")+" denizde!"," ve yanılıyorsam kahrolayım!"),LinkRandPhrase("Ben "+GetFullName(Pchar)+", kaptan.","Benim adım "+GetFullName(Pchar)+".","Bana kaptan diyebilirsin "+GetFullName(Pchar)+"."));
				Link.l1.go = "Meeting";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("Tüm şehir diken üstünde - kraliyet müfettişi don Fernando de Alamida geldi. Bilirsin, burada çok şey gördüm ama bu... İnsanları değiştiren acı değil, onunla nasıl başa çıktıklarıdır. Söylenene göre, babasının ölümünden sonra bambaşka biri olmuş. Şimdi tüm Takımadalar'da ondan daha dürüst ve... acımasız bir Taç hizmetkârı bulamazsın.","Şu 'Kutsal Merhamet'e bir bak! Kralın bizzat özel tasarımlarla inşa edilmesini emrettiğini söylüyorlar. Ve bak - üstünde tek bir çizik yok. Sanki Meryem Ana'nın kendisi koruyor gibi. Ama bazı söylentiler duydum... Belki de koruyan Meryem değildir.","Don Fernando'u öldürmeye kaç kez teşebbüs ettiklerini biliyor musun? Sadece geçen yıl açık denizlerde ona on iki kez saldırdılar! Ama böylesine sadık ve eğitimli bir mürettebatla, bir de Tanrı'nın korumasıyla - on üçüncüsünden de sağ çıkacaktır!"),LinkRandPhrase("Düydün mü? Don Fernando de Alamida şehrimize gelmiş, şu anda sokaklarda bir yerlerdeymiş diyorlar. Onu kendi gözlerimle görmek isterdim...","Zor bir adam bu don Fernando. Kimileri onun Anavatanı pislikten arındıran bir kurtarıcı olduğunu söylüyor. Diğerleri ise babasının ölümünden sonra içinde bir şeylerin kırıldığını ve yakında hepimizin ağlayacağını fısıldıyor. Ama sana şunu söyleyeyim: Ondan korkma. Onu böyle yapanlardan kork.","Ne kadar yakışıklı bir adam, şu don Fernando! Ama biliyor musun, tuhaf olan ne? Sanki kimseyi fark etmiyor. Hep görev, hep hizmet. Bir kız olduğunu duymuştum... ama bir rahiple görüştükten sonra, dünyevi zevklerden tamamen vazgeçmiş. Sanki bir yemin etmiş gibi."),RandPhraseSimple(RandPhraseSimple("Lanet müfettiş! O buradayken şehir ölü gibi oluyor. Ne ticaret var, ne eğlence. Nefes almak bile sanki daha sessiz olmalı. Ve biliyor musun, en korkutucu olan ne? Her limanda aynı bu. Saat gibi işliyor. Majesteleri sanki hepimize işkence olsun diye bunu bilerek icat etmiş gibi!","Don Fernando yetimhaneyi yine ziyaret etti. Cömertçe bağış yapıyor, saatlerce dua ediyor. Böyle değerli bir adam, o lanetli zimmetçilere örnek gösterilmeli!"),RandPhraseSimple("Ha! 'Aziz' Fernando gene bütün genelevleri kapattı. Neyse, yakında çekip gider, onlar da hemen tekrar açılır.","Müf... müfettiş geldi, işte olan bu! Don Fernando de Almeyda, ya da adı neydi, Alamida! O kadar önemli ki vali bile yanında dikkatli davranıyor. Söylentilere göre gözlerinin içine bakıp bütün günahlarını bir anda görebiliyormuş. Korkunç!")));
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
				link.l1 = PCharRepPhrase("Sadece şu 'kasaba' dediğiniz delikle ilgili bir şey sormak istiyorum.","Bu kasaba hakkında sana bir şey sormak istiyorum.");
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
						link.l3 = RandPhraseSimple("Mali konuları konuşmak istiyorum.","Mali işler hakkında...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Dinle, umarım bana yardımcı olabilirsin. Bir  satın almak istiyorum "+pchar.GenQuest.Device.Shipyarder.Type+", ve bana bu şeyin sizin kasabada satıldığı söylendi. Yani, birisi bunu sokaklarda satıyormuş. Bir bilginiz var mı?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Biliyor musun ","Farkında mısın ","Duymuş muydun ")+" yakın zamanda yerel kilisenin soyulduğunu duydun mu? ";
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Ah, demek sensin "+GetFullName(Pchar)+" "+GetSexPhrase("- eski dostum!","- güzelim!")+"","Seni gördüğüme sevindim, "+GetSexPhrase("eski dostum!","güzelim!")+" "+Pchar.name,"Ah, bu işte "+GetSexPhrase("kaptanın kendisi","kaptanın kendisi")+" "+GetFullName(Pchar))+RandPhraseSimple(". Seni öldü sanmıştım!",". Ve belki de "+GetSexPhrase("Her zamanki gibi sarhoşsun.","biraz sarhoş."))+LinkRandPhrase(" Devam et, neye ihtiyacın var?"," Bu sefer ne oldu?"," Yine mi rahatsız ediyorsun?"),LinkRandPhrase(TimeGreeting()+", kaptan ","İyi günler dilerim, "+GetAddress_Form(NPChar)+" ","Selam, Kaptan ")+GetFullName(Pchar)+LinkRandPhrase(". Size nasıl yardımcı olabilirim "+GetSexPhrase("böylesine değerli bir adam","böylesine değerli bir kız")+", senin gibi mi?",". Neden buradasın?",". Bu sefer neyi öğrenmek istiyorsun?")),PCharRepPhrase(LinkRandPhrase("Merhaba, Kaptan ","Selamlar, ah, demek sensin "+GetAddress_Form(NPChar)+" ","Ah, kaptan ")+GetFullName(Pchar)+LinkRandPhrase(", bir daha asla karşılaşamayacağımızı sanmıştım, ve",", seni gördüğüme sevindim diyemem ama",",   hâlâ hayatta olduğunu görüyorum, ne yazık, ve ")+LinkRandPhrase(" ne istiyorsun?"," neden buradasın?"," Size nasıl yardımcı olabilirim?"),LinkRandPhrase(TimeGreeting()+", kaptan "+GetFullName(Pchar)+". Size nasıl yardımcı olabilirim?","Ah, işte kaptan geldi "+GetFullName(Pchar)+"! Size nasıl yardımcı olabilirim?","Selamlar, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+" . Bir şey ister misin?")));  
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("Kulakların seni yanıltıyor. Gitmem gerek.","Hayır, bir şey yok, sadece meyhaneye gidiyordum."),RandPhraseSimple("Pekâlâ, neyse. İyi şanslar!","Şehirde biraz dolaşıyorum. Hoşça kal."));
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
			dialog.text = LinkRandPhrase("Bir kağıttan bana ne, hem zaten okumam yok. Tefeciye git, harflerden anlıyormuş diyorlar, ha!","Ne hakkında konuştuğunu bilmiyorum, başkasına sor, kaptan"+GetFullName(Pchar)+".","Sana nasıl yardımcı olacağımı bilmiyorum, Kaptan "+GetFullName(Pchar)+"   Tefeciyle konuşmayı dene, belki bir şeyler biliyordur. ");
			link.l1 = "Teşekkürler.";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Kaptan, yalan söylemiyor musun "+GetFullName(Pchar)+"?","Ee, ne olmuş yani "+PChar.name+"?","Seni hatırlayacağım, "+GetFullName(Pchar)+".")+" Şimdi söyle bakalım, ne istiyorsun?",LinkRandPhrase("Sizi tanıdığıma memnun oldum, Kaptan "+PChar.name,"Tanıştığımıza memnun oldum, "+GetAddress_Form(NPChar)+" "+PChar.lastname,"Memnun oldum, Kaptan "+PChar.name)+". Ama sanırım sadece adımı öğrenmek istemedin, değil mi?");
            link.l1 = PCharRepPhrase("Bu 'kasaba' dediğiniz bu berbat yer hakkında bir şey sormak istiyorum.","Bu kasaba hakkında sana bir şey sormak istiyorum.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("Sana bir sorum var.","Bazı bilgilere ihtiyacım var.");
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
   				link.l16 = "Dinle, umarım bana yardımcı olabilirsin. Bir  satın almak istiyorum "+pchar.GenQuest.Device.Shipyarder.Type+", ve bana bu şeyin sizin kasabada satıldığı söylendi. Birisi sokaklarda satıyormuş. Bunun hakkında bir şey biliyor musunuz?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("Biliyor musun ","Farkında mısın ","Duymuş muydun ")+" yakın zamanda yerel kilisenin soyulduğunu duydun mu?";
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("Kulakların seni yanıltıyor. Gitmem gerek.","Hayır, önemli bir şey değil, meyhaneye gidiyordum."),RandPhraseSimple("Pekala, önemli bir şey değil. İyi şanslar!","Sadece şehirde dolaşıyorum. Hoşça kal."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Ah, seni görmek de bir içki kadar iyi geldi, ne istersen sor.","Konuşmayı seviyorsun, kaptan? Ben de... Özellikle bir bardak rom eşliğinde.","Evet, "+PChar.name+"?"),LinkRandPhrase("Daha ne istiyorsun?","Alırım, kaptan "+PChar.name+", sohbet etmeyi sevdiğin doğru mu?")),PCharRepPhrase(LinkRandPhrase("Daha ne istiyorsun, "+GetAddress_Form(NPChar)+"?","Dinliyorum, kaptan.","Gitmem gerek, o yüzden çabuk sor, Kaptan."),LinkRandPhrase("Hoş sohbetten her zaman memnun olurum, "+GetAddress_Form(NPChar)+" "+PChar.lastname+" . Konuş.","Evet, "+GetAddress_Form(NPChar)+"?","Konuşmayı seviyor musun, kaptan? Ben de... ")));
			link.l1 = LinkRandPhrase("Bu kasabada hangi söylentiler dolaşıyor?","Bu taraflarda yeni bir haber var mı?","Karada hayat nasıl?");
			link.l1.go = "rumours_townman";
			link.l2 = LinkRandPhrase("Bana yolu gösterebilir misin?","Bir yere giden yolu bulamıyorum...","Beni bir yere götürmeme yardım et...");
			link.l2.go = "town";  //(перессылка в файл города)
			link.l3 = RandPhraseSimple("Bir kişi hakkında insanların ne söylediğini bilmek istiyorum.","Birisi hakkında insanların ne dediğini biliyor musun?");
			link.l3.go = "info"; //(перессылка в файл города)
			link.l4 = RandPhraseSimple("Buradaki yerliler hakkında daha fazla bilgi almak istiyorum.","Buralılar hakkında bana bir şey söyleyebilir misin?");
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple("Kulakların seni yanıltıyor. Gitmem gerek.","Hayır, bir şey yok, meyhaneye gidiyorum."),RandPhraseSimple("Pekala, önemli bir şey değil. İyi şanslar!","Sadece şehirde dolaşıyorum. Hoşça kal."));
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
				link.l3 = "Yerel tersane ustası hakkında daha fazla bilgi almak istiyorum.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "Yerel dükkân sahibini daha yakından tanımak istiyorum.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "Önemli değil. Unut gitsin.";
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
           dialog.text = "Hm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Hiç duymadım... Uzun zamandır burada yaşıyorum, ama hiç öyle bir şey görmedim.";
			link.l1 = "Eh, bu bir gemi yapım aracı, "+pchar.GenQuest.Device.Shipyarder.Describe+" . Kasabada böyle bir şeyi satan oldu mu? Ya da belki birinin yanında taşıdığını gördünüz mü?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Hm... Evet, o aletle dolaşan bir adamı birkaç saat önce gördüm. Sokaklarda yürüyordu. İlginç bir aletmiş gerçekten.";
				link.l1 = "Nasıl biriydi ve nereye gidiyordu? Gerçekten böyle bir bilgiye ihtiyacım var.";
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
					link.l1 = LinkRandPhrase("İyiyim, teşekkürler.","Anladım, teşekkür ederim.","Peki, affedersiniz.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Bu konuda hiçbir şey bilmiyorum, ama meyhanedeki müdavimlere sorabilirsin, kesinlikle sana daha fazlasını anlatacaklardır.","Sana hiçbir şey söyleyemem, meyhanedekilere sor.");
				link.l1 = "Bunun için teşekkürler.";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//-------------------------------горожанин-пассажир----------------------------------------------
		case "passenger":
			if (hrand(19) > 9) SetPassengerParameter("Townpassenger", false);
			else SetPassengerParameter("Townpassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity"))
			{
				dialog.text = "Kaptan,   şu   adı   geçen   koloniye   gitmem   gerekiyor "+XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City)+", mümkün olan en kısa sürede, bu iş üstünde "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Dat")+", içinde "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+" . Gemin çoğu burada gezen küçük teknelerle kıyaslandığında sağlam görünüyor. Sana ödeme yapabilirim "+FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money))+". Ne dersin?";
			}
			else
			{
				dialog.text = "Kaptan, kolonye gitmem gerekiyor "+XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City)+", bu bir "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc")+", bir "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+". Biliyorum, bu kulağa son derece riskli geliyor, ama belki de "+FindRussianDublonString(sti(pchar.GenQuest.Townpassenger.Money))+"   sana güzel bir destek olurdu, değil mi?";
			}
			link.l1 = "Hm. Ben de bu tarafa gidiyorum, bu şartlarda seni gemime alabilirim.";
			link.l1.go = "passenger_1";
			link.l2 = "Üzgünüm,  "+GetAddress_FormToNPC(NPChar)+", ama ben başka bir yöne gidiyorum. Sana yardımcı olamam.";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "Ne yazık. Peki, başka bir gemiyi bekleyeceğim. Hoşça kal.";
			link.l1 = "Görüşürüz.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Townpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Harika, çünkü beklemekten yoruldum. Oraya vardığımızda ödemenizi alacaksınız.";
			link.l1 = "Gemiye git, "+GetAddress_FormToNPC(NPChar)+". Yakında ayrılıyoruz.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Townpassenger.id = npchar.id;
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
			AddQuestUserDataForTitle(sTitle, "sType", "citizen");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Townpassenger.City) + ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc")+"."; // belamour gen
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Townpassenger.Money)));
			pchar.quest.Townpassenger.win_condition.l1 = "location";
			pchar.quest.Townpassenger.win_condition.l1.location = pchar.GenQuest.Townpassenger.City+"_town";
			pchar.quest.Townpassenger.function = "Townpassenger_complete";
			SetFunctionTimerCondition("Townpassenger_Over", 0, 0, sti(pchar.GenQuest.Townpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Townpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "İşte geldik, harika! Geminizdeki bu yolculuk oldukça keyifliydi. Teşekkür ederim. Alın paranızı, efendim.";
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
			if (CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Townpassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Townpassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Townpassenger");
		break;
//<-- горожанин-пассажир
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dinle, bu kasabanın bir vatandaşı olarak senden kılıcını kınına koymanı istiyorum.","Dinle, bu kasabanın bir vatandaşı olarak senden kılıcını kınına sokmanı istiyorum.");
				link.l1 = LinkRandPhrase("Pekala.","Dediğiniz gibi olsun.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Silahla koşarken dikkatli ol. Bu beni tedirgin ediyor...","Önümde çıplak kılıçla dolaşan bir yabancıdan hiç hoşlanmam...");
				link.l1 = RandPhraseSimple("Anladım.","Endişelenme.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		case "pirate_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;

	}
}
