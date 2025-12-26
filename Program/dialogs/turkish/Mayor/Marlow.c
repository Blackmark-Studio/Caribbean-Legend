// Захария Марлоу, Чёрный Пастор, Пуэрто-Принсипе, Куба
int iMarlowTotalTemp;
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                    if (npchar.angry.name == "pirate_threat")
                    {
                        if (Dialog.CurrentNode == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                        else Dialog.CurrentNode = "AngryRepeat_1";
                    }
                break;
            }
        }
    } //<-- блок angry

	switch(Dialog.CurrentNode)
	{
		case "First time":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Sen deli misin? Kasap mı olmak istedin? Bütün korsanlar sana öfkeli, oğlum, buradan gitmen en iyisi...","Sen kafayı yemişsin galiba, oğlan. Biraz kolunu kanadını açmak mı istedin? Alınma ama burada işin yok. Kaybol!");
				link.l1 = RandPhraseSimple("Dinle, durumu düzeltmek istiyorum...","Bu sorunu çözmeme yardım et...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", denizdeki güvenliğim hakkında" + GetSexPhrase("", " konuşmak istiyorum") + ". Sahil Kardeşliği tayfası benim mütevazı varlığıma fazla ilgi gösteriyor. Onları biraz dizginleyebilir misin?";
			link.l0.go = "pirate_threat";
			
			dialog.text = NPCStringReactionRepeat("Bana söyleyecek bir şeyin var mı? Yok mu? O zaman defol buradan!",
						"Bence kendimi açıkça ifade ettim, beni rahatsız etmeyi bırak.",
						"Ne kadar açık konuşsam da, hâlâ sinirimi bozuyorsun!","Doğrusu, bu kabalıktan bıktım artık.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Zaten gidiyorum.",
						"Tabii, "+npchar.name+"...",
						"Üzgünüm, "+npchar.name+"...",
						"Ah...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			//--> Сага
			if(CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && !CheckAttribute(npchar, "quest.sharkbegin"))
			{
				link.l1 = "Shark Dodson'ı arıyorum. Onu en son görenin sen olduğunu söylüyorlar. Bu konuda bana yardımcı olabilir misin?";
				link.l1.go = "Shark";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax" && CheckCharacterItem(pchar, "witches_hammer"))
			{
				link.l1 = "Neden bu kadar kabasın? Yoksa istediğin kitabı benden almakla ilgilenmiyor musun?";
				link.l1.go = "book";
			}
			//<-- Сага
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Tutsak hakkında konuşmak istiyorum.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
				{
					link.l1 = "Merhaba, Papaz. Göreviniz hakkında konuşmak istiyorum.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
				{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
					link.l1 = "Tutsak hakkında konuşmak istiyorum.";
					link.l1.go = "CapComission6";
				}
			}
		break;
		
		case "shark":
			dialog.text = "Steven Dodson? I don't know how my story would help you, because Shark has been missing for the last few months and no one has seen him. It's not a surprise though; he killed Blaze Sharp and disgraced his own name with that foolish act. He made a few powerful corsairs his enemies.";
			link.l1 = "Shark'ın Sharp'ın ölümünde suçsuz olduğuna inanmak için her sebebim var. Bunu kanıtlayamam, ama belki Shark kendisi kanıtlayabilir. Bana onun hakkında bir şey söyleyecek misin?";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "Birkaç ay önce, Steven bana gelip çok tuhaf bir anlaşma teklif etti: bir ay boyunca teminat olarak 'Fortune' adlı fırkateynini bıraktı, karşılığında da ağzına kadar erzak dolu bir brig aldı. Sonra ya brigi geri getirip erzakların parasını ödeyecekti, ya da fırkateyn bende kalacaktı. Bir ay geçti - ne Shark'tan, yani brigimden, ne de paradan bir haber çıktı. Üstelik, Blaze'in öldürüldüğüne ve Shark'ın şüpheli olduğuna dair söylentiler duydum. Ne düşünebilirdim ki? Doğru! Steven'ın en kötüsünden kaçtığını düşündüm. Fırkateynini William Patterson adında bir İngiliz'e sattım, adam çok memnun kaldı ve gemi için yüklüce bir tomar dublon ödedi. Yani masraflarımı tamamen karşıladım ve ona karşı hiçbir kinim yok. Sharp'ın ölümüne de aldırmıyorum, kendime yetecek kadar derdim var.";
			link.l1 = "Sence o kaçmak isteseydi senin brig'ine mi ihtiyaç duyardı? Kendi gemisi vardı, herhangi bir brig'den yüz kat daha iyiydi. Görünen o ki Shark'ın bir planı vardı, ama bir şeyler ters gitti ve zamanında geri dönmedi.";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "Sana zaten söyledim, Dodson'ın dertleri umurumda değil. Anlaşmanın bana düşen kısmını yerine getirdim. Gemiye gelince, o lanet brigi neden istediğini ona sor istersen. Zorla aldırmadım ya.";
			link.l1 = "Pekâlâ, artık bu konuyu konuşmayalım. Elbette haklısın. Söylesene, Steven'ın senin brigantinle nereye gittiğinin farkında mıydın?";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "Kim bilir, kesin bir şey söylemek zor. Ama bazı tahminlerim var. Kuzeybatıya, Main'e doğru yelken açtı. Yani ya düşman yerlileriyle ünlü Tehlike Körfezi'ne ya da Papistleri ve Engizisyonuyla bilinen Yeni İspanya'ya gitmiş olabilir.\nBuralardan birine gideceğini sanmıyorum. Ama Küba'nın kuzeybatısında 'Terkedilmiş Gemiler Şehri' diye tuhaf bir yer olduğunu söylüyorlar. Birçok kişi bunun bir efsane olduğunu düşünür, ama ben öyle düşünmüyorum. Romantik olduğumdan değil, oraya kayıklarıyla giden gerçek insanlar olduğu için. En azından, eskiden vardı.";
			link.l1 = "Onlar da kim?";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "Küba'dan gelen bukanyerler. Barçalarını boğa karkaslarıyla doldurup kuzeybatıya açılmışlardı. Her zaman biraz sonra cepleri para ya da nadir ve değerli mallarla dolu olarak geri dönerlerdi.";
			link.l1 = "İlginç! Bu korsanları nerede bulabilirim?";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "Why are you asking me? Search Cuba's woods. Even if you find them, they won't tell you anything; why would they reveal the source of their good fortune? So don't waste your time, no one has seen them at it for a long while.\nAlso, I heard of some notes written by the Spanish sailor Alvarado, who visited the island himself. So I am curious, perhaps Steven did sail there after all.";
			link.l1 = "Haritalarda olmayan o bilinmeyen ada... Pek umut verici bir bilgi değil.";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "En başından beri hikayemin sana yardımcı olmayacağını söylemiştim. Peki, Dodson'a neden ihtiyacın var?";
			link.l1 = "Orman Şeytanı ve ben, onu Kıyı Kardeşliği'nin lideri olarak seçmek istiyoruz. Sana daha önce de söylediğim gibi, Blaze'in başkasının elinden öldüğüne dair ciddi sebeplerimiz var.";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "Heh! Jan onun yerine mi geçiyor? Biliyorsun kanunu - Dodson her barondan oy almak zorunda.";
			link.l1 = "Kanunları biliyorum. O zaman ikinci sorum: Seçimde Dodson'a oy verecek misin?";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "Well, he should return first. Actually, I don't care who leads the Brethren as long as he does his business well and doesn't bother me. As I said, I have problems of my own. Do you know how many witches and mages are on our island? No? I'll tell you: a legion! Besides, there are also a lot of Papists in Santiago and Havana.\nSpeaking of mages. There is a book called 'Hammer for the Witches'. I really want to get it, but only in English; I don't need Latin, German, or Spanish translations, I don't know these languages. Bring me the book and I will vote for Dodson.\nBe aware that Jackman promised me to find it too, so if he succeeds first... don't blame me then.";
			link.l1 = "Pekala, bunu düşüneceğim. Zamanını ayırdığın için sağ ol. Görüşürüz.";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "after_marlow";
			npchar.quest.sharkbegin = "true";
			AddQuestRecord("SharkHunt", "2");
		break;
		
		case "book":
			dialog.text = "Kitap mı? Sanırım 'Cadılar İçin Çekiç'ten bahsediyorsun?";
			link.l1 = "Elbette. Senin için bulmayı başardım. İstediğin gibi, İngilizce.";
			link.l1.go = "book_1";
		break;
		
		case "book_1":
			dialog.text = "Ha, böyle kaba bir karşılama için kusura bakma dostum. Bir daha olmaz... Şu harikayı bir göreyim!";
			link.l1 = "Tabii, bir bak.";
			link.l1.go = "book_2";
		break;
		
		case "book_2":
			RemoveItems(pchar, "witches_hammer", 1); // удалить трактат
			dialog.text = "Sonunda! Şimdi titreyin, Cehennem’in uşakları! Elim kılıç tutmaz olana dek sizi rahat bırakmayacağım...";
			link.l1 = "Senin adına sevindim, Papaz. Peki, oyunun ne olacak?";
			link.l1.go = "book_3";
		break;
		
		case "book_3":
			dialog.text = "Sana söylediğim gibi, 'Kimin baş olacağı umurumda değil.' Eminim Svenson değersiz birini seçmez. O yüzden oyumu al. Ne istiyorsan onunla yap. İşte payım.";
			link.l1 = "Teşekkürler, Zekeriya. Orada görüşürüz!";
			link.l1.go = "book_4";
		break;
		
		case "book_4":
			GiveItem2Character(pchar, "splinter_zm"); // дать осколок
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "27");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Sen deli misin? Kasap mı olmak istedin? Bütün korsanlar sana öfkeli, oğlum, buradan gitmen en iyisi...","Sen kafayı yemişsin galiba, oğlan. Biraz kolunu kanadını açmak mı istedin? Alınma ama burada işin yok. Kaybol!");
				link.l1 = RandPhraseSimple("Dinle, durumu düzeltmek istiyorum...","Bu sorunu çözmeme yardım et...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", denizdeki güvenliğim hakkında" + GetSexPhrase("", " konuşmak istiyorum") + ". Sahil Kardeşliği tayfası benim mütevazı varlığıma fazla ilgi gösteriyor. Onları biraz dizginleyebilir misin?";
			link.l0.go = "pirate_threat";
			
			dialog.text = NPCStringReactionRepeat("Bana söyleyecek bir şeyin var mı? Yok mu? O zaman defol buradan!",
						"Bence kendimi açıkça ifade ettim, beni rahatsız etmeyi bırak.",
						"Ne kadar açık konuşsam da, hâlâ sinirimi bozuyorsun!","Doğrusu, bu kabalıktan bıktım artık.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Zaten gidiyorum.",
						"Tabii, "+npchar.name+"...",
						"Üzgünüm, "+npchar.name+"...",
						"Ah...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Tutsak hakkında konuşmamız lazım.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}		
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Tutsak hakkında konuşmamız lazım.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}	
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")//  правка лесник,новая проверка ,исключающая тут же сдачу задания
			{
				link.l1 = "Merhaba, Papaz, göreviniz için buradayım.";
				link.l1.go = "CapComission3";
			}
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && CheckAttribute(pchar, "questTemp.LongHappy"))
			{ // лесник . похититель  ( после ДЛС ДиС ,когда барбазона уже нет)
				link.l1 = "Tutsaklarla ilgili işlerde parmağın olduğunu duydum...";
				link.l1.go = "Marginpassenger";
			}
		break;
		
	//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = "Ha-ha. Burada tek bir tutsağım olduğunu mu sanıyorsun? Adını söyle.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+" . O burada mı?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "O öyleydi. Onu geçen hafta buradayken Barbadoslu o plantasyon sahibine – Albay Bishop'a sattım.";
				link.l1 = "Lanet olsun...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ah, sonunda. Onu Barbados'taki o plantasyon sahibine satmayı düşünüyordum, bir iki haftaya burada olacak... Fidyen var mı?";
				link.l1 = "Bak, ufak bir sorun var... Aslında o kadar param yok. Ama çalışmaya hazırım.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Onu satmamış olman iyi. Al paralarını – 150.000 peso. Nerede bulabilirim onu?"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Çok yavaştın... Ve ona neden bu kadar önem veriyorsun? Ben sadece akrabalarıyla pazarlık ettim.";
			link.l1 = "Beni buraya gelmem için çağırdılar.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Pekâlâ, geç kaldın. Yapabileceğim bir şey yok.";
			link.l1 = "Dinle, onu kaça sattın, sır değilse?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, değil. Ama sana söylemeyeceğim... söylersem güleceksin. Ha-ha-ha-ha! Hoşça kal.";
			link.l1 = "Görüşürüz.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");//правка лесник.  в СЖ запись ниже не работает																																				  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));																															 
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(3) == 1)
			{
				dialog.text = "Pekala, "+pchar.name+", biliyorsun, işler öyle yürümüyor. Parayı getir, o zavallını alırsın, ha-ha.";
				link.l1 = "Pekala. Görüşürüz.";
				link.l1.go = "CapComission2_4";
			}
			else
			{
				dialog.text = "Pekala, pekala... Bir işim var... Nereden başlayacağımı bile bilmiyorum. Sınırı aşan bir korsanı batırmam gerekiyor.";
				link.l1 = "Ormanda onu öldürmek daha kolay olmaz mı?";
				link.l1.go = "CapComission2_2_1";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "İşler böyle yürümez, biliyorsun... Onun ölmesine ihtiyacım yok, sadece bazılarına ganimetten payımı almamayı öğretmem gerek. Ama ölürse de pişman olmam.";
			link.l1 = "Neden kendi adamlarını onun peşinden göndermiyorsun?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
			dialog.text = "Hm... Pekala, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" bazı korsanları, ganimet paylarının bizim sakladığımız yerde,   çok uzakta olmayan bir yerde tutulduğuna ikna etti "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". İki gemileri '"+pchar.GenQuest.CaptainComission.ShipName1+"' ve '"+pchar.GenQuest.CaptainComission.ShipName2+"' demir aldı kısa süre önce ve yelken açtı "+sLoc+". Şimdi neden bu işi adamlarıma emanet edemeyeceğimi anlıyor musun?";
			link.l1 = "Evet, biliyorum. Ne kadar vaktim var?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12 ila 15 gün, daha fazla değil. Onların gizli yere ulaşmaması benim için önemli, yoksa değerli yükle onları batırmanın bir anlamı kalmaz. O durumda, buraya getirmeleri daha iyi olurdu...";
			link.l1 = "Pekala, varım. Onları yakalamaya çalışacağım.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");//правка																			   
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			//pchar.GenQuest.CaptainComission.PirateShips = "sdatkwest";	// лесник - заменил проверку для сдачи сразу.
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Merak etme. Adamlarım onu gemine götürecek. Hem, sana ne onun derdinden?";
			link.l1 = "Hayır. Akrabaları onu getirmemi istedi.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ah, bu da iyi. Adamına bu kadar düşük bir fiyat teklif ettiğim için neredeyse üzülüyordum. Ha-ha-ha-ha. Hoşça kal.";
			link.l1 = "Görüşürüz.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// belamour gen	
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник																																																			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");		// лесник																											 
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "So, , "+GetFullName(pchar)+", adamlarımı batırdın mı? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Hayır. Onları yakalayamadım. Ve dönüş yolunda da karşılaşmadım.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "Yaptım. Onları köpekbalıklarına yem ettim.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Lanet olsun! Onlarla karşılaşmış olsam da olmasam da, artık fark etmez! Peki, sıradaki önerin ne olacak?";
			link.l1 = "Belki bana daha kolay bir işin vardır?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Dinle, "+NPChar.name+", esiri daha ucuza ver...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Hayır.";
			link.l1 = "Öyleyse hoşça kal...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Fiyatı mı düşüreyim?! Senin beceriksizliğin yüzünden malımı kaybettim! Şimdi istersem fiyatı artırırım! Onu istiyorsan 200.000 peso verirsin, yoksa defolup gidersin.";
			link.l1 = "Çok pahalı... Hoşça kal...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Lanet olsun, al paralarını.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Marlow");		// лесник																								   
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Marlow"); // правка	// лесник																											 
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Bu zavallıyı alabilirsin...";
			link.l1 = "Elveda.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Marlow"); // правки имени в сж лесник																										  
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в сж не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho! Aferin! Al şu zayıfı ve sana bol şans.";
			link.l1 = "Teşekkürler. Hoşça kal.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
			/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
		     ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
			dialog.text = "Fidye parasını getirdin mi "+GetSexPhrase("","ла")+"? Onu plantasyon sahiplerine satacağımı söylerken şaka yapmıyordum.";			
			link.l1 = "Dinle, "+NPChar.name+", bak şimdi... O kadar param yok. Ama istekliyim"+GetSexPhrase("","а")+" çalışmak.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Onu satmamış olman iyi. Al paralarını - 150.000 peso. Nerede bulabilirim onu?"link.l2.go ="CapComission2_3";
			}			
		break;*/
		  case "CapComission6":                        // лесник . пусть шарль бабло ищет,или забить на пленника.
			dialog.text = "Parayı getirdin mi? O adamı plantasyona satmak konusunda şaka yapmıyordum.";			
			link.l1 = "Param yok, "+NPChar.name+", ama üzerinde çalışıyorum.";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Onu satmamış olman iyi. Al paralarını - 150.000 peso. Nerede bulabilirim onu?"link.l2.go ="CapComission2_3";
			}			
		break;

																																				 																																													  																																															
//--------------------------------------------Похититель------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "Ve benim ne yaptığımla neden ilgileniyorsun? Biliyor musun, en iyisi sen git...";
			link.l1 = "Tshh, sakin ol. Seninle işim var. Bu, tutsağınla ilgili.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Ah, peki. Kimi fidyeyle serbest bırakmamı istiyorsun?";
			link.l1 = "Bekle. Kimseyi satın almaya gelmedim, sana bir esiri satın alma fırsatı sunmaya geldim. Hem de onun için fidye alma şansın olacak.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Hm. Peki neden benim yardımımı istiyorsun? Parayı doğrudan kendin almak istemiyor musun?";
			link.l1 = "Bu benim için oldukça riskli. Yetkililerle başım belaya girebilir.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ha-h... peki o zaman. Hadi bakalım. Kim bu tutsağın?";
			link.l1 = "Bu "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Anladım... yalan söylemiyorsan bu adil bir alışveriş olurdu. Sanırım bu adam için sana ödeme yapabilirim "+iTemp+" peso ya da ilginç bir bilgi sunabilirsin. Seçim senin.";
			link.l1 = "En iyisi peso alayım. Bu işten artık bıktım...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ha! Devam et, anlat bakalım. Eminim bana ilginç bir şeyin vardır.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "Para işte. Al onları. Artık senin sorunun değil. Satış konusu olanı buraya getir.";
			link.l1 = "Şimdiye kadar kasaba kapılarının yakınında olmalı. Teşekkür ederim! Gerçekten bana çok yardımcı oldun.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Rica ederim, bana daha fazlasını getir... Görüşürüz!";
			link.l1 = "İyi şanslar...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT, FLAG_GOODS_VALUABLE_WOOD);
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "Akıllı bir adamla iş yapmak güzeldir. Şimdi dinle: birkaç gün içinde "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat")+" Ana Karayolundan yüklü değerli mallarla dolu bir İspanyol keşif birliği gelecek. Yükü alacak bir gemiyi bekliyor olacaklar. Eğer bir hafta içinde oraya varırsan, yükü kendin alabilirsin.\nSenin yerinde olsam, çoktan gemime gidiyor olurdum. Ve mahkumu buraya getir.";
					link.l1 = "Sağ ol! Mallar, yaşadığım sıkıntılar için iyi bir karşılık olacak. Yolcum da muhtemelen şehir kapılarında bekliyordur. Onu sana getirecekler.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "Akıllı bir adamla iş yapmak güzeldir. Şimdi dinle: yaklaşık bir hafta sonra, bir İspanyol brigantini '"+pchar.GenQuest.Marginpassenger.ShipName1+"' değerli mallarla yüklü olarak   yola çıkacak "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" to "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". Acele edersen, onu kolayca yakalarsın.\nHâlâ burada mısın? Senin yerinde olsam çoktan gemime gidiyor olurdum. Ve mahkumu buraya getir.";
					link.l1 = "Sağ ol! Mallar, yaşadığım sıkıntılar için iyi bir karşılık olacak. Yolcum da muhtemelen şehrin kapılarında bekliyordur. Onu sana getirecekler.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));//лесник - окончание в СЖ // belamour gen: Abl - это к Залив"ом", нужен дательный
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen : как-то странно, наводку даёт Захар, а в сж Добряк дефолтом
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen 
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
		
		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Soygun! Bu kabul edilemez! Hazırlan, "+GetSexPhrase("oğlan","kız")+"...","Hey, ne halt ediyorsun orada?! Beni soyabileceğini mi sandın? İşin bitti...","Ne oluyor lan? Ellerini çek! Demek hırsızmışsın! Yolun sonu, alçak...");
			link.l1 = LinkRandPhrase("Kahretsin!","Caramba!!","Lanet olsun!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Defol ","Defol")+" buradan!","Defol evimden!");
			link.l1 = "Oops...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Ucuz laflarınla beni oyalama. Bir dahaki sefere sonucu hiç beğenmeyeceksin...";
        			link.l1 = "Anladım.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("Bitti, konuşmak yok.","Seninle artık konuşmak istemiyorum, o yüzden beni rahatsız etmesen iyi olur.");
			link.l1 = RandPhraseSimple("Sen nasıl istersen...","Hm, peki o zaman...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Umarım biraz daha saygılı olur ve kaba davranmayı bırakırsın?";
        			link.l1 = "Emin olabilirsin, Papaz, yapacağım.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Puertoprincipe_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		case "pirate_town":
            dialog.text = "Bu sorunu çözmek mi? Ne yaptığının farkında mısın sen? Neyse, bana bir milyon peso getir, adamlara yaptıklarını unuttururum. Bu işine gelmiyorsa, defol git cehenneme.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Pekâlâ, ödemeye hazırım.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Anlaşıldı. Gidiyorum.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Güzel! Kendini tekrar temiz say. Ama umarım bir daha böyle iğrenç şeyler yapmazsın.";
			link.l1 = "Yapmam. Benim için fazla pahalı. Hoşça kal...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		case "pirate_threat":
			if (GetNpcQuestPastDayWOInit(NPChar, "ThreatTalk") == 0)
			{
				dialog.text = NPCStringReactionRepeat("Bugün bu konuyu zaten konuştuk.",
				                                      "Yeterince açık konuşmadım mı?",
				                                      "Israrcılığın can sıkmaya başladı.",
				                                      "Artık sabrım taştı. Defol buradan!",
				                                      "repeat", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Başka zaman konuşuruz...",
				                                   "Elbette, "+npchar.name+"...",
				                                   "Üzgünüm, "+npchar.name+"...",
				                                   "Ah...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
				break;
			}
			if (iGPThreat != 0)
			{
				iBarbazonTotalTemp = 10 * iGPThreatRate;
				dialog.text = "Ha! Kardeşlik tayfası seni fena hırpalıyor ha, " + GetSexPhrase("dostum", "dostum") + "? Onları bir süreliğine dizginleyebilirim. Ama bunun bir bedeli var. " + FindRussianDublonString(iBarbazonTotalTemp) + " ver, işi halledelim.";
				if (PCharDublonsTotal() > iBarbazonTotalTemp)
				{
					if (iGPThreat < 5) link.l0 = "Elbette, işte paran.";
					else link.l0 = "Başka çarem yok gibi görünüyor. Al paranı.";
					link.l0.go = "pirate_threat_pay";
				}
				link.l1 = "Sonra tekrar gelirim...";
				link.l1.go = "exit";
			}
			else
			{
				SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
				if (NextDiag.TempNode != "I_know_you_good")
					dialog.text = "Aklını mı kaçırdın" + GetSexPhrase("", "") + "? Bizim tayfa seni vebalı gibi kaçıyor. Hadi git, kafamı ütüleme.";
				else
					dialog.text = "Neden bahsediyorsun, " + GetSexPhrase("dostum", "dostum") + "? Sen baş belasının tekisin — köpekler bile bunu hissediyor. Kimse seninle uğraşmak istemiyor.";
				link.l1 = "Anladım...";
				link.l1.go = "exit";
			}
		break;

		case "pirate_threat_pay":
			iGPThreatRate = 0;
			iGPThreat = 0;
			SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
			RemoveDublonsFromPCharTotal(iBarbazonTotalTemp);
			DialogExit();
			PiratesDecreaseNotif("");
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
