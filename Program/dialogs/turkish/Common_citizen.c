// boal 25/04/04 общий диалог горожан
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
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    int iTest, iTemp;
    iTest = FindColony(NPChar.City); // город
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
            /*if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("Bir casus mu? Muhafızlar!","Alarm! Bir davetsiz misafir var!");
				link.l1 = "Kapa çeneni. Gidiyorum.";
				link.l1.go = "fight";
				break;
			}*/
			
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("Bu kasabayı yönetenin sen olduğunu söylüyorlar, "+GetSexPhrase("bey","miss")+".","Ne hoş bir karşılaşma, şehir başkanı bana bir soru ile yaklaştı.");
					link.l1 = RandPhraseSimple("Fikrimi değiştirdim.","Ben sadece bu kasabayı keşfediyorum. Hoşça kal.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Sana bir sorum var.","Bilgiye ihtiyacım var.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Biraz iş konuşmak istiyorum.","Mali durum hakkında...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
				    dialog.text = RandPhraseSimple("Ne istiyorsun? Yürümeye devam et.","Yolumdan çekil, kaybol!");
					link.l1 = RandPhraseSimple("Hey, havlama artık, olur mu?","Sakin ol, yoksa pişman olabilirsin!");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Sana bir sorum var.","Bir dakikanızı rica ediyorum, lütfen. Size bir sorum var.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Bir işi konuşmak istiyorum.","Mali durum hakkında...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";

                // homo 05/08/06
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Benim adım ","Benim adım ","Bana   diyebilirsin ")+GetFullName(npchar)+LinkRandPhrase(". Ne istiyorsun?",". Henüz yapmadım "+NPCharSexPhrase(NPChar,"Seni burada daha önce görmüştüm","Seni orada daha önce görmüştüm")+", sen kimsin?",". Sen kimsin, benden ne istiyorsun?"),LinkRandPhrase("Selamlar, "+GetAddress_Form(NPChar)+" . Benim adım "+GetFullName(npchar)+". Seninki ne?","Merhaba, "+GetAddress_Form(NPChar)+"! Ben "+GetFullName(npchar)+" . İsminizi öğrenebilir miyim?","Evet, "+GetAddress_Form(NPChar)+". Ne istiyorsun? Bu arada, adım "+GetFullName(npchar)+". Peki sen kimsin?"));

				Link.l1 = pcharrepphrase(LinkRandPhrase("Vay canına! ","Lanet olsun! ","Sana lanet olsun! ")+"Evet, ben Kaptanım "+GetFullName(Pchar)+LinkRandPhrase(", gerçekten de beni hiç duymamışsın"+NPCharSexPhrase(NPChar,", seni serseri?","?")," ve "+GetSexPhrase("en azılı korsan","en ünlü kadın korsan")+" bu sularda! "," ve eğer bu doğru değilse, cehennemde yanayım!"),LinkRandPhrase("Ben Kaptanım"+GetFullName(Pchar)+".","Benim adım "+GetFullName(Pchar)+".","Bana Kaptan diyebilirsin "+GetFullName(Pchar)));

                //LinkRandPhrase("I am Captain" + GetFullName(Pchar) + ".", "My name is " + GetFullName(Pchar) + ".", "You may call me Captain " + GetFullName(Pchar));
				Link.l1.go = "Meeting";
			}
			else
			{
				if(rand(5) == 1 && NPChar.sex == "woman" && !CheckAttribute(NPChar, "CitizenFindItem.NoQuest") && !CheckAttribute(PChar, "GenQuest.CitizenFindItem.StartQuest") && CheckAttribute(NPChar, "City"))
				{
					dialog.Text = "Kaptan, bana yardımcı olur musunuz?";
					link.l1 = LinkRandPhrase("Üzgünüm, hayır. Fazla vaktim yok.","Üzgünüm, yapamam. Çok meşgulüm.","Hayır, yapamam. Dikkatimi gerektiren acil işlerim var.");
					link.l1.go = "CitizenFindItem_NoQuest";
					link.l2 = LinkRandPhrase("Tabii, yapabilirim. Sorun ne?","Evet, sana yardım edeceğim. Bu işin hakkında bana daha fazla anlat.","Bana işinizden biraz daha bahseder misiniz...");
					link.l2.go = "CitizenFindItem_1";
					NextDiag.TempNode = "First time";
					break;
				}
				
				if(CheckAttribute(PChar, "GenQuest.CitizenFindItem.CitizenID") && PChar.GenQuest.CitizenFindItem.CitizenID == NPChar.ID && CheckCharacterItem(PChar, "DOjeronRing"))
				{
					dialog.Text = "Evet, Kaptan, dinliyorum.";
					link.l1 = NPChar.name+", evlilik yüzüğünü buldum.";
					link.l1.go = "CitizenFindItem_Complete_1";
					break;
				}
			
				link.l1 = PCharRepPhrase("Bu kasaba hakkında daha fazla şey öğrenmek istiyorum.","Bu kasaba hakkında bana anlat.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("Sana bir sorum var.","Bilgiye ihtiyacım var.");
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
						link.l3 = RandPhraseSimple("Bir iş konuşmak istiyorum.","Mali durum hakkında...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
				if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	            {
					link.l4 = NPCharSexPhrase(npchar,LinkRandPhrase("Dur bir! Kim olduğunu hemen söyle! Valinin isteği üzerine bir düşman casusunu arıyorum "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Dur! Kasabanın çıkarları için hareket ediyorum "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" vali emriyle. Şehirde düşman bir ajan arıyorum.","Dur, dostum! Yerel vali "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" kasabada bir casus bulmak istiyor."),LinkRandPhrase("Dur bir dakika, hanımefendi! Kim olduğunu hemen söyle! Valinin isteğiyle bir düşman casusunu arıyorum "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Hanımefendi, sizi alıkoymam gerek! Kasabanın iyiliği için hareket ediyorum "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" valinin emriyle. Şehirde düşman bir ajan arıyorum","Kıpırdama, güzelim! Yerel vali "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" kasabada bir casus bulmak istiyor..."));
					link.l4.go = "SitySpy";
				}
				// <-- квестовый генератор мэра, поиск шпиёна на улице
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Belki bana biraz tavsiye verebilirsin. Satın almak istiyorum "+pchar.GenQuest.Device.Shipyarder.Type+", ve bana kasabanızda satıldığı söylendi. Birisi sokaklarda satıyormuş. Bunun hakkında bir bilginiz var mı?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Farkında mısın","Biliyor muydun","Duymuş muydun")+" yakınlardaki bir kilisenin yakın zamanda yağmalandığını duydun mu? ");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
                dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Ah, sensin demek, "+GetFullName(Pchar)+" "+GetSexPhrase(", yaşlı düzenbaz","- ateşli hanımefendi")+"","Seni tekrar görmek güzel, "+GetSexPhrase("ahbap","güzellik")+" "+Pchar.name,"Ah, bu iyi eski "+GetSexPhrase("Kaptan","hanımefendi")+" "+GetFullName(Pchar))+LinkRandPhrase(". Seni ölmüş sanmıştım!",". Ve elbette, "+GetSexPhrase("Her zamanki gibi sarhoş.","zaten keyfim yok.")+"",". Ve gördüğüm kadarıyla, hâlâ özgürsün!")+LinkRandPhrase(" Söyle bakalım – neye ihtiyacın var?"," Bu sefer neye ihtiyacın var?"," Yine boş yere mi başımı ağrıtıyorsun?"),LinkRandPhrase(TimeGreeting()+", Kaptan ","Merhaba, "+GetAddress_Form(NPChar)+" ","Sizi selamlıyorum, Kaptan ")+GetFullName(Pchar)+LinkRandPhrase(". Ne olabilir ki "+GetSexPhrase("böylesine centilmen bir beyefendi","böylesine alımlı bir hanımefendi")+", gibi mi? Benden isteyebileceğin bir şey var mı?",". Seni buraya ne getirdi?"," . Bu sefer ne öğrenmek istiyorsun?")),PCharRepPhrase(LinkRandPhrase("Merhaba, Kaptan ","Merhaba. Ah, sensin demek "+GetAddress_Form(NPChar)+" ","Ah, Kaptan ")+GetFullName(Pchar)+LinkRandPhrase(", düşündüm"+NPCharSexPhrase(NPChar," "," ")+"bir daha asla karşılaşmayacaktık,",", memnun olduğumu söyleyemem"+NPCharSexPhrase(NPChar," "," ")+"seni görmek, ama",", anladım, hâlâ hayattasın. Ne yazık. Peki,")+LinkRandPhrase(" neye ihtiyacın var?"," ne için geldin?"," ne yapabilirim "+NPCharSexPhrase(NPChar,"size nasıl yardımcı olabilirim?","size nasıl yardımcı olabilirim?")),LinkRandPhrase(TimeGreeting()+", Kaptan "+GetFullName(Pchar)+" . Size nasıl yardımcı olabilirim?","Ah, bu da kimmiş"+GetSexPhrase("","")+" Kaptan "+GetFullName(Pchar)+"! Bu sefer ne öğrenmek istersiniz?","Merhaba, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+" . Bir şey mi istediniz?")));                         
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("Hayır, hayal görüyorsun. Ben artık gideceğim.","Hayır, hiçbir şey – sadece gidiyordum"+GetSexPhrase("","")+" meyhaneye. "),RandPhraseSimple("Hayır, hiçbir şey yok. Sana bol şans!","Sadece etrafa bakıyorum. Hoşça kal."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "Hangi sorular?";
			link.l1 = "Bu belgelerdeki isim sana bir şey ifade ediyor mu?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("Yabancı kağıtlardan anlamam. Hem, okuma yazmam yok. Git tefeciye sor, o şeytan kesin okuma yazma biliyordur.","Neden bahsettiğiniz hakkında hiçbir fikrim yok. Kasaba halkına sorun, Kaptan "+GetFullName(Pchar)+".","Sana nasıl yardımcı olacağımı gerçekten bilmiyorum, Kaptan "+GetFullName(Pchar)+". Gidip tefeciye sor – belki o biliyordur.");
			link.l1 = "Seve seve tavsiyene uyacağım!";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Ama yalan söylemiyor musun, Kaptan "+GetFullName(Pchar)+"?","Eee, ne olmuş yani, "+PChar.name+"?","Seni hatırlayacağım, "+GetFullName(Pchar)+".")+"Ve şimdi, neye ihtiyacın var?",LinkRandPhrase("Sizi tanımak bir zevk, Kaptan "+PChar.name,"Memnun oldum"+NPCharSexPhrase(NPChar," "," ")+" tanıştığıma memnun oldum, "+GetAddress_Form(NPChar)+" "+PChar.lastname,"Sizi tanıdığıma memnun oldum, Kaptan "+PChar.name)+" . Ama sanırım buraya sadece adımı öğrenmek için gelmedin?");

            link.l1 = PCharRepPhrase("İstedim "+GetSexPhrase("","")+" şu kasaba dediğiniz deliği biraz tanımak istiyorum!","İstedim "+GetSexPhrase("","")+" bu kasaba hakkında bir şeyler bilmek.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("Sana bir sorum var.","Bilgiye ihtiyacım var.");
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
					link.l3 = RandPhraseSimple("Bir iş konuşmak istiyorum.","Mali durumlar hakkında...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Belki bana biraz tavsiye verebilirsin. Satın almak istiyorum "+pchar.GenQuest.Device.Shipyarder.Type+", ve bana kasabanızda satıldığı söylendi. Yani, birisi sokaklarda satıyormuş. Bunun hakkında bir şey biliyor musunuz?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	        {
				link.l4 = NPCharSexPhrase(npchar,LinkRandPhrase("Dur bir! Kim olduğunu hemen söyle! Valinin isteği üzerine bir düşman casusunu arıyorum "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Dur! Ben hareket ediyorum, çünkü"+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" vali emriyle. Şehirde düşman bir ajan arıyorum.","Dur, dostum! Yerel vali "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" kasabada bir casus bulmak istiyor."),LinkRandPhrase("Dur bir dakika, hanımefendi! Kim olduğunu hemen söyle! Valinin isteğiyle bir düşman casusunu arıyorum "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Hanımefendi, sizi alıkoymak zorundayım! Şehrin çıkarları için hareket ediyorum "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" vali emriyle. Şehirde düşman bir ajan arıyorum.","Dur, güzel kadın! Yerel vali "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" kasabada bir casus aramak istiyor..."));
				link.l4.go = "SitySpy";
			}
			// <-- квестовый генератор мэра, поиск шпиёна на улице
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("Farkında mısın","Duymuş muydun","Duydun mu")+" yakınlardaki bir kilisenin yakın zamanda soyulduğunu duydun mu?");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("Hayır, hayal görüyorsun. Şimdi gidiyorum.","Hayır, hiçbir şey - sadece meyhaneye gidiyordum."),RandPhraseSimple("Hayır, hiçbir şey yok. Sana bol şans!"," Sadece etrafa bakıyordum. Hoşça kal. "));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Ah evet, ben de neredeyse o kadar mutluyum"+NPCharSexPhrase(NPChar," "," ")+"Seni bir kadeh içki gibi görmek. Ne istersen sor.","Konuşmayı sever misin, Kaptan? Ben de... Özellikle bir bardak rom eşliğinde.","Evet, "+PChar.name+"?"),LinkRandPhrase("Ne istiyorsun?","Anladım, Kaptan "+PChar.name+". Sen"+GetSexPhrase("","")+"   tam bir gevezesin. ","Beni yordun"+GetSexPhrase("","")+" sorularınla, Kaptan. En iyisi bana rom konusunda yardım et.")),PCharRepPhrase(LinkRandPhrase("Ne bilmek istiyorsun "+GetAddress_Form(NPChar)+"?","Sizi dinliyorum, Kaptan.","Gitmem gerekiyor, o yüzden lütfen çabuk olun, Kaptan."),LinkRandPhrase("Her zaman memnuniyetle"+NPCharSexPhrase(NPChar," "," ")+"  iyi bir dostluğa sahip olmak, "+GetAddress_Form(NPChar)+" "+PChar.lastname+" . Ne söylemek istiyorsan söyle.","Evet, "+GetAddress_Form(NPChar)+"?","Sohbet etmeyi sever misiniz, Kaptan? Ben de severim...")));

            // homo 25/06/06
			link.l1 = LinkRandPhrase("Buradaki meyhanede hangi dedikodular dolaşıyor?","Bu topraklarda neler oluyor?","Burada karada neler yeni?");
			link.l1.go = "rumours_citizen";
			link.l2 = LinkRandPhrase("Beni oraya yönlendirebilir misiniz?","Belirli bir yere giden yolu bulamıyorum...","Yolu gösterebilir misiniz...?");
			link.l2.go = "town";  //(перессылка в файл города)
			if(Rand(1)==0)
			{
				link.l3 = LinkRandPhrase("Belirli bir kişi hakkında insanların ne söylediğini öğrenmek istiyorum.","Bir kişi hakkında insanların ne söylediğini duymadın mı?","Buradaki yerliler hakkında bir şeyler öğrenmek istiyorum.");
				if(rand(1) == 0 || PChar.location == "LaVega_Town" || PChar.location == "PuertoPrincipe_town"
				|| PChar.location == "Pirates_town" || PChar.location == "Panama_town" || !CheckAttribute(NPChar, "City"))
				{
					link.l3.go = "info"; //(перессылка в файл города)
				}
				else
				{
					link.l3.go = "RumourAboutOwners"; // Warship. Сделал по-другому - у жителя каждого города будет свой диалог.
				}
			}
			else
			{
				link.l3 = "Lütfen bana koloniniz hakkında daha fazla bilgi verin.";
				link.l3.go = "colony";
			}
            link.l4 = RandPhraseSimple("Önemli işlerim var!","Sizinle bir işim var.");
			link.l4.go = "quests";  //(перессылка в файл города)
			link.l5 = PCharRepPhrase(RandPhraseSimple("Hayır, hayal görüyorsun. Şimdi gidiyorum.","Hayır, hiçbir şey - sadece meyhaneye gidiyordum."),RandPhraseSimple("Hayır, hiçbir şey yok. Sana bol şans!","Sadece etrafa bakıyorum. Hoşça kal."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "Kimin hakkında bilgi almak istersiniz?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "Vali hakkında.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "Yerel meyhanenin sahibi hakkında.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "Liman müdürü hakkında.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "Yerel dükkânın sahibi hakkında.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "Boşver, unut gitsin.";
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
		
		case "colony":
			dialog.text = LinkRandPhrase("Doğrusunu söylemek gerekirse, bu konuda pek bir şey bilmiyorum ama yine de sana birkaç şey anlatabilirim.","Kolonimizde seni ilgilendiren ne var?","Tabii. Ne bilmek istiyorsun?");
            switch(Rand(1))
			{
				case 0:
					link.l1 = "Burası nasıl bir kasaba?";
					link.l1.go = "colony_town";
				break;

				case 1:
					link.l1 = "Kasabayı savunan kale hakkında ne biliyorsun?";
					link.l1.go = "fort";
				break;
            }
			link.l2 = "Konu değiştirelim.";
			link.l2.go = "new question";
		break;
	  // to_do
		case "colony_town":
            dialog.text = "Şaka mı yapıyorsun? Yoksa dalga mı geçiyorsun? Ekranının sağ üst köşesine bak.";
			link.l1 = "Evet, benim hatam.";
		    link.l1.go = "exit";
		break;
		
		case "fort":
            dialog.text = "Bu konuda hiçbir şey bilmiyorum.";
			link.l1 = "Yazık.";
		    link.l1.go = "exit";
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Daha önce hiç duymadım... Aslında bu nedir? Bunca zamandır böyle bir şey duymamıştım"+NPCharSexPhrase(npchar,"","")+".";
			link.l1 = "Eh, bu bir gemi yapımcısının aleti, "+pchar.GenQuest.Device.Shipyarder.Describe+". Kasabada böyle bir şey satan oldu mu? Belki. Böyle bir şeyi taşıyan birini fark ettin mi?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Hmm... Evet, sanırım öyle bir şeyi olan birini gördüm. Birkaç saat önce onunla buralarda dolaşıyordu. Gerçekten ilginç bir alet.";
				link.l1 = "Nasıl biriydi ve nereye gitti? O alete gerçekten ihtiyacım var.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Hayır, öyle bir şey görmedim.";
				link.l1 = "Anladım. Pekâlâ, biraz soruşturmanın zamanı geldi!";
				link.l1.go = "exit";
			}
		break;
		
		//============================ Генератор мэра. Квест по розыску шпиона на улице ============================
		case "SitySpy":
			dialog.text = NPCStringReactionRepeat(NPCharSexPhrase(npchar,"Ve bunun benimle ne ilgisi var? Ben buralıyım!","Peki, neden bu konuyla beni rahatsız ediyorsun? Ben bu şehirde yaşıyorum ve böyle şeylerden hiç haberim yok!"),NPCharSexPhrase(npchar,"Benden yine ne istiyorsun? Sana zaten casus olmadığımı söylemedim mi?!","Benim zaten buralı olduğumu söylemedim mi?!"),NPCharSexPhrase(npchar,"Canım, yine sen misin! Beni rahat bırak – ben buralıyım!","Neden yine aptalca sorularınla beni rahatsız ediyorsun?"),NPCharSexPhrase(npchar,"Yine mi! Bu artık iyice saçmalık oldu!","Baksana, beni rahat bırak, olur mu? Lütfen!"),"block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Kim sözünü doğrulayabilir?","Ah, üzgünüm - zaten size sormuştum...","Üzgünüm, burada o kadar çok insan var ki...","Peki, peki...",npchar,Dialog.CurrentNode);
		    link.l1.go = DialogGoNodeRepeat("SitySpy_1", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			// ==> выбираем подтверждателя
			int num = FindNearCharacters(npchar, 20.0, -1.0, -1.0, 1.0, false, true);
			if(num > 0)
			{
				for(i = 0; i < num; i++)
				{
					iTemp = chrFindNearCharacters[i].index;
					if (CheckAttribute(&characters[iTemp], "CityType"))
					{
						if(characters[iTemp].CityType == "soldier" || characters[iTemp].CityType == "citizen")
						{
							break;
						}
					}
				}
				pchar.GenQuest.SeekSpy.Idx = chrFindNearCharacters[i].index; //индекс выбранного
				pchar.GenQuest.SeekSpy.Type = characters[sti(pchar.GenQuest.SeekSpy.Idx)].chr_ai.type; //тип кто помог
				pchar.GenQuest.SeekSpy.BaseIdx = npchar.index; //индекс
			}
		break;
		case "SitySpy_1":
			if (sti(pchar.GenQuest.SeekSpy.Idx) == -1 || sti(pchar.GenQuest.SeekSpy.Idx) == 1) //на всякий случай
			{
				dialog.text = "Herkes yapabilir! Dinle, neden beni sürekli rahatsız ediyorsun?! Bir derdin varsa, git valiye söyle ve işini orada hallet!",link.l1 ="Hmm... Böyle önemsiz bir meseleyle onu rahatsız etmemek en iyisi. Sana inanıyorum.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Bu kasabada kimse var mı! "+NPCharSexPhrase(npchar,GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)])+" mesela şimdi yapabilirim, "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)],"o","o")+" tam orada duruyor.","Ah, Tanrım, mesela, "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)],GetAddress_FormToNPC(NPChar)+" "+characters[sti(pchar.GenQuest.SeekSpy.Idx)].lastname,GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)]))+" Bunu yapabilirim.");				
			link.l1 = "Pekâlâ, o zaman görelim.";
		    link.l1.go = "SitySpy_2";
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			sld.dialog.currentnode = "SeekSpy_Checking";
			pchar.GenQuest.SeekSpy.time = 4.0; //время на подбежать
			if (sld.chr_ai.type == "merchant") pchar.GenQuest.SeekSpy.time = 0.0; //мерчант базарит сразу
            LAi_SetActorTypeNoGroup(sld);
		break;
		case "SitySpy_2":
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorTurnToCharacter(npchar, sld);
			LAi_ActorDialog(sld, pchar, "", stf(pchar.GenQuest.SeekSpy.time), 0); 
			DialogExit();
		break;
		//=================== ноды квеста мэра. поиск шпиона на улице, опрос свидетеля ==================
		case "SeekSpy_Checking":
			dialog.text = "Evet, "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]," gerçekten buranın yerlisi.","o gerçekten buralı.");
			link.l1 = RandPhraseSimple("Anladım"+GetSexPhrase("","")+". Yardımınız için teşekkür ederim.","Her şey yolunda. Yardımınız için teşekkür ederim.");
			link.l1.go = "SeekSpy_Checking_1";
		break;
		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;
		
		// Мини квест на поиск обручального кольца -->
		case "CitizenFindItem_1":
			dialog.text = "Bakın, dün şehir dışındaydım, dolaşıyordum ve evlilik yüzüğümü kaybettim... "+GetSexPhrase("Kaptan, lütfen onu arayabilir misiniz?","Hanımefendi, lütfen, bana bulmamda yardım edin!")+"";
			link.l1 = "Tabii ki "+GetSexPhrase("Yapabilirim! Senin gibi güzel bir kız için her şeyi yaparım!","Sana yardım edeceğim. Kilise bize ihtiyacı olanlara yardım etmemizi öğretiyor.")+"";
			link.l1.go = "CitizenFindItem_2";
			link.l2 = LinkRandPhrase("Hayır, yapamam. Üzgünüm. Yapmam gereken çok iş var.","Üzgünüm, yapamam. Şimdi hatırladım."+GetSexPhrase("","")+",   hala bitmemiş işlerim var...","Çok az vaktim var, bu yüzden sana hiçbir konuda yardımcı olamam...");
			link.l2.go = "CitizenFindItem_NoQuest";
			break;
			
		case "CitizenFindItem_2":
			dialog.text = ""+GetSexPhrase("Kaptan","Hanımefendi")+", bu harika! Lütfen bu yüzüğü benim için bul, kocam neredeyse geliyor "+sti(NPChar.LifeDay)+" günlerdir, ve alyansım olmadan beni görmesini istemem.";
			link.l1 = RandPhraseSimple("Nerede kaybettin, diyorsun?","Peki   tam   olarak   nerede   kaybettin?");
			link.l1.go = "CitizenFindItem_3";
		break;
			
		case "CitizenFindItem_3":
			dialog.text = "Şehir kapılarının hemen ilerisinde...";
			link.l1 = "Pekala, o zaman onu aramaya gidiyorum...";
			link.l1.go = "CitizenFindItem_4";
		break;
			
		case "CitizenFindItem_4":
			dialog.text = "Evet, lütfen yap. Ve acele et – unutma ki sadece "+sti(NPChar.LifeDay)+" gün.";
			link.l1 = "Hatırlıyorum.";
			link.l1.go = "exit";
			PChar.GenQuest.CitizenFindItem.StartQuest = true;
			PChar.GenQuest.CitizenFindItem.City = NPChar.City;
			PChar.GenQuest.CitizenFindItem.CitizenID = NPChar.ID;
				
			sCity = NPChar.City + "_ExitTown";
				
			//sTemp = "randitem" + (rand(1)+1); // Т.е. может получиться, что его вовсе найти не удастся. И это гуд.
			sTemp = "randitem1";
			Log_TestInfo("The ring shall be in the locator - " + sTemp);
			PChar.GenQuest.CitizenFindItem.ItemLocator = sTemp;
			ChangeItemDescribe("DOjeronRing", "itmdescr_WeddingRing");			
			items[FindItem("DOjeronRing")].Name = "itmname_WeddingRing";
			items[FindItem("DOjeronRing")].City = XI_ConvertString("Colony" + NPChar.City + "Gen");
			SetFunctionTimerCondition("CitizenFindItemMiniQuest_Timer", 0, 0, sti(NPChar.LifeDay), false);
			PChar.GenQuestRandItem.(sCity).(sTemp) = "DOjeronRing";
			SetGameModeCondition("CitizenFindItemMiniQuest_CheckItem");			
		break;
			
		case "CitizenFindItem_NoQuest":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			NPChar.CitizenFindItem.NoQuest = true; // Эта девушка квест больше не даст
		break;
			
		case "CitizenFindItem_Complete_1":
			dialog.text = ""+GetSexPhrase("Kaptan","genç hanım")+"! Çok mutluyum! Sana nasıl teşekkür edebilirim?";
			link.l1 = "Ah, teşekkür etmene gerek yok - tamamen karşılıksız yaptım.";
			link.l1.go = "CitizenFindItem_Complete_2";
			link.l2 = "Birkaç yüz peso kesinlikle fena olmazdı...";
			link.l2.go = "CitizenFindItem_Complete_3";
			RemoveItems(PChar, "DOjeronRing", 1);
			DeleteAttribute(PChar, "GenQuest.CitizenFindItem");
			NPChar.CitizenFindItem.NoQuest = true;
			PChar.Quest.CitizenFindItemMiniQuest_Timer.over = "yes";
			BackItemDescribe("DOjeronRing");
			items[FindItem("DOjeronRing")].Name = "itmname_DOjeronRing";
			DeleteAttribute(&items[FindItem("DOjeronRing")], "City");
		break;
			
		case "CitizenFindItem_Complete_2":
			dialog.text = "Ah, "+GetSexPhrase("Kaptan, gerçekten çok asil bir insansınız","hanımefendi, ne kadar asilsiniz")+"! Kilisede senin için mutlaka dua edeceğim! Elveda...";
			link.l1 = "Elveda, "+NPChar.name+".";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar,"nobility" ,1);
			AddCharacterExpToSkill(PChar, "Leadership", 10);
			AddCharacterExpToSkill(PChar, "Fortune", 10);
		break;
			
		case "CitizenFindItem_Complete_3":
			iTemp = (rand(3)+1)*50;
			dialog.text = "Ah, elbette. Buyurun -"+FindRussianMoneyString(iTemp)+". Hepsi bu kadar. Lütfen bu parayı alın... Ve elveda.";
			link.l1 = "Hoşça kal, "+GetFullName(NPChar)+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(PChar, iTemp);
		break;
		// <-- Мини квест на поиск обручального кольца
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("Hayır, bununla ilgili hiçbir şey bilmiyorum.","Bu konuda hiçbir şey bilmiyorum.","Hiçbir şey bilmiyorum.");
					link.l1 = LinkRandPhrase("Pekala, sağ ol.","Anladım, teşekkür ederim.","Peki, lütfen beni mazur gör.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Bu konuda hiçbir şey bilmiyorum, ama meyhanedeki müdavimlere sorabilirsin - sana mutlaka bir şeyler anlatırlar.","Sana hiçbir şey söyleyemem. Meyhanede etrafa sor.","Özel olarak bir şey bilmiyorum, ama meyhanede bazı dedikodular duyduğumu işittim.");
				link.l1 = "Hiç yoktan iyidir, en azından.";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dinle - bu kasabanın bir vatandaşı olarak, kınından çekilmiş bir kılıçla dolaşmaktan kaçınmanı rica ediyorum.","Dinle - bu kasabanın bir vatandaşı olarak, kınından çıkarılmış bir kılıçla dolaşmaktan kaçınmanı rica ediyorum.");
				link.l1 = LinkRandPhrase("Pekala.","Pekala.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sakin ol "+GetSexPhrase("dostum","kız")+" elinde silahla ortalıkta dolaşırken. Bu beni tedirgin ediyor...","Hoşlanmam bundan "+GetSexPhrase("adamlar","herhangi biri")+" silahlarla hazır halde dolaşıyorlar. Bu beni korkutuyor...");
				link.l1 = RandPhraseSimple("Anladım.","Onu kaldırırım.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}
