// Маркус Тиракс, барон Ла Веги
int iTerraxTotalTemp;
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;
	bool bOk;

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
    }
// ------------------------------------------блок angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && !CheckAttribute(npchar, "quest.mtraxx_complete")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "Ah, Prens, sonunda geldin. Hiç değilse biriniz zahmet edip ortaya çıktı! İş bekliyor, ama hepiniz ortadan kayboldunuz! Herkes nerede, lanet olsun?";
					link.l1 = "Hiçbir fikrim yok... Marcus, ben gidiyorum. Yeter artık. Ölüler rüyalarıma geliyor, Lucifer bizzat ensemde nefes alıyor. Son zamanlarda çok fazla kan döküldü.";
					link.l1.go = "mtraxx_113";
					break;
				}
			}
			// Jason НСО
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Benim için bir 'iş' var mı?";
				link.l1 = "Selam, Marcus. Evet, bir 'işim' var. Kârlı ve pratik.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "Parayı getirdin mi?";
				link.l1 = "Yaptım.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "İşte müşterimiz! İş tamam, Baron'unuz iyi korunan bir zindanda oturuyor. Belki bir bakmak istersin, ha-ha?!";
				link.l1 = "Bunu yapmak için bolca vaktim olacak, ha-ha. Ona iyi davranılıyor mu?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, ne oluyor lan?!";
				link.l1 = "Marcus, her şey ters gitti. Ne gelebilirdim ne de sana haber verebildim...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "İşte bizim kuklacımız!";
				link.l1 = "Ha-ha! Gösteri mükemmeldi!";
				link.l1.go = "patria_x29";
				break;
			}
			
			link.l0 = ""+npchar.name+", denizdeki güvenliğim hakkında" + GetSexPhrase("", " konuşmak istiyorum") + ". Sahil Kardeşliği tayfası benim mütevazı varlığıma fazla ilgi gösteriyor. Onları biraz dizginleyebilir misin?";
			link.l0.go = "pirate_threat";
			
            dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Bana söyleyecek bir şeyin var mı? Yok mu? O zaman beni rahat bırak!","Ha, "+pchar.name+"! Benimle işin mi var? Yok mu? O zaman beni rahatsız etme.")+"","Sana açıkça söyledim sanıyordum... Git dedim, ama hâlâ gelip sinirimi bozuyorsun!","Doğrusu, bu kabalıktan bıktım artık.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ben zaten gidiyorum.","Tabii, Marcus...","Üzgünüm, Marcus...","Oops...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Sen deli misin? Kasap mı olmak istedin? Bütün korsanlar sana öfkeli, oğlum, buradan gitmen en iyisi...","Sen kafayı yemişsin galiba, oğlan. Biraz kolunu kanadını açmak mı istedin? Alınma ama burada işin yok. Kaybol!");
				link.l1 = RandPhraseSimple("Dinle, durumu düzeltmek istiyorum...","Bu sorunu çözmeme yardım et...");
				link.l1.go = "pirate_town";
				break;
			}
			// Сага - завершаем искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				// Addon 2016-1 Jason пиратская линейка патч 17/1
				if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "Marcus, bana kızgın olmayı hiç bırakacak mısın? Cartagena'yı birlikte bastığımız arkadaşın Vincent'ı kurtardım, seni de ölümden aldım! Yoksa Bernard sana hâlâ hiçbir şey söylemedi mi?";
					link.l1.go = "Temptation_13";
				}
				else
				{
					link.l1 = "Neden bu kadar kabasın, Marcus? Bernard benim hakkımda hiçbir şey söylemedi mi?";
					link.l1.go = "Temptation";
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "to_lavega")
			{
				link.l2 = "Bir iş arıyorum... Akıllıca, kârlı bir şeyin var mı?";
				link.l2.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Satacak biraz ipeğim var.";
				link.l2.go = "Mtraxx_silktrade";
			}
			if (pchar.questTemp.Mtraxx == "silk_14")
			{
				link.l1 = "Sana bir alıcı buldum. Port Royal'dan bir gemi yapımcısı. Üretimi için gemi ipeğine ihtiyacı var ve her ay yüz topu, top başına 5 doblona alabilecek. Adamları malları 10'u ile 15'i arasında, gece, Negril Burnu'ndan teslim alacak. Parola: 'Lyonlu bir tüccar.' Kel Geffrey ilk partiyi zaten Jamaika'ya teslim etti.";
				link.l1.go = "mtraxx_13";
			}
			if (pchar.questTemp.Mtraxx == "silk_15")
			{
				link.l1 = "I've found you a buyer. He's a shipbuilder from Port Royal. He needs ship silk for his production and will be able to buy batches of one hundred rolls every month for 5 doubloons a roll. His men will receive the goods from the 10th to the 15th, at night, at Negril Cape. The password is 'A merchant of Lyons'. It took me more than two months to find such a buyer; Geffrey must have already sold the silk to smugglers. I am sorry, Marcus.";
				link.l1.go = "mtraxx_15";
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Sen deli misin? Kasap mı olmak istedin? Bütün korsanlar sana öfkeli, oğlum, buradan gitmen en iyisi...","Sen tam bir kudurmuş köpeğe dönmüşsün, oğlan. Biraz elini kolunu açmak mı istedin? Alınma, ama burada sana yer yok. Kaybol!");
				link.l1 = RandPhraseSimple("Dinle, durumu düzeltmek istiyorum...","Bu sorunu çözmeme yardım et, lütfen...");
				link.l1.go = "pirate_town";
				break;
			}
			// Jason НСО
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, ne oluyor lan?!";
				link.l1 = "Marcus, her şey berbat oldu. Ne gelebilirim ne de sana haber verebilirim...";
				link.l1.go = "patria_33";
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Seni görmek güzel, dostum!";
				link.l1 = "Seni görmek de güzel. Muhteşem gösteri için teşekkürler!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Seni görmek güzel, çocuk! Sana nasıl yardımcı olabilirim?";
				link.l1 = "Sana bir teklifim var. Korsanlara yaraşır, bilirsin!";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "İşte müşterimiz! İş tamam, Baron'unuz iyi korunan bir zindanda oturuyor. Belki bir göz atmak istersin, ha?!";
				link.l1 = "Bunu yapmak için bolca vaktim olacak, ha-ha. Ona iyi bakıyorlar mı?";
				link.l1.go = "patria_10";
				break;
			}
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Benim için bir işin var mı?";
				link.l1 = "Selam, Marcus. Evet, bir iş var. Kârlı ve korsanca.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "Parayı getirdin mi?";
				link.l1 = "Yaptım.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "İşte müşterimiz! İş tamam, Baron'unuz iyi korunan bir zindanda oturuyor. Belki görmek istersin, ha-ha?!";
				link.l1 = "Bunu yapmak için bolca vaktim olacak, ha-ha. Ona iyi davranılıyor mu?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, ne oluyor lan?!";
				link.l1 = "Marcus, her şey ters gitti. Ne gelebilirdim ne de sana haber verebildim...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "İşte bizim kuklacımız!";
				link.l1 = "Ha-ha! Gösteri mükemmeldi!";
				link.l1.go = "patria_x29";
				break;
			}
			// Тени прошлого
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Seni görmek güzel, oğlan! Sana nasıl yardımcı olabilirim?";
				link.l1 = "Marcus, seninle konuşmam lazım. Hoşuna gitmeyecek belki ama yine de yardımına ihtiyacım var.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Ha, işte buradasın, "+pchar.name+". Gelişini bekliyordum. Orman Şeytanı, Tortuga ile ilgili derdin konusunda beni şaşkına çevirdi...";
				link.l1 = "Bana bir çözüm bulduğunu söyledi. Doğru mu?";
				link.l1.go = "terrapin";
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Satacak ipeğim var.";
				link.l2.go = "Mtraxx_silktrade";
			}
			
			link.l0 = ""+npchar.name+", denizdeki güvenliğim hakkında" + GetSexPhrase("", " konuşmak istiyorum") + ". Sahil Kardeşliği tayfası benim mütevazı varlığıma fazla ilgi gösteriyor. Onları biraz dizginleyebilir misin?";
			link.l0.go = "pirate_threat";
			
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", seni gördüğüme sevindim! Bu sefer ne istiyorsun?","Ne istiyorsun?","Yine mi? Yapacak bir işin yoksa insanları rahatsız etme!","Sen bir "+GetSexPhrase("iyi korsan","aferin kızım")+", şimdilik yaşayabilirsin. Ama seninle daha fazla konuşmak istemiyorum.","repeat",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sadece seni görmek istedim.","Hiçbir şey.","Pekala, Marcus, özür dilerim.","Lanet olsun, gerçekten üzgünüm Marcus!",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Soygun! Bu kabul edilemez! Ölümüne hazır ol, fare...","Hey, orada ne yapıyorsun?! Beni soyabileceğini mi sandın? İşin bitti...","Ne oluyor lan?! Meğer hırsızmışsın! Yolun sonu, alçak...");
			link.l1 = LinkRandPhrase("Kahretsin!","Caramba!","Ah, kahretsin!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Defol","Defol")+" buradan!","Defol evimden!");
			link.l1 = "Oops...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Değersiz laflarınla beni işimden alıkoyma. Bir dahaki sefere bu kadar iyi kurtulamazsın...";
        			link.l1 = "Anladım, Marcus.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("Senden bıktım.","Seninle konuşmak istemiyorum, bu yüzden benden uzak dursan iyi edersin.");
			link.l1 = RandPhraseSimple("Pekâlâ...","Hm, peki o zaman...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Umarım artık beni boş laflarınla rahatsız etmezsin, yoksa seni öldürmek zorunda kalırım. Şunu da söyleyeyim, bunu yapmaktan memnun olmayacağım.";
        			link.l1 = "Bundan emin olabilirsin, Marcus, asla...";
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
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		
//--> -----------------------------Сага - Искушение Барбазона завершающие этапы---------------------------
		case "Temptation":
			dialog.text = "Ha! Türklerin kahramanı mı oldun? Kusura bakma, biraz kaba karşıladım seni, çocuk. Bernard bana senin o meşhur işlerinden ve bana kurulan bir tuzaktan bahsetti. Detayları senden duymak isterim...";
			link.l1 = "Gerçekten de bir tuzaktı. Avladıkları kişi Bernard değil, sendin. O sadece yemdi.";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "";
			link.l1 = "Plan basitti. Arkadaşını kurtarıp 'Separator'a ilk ayak basan sen olacaktın. Tam o anda da gemiye ateş açıp paramparça edeceklerdi. Brigantin cehennem gibi barutla doluydu.";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "Lanet olsun! O deliliği kim düşündü?! Ve Bernard'ı nereye sakladıklarını nasıl bulmam gerekiyordu?!";
			link.l1 = "Bu planın yazarları Jackman ve kardeşi David'di. Bir ulak sana 'Separator'ın Turks Adası'nın güney koyunda yardımını beklediğini bildirecekti. Beni o ulak olarak seçtiler, işte hataları da buydu.";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "Anlamıyorum! Bütün bunların içinde senin rolün ne?";
			link.l1 = "Uzun zamandır o alçak Jackman’ı izliyorum. Jan Svenson’la çalışıyorum, bilmezsen. Orman Şeytanı’yla birlikte onu ortaya çıkarmaya karar verdik. Jan, Blaze’in ölümünden onun sorumlu olduğuna emin, Steven ise boş yere suçlandı.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end") link.l1.go = "Temptation_14";
			else link.l1.go = "Temptation_4"; //патч 17/1
		break;
		
		case "Temptation_4":
			dialog.text = "Heh! Ama Blaze'in cesedinde baş harfleri kazınmış bir köpekbalığı dişi bulundu – S.D. – bunun Steven'a ait olduğunu herkes bilir...";
			link.l1 = "Hepsi bir tuzaktı. Jackman büyük oynadı. Nathaniel Hawk'ı ortadan kaldırıp Maroon Town'da onun yerine geçti, sonra da Sharp'ı öldürüp suçu Shark'ın üstüne attı. Yaptıklarına dair elimde yeterince kanıt var. Hepsini Jacob'ın sandığında buldum. Sharp'ın haritasının ikinci parçası ve Hawk'ın parçası da oradaydı.";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			dialog.text = "Kahretsin! Demek Steven masummuş? Peki Jacob neden bütün bunları yaptı?";
			link.l1 = "Kardeşliğin başına geçmeyi bekliyordu ve Isla Tesoro ile ilgili bir şey olacağını öngörüyordu. Senin ve Svenson'ın desteğini kazanamayınca, ikinizden de kurtulmaya karar verdi. İlk sırada sendin. En tehlikeli olan Jan ise ikinciydi.";
			link.l1.go = "Temptation_6";
		break;
		
		case "Temptation_6":
			dialog.text = "O şerefsiz nerede?! Onu paramparça edeceğim!";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "Jackman ve kardeşi öldü, avcılarının geri kalanı da öyle. Onlarla bizzat ilgilendim. Bu herif artık kimseye zarar veremeyecek. Marcus, Steven Dodson için oyunu verir misin? Bu benim kişisel ricam.";
				link.l1.go = "Temptation_7";
			}
			else
			{
				link.l1 = "Jackman ve kardeşiyle birlikte avcıların geri kalanı da öldü. Onlarla bizzat ilgilendim. Bu herif artık kimseye zarar veremeyecek. Ne yazık ki Steven öldürüldü...";
				link.l1.go = "Temptation_10";
			}
		break;
		
		case "Temptation_7":
			dialog.text = "Tabii, oyumu vereceğim! Blaze'den sonra aramızda en layık olanın Shark olduğunu hep düşünmüşümdür. Onun suçlu olduğuna neredeyse inanmıştım. Hepimiz inandık! Al, işte parçam.";
			link.l1 = "Pekala! Artık rahatça nefes alabilirsin.";
			link.l1.go = "Temptation_8";
		break;
		
		case "Temptation_8":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "Doğru... Anladığım kadarıyla, Köpekbalığı'nın çıkarlarını temsil ediyorsun?";
			link.l1 = "Evet. Jan Svenson ve ben. Tamam Marcus, görüşürüz!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_10":
			dialog.text = "Öldü mü?! Nasıl? Jackman'ın işi mi bu da?";
			link.l1 = "Hayır. Onu kendi lostromosu öldürdü, adı Chad Kapper’dı. Zaten hak ettiğini buldu... Marcus, Svenson senin Kardeşliğin yeni lideri olmaya en layık kişi olduğunu düşünüyor. Diğer baronlar da bu kararı destekleyecek. Bunu kabul ediyor musun?";
			link.l1.go = "Temptation_11";
		break;
		
		case "Temptation_11":
			dialog.text = "Heh! Bunu bana iki kere söylemene gerek yok. Kardeşliğin Başı olmak büyük bir onur! Karşı çıkacağımı aklından bile geçirme.";
			link.l1 = "Harika. Bunu kabul ettiğine sevindim.";
			link.l1.go = "Temptation_12";
		break;
		
		case "Temptation_12":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "Al, al şu parçamı. Bunu Svenson'a götür. Sanırım burada patron o, değil mi?";
			link.l1 = "Evet, öyle. Peki Marcus, görüşürüz!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_9":
			dialog.text = "Evet, ayrıca dostum Bernard'ı kurtardığın için sana teşekkür etmek istiyorum. Al, içinde altın dolu bu keseyi kabul et.";
			link.l1 = "Teşekkürler! Hoşça kal!";
			link.l1.go = "Temptation_exit";
		break;
		
		case "Temptation_exit":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 300);
			Log_Info("You have received 300 doubloons");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "25");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "Temptation_13":
			dialog.text = "Evet, Charlie Prince'in Turks'e görkemli gelişinden bahsetti bana... Kıçımı kurtardığını mı söylüyorsun? Nasıl? Bernard bir tuzaktan söz etti...";
			link.l1 = "Yes, it was a trap. You were the target; Bernard was just the bait...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_14":
			dialog.text = "Ha-ha-ha, Orman Şeytanı için çalışıyorsun ha, Prens? Peki, onun yanında benden daha iyi para mı kazanıyorsun? Söyle bakalım, dürüst ol!";
			link.l1 = "Marcus, geçmişi artık tamamen bir kenara bırakalım. Şimdi ortak bir amacımız var ve bu, kervanları yağmalamaktan çok daha önemli. Lanet olsun! Şu an en önemli şey bu! Kardeşliğin geleceği tehlikede!";
			link.l1.go = "Temptation_15";
		break;
		
		case "Temptation_15":
			dialog.text = "Pekâlâ Prens, anladım! Sonuçta özgür bir korsansın, Orman Şeytanı için çalışmak senin seçimin oldu ve iyi bir karar vermişsin... Steven yani... Ona iftira atıldığını söyledin, değil mi?";
			link.l1 = "Kesinlikle doğru.";
			link.l1.go = "Temptation_4";
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "Tabii, sana yardım etmek için elimden geleni yapacağım! Devam et.";
			link.l1 = "Bak bakalım, Marcus... Bu bir köpekbalığı dişi. Bunun hakkında ne söyleyebilirsin?";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "Ha! Bu, Steven Dodson'ın bir kızı etkilemek için öldürdüğü beyaz köpekbalığının dişi. O günden beri herkes ona Köpekbalığı diyor. Bunu basit bir kılıçla suyun altında başarabilen çok az kişi vardır. Ama o genç ve deliydi, Beatrice Sharp ise Karayipler'in en güzel kızıydı... Peki, sen bunu nasıl ele geçirdin?";
			link.l1 = "Bu bana Saint John's'un eski celladı tarafından verildi. Bu dişle bir adam öldürüldü. Adı... Joshua Leadbeater'dı.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "That is an old story. Steven killed that man. He was shocked by Beatrice's death and thought that Leadbeater was the only living person responsible for it. But later he found some papers on Joshua's corpse, studied them, and repented his deed.\nThe Mask wasn't to blame for Beatrice's death; he only needed Butcher. Butcher's jealous ex-girlfriend Jessica had set all this up.";
			link.l1 = "O kağıtları okudun mu?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "Neden yapayım ki? Tabii ki hayır. Onlarla ilgilenmedim bile. Ama vaktin varsa Maskenin neden Kasabı kovaladığını sana anlatabilirim. Sarhoş Steven bu hikayeyi bana defalarca anlattı.";
			link.l1 = "Vaktim var. Güven bana, ilgimin bir sebebi var. Hatta bu hikayeyi yazabilirim bile.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "Biliyorum, zamanını asla boşa harcamazsın. O halde dinle. Joshua Leadbeater bir İngiliz donanma kaptanıydı ve efsanevi 'Neptune' onun komutası altındaydı...";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("One hour later", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... ama Leadbeater hayatta kaldı ve yoldan geçen bir gemi tarafından kurtarıldı. Yarası onu sakat bıraktı ve o zamandan beri maske takıyor. Bir süre sonra, insanlar ona Maske demeye başladı. Hayatını mahveden adamdan intikam almak onun tek amacı oldu.";
			link.l1 = "Anladım... Hepsini yazdım. Sanırım tekrar okuyup elimdeki tüm bilgilerle karşılaştırmam gerekecek. Gerçekten üzücü bir hikaye. Jessica'yı hiç gördün mü?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "Sure! She accompanied Butcher on all his voyages until he left her for Beatrice. Jess couldn't forgive him for that. People called her the Butcher's talisman, because he always had luck while she was there with him.\nBelieve it or not, but as soon as he got rid of her in Barbados, his business went bad, the booty became poor, and the 'Neptune' became a frequent guest at the shipyard of Isla Tesoro. But that can be explained by the fact that Butcher had been spending most of his time with Beatrice in the cabin rather than on the quarterdeck.\nBeatrice was not like Jessica; she wasn't addicted to adventure and war, although Nicholas taught her fencing and sailing. Yes, she was fond of sea romances, but she didn't have enough steel in her. Butcher's 'Neptune' wasn't the right place for her. In the end, it killed her.";
			link.l1 = " Peki ya Jessica? ";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "Oh, she was something, alright... Every sailor on the 'Neptune' obeyed her orders, and not just because she was the captain's girlfriend. Jess was a master of fencing and sailing; Butcher's efforts weren't wasted. She was tough and reckless, and she was so beautiful. A lot of men wanted to share a bed with her, but she wanted only Butcher. Bothering her was really risky; many felt the consequences on their own skin, quite literally, and for the most persistent, her fencing lessons turned out to be the last of their lives. Jess owned a very special sword, the only one of its kind in the Caribbean. I have no clue where she got it. A flame-bladed sword. The blade couldn't be grabbed by hand, and even the slightest touch left a terrible wound. Jess was an adventurer not by birth, but by vocation. By the way, if you want to know more about her, you can talk to an acquaintance of yours. He can tell you much more about her than I can.";
			link.l1 = "Gerçekten mi? Peki bu adam kim?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "Jan Svenson. Orman Şeytanı bunu asla kabul etmezdi ama Jessica için planları vardı. O zamanlar Batı Main'i çoktan ele geçirmişti ve şöhreti kıskanılacak düzeydeydi, bu yüzden kaplan gibi bir kadın ona yakışıyordu.\nKasap, Jess'ten kurtulunca Jan, Barbados'a şüpheli bir şekilde sık sık uğramaya başladı; garnizon korkudan tir tir titriyordu. Bildiğin gibi, Jessica Bridgetown'lu bir plantasyon sahibinin kızıydı.\nKısacası, niyetleri özel çevrelerde gayet iyi biliniyordu ama kimse bu konuda açıkça konuşmaya cesaret edemiyordu. Jan bugünlerde Blueweld'de arkasını yaslayıp oturuyor olabilir, ama o zamanlar ona yanlış bir laf etmek kötü sonuçlanabilirdi.\nSonunda, aralarındaki iş yürümedi. Jess, Kasap'ın ihanetinin acısıyla yaşayamıyordu ve bir yıl sonra Mask'in yardımıyla intikamını aldı. Bu intikam herkes için korkunç bitti: Kasap için, Beatrice için, Mask için ve kendisi için. Hepsi öldü.";
			link.l1 = "Hayır. Kasap hâlâ hayatta.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "Ne?! Yanlış mı duydum?! O hayatta mı?!";
			link.l1 = "Evet. Kaptan Butcher asılmadı. Aslında asıldı, ama celladı korkutan Jacob Jackman ve Henry the Hangman sayesinde hayatta kaldı. Asma sadece bir gösteriydi. Kanıtım var.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "İnanılmaz!   Peki şimdi nerede?";
			link.l1 = "Adı Lawrence Beltrop, Port Royal'da yaşıyor. Ama anlaşılan hiç değişmemiş ve hâlâ tehlikeli biri. Kardeşlik içinde başımıza çok bela açan Jackman da onun emirlerini yerine getiriyordu.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "Kahretsin! Sonunda çavuş başı kaptanını bulmuş demek! Bunca yıl sonra... Beltrop diyorsun... dur! Şimdi anladım, Blaze'in evraklarında neden o garip sorgu protokolü vardı... Görünen o ki Blaze, Kasap Beltrop hakkında ilginç bir şey keşfetmiş...";
			link.l1 = "Ne saçmalıyorsun?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "Bu eve yerleştiğimde, Blaze'in evraklarını incelemek için kendime biraz zaman ayırdım. Samuel Brooks adında biriyle ilgili bir sorgu protokolü buldum. Ünlü korsan ve Nicolas Sharp'ın en yakın dostu Thomas Beltrope'un maceralarına dair birçok ayrıntı vardı. Görünüşe göre o, Butcher'ın babasıymış.";
			link.l1 = "İlginç. Görünen o ki, Beltrop ve Sharp'ın çocukları babalarının işini devralmış...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "Öyle görünüyor... Söylesene dostum, neden çoktan ölmüş insanların geçmişiyle bu kadar ilgileniyorsun? Bütün bunların sebebi ne?";
			link.l1 = "Ellen McArthur'ın, Beatrice Sharp'ın kızı ve Nicolas Sharp'ın torunu olduğunu ve bu soyadını taşımaya hakkı olduğunu kanıtlayan belgelere ihtiyacım var. Soyadının Beltrop olmasının hiçbir önemi yok.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "Ellen McArthur hakkında Blaze'in arşivlerinde hiçbir şey bulamadım. Beatrice'in, yeğeninin doğumunu Blaze'e söylememesi tuhaf. Ona hiç benzemiyor.";
			link.l1 = "Dinle, belki Sharp'ın evraklarında bu hikayeyle ilgili başka bir şey vardır? Elde edebileceğim her detaya ihtiyacım var!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "Hm... Maybe. According to Blaze's notes, he was trying to find the island where his sister died. There are copies of archive papers concerning Leadbeater's punitive expedition. Nothing interesting, except for a few latitude numbers.\nThis parallel crosses the Caribbean Sea in its northern part. But there is no sign of longitude. Obviously, Blaze's search failed; you can't even imagine how many small islands are at that latitude.";
			link.l1 = "Ve enlem nedir?";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "Bakalım... İşte: 21° 32' Kuzey. Sana nasıl yardımcı olacağını bilmiyorum.";
			link.l1 = "Olabilir. Dürüst hikayen için çok teşekkür ederim, Marcus. Görüşürüz!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "I_know_you_good";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "terrax"; // 280912
		break;		
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "Pekâlâ, senin için bir şeyler yapabilirim. Bildiğin gibi, Tortuga'nın güvenliği sadece Fort La Roche tarafından sağlanmıyor, aynı zamanda adanın kıyılarını sürekli koruyan bir korsan filosu da var. Tortuga limanı güvende, bu adamlar işlerini iyi biliyor ve güçlü gemilere sahipler. Levasseur uzun zamandır bu kaptanları kendi tarafına çekmeye çalışıyor.\nBu adamlar bir hat filosuna bile karşı koyabilecek güçteler ve ciddi rakip olacaklar. Yani, ben Hem Korsanlar Yasası'nın koruyucusu hem de Kıyı Kardeşliği'nin lideri olarak, bu bekçilerin Tortuga'nın kıyılarını terk etmesini sağlayabilirim.";
			link.l1 = "Hepsi bu mu?";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Bu yetmiyor mu? Sana daha fazla yardımcı olamam zaten. Kaleyi yok etmen gerekiyor, ama en azından o muhafız gemileriyle savaşmak zorunda değilsin. Bana güven, onlar kaleden daha tehlikeli, bu yüzden yardımımla işin kolaylaşacak.";
			link.l1 = "Pekala, nasıl olsa saldırmam gerekecekse, korsan filosunun ayrılması gerçekten işime yarayacak. Teşekkürler, Marcus! Tortuga'ya ne zaman saldırabilirim?";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Ne zaman istersen. Muhafız gemileri benim işaretimle ayrılacak.";
			link.l1 = "Pekala. Şimdi hazırlanmak için gitmem gerekiyor.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			DialogExit();
			// Левассера - к барьеру!
			sld = characterFromId("Tortuga_Mayor");
			LAi_LoginInCaptureTown(sld, true);
			pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
			pchar.questTemp.Terrapin = "hardcore";
			pchar.questTemp.Sharlie.DelTerGuard = "true"; // убираем пиратскую эскадру
		break;
		
		case "pirate_town":
            dialog.text = " Sorunu çözmek mi? Ne yaptığının farkında mısın sen? Neyse, bana bir milyon peso getir, adamlara bu işi unuttururum. Eğer bu fikir hoşuna gitmediyse, defol git cehenneme.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Pekala, ödemeye hazırım.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Elveda...";
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
			link.l1 = "Yapmam. Benim için fazlasıyla pahalı. Hoşça kal...";
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
		
		// Addon 2016-1 Jason ------------------------- пиратская линейка --------------------------
		case "Mtraxx":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Önce kendine bir gemi bul, sonra iş iste. Karada yaşayanların burada işi yok. Defol!";
				link.l1 = "Hmm... Anladım.";
				link.l1.go = "exit";
				break;
			}
			if(ChangeCharacterHunterScore(Pchar, "spahunter", 0) > 10)
			{
				dialog.text = "Aklını tamamen mı yitirdin? İspanyol dünyasının yarısı peşinde. Fayda yerine zarar getireceksin. Önce kendi işlerini hallet, sonra başvur. Söylemek istediğim buydu! Şimdi defol buradan!";
				link.l1 = "Hmm... Anladım.";
				link.l1.go = "exit";
				break;
			}
            dialog.text = "Biraz aksiyon mu arıyorsun, ha? Ha-ha! Güzel... Ama seni uyarıyorum, oğlum, benim yanımda huzur bulamazsın. Barut kokusundan korkuyorsan ya da kan dökemiyorsan - kapı arkanda. Korkaklara tahammülüm yok. Ve ispiyoncuysan ya da ganimetten ortak payını çalmaya meraklı bir sıçansan, benimle fazla dayanamazsın. Ee, ne diyorsun? Var mısın?";
			link.l1 = "Ben varım, Marcus. Dövüşmekten korkmam ve hiçbir köpek beni ne korkaklıkla ne de hainlikle suçlayamaz.";
			link.l1.go = "Mtraxx_1";
			link.l2 = "Vay, bu bana fazla geldi! Affedersin Marcus, ama ben en iyisi gideyim...";
			link.l2.go = "Mtraxx_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "Mtraxx_exit":
            DialogExit();
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_wait":
            dialog.text = "Ne, hâlâ burada mısın?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Satacak biraz ipeğim var.";
				link.l2.go = "Mtraxx_silktrade";
				link.l1 = "Ben zaten gidiyorum.";
				link.l1.go = "exit";
				break;
			}
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Ha-ha, peki bakalım, cesur küçük korsanım, o zaman iş konuşalım. Santo Domingo'daki kaynağım bana öyle zengin bir İspanyol kaptandan bahsetti ki, mavi kehribarını fahişelere bile dağıtıyormuş. Mavi kehribarı duydun mu hiç?";
			link.l1 = "Bende var. Nadir ve değerli bir taş.";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Kesinlikle. Burada bile, bankerler ve kuyumcular buna iyi para ödüyor, eski güzel Avrupa'da ise bunun on katını alabilirsin. Kehribar Karayipler'de nadir bir taş değil, ama mavi türü gerçekten ender bulunur. Ve şimdi bir Kastilyalı tilki, Küba ve Hispaniola bankerlerinin sahip olduğu tüm sarı kehribardan daha fazla mavi kehribarı olduğunu övüne övüne anlatıyor.";
			link.l1 = "Bir sarhoş İspanyolun hikayelerine güvenilir mi? Üç dublon bulmuş, herkese El Dorado’yu bulduğunu anlatıyor.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Ben olsam yapmazdım, ama gerçekten mavilimsi kehribarları fahişelere veriyormuş. Demek ki övündüklerinde bir gerçeklik payı var. Santo Domingo'ya git ve araştır. Eğer mavi kehribar yatağını bulursan, bu daha da iyi olur. Bunu yaparsan, sana hem ödül hem de La Vega'da saygı garanti ederim.";
			link.l1 = "Ya verdiğin bilgi hiçbir işe yaramazsa?";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "O zaman bana Kastilyalının yalancı olduğunu kanıtla.";
			link.l1 = "Pekâlâ. Santo Domingo’daki kaynağın kim?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
			// belamour legendary edition даем флаг и лизензию ГВИК если отсутствует -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 60 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 60) 
					{
						sTemp = ". Wait a minute, take a trading license for 60 days."; 
						GiveNationLicence(HOLLAND, 60);
					}
				}
				else // нет флага
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ". Wait a minute, take a 60-day trade license and a Spanish flag to land in Santo Domingo. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
						GiveNationLicence(HOLLAND, 60);
						STH_SetJokerFlag(SPAIN, true);
						log_info("You have received spanish flag");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 60) 
						{
							sTemp = ". Wait, how are you going to trade without having the right flag?! Here you go, a 60-day trading license, longer than yours. As well as the Spanish flag for landing in Santo Domingo. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
							GiveNationLicence(HOLLAND, 60);
							STH_SetJokerFlag(SPAIN, true);
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Wait, how are you going to trade without having the right flag?! Here, take the Spanish flag for the Santo Domingo landings. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
							STH_SetJokerFlag(SPAIN, true);
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "Bir genelev kızı var, adı Gabriela Chapado. Benim adımı ve parolayı söyle - 'Kehribar Kolye'. Sana ayrıntıları verecek. Ve sakın vakit kaybetme - bilgi hâlâ taze, ama bir iki güne bayatlayabilir."+sTemp;
			link.l1 = "Anladım Marcus. Santo Domingo'ya gidiyorum.";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_1";
			pchar.questTemp.Mtraxx.AffairOfHonor = "true"; // конфликт с делом чести
			pchar.questTemp.ZA.Block = true;			// конфликт с квестом "Заносчивый аристократ"
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_1", "1");
			Mtraxx_JewelryBegin();
			AddMapQuestMarkCity("SantoDomingo", false);
		break;
		
		case "mtraxx_7":
			i = GetCharacterItem(pchar, "jewelry7");
            dialog.text = "Zaten gelişinden haberim vardı. Raporunu ver bakalım!";
			link.l1 = "O mavi kehribar sevdalısıyla işimi hallettim, kolay olmadı ama. Onun madenlerini bulup yağmaladım. Sana getirdim "+FindRussianQtyString(i)+" mavi kehribar parçası.";
			link.l1.go = "mtraxx_8";
			DelLandQuestMark(characterFromId("Terrax"));
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "mtraxx_8":
			if (sti(pchar.questTemp.Mtraxx.JewQty) > GetCharacterItem(pchar, "jewelry7"))
			{
				PlaySound("interface\important_item.wav");
				Log_Info("You have given "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" pieces of blue amber");
				RemoveItems(pchar, "jewelry7", GetCharacterItem(pchar, "jewelry7"));
				dialog.text = "Pekâlâ, pekâlâ... Evlat, sana fare olmanın tehlikeleri hakkında yaptığım uyarıyı hatırlıyor musun? O zaman bana ne demiştin? Hiçbir köpek seni bunun için suçlayamaz mı dedin? Beni aptal mı sanıyorsun, çocuk? Senin yağmaladığının gayet farkındayım "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.JewQty))+" Miskito Sahili'nde mavi kehribar parçaları buldum. Şimdi koş, küçük fare, koş, ve bir daha asla karşılaşmamamız için dua et!";
				link.l1 = "Lanet olsun!";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.Dialog.currentnode = "First time";
				CloseQuestHeader("Roger_1");
				// belamour legendary edition забрать флаг обратно
				if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
				{
					DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
					STH_SetJokerFlag(SPAIN, false); 
					log_info("You have given spanish flag");
				}
			}
			else
			{
				PlaySound("interface\important_item.wav");
				Log_Info("You have given "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" pieces of blue amber");
				RemoveItems(pchar, "jewelry7", sti(pchar.questTemp.Mtraxx.JewQty));
				dialog.text = "Aferin, oğlum! En iyi yanını gösterdin: zor bir işi hallettin ve ele geçirdiğin her şeyi getirdin. İyi iş çıkardın! Senin hakkında yanılmadığıma sevindim.";
				link.l1 = "Benim payım ne olacak, Marcus?";
				link.l1.go = "mtraxx_9";
			}
		break;
		
		case "mtraxx_9":
			i = sti(pchar.questTemp.Mtraxx.JewQty)/2;
			PlaySound("interface\important_item.wav");
			Log_Info("You have received "+FindRussianQtyString(i)+" pieces of blue amber");
			TakeNItems(pchar, "jewelry7", i);
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				STH_SetJokerFlag(SPAIN, false); 
				log_info("You have given spanish flag");
			}
            dialog.text = "Gerçek bir korsan gibi konuştun, ha-ha-ha! Ganimetin yarısı senin. Al bakalım.";
			link.l1 = "Sağ ol, Kaptan. Başka bir işin var mı bana?";
			link.l1.go = "mtraxx_10";
			DeleteAttribute(pchar, "questTemp.Mtraxx.JewQty");
			CloseQuestHeader("Roger_1");
			Achievment_Set("ach_57");
		break;
		
		case "mtraxx_10":
            dialog.text = "I always have tasks for capable lads. There is a delicate matter I want you to deal with. There is a ship stationed in Capsterville, called the 'Snake', under the command of Geffrey Brooke, also known as Bald Geffrey. He works for me. An excellent fighter, knows everything about guns and blades, yet a complete idiot in every other aspect of life. But let's not be too hard on Baldy, no one is perfect, ha-ha! So. This tough guy attacked a Dutch convoy north of Saint Martin and captured a bark filled with sacks of wheat. Thing is, he managed to find hidden ship silk among the sacks. A really big cargo. This merchandise is extremely valuable and rare; the Dutch bring it from Europe solely for their military needs. This silk is used for special sails which increase a ship's speed and ability to sail by the wind. It is almost impossible to buy, selling it is not a problem but it is hard to find the right price. These goddamn traders always reduce the price! I am aware that there are people in the Caribbean who are ready to give a good price in doubloons to buy this silk, and your goal is to find such people. What? Any fool can plunder caravans, but trade is only for people with at least a sign of brains' existence in their skull. I am planning to sell ship silk on a monthly basis, so your goal is to find a regular buyer who will pay at least 4 golden doubloons for a roll. You have two months to do that, I cannot keep Bald Geffrey in Capsterville forever. That's all. Set sail to Capsterville and talk to Geffrey before he sells the cargo to smugglers for a penny. I've already told you that he is a bit 'simple'.";
			link.l1 = "Hm... Anladım. Zaten yoldayım.";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_1";
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_2", "1");
			Mtraxx_SilkBegin();
		break;
		
		case "mtraxx_12":
            dialog.text = "Ha! İşte cesur kaptan "+GetFullName(pchar)+"! Peki ya alıcı?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				link.l1 = "I've found you a buyer. He's a shipbuilder from Port Royal. He needs ship silk for his production and will be able to buy batches of one hundred rolls every month for 5 doubloons a roll. His men will collect the goods from the 10th to the 15th, at night, at Negril Cape. The password is 'A merchant of Lyons'. It took me more than two months to find such a buyer; Geffrey must have already sold the silk to smugglers. I'm sorry, Marcus.";
				link.l1.go = "mtraxx_15";
			}
			else
			{
				link.l1 = "Sana bir alıcı buldum. Port Royal'dan bir gemi yapımcısı. Üretimi için gemi ipeğine ihtiyacı var ve her ay yüz top halinde, top başına 5 dublon ödeyerek satın alabilecek. Adamları malları her ayın 10'u ile 15'i arasında, gece vakti Negril Burnu'nda teslim alacak. Parola: 'Lyonlu bir tüccar'. Kel Geffrey ilk partiyi Jamaika'ya çoktan teslim etti.";
				link.l1.go = "mtraxx_13";
			}
		break;
		
		case "mtraxx_13":
            dialog.text = "Harika, dostum! Güzel iş çıkardın. Hem ellerini hem de kafasını kullanabilen bir adam bulmak zor. Ödülünü almak için 20 gün sonra yanıma gel. O zamana kadar Kel Geffrey ilk işten parayı getirmiş olur."; // правки прогона 3
			link.l1 = "Pekala, Marcus. Yakında görüşürüz. Umarım benim için başka bir işin olur.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_14":
            dialog.text = "Yapacağım. Sonra görüşürüz.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 30, false);
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 40, false);
				AddQuestRecord("Roger_2", "23");
			}
			else
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 20, false); // правки прогона 3
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 30, false);
				AddQuestRecord("Roger_2", "24");
			}
		break;
		
		case "mtraxx_15":
			pchar.quest.Mtraxx_SilkTimeLateAll.over = "yes";
            dialog.text = "Yazık, ama yine de büyük bir başarı. İyi iş çıkardın! Geffrey'nin partisinden payını alamayacaksın, ama yine de bir ödülü hak ettin. Bir ay sonra yanıma gel, o zamana kadar ilk partiyi alıcına satmış olurum, sonra konuşuruz.";
			link.l1 = "Pekala, Marcus. Yakında görüşürüz. Umarım bana yeni bir işin olur.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_16":
			//pchar.quest.Mtraxx_SilkPayLate.over = "yes";
            dialog.text = "İşte buradasın, "+pchar.name+". Ödülün hakkında konuşalım.";
			link.l1 = "Böyle sohbetleri severim, ha-ha-ha! Kulak kesildim.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate")) link.l1.go = "mtraxx_19";
			else link.l1.go = "mtraxx_17";
		break;
		
		case "mtraxx_17":
            dialog.text = "Kel Geffrey, alıcına ilk 105 top gemi ipeğini sattı. Ben top başına 4 dublon bekliyordum, bu yüzden aradaki farkı sana vermek adil olur. Kararım bu. Payın 105 dublon ve üstüne bir de bonus - her top için bir dublon. Yani toplamda 210 dublon ediyor. Al, bunlar senin.";
			link.l1 = "Teşekkür ederim, Marcus!";
			link.l1.go = "mtraxx_18";
		break;
		
		case "mtraxx_18":
			TakeNItems(pchar, "gold_dublon", 210);
			PlaySound("interface\important_item.wav");
            dialog.text = "Bir şey daha. Bundan biraz daha fazla kazanç elde edebilirsin.";
			link.l1 = "İlginç... Devam et.";
			link.l1.go = "mtraxx_19";
		break;
		
		case "mtraxx_19":
            dialog.text = "Alıcın önümüzdeki iki ay içinde 100'den fazla ipek rulosu istiyor. Eğer elinde varsa, bana 20 ila 100 rulo getir, tanesi 5 dublondan alırım. Teklif iki ay geçerli.";
			link.l1 = "Pekala! Varsa daha fazla getiririm.";
			link.l1.go = "mtraxx_20";
			pchar.questTemp.Mtraxx.SilkTrade = "true";
			SetFunctionTimerCondition("Mtraxx_SilkTradeOver", 0, 0, 60, false);
		break;
		
		// торговля шелком
		case "mtraxx_silktrade":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "Ne kadarın var?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			if (iTotalTemp > 100) link.l1.go = "mtraxx_silktrade_2";
			else link.l1.go = "mtraxx_silktrade_1";
		break;
		
		case "mtraxx_silktrade_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*5);
            dialog.text = "Çok iyi. Al altınları - bir zar atışı için 5 dublon, anlaştığımız gibi.";
			link.l1 = "Teşekkürler!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_2":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 100);
			TakeNItems(pchar, "gold_dublon", 500);
            dialog.text = "Yüz rulo alacağım. Altını al - her rulo için 5 dublon, anlaştığımız gibi.";
			link.l1 = "Teşekkürler!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_3":
            DialogExit();
			npchar.dialog.currentnode = "First time";
			DeleteAttribute(pchar, "questTemp.Mtraxx.SilkTrade");
		break;
		
		case "mtraxx_20":
            dialog.text = "Daha acil bir şey konuşalım, tehlikeli bir işle uğraşmak ister misin?";
			link.l1 = "Tabii! Adamlarım ve ben hemen yelken açmaya hazırız.";
			link.l1.go = "mtraxx_24";
		break;
		
		case "mtraxx_22":
            dialog.text = "Allah'ın belası, "+pchar.name+", nerelerdeydin sen? Sana yanıma gelmeni söylediğimi hatırlıyor musun? Sana bir işim vardı, ama senin harika zamanlaman sayesinde heba oldu. Beni gerçekten sinirlendirdin, çocuk. Defol git, güvenemediğim insanlarla çalışmam.";
			link.l1 = "Vay kahretsin...";
			link.l1.go = "mtraxx_23";
		break;
		
		case "mtraxx_23":
			DialogExit();
            npchar.dialog.currentnode = "First time";
			CloseQuestHeader("Roger_2");
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_24":
			// belamour legendary edition даем флаг и лизензию ГВИК если отсутствует -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 40 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 40) 
					{
						sTemp = ", as well as a trade license for 40 days."; 
						GiveNationLicence(HOLLAND, 40);
					}
				}
				else // нет флага
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ", as well as a trade license for 40 days. Besides, how are you going to fool the bungler in the fort?! You will let me down one day with such sloppiness... Here you go... You will return it back upon arrival. The new generation, pah...";
						GiveNationLicence(HOLLAND, 40);
						STH_SetJokerFlag(SPAIN, true);
						log_info("You have received spanish flag");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 40) 
						{
							sTemp = ". Tell me, how are you going to fool the bungler in the fort?! Your paper won't help you without the right flag. I feel that you will let me down one day with such sloppiness... Here, a trading license for 40 days, more than yours. As well as the Spanish flag for landing in Maracaibo. You will return it upon arrival. The new generation, pah...";
							GiveNationLicence(HOLLAND, 40);
							STH_SetJokerFlag(SPAIN, true);
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Tell me, how are you going to fool the bungler in the fort?! Your paper won't help you without the right flag. I feel that you will let me down one day with such sloppiness... Here you go... You will return it back upon arrival. The new generation, pah...";
							STH_SetJokerFlag(SPAIN, true);
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "Then listen closely. Two months ago I had an appointment with a captain by the name of Jean Picard, also known as Jean the Handsome. He didn't show up to the meeting and since I was going to discuss serious matters with him, I did some investigation regarding his whereabouts. Turned out our good brave privateer and his brigantine had managed to engage in a fight with a Spanish heavy galleon under command of don Eduardo de Losad and he is a tough son of a bitch. As a result, Jean and what's left of his crew was taken to Maracaibo and sold to a local plantation. This is where he is, busy with honest labor, at the moment.\nYour tasks are: firstsly - investigate the details of his misfortunes, secondly - get him out from plantation alive and bring him here; I really need details of his story. I am assigning a captain of a barquentine called 'Moray' to assist you in this. Captain's name is Paul Chant also known as Pelly the Cutlass. Remember Geffrey? He is almost as dumb as him, but good at fighting too.\nHe will be waiting for you at cape Ragget Point, on Barbados. Find him and his 'Moray' and sail to Maracaibo. Cutlass will follow your orders without asking stupid questions. Actually, he won't be asking questions at all. Just do your job and come back here, I'll be waiting for you. Here is ten thousand pesos for future expenses"+sTemp+". Any questions?";
			link.l1 = "Hayır. Her şey açık. Barbados'a gidiyorum.";
			link.l1.go = "mtraxx_25";
		break;
		
		case "mtraxx_25":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "O zaman sana bol şans. Acele et, Cutlass'ı ve zavallı Jean'ı bekletme.";
			link.l1 = "Tabii, patron! Hemen geliyorum.";
			link.l1.go = "mtraxx_26";
		break;
		
		case "mtraxx_26":
            DialogExit();
			CloseQuestHeader("Roger_2");
			npchar.dialog.currentnode = "mtraxx_wait";
			// belamour legendary edition по пути могут заскочить к Московиту, если рабов нет
			pchar.questTemp.Mtraxx.GiveMeSlaves = "Baster";
			AddQuestRecord("Roger_3", "1");
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			Mtraxx_PlantBegin();
		break;
		
		case "mtraxx_27":
			pchar.quest.Mtraxx_PlantGoHomeOver.over = "yes"; 
            dialog.text = "Tekrar hoş geldin, cesur korsanım, ha-ha! Bir İspanyol filosunu batırdın mı? Picard bana çoktan anlattı. Güzel iş!";
			link.l1 = "Evet, adamlarım Maracaibo'dan ayrılırken onlara iyi bir ders verdi.";
			link.l1.go = "mtraxx_28";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup3"))
			{
				dialog.text = "Tekrar hoş geldin, cesur korsanım, ha-ha! Picard bana çoktan anlattı. Aferin sana!";
				link.l1 = "...";
				link.l1.go = "mtraxx_28";
			}
		break;
		
		case "mtraxx_28":
            dialog.text = "Gözlerinde ödülünü beklediğini görebiliyorum. Haklısın. Jean sana ödeyecek, sonuçta orada kurtarmaya çalıştığımız onun hayatıydı. Ona bir fatura gönder, ama sonra – çocuğun ne tayfası var ne de gemisi. Akıllı bir çocuk, tıpkı senin gibi, bu hali uzun sürmez.";
			link.l1 = "Hm... Pekala... Bekleyeceğim. Marcus, bana göre bir iş var mı? Kimseyi kurtarmak ya da aramakla ilgili olmayan bir şey?";
			link.l1.go = "mtraxx_29";
		break;
		
		case "mtraxx_29":
            dialog.text = "En parlak mum olmaktan yoruldun mu? Seni burada hayal kırıklığına uğratacağım: Cutlass gibi beyin yoksunu haydutlardan bende bolca var, bu yüzden yeteneklerini ona göre kullanacağım. Bir ay sonra sana bir işim olacak. Şimdilik, Isla Tesoro'ya gitmeli ve Pasquale Lavoisier ile görüşmelisin, kendisi Sharptown'ın tüccarıdır.\nCiddi bir iş için kendisine mümkün olan en kısa sürede sert bir korsan gönderilmesini istedi – muhtemelen tam da istediğin şey: daha az düşünmek, daha çok ateş etmek. Ona kendini tanıtmak için bir haftan var, o yüzden vakit kaybetme yoksa bu görevi kaybedersin. Ve kibar ol, onu kandırmaya çalışma, bu adam Kardeşlik arasında saygı görür. Şimdi git, bir ay sonra yanıma gel. Sakın geç kalma!";
			link.l1 = "Pekâlâ, Marcus. Görüşürüz!";
			link.l1.go = "mtraxx_30";
		break;
		
		case "mtraxx_30":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				STH_SetJokerFlag(SPAIN, false); 
				log_info("You have given spanish flag");
			}
			CloseQuestHeader("Roger_3");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_4", "1");
			pchar.questTemp.Mtraxx = "pasq_start";
			Mtraxx_PasqualeBegin();
			SetFunctionTimerCondition("Mtraxx_PlantFithTaskTimer", 0, 0, 35, false);
			SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
		
		case "mtraxx_31":
            dialog.text = "Vay canına! Bir ölü geri dönmüş! Seni çoktan gömmüştük, oğlan! Ama demek ki hâlâ hayattasın";
			link.l1 = "Gördüğün gibi, Marcus...";
			link.l1.go = "mtraxx_32";
		break;
		
		case "mtraxx_32":
            dialog.text = "O halde Maracaibo'dan Hispaniola'ya gelmen neden bu kadar uzun sürdü? Artık örgütümde yoksun, oğlum. Seni sağ görmekten gerçekten memnunum, ama burada senin için başka iş yok.";
			link.l1 = "Eh!.. Ne yazık...";
			link.l1.go = "mtraxx_33";
		break;
		
		case "mtraxx_33":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_34x":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_34";
		break;
		
		case "mtraxx_34":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 35 && !bImCasual) // опоздал
			{
				dialog.text = "Kahretsin "+pchar.name+", neredeydin sen?! Sana bir ay sonra gel dedim! Burası ordu değil ama biraz disiplin beklenir! Defol git, artık seninle çalışmayacağım!";
				link.l1 = "Nasıl istersen...";
				link.l1.go = "mtraxx_33";
				break;
			}*/
			if (GetNpcQuestPastDayParam(npchar, "task_date") < 28) // рано пришёл
			{
				dialog.text = ""+pchar.name+", sana 'bir ay sonra gel' dedim. Şu anda sana ayıracak vaktim yok.";
				link.l1 = "Pekala...";
				link.l1.go = "mtraxx_34x";
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_angry")
			{
				dialog.text = "Lavoisier’in adamı, onun siyah ağacı konusunda ona kazık attığını söyledi. Sana farelik yapmamanı ve Pasquale’e adil olmanı söylemiştim. İki kuralımı da çiğnedin. Akıllı birisin, ama bu kabul edilemez. Defol buradan ve buraya giden yolu unut.";
				link.l1 = "Siktir...";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_fail")
			{
				dialog.text = "Lavoisier'in adamı, siyah kerestesiyle onu kandırdığını, tüm partiyi getirmediğini söyledi. Eğer bu işi akılsız Cutlass ya da Bald yapmış olsaydı, belki de gerçekten tüm yükü ele geçiremediklerine inanırdım. Ama senin kadar zeki biri... Pasquale'i kandırmaya mı kalktın? Sana 'onu aldatma' demiştim! Artık sana güvenim kalmadı, seninle de işim bitti. Defol buradan ve bu yerin yolunu da unut!";
				link.l1 = "Senin Lavoisier de tam bir fare!";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_late" || pchar.questTemp.Mtraxx == "pasq_sink" || pchar.questTemp.Mtraxx == "pasq_esc")
			{
				pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират // правки прогона 3
				dialog.text = "Ha! Charlie Prince, cesur bir kaptan! La Vega'da yeni adın bu, bilmediysen söyleyeyim. Peki, zorba rolünü oynamaktan keyif aldın mı? Yoksa? Şans Tanrıçası bu sefer sırtını mı döndü sana? Benim beyin yoksunu ajanlarım Cutlass gibi yaşar: bugün genelevde eğlenir, kazandığı her şeyi harcar, bir hafta sonra kapımda dilenip, kendi gibi aptal tayfasına ödeyecek birkaç binlik ister. Neyse. İş konuşalım mı?";
				link.l1 = "Tabii ki!";
				link.l1.go = "mtraxx_36";
				break;
			}
            dialog.text = "Ha! Charlie Prince, cesur bir kaptan! Ha-ha! Lavoisier’in adamı bana iyi iş çıkardığını söyledi. Bizim fırsatçımıza biraz saygı gösterebildiğine sevindim.";
			link.l1 = "Biraz daha cömert olsa fena olmazdı...";
			link.l1.go = "mtraxx_35";
		break;
		
		case "mtraxx_35":
			pchar.questTemp.Mtraxx.Pasquale.Continue = "true"; // правки прогона 3
            dialog.text = "Sana o beyinsiz zorbalardan ve çalıntı mal alanlardan bahsettiğimi hatırlıyor musun? Güzel. Bir daha asla böyle bir işe bulaşma. Bırak bu işleri Cutlass gibiler yapsın. Neyse. Şimdi iş konuşalım mı?";
			link.l1 = "Tabii ki!";
			link.l1.go = "mtraxx_36";
		break;
		
		case "mtraxx_36":
            dialog.text = "Harika! Jean Picard buraya geliyor, sana daha fazlasını anlatacak. Bu görevde Jean'la birlikte çalışacaksınız. Ayrıca, bu onun sana olan borcunu ödemesi için bir fırsat... İşte geliyor!";
			link.l1 = "...";
			link.l1.go = "mtraxx_37";
		break;
		
		case "mtraxx_37":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_38";
			chrDisableReloadToLocation = true;
			// преобразуем Пикара
			sld = characterFromId("Mrt_Rocur");
			sld.model = "Jan_Pikar";
		
			SetCharacterPerk(sld, "GunProfessional");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			GiveItem2Character(sld, "blade_17");
			EquipCharacterbyItem(sld, "blade_17");
			GiveItem2Character(sld, "pistol6");
			EquipCharacterbyItem(sld, "pistol6");
			TakeNItems(sld, "bullet", 40);
			TakeNItems(sld, "gunpowder", 40);
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.dialog.currentnode = "rocur_29";
			sld.greeting = "Rocur_03";
			Characters_RefreshModel(sld);
			LAi_SetCheckMinHP(sld, 10, true, "");
			TakeNItems(sld, "potion2", 7);
			TakeNItems(sld, "potion3", 7);
			TakeNItems(sld, "potion4", 7);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "mtraxx_38":
            dialog.text = "My man will join your raid. Name's Luka Bayard, mostly known as Luke Leprechaun. He and his men are buccaneers—hunters who have spent most of their lives in the forests of Hispaniola. So they are masters at trekking through the jungle; add your fighters to theirs and consider Merida yours. You'll take a third of the loot. The rest goes to Jean. Jean, you'll pay your debt to this brave captain from your share, then bring what's left to me. We'll settle things between us then. Questions? Splendid! Leprechaun will be waiting for you in our harbour. Good luck, corsairs, ha-ha!";
			link.l1 = "...";
			link.l1.go = "mtraxx_39";
		break;
		
		case "mtraxx_39":
            DialogExit();
			CloseQuestHeader("Roger_4");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_5", "1");
			pchar.questTemp.Mtraxx = "merida_start";
			Mtraxx_MeridaBegin();
			LAi_SetHuberType(npchar);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Mtraxx_MeridaAddPicar", 5.0);
			pchar.GenQuest.HunterLongPause = true;
		break;
		
		case "mtraxx_40":
            dialog.text = "Tekrar hoş geldin, cesur haydutum! Baskının haberi çoktan bize ulaştı.";
			link.l1 = "Bunu duymaktan hoşlandığımı söyleyemem. Böyle şeyler bilinmese daha iyi...";
			link.l1.go = "mtraxx_41";
		break;
		
		case "mtraxx_41":
            dialog.text = "Bana güven, asla öyle olmazlar, dostum. Neyse. Picard sana olan borcunu ödedi mi?";
			link.l1 = "Evet.";
			link.l1.go = "mtraxx_42";
		break;
		
		case "mtraxx_42":
            dialog.text = "Çok iyi. Luke Leprechaun sende iyi bir izlenim bıraktı mı?";
			link.l1 = "Yaptı.";
			link.l1.go = "mtraxx_43";
		break;
		
		case "mtraxx_43":
            dialog.text = "O zaman harika. Herkes mutlu, herkes parasını aldı.";
			link.l1 = "Benim için bir işin var mı, Marcus?";
			link.l1.go = "mtraxx_44";
			// belamour legendary edition отказ после событий Мериды
			link.l2 = "Biliyor musun Marcus, her şeyi düşündüm ve bu iş bana göre değil. Üzgünüm ama kararımı çoktan verdim.";
			link.l2.go = "mtraxx_44a";
		break;
		
		case "mtraxx_44":
            dialog.text = "Henüz gerçek bir iş yok. Ama senden kişisel bir ricam olacak. İlgilenir misin?";
			link.l1 = "Tabii, patron. Ne isteğin var?";
			link.l1.go = "mtraxx_45";
		break;
		
		case "mtraxx_45":
            dialog.text = "La Vega kıyılarında 'Kittie' adında bir pinas var. Günlerdir orada, Bridgetown'a kadar eşlik edecek birini bekliyor. Onu oraya tek başına göndermem söz konusu bile olamaz, sebeplerini sen de biliyorsun. Ona eşlik etme nezaketini gösterir misin? Döndüğünde seni gerçek bir işle bekliyor olacağım. Ve elbette, bu eskortluk için de paranı alacaksın.";
			link.l1 = "Anlaştık.";
			link.l1.go = "mtraxx_46";
		break;
		
		case "mtraxx_46":
            dialog.text = "Güzel! İyi seyirler.";
			link.l1 = "Teşekkürler!";
			link.l1.go = "mtraxx_47";
		break;
		
		case "mtraxx_47":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_6", "1");
			pchar.questTemp.Mtraxx = "ignasio_start";
			sld = characterFromId("Mtr_KittyCap");
			DeleteAttribute(sld, "DontDeskTalk");
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
		break;
		// belamour legendary edition -->
		case "mtraxx_44a":
            dialog.text = "Ne?! Seni sokaktan aldım, ceplerini kehribar ve mücevherle doldurdum! Bana böyle mi karşılık veriyorsun?";
			link.l1 = "Merida bana bu iş için yeterince acımasız olmadığımı gösterdi. Senin ve adamların kadar acımasız değilim. Zalim olma.";
			link.l1.go = "mtraxx_45a";
		break;
		
		case "mtraxx_45a":
            dialog.text = "Zavallı! Hadi, defol! Git biraz yük taşı ya da daha iyisi, diğer zavallılar gibi içip geber!";
			link.l1 = "...";
			link.l1.go = "mtraxx_46a";
		break;
		
		case "mtraxx_46a":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "First time";
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			sld = characterFromId("Mtr_KittyCap");
			sld.lifeday = 0;
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx = "fail";
			if(CheckAttribute(pchar, "GenQuest.HunterLongPause")) DeleteAttribute(pchar, "GenQuest.HunterLongPause");
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // выставим за дверь
		break;
		// <--- legendary edition
		case "mtraxx_48":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "Ah, işte geldin... Seni bekliyordum. 'Kittie'yi koruduğun için işte 10.000.";
			link.l1 = "Teşekkürler... Seninle konuşmam gereken bir şey var, Marcus.";
			link.l1.go = "mtraxx_49";
		break;
		
		case "mtraxx_49":
            dialog.text = "Sen mi?! Ha-ha! Ateş et!..";
			link.l1 = "Jean Picard'ın nasıl köleleştirildiğini hatırlıyor musun? Önce bir İngiliz korsanıyla birlikte bir Hollanda kervanını yağmaladı, sonra da aynı şey ona bir İspanyol ağır gemisi tarafından yapıldı.";
			link.l1.go = "mtraxx_50";
		break;
		
		case "mtraxx_50":
            dialog.text = "Hatırla. Sonra?";
			link.l1 = "Bridgetown'da bana Ignacio Marco yaklaştı. Aynı İngiltere'ye hizmet eden Portekizli korsan. Curacao ile Trinidad arasında ıssız bir adanın yakınlarında bir Hollanda kervanını yağmalamamı teklif etti.";
			link.l1.go = "mtraxx_51";
		break;
		
		case "mtraxx_51":
            dialog.text = "Pekala, pekala... Kabul ettin mi?";
			link.l1 = "Yaptım. Öncelikle, bu iyi bir anlaşmaydı. İkincisi, Picard'ın hikayesini hatırladım ve araştırmaya karar verdim...";
			link.l1.go = "mtraxx_52";
		break;
		
		case "mtraxx_52":
            dialog.text = "Eminim öyle yaptın.";
			link.l1 = "Evet. Bir kervan vardı, işi temiz ve düzgün hallettik. Sonra ganimeti karada paylaştık, ama önce sessizce bir gözcüyü dürbünle tepeye gönderdim. İyi ki de göndermişim, çünkü kısa süre sonra başında ağır bir kalyon olan bir İspanyol filosu ortaya çıktı.";
			link.l1.go = "mtraxx_53";
		break;
		
		case "mtraxx_53":
            dialog.text = "Ortağın kesin kaçtı, bu yüzden İspanyollar seni mi kovaladı?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.LosadaSink")) 
			{
				link.l1 = "Aynen öyle. Ona hiç aldırış etmediler. Onların kaybı: İspanyollarla öyle bir savaştık ki, bunu asla unutamayacaklar. O Kastilyalılar iyi dövüşçülerdi, ama tüm filoyu yere serdik.";
				link.l1.go = "mtraxx_53x";
			}
			else
			{
				link.l1 = "Aynen öyle. Ona hiç dikkat bile etmediler. Ben ise gözcüm sayesinde kaçmayı başardım...";
				link.l1.go = "mtraxx_53y";
			}
		break;
		
		case "mtraxx_53x":
			DeleteAttribute(pchar, "questTemp.Mtraxx.LosadaSink");
            dialog.text = "Heh! Eduardo de Losad'ın filosunu indirdin ha! Sen tam bir Deniz Şeytanısın, Prens! Bahse girerim İspanyollar çoktan peşine avcılarını salmıştır.";
			link.l1 = "Onların suçu... Yine de, bu pislikle ilgilenmeliyiz Ignacio. Ne demek istediğimi anlıyorsun, değil mi?";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_53y":
            dialog.text = "Heh! Kastilyalılar senin ellerinden kaçtığını fark edince ortalığın nasıl karıştığını hayal edebiliyorum! Güzel iş çıkarmışsın!";
			link.l1 = "Onların derdi, benim değil. Yine de, bu pislikle ilgilenmeliyiz, Ignacio. Ne demek istediğimi anlıyorsan.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_54":
            dialog.text = "Ben hallederim. Bu Ignacio Marco hakkında daha fazla şey öğrenmeliyiz. Birisi için çalışıyor olabilir. Adamlarıma olan 'ilgisi' şüpheli. Hangi geminin sahibi?";
			link.l1 = "Bir polacre, 'Torero'. Eşsiz bir gemi, özgün bir tasarım olmalı.";
			link.l1.go = "mtraxx_55";
		break;
		
		case "mtraxx_55":
            dialog.text = "Güzel, o zaman onu izlemek daha kolay olacak... Anladım. Ve sana gelince, Prens, sana bir işim var. Hazır mısın?";
			link.l1 = RandSwear()+"Elbette, reis!";
			link.l1.go = "mtraxx_56";
		break;
		
		case "mtraxx_56":
            dialog.text = "O halde dinle. Bir süre önce bölgemizde ilginç bir korsan vardı. Adı Wulfric Iogansen, namıdiğer Kızıl Kurt. Çok renkli bir karakterdi. Birkaç yıl önce Avrupa'nın kuzeyinden buralara geldi. Bu Viking, Levasseur'a koruma parası ödemiyor, kimseyle dostluk kurmuyor ve kendi halinde takılıyordu. Çok ketum biriydi, tayfasından kimse sağ çıkmamıştı. Tayfasından biri meyhanede baskınları hakkında konuşacak olursa, dillerini bizzat kendisi kestiği söylenirdi... Çoğu korsandan farklı olarak, Wulfric parayı fahişelere ya da içkiye harcamazdı. Ganimetini ucuza satmazdı. Bankerlere güvenmez, gemisini de hiç değiştirmezdi. Elinde güzel bir korvet, 'Freyja', ve sadık bir tayfası vardı; hizmetleri ve sessizlikleri için iyi para öderdi. Bence olabildiğince çok altını biriktirip Avrupa'ya dönüp orada kral gibi yaşamak istiyordu. Ama işler onun için öyle gitmedi, İspanyol avcılar sayesinde. Bu adam İspanya'ya büyük zararlar vermişti, bu yüzden ceza seferleri onu Hispaniola açıklarında avladı, 'Freyja'yı batırdı ve tüm tayfasıyla birlikte Kurt'u da öldürdü. Sığ sularda İspanyol gemileriyle çevrili halde, Kızıl Kurt ölümünü buldu. Ama mesele şu: La Vega'daki herkes Kurt'un hazinelerini biliyordu ve batık 'Freyja'yı bile buldular, ama ne yerliler ne de dalgıçlar hiçbir hazineye rastlamadı. Aptal değildi, mutlaka orada, sadece kendisinin ve tayfasının bildiği büyük bir saklanma yeri vardı, ama onlara... malum nedenlerle soramayız. Şimdi ise işin ilginç kısmı geliyor: Elimde onun sapasağlam kaptan günlüğü var, gemisinde kilitli bir sandıkta saklanmıştı. Hazinenin yerini açıkça göstermiyor, ama satır aralarında bir şeyler bulabilirsin. Günlüğü oku, Viking'in Karayipler'de iki yıl yağmaladıktan sonra hazinesini nereye sakladığını öğren ve bul. Başarırsan – üçte ikisi senin. Var mısın?";
			link.l1 = "Hm... karanlık bir odada kara kedi aramaya benziyor. Kayıt nerede?";
			link.l1.go = "mtraxx_57";
		break;
		
		case "mtraxx_57":
            dialog.text = "Al, işte burada. İyi şanslar!";
			link.l1 = "Sağ ol, buna ihtiyacım olacak...";
			link.l1.go = "mtraxx_58";
		break;
		
		case "mtraxx_58":
            DialogExit();
			CloseQuestHeader("Roger_6");
			npchar.dialog.currentnode = "mtraxx_wait";
			GiveItem2Character(pchar, "wolfreeks_book");
			AddQuestRecord("Roger_7", "1");
			pchar.questTemp.Mtraxx = "wolfreek_start";
			pchar.questTemp.Mtraxx.Logbook.CanRead = "true";
			pchar.questTemp.Mtraxx.Logbook.Page1 = "true";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
		break;
		
		case "mtraxx_59":
            dialog.text = "Ah, işte cesur kaptanımız geldi. Kızıl Kurt'un hazinesi ne oldu?";
			link.l1 = "Üzerinde çalışıyorum. Bunun için senin yardımına ihtiyacım var.";
			link.l1.go = "mtraxx_60";
		break;
		
		case "mtraxx_60":
            dialog.text = "Dinliyorum.";
			link.l1 = "Wulfric'in günlüğünde birkaç kez geçen bilinmeyen bir kelime var, 'Gord'. Soruşturmama devam edebilmem için bunun anlamını öğrenmeliyim.";
			link.l1.go = "mtraxx_61";
		break;
		
		case "mtraxx_61":
            dialog.text = "Hm... Gord, diyorsun... Ben de daha önce hiç duymadım. Peki, bir hafta sonra yanıma gel: Gemilerde katiplik yapan birkaç akıllı kafayla konuşacağım. En azından saymayı ve okumayı biliyorlar. Belki bize bir fikir verirler.";
			link.l1 = "Pekâlâ, Marcus. O zaman bir hafta sonra görüşürüz.";
			link.l1.go = "mtraxx_62";
		break;
		
		case "mtraxx_62":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			SetFunctionTimerCondition("Mtraxx_WolfreekTimer", 0, 0, 7, false);
		break;
		
		case "mtraxx_63":
            dialog.text = "Senin için bir cevabım var. Bir ukala bana akıl verdi. Gord, özgür bir jarlın tahkimli yerleşimidir.";
			link.l1 = "Özgür bir jarl mı? O da kim?";
			link.l1.go = "mtraxx_64";
		break;
		
		case "mtraxx_64":
            dialog.text = "Bir çeşit Viking korsan amirali. Mesela, ben özgür bir jarlım ve La Vega benim gordum. Görünen o ki, Kızıl Kurt atalarının hikayesini bayağı sevmiş, ha-ha! Bu bilgi işine yaradı mı?";
			link.l1 = "Henüz bilmiyorum. Önce notları karşılaştırmam lazım. Yani Gord yerleşim anlamına geliyor... Teşekkürler, Marcus!";
			link.l1.go = "mtraxx_65";
		break;
		
		case "mtraxx_65":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			Mtraxx_WolfreekReadLogbookFourth();
		break;
		
		case "mtraxx_66":
            dialog.text = "Ee? O ukalıklı suratından işini başardığını anlıyorum.";
			link.l1 = "Evet. Kızıl Kurt'un hazinesi bulundu! Ama kolay olmadı.";
			link.l1.go = "mtraxx_67";
		break;
		
		case "mtraxx_67":
            dialog.text = "Vikinglerimiz ne kadar sakladı?";
			link.l1 = "750.000 peso ve 900 dublon.";
			link.l1.go = "mtraxx_68";
		break;
		
		case "mtraxx_68":
            dialog.text = "Ho-ho! İyi iş çıkardın, Prens. Peki ya benim payım?";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "Al, bunu da yanında götür. Anlaştığımız gibi: 250.000 peso ve 300 dublon.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "Tüm peso ve doblonlar kamarımda. Onları buraya getirmem için bana bir dakika ver!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_68_1":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_68_2";
		break;
		
		case "mtraxx_68_2":
            dialog.text = "Payımı getirdin mi?";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "Al, bunu al. Anlaştığımız gibi: 250.000 peso ve 300 dublon.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "Evet-evet, geliyorum!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_69":
			AddMoneyToCharacter(pchar, -250000);
			RemoveDublonsFromPCharTotal(300); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "Çok iyi. Yine harika iş çıkardın. Aferin!";
			link.l1 = "Marcus, Ignacio Marco hakkında bir şey öğrenebildin mi?";
			link.l1.go = "mtraxx_70";
			// mitrokosta возможность отстройки исламоны
			pchar.questTemp.IslaMona = "start";
		break;
		
		case "mtraxx_70":
            dialog.text = "Evet, ama önce doğrulamam lazım...";
			link.l1 = "Ne?";
			link.l1.go = "mtraxx_71";
		break;
		
		case "mtraxx_71":
            dialog.text = "Marco'nun birileriyle bağlantısı olduğundan şüpheleniyorum... Ve kiminle olduğunu bulmanı istiyorum. Martinique'e git. Gemini Saint Pierre'de bırak ve ormandan geçerek Le Francois'ya ulaş. Adamımızın orada görüldüğünü duydum. Etraftaki korsanlara bir şey sorma, sadece izle ve gözlemle. Onu bulduğunda, takip et ve nereye gittiğini ya da kiminle buluştuğunu öğren. Sakın ona ya da gemisine saldırma, çünkü bunu yaparsan şu anda hazırladığım bir planı mahvedersin! Seni uyarıyorum! Takip et ve gözle, yeterince bilgi edindiğinde bana geri dön. O alçağın gırtlağını sıkmak için ellerinin kaşındığını biliyorum, ama sakin ol. Şimdi git. Üç haftan var. Bol şans.";
			link.l1 = "Yoldayım, patron.";
			link.l1.go = "mtraxx_72";
		break;
		
		case "mtraxx_72":
            DialogExit();
			CloseQuestHeader("Roger_7");
			RemoveItems(pchar, "wolfreeks_book", 1);
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_8", "1");
			pchar.questTemp.Mtraxx = "corrida_start";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1.location = "Martinique";
			pchar.quest.mtraxx_corrida_martinique.function = "Mtraxx_CorridaStart";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1.location = "LaVega_exittown";
			pchar.quest.mtraxx_pasq_continue.function = "Mtraxx_PasqualeJan";
			bDisableFastReload = true;
			//SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
			
		case "mtraxx_73":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 22) // опоздал
			{
				dialog.text = "Lanet olsun, Prens! Eğer bu kadar ağır olmasaydın hem intikamını alır hem de yüklü bir para kazanırdın! Bunu senden beklemezdim ama iyi bir çocuksun, seni affediyorum. Gözümde itibarını geri kazanman için bir ayın var. Herkesi bir baskın için topluyorum!\nBir ay sonra bana tek ama güçlü bir gemiyle gel. Luke, Cutlass, Geffrey ve Jean da katılacak. Sakın geç kalma, bir gün bile olsa!";
				link.l1 = "Anladım, Marcus. Bir daha olmayacak!";
				link.l1.go = "mtraxx_73x";
				break;
			}*/
			dialog.text = "İyi zamanlama! Hemen bana rapor ver.";
			link.l1 = "I've tracked my obligor to Le Francois. His polacre was part of a squadron consisting of a corvette and a frigate. Marco himself paid a visit to Barbaszon; they had a meeting at his place for two hours, and other visitors were sent away by his guards. Then he left the house with two gloomy fellows: one was red-haired and bearded, wearing a reiter cuirass; the other had a moustache and wore heavy trench armour. They all went to the port and sailed away before I reached Saint Pierre.";
			link.l1.go = "mtraxx_74";
		break;
		
		/*case "mtraxx_73x":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "5");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер 
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
		break;*/
		
		case "mtraxx_74":
            dialog.text = "Bu iyi. Şimdi her şeyi daha net görüyorum. Gördüğün o iki herif ya Barbazon ya da Jackman için çalışıyor. Onlar neredeyse benim Kel ve Palalı kadar tehlikeli, ama daha iyi dövüşüyorlar. Kızıl saçlı olanın adı Prowler, 'Cuttlefish' adlı korvetin kaptanı, bıyıklının adı ise Ghoul, 'Merciless' adlı fırkateyni yönetiyor. Bizim dostumuz Ignacio'ya gelince – o sadece İngilizler ve İspanyol don Losad için değil, aynı zamanda Barbazon için de çalışıyor. Bu yüzden seni ve Picard'ı tuzağa düşürmeye kalktı.";
			link.l1 = "Neden?";
			link.l1.go = "mtraxx_75";
		break;
		
		case "mtraxx_75":
            dialog.text = "Barbazon'un emriydi. Sen bilmiyordun, ama Jacques fırsat buldukça çorbama tükürmeden duramaz. Açıkça bana karşı çıkmaya cesaret edemez, sebeplerini tahmin edersin, bu yüzden gizlice arkamdan iş çevirir. Picard'ın ve senin adamlarım olduğunuzu biliyordu. Paralı askerini peşine salmak tam da onun tarzı, üstelik gördüğün gibi, salak birini de göndermemiş.";
			link.l1 = "Marco'yla işimi bitirir bitirmez Barbazon'a uğrayacağım...";
			link.l1.go = "mtraxx_76";
		break;
		
		case "mtraxx_76":
            dialog.text = "Bu saçmalığı kafandan çıkar! Barbazon'a açık çatışmada karşı koyma şansın yok. Seni kolayca mahveder. Ona kendi oyunuyla karşılık vereceğiz - adamlarına saldırarak. Bunu yapmaya hazır mısın? Pis bir iş bu.";
			link.l1 = "Bu tam bana göre bir iş!";
			link.l1.go = "mtraxx_77";
		break;
		
		case "mtraxx_77":
            dialog.text = "Ignacio Marco, Prowler, Goul ve Barbazon'un adamlarından biri olan Joker Jim, Altın Filo'ya ait İspanyol gemilerinden birini ele geçirmek için bir plan yaptı. Tüm operasyonun fikri bizzat Barbazon'a ait ve ben de casuslarımdan detayları öğrenmeyi başardım. Altın Filo'ya ait ağır bir kalyon, filonun geri kalanı İspanya'ya dönerken Havana'daki tersanede kalmış. Kalyon onarıldı ve yakında iki gemiyle birlikte Avrupa'ya doğru yola çıkacak. Filotilla Küba'dan kuzeydoğuya doğru yelken açacak, ama tam rotalarını bilmiyorum.\nAldığım bilgiye göre İspanyol gemileri önce Santo Domingo'ya, ardından Porto Riko kıyılarını takip ederek doğrudan okyanusa açılmayı planlıyor. Barbazon da bunu biliyor. Ancak, Hispaniola sadece güneyden değil, kuzeyden de dolaşılabildiği ve rota değiştirip Santo Domingo'ya uğramadan Turks ya da Isla-Tesoro üzerinden okyanusa çıkılabildiği için, Jacques işi şansa bırakmamak adına kurnaz tilki Ignacio'yu Küba'ya gönderdi.\nMarco'nun görevi, Küba'dan ayrılacak olan İspanyol kalyonunun sefer programını öğrenmek. İspanyollar arasında bağlantıları var, bu yüzden bu iş onun için sorun olmayacaktır. Barbazon'un çetesinin geri kalanı Marco'yu Saint Martin'de bekliyor; bu da bu ganimeti avlamaya başlamak için en uygun yer. Fakat Marco ile Hollandalılar arası iyi olmadığı için Saint Martin sularına giremeyecek, bu yüzden arkadaşlarına uzaktan bir haber göndermek zorunda kalacak...";
			link.l1 = "Sanırım burada ne yapmam gerektiğini biliyorum...";
			link.l1.go = "mtraxx_78";
		break;
		
		case "mtraxx_78":
            dialog.text = "Bana oldukça zeki olduğunu düşündürdün, ama işim bitmedi. Bu planı Gabriela Chapada'nın yardımıyla bozduk. Onu tanıyorsun. Birlikte, İspanyollara korsan pususunun Porto Riko yakınlarında kurulacağını bildirdik. Yani, gemi o bölgeden geçmeyecek, ama gizlice oraya bir korsan avcısı filosu gönderdiler. Birkaç görevin var. İlki, 'Torero'yu bulup ele geçirmek olacak. Kaptanıyla ne yapacağını sanırım biliyorsun.";
			link.l1 = "Doğal olarak...";
			link.l1.go = "mtraxx_79";
		break;
		
		case "mtraxx_79":
            dialog.text = "İkincisi, İspanyol altın gemisinin gerçek rotasını öğrenmen gerekecek. Marco'nun elinde programı olmalı. Onu bul ve bana gönder.";
			link.l1 = "Nasıl?";
			link.l1.go = "mtraxx_80";
		break;
		
		case "mtraxx_80":
			GiveItem2Character(pchar, "Dove"); 
            dialog.text = "Havadan. Bir kafes al... Bu, La Vega'da doğup büyüyen bir posta güvercini, adı Spyke. Onu Trinidad'dan bile bıraksan, buraya geri döner. Programı ele geçirince bir not yaz, bacağına bağla ve sal. Spyke birkaç saat içinde bana ulaşır. Ona iyi bak, Prens!";
			link.l1 = "Tabii ki, patron!";
			link.l1.go = "mtraxx_81";
		break;
		
		case "mtraxx_81":
            dialog.text = "Üçüncüsü, 'Torero' ile Saint Martin'e git. Sadece onunla! Yoksa hemen şüphelenirler. Onlara Porto Riko'ya gitmeleri için işaret gönder, orada İspanyollar bekliyor olacak. Sinyal kodları Marco'nun belgelerinde olmalı. Ya da bizzat ondan öğrenebilirsin.";
			link.l1 = "Anladım. Barbazon'un adamlarını İspanyollara göndermek akıllıca bir hamleydi, ha-ha!";
			link.l1.go = "mtraxx_82";
		break;
		
		case "mtraxx_82":
            dialog.text = "Kesinlikle! Ona gölgelerden saldıracağım. Tıpkı onun yaptığı gibi. Ve son bir şey: Onlara işaret verdiğin anda, hemen yelken açıp İspanyol kalyonunu ve eskortunu yakalamaya git. Kaybedecek zamanımız olmayacak.";
			link.l1 = "Bir polakrada mı? Ağır bir kalyona ve iki gemiye karşı, hem de kesinlikle şalopalar değilken? Beni paramparça ederler!";
			link.l1.go = "mtraxx_83";
		break;
		
		case "mtraxx_83":
            dialog.text = "Ağlamayı kes, küçük bir kız gibi! Neden bana Spyke'ı göndereceğini sanıyorsun? Takviyesiz kalmayacaksın. Yeter ki kervanın kaçmasına izin verme, okyanusa ulaşmalarına engel ol. Anladın mı?";
			link.l1 = "Evet, patron.";
			link.l1.go = "mtraxx_84";
		break;
		
		case "mtraxx_84":
            dialog.text = "Ödülün, yüklü bir altın ve Marco'nun polacrası olacak. Duyduğuma göre lanet iyi bir gemiymiş. Sorun var mı? Görevini anladın mı?";
			link.l1 = "Ben Cutlass değilim, ne yapmam gerektiğini biliyorum. 'Torero'yu nerede yakalamalıyım?";
			link.l1.go = "mtraxx_85";
		break;
		
		case "mtraxx_85":
            dialog.text = "Biz burada sohbet ederken, gemi hızla Küba'dan Philipsburg'a doğru yol alıyor. Şimdi Tortuga'ya yakın olmalı, ya da biraz doğusunda. O yüzden demiri alın ve Saint Martin'e doğru yelken açın, 'Torero'yu adadan çok uzaklaşmadan yakalayın, ama sakın Barbazon'un adamları dövüşü görmesin, yoksa bütün planım mahvolur.";
			link.l1 = "Hemen!";
			// belamour legendary edition испанский флаг к выдаче -->
			if(IsCharacterPerkOn(pchar,"FlagSpa")) link.l1.go = "mtraxx_86";
			else link.l1.go = "mtraxx_85f";
		break;
		
		case "mtraxx_85f":
			STH_SetJokerFlag(SPAIN, true);
			log_info("You have received a spanish flag");
			pchar.questTemp.GiveMeSpaFlag = true;
            dialog.text = "Ne oluyor lan? Şömine maşasıyla döverim seni, Prens. Böyle basit şeyleri açıklamak zorunda kalacağımı düşünmemiştim. İspanyol bayrağını sıkı tut, yoksa her şeyi başlamadan berbat edersin. Onu bana geri ver. Şimdi defol buradan!";
			link.l1 = "Zaten denizdeyim, Patron";
			link.l1.go = "mtraxx_86";
		break;
		// <-- legendary edition
		case "mtraxx_86":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			AddQuestRecord("Roger_8", "6");
			pchar.questTemp.Mtraxx = "corrida_marko";
			/*pchar.quest.mtraxx_corrida_landtimer.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.function = "Mtraxx_CorridaLandTimer";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_corrida_checktime.function = "Mtraxx_CorridaCheckTime";*/
			pchar.quest.mtraxx_corrida_torero.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.hour  = sti(GetTime()+12);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.function = "Mtraxx_CorridaToreroOnMap";
			SetFunctionTimerCondition("Mtraxx_CorridaTimeFindTorero", 0, 0, 7, false); // время на перехват Тореро, снимать при потоплении или захвате
		break;
		
		case "mtraxx_87":
            dialog.text = "Demek prens, her şeyi berbat ediyorsun, ha?";
			link.l1 = "Yaptım. Bu görev beklediğimden çok daha zorlu çıktı. Bana öfkeli bir nutuk çekip kapıyı gösterebilirsin.";
			link.l1.go = "mtraxx_88";
		break;
		
		case "mtraxx_88": // belamour legendary edition увеличиваем срок
            dialog.text = "Hadi, bırak artık. Olur böyle şeyler. Sen iyi bir korsansın, bazen hepimiz kaybederiz. O altını alamadık, yazık oldu... ama bir yerde alamadıysak, başka yerde alırız, ha-ha! İtibarını geri kazanmak için bir şansın olacak: üç hafta sonra bana gel, tercihen daha güçlü bir gemiyle, ama sadece bir tane - koca bir filo olacağız. Herkesi baskına topluyorum!\nÜç hafta sonra bana tek ama güçlü bir gemiyle gel. Luke, Cutlass, Geffrey ve Jean da katılacak. Sakın geç kalma!";
			link.l1 = "Yapmam, patron!";
			link.l1.go = "mtraxx_89";
		break;
		
		case "mtraxx_89":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				STH_SetJokerFlag(SPAIN, false); 
				log_info("You have given a spanish flag");
			}
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "22");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер 
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			//SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
			if (CheckCharacterItem(pchar, "Dove")) RemoveItems(pchar, "Dove", 1);
		break;
		
		case "mtraxx_board":
            dialog.text = "Ho-ho, selam çocuk! Beni burada göreceğini beklemiyordun, değil mi? Ha-ha-ha! Sonunda İspanyol kervanını bulduk...";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Gold")) // был абордаж
			{
				link.l1 = "Evet patron, bulduk, ama kolay olmadı.";
				link.l1.go = "mtraxx_board_1";
			}
			else
			{
				link.l1 = "Evet, ama Altın Galyon tüm altınlarıyla birlikte battı.";
				link.l1.go = "mtraxx_board_7";
			}
		break;
		
		case "mtraxx_board_1":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_GOLD);
            dialog.text = "Ne kadar altın aldık, Prens?";
			if (iTotalTemp < 1) link.l1 = "Eh... Hiçbir şey.";
			else link.l1 = "Heh... "+iTotalTemp+" toplamda!";
			link.l1.go = "mtraxx_board_2";
		break;
		
		case "mtraxx_board_2":
			if (iTotalTemp < 20)
			{
				dialog.text = "Kahretsin! İspanyollar onu denize atmış olmalı ki elimize geçmesin. En azından bedelini ödediler. Barbazon'un adamları da öyle, bu da bir zafer sayılır...";
				link.l1 = "Altın için üzgünüm... Şimdi ne olacak, Marcus? La Vega'ya mı gidiyoruz?";
				link.l1.go = "mtraxx_board_4";
				AddQuestRecord("Roger_8", "18");
				break;
			}
			if (iTotalTemp >= 20 && iTotalTemp < 300)
			{
				dialog.text = "Acınası. Buraya gelmemin masrafını bile karşılamıyor. İspanyollar bunu denize atmış olmalı ki elimize geçmesin. En azından bedelini ödediler. Barbazon'un adamları da öyle, bu da bir zafer sayılır...";
				link.l1 = "Altın için üzgünüm... Yine de paylaşalım.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				break;
			}
			if (iTotalTemp >= 300 && iTotalTemp < 700)
			{
				dialog.text = "Bu ganimet pek de iyi sayılmaz. Masrafları ancak karşılar. İspanyolların bir kısmını denize attığı kesin, bize kalmasın diye. En azından bunun bedelini ödediler. Barbazon'un adamları da öyle, bu da bir zafer sayılır...";
				link.l1 = "Altın için üzgünüm... Yine de paylaşalım.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
				break;
			}
			if (iTotalTemp >= 700 && iTotalTemp < 1000)
			{
				dialog.text = "Fena değil, ama daha iyisini beklerdim. İspanyolların bir kısmını denize attığına bahse girerim, elimize geçmesin diye. En azından bedelini ödediler. Barbazon'un adamları da öyle, bu da bir zafer sayılır...";
				link.l1 = "Hadi ganimeti paylaşalım!";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "20");
				AddCharacterExpToSkill(pchar, "Fortune", 200);
				break;
			}
			dialog.text = "Harika! Güzel bir ganimet kaptık, dostum! Barbazon'un adamları da hak ettiklerini buldu, ha-ha!";
			link.l1 = "Heh, bu bayağı altın! Hadi paylaşalım!";
			link.l1.go = "mtraxx_board_3";
			AddQuestRecord("Roger_8", "21");
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mtraxx_board_3":
			RemoveCharacterGoods(pchar, GOOD_GOLD, makeint(iTotalTemp/2));
			WaitDate("", 0, 0, 0, 3, 10);
			LAi_Fade("", "");
            dialog.text = "... her zamanki gibi Kardeşlik'te - herkes hakkını alır. 'Torero'yu elinde tutabilirsin, o senin ganimetin.";
			link.l1 = "Sırada ne var, Marcus? La Vega'ya mı gidiyoruz?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_board_4": // belamour legendary edition увеличиваем срок до 3х месяцев
            dialog.text = "La Vega'da kesinlikle olacağım, seni orada üç hafta boyunca bekleyeceğim. Hazır olduğunda gel. Tercihen daha sağlam bir gemiyle, ama sadece bir gemiyle gel - bir filo olacağız. Bütün adamlarımı sefere çıkarıyorum. Sen de benim komutam altında olacaksın, Jean Handsome, Kel Geoffrey, Cleaver Pelly ve Luke Leprechaun da bizimle. Hazırlan. Ciddi bir sefer ve oldukça büyük bir ganimet bekliyoruz. Tüm ayrıntıları sonra öğreneceksin.";
			link.l1 = "Pekala, patron! Üç hafta sonra La Vega’da görüşürüz.";
			link.l1.go = "mtraxx_board_5";
		break;
		
		case "mtraxx_board_5":
            dialog.text = "Elveda, katil! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "mtraxx_board_6";
		break;
		
		case "mtraxx_board_6":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Ship_SetTaskRunAway(SECONDARY_TASK, sti(npchar.index), sti(pchar.index));
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_corrida_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_corrida_complete.function = "Mtraxx_CorridaComplete";
			RemoveItems(pchar, "wolfreeks_book", 1);
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				STH_SetJokerFlag(SPAIN, false); 
				log_info("You have given spanish flag");
			}
		break;
		
		case "mtraxx_board_6x":
            dialog.text = "Başka bir şey?";
			link.l1 = "Hayır, sanmıyorum. Zaten gemime gidiyorum.";
			link.l1.go = "mtraxx_board_6y";
		break;
		
		case "mtraxx_board_6y":
            DialogExit();
			npchar.DeckDialogNode = "mtraxx_board_6x";
		break;
		
		case "mtraxx_board_7":
            dialog.text = "Heh! Bunun suçu kimde, Prens? Senin mi?";
			link.l1 = "Üzgünüm patron, ama ikimiz de yeterince iyiydik... Sen de harika nişan aldın. Bu arada, nişanın gerçekten iyiydi...";
			link.l1.go = "mtraxx_board_8";
		break;
		
		case "mtraxx_board_8":
            dialog.text = "Her neyse. Suç ikimizin de. Ama elimiz boş değil - Barbazon'un adamları onlara ne getirdiysek aldı, bu da başlı başına bir zafer...";
			link.l1 = "Altın için üzgünüm... Sırada ne var, Marcus? La Vega'ya mı gidiyoruz?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_90x":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_90";
		break;
		
		case "mtraxx_90":
			pchar.quest.Mtraxx_CartahenaLate.over = "yes";
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Prens, aklını mı kaçırdın? Sana sadece bir gemi getirmeni söyledim! Fazla olanı hemen elden çıkar ve bir an önce geri dön! Şimdi!";
				link.l1 = "Pekâlâ, pekâlâ!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (RealShips[sti(pchar.Ship.Type)].Type.Merchant) // торговые
			{
				dialog.text = "Prens, ikinci Kılıcım olmaya karar verdin mi? Neden bana bir ticaret gemisi getirdin? Sana güveniyordum! Git ve bana düzgün bir savaş gemisi getir! Hadi!";
				link.l1 = "Pekala, pekala!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) > 3)
			{
				dialog.text = "Prens, beni şaşırttın. Sana savaş gemisiyle gelmeni söyledim! Bu tenekeyle bana nasıl yardım edeceksin? Buraya üçüncü ya da ikinci sınıf bir gemiyle dön, ne daha aşağısı ne de daha yukarısı! Hadi! Kimseyi bekleyecek değilim.";
				link.l1 = "Pekala, pekala!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "Prens, neden Sovereign of the Seas'i buraya getirmiyorsun? Sana savaş gemisi getir dedim ama kastettiğim lanet olası bir hat gemisi değildi! Buraya üçüncü ya da ikinci sınıf bir gemiyle dön! Hemen! Kimseyi bekleyecek değilim.";
				link.l1 = "Pekala, pekala!";
				link.l1.go = "mtraxx_90x";
				break;
			}
            dialog.text = "İyi zamanlama, korsan! Seni sağ salim görmek güzel! Bir sefere hazır mısın?";
			link.l1 = "Tabii ki, şef. Her zaman hazırım.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon")) link.l1.go = "mtraxx_91";
			else link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_91":
            dialog.text = "Bu arada, Porto Riko'ya gönderdiğin Barbazon'un filosu hakkında bir şeyler duymak ister misin?";
			link.l1 = "Tamamen aklımdan çıkmış. Tabii ki bilmek isterim. Sonları ne oldu?";
			link.l1.go = "mtraxx_92";
		break;
		
		case "mtraxx_92":
            dialog.text = "Kesinlikle yaptılar! Amiral gemisi – Joker Jim’in firkateyni ‘Baykuş’ – su hattına kadar yandı. Joker Jim’in kendisinden ise tek bir iz bile yok. Tramp ve Ghoul fena dayak yedi, ama kaçmayı başardılar: Tramp, La Rocha’nın toplarının koruması altında Tortuga’ya, Ghoul ise Isla Tesoro’ya sığındı. Pasquale bana, Ghoul’un gemisini Sharptown yakınlarındaki resiflere oturttuğunu ve zar zor kurtardığını söyledi. Usta Alexus’un şimdi başı bayağı dertte, hehe. Sonuç olarak, İspanyollar beni biraz hayal kırıklığına uğrattı. Herkesi öldürürler sanmıştım.";
			link.l1 = "Heh. Ne olursa olsun, Barbazon'un çizmelerine işedik. Ona bir mesaj gönderdik.";
			link.l1.go = "mtraxx_93";
		break;
		
		case "mtraxx_93":
            dialog.text = "Doğru. Şimdi iş konuşalım.";
			link.l1 = "Dinliyorum.";
			link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_94":
            dialog.text = "İstihbarat servisimin, yani iyi dostum Bernard Vensan’ın verdiği bilgiye göre, İspanyollar Cartagena’da devasa bir külçe altın yığını saklıyor. Daha da doğrusu, kalenin altında. Normalde bu hazine İspanya’nın Altın Filosu’na ait olurdu, ama bu kez onu biz alacağız. Cartagena’yı basmak için İspanyol Ana Karası’na gidiyoruz.";
			link.l1 = "Ne dedin sen? Koca bir koloniyi, hem de lanet olası bir kale ile birlikte mi yağmalayacağız?";
			link.l1.go = "mtraxx_95";
			// belamour legendary edition отказ от великого похода
			link.l2 = "Seninle Cartagena'ya gelmeyeceğim, Marcus. Bütün bir şehri yakmak bana göre değil.";
			link.l2.go = "mtraxx_94a";
		break;
		
		case "mtraxx_95":
            dialog.text = "You heard right. That's exactly what we're going to do. My warship will deal with the fort, with your help of course. Bold Jeffrey will be carrying ground troops on his new East Indiaman, stolen from the Dutch. Pelly has finally got rid of his battered brigantine and acquired a decent corvette, not without my financial aid, of course. Paul Chant and you are responsible for taking out the patrol fleet; your crews will also take part in the assault, and you, Charles, such a fine fighter and captain, will help me destroy the fort. Jean Picard didn't show up, which is strange since his corvette has been seen in Port Royal. Well, if he isn't interested in Spanish gold, that's his problem, so to hell with him. Instead of him, my friend Bernard Vensan will join the raid. Plus, Leprechaun and his buccaneers will assist our troops. We will take the gold from the fort and ransom from the city. They won't forget it, ha-ha!  Now, go rest. And come join me and the other captains in the tavern this evening! We should drink to our cause! I'll order the bartender to drive out all the local drunks, so only the six of us and some charming girls will be in the tavern. You're drinking with your comrades tonight, and tomorrow morning you'll lead the squadron, you'll set the course. And try to bring us to Cartagena as soon as possible. All clear?";
			link.l1 = "Peki, peki, reis!";
			link.l1.go = "mtraxx_96";
		break;
		
		case "mtraxx_96":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			chrDisableReloadToLocation = true;
			CloseQuestHeader("Roger_8");
			pchar.questTemp.Mtraxx = "cartahena";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LaVega_townhall", "goto", "goto3");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaReloadInTavern", 10.0);
			pchar.worldmapencountersoff = "1"; // уберем враждебные энкаунтеры
		break;
		// belamour legendary edition -->
		case "mtraxx_94a":
            dialog.text = "Sen... sen... Deli Prens! Beni oyuna mı getiriyorsun?! Biliyor musun, cehenneme git! Kardeşliğe katılma şansın vardı, bu işe yaramaz sürünün arasından sıyrılma fırsatın vardı. Ama sen korkakça o şansı kaçırdın. Defol git, mızmızlanmayı bırak! Zayıf herif! Seni bir daha görürsem köpekleri üstüne salarım!";
			link.l1 = "...";
			link.l1.go = "mtraxx_95a";
		break;
		
		case "mtraxx_95a":
            DialogExit();
			QuestSetCurrentNode("Terrax", "First time");
			CloseQuestHeader("Roger_8");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Corrida");
			DeleteAttribute(pchar, "questTemp.Mtraxx.InTavern");
			LocatorReloadEnterDisable("LaVega_town", "reload6", true); // закрыть на месяц
			SetFunctionTimerCondition("Mtraxx_CartahenaLateOpen", 0, 0, 30, false);
			Mtraxx_TerraxReset(8);
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // выставим за дверь
		break;
		// <-- legendary edition
		case "mtraxx_97":
            dialog.text = "Prens, sonunda geldin! Bakın çocuklar - ona bir hediye hazırladık, o ise kim bilir nerelerde dolaşıyor! Otur bakalım, başlıyoruz!\nCesur korsanlar! Cartagena'nın altını bizi bekliyor, ha-ha! Ve onu alacağız, gök gürültüsüne yemin ederim! Ama çok çalışanlar iyi de dinlenmeli! Bu gece işte bu yüzden bu güzel mekânda keyfimize bakacağız. Kendinize bolca rom koyun, ne kadar çok o kadar iyi! Kupalarınızı ağzına kadar doldurun! Hazine rüzgârlarına, talih rüzgârlarına! Son damlasına kadar içiyoruz!\nSenin için, meyhanemizin mahzenlerinden en güzel içki ve adanın en güzel kadınları, ha-ha-ha!\nVe sana, Charles, bizden — harika bir şapka. Tak bakalım, itiraz etme!\nKorsanlar, şarkımızı söyleyin! En sevdiğimizi!..";
			link.l1 = "";
			link.l1.go = "mtraxx_98";
		break;
		
		case "mtraxx_98":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			LAi_SetSitType(npchar);
			GiveItem2Character(PChar, "hat8");
			EquipCharacterByItem(PChar, "hat8");
			DoQuestCheckDelay("Mtraxx_CartahenaTavernSong", 1.0);
		break;
		
		case "mtraxx_99":
            dialog.text = "Kim olduğumuzu gösterme zamanı, korsanlar. Leprechaun! Adamlarını al ve şehir kapılarını ele geçir. Kaleye takviye göndermelerini istemiyoruz! Biz kalenin askerlerine saldırırken arkalarından sert vurun!";
			link.l1 = "";
			link.l1.go = "mtraxx_100";
		break;
		
		case "mtraxx_100":
            dialog.text = "Prens ve Paul! Üç gemilik askeri filoyu gördünüz, onlardan kurtulun. Kaleden uzak durun ve onların gemilerine çıkmayın. Ne zamanımız ne de fırsatımız var ganimetlerle uğraşmaya. Her şey anlaşıldı mı?! Prens, özellikle sana söylüyorum, kahramanlık merakını biliyorum, ona da sıra gelecek!\nKaleye fazla yaklaşmayın, şu gemileri batırın ve geri dönün! Burada sizi bekliyor olacağız. Her şey anlaşıldı mı? Harika, ha-ha-ha-ha! Hücum!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaSquadronAttack");
		break;
		
		case "mtraxx_101":
            dialog.text = "Demek, İspanyol filosu sonsuza dek gitti. Şimdi 'Kızıl Ejderha'nın sırası geldi. Cartagena kalesini yerle bir edeceğiz. Benimle misin?";
			link.l1 = "Tabii ki!";
			link.l1.go = "mtraxx_102";
		break;
		
		case "mtraxx_102":
            dialog.text = "'Kızıl Ejderha' çok sağlam bir gemi, topları da çok güçlü, seninki onun yanında halt etmiş olur. O yüzden aklını başına al, kahramanlık taslama ve toplarımdan uzak dur!";
			link.l1 = "...";
			link.l1.go = "mtraxx_103";
		break;
		
		case "mtraxx_103":
            DialogExit();
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
	
			Weather.Wind.Angle = 0.0;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
			
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Group_FindOrCreateGroup("Terrax_SeaGroup2");
			Group_DelCharacter("Terrax_SeaGroup", "Jeffry");
			Group_DelCharacter("Terrax_SeaGroup", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Jeffry");
			Group_AddCharacter("Terrax_SeaGroup2", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Pelly");
			Group_SetGroupCommander("Terrax_SeaGroup2", "Jeffry");
			Group_SetTaskNone("Terrax_SeaGroup2");
			Group_LockTask("Terrax_SeaGroup2");
			sld = CharacterFromID("Cartahena Fort Commander");
			LAi_SetImmortal(sld, false);
			Ship_SetTaskAttack(SECONDARY_TASK, sti(npchar.index), sti(sld.index));
			AddQuestRecord("Roger_9", "5");
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx.Cartahena.Fort = "true";
			SetFunctionExitFromLocationCondition("Mtrxtofort", pchar.location, false);
		break;
		
		case "mtraxx_104":
            dialog.text = RandSwear()+"Ne dövüştük ama! İşte bu, cesur korsanlarım! Cartagena artık bizim! Direniş kırıldı! Cesur Leprechaun! Benimle kaleye gel – Bernie altını çoktan bulmuş olmalı. Prens, Cutlass’ı yanına al ve valiye gidip 250.000 peso fidye için pazarlık yap! Paraları var, o yüzden ısrarcı ol. Bunu başarabileceğini biliyorum.";
			link.l1 = "Heh! Zevkle, patron!";
			link.l1.go = "mtraxx_105";
		break;
		
		case "mtraxx_105":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "Cartahena_fort", "goto", "goto10", "", 5.0);
			sld = CharacterFromID("Jeffry");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto11", "", 5.0);
			sld = CharacterFromID("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto12", "", 5.0);
			sld = CharacterFromID("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			AddQuestRecord("Roger_9", "6");
			// запрещаем драки в городе, резиденции, форте
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_fort")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_town")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_townhall")], true);
			LAi_LocationDisableOfficersGen("Cartahena_townhall", true);
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1 = "locator";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.location = "Cartahena_town";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator = "reload3_back";
			pchar.quest.mtraxx_cartahena_townhall.function = "Mtraxx_CartahenaToResidence";
		break;
		
		case "mtraxx_106":
            dialog.text = "Nasıl gidiyor, Prens?";
			link.l1 = "Her şey harika. Cartagena'nın en zenginlerini 350.000 peso ödemeye zorladım.";
			link.l1.go = "mtraxx_107";
		break;
		
		case "mtraxx_107":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "Ho-ho, işte benim adamım! Ama para nerede?";
				link.l1 = RandSwear()+"Hemen getireceğim!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "Ho-ho, işte benim adamım! Sen ve Cutlass, hızınız ve becerikliliğiniz için kişi başı 50.000'i prim olarak alabilirsiniz. Geri kalanını ise sonra aramızda paylaşacağız.";
				link.l1 = "Al bakalım!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_107x":
           DialogExit();
		   npchar.dialog.currentnode = "mtraxx_108";
		break;
		
		case "mtraxx_108":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "Ee? O zaman oyalanmayı bırak da paraları buraya getir!";
				link.l1 = "Geliyorum!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "Harika! Sen ve Cutlass hızınız ve becerikliliğiniz için 50.000'er altın bonus alacaksınız. Geri kalanını ise sonra aramızda paylaşacağız.";
				link.l1 = "Al bakalım!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_109":
			AddMoneyToCharacter(pchar, -300000);
            dialog.text = "Altınımız için endişelisin, değil mi? Bulundu – 5.000 birim, şimdiden gemilerimize taşınıyor. Paylaşım yapıldı, adamlar da kabul etti, umarım Cutlass ve sen de itiraz etmezsiniz.";
			link.l1 = "Benim payım ne?";
			link.l1.go = "mtraxx_110";
		break;
		
		case "mtraxx_110":
            dialog.text = "Tüm operasyonu ben planladığım ve 'Kızıl Ejderha' kaleyle uğraşmak gibi en zor işi üstlendiği için, adamlarım ve ben ganimetin yarısını alacağız. Diğer yarısı ise, diğer dört geminin kaptanları arasında, mürettebatlarının büyüklüğüne göre paylaşılacak. Senin ise "+GetCrewQuantity(pchar)+" emrinde adam var, senin payın "+sti(pchar.questTemp.Mtraxx.Cartahena.Gold)+" altın birimi ve "+sti(pchar.questTemp.Mtraxx.Cartahena.Money)+" pesos.";
			link.l1 = "Pekâlâ, madem herkes buna razı, ben de razıyım!";
			link.l1.go = "mtraxx_111";
		break;
		
		case "mtraxx_111":
            dialog.text = "Splendid. Congratulations on this successful voyage, corsairs! Nothing left for us here, time to go home. All of us, myself included, receive a month's vacation. Not you, Prince, though; I have another task for you. You see, Janette, the Madame of Tortuga's brothel, had a complaint about you: she said that Charlie Prince doesn't give much attention or affection to her establishment. Therefore, I command you to sail to Tortuga, go to Janette's, and spend your bonuses there. You've earned it. Make the Madame and her girls happy. I don't want to see you before you've had your rest in Tortuga, ha-ha-ha!";
			link.l1 = "Anlaşıldı, patron. Şimdiye kadar aldığım en keyifli görev bu. Halledeceğim!";
			link.l1.go = "mtraxx_112";
		break;
		
		case "mtraxx_112":
            dialog.text = "Elveda, beyler! Gemiye binin ve yelken açın! Hepinizi La Vega'da göreceğim!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaFinal");
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "mtraxx_113":
            dialog.text = "Ne?! Jean şimdi İngilizlerin uşağı olmuş, Bold ve Cutlass ortadan kaybolmuş, Leprechaun ve adamları da yok! Şimdi de sen mi?!";
			link.l1 = "Marcus, kararımı verdim. Ben iyi para kazandım, sen de benim üzerimden epey kazanç sağladın. Ama artık yeter. Gidiyorum.";
			link.l1.go = "mtraxx_114";
		break;
		
		case "mtraxx_114":
            dialog.text = "Sen de Picard gibi, kendi başına daha iyi para kazanabileceğini mi sanıyorsun? Öyle mi? Bensiz idare edebileceğini mi düşünüyorsun? Ha-ha-ha! Defol git buradan, Prens, seni tutacak değilim. Çok yakında, hem de çok yakında, ne kadar yanıldığını göreceksin ve sonra gelip yalvaracaksın beni tekrar al diye. Ve biliyor musun? Almayacağım! Ha-ha! Gözüm görmesin seni!";
			link.l1 = "...";
			link.l1.go = "mtraxx_115";
		break;
		
		case "mtraxx_115":
            DialogExit();
		    npchar.quest.mtraxx_complete = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "Ho-ho! Doğru yere geldin! Söyle bakalım!";
			link.l1 = "Korsanlardan korkmayan bir adam var. Bizi ciddiye almıyor. Ona saygının ne olduğunu öğretmek gerek. Unutma, öldürme sakın.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Hah! Bu da kimmiş, yaşlı Charles'tan başkası değil! Eminim yine bir belaya bulaştın! Anlat bakalım, bu sefer hedef kim ve ona ne öğretmemizi istiyorsun?";
			link.l1 = "Avrupa'dan bir misafir, Fransız Maliye Bakanlığı'ndan bir müfettiş - Baron Noel Forget. Burada bir Fransız Ticaret Şirketi kurmak istiyor, ama yakın bir dostumla birlikte buna karşı çıkıyoruz. Baronu, Levasseur yenildikten sonra Hollandalılar, İngilizler ve özellikle de korsanlar yüzünden burada ticaret yapmanın çok tehlikeli olacağına ikna etmeye çalıştık, ama bizi dinlemedi. Ona korkuyu hissettirmemiz, bunu bizzat yaşatmamız lazım.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_x":
			dialog.text = "Ho-ho! Doğru yere geldin! Söyle bakalım!";
			link.l1 = "Korsanlardan hiç korkmayan bir adam var. Bizi ciddiye almıyor. Ona saygının ne demek olduğunu öğretmek gerek. Unutma, öldürme onu.";
			link.l1.go = "patria_x1";
		break;
		
		case "patria_x1":
			dialog.text = "Hah! Ne oldu da birden korsan tutmaya karar verdin? Neyse, bana ne, paramı verdiğin sürece umurumda değil. Şimdi ayrıntılara geçelim, bu sefer hedef kim ve ona ne öğretmemizi istiyorsun";
			link.l1 = "Avrupa'dan bir misafir, Fransız Maliye Bakanlığı'ndan bir müfettiş - Baron Noel Forget. Burada bir Fransız Ticaret Şirketi kurmak istiyor, ama yakın bir dostumla birlikte buna karşı çıkıyoruz. Baronu, Levasseur yenildikten sonra Hollandalılar, İngilizler ve özellikle de korsanlar yüzünden burada ticaret yapmanın çok tehlikeli olacağına ikna etmeye çalıştık, ama bizi dinlemedi. Ona korku salmamız, bunu kendi teninde hissetmesini sağlamamız gerekiyor.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "Evet, evet... Gerçek bir baron! Gemisine saldırmalı mıyız?";
			link.l1 = "Plan şu: Gemisi yakında Port-au-Prince'den Capsterville'e doğru yola çıkacak. Baronu Saint Kitts yakınlarında yakalayıp rehin almalısın. Gemiyi batırmasan ya da adamlarını öldürmesen iyi olur. Sonuçta Fransızlar bizim dostumuz. Bunun üstesinden gelebilecek misin?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "Pekâlâ, hiçbir şeyin garantisini veremem. Ama deneyeceğim. Hangi gemi bu?";
			link.l1 = "'Favory' adında bir brig.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Bir brig benim 'Kızıl Ejder'imle baş edemez. Onlarla kolayca başa çıkarız. Teslim olurlarsa, herkesi sağ bırakırım.";
			link.l1 = "Mükemmel. Korku sal ve teslim olmaları için bir şans ver. Sonrasında Baronu fare kaynayan ambarlara gönder. Bulabildiğin en pis yeri seç, ama onu orada bir günden fazla tutma, yoksa hastalanıp ölebilir. Sonra onu kamarada barındır, bulabildiğin tenha bir yere kapat ve kilitle. Adamlarından bazılarını yakalanmış Fransız tüccarları gibi giydir ve rol yapmalarını sağla. Üç gün boyunca aralıksız ona acımasız korsanların peşlerine düştüğünü, onları soyduğunu, fidye istediğini, işkence ettiğini... tüm ayrıntılarıyla anlatsınlar.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ha-ha-ha! Bu, uzun zamandır aldığım en komik iş olmalı! Peki, o zaman, sana öyle oyuncular bulacağım ki, delikanlı. Hiç şüphen olmasın, onların hikâyelerinden sonra Baron'unun altına edeceği kesin! Ona pala ve kızgın sürgü izlerini gösterecekler...";
			link.l1 = "Mükemmel! O zaman onu de Poincy'ye fidye talep eden bir mektup yazmaya zorlayacaksın. Böyle büyük bir adam için üç buçuk milyon o kadar da fazla sayılmaz.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "Güzel. Şimdi ne yapacağız?";
			link.l1 = "Sonra Baronu Turks'e getireceksin. Orada fidyeyi alacaksın ve Baronu bana teslim edeceksin. Ayrıca ona söylemelisin ki, Tortuga ve Levasseur'un hesabını tüm Fransızlar verecek, hem de bir kerelik değil.";
			if (CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax")) link.l1.go = "patria_x7";
			else link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "Ha-ha-ha! Bu gerçekten harika bir numara! Biz şahsen, yani, Levasseur’a ne yaptığımızı biliyorsun, şimdi de... ha-ha-ha!.. Peki, delikanlı. Olacak bu iş! Yani diyorsun ki gemi yakında varacak?";
			link.l1 = "Yakında. Gözümüzü dört açmalıyız.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_x7":
			dialog.text = "Ha-ha-ha! Bu tam bir numara! Bu maskaralık için senden ne kadar istemeliyim? Peki, yüz bin işi çözer. Parayı ver.";
			if (sti(pchar.money) >= 100000) 
			{
				link.l1 = "Al bunu.";
				link.l1.go = "patria_x8";
			}
			else
			{
				link.l1 = "Pekala, getireceğim.";
				link.l1.go = "patria_xwait";
			}
		break;
		
		case "patria_xwait":
			DialogExit();
			pchar.questTemp.Patria.Condotier.NeedMoney = "true";
		break;
		
		case "patria_x8":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "Mükemmel! Geminin yakında varacağını mı söyledin?";
			link.l1 = "Yakında. Gözümüzü dört açmamız gerek.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "Merak etme, seni hayal kırıklığına uğratmam. Bu işi bizzat halledeceğim. Baronu yakaladıklarına dair bir söylenti duyarsan, bana gel.";
			link.l1 = "İyi. Teşekkürler, Marcus.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "71");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
			else LocatorReloadEnterDisable("Lavega_town", "reload6", true);
		break;
		
		case "patria_10":
			dialog.text = "Elbette, delikanlı. Anlaştığımız gibi. Acımasız korsanların korkutucu hikâyeleri, masum Fransız tüccarların katledilmesi, kırbaç sesi, inlemeler ve çığlıklar. Kor dolu mangal ve yanık kelepçeler. Tam da olması gerektiği gibi.";
			link.l1 = "Dur, dur! Sakin ol! Onu sağ bırakmam lazım";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Merak etme, yaşayacak. Bu mektubu titrek bir elle yazmış. Al, burada.";
			link.l1 = "Orada ne yazıyor? Poincy'den onu buradan çıkarmasını mı istiyor?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Aynen öyle, evlat! Yalvarıyor, ha!";
			link.l1 = "Bu mektubu at, hatta daha iyisi - yak. Bir hafta sonra Turks'ta buluşacağız. Fidyenin toplanması için zamana ihtiyacımız varmış gibi görünmeli.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "Anladım. Bir hafta sonra, kuzey körfezinde, Turks'te. Parayı almayı unutma: bu iş düzgün görünmeli. Bittikten sonra bana gel, konuşacağız.";
			link.l1 = "Tabii ki, sonra görüşürüz, Marcus!";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "Hey, kurbağa yiyici! Dur!";
			link.l1 = "Kımıldamıyorum.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "Baronun burada. Biraz yıpranmış, heh, ama tek parça halinde. Hâlâ tanınabiliyor mu? Ha-ha-ha!";
			link.l1 = "Evet... biraz.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Mükemmel. Şimdi parayı ver yoksa işini bitiririz! Ve sakın bizi kandırmaya kalkma, seni gözümüzden kaçırmıyoruz!";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "Al, bunu.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "Kahretsin! Onu gemide unuttum...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "Ha-ha-ha! Akıllı bir çocuksun, fransız. Al şu 'yüceliğini'. Ve Poincy'ye söyle, parayı hazırlasın: Levasseur ve Tortuga'ya yaptıklarının bedelini ödeyeceksin. Tüccarların da malları ve gemileriyle bize ödeyecek. Ha-ha-ha! Takımadalara bize daha fazla baron getirmeyi unutma, onlar bize bolca kazanç sağlıyor! Ha-ha-ha!";
			link.l1 = "Lütfen, tekneme git Baron.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "Ve sakın peşimize düşmeyi aklından bile geçirme, kaptan. Kim olduğumu biliyorsun. Daha fazla Fransız esirim var ve eğer zamanında eve dönmezsem, hepsi idam edilecek. Anladın mı?";
			link.l1 = "Zamanı gelecek, sizinle hesaplaşacağız, lanetli kafirler!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Ha-ha-ha-ha! Tabii ki yapacaksın!";
			link.l1 = "...";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax"))
			{
				LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
				Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			}
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "Benimle dalga mı geçiyorsun?! Bu bir oyun mu yoksa?!";
			link.l1 = "Bir dakika, hemen getiriyorum...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "Ah Marcus, senin aptalın ne halt etti!";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) link.l1.go = "patria_25";
			else link.l1.go = "patria_x25";
		break;
		
		case "patria_25":
			dialog.text = "Charles, ne yapıyordun? Para nerede? Adamlarıma bunun gerçek olmadığını söylemedim... ve bu aptal da bizi kandırmak istediğini sandı...";
			link.l1 = "Felaket! Baron öldü... Şimdi de Poincy ne yapacak?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_x25":
			dialog.text = "Charles, ne yapıyordun? Para nerede? Adamlarıma bunun gerçek olmadığını söylemedim... ve bu salak da onları kandırmaya çalıştığını sandı...";
			link.l1 = "Felaket! Baron öldü... Şimdi de Poincy ne yapacak?";
			link.l1.go = "patria_x26";
		break;
		
		case "patria_x26":
			dialog.text = "Pekâlâ evlat, bu senin hatan, umarım bunu anlıyorsundur. Belki de en iyisi budur, ölü bir adam kimseye zarar veremez.";
			link.l1 = "Ne aptalım ben! Her şeyi berbat ettim. Peki, Poincy'ye gideceğim... Böyle bir aptal olduğum için beni affet, Marcus, görüşürüz.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_26":
			dialog.text = "Pekâlâ evlat, bu senin suçun, umarım bunu anlıyorsun. Belki de böylesi en iyisidir.";
			link.l1 = "Ne aptalım ben! Her şeyi berbat ettim. Peki, Poincy'ye gideceğim... Böyle bir aptallık yaptığım için affet beni Marcus, görüşürüz.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Dinlenmeye ihtiyacın var, eski formunda değilsin. Bir ara yanıma gel, sana biraz rom ve güzel kadınlar ayarlarım.";
			link.l1 = "Teşekkür ederim, fırsat bulduğumda sana uğrayacağım.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "Bir şey değil, evlat. Bu yıl en çok eğlendiğim an buydu! Ben ve adamlarım öyle çok güldük ki! Bunun için sana teşekkür etmek isterim. Al, paran burada.";
			link.l1 = "Bunun bir kısmını gösterdiğin başarı için kendine ayırmalısın.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_x29":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Al paranı al, 'entrikacı'. Ha-ha! Bu eğlenceliydi.";
			link.l1 = "Yardımın için teşekkürler, Marcus. İyi şanslar!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Boşver. Bunu dostluğumuz için yaptım. Kıyı Kardeşliği sana çok daha fazlasını borçlu, ama sen tek bir dublon bile istemedin.";
			link.l1 = "Yine de, hizmetlerin ve emeğinin karşılığı olarak en az elli bin al. Teşekkürler, Marcus!";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "Rica ederim. Charles, ne zaman vaktin olursa bana uğra!";
			link.l1 = "Memnuniyetle!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "Bir hafta geciktin! Adamlarıma bunun gerçek olmadığını söylemedim... Daha fazla beklemeyi reddettiler ve senin Baronunu öldürmeye karar verdiler!";
			link.l1 = "Ne aptalım ben! Her şeyi berbat ettim! Poincy'ye ne diyeceğim şimdi?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_x33":
			dialog.text = "Bir hafta geciktin! Adamlarıma bunun gerçek olmadığını söylemedim... Daha fazla beklemeyi reddettiler ve senin Baronunu öldürmeye karar verdiler!";
			link.l1 = "Ne aptalım ben! Her şeyi berbat ettim! Poincy'ye ne diyeceğim şimdi?";
			link.l1.go = "patria_x34";
		break;
		
		case "patria_34":
			dialog.text = "Pekâlâ, delikanlı, bunun senin hatan olduğunu umarım anlıyorsundur. Belki de senin için daha iyi olur.";
			link.l1 = "Pekâlâ, Poincy'ye gideceğim... Aptallığım için beni affet, Marcus, görüşürüz...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_x34":
			dialog.text = "Bu belaya kendi başını soktun, bu tamamen senin suçun.";
			link.l1 = "Sanırım sonra görüşürüz...";
			link.l1.go = "patria_36";
		break;
		
		case "patria_35":
			dialog.text = "Dinlenmen lazım, eski formunda değilsin. Bir ara yanıma uğra, sana biraz rom ve güzel kadınlar ayarlayayım.";
			link.l1 = "Teşekkürler, fırsat bulduğumda uğrarım.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ_1":
			DelLandQuestMark(npchar);
			
			if (pchar.questTemp.Mtraxx == "full_complete")
			{
				dialog.text = "Uzun zaman oldu, Prens.";
				link.l1 = "Bu ismin bana şans getirdiğinden hiç emin değilim, Marcus.";
				link.l1.go = "PZ_Prince1";
			}
			else
			{
				dialog.text = "De Maure! Seni buraya ne getirdi?";
				link.l1 = "Ah, Marcus. Sana bir şey sormak istiyordum.";
				link.l1.go = "PZ_DeMaure1";
			}
		break;
		
		case "PZ_Prince1":
			dialog.text = "Tam tersi olduğunu görüyorum. Seni buraya ne getirdi?";
			link.l1 = "Tortuga'daki yeni genelevi duydun mu?";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_DeMaure1":
			dialog.text = "O halde, sor. Resmiyetle aram yok, lafı dolandırmadan söyle.";
			link.l1 = "Tortuga'daki yeni genelevi duydun mu?";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "Sarhoş musun? Ne biçim soru bu? Eğer gerçekten konuşmak istediğin buysa, vaktimi harcama.";
			link.l1 = "Sanırım duymadın? Orada yakın zamanda yeni bir genelev açıldı—hem de çok pahalı bir yer, sadece en güzel, sağlıklı ve bakımlı kızların çalıştığı bir yer.";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "Ah, o mu! Tabii ki duydum – kim duymamış ki?";
			link.l1 = "Ben de bunu daha yeni öğrendim.";
			link.l1.go = "PZ_4";
		break;
		
		case "PZ_4":
			dialog.text = "Ha-ha-ha-ha, seni alçak, kahretsin! Ama yine de, neden bunu benimle konuşuyorsun? Neden önce Hawks'ı denemiyorsun? Heh heh. Gerçi... orada zaten biraz eğlendin mi?";
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				link.l1 = "Var. Bu arada, sadece doblon kabul ediyorlar.";
				link.l1.go = "PZ_Fucked1";
			}
			else
			{
				link.l1 = "Oraya gittim, ama hizmetlerden faydalanmadım. Fakat...";
				link.l1.go = "PZ_NoFucked1";
			}
		break;
		
		case "PZ_Fucked1":
			dialog.text = "Demek gösteriş yapmaya geldin! Ha, ne düzenbazsın.";
			link.l1 = "Aslında, hayır. Gerçekten sana bir şey sormak istiyordum, Marcus.";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_NoFucked1":
			dialog.text = "Bunu yapmadın mı?! Aptalsın, De Maure. Senin yerinde olsam...";
			link.l1 = "Biliyorum, tam bir sefahat başlatırdın. Ama seninle konuşmak istediğim konu tam olarak bu değil.";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_5":
			dialog.text = "Ne var? Hadi, beni merakta bırakma.";
			link.l1 = "O yerin sahibini arıyorum. Bana, seninle tanışmak ve ticaretine yatırım fırsatı sunmak istediği söylendi. Onu karıştırmazsın - Çinli.";
			link.l1.go = "PZ_6";
		break;
		
		case "PZ_6":
			dialog.text = "Ho ho. Hayır, son zamanlarda Çinli bir kadınla tanışma şerefine nail olmadım. Ama onunla tanışıp işine yatırım yapmaya da hayır demezdim. Sonuçta, Levasseur'un bölgesine öylece elini kolunu sallayarak giremezsin, ve senin kralının tebaası olarak, o da benim 'Ejderha'mı görür görmez kıyı gemilerini ateşe vermek zorunda kalırdı.";
			link.l1 = "Önce Port-au-Prince'i düşünüyor gibi görünüyor...";
			link.l1.go = "PZ_7";
		break;
		
		case "PZ_7":
			dialog.text = "Öyle mi düşünüyorsun? Bu bir hata. De Mussac'ın benden daha fazla parası olsa bile, ki sanmıyorum, şehrin bütçesinden bir geneleve tek kuruş ayıramaz, ne kadar altın getirirse getirsin.";
			link.l1 = "İyi bir nokta. Belli ki bu hırsını hiç düşünmemiş.";
			link.l1.go = "PZ_8";
		break;
		
		case "PZ_8":
			dialog.text = "Bilirsin, diğer genelevlerin nasıl ayakta kaldığını hep merak etmişimdir. Bir kadının düşünme yeteneğiyle ya da hele ki hükmetmesiyle alakası yok bu işin - aklında bulunsun.";
			link.l1 = "Bu konuda yanılıyorsun. Zamanın için sağ ol, Marcus! Eğer önce ben karşılaşırsam, seni görmekten memnun olacağını ona söylerim.";
			link.l1.go = "Exit";
			
			AddQuestRecord("PZ", "32");
			
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1 = "location";
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PZ_SetHeavyFrigate.win_condition = "PZ_SetHeavyFrigate";
			DelMapQuestMarkCity("LaVega");
			AddMapQuestMarkCity("PortPax", false);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", true);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
		break;
	}
}