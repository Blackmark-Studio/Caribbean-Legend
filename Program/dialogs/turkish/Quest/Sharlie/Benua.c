int iBenuaPseudoGlobal;

// аббат Бенуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
    bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan.Late")) // Addon 2016-1 Jason пиратская линейка 1
			{
				dialog.text = "Seni görmek güzel, oğlum.  Borcunu ödemeye mi geldin?";
				if (PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
				{
					link.l1 = "Evet, baba. Benim.";
					link.l1.go = "FastStart_7";
				}
				else
				{
					link.l1 = "Geciktiğim için üzgünüm, ama bunun için burada değilim. Ama yakında olacağım, merak etme.";
					link.l1.go = "exit";
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "benua_final")
			{
				dialog.text = "Bir şeye ihtiyacın var mı, oğlum?";
				link.l1 = "Evet, baba. Kardeşim Michel de Montper'i görmek istiyorum. O şöyle demişti...";
				link.l1.go = "escape";
				break;
			}
			dialog.text = "Bir şeye mi ihtiyacın var, oğlum?";
			//--> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua"))
			{
				dialog.text = "Merhaba, evladım. Geldiğine sevindim. Seninle konuşmak istiyordum.";
				link.l1 = ""+TimeGreeting()+", Peder. Sizi dinliyorum.";
				link.l1.go = "SharlieEpilog_Benua_1";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua_back"))
			{
				link.l99 = "Babam hakkında konuşmak istiyorum.";
				link.l99.go = "SharlieEpilog_Benua_3";
			}
			//<-- Эпилог
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "Evet, Baba. Yardımına ihtiyacım var. Benim adım "+GetFullName(pchar)+" . Michel de Montper bana sizinle konuşmamı tavsiye etti.";
				link.l1.go = "FastStart";
			}
			if (CheckAttribute(npchar, "quest.help") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "Evet, baba. Yardımına ihtiyacım var. Benim adım "+GetFullName(pchar)+". Kardeşim Michel de Monper bana sizinle konuşmamı tavsiye etti.";
				link.l1.go = "meet";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Evet, baba. Michel'e yardım etmek için bir gemiye ihtiyacım var, ama Karayipler'e daha yeni geldim ve cebim bomboş. Ağabeyim bana biraz borç verebileceğini söyledi...";
				link.l1.go = "FastStart_2";
			}
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua"))
			{
				link.l1 = "Selamlar, Baba. Sana ihtiyacımız var – hem de oldukça sıra dışı bir konuda.";
				link.l1.go = "WildRose_Abb_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2") && PCharDublonsTotal() >= 800)
			{
				link.l3 = "Baba, gereken parayı topladım. Sekiz yüz altın.";
				link.l3.go = "WildRose_Abb_14_pay";
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3"))
			{
				dialog.text = "Selam, oğlum. Sanırım... öhöm, meselelerinin sonucunu öğrenmeye geldin?";
				link.l1 = "Her zamanki gibi keskin gözlüsün, baba. Beni bekletme – söyle bakalım, adamın ne bulmuş?";
				link.l1.go = "WildRose_Abb_16";
				break;
			}
			//<-- Дикая Роза
			if (CheckAttribute(npchar, "quest.help") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Evet, baba. Yardımına ihtiyacım var.";
				if (CheckAttribute(npchar, "quest.relation_info")) link.l1.go = "help";
				else link.l1.go = "help_start";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan") && PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
			{
				link.l2 = "Evet, baba. Benim.";
				link.l2.go = "FastStart_7";
			}
			link.l9 = "Hayır, hiçbir şey, baba.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Benua_meeting":
			DelLandQuestMark(npchar);
			if(CheckAttribute(pchar, "questTemp.Sharlie.Citcount"))
				DeleteAttribute(pchar, "questTemp.Sharlie.Citcount");
			DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			dialog.text = "Seni buraya ne getirdi, oğlum?";
			link.l1 = "Merhaba, Baba. Sizinle konuşmam söylendi. Benim adım Charles de Maure. Michel de Monper'i arıyorum. Bildiğim kadarıyla, o şu anda Martinique'te bir yerde olmalı. Ben... onun kardeşiyim.";
			link.l1.go = "Benua_meeting_1";			
		break;
		
		case "Benua_meeting_1":
			dialog.text = "Michel de Monper'in kardeşi mi? De Maure? Ne garip...";
			link.l1 = "Şüphelerinizi anlıyorum, baba. Sadece soyadlarımız farklı. Benim babam Henri de Montper.";
			link.l1.go = "Benua_meeting_2";			
		break;
		
		case "Benua_meeting_2":
			dialog.text = "A-ah, şimdi anlıyorum. Henri de Monper’i şahsen tanırdım. Yüzünü ışığa çevir, delikanlı. Evet! Ona tıpatıp benziyorsun. Aynı duruş, aynı soylu yüz hatları! Henri de Monper’in oğlunu cemaatimizde görmekten memnuniyet duydum.\nSoruna gelince, sana şunu söyleyebilirim: Michel Malta Şövalyeleri Tarikatı’nda yüksek rütbeli bir subay, fakat... başı dertte. Neyse ki, Tarikat’ın şövalyelerinden biri şu anda beni ziyarete geldi. Sanırım, seni talihsiz kardeşinin yanına götürmeyi kabul edebilir—Tanrı onun kaderine merhamet etsin...";
			link.l1 = "Bu adam kim, kutsal baba?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;		
			if (GetCharacterIndex("SharlieKnown") != -1)
			{
				sld = characterFromId("SharlieKnown");
				sld.lifeday = 0;
			}			
		break;
		
		case "Benua_meeting_3":
			DialogExit();
			NextDiag.CurrentNode = "Benua_meeting_repeat";
			AddQuestRecord("Sharlie", "4");
			pchar.quest.Sharlie_Benua.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Benua.win_condition.l1.date.hour  = 6;
			pchar.quest.Sharlie_Benua.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Sharlie_Benua.function = "Sharlie_BenuaMaltie";
		break;
		
		case "Benua_meeting_repeat":
			dialog.text = "Oğlum, yarın sabah tekrar gel. Şu anda sana söyleyecek başka bir şeyim yok.";
			link.l1 = "Pekâlâ.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Benua_meeting_repeat";
		break;
		
		/* case "Benua_maltie":
			dialog.text = "Merhaba, oğlum. Söz verdiğim gibi, dün bahsettiğim kişi şimdiden burada ve seni bekliyor. Seni, duyduğuma göre perişan halde olan kardeşinin yanına götürmeye hazır. Tanrı onun ruhuna merhamet etsin...";
			link.l1 = "Bu adam kim, kutsal baba?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;
		break; */
		
		case "escape":
			dialog.text = "Evet, Charles, bunun farkındayım. Ama seni hayal kırıklığına uğratmak zorundayım. Michel burada değil.";
			link.l1 = "Ne demek burada değil? Kilisende beni bekleyeceğini söylemişti! Peder, ne oldu? Kardeşim nerede?!";
			link.l1.go = "escape_1";
		break;
		
		case "escape_1":
			dialog.text = "Oğlum, kardeşin dün gece geç saatlerde benim mütevazı evimden ayrıldı. Nereye gittiğini bilmiyorum. Ama sana bu mektubu bıraktı.";
			link.l1 = "İnanamıyorum... bunca şeyi onun için yaptıktan sonra! O mektubu ver bana!";
			link.l1.go = "escape_2";
		break;
		
		case "escape_2":
			dialog.text = "Bu kadar öfkelenme, Charles. İşte mektup. Oku ve sonra... sonra seninle konuşmak isterim. Ama önce, kardeşinin mesajını oku.";
			link.l1 = "Sabırsızlıktan yanıyorum!";
			link.l1.go = "escape_3";
		break;
		
		case "escape_3":
			DialogExit();
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_mishelle");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Mishelle";
			NextDiag.CurrentNode = "escape_4";
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false); // лесник открыл входы
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", false);
		break;
		
		case "escape_4":
			if (CheckAttribute(pchar, "GenQuest.specialletter.read") && pchar.GenQuest.specialletter.read == "Letter_Mishelle")
			{
				dialog.text = "Mektubu okuduğunu görüyorum. Şimdi sana bir şey söylemek istiyorum, Charles...";
				link.l1 = "Ama... bu nasıl olur? Bu ne saçmalık böyle? Kardeşimin tuhaf biri olduğunu biliyorum ama deli değil ki!";
				link.l1.go = "escape_5";
			}
			else
			{
				dialog.text = "Oğlum, mektubu oku. Sonra konuşuruz.";
				link.l1 = "Evet, baba...";
				link.l1.go = "exit";
				NextDiag.TempNode = "escape_4";
			}
		break;
		
		case "escape_5":
			dialog.text = "Kardeşinin davranışları beni de şaşırttı, Charles. Hâlâ zaman zaman kafam karışıyor. Tarikatın ve Teslis’in sadık bir hizmetkârıydı, ama şimdi bir kaçak gibi davranıyor.";
			link.l1 = "Böylesine tuhaf bir davranışın sebebi ne olabilir, bir fikrin var mı?";
			link.l1.go = "escape_6";
		break;
		
		case "escape_6":
			dialog.text = "Ne yazık ki, bilmiyorum. Ama sanırım onun kendi sebepleri var, hem de derin sebepler. Bir insanın geçmişini tamamen silmesi, çok önemli bir nedeni olduğunu gösterir. Ne olabileceğini hayal bile edemiyorum. Ama bunun çok kötü, hatta korkunç bir şeyle ilgili olduğunu hissediyorum...";
			link.l1 = "Ne olabilir ki, baba?";
			link.l1.go = "escape_7";
		break;
		
		case "escape_7":
			dialog.text = "Oğlum, bir rahip gözleriyle değil, kalbiyle görür. Bunu sana kelimelerle anlatamam ama... kardeşin kirli, uğursuz bir işe kalkıştı. Bunu ağzımdan duyacağımı hiç düşünmezdim. Fakat...";
			link.l1 = "Doğrusu, kardeşimin bir dolap çevirdiğinden hiç şüphem yok. Hatta tam olarak ne yapacağını da tahmin edebiliyorum. Bu 'bir şey' sarı renkte ve hoş bir şıngırtı sesi çıkarıyor.";
			link.l1.go = "escape_8";
		break;
		
		case "escape_8":
			dialog.text = "Bence kardeşini harekete geçiren şey altın hırsı değil. Daha büyük bir şeye ihtiyacı olduğunu düşünüyorum.";
			link.l1 = "Michel'den çok şey öğrendim ve onun felsefesini kavradım, bu yüzden onun için neyin önemli olup olmadığını ayırt edebileceğimi düşünüyorum. Ama değerli sözlerini aklımda tutacağım, baba.";
			link.l1.go = "escape_9";
		break;
		
		case "escape_9":
			dialog.text = "Tanrı seni korusun, oğlum. Git, hadi şimdi. Rab seni gözetsin!";
			link.l1 = "Teşekkür ederim, baba. Hoşça kal!";
			link.l1.go = "escape_10";
		break;
		
		case "escape_10":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddDialogExitQuestFunction("Sharlie_Benua_BrotherEscape");
		break;
		
		// уменьшение награды за голову
		case "meet":
			dialog.text = "Michel de Monper'ın kardeşi mi? De Maure? Ne tuhaf...";
			link.l1 = "Şüphelerini anlıyorum, baba. Sadece soyadlarımız farklı. Benim babam Henri de Montper.";
			link.l1.go = "meet_1";			
		break;
		
		case "meet_1":
			dialog.text = "A-ah, şimdi anladım. Henri de Monper'i şahsen tanırdım. Yüzünü ışığa çevir, genç adam... Evet! Ona tıpatıp benziyorsun. Aynı yüz hatları, aynı soylu duruş! Henri de Monper'in oğlunu cemaatimizde görmekten memnuniyet duydum.\nMichel'in Avrupa'dan gelen biri tarafından ziyaret edildiğini duymuştum ama bunun kendi kardeşi olabileceğini hiç düşünmemiştim. Umarım Michel'e yardımcı olabilirsin, zor bir dönemden geçiyor. Her neyse, sana nasıl yardımcı olabilirim?";
			link.l1 = "Michel bana, eğer bir gün yetkililerle başım belaya girerse, bana yardım edebileceğini söyledi.";
			link.l1.go = "help_info";	
			npchar.quest.meet = true;
		break;
		
		case "help_info":
			dialog.text = "Michel sana bunu mu söyledi? Anladım. Bu tür konularda yardımcı olabilirim. Kutsal Roma Kilisesi ve Hollanda kolonilerinde bir miktar nüfuzum var. Bu nedenle, hem İspanyol hem de Hollanda makamlarıyla aranızda aracılık yapabilirim. Tabii ki, eğer işlediğiniz kusur çok ciddiyse fazla bir şey yapamam – o durumda ancak hafif bir iyileşme sağlanabilir. Tam bir uzlaşma için birkaç kez aracılık etmem gerekecek. Ayrıca, her durumda bana hayır işleri ve yolculuk masrafları için altın doblonlar sağlamanız gerekecek. Bir seferde yalnızca bir ulus için yardımcı olabilirim. Eğer bu şartlar size uygunsa, bana çekinmeden başvurun, neler yapılabileceğine bakarız.";
			link.l1 = "Teşekkür ederim! Bunu aklımda tutacağım.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "help_start":
			dialog.text = "Senin için ne yapabilirim, oğlum? Konuş, seni dinliyorum.";
			link.l1 = "Michel bana, eğer bir gün başım otoritelerle derde girerse, yardım edebileceğini söylemişti.";
			link.l1.go = "help_info";
		break;
		
		case "help":
			dialog.text = "Sana nasıl yardımcı olabilirim, oğlum?";
			//--> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua_DublonsLater"))
			{
				link.l1 = "Volvamos al asunto del pago por la entrega de las órdenes.";
				link.l1.go = "SharlieEpilog_Benua_DublonsLater_2";
			}
			if (CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_2"))
			{
				link.l1 = "Quiero enviar una orden...";
				link.l1.go = "SharlieEpilog_Benua_Delivery";
			}
			//<-- Эпилог
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "İspanyol yetkililerle başım belaya girdi.";
				link.l1.go = "relation_spa";
			}
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "Hollanda makamlarıyla başım belaya girdi.";
				link.l2.go = "relation_hol";
			}
			link.l9 = "Üzgünüm, sanırım bu sefer işleri kendim halledeceğim.";
			link.l9.go = "exit";
		break;
		
		case "relation_spa": // patch-10
			pchar.GenQuest.BenuaNation = SPAIN;
			dialog.text = "Demek, soylu señores seni Havana'nın zindanlarına tıkmaya hevesli...";
			link.l1 = "Aynen öyle, baba...";
			link.l1.go = "relation";
		break;
		
		case "relation_hol":
			pchar.GenQuest.BenuaNation = HOLLAND;
			dialog.text = "Demek ki, kurnaz tüccarlar seni Willemstad zindanlarına atmak için can atıyorlar...";
			link.l1 = "Aynen öyle, baba...";
			link.l1.go = "relation";
		break;
		
		case "relation":
			rate = wdmGetNationThreat(sti(pchar.GenQuest.BenuaNation));
			iBenuaPseudoGlobal = DiplomatDublonPayment(rate, "Benua", false);
			sTemp = FindRussianDublonString(iBenuaPseudoGlobal);
			if (rate < 2)
			{
				dialog.text = "Evet, bu söylentiler bizim kiliseye de ulaştı. Derdine yardımcı olabilirim. Bu çözülebilecek bir mesele. İhtiyacım olan "+sTemp+"   durumunu biraz olsun düzeltmek için. ";
				if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
				{
					link.l1 = "Harika!   Altın burada.";
					link.l1.go = "agree";
				}
				link.l2 = "O halde, altınları bulmak için tam zamanı.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate < 4)
				{
					dialog.text = "Evet, senin 'marifetlerinin' dedikoduları bizim kiliseye de ulaştı. İtibarını zedeledin, evladım. Daha tedbirli olmalısın. Ama sana yardım edebilirim. Benim de ihtiyacım var "+sTemp+" durumunu hafifletmek için. ";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "Harika!   Al altınları.";
						link.l1.go = "agree";
					}
					link.l2 = "O halde, doblonları bulmam için doğru zaman.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Evet, oğlum. Sen de en az kardeşin kadar çaresizsin... Bu muhtemelen aileden gelen bir özellik. Durumu tamamen düzeltemem ama yine de, içinde bulunduğun bu kasvetli hali biraz olsun hafifletebileceğime inanıyorum. Sonrasında istersen daha fazla adak da sunabiliriz. İhtiyacım olan şey "+sTemp+" şimdilik ve hemen sorununu çözmeye başlayacağım.";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "Harika! İşte altın.";
						link.l1.go = "agree";
					}
					link.l2 = "O halde altınları bulmamın tam zamanı.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iBenuaPseudoGlobal); // Sinistra legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Şimdi en az iki hafta beklemen gerekecek. Bu süre içinde doğru insanlarla buluşup konuşabileceğimi düşünüyorum.";
			link.l1 = "Teşekkür ederim, baba! Bekliyor olacağım...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            bOk = HasShipTrait(pchar, "trait23");
            rate = 10 + hrand(5);
            rate = GetIntByCondition(bOk, rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromBenuaComplete", 0, 0, rate, false);
			pchar.GenQuest.BenuaNation.Rate = GetDiplomatRate(bOk, sti(pchar.GenQuest.BenuaNation));
			npchar.quest.relation = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка 1
		case "FastStart":
			dialog.text = "De Maure? Ve sen Michel de Monper’in kardeşi misin? Garip...";
			link.l1 = "Şüphelerinizi anlıyorum, padre. Babam Henri de Montper.";
			link.l1.go = "FastStart_1";			
		break;
		
		case "FastStart_1":
			dialog.text = "A-ah, anlıyorum. Henri de Monper'i şahsen tanırdım. Işığa çık, delikanlı. Evet! Aynı gözler, aynı soylu yüz hatları! Henri de Monper'in oğlunu kilisemizde görmekten memnuniyet duydum. Umarım kardeşine yardımcı olabilirsin. Son zamanlarda başına çok talihsizlik geldi.";
			link.l1 = "Evet, baba. Michel'e yardım etmek için bir gemiye ihtiyacım var, ama Karayipler'e yeni geldim ve cebimde beş kuruş yok. Ağabeyim bana biraz borç verebileceğini söyledi...";
			link.l1.go = "FastStart_2";	
			npchar.quest.meet = true;
		break;
		
		case "FastStart_2":
			DelLandQuestMark(npchar);
			dialog.text = "Michel sana bunu mu söyledi?";
			link.l1 = "Padre, kulağa pek güvenilir gelmiyor olabilirim, ama bu doğru. Bir gemi bulduğum anda kardeşimi hapisten çıkarabileceğim.";
			link.l1.go = "FastStart_3";
		break;
		
		case "FastStart_3":
			dialog.text = "Anladım, evladım. Doğruyu söylediğini görebiliyorum. Peki, Michel ve baban hatrına sana yardım edeceğim. Biraz birikmişim var, al bunları. Sanırım 50.000 peso ve 100 dublon yeterli olacaktır.";
			link.l1 = "Teşekkür ederim, padre. Şartlar nedir?";
			link.l1.go = "FastStart_4";
		break;
		
		case "FastStart_4":
			AddMoneyToCharacter(pchar, 50000);
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Hiç baskı yok. Geri ödemek için yarım yıl yeterli olur.";
			link.l1 = "Çok iyi, kutsal baba. Tekrar teşekkür ederim!";
			link.l1.go = "FastStart_5";
		break;
		
		case "FastStart_5":
			dialog.text = "Git, oğlum, benim kutsamamla.";
			link.l1 = "...";
			link.l1.go = "FastStart_6";
		break;
		
		case "FastStart_6":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			npchar.quest.FastStart = "true";
			pchar.questTemp.Sharlie.BenuaLoan = "true";
			SetFunctionTimerCondition("Sharlie_BenuaLoanTime", 0, 0, 180, false);
			AddQuestRecord("Sharlie", "5-2");
		break;
		
		case "FastStart_7":
			dialog.text = "Harika, oğlum. Umarım o para sana iyi gelmiştir.";
			link.l1 = "Evet, gerçekten de öyle oldu! Teşekkür ederim!";
			link.l1.go = "FastStart_8";
		break;
		
		case "FastStart_8":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddMoneyToCharacter(pchar, -50000);
			RemoveDublonsFromPCharTotal(100);
			pchar.quest.Sharlie_BenuaLoanTime.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.BenuaLoan");
			AddQuestRecord("Sharlie", "5-3");
		break;
		
		// Jason Долго и счастливо
		case "LH_abbat":
			dialog.text = "Charles, gözlerime inanamıyorum! Seni buraya getiren ne?!";
			link.l1 = "Beni kutsayın, Aziz Baba, çünkü size güzel haberlerle geldim - evleniyorum ve düğünümde nikâhı sizin kıymanızı istiyorum.";
			link.l1.go = "LH_abbat_1";
		break;
		
		case "LH_abbat_1":
			dialog.text = "Oğlum, bu harika! Demek babandan o mektubu aldın ve her zamanki gibi yine kendi bildiğini okudun? Senin adına gerçekten sevindim! Ama korkarım, bu kilisede evlenmeye karar vermediğin sürece sana yardımcı olamam.";
			link.l1 = " Görevlerinizin çıkmaza girdiğini anlıyorum, Aziz Baba. Size bir konuda yardımcı olabilir miyim? Evlilik töreni İspanyol bir şapelde gerçekleşecek olsa da, bu maceraya atılmak isterim elbette, fakat kutlamayı Martinique'te yapmaya kararlıyım. Ne çok gösterişli, ne de sade; saygın tanıklar ve onurlu misafirlerin huzurunda bir kutlama olacak.";
			link.l1.go = "LH_abbat_2";
		break;
		
		case "LH_abbat_2":
			dialog.text = "I'm sorry, my son, but all your authority is worth nothing against the stubbornness of the highest hierarchs of the Catholic Church, especially in the Spanish colonies. We haven't agreed on the question of sharing the influence of the Catholic missions between our countries, and now I'm here, as an honoured guest and an honoured hostage. The Spaniards are waiting for a better offer from our side. I have sent a message to Europe; hopefully the answer will come in two months' time and we will be able to resume negotiations. If it doesn't arrive in two months, it will certainly be here within the next six months.\nAnd yes, while the Pope and Mazarin have reached a compromise in the last couple of weeks, it's too early to talk about a truly warm relationship. Honestly, I'm not sure that we will ever come to any agreement. It seems to me that Palotti simply keeps me as a bargaining chip in his own political power plays. However, I have to say, the inquisitor has excellent coffee!";
			link.l1 = "Ne altı ayım var, ne de iki ayım! Babamın isteğini yerine getirmeliyim, yoksa beni istemediğim biriyle evlendirmeye zorlayacak. Üstelik sağlığı da eskisi gibi değil, ama yine de ona seçtiğim kadını ve geleceğin Monper hanımefendisini tanıtacak zamanım olsun isterim.";
			link.l1.go = "LH_abbat_3";
		break;
		
		case "LH_abbat_3":
			dialog.text = "Korkarım düğünün için başka bir rahip bulman gerekecek, evladım. Ne yazık ki, ben burada uzun süre kalacağım.";
			link.l1 = "Seni engizisyoncunun kahvesinden kaçırırsam ne dersin?";
			link.l1.go = "LH_abbat_4";
		break;
		
		case "LH_abbat_4":
			dialog.text = "Yardımınızı memnuniyetle kabul ederim. Bu göreve tesadüfen seçilmediğimden şüpheleniyorum. En kötü ihtimalle, Benoit Baba'yı basitçe unutacaklar. Ve her ne kadar Tanrı bana sabretmemi emretmiş olsa da, tüm o... nimetlerine rağmen, vardığım sonuç beni ağır bir yük altında bırakıyor. Ama tekrar ediyorum - Palotti Baba'nın isteklerinize kulak vereceği pek olası değil.";
			link.l1 = "O zaman kendime zaman kazandıracağım ve onu ikna etmeye çalışmayacağım. Ayin biter bitmez kiliseden çıkıp doğrudan gemime gideceğiz. Tereddüt etmeyin, Aziz Baba – buluşmamızı gördüler ve beni tanıyacaklar, eğer sizi valinin konağından çıkarmam gerekirse size yardım etmek çok daha zor olacak.";
			link.l1.go = "LH_abbat_5";
		break;
		
		case "LH_abbat_5":
			dialog.text = "Bu çok riskli, oğlum, gerçekten çok riskli. Dışarıda bir grup muhafız beni konağa götürmek için bekliyor ve şehir askerlerle dolu.";
			link.l1 = "Sürpriz unsurunu kullanacağız, Benoit Baba. Bana güvenmen yeterli, her şey yoluna girecek. Bu işlerde biraz... tecrübem var.";
			link.l1.go = "LH_abbat_6";
		break;
		
		case "LH_abbat_6":
			dialog.text = "Nasıl istersen. Ama lütfen, gereksiz kan dökülmesin! Ben de bu türden bazı şeyler yaşadım... Bize yol göster, oğlum. Arkandayım. Ama silah almayacağım, bunu isteme benden.";
			link.l1 = "Hiç düşünmedim bile, Baba. Ben hallederim. Peşimden gel, ama dikkatli ol, üstümüze ateş edebilirler.";
			link.l1.go = "LH_abbat_7";
		break;
		
		case "LH_abbat_7":
			DialogExit();
			LongHappy_SantiagoBenuaEscape();
		break;
		
		case "LH_abbat_8":
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);
			dialog.text = "Oğlum, beni serbest bıraktığın için sana teşekkür etmeye fırsatım olmamıştı. Görünüşe göre, İspanyol piskoposu ve Engizitör Palotti, kardinalimizle Vatikan arasındaki yeni kurulan ilişkileri bozmak istemişler. Yani sen tamamen ülkemizin çıkarları için hareket ettin. Yine. Ama benden başka kimse sana 'teşekkür ederim' demeyecek.";
			link.l1 = "Alışılmış bir şey, Kutsal Baba. Yardım edebildiğime sevindim. Ama size de bir şey sormam gerekiyor, hatırlıyor musunuz?";
			link.l1.go = "LH_abbat_9";
		break;
		
		case "LH_abbat_9":
			dialog.text = "Elbette! O halde gelelim asıl keyifli meseleye – Charles, en önemli günün için hazırlıklar nasıl gidiyor?";
			link.l1 = "Yavaş yavaş şekilleniyor. Daha kolay ve hızlı hazırlanan askeri seferler gördüm, ama buna değer!";
			link.l1.go = "LH_abbat_10";
		break;
		
		case "LH_abbat_10":
			dialog.text = "Elbette, oğlum! Ve bu vesileyle bir şeyi açıklığa kavuşturmak istiyorum – düğün törenini nasıl hayal ediyorsun?";
			link.l1 = "Yani, ne kadar kendini beğenmiş?";
			link.l1.go = "LH_abbat_11";
		break;
		
		case "LH_abbat_11":
			dialog.text = "Elbette! Kiliseyi hazırlamam gerekiyor, belki sen de bazı önemli insanları davet etmek istersin.";
			link.l1 = "Özel bir şey yok, Kutsal Baba. Dostumuz saydığım kişiler bizi başka bir yerde bekliyor olacak. Burada ise sadece birkaç görevli, adamlarım ve sıradan birkaç meraklı bulunacak.";
			link.l1.go = "LH_abbat_12";
		break;
		
		case "LH_abbat_12":
			dialog.text = "Pekâlâ, o zaman, sanırım küçük bir bağışla idare edebiliriz.";
			link.l1 = "Bu kulağa pek de korkutucu gelmiyor. Peki, böyle bir bağışın altın cinsinden karşılığı ne kadar?";
			link.l1.go = "LH_abbat_13";
		break;
		
		case "LH_abbat_13":
			dialog.text = "Koro, dini ayin ve diğer masraflar için - yüz elli, daha fazlası değil. Ayrıca, yeni evlilerden gelen geleneksel bağışla birlikte toplamda - iki yüz dublon.";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "Buyurun, Kutsal Baba.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "Şu askeri seferler meselesi... Bankaya gidip dönmem gerekecek.";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_14":
			DialogExit();
			npchar.dialog.currentnode = "LH_abbat_14_1";
		break;
		
		case "LH_abbat_14_1":
			dialog.text = "Bağışın ne olacak, oğlum?";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "Buyurun, Kutsal Baba.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "Evet, evet, yakında getireceğim...";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_15":
			RemoveDublonsFromPCharTotal(200); // Sinistra legendary edition
			dialog.text = "Hâlâ cevaplanması gereken bir soru var - gelini kim teslim edecek ve onun adına nikaha şahitlik edecek?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				pchar.questTemp.LongHappy.Pater1 = "Svenson";
				link.l1 = "Jan Svensson, Blueweld'den. İngiliz ama saygın bir adam ve Helen'e öz kızıymış gibi bağlı, üstelik onun evlatlık annesi de Gladys McArthur.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					pchar.questTemp.LongHappy.Pater1 = "Noel";
					link.l1 = "Baron Noël Forget, eminim bana bu onuru gösterecektir.";
				}
				else
				{
					pchar.questTemp.LongHappy.Pater1 = "Puancie";
					link.l1 = "Chevalier Philippe de Poincy, eminim bana bu onuru gösterecektir.";
				}
			}
			link.l1.go = "LH_abbat_16";
		break;
		
		case "LH_abbat_16":
			dialog.text = "Peki, damat için kim şahitlik edecek? Unutmayın, bu kişi soylu bir aileden gelmeli ve saygın biri olmalı.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					link.l1 = "Baron Noël Forget, eminim bana bu onuru gösterecektir.";
					link.l1.go = "LH_abbat_17_1";
				}
				else
				{
					link.l1 = "Chevalier Philippe de Poincy, eminim bana bu onuru gösterecektir.";
					link.l1.go = "LH_abbat_17_2";
				}
				link.l2 = "Fadey, Guadeloupe'tan saygın bir tüccardır. Sadece onun en sevdiği içkiden biraz stoklamam gerek.";
				link.l2.go = "LH_abbat_17_3";
			}
			else
			{
				link.l1 = "Fadey, Guadeloupe'tan saygın bir tüccardır. Sadece onun en sevdiği içkiden biraz stoklamam gerekiyor.";
				link.l1.go = "LH_abbat_17_3";
			}
		break;
		
		case "LH_abbat_17_1":
			pchar.questTemp.LongHappy.Pater2 = "Noel";
			dialog.text = "Harika, davetiyeleri göndereceğim, ama misafirlerin gelmesi biraz zaman alacak. Sanırım her şey bir ay içinde hazır olur ve davetliler de şehre gelmiş olurlar.";
			link.l1 = "Güzel! O zaman birkaç işimi halletmek için vaktim var. Yakında görüşürüz, Kutsal Baba, bana şans dile!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_2":
			pchar.questTemp.LongHappy.Pater2 = "Puancie";
			dialog.text = "Harika, davetiyeleri göndereceğim, fakat misafirlerin gelmesi biraz zaman alacak. Sanırım her şey bir ay içinde hazır olur ve davetliler de şehre varmış olurlar.";
			link.l1 = "Güzel! O zaman birkaç işimi halletmek için vaktim var. Yakında görüşürüz, Aziz Baba, bana şans dile!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_3":
			pchar.questTemp.LongHappy.Pater2 = "Fadey";
			dialog.text = "Harika, davetiyeleri göndereceğim, ama misafirlerin buraya gelmesi biraz zaman alacak. Sanırım her şey bir ay içinde hazır olur ve belirtilen kişiler de şehre gelmiş olur.";
			link.l1 = "Güzel! O zaman birkaç işimi halletmek için vaktim var. Yakında görüşürüz, Aziz Baba, bana şans dile!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_18":
			DialogExit();
			AddQuestRecord("LongHappy", "11");
			SetFunctionTimerCondition("LongHappy_SenPierreGuests", 0, 0, 31, false); // таймер
			if (!CheckAttribute(pchar, "questTemp.LongHappy.MarryRum"))
			{
			pchar.questTemp.LongHappy = "toIslaTesoro";
			LocatorReloadEnterDisable("Pirates_town", "reload4_back", true);//закрыть таверну Исла-Тесоро
			}
			npchar.dialog.currentnode = "First time";
		break;
		
		case "LH_abbat_19":
			dialog.text = "İşte o gün geldi, oğlum! Her şey hazır – birkaç saat içinde başlayabileceğiz. Solgun görünüyorsun!";
			link.l1 = "Biraz gerginim, Kutsal Baba.";
			link.l1.go = "LH_abbat_20";
		break;
		
		case "LH_abbat_20":
			dialog.text = "Bu çok normal. Bugün hayatının en önemli günü ve ben de, buradaki herkes gibi, senin adına içtenlikle mutluyum. Umarım en azından temel duaları hatırlıyorsundur – kiliseye pek ilgi gösterdiğin söylenemez, değil mi? Yine de, her durumda sana yardımcı olacağım.\nBir de – anladığım kadarıyla, gelin prensiplerinden ödün vermeyecek ve onu bir elbiseyle görmeyeceğiz? Demek ki sosyete senden bir sürpriz daha görecek – sürprizlerle dolusun zaten. Neyse, git oğlum, kendini toparla ve başlayalım.";
			link.l1 = "Evet, Kutsal Baba. Hadi yapalım.";
			link.l1.go = "LH_abbat_21";
		break;
		
		case "LH_abbat_21":
			DialogExit();
			chrDisableReloadToLocation = true;
			WaitDate("", 0, 0, 0, 2, 0);
			DoQuestReloadToLocation("FortFrance_church", "reload", "reload1", "LongHappy_MarryInit");
		break;
		
		case "LH_abbat_22":
			pchar.questTemp.LongHappy.Mistake = 0;
			dialog.text = "Pater noster, qui es in caelis, sanctificetur nomen tuum, ad...";
			link.l1 = "...adveniat regnum tuum";
			link.l1.go = "LH_abbat_23_1";
			link.l2 = "...requiem aeternam dona eis";
			link.l2.go = "LH_abbat_23_2";
		break;
		
		case "LH_abbat_23_1":
			dialog.text = "...fiat voluntas tua, sicut in caelo et in terra. Panem nostrum quotidianum da nobis hodie, et dimitte nobis debita nostra si...";
			link.l1 = "...sicut et nos dimittimus debitoribus nostris";
			link.l1.go = "LH_abbat_24_1";
			link.l2 = "...sicut erat in principio, et nunc et semper, et in saecula saeculorum. Amen";
			link.l2.go = "LH_abbat_24_2";
		break;
		
		case "LH_abbat_23_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "E-e... Hm...";
			link.l1 = "";
			link.l1.go = "LH_abbat_23_1";
		break;
		
		case "LH_abbat_24_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "E-e... Hm...";
			link.l1 = "";
			link.l1.go = "LH_abbat_24_1";
		break;
		
		case "LH_abbat_24_1":
			dialog.text = "et ne nos inducas in tentationem; sed libera nos a malo. Amen.";
			link.l1 = "Amin.";
			link.l1.go = "LH_abbat_25";
		break;
		
		case "LH_abbat_25":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Sevgili dostlar, Tanrı'nın huzurunda ve bu cemaatin önünde, bu adam ve kadını kutsal evlilik bağıyla birleştirmek için burada toplandık. Sevgili "+sld.name+" ve Charles, sen Tanrı'nın sözünü dinledin; O sana insan sevgisinin ve evliliğin anlamını hatırlattı. Şimdi, Kutsal Kilise adına, niyetlerini sorgulamak istiyorum.\n"+sld.name+" ve Charles, Rab'bin huzurunda evlilik bağına kendi isteğinle ve içtenlikle katılmak istiyor musun?";
			link.l1 = "Evet.";
			link.l1.go = "LH_abbat_26";
		break;
		
		case "LH_abbat_26":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_27":
			dialog.text = "Sağlıkta ve hastalıkta, mutlulukta ve kederde, hayatınızın sonuna dek birbirinize sadık kalmaya söz veriyor musunuz?";
			link.l1 = "Evet.";
			link.l1.go = "LH_abbat_28";
		break;
		
		case "LH_abbat_28":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_22";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_29":
			dialog.text = "Efendimizin size bahşedeceği çocukları sevmeye, kabul etmeye ve onları Hristiyan inancıyla yetiştirmeye niyet ediyor musunuz?";
			link.l1 = "Evet.";
			link.l1.go = "LH_abbat_30";
		break;
		
		case "LH_abbat_30":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_31":
			dialog.text = "Pekala, şimdi birbirinize dönün ve yemin edin.";
			link.l1 = "";
			link.l1.go = "LH_abbat_32";
		break;
		
		case "LH_abbat_32":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_33":
			dialog.text = "Burada bulunanlardan herhangi biri, bu çiftin kutsal evlilik bağıyla birleştirilmesine engel olabilecek bir sebep biliyorsa, şimdi konuşsun ya da sonsuza dek sussun.\nBu durumda, Tanrı'nın huzurunda ve burada toplananların önünde, sizi karı koca ilan ediyorum! In nomine Patris, et Filii, et Spiritus Sancti. Amin.";
			link.l1 = "Amin.";
			link.l1.go = "LH_abbat_34";
		break;
		
		case "LH_abbat_34":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_35":
			string sTemp;
			if (sti(pchar.questTemp.LongHappy.Mistake) > 1) sTemp = "(Whispering) Charles, my son, just move your lips, I beg you - don't try to make any sound...";
			else sTemp = "";
			dialog.text = "Yeni evliler, diz çöküp birlikte dua edin. Oratio fidelium. "+sTemp+"";
			link.l1 = "";
			link.l1.go = "LH_abbat_36";
		break;
		
		case "LH_abbat_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.lastname = "de Maure";
			sld.SpecialRole = "wife";
			sld.dialog.currentnode = "LongHappy_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 4.0);
		break;
		
		case "LH_abbat_37":
			dialog.text = "Tebrikler oğlum. Baban seninle gurur duyardı, ben de gurur duyuyorum. Bu zor zamanlarda mutlu olun ve birbirinize iyi bakın.";
			link.l1 = "Teşekkür ederim, Kutsal Baba. Ayin harikaydı ve onu sizin yönetmiş olmanıza çok sevindim.";
			link.l1.go = "LH_abbat_38";
		break;
		
		//--> Дикая Роза
		case "WildRose_Abb_2":
			dialog.text = "Demek bana danışmaya geldiniz, çocuklarım? O halde, sizi dinliyorum.";
			link.l1 = "Daha çok yardım için, baba. Bağlantıları olan ve her türlü insanı tanıyan birinden yardım...";
			link.l1.go = "WildRose_Abb_3";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua");
		break;

		case "WildRose_Abb_3":
			dialog.text = "Beni böldüğüm için affet oğlum, ama ben sadece mütevazı bir rahibim, gizli bir ajan değilim.";
			link.l1 = "Yine de, mütevazı bir rahip gizli bir ajanı tanıyor olabilir, değil mi? Ya da en azından ona nasıl ulaşabileceğimizi önerebilir?";
			link.l1.go = "WildRose_Abb_4_fortune";
			link.l2 = "Bizi buraya getiren mesele gerçekten de uzun zaman önce unutulmuş bazı sırlarla ilgili... Biz sadece onları yeniden gün yüzüne çıkarmaya çalışıyoruz.";
			link.l2.go = "WildRose_Abb_4_stealth";
		break;

		case "WildRose_Abb_4_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Bak genç adam, bu tavrını hiç beğenmedim. Lafı dolandırmadan sadede gel, ondan sonra sana nasıl – ya da gerçekten yardım edip edemeyeceğime – bakarız.";
			link.l1 = "Evet, baba. Kısa kesmeye çalışacağım...";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_4_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = ""+pchar.name+", bilmecelerle konuşma – itiraf etmeliyim ki, bu yorucu.";
			link.l1 = "Evet, baba. Kısa tutmaya çalışacağım...";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_5":
			dialog.text = "Devam et, oğlum.";
			link.l1 = "Yoldaşım Mary Casper, babasını – ya da en azından onunla ilgili bir iz – arıyor. Babasının İngiliz Donanması’nda subay olduğunu ve 1638’de Cape Catoche açıklarında batan ‘Wrangler’ adlı brigantinde görev yaptığını öğrendik.";
			link.l1.go = "WildRose_Abb_6";
		break;

		case "WildRose_Abb_6":
			dialog.text = "Ve hâlâ yaşıyor olmasını mı umuyorsun? Bunca yıl sonra?";
			link.l1 = "Gemide sağ çıkmamış olsa bile, Mary babasının nereden geldiğini, nasıl bir insan olduğunu, nasıl bir hayat sürdüğünü bilmek istiyor... Resmi belgelerde ayrıntı pek yok – ama yine de, onlarda bile değerli bir şey bulmak mümkün, sizce de öyle değil mi, Peder?";
			link.l1.go = "WildRose_Abb_7";
		break;

		case "WildRose_Abb_7":
			dialog.text = "Senin düşüncen doğru, oğlum. Niyetin iyi ve Tanrı'ya yakışır bir iş. Ama yine de benden tam olarak ne beklediğini anlayamıyorum.";
			link.l1 = "Uzun zamandır Takımadalar’da yaşıyorsun, baba. Belki İngiliz Donanması subaylarıyla ilgili sömürge arşivlerine erişimi olan birini tanıyorsundur?";
			link.l1.go = "WildRose_Abb_8_stealth";
			link.l2 = "İngiliz deniz subaylarının kayıtlarının tutulduğu sömürge arşivlerine erişimi olan birine ihtiyacımız var. Böyle birini mutlaka tanıyorsundur, Peder.";
			link.l2.go = "WildRose_Abb_8_charisma";
		break;

		case "WildRose_Abb_8_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "Ne istediğini anlıyor musun, oğlum? Mesele sadece bu bilginin askeri bir sır olmasında değil...";
			link.l1 = "Peki başka ne var, Baba? Açıkça konuşacağım...";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_8_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Ne istediğini anlıyor musun, oğlum? Mesele sadece bu bilginin askeri bir sır olmasında değil...";
			link.l1 = "Peki ya başka ne, Baba? Açıkça konuşacağım...";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_9":
			dialog.text = "Sorun tam da bu sömürge arşivlerinde yatıyor. Yirmi yıl önce Jamaika İspanyolların elindeydi, St. John’s ve Bridgetown ise sürekli baskın tehdidi altındaydı. Orada herhangi bir Kraliyet Donanması gemisinin konuşlanmış olması pek olası değil...";
			link.l1 = "Londra'daki Amirallik arşivlerini mi kastediyorsun, baba?";
			link.l1.go = "WildRose_Abb_10";
		break;

		case "WildRose_Abb_10":
			dialog.text = "Belki. Belgeler Amiralliğe gönderilmiş olmalı. Onları elde etmek kolay olmayacak.";
			link.l1 = "Ama yapılabilir, değil mi Baba?";
			link.l1.go = "WildRose_Abb_11";
		break;

		case "WildRose_Abb_11":
			dialog.text = "Hiçbir şey imkânsız değildir, oğlum. Ama çaba... ve ödeme gerekecek.";
			link.l1 = "Elbette, Baba. Parayı size mi vereyim, yoksa başka biriyle mi görüşmem gerekiyor?";
			link.l1.go = "WildRose_Abb_12";
		break;

		case "WildRose_Abb_12":
			dialog.text = "Ben kendim başka biriyle görüşeceğim, oğlum. Senden istediğim şey ise... sekiz yüz doblon.";
			link.l1 = "Pekala, baba. Ne kadar sürecek?";
			link.l1.go = "WildRose_Abb_13";
		break;

		case "WildRose_Abb_13":
			dialog.text = "Sanırım iki ay. Bu arada, aradığınız kişinin adını bana hâlâ söylemediniz.";
			link.l1 = " O adamın adı Joshua Casper. ";
			link.l1.go = "WildRose_Abb_14";
		break;

		case "WildRose_Abb_14":
			dialog.text = "Bunu aklımda tutacağım. Eğer şimdi tüm parayı ödemeye hazırsan — yarın bile haber gönderebilirim.";
			if (PCharDublonsTotal() >= 800)
			{
				link.l1 = "Elbette, baba. Al, buyur. Sekiz yüz altın.";
				link.l1.go = "WildRose_Abb_14_pay";
			}
			link.l2 = "Hayır baba, yanımda o kadar para yok. Ama yakında döneceğim ve getireceğim.";
			link.l2.go = "WildRose_Abb_14_nopay";
		break;

		case "WildRose_Abb_14_pay":
			RemoveDublonsFromPCharTotal(800);
			dialog.text = "Pekâlâ, "+pchar.name+" . İki ay sonra geri dön – o zamana kadar sana bir cevap bulacağımdan eminim.";
			link.l1 = "Teşekkür ederim, baba. Yeniden görüşene dek!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_1");
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2");
		break;

		case "WildRose_Abb_14_nopay":
			dialog.text = "Dediğin gibi, oğlum.";
			link.l1 = "Yakında döneceğim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			pchar.questTemp.WildRose_Etap3_Benua_2 = true;
		break;
		
		case "WildRose_Abb_16":
			dialog.text = "Joshua Casper'ı ve onun gemisini öğrendi – fakat bu gemi 'Wrangler' değildi. Kraliyet Donanması'nda bu isme sahip bir brig hiçbir zaman olmadı.";
			link.l1 = "Hm... Joshua Casper'ın görev yaptığı geminin kesinlikle o ismi taşıdığından eminim. Peki ya Joshua'nın kendisi?";
			link.l1.go = "WildRose_Abb_17";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3");
		break;

		case "WildRose_Abb_17":
			dialog.text = "O adam, birçok meziyeti ve ödülüyle seçkin bir subaydı – hepsi de şahsi sicilinde kayıtlıydı. Gerçi gerçek inancımıza mensup değildi, ama yine de değerli bir kaptandı. Mademoiselle böyle bir kökenden gurur duyabilir.";
			link.l1 = "Bu iyi bir haber, Baba. Ama izin verirsen, gemiye dönelim. Eğer o 'Wrangler' değilse, adı neydi?";
			link.l1.go = "WildRose_Abb_19";
			AddQuestRecordInfo("WildRose_Records_3", "1");
		break;

		case "WildRose_Abb_19":
			dialog.text = "'Cornwall'. 1638 yılının Ocak ayında Plymouth'tan ayrıldı; görevi Antigua ve Providence garnizonlarına maaşları teslim etmekti.";
			link.l1 = "İnanılmaz...";
			link.l1.go = "WildRose_Abb_20";
			AddQuestRecordInfo("WildRose_Records_4", "1");
		break;

		case "WildRose_Abb_20":
			dialog.text = "Gemi nihai varış noktasına ulaştı mı, bilmiyorum. Ama St. John’s limanına uğradı. Liman ofisinde o yılın 2 Haziran tarihli Kaptan Casper’ın bir raporu hâlâ duruyor.";
			link.l1 = "Senin göründüğün kadar basit biri olmadığını biliyordum, baba! Bu belge, sanırım, bazı önemli ayrıntılar içeriyor?";
			link.l1.go = "WildRose_Abb_21_charisma";
			link.l2 = "Sana sonsuza dek minnettarız, Baba. Bu belgeyi andığına göre – içinde önemli bir şey olmalı, değil mi?";
			link.l2.go = "WildRose_Abb_21_honor";
			AddQuestRecordInfo("WildRose_Records_5", "1");
		break;

		case "WildRose_Abb_21_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Sadece Azorlar yakınlarında İspanyol kalyonu 'Toro' ile yapılan bir çarpışmanın raporu var; mürettebatın üçte biri ölmüş – raporu oku, her şey orada yazıyor.";
			link.l1 = "Bir soru daha: Antigua liman idaresinin kayıtlarına erişiminiz olduğuna göre, Joshua Casper’ın adını başka bir yerde de gördünüz mü, tesadüfen?";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_21_honor":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "Azorlar yakınlarında İspanyol 'Toro' gemisiyle yapılan bir çatışmanın raporu var, mürettebatın üçte biri ölmüş – raporu oku, her şeyi anlatıyor.";
			link.l1 = "Bir soru daha: Antigua liman idaresinin kayıtlarına erişiminiz olduğuna göre, Joshua Casper’ın adını başka bir yerde de gördünüz mü, tesadüfen?";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_22":
			dialog.text = "Benden çok şey istiyorsun, oğlum. Eğer o kazadan sağ çıkıp sonra filoya döndüğünü ima ediyorsan – buna pek ihtimal vermiyorum.";
			link.l1 = "Tanrı'nın işleri gizemlidir, Baba.";
			link.l1.go = "WildRose_Abb_23";
		break;

		case "WildRose_Abb_23":
			dialog.text = "Evet, oğlum. Ama bak, kişisel dosyasında Joshua Casper'ın 1586 yılında doğduğu yazıyor...";
			link.l1 = "Belki de haklısın, baba.";
			link.l1.go = "WildRose_Abb_24_fortune";
			link.l2 = "Biliyor musun Baba, Karayipler'de geçirdiğim yıllarda öyle şeyler gördüm ki, en inanılmaz hikayelere bile inanabilirim.";
			link.l2.go = "WildRose_Abb_24_charisma";
		break;

		case "WildRose_Abb_24_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Böylesine bir subay, elbette savaşta ölmeye layıktı. Ama felsefi açıdan bakarsak, bir bakıma bu da bir savaştı...";
			link.l1 = "Ben bir filozof değilim, baba. Ama her şey için teşekkür ederim...";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_24_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Böylesine bir subay, elbette savaşta ölmeye layıktı. Ama felsefi açıdan bakarsak, bu da bir bakıma savaştı...";
			link.l1 = "Ben bir filozof değilim, Baba. Ama her şey için teşekkür ederim...";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_25":
			dialog.text = "Tanrı sizi bu yolda yönlendiriyor, evlatlarım, ve size yardımcı olmak benim mütevazı görevim. Ama korkarım ki bu konuda sizin için yapabileceğim başka bir şey kalmadı...";
			link.l1 = "Anladım, Baba. O halde, müsaadenizle ayrılalım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_5");
		break;
		//<-- Дикая Роза
		
		//--> Эпилог
		case "SharlieEpilog_Benua_1":
			dialog.text = "Babanın durumu beni derinden endişelendiriyor. Sana mektubunda bundan bahsetti mi bilmiyorum ama bana yazdığı mesajda bedeninin artık onu terk ettiğini ve uzun süre dayanamayacağını düşündüğünü itiraf etti.";
			link.l1 = "Hastalığın geçmediğinden bahsetmişti... Ama korkularından söz etmemiş gibi görünüyor.";
			link.l1.go = "SharlieEpilog_Benua_2";
			DeleteAttribute(pchar, "questTemp.SharlieEpilog_Benua");
		break;

		case "SharlieEpilog_Benua_2":
			dialog.text = "Ben de sana fazlasını söyleyemem — bana anlattıkları bunlardı. Ama bir şey açık: seni bir daha göremeden Tanrı'nın huzuruna çıkmaktan korkuyor.";
			link.l1 = "Bundan bahsetti. Doğrusu, ben de onu ziyaret etmeyi düşünüyordum... Ama...";
			link.l1.go = "SharlieEpilog_Benua_3";
		break;

		case "SharlieEpilog_Benua_3":
			if (!CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_1"))
			{
				dialog.text = "Oğlum, kimin ne kadar ömrü kaldığını yalnızca Tanrı bilir. Bu buluşmayı erteleme: bazen tek bir sarılma, binlerce duanın sağlayamayacağı huzuru verebilir ruha.";
				npchar.SharlieEpilog_BenuaRazgovor_1 = true;
			}
			else
			{
				dialog.text = ""+pchar.name+", umarım bu ziyaretini artık ertelemezsin? Unutma, zaman senin aleyhine işliyor...";
			}
			link.l1 = "Haklısınız, rahip. Hemen seyahate hazırlanmaya başlayacağım. Şu anki konumum gereği her şeyi yoluna koymak biraz zaman alabilir...";
			link.l1.go = "SharlieEpilog_Benua_5";
			link.l2 = "Endişelerinizi anlıyorum kutsal baba, bu konuda düşüneceğime söz veriyorum. Ancak şu anda erteleyemeyeceğim çok önemli işlerim var. Bu konuşmaya sonra döneriz.";
			link.l2.go = "SharlieEpilog_Benua_4_exit";
		break;

		case "SharlieEpilog_Benua_4_exit":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_DlgExit_2");
		break;

		case "SharlieEpilog_Benua_5":
			dialog.text = "Eğer borçların varsa, oğlum, onları ödemekle başlamanı tavsiye ederim. Tefeciler oldukça intikamcı insanlardır: itibarına büyük zarar verebilirler ve bununla birlikte tüm ailenin iyi ismine de — hatta Eski Dünya’da bile.\n"+
			"Diğer konulara gelince — babanla olan dostluğum ve Tanrı’nın yüceliği adına — sana elimden gelen her türlü yardımı yapacağım. Yazılı talimatlarını verebilirsin, ben de onların zamanında alıcılara ulaşmasını sağlarım. Sadece kurye masraflarını ödemen yeterli. Bence tüm mektuplar için iki yüz doblon yeterli olacaktır.";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "Teşekkür ederim, kutsal baba. Yardımınız gerçekten yerinde olacak. Alın, lütfen.";
				link.l1.go = "SharlieEpilog_Benua_6";
			}
			link.l2 = "İlginiz için teşekkür ederim, kutsal baba. Ne yazık ki şu anda yanımda gereken miktar yok. Bu konuyu biraz sonra tekrar ele alalım.";
			link.l2.go = "SharlieEpilog_Benua_DublonsLater";
			SharlieEpilog_Benua_Dlg_1();
		break;

		case "SharlieEpilog_Benua_DublonsLater":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_DlgExit_3");
		break;

		case "SharlieEpilog_Benua_DublonsLater_2":
			dialog.text = "Elbette, "+pchar.name+". Sanırım iki yüz doblon getirdin?";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "Elbette. Buyurun, alın.";
				link.l1.go = "SharlieEpilog_Benua_6";
			}
			link.l2 = "Ne yazık ki, şu anda gerekli miktara sahip değilim.";
			link.l2.go = "exit";
		break;

		case "SharlieEpilog_Benua_6":
			dialog.text = "Mükemmel, oğlum.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			RemoveDublonsFromPCharTotal(200);
			DeleteAttribute(pchar, "questTemp.SharlieEpilog_Benua_DublonsLater");
		break;
		
				case "SharlieEpilog_Benua_Delivery":
			if (!CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_2"))
			{
				dialog.text = "Peki, nereden başlamak istersin?";
				npchar.SharlieEpilog_BenuaRazgovor_2 = true;
			}
			else
			{
				dialog.text = "Kime ve ne hakkında haber vermek istiyorsun?";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_IslaMona"))
			{
				link.l1 = "Bir keresinde haritalarda yer almayan bir ada bulmuştum. Orada hâlihazırda birkaç yerleşimci vardı ve onların hamisi oldum. Ben ayrılınca yeni bir 'valiye' ihtiyaçları olacak.";
				link.l1.go = "SharlieEpilog_Benua_IslaMona";
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_Baron"))
			{
				link.l2 = "La Vega'dan Marcus Tirax'a bir mektup göndermek istiyorum. Konu çok önemli değil ama mektubun zamanında ulaşması gerekiyor.";
				link.l2.go = "SharlieEpilog_Benua_Baron";
			}
			if (CheckCharacterItem(PChar, "patent_fra") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_Patent"))
			{
				link.l3 = "Fransa'ya ait geçerli bir patentim var — Capsterville şansölyesine kararımı bildirmek istiyorum.";
				link.l3.go = "SharlieEpilog_Benua_Patent";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Money"))
			{
				link.l4 = "Kutsal baba, bu topraklarda geçirdiğim yıllar boyunca epey para biriktirdim. Ancak aileme kalmadan önce bu parayı arındırmak istiyorum. Belki de bulaştığı kanı temizlemek... Bu diyarlardan bir haydut gibi ganimetle değil, vicdanı ve itibarı toplumun gözünde temiz bir insan olarak ayrılmak istiyorum.";
				link.l4.go = "SharlieEpilog_Benua_Money";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Svenson") && CheckAttribute(pchar, "questTemp.SharlieEpilog_IslaMona_France"))
			{
				link.l5 = "Blueveld’den Jan Svenson’a ayrıldığımı bildirmek isterim. Adaları terk ederken ona haber vermemek saygısızlık olurdu.";
				link.l5.go = "SharlieEpilog_Benua_Svenson";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Houk"))
			{
				link.l6 = "Maroon Town’daki Hawk ailesine yolculuğumdan bahsetmek istiyorum.";
				link.l6.go = "SharlieEpilog_Benua_Houk";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Jino"))
			{
				link.l7 = "Saint John’s’dan Gino Guineyli’ye Eski Dünya’ya gittiğimi bildirmek istiyorum.";
				link.l7.go = "SharlieEpilog_Benua_Jino";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_S") || CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_M") || CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_L"))
			{
				link.l85 = "Hepsi bu kadar, baba... Görünüşe göre yola çıkmaya hazırım.";
				link.l85.go = "SharlieEpilog_Benua_TimeToGoHome";
			}
			link.l99 = "Affedin kutsal baba, gitmem gerek.";
			link.l99.go = "SharlieEpilog_exit";
		break;
		
		case "SharlieEpilog_exit":
			DialogExit();
			LAi_SetStayType(npchar);
			NextDiag.CurrentNode = "First time";
		break;
		
				case "SharlieEpilog_Benua_Jino":
			dialog.text = "Elbette, oğlum.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Jino_2";
			pchar.questTemp.SharlieEpilog_Jino = true;
		break;
		
		case "SharlieEpilog_Benua_Jino_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Jino_3";
			AddQuestRecord("SharlieEpilog", "8_1");
		break;
		
		case "SharlieEpilog_Benua_Jino_3":
			dialog.text = "...";
			link.l1 = "Hazır. Gönderilebilir.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Houk":
			dialog.text = "Elbette, oğlum.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Houk_2";
			pchar.questTemp.SharlieEpilog_Houk = true;
		break;
		
		case "SharlieEpilog_Benua_Houk_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Houk_3";
			AddQuestRecord("SharlieEpilog", "8");
		break;
		
		case "SharlieEpilog_Benua_Houk_3":
			dialog.text = "...";
			link.l1 = "Hazır. Gönderilebilir.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Svenson":
			dialog.text = "Blueveld’den Jan Svenson... Hatırlayacağım. Ver mektubu — bugün yola çıkacak.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Svenson_2";
			pchar.questTemp.SharlieEpilog_Svenson = true;
		break;
		
		case "SharlieEpilog_Benua_Svenson_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Svenson_3";
			AddQuestRecord("SharlieEpilog", "7");
		break;
		
		case "SharlieEpilog_Benua_Svenson_3":
			dialog.text = "...";
			link.l1 = "Jan’ın evini bulmak zor değil. Herhangi birine sor yeter — tüm Blueveld’de onu ve nerede yaşadığını bilmeyen biri zor bulunur.";
			link.l1.go = "SharlieEpilog_Benua_Svenson_4";
		break;
		
		case "SharlieEpilog_Benua_Svenson_4":
			dialog.text = "Endişelenme, oğlum, bizim adamlarımız işlerini iyi bilir. Mektup doğru kişiye ve zamanında ulaşacak.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Money":
			dialog.text = "Kilise, suç yoluyla kazanılmış altını kutsasın mı istiyorsun?";
			link.l1 = "Daha çok — Fransa ve Majesteleri’ne hizmet ederken kazanılmış bir altın.";
			link.l1.go = "SharlieEpilog_Benua_Money_2";
		break;
		
		case "SharlieEpilog_Benua_Money_2":
			dialog.text = "Seni anlıyorum, oğlum. Kilisenin parayı arındırmadığını ve nasıl kazanıldığını değiştirmediğini söyleyebilirim. Ama açlar aç kalmaya, evsizler sokakta yatmaya, hastalar yardım görmeden ölmeye devam ediyorsa, bunun ne faydası olur? Bu parayı kutsamaya hazırım. Karşılığında, bu servetin küçük bir kısmının sana değil, yardıma muhtaç olanlara hizmet etmesini istiyorum.";
			link.l1 = "Elbette, kutsal baba, ne kadar derseniz bağışlamaya hazırım.";
			link.l1.go = "SharlieEpilog_Benua_Money_3";
		break;
		
		case "SharlieEpilog_Benua_Money_3":
			dialog.text = "Peki, yanına ne kadar para almak istiyorsun?";
			link.l1 = "On milyon peso.";
			link.l1.go = "SharlieEpilog_Benua_Money_4";
			if (sti(pchar.Money) >= 250000)
			{
				link.l2 = "Yirmi beş milyon peso.";
				link.l2.go = "SharlieEpilog_Benua_Money_5";
			}
			if (sti(pchar.Money) >= 500000)
			{
				link.l3 = "Elli milyon peso.";
				link.l3.go = "SharlieEpilog_Benua_Money_6";
			}
		break;
		
				case "SharlieEpilog_Benua_Money_4":
			dialog.text = "Bu durumda, yüz bin peso bağış yeterli olacaktır. Bu parayla ihtiyacı olanlar için aylarca yemek sağlayabiliriz. Bu miktarı hemen şimdi vermeye hazır mısın, oğlum?";
			link.l1 = "Elbette. Buyurun, alın. Gerçekten yardıma ihtiyacı olanlara yardımcı olmak beni memnun eder ve eminim ki bu para sizin gözetiminizde akıl ve onurla kullanılacaktır.";
			link.l1.go = "SharlieEpilog_Benua_Money_4_1";
			link.l2 = "Affedersiniz, bunu bir kez daha düşünmem gerekiyor.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money_5":
			dialog.text = "Bu durumda bağışın iki yüz elli bin peso olmalı. Bu miktar bize, senin adını yüceltecek ve en azından başlarda ihtiyaçlarını karşılayacak bir yetimhane inşa etmemizi sağlar. Bu miktarı hemen şimdi vermeye hazır mısın, oğlum?";
			link.l1 = "Elbette. Buyurun, alın. Gerçekten yardıma ihtiyacı olanlara yardımcı olmak beni memnun eder ve eminim ki bu para sizin gözetiminizde akıl ve onurla kullanılacaktır.";
			link.l1.go = "SharlieEpilog_Benua_Money_5_1";
			link.l2 = "Affedersiniz, bunu bir kez daha düşünmem gerekiyor.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money_6":
			dialog.text = "Görünüşe göre zamanını boşa harcamamışsın, "+pchar.name+". Sanırım beş yüz bin peso bağış fazlasıyla yeterli olacaktır. Böyle bir katkı sayesinde bir hastane inşa edebilir ve onu uzun yıllar boyunca tüm ihtiyaçlarıyla donatabiliriz. Bu miktarı hemen şimdi vermeye hazır mısın, oğlum?";
			link.l1 = "Elbette. Buyurun, alın. Gerçekten yardıma ihtiyacı olanlara yardımcı olmak beni memnun eder и eminim ki bu para sizin gözetiminizde akıl ve onurla kullanılacaktır.";
			link.l1.go = "SharlieEpilog_Benua_Money_6_1";
			link.l2 = "Affedersiniz, bunu bir kez daha düşünmem gerekiyor.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money_4_1":
			dialog.text = "Harika, oğlum.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -100000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "10000000");
			AddQuestUserData("SharlieEpilog", "tSum", "100000");
			pchar.questTemp.SharlieEpilog_gold_S = true;
			pchar.questTemp.SharlieEpilog_Money = true;
		break;

		case "SharlieEpilog_Benua_Money_5_1":
			dialog.text = "Harika, oğlum.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -250000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "25000000");
			AddQuestUserData("SharlieEpilog", "tSum", "250000");
			pchar.questTemp.SharlieEpilog_gold_M = true;
			pchar.questTemp.SharlieEpilog_Money = true;
		break;

		case "SharlieEpilog_Benua_Money_6_1":
			dialog.text = "Harika, oğlum.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -500000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "50000000");
			AddQuestUserData("SharlieEpilog", "tSum", "500000");
			pchar.questTemp.SharlieEpilog_gold_L = true;
			pchar.questTemp.SharlieEpilog_Money = true;
			Achievment_Set("ach_CL_205");
		break;

		case "SharlieEpilog_Benua_Patent":
			dialog.text = "Peki kararın ne olacak, oğlum?";
			link.l1 = "Uzun bir yolculuk beni bekliyor olsa da, patentimi korumak istiyorum — ve aynı şekilde Fransa’ya ve Kral’a olan sadakatimi de.";
			link.l1.go = "SharlieEpilog_Benua_Patent_2";
			link.l2 = "Patentten vazgeçmeye karar verdim. Önümde uzun bir yol var ve ne zaman döneceğimi bilmiyorum. Belki de yerine getiremeyeceğim görev ve kuralları taşımanın anlamı yok.";
			link.l2.go = "SharlieEpilog_Benua_Patent_6";
			pchar.questTemp.SharlieEpilog_Patent = true;
		break;

		case "SharlieEpilog_Benua_Patent_2":
			dialog.text = "Böyle bir karar verdiğine sevindim, oğlum. Devletimizin bugün her zamankinden daha fazla güçlü ve cesur şövalyelere ihtiyacı var. Ama söyle bana, "+pchar.name+", hiç yerleşmeyi, bir yuva kurmayı, her an hayatını riske atmamayı düşündün mü? Zira insan, sonsuza dek ateşte sınanmak için yaratılmamıştır.";
			link.l1 = "Ellerimi kucağımda bağlayıp oturabileceğimden emin değilim, kutsal baba. Ama Kitap’ta yazdığı gibi: 'Rabbin savaşçılarına da işleri tamamlandığında dinlenme verilir.' Henüz işim bitmiş değil ama günü geldiğinde kılıcımı sonsuza dek kınına koymayı umuyorum.";
			link.l1.go = "SharlieEpilog_Benua_Patent_3";
		break;

		case "SharlieEpilog_Benua_Patent_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Patent_4";
			AddQuestRecord("SharlieEpilog", "5_2");
		break;

		case "SharlieEpilog_Benua_Patent_4":
			dialog.text = "Harika, oğlum. Eminim ki Majesteleri senin sadakatini ve özverini karşılıksız bırakmayacaktır.";
			link.l1 = "Şu an aklım bambaşka yerlerde... Umarım babam malikanemizde kalmam için ısrar etmez. Buna hazır olduğumu sanmıyorum. Ama neyse ki, bunu düşünmek için bolca vaktim olacak.";
			link.l1.go = "SharlieEpilog_Benua_Patent_5";
		break;

		case "SharlieEpilog_Benua_Patent_5":
			dialog.text = "...";
			link.l1 = "Peki öyleyse, şimdi dünyevi işlere geri dönelim.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Patent_6":
			dialog.text = "Bu mantıklı bir karar. Ancak şunu da belirtmeliyim ki: ayrılman Fransa’nın bu sulardaki gücünü ciddi şekilde zayıflatacak.";
			link.l1 = "Eminim ki Majestelerinin emrinde, Fransa’nın görkemini sarsmayacak kadar onurlu kaptanlar vardır.";
			link.l1.go = "SharlieEpilog_Benua_Patent_7";
		break;
		
		case "SharlieEpilog_Benua_Patent_7":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Patent_8";
			AddQuestRecord("SharlieEpilog", "5_1");
		break;

				case "SharlieEpilog_Benua_Patent_8":
			dialog.text = "...";
			link.l1 = "Hepsi bu kadar. Sanki omuzlarımdan bir yük kalktı. İtiraf etmeliyim ki Karayipler’e kim olarak geldiğimi bile unuttum… Ne çok şey yaşandı.";
			link.l1.go = "SharlieEpilog_Benua_Patent_9";
		break;

		case "SharlieEpilog_Benua_Patent_9":
			dialog.text = "Belki bunu defalarca duymuşsundur, oğlum: Tanrı’nın yolları esrarlı ve anlaşılmazdır. Yukarıdan sana takdir edilmiş ne varsa onlarla onurla yürüdün. Fakat inanıyorum ki sınavların henüz bitmedi ve belki de şanının tacı daha yeni yükselecek.";
			link.l1 = "Şan bir yük getirir, kutsal baba. Onu arzulayan herkes onun ağırlığını taşıyamaz… ve doğru zamanda duramaz.";
			link.l1.go = "SharlieEpilog_Benua_Patent_10";
		break;

		case "SharlieEpilog_Benua_Patent_10":
			dialog.text = "...";
			link.l1 = "Peki, şimdi dünyevi işlere dönelim.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Baron":
			dialog.text = "Oğlum, korsanların lideriyle işin mi var?";
			link.l1 = "Kodex’in koruyucusunu tanıyor musunuz?";
			link.l1.go = "SharlieEpilog_Benua_Baron_2";
			pchar.questTemp.SharlieEpilog_Baron = true;
		break;
		
		case "SharlieEpilog_Benua_Baron_2":
			dialog.text = "Kodex’in koruyucusu mu? Hayır, onunla tanışmıyorum. Marcus Tirax’ı tanıyorum — arkasında öyle bir kan var ki Rabbin affını kazanmak için yüzlerce yıl dua bile yetmez. Ve yine de… gerçekten onunla iş yapıyor musun?";
			link.l1 = "Onun sempatisini kazanmak zorunda kaldım… Michel’i hapisten çıkarmak için. Her neyse, hatamı anladım ve artık onunla ilişki sürdürmek istemiyorum. Bu mektupla aramızdaki son bağı koparacağım.";
			link.l1.go = "SharlieEpilog_Benua_Baron_3";
			link.l2 = "Artık bunun bir önemi yok. Takımadaları terk ediyorum ve yollarımız kendi kendine ayrılacak, kutsal baba.";
			link.l2.go = "SharlieEpilog_Benua_Baron_7";
		break;
		
		case "SharlieEpilog_Benua_Baron_3":
			dialog.text = "Peki o bağ nedir, oğlum? Umarım masumların kanıyla lekelenmemiştir?";
			link.l1 = "Resmî olarak Le-François korsan yerleşiminin başıydım. Gerçekte ise her şeyi başka biri yönetiyordu. Bugün korsan baronu unvanından feragat ediyorum — tamamen ve geri dönüşü olmadan.";
			link.l1.go = "SharlieEpilog_Benua_Baron_4";
		break;
		
		case "SharlieEpilog_Benua_Baron_4":
			dialog.text = "Doğru yola girdiğin için memnunum, oğlum, ve ruhunun kurtuluşu için dua edeceğim. Herkes hata yapabilir, fakat Rab sadece içten tövbe edenleri affeder.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Baron_5";
		break;
		
		case "SharlieEpilog_Benua_Baron_5":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Baron_6";
			AddQuestRecord("SharlieEpilog", "4_1");
		break;
		
				case "SharlieEpilog_Benua_Baron_6":
			dialog.text = "Harika, "+pchar.name+". Mektubu bana ver — adresine ulaştığından emin olurum. Ve dua etmeyi unutma, oğlum. Yalnızca tövbe ve dua, ruhu en ağır günahlardan bile arındırabilir.";
			link.l1 = "Teşekkür ederim, kutsal baba. Belki de her şeyimi henüz yitirmedim.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Baron_7":
			dialog.text = "Günah ne kadar büyük olursa olsun, oğlum, affın kapıları daima açıktır. Tövbe, dua ve iyilikler ruhu temizler — tıpkı yağmurun taşı tozdan arındırması gibi.";
			link.l1 = "Her şeyin bir zamanı vardır, kutsal baba. Şimdi ise dünyevi işlerimle ilgilenmeliyim.";
			link.l1.go = "SharlieEpilog_Benua_Baron_8";
		break;
		
		case "SharlieEpilog_Benua_Baron_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Baron_9";
			AddQuestRecord("SharlieEpilog", "4_2");
		break;
		
		case "SharlieEpilog_Benua_Baron_9":
			dialog.text = "...";
			link.l1 = "Alın lütfen.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_IslaMona":
			dialog.text = "Harika, oğlum. Bu insanları düşündüğün ve onları unutmadığın için sevindim. Bu adayı kime emanet etmek istiyorsun?";
			link.l1 = "Üzerine Fransız bayrağının çekilmesi gerektiğini düşünüyorum. Er ya da geç ada keşfedilecek ve başka ülkeler ona sahip olmak isteyebilir. Buna izin veremem.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France";
			link.l2 = "Bu ada ve halkı, bir kraliyet otoritesinin gölgesi altında değil, özgürce yaşamalı. Bluelveld’den dostum Jan Svenson’a mektup göndermek niyetindeyim. Bu toprağa göz kulak olmayı kabul edeceğinden eminim. Fakat sizi temin ederim, kutsal baba — bu konuşma gizli kalsın, bu insanların güvenliği için.";
			link.l2.go = "SharlieEpilog_Benua_IslaMona_Pirate";
			pchar.questTemp.SharlieEpilog_IslaMona = true;
		break;
		
		case "SharlieEpilog_Benua_IslaMona_France":
			dialog.text = "Bilgece davranıyorsun, "+pchar.name+". Kral’ın koruması altında bu ada düzen ve güvenlik bulacak.";
			link.l1 = "Gerekli mektubu Capsterville dairesine ve ada halkına göndereceğim. Koordinatları zarfa yazacağım.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France_2";
		break;
		
		case "SharlieEpilog_Benua_IslaMona_France_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_IslaMona_France_3";
			pchar.questTemp.SharlieEpilog_IslaMona_France = true;
			AddQuestRecord("SharlieEpilog", "3_1");
		break;
		
		case "SharlieEpilog_Benua_IslaMona_France_3":
			dialog.text = "...";
			link.l1 = "Alın. Umarım adamlarınız, Majestelerinin filosundan önce adayı bulabilir.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France_4";
		break;
		
		case "SharlieEpilog_Benua_IslaMona_France_4":
			dialog.text = "Endişelenme, oğlum. Bu mektupların teslimini en iyi kuryelerimize emanet edeceğim.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_IslaMona_Pirate":
			dialog.text = "Doğru yolu seçip seçmediğini yargılamak bana düşmez, oğlum. Er ya da geç biri bu adayı keşfedecek ve bir devlet ona sahip olmak isteyecek. Bu sadece bir zaman meselesi. Ama bu kararı aldıysan — bu Tanrı’nın isteğidir. Endişelenme: bu insanları tehlikeye atmam ve onlar için dua ederim.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_Pirate_2";
		break;
		
		case "SharlieEpilog_Benua_IslaMona_Pirate_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_IslaMona_Pirate_3";
			pchar.questTemp.SharlieEpilog_IslaMona_Pirate = true;
			AddQuestRecord("SharlieEpilog", "3_2");
		break;
		
		case "SharlieEpilog_Benua_IslaMona_Pirate_3":
			dialog.text = "Bluelveld’den Jan Svenson, değil mi?";
			link.l1 = "Aynen öyle, kutsal baba. İkinci mektubun ise doğrudan adaya ulaştırılması gerekiyor. Koordinatlar zarfın üzerinde yazıyor.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_TimeToGoHome":
			dialog.text = "Harika, oğlum. Yanılmıyorsam buraya '"+GetShipName("Ulysse")+"' adlı bir pinasla gelmiştin?";
			link.l1 = "Doğru. Ama neden sordunuz?";
			link.l1.go = "SharlieEpilog_Benua_TimeToGoHome_2";
		break;
		
		case "SharlieEpilog_Benua_TimeToGoHome_2":
			dialog.text = "Çünkü bu gemi yakın zamanda açık artırmaya çıkarıldı. Ve senin için, Charles, eve aynı gemiyle dönme şansı var — ama bu sefer kaptanı olarak.";
			link.l1 = "Hımm… İtiraf etmeliyim ki teklif cazip. Liman ofisine uğramalıyım. Teşekkür ederim, kutsal baba.";
			link.l1.go = "SharlieEpilog_Benua_TimeToGoHome_3";
		break;
		
		case "SharlieEpilog_Benua_TimeToGoHome_3":
			DialogExit();
			NextDiag.CurrentNode = "First Time";
			AddDialogExitQuestFunction("SharlieEpilog_PU_Ulysse_1");
		break;
		//<-- Эпилог
		
		case "LH_abbat_38":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
