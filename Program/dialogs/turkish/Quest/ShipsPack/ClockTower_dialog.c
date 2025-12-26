int iClockSP4PseudoGlobal = SOUND_INVALID_ID;

void ProcessDialogEvent()
{
	ref NPChar, sld, realShip;
	aref Link, NextDiag, arTmp;
	int i, n, NextMonth, idx;
	string sTemp, sStr, Month, NationName, shipType;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	if (HasSubStr(Dialog.CurrentNode, "chosenIdx/"))
	{
		Dialog.tmpIdx = FindStringAfterChar(Dialog.CurrentNode, "/");
		Dialog.CurrentNode = FindStringBeforeChar(Dialog.CurrentNode, "/");
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Ne istiyorsunuz?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "exit";
		break;
		
		// Диалог с Йоханом
		case "ClockTower_Johan_1":
			dialog.text = "Durun, bay kaptan. Bu noktadan öteye geçiş yok.";
			link.l1 = "Neden olmasın?";
			link.l1.go = "ClockTower_Johan_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_2":
			dialog.text = "Şu kuleyi görüyor musun? Hollanda Batı Hindistan Şirketi'nin ofisi. Gemi kayıt bölümü ve arşivi. Sadece randevu ile giriş.";
			link.l1 = "Bir randevu nasıl alınır?";
			link.l1.go = "ClockTower_Johan_3";
		break;

		case "ClockTower_Johan_3":
			dialog.text = "Bilmesi gerekenler bilir. Mynheer direktör öyle herkesle çalışmaz.";
			link.l1 = "'Mynheer direktör'? O da kim?";
			link.l1.go = "ClockTower_Johan_4";
		break;

		case "ClockTower_Johan_4":
			dialog.text = "Direktör van Doorn. Belki tam olarak bir direktör değil, ama herkes ona böyle diyor. On yıldır burada çalışıyor — her şeyi düzene soktu. Şimdi Karayipler'deki her gemi onun ofisinden geçiyor.";
			link.l1 = "Her gemi mi? Savaş gemileri bile mi?";
			link.l1.go = "ClockTower_Johan_5";
		break;

		case "ClockTower_Johan_5":
			dialog.text = "Sadece en iyi gemiler ve en zengin kaptanlar. Büromuzun müşterisi olmak büyük bir onurdur!";
			link.l1 = "Ne tür hizmetler sunuyorsunuz?";
			link.l1.go = "ClockTower_Johan_6";
		break;

		case "ClockTower_Johan_6":
			dialog.text = "Detaylara vakıf değilim — sadece girişi koruyorum. Ama insanların buradan memnun ayrıldıklarını duydum.";
			link.l1 = "Etkileyici.";
			link.l1.go = "ClockTower_Johan_7";
		break;
		
		case "ClockTower_Johan_7":
			dialog.text = "Sana bir şey daha söyleyeyim. Şu saate bakıyor musun? Avrupa'nın harikası — bizim bu ücra köşede böylesini bulamazsın. Sayın müdür bizzat ilgileniyor onunla.";
			link.l1 = "Belki bir anlaşmaya varabiliriz?";
			link.l1.go = "ClockTower_Johan_8_1";
			link.l2 = "İçeri girebilmek için mutlaka yapabileceğim bir şey vardır, değil mi?";
			link.l2.go = "ClockTower_Johan_8_2";
		break;

		case "ClockTower_Johan_8_1":
			dialog.text = "Rüşvet almam!";
			link.l1 = "Özür dilerim. İyi bir insansın. Adın ne?";
			link.l1.go = "ClockTower_Johan_9";
		break;
		
		case "ClockTower_Johan_9":
			dialog.text = ""+npchar.name+"... Bak... Biliyorum, buralı değilsin. Ama burada bir düzenimiz var. Bay müdür hep der ki: Bir kez zayıflık gösterirsen, kulemiz yerle bir olur. İçeri girmek mi istiyorsun? Şehre yardım et — fark edilirsin.";
			link.l1 = "Anladım. Dikkatli ol, asker.";
			link.l1.go = "ClockTower_Johan_11";
		break;

		case "ClockTower_Johan_8_2":
			dialog.text = "Eh, bilmiyorum. Mynheer direktör Willemstad'ın dostlarını ödüllendirir. Şehre yardım et — fark edilirsin. Buradan olmadığını anlıyorum. Ama burada bir düzenimiz var. Mynheer direktör her zaman der ki: Bir kez zayıflık gösterirsen, kulemiz yerle bir olur.";
			link.l1 = "Anladım. Peki, senin adın ne?";
			link.l1.go = "ClockTower_Johan_10";
		break;
		
		case "ClockTower_Johan_10":
			dialog.text = ""+npchar.name+", "+GetTitle(NPChar,true)+".";
			link.l1 = "Ve ben "+GetTitle(NPChar,false)+" "+GetFullName(pchar)+" . Dikkatli ol, asker.";
			link.l1.go = "ClockTower_Johan_11";
		break;
		
		case "ClockTower_Johan_11":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_1");
		break;
		
		case "ClockTower_Johan_repeat":
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) >= 51)
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"!";
				link.l1 = "Bir şey mi oldu?";
				link.l1.go = "ClockTower_Johan_22";
				Notification_ReputationNation(true, 51, HOLLAND);
			}
			else 
			{
				dialog.text = ""+Greeting(true)+", "+GetTitle(NPChar,true)+". Size nasıl yardımcı olabilirim?";
				link.l1 = "Hayır, "+npchar.name+". Devam et.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_repeat";
				Notification_ReputationNation(false, 51, HOLLAND);
			}
		break;
		
		case "ClockTower_Johan_21":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"!";
			link.l1 = "Bir şey mi oldu?";
			link.l1.go = "ClockTower_Johan_22";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_22":
			dialog.text = "Tebrikler. Bir randevunuz planlandı.";
			link.l1 = "Bir randevu mu? Kiminle?";
			link.l1.go = "ClockTower_Johan_23";
		break;

		case "ClockTower_Johan_23":
			dialog.text = "Mynheer direktörün yardımcısıyla. Şehre yaptığınız yardımı duydu ve beni sizi davet etmekle görevlendirdi.";
			link.l1 = "Ya yönetmenin kendisi?";
			link.l1.go = "ClockTower_Johan_24";
		break;

		case "ClockTower_Johan_24":
			dialog.text = "Uh... Bu konuda sana bir şey söylemeye yetkim yok. Orada bol şans, "+GetTitle(NPChar,true)+".";
			link.l1 = "Teşekkür ederim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower");
		break;
		
		// Диалог с Маартеном Виссером, заместителем директора
		case "ClockTower_Visser_1":
			dialog.text = "DWIC gemi sicil departmanına hoş geldiniz. Kaptan...?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_2":
			dialog.text = ""+GetFullName(NPChar)+",\n"+"Maarten Visser, müdür yardımcısı.\n"+"Willemstad'a oldukça yardımcı olduğunu duydum. Belki bizim ofisimiz de sana yardımcı olabilir.";
			link.l1 = "Bu yüzden buradayım.";
			link.l1.go = "ClockTower_Visser_3_1";
			link.l2 = "Curaçao'nun başkentine hizmet edebildiğim için memnunum.";
			link.l2.go = "ClockTower_Visser_3_2";
		break;

		case "ClockTower_Visser_3_1":
			dialog.text = "Her kaptan — Fransız, İspanyol, Hollandalı — bizden gemi denetimi isteyebilir. Donanımı, topları, teçhizatı inceleriz. Zayıf noktaları bulur, öneriler sunarız";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
		break;

		case "ClockTower_Visser_3_2":
			dialog.text = "Her kaptan — Fransız, İspanyol, Hollandalı — bizden gemi denetimi talep edebilir. Donanımı, topları, teçhizatı inceleriz. Zayıf noktaları bulur, öneriler sunarız";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "ClockTower_Visser_4":
			dialog.text = "Eğer bir denetim yetmezse, yeni gemi belgeleri de temin edebiliriz. Yani, ofisimizin işleri geminizi iyileştirecek — değerli maun ve ipeği harcamadan.";
			link.l1 = "Bu nasıl mümkün olabilir?";
			link.l1.go = "ClockTower_Visser_4_1";
		break;

		case "ClockTower_Visser_4_1":
			dialog.text = "Kaptan, ne kadar kudretli bir yere adım attığının ve bir kalem darbesinin neler başarabileceğinin farkında değilsin.";
			link.l1 = "Altınlar için, öyle mi?";
			link.l1.go = "ClockTower_Visser_5";
		break;

		case "ClockTower_Visser_5":
			dialog.text = "Elbette. Hizmetlerimiz ucuz değildir ve geminizin büyüklüğüne göre değişir. Ama her zaman karşılığını verir. Bizim kapımızdan geçen bir kaptan nadiren başarısız olur\n"+"Ancak, sadece altınınızı almakla kalmıyoruz — aynı zamanda onu kazanmanız için de fırsatlar sunuyoruz. Korsanlar öyle çoğaldı ki, Küçük Antiller'de bile kaptanlar bu belaları kovmak için filolar kurmak zorunda kalıyor. Yok ettiğinize dair kanıt getirin — ve ödemenizi yine o doblonlarla alın.";
			link.l1 = "Ne tür bir kanıt?";
			link.l1.go = "ClockTower_Visser_6";
		break;

		case "ClockTower_Visser_6":
			dialog.text = "Gemi günlükleri. O çapulcular bile bir şekilde kayıt tutmak zorunda — yoksa bir sandal bile düzgünce yönetemezsin. Günlükler, suçun kesin kanıtı olmanın yanında, her zaman arşivlerimizde yer bulur. Sigorta anlaşmazlıklarında da işe yarar\n"+"Hizmetlerimizle ilgileniyorsanız, müşteri listemizde bir yer açıldı — kaptanlarımızdan biri yakın zamanda ortaklığını sonlandırdı. İşi tamamlayın — ve yer sizin olsun.";
			link.l1 = "Neden bu kadar karmaşa? Altınlarım yetmiyor mu?";
			link.l1.go = "ClockTower_Visser_7";
		break;

		case "ClockTower_Visser_7":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+", biz nicelikten çok niteliğe önem veririz. Ofisimizin her müşterisi en iyi hizmeti ve bizzat mynheer müdürün kişisel ilgisini görür. Ve inanın bana, bu, hiç de yoksul sayılmayacak şirketimiz için bile hatırı sayılır bir masrafa mal oluyor. Bir ayda sadece otuz gün olduğuna göre, yalnızca otuz müşteriye hizmet verebiliyoruz.";
			link.l1 = "Ne yapılması gerekiyor?";
			link.l1.go = "ClockTower_Visser_8";
		break;

		case "ClockTower_Visser_8":
			dialog.text = "Beş korsan gemisinin seyir defterini getir — bu, ne kadar etkili olduğunu kanıtlar. Ödül, sahiplerinin ne kadar tehlikeli olduğuna bağlı.";
			link.l1 = "Pekala. Bunu yapacağım.";
			link.l1.go = "ClockTower_Visser_9_1";
			link.l2 = "Bunu düşünmem lazım.";
			link.l2.go = "ClockTower_Visser_9_2";
			link.l3 = "Yönetmenin kendisi nerede?";
			link.l3.go = "ClockTower_Visser_9_3";
		break;

		case "ClockTower_Visser_9_1":
			dialog.text = "Mükemmel. Sonuçları bekliyorum ve ortaklığımızı dört gözle izliyorum.";
			link.l1 = Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_2":
			dialog.text = "Dediğin gibi olsun. Teklifim geçerli. Ama yerin sandığından daha çabuk dolabilir.";
			link.l1 = Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_3":
			dialog.text = "Denizde. Mynheer van Doorn, ofisi yönetmekle amiral gemisine komuta etmeyi bir arada yürütüyor.";
			link.l1 = "Bunu nasıl başarıyor?";
			link.l1.go = "ClockTower_Visser_10";
		break;

		case "ClockTower_Visser_10":
			dialog.text = "Günde on sekiz saat çalışıyor. Yukarıdaki ofiste, burada uyuyor. Uykunun zaman kaybı olduğunu söylüyor. Ona dört saat yetiyor.";
			link.l1 = "Bu devasa saat mekanizmalarının çıkardığı gürültüye ne demeli? Burada insan nasıl uyuyabilir ki?";
			link.l1.go = "ClockTower_Visser_11";
		break;

		case "ClockTower_Visser_11":
			dialog.text = "Onunla bizzat konuşabilecek ve belki de bir şeyler öğrenebileceksin. Müşterilerle konuşmaktan her zaman memnundur. Anlaştık mı?";
			link.l1 = "Mükemmel.";
			link.l1.go = "ClockTower_Visser_12";
			link.l2 = "Tam olarak değil...";
			link.l2.go = "ClockTower_Visser_12";
		break;

		case "ClockTower_Visser_12":
			dialog.text = "İyi günler, "+GetTitle(NPChar,false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;
		
		case "ClockTower_Visser_13_exit":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_2");
		break;
		
		// Йохан спрашивает про журналы
		case "ClockTower_Johan_31":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"! Günlükler yanında mı?";
			link.l1 = "Bakıyorum, iyi bilgilendirilmişsin, "+npchar.name+".";
			link.l1.go = "ClockTower_Johan_32";
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Johan_32":
			if (!CheckAttribute(npchar, "questTemp.ClockTower_Johan_journal"))
			{
				dialog.text = "Ha! Burası ne iskele ne de şehir kapısı, ben de nöbet tutan sıradan bir muhafız değilim, şirketin bir çalışanıyım.";
				npchar.questTemp.ClockTower_Johan_journal = true;
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"! Günlükler yanında mı?";
			}
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "Kütükleri getirdim. Geçmeme izin verecek misin?";
				link.l1.go = "ClockTower_Johan_33";
			}
			link.l2 = "Başka bir zaman.";
			link.l2.go = "ClockTower_Johan_34";
		break;
		
		case "ClockTower_Johan_33":
			dialog.text = "İşe yaradığına sevindim! Devam et, seni bekliyorlar.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower_2");
		break;
		
		case "ClockTower_Johan_34":
			dialog.text = "İyi günler, kaptan bey, "+GetTitle(NPChar,true)+".";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Johan_32";
		break;
		
		case "ClockTower_Visser_21":
			dialog.text = "Kaptan! Geri döndünüz. Günlükleri getirdiniz mi?";
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "Evet. Hepsi beşi.";
				link.l1.go = "ClockTower_Visser_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "Başka bir zaman.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Visser_21";
			}
			// link.l1.go = "ClockTower_Visser_36";	
			
		break;

		case "ClockTower_Visser_22":
			dialog.text = "Mükemmel. Göreyim bakalım onları.\n"+"Evet, her şey yolunda. Bunlar gerçek korsan gemileri. Kaliteli işçilik. Hak ettiğin bu "+SellJournals()+" dublon\nLütfen, alın bunları. Ve buraya da imzanızı atın, lütfen.";
			link.l1 = "Yani, listede ben de varım?";
			link.l1.go = "ClockTower_Visser_23";
			//RemoveItemsFromKPTotal("ClockTower_PirateJournal", 5);	// 
		break;

		case "ClockTower_Visser_23":
			dialog.text = "Neredeyse. Önce evrak işlerini halletmemiz lazım. Birkaç dakikamızı alır\n"+"Tam adınız?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_24";
		break;

		case "ClockTower_Visser_24":
			dialog.text = "Uyruk?";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_25";
		break;

		case "ClockTower_Visser_25":
			dialog.text = "Geminizin adı?";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_26";
		break;

		case "ClockTower_Visser_26":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "Ne tür bir gemi?";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_27";
		break;

		case "ClockTower_Visser_27":
			dialog.text = "Top sayısı?";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_28";
		break;

		case "ClockTower_Visser_28":
			dialog.text = "Mürettebat sayısı?";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_29";
		break;

		case "ClockTower_Visser_29":
			dialog.text = "Güzel. Şimdi buraya imzala. Ve buraya. Buraya da.";
			link.l1 = "Hepsi bu mu?";
			link.l1.go = "ClockTower_Visser_30";
		break;

		case "ClockTower_Visser_30":
			dialog.text = "Neredeyse bitti. Geriye sadece sizi kayda geçirmek kaldı. Tabii ki, bay müdürün sizi şahsen görmesi gerekir... Ama bu sadece bir formalite — yeni müşterileri kabul etme yetkim var\n"+"...Ama yine konudan sapıyorum. Şimdi, tekrar edilebilen hizmetlere gelirsek...\n"+"Sigorta. Pahalıdır, ama şirket tarafından sigortalanan gemilere hiçbir donanma filosu dokunmaz. Liman deposunda istediğin kadar gemi tutabilirsin, koloni kuşatması sırasında onları kaybetmekten korkmana gerek yok\n"+"Gemi denetimi — stratejik malzeme harcamadan tüm özellikleri biraz artırır. Her şeyi inceleyeceğiz: donanım, ambar, mürettebat kamaraları. Tavsiyeler sunarız. Fiyat geminin büyüklüğüne göre değişir\n"+"Kayıtlarımızda yer almak. Karayipler bölgesinde geminizin güvenliğini artırır, böylece ödül avcıları, korsanlar ve askerler size saldırmadan önce iki kez düşünür\n"+"Denetim ve kayıt yalnızca belirli bir gemi için bir kez yapılabilir. Yani parayı harcadıysan, gemine iyi bak. Kaptanlar gemilerini umursamazca kullanıp eldiven değiştirir gibi değiştirdiklerinde, üstlerimin ne kadar sinirlendiğini tahmin bile edemezsin!\n"+"Ama yine konudan sapıyorum. Şimdi tekrarlanabilir hizmetlere gelecek olursak...\n"+"Belge değişimi. Gemilerin farklı uzmanlık alanları olabileceğini biliyorsun. Ama bunun esas olarak geminin nasıl belgelenmiş olduğuna bağlı olduğunu muhtemelen hiç düşünmemişsindir. Savaş geminin kuşatma için belgelenmiş olmasından memnun değilsen, kime başvuracağını biliyorsun\n"+"Zaten korsan gemilerinin günlüklerini getirmenin ödüllerini duymuşsundur... Korsan ne kadar tehlikeliyse, günlüğü için o kadar çok öderiz.";
			link.l1 = "Etkileyici. Şunu söylemeliyim ki, mynheer Visser, ofisiniz gerçekten...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor");
		break;

		case "ClockTower_Visser_31":
			dialog.text = "Amsterdam limanda! Bay müdür geri döndü!";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_31_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
			ClockTower_AmsterdamInTheHarbor_2();
		break;

		case "ClockTower_Visser_31_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_32", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_32":
			dialog.text = "Ne?! Şimdiden mi?! Ama onun üç gün daha dönmemesi gerekiyordu!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_32_add";
		break;

		case "ClockTower_Visser_32_add":
			StartInstantDialog("ClockTower_Johan_clone", "ClockTower_Visser_33", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_33":
			dialog.text = "Mynheer direktör zaten karaya çıktı! Doğruca buraya geliyor!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_33_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
		break;

		case "ClockTower_Visser_33_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_34", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_34":
			dialog.text = "Aman Tanrım... Eğer seni görürse...";
			link.l1 = "Sorun ne? Az önce kendin yeni müşterileri kabul etme yetkin olduğunu söyledin.";
			link.l1.go = "ClockTower_Visser_35";
		break;

		case "ClockTower_Visser_35":
			dialog.text = "Ben de isterim! Ama o hoşlanmaz... Neyse. Kaptan, dışarıda bekleyin. Girişte. Müdür bey sizinle konuşmak isteyecek.";
			link.l1 = "Benimle mi?";
			link.l1.go = "ClockTower_Visser_36";
		break;

		case "ClockTower_Visser_36":
			dialog.text = "Her yeni müşteriyi bizzat inceler. Her zaman. Hadi, çabuk git!";
			link.l1 = "Tomarların karşılığında doblonları geri vermiyorum!";
			link.l1.go = "ClockTower_Visser_36_1";
			link.l2 = "Yazık, dinlemek için kalırdım.";
			link.l2.go = "ClockTower_Visser_36_2";
		break;

		case "ClockTower_Visser_36_1":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;

		case "ClockTower_Visser_36_2":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;
		
		// диалог с Йоханом, после того как мы вышли из башни
		case "ClockTower_Johan_41":
			dialog.text = "...";
			link.l1 = "Ne oldu o, Johan?";
			link.l1.go = "ClockTower_Johan_42";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_42":
			dialog.text = "Mynheer direktör geri döndü.";
			link.l1 = "Bunda bu kadar korkunç olan ne var?";
			link.l1.go = "ClockTower_Johan_43";
		break;

		case "ClockTower_Johan_43":
			dialog.text = "Korkulacak bir şey yok! Sadece... Mynheer müdür sürprizleri sevmez. Her şey plana uygun gitmeli. Ve işte, henüz incelemediği yeni bir müşteri daha.";
			link.l1 = "Maarten, beni kayda geçirme yetkisi olduğunu söyledi.";
			link.l1.go = "ClockTower_Johan_44";
		break;

		case "ClockTower_Johan_44":
			dialog.text = "Hayır, mesele bu değil. Mynheer müdür sadece... şey, her şeyi kendi başına kontrol etmek istiyor. En küçük ayrıntıya kadar. Yoksa her şeyin dağılacağını söylüyor. Göreceksin, şimdi yine saatini dert etmeye başlayacak.";
			link.l1 = "Ne?";
			link.l1.go = "ClockTower_Johan_45";
		break;

		case "ClockTower_Johan_45":
			dialog.text = "Mynheer van Doorn sinirlendiğinde saati durdurur ve onunla oynamaya başlar. Bazen şehir yarım gün boyunca zamansız kalır. Ve bu olur...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_45_1";
		break;

		case "ClockTower_Johan_45_1":
			dialog.text = "Ah... Duydun mu? Başladı.";
			link.l1 = "Patron geri döndü. Her şey eskisi gibi.";
			link.l1.go = "ClockTower_Johan_46_1";
			link.l2 = "Gayet iyi duyuyorum. Maarten'ın canına okuyorlar.";
			link.l2.go = "ClockTower_Johan_46_2";
			iClockSP4PseudoGlobal = ClockTower_PlaySound_rh2("Location/SP4_quest2");
		break;

		case "ClockTower_Johan_46_1":
			dialog.text = "Ne yazık ki, bu artık olağan hale geldi.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_46_2":
			dialog.text = "Bu biraz sert oldu. Bana sorarsan, bu hiç adil değil.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";	
			ChangeCharacterComplexReputation(pchar, "nobility", -2);

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_47":
			dialog.text = "Görünüşe göre ortalık sakinleşti. Yakında seni içeri alacaklar.";
			link.l1 = "Başım belada mı?";
			link.l1.go = "ClockTower_Johan_48";
		break;

		case "ClockTower_Johan_48":
			dialog.text = "Endişelenme. Hiçbir yanlış yapmadın.";
			link.l1 = "Bu içimi rahatlattı.";
			link.l1.go = "ClockTower_Johan_49";
		break;

		case "ClockTower_Johan_49":
			dialog.text = "Hadi ama! Mynheer müdür bazen fazla katı olabiliyor... Ama cömerttir ve naziktir... Bak, görüyor musun?";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_50";
		break;

		case "ClockTower_Johan_50":
			dialog.text = "Ah, sana söylemiştim!";
			link.l1 = "...";
			link.l1.go = "exit";
			ClockTower_VisserComingTowardsUs();
		break;

		case "ClockTower_Visser_37":
			dialog.text = "Bay müdür sizi içeride bekliyor.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VisserComingTowardsUs_2");
			DelLandQuestMark(npchar);
		break;
		
		// Первое знакомство с ван Дорном
		case "ClockTower_VanDoorn_1":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+GetFullName(pchar)+", "+NationName+". Gemin — '"+PChar.Ship.Name+"', "+shipType+". "+GetCannonQuantity(pchar)+" silahlar ve "+GetMaxCrewQuantity(pchar)+" mürettebat.";
			link.l1 = "Her şey tamam.";
			link.l1.go = "ClockTower_VanDoorn_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_VanDoorn_2":
			shipType = XI_ConvertString(GetShipTypeName(npchar));
			dialog.text = "Senin hakkında her şeyi biliyorum ama sen benim hakkımda, Johan'ın dedikodusundan başka hiçbir şey bilmiyorsun, bu haksızlık. Hendrik van Doorn. Hollanda Batı Hindistan Şirketi'nin Karayipler'deki sicil departmanının müdürü. Amsterdam fırkateyninin komutanı. "+shipType+". "+GetCannonQuantity(npchar)+" silahlar ve "+GetMaxCrewQuantity(npchar)+" mürettebat.";
			link.l1 = "Sizinle tanıştığıma memnun oldum.";
			link.l1.go = "ClockTower_VanDoorn_3";
		break;

		case "ClockTower_VanDoorn_3":
			dialog.text = "Beş korsan gemisinin seyir defterini ele geçirdin. Yardımcım sana büyük saygı duydu, seni müşteri kaydına aldı ve ofisimin hizmetleriyle ilgili seni bilgilendirdi\n"+"Ama kabul konusunda son karar her zaman bana ait. Şahsen. Bir görüşmeden sonra. Maarten bir aday önerebilir — o kadar.";
			link.l1 = "Hadi başlayalım.";
			link.l1.go = "ClockTower_VanDoorn_4";
		break;

		case "ClockTower_VanDoorn_4":
			if (!CheckAttribute(npchar, "ClockTower_option"))
			{
				dialog.text = "Hem korsanlarla etkili bir şekilde mücadele eden, hem de hizmetlerimizi karşılayacak kadar ticari açıdan başarılı kaptanlara ihtiyacım var. Bu kriterleri karşılıyor musun?";
			}
			else dialog.text = "";
			if (!CheckAttribute(npchar, "ClockTower_option_1") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				link.l1 = "Mortimer Grimm'i yok ettim. Memento adlı brigantin kaptanıydı.";
				link.l1.go = "ClockTower_VanDoorn_option_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_2") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				link.l2 = "Bence şirketiniz Albert Blackwood'u yenmemi çok takdir etti. Kar gemisi Lady Beth gerçekten zorlu bir rakipti.";
				link.l2.go = "ClockTower_VanDoorn_option_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_3") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				link.l3 = "Fernando de Alamida bir korsan değildi, ama...";
				link.l3.go = "ClockTower_VanDoorn_option_3";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_4") && CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l4 = "Tüm denizcilerin korkulu rüyasını yendim. Bunu bilmelisin.";
				link.l4.go = "ClockTower_VanDoorn_option_4";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_5") && GetCharacterShipClass(PChar) <= 3)
			{
				link.l5 = "Sen az önce gemimi kayıtlara geçirdin. Sence beceriksiz bir kaptan onu bu halde tutabilir miydi?";
				link.l5.go = "ClockTower_VanDoorn_option_5";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_6") && sti(pchar.Money) >= 1000000)
			{
				link.l6 = "Ben gayet iyiyim, Karayipler'de para ağaçta yetişiyor.";
				link.l6.go = "ClockTower_VanDoorn_option_6";
			}
			link.l7 = "Mynheer Visser zaten yetkinliğimi onayladı. Kendi yardımcınızın değerlendirmesi yeterli değil mi?";
			link.l7.go = "ClockTower_VanDoorn_5";
			npchar.ClockTower_option = true;
		break;

		case "ClockTower_VanDoorn_option_1":
			dialog.text = "Grimm mi? Bizim örgütümüz Grimm hakkında hiç şikayet almadı, tam tersi. Ama onun yerine geçen kişi... Kim olduğunu ve aslında Karayiplere hangi amaçla geldiğini biliyorum. Böyle bir kötülüğün zaman aşımı olmaz, ve senin bu suçluyu, ülkemin gerçek düşmanını cezalandırmış olmana sevindim.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_1 = true;
		break;

		case "ClockTower_VanDoorn_option_2":
			dialog.text = "Eğer Cayman olayına dair raporu doğru hatırlıyorsam, o iddiayı doğrulama şansınız olmamıştı. Bana kalırsa durum tamamen net değil, ama zaferiniz kesinlikle yetkin bir işti.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_2 = true;
		break;

		case "ClockTower_VanDoorn_option_3":
			dialog.text = "Ama çok daha kötü birine de dönüşebilirdi, evet gerçekten. Değerli bir düşmandı, gerçi sana değil, nankör üstlerine yenildi. Ben Hollandalıyım, bu yüzden Kastilya ile savaş konusunda ne dediğimi iyi bilirim.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_3 = true;
		break;

		case "ClockTower_VanDoorn_option_4":
			dialog.text = "'"+GetShipName("Uçan Kalp")+"'. Hâlâ şaşırıyorum ki dürüst insanlar o canavar limana girerken kaçışmıyor. Bu hikâyede beni şaşırtan çok şey var, kaptan. Ama bir gün bu da kitaplarımızda yerini bulacak ve tüm gizemini yitirecek. Sana gelince... kendini ölümsüzleştirdin.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_4 = true;
		break;

		case "ClockTower_VanDoorn_option_5":
			dialog.text = "Şaşırırsın. Ama senin durumunda, şüpheye yer yok, bu doğru.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_5 = true;
		break;

		case "ClockTower_VanDoorn_option_6":
			dialog.text = "Ve bu yüzden hiçbir değeri yok. Tabii eğer onlar doblon değilse.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_6 = true;
		break;

		case "ClockTower_VanDoorn_5":
			dialog.text = "\nOfisin hizmetlerinden yararlanmanız onaylandı. Saygın Hollanda Batı Hindistan Şirketi'nin Denizcilik Siciline hoş geldiniz.";
			link.l1 = "Teşekkür ederim.";
			link.l1.go = "ClockTower_VanDoorn_6";
		break;

		case "ClockTower_VanDoorn_6":
			dialog.text = "Bu karşılıklı fayda sağlayan bir işbirliği. Karayipler'deki en iyi hizmetlere erişim kazanırsınız. Biz de güvenilir bir ortak ediniriz.";
			link.l1 = "İyi.";
			link.l1.go = "ClockTower_VanDoorn_7";
		break;

		case "ClockTower_VanDoorn_7":
			dialog.text = "Bekle! Duyuyor musun?";
			link.l1 = "Hiçbir şey duymuyorum.";
			link.l1.go = "ClockTower_VanDoorn_8";
			// sound stops
			i = FindSoundEventId("Location/clocks_mechanism_inside");
			SetSoundEventPauseState(i, true);
			DelEventHandler("NextHour", "Villemstad_BigClock_Above");
		break;

		case "ClockTower_VanDoorn_8":
			dialog.text = "Tam da mesele bu! Sadece bir hafta uzak kalmam yetti...";
			link.l1 = "Bir sorun mu var?";
			link.l1.go = "ClockTower_VanDoorn_9";
		break;

		case "ClockTower_VanDoorn_9":
			dialog.text = "Saatle ilgili. Mekanizmayı kontrol etmem gerek. Özür dilerim. Bu... önemli.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
		break;

		case "ClockTower_VanDoorn_10":
			if (!CheckAttribute(npchar, "ClockTower_question"))
			{
				dialog.text = "Şimdi her şey yolunda görünüyor. Tekrar özür dilerim. Sorularınız var mı?";
				LAi_Fade("", "");
				// sound returns
				i = FindSoundEventId("Location/clocks_mechanism_inside");
				SetSoundEventPauseState(i, false);
				SetEventHandler("NextHour", "Villemstad_BigClock_Above", 0);
			}
			else dialog.text = "Başka soruların var mı?";
			if (!CheckAttribute(npchar, "ClockTower_question_1"))
			{
				link.l1 = "Yardımcınız ofisin hizmetlerini ayrıntılı şekilde açıkladı. Bunların hepsi nasıl mümkün olabiliyor?";
				link.l1.go = "ClockTower_VanDoorn_question_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_2"))
			{
				link.l2 = "İki görevi nasıl birleştiriyorsun? Kaptanlık ve müdürlük?";
				link.l2.go = "ClockTower_VanDoorn_question_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_3"))
			{
				link.l3 = "Bu koşullarda nasıl çalışıyorsun? Saat mekanizmalarının gürültüsü, karanlık ve ağır perdelerle kapatılmış pencereler.";
				link.l3.go = "ClockTower_VanDoorn_question_3";
			}
			link.l4 = "Hayır, zamanınız için teşekkür ederim. Peki ya ofisin hizmetleri?";
			link.l4.go = "ClockTower_VanDoorn_11";
			npchar.ClockTower_question = true;
		break;

		case "ClockTower_VanDoorn_question_1":
			dialog.text = "Burada hiçbir büyü yok, kaptan. Dünyayı kalem ve mürekkep yönetir. Kilise birinin doğumunu, vaftizini, evliliğini ve ölümünü kaydeder. Sadece bir satırı değiştir — ve kaderi değişir. Bir gemi biraz daha karmaşıktır, ama onun için de bir kalem darbesi çok şeyi değiştirir. Saklamayacağım, başardıklarımla gurur duyuyorum. Yine de, daha iyisi olabileceğini biliyorum. Ya defterlere sadece gemileri ve insanları değil, tüm bir dünyayı kaydetseydik?";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_1 = true;
		break;

		case "ClockTower_VanDoorn_question_2":
			dialog.text = "Birinin yapması gerekiyordu. Amsterdam'ın önceki kaptanı, Antigua'dan bir grupla savaşırken öldü. Şirket uygun birini bulamadı. Ben gönüllü oldum. Eğitim aldım. Sınavları geçtim. Yetki belgesi aldım\n"+"Evet, ben zavallı bir kaptanım. Senden çok daha kötüyüm — bu kesin. Ama iyi bir yönetici her şeyi idare edebilir, sadece bir gemiyi değil. Üç kişiye komuta etmeyi öğrenmek zordur. Bunu başardığında, üç bin kişiye de komuta edebilirsin. Ofis, gemi, kasaba, hatta koca bir şirket — sınır yok, yeter ki yetenekli insanları bulup sana vekalet etmelerine güvenebilesin... İşte o son kısmı en zoru. Gerçek lanet bu.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_2 = true;
		break;

		case "ClockTower_VanDoorn_question_3":
			dialog.text = "Ve neredeyse nefes alacak hava yok. Kaptan, insan kendi ortamını kendi yaratır. Burada bana engel olan hiçbir şey ve hiç kimse yok; her şey elimde ve yalnızca bana ve zamana bağlı. Elimden gelse, dış dünyayla sadece kâğıt üzerinden iletişim kurardım. Ne yazık ki bu imkânsız. Üzerinize alınmayın kaptan. Yalnız kalmak, ama yalnız hissetmemek daha iyidir. Ne demek istediğimi anlıyorsanız tabii.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_3 = true;
		break;

		case "ClockTower_VanDoorn_11":
			// pchar.quest.ClockTower.date = rand(27)+1;
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Yalnızca randevu ile müşteri kabul ediyoruz. Sizin randevunuz... "+pchar.quest.ClockTower.date+" "+month+". Belirlenen günde gelmezseniz de sorun değil. Johan ile iletişime geçin, bir sonraki uygun randevuyu size bildirecek.";
			link.l1 = "Neden bu kadar karmaşa?";
			link.l1.go = "ClockTower_VanDoorn_12";
		break;

		case "ClockTower_VanDoorn_12":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Hizmetlerimiz pahalıdır çünkü gerçek mucizeler yaratır ve müşterilerimize büyük fayda sağlarız. Çıkar çatışması ihtimali yoktur; bu yüzden, belirli bir kişiye hizmet etmek için tüm bir iş gününü ayırıyoruz. Bir sonraki uygun tarihiniz: "+pchar.quest.ClockTower.date+" "+month+"\n"+"Eğer Visser'i görürsen... Maarten adaylığını önermekle doğru yaptı. Lütfen bu mesajı ilet. O iyi bir yardımcı. Bundan şüphesi olmasın.";
			link.l1 = "İyi.";
			link.l1.go = "ClockTower_VanDoorn_13";
		break;

		case "ClockTower_VanDoorn_13":
			dialog.text = "Günaydın, "+GetTitle(NPChar,false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VanDoornInCabinet_3");
		break;
		
		case "ClockTower_Visser_41":
			dialog.text = "Nasıl geçti?";
			link.l1 = "Uzun bir gündü, ama van Doorn kararını onayladı.";
			link.l1.go = "ClockTower_Visser_42";
		break;

		case "ClockTower_Visser_42":
			dialog.text = "Tanrıya şükür. Demek ki her şeyi doğru yapmışım.";
			link.l1 = "Bana, sana iyi bir yardımcı olduğunu söylememi söyledi.";
			link.l1.go = "ClockTower_Visser_43";
		break;

		case "ClockTower_Visser_43":
			dialog.text = "Gerçekten mi? O... bunu mu söyledi?";
			link.l1 = "Evet. Bunu söyledi.";
			link.l1.go = "ClockTower_Visser_44";
		break;

		case "ClockTower_Visser_44":
			dialog.text = "Lanet olsun. Bunu söylememeliydi. Şimdi kendimi nankör bir herif gibi hissedeceğim. Yoksa bunu önceden görüp her şeyi planladı mı?";
			link.l1 = "Sayın müfettiş, birdenbire kendiniz olmaktan çıktınız.";
			link.l1.go = "ClockTower_Visser_45";
		break;

		case "ClockTower_Visser_45":
			dialog.text = "Kaptan, ben bir iş adamıyım, sen de öylesin, o yüzden lafı uzatmadan sadede gelelim.\n"+"Mynheer direktör uzun zamandır bizim için çalışmıyor.";
			link.l1 = "Ne, affedersin?!";
			link.l1.go = "ClockTower_Visser_46";
		break;

		case "ClockTower_Visser_46":
			dialog.text = "Buraya tek bir amaçla, bir sözleşmeyle geldi — gemi sicil departmanını kurmak için. Bunu mükemmel bir şekilde başardı, halefini yetiştirdi, beni terfi ettirdi... ve hepsi bu.";
			link.l1 = "Ne yani, bu kadar mı?";
			link.l1.go = "ClockTower_Visser_47";
		break;

		case "ClockTower_Visser_47":
			dialog.text = "Sözleşmesi çoktan sona erdi. Tam olarak ne zaman olduğunu bilmiyoruz, ama bu adamın artık bu görevi sürdürmeye hakkı olmadığına tamamen eminiz.";
			link.l1 = "Anladım. Bu binanın merkez kanadındaki kodamanlar hemen huzursuzlanıyor.";
			link.l1.go = "ClockTower_Visser_48_1";
			link.l2 = "Anladım. Onun yerini sana bırakmasını beklemekten yoruldun.";
			link.l2.go = "ClockTower_Visser_48_2";
		break;

		case "ClockTower_Visser_48_1":
			dialog.text = "Aynen öyle! Ve bunun için hiçbir şey yapamazlar!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_48_2":
			dialog.text = "Açık konuşacağım. Gerçekten çok yoruldum. Kahretsin, van Doorn beni özellikle sözleşmesi bitince onun yerine geçmem için terfi ettirdi!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_49":
			dialog.text = "Yine de, kendimi kandırılmış hissetsem bile, bu lanetli sandalyeyi onun altından çekmem! Tanrı biliyor, bu adama minnettarım ve ona hayranım!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_50";
		break;

		case "ClockTower_Visser_50":
			dialog.text = "Hayır, efendim. Van Doorn ortak üstlerimizi devirmek istiyor. Şu anda kule duvarının arkasında — tam bu binanın merkezi kanadında — oturanları! Ama onlar bile onu kontrol etmenin bir yolunu bulamıyorlar!";
			link.l1 = "Bunda ne var ki? Van Doorn, Stuyvesant'tan pek de daha önemli sayılmaz.";
			link.l1.go = "ClockTower_Visser_51";
		break;

		case "ClockTower_Visser_51":
			dialog.text = "Bu bir gemi ya da kraliyet sarayı değil, kaptan. Bizim topluluğumuz bambaşka bir tür organizasyon. Böyle değerli birini öylece parmağınızı uzatıp kovamazsınız.\n"+"Öncelikle, van Doorn'un sözleşmesinin aslı kimsenin elinde değil. Yani, onu kovmak için bir gerekçemiz yok. Denersek, avukat ordusunu üstümüze salar, sonunda borçlu çıkan biz oluruz.\n"+"İkincisi, yönetim Amsterdam için van Doorn’a komisyon verdiğinde hata yaptı. Belki kaptan olarak zayıf olabilir, ama tüm bölgede eşi benzeri olmayan bir mürettebat topladı. Emri verin — ve Şirket’in seçkin askerleri gözlerini bile kırpmadan bu binayı ele geçirir.\n"+"Üçüncüsü, karısı ona gerçekten tapıyor. Yıllardır onu görmemiş olması önemli değil. De Witt'in kendi kızı, sevdiği kocası için her şeyi yapabilecek biri. Ve On Yediler Konseyi bunu kabullenmek zorunda kalıyor.\n"+"Bugünkü patlamasına şahit oldunuz, kaptan. Size bir sır vereyim: bu artık giderek daha sık oluyor. Yöneticiler bir gün onları kapı dışarı edeceğinden korkuyor. Ve ellerinden hiçbir şey gelmeyecek, çünkü Amsterdam limanda, van Doorn'un ofisinde değerli bir müşterisi var, evde ise — kayınpederinden, Yedi Birleşik Eyalet Cumhuriyeti'nin Büyük Pansiyoneri'nden destek alıyor!\n"+"Başka bir deyişle, müdürlük yardımınız için size oldukça cömertçe ödeme yapacak. Ve gemi sicil ofisindeki ayrıcalıklarınızı koruyacak.";
			link.l1 = "Etkileyici. Gerçekten de tam bir iş adamısın, Maarten. Bana ihaneti, ofisinin hizmetlerini satarken gösterdiğin profesyonellikle satıyorsun.";
			link.l1.go = "ClockTower_Visser_57";
		break;

		case "ClockTower_Visser_57":
			dialog.text = "Van Doorn'un bizzat sana pazarlık sanatını öğrettiği ve söylediklerine gerçekten inandığın zaman, bu hiç de zor değil.";
			link.l1 = "Benden ne istiyorsun?";
			link.l1.go = "ClockTower_Visser_58";
		break;

		case "ClockTower_Visser_58":
			dialog.text = "Bunu ancak bir yabancı yapabilir. Gece ofise gizlice gir ve orada van Doorn'un orijinal sözleşmesini bul. Kapıların açık olmasını sağlayacağım.";
			link.l1 = "Neden kendin yapmıyorsun? Ve beni durduran ne, hemen şimdi gidip amirine her şeyi anlatmamı engelleyen ne?";
			link.l1.go = "ClockTower_Visser_59";
		break;

		case "ClockTower_Visser_59":
			dialog.text = "Çünkü van Doorn, gece saatlerinde şirket çalışanları dışında herkesi kabul etme alışkanlığına sahip. Bu yüzden bu kuleden alışılmadık bir saatte çıkarken kimse şaşırmayacak.";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_60";
		break;

		case "ClockTower_Visser_60":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Tehdidine gelince... Artık yönetmene ulaşamazsın, başka bir günün planlandı. "+pchar.quest.ClockTower.date+" "+month+", değil mi? O zamana kadar haberin aciliyeti biraz azalmış olacak. Hem, müdür asla muhbirlere ödül vermez. Ve her zaman çalışanlarını korur.";
			link.l1 = "Sana uygun.";
			link.l1.go = "ClockTower_Visser_61";
		break;

		case "ClockTower_Visser_61":
			dialog.text = "Bu ihanet değil, kaptan. Sadece sözleşmeye sadık kalmak ve şirketi korumak istiyoruz. Ayrıca, bu arada senin de çok yardımcı olduğun Willemstad’ı.";
			link.l1 = "Düşüneceğim. Ama hiçbir şey için söz vermiyorum.";
			link.l1.go = "ClockTower_Visser_62";
		break;

		case "ClockTower_Visser_62":
			dialog.text = "Senden daha fazlasını istemem, kaptan. Her şeyden önce, sen bizim müşterimizsin. Sonuç ne olursa olsun, seni bulup ofisin kayıtlarına geçirenin ben olmamdan büyük gurur duyuyorum.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_63";
		break;

		case "ClockTower_Visser_63":
			dialog.text = "Beni her zaman merkezi kanatta bulabilirsin. İyi günler.";
			link.l1 = "Yeniden görüşene dek.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Quest_3");
		break;
		
		case "ClockTower_Visser_64":
			dialog.text = "Merhaba, "+GetTitle(NPChar,false)+"  Bir haber var mı? ";
			link.l1 = "Henüz bir şey yok.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_64";
		break;
		
		case "ClockTower_Johan_51":
			if (GetHour() >= 6 && GetHour() < 24)
			{
				if (pchar.quest.ClockTower.date <= GetDataDay())
				{
					NextMonth = GetDataMonth() + 1;
					if (NextMonth == 13) NextMonth = 1;
				}
				else NextMonth = GetDataMonth();
				Month = XI_ConvertString("MonthGen_" + NextMonth);
				if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+", bugün senin günün. Lütfen, devam et.";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
						
						ClockTower_RightDay();
					}
					else
					{
						dialog.text = "Günaydın, "+GetTitle(NPChar,false)+"!";
					}
				}
				else
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+", başka bir gün bekleniyorsunuz. Sizi görmekten memnuniyet duyarız: "+pchar.quest.ClockTower.date+" "+month+".";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					}
					else
					{
						dialog.text = "Günaydın, "+GetTitle(NPChar,false)+"!";
					}
				}
				link.l1 = "Teşekkür ederim, Johan.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_51";
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeatnight"))
				{	// первая ночная встреча с Йоханом
					dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+", oldukça geç kaldınız. Ofis kapalı.";
					link.l1 = "Merhaba, "+npchar.name+". Geceleri bile çalıştığını duydum.";
					link.l1.go = "ClockTower_Johan_52";
					npchar.ClockTower_repeatnight = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = ""+TimeGreeting()+", "+GetTitle(NPChar,false)+"!";
					link.l1 = "";
					link.l1.go = "ClockTower_Johan_53";
				}
			}
		break;
		
		case "ClockTower_Johan_52":
			dialog.text = "Doğru. Her türlü insan uğrar buraya. Hatta bazen rahipler bile gelir, heh-heh. Ama önce hepsi benimle karşılaşmak zorunda. Ve seninle ilgili bana hiçbir talimat gelmedi.";
			link.l1 = "Bekle, burada gece gündüz nöbet mi tutuyorsun? Bu nasıl mümkün olabilir?";
			link.l1.go = "ClockTower_Johan_53";
		break;

		case "ClockTower_Johan_53":
			if (!CheckAttribute(npchar, "ClockTower_repeatnight_2"))
			{
				dialog.text = "Evet. Beyefendi müdür az önce emri verdi. Nasıl başarıyor bilmiyorum ama yine de hem dinlenmeye hem de göreve vakit bulabiliyorum. Üstelik maaşımı da artırdılar — şikayet edemem!";
				npchar.ClockTower_repeatnight_2 = true;
			}
			else
			{
				dialog.text = "Başka bir şey?";
			}
			if (!CheckAttribute(pchar, "questTemp.ClockTower_NightFree"))
			{
				link.l1 = "Beni geçirmelisin. Şirketin üst yönetimi için çalışıyorum.";
				link.l1.go = "ClockTower_Johan_54";
				link.l2 = "(Öldür onu)";
				link.l2.go = "ClockTower_Johan_KillHim";
			}
			link.l3 = "Devam et, asker.";
			link.l3.go = "ClockTower_Johan_NightExit";
		break;
		
		case "ClockTower_Johan_KillHim":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_KillToJohan");
		break;
		
		case "ClockTower_Johan_NightExit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_Johan_51";
		break;
		
		case "ClockTower_Johan_54":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				dialog.text = "Ee. Benden ne istiyorsun, kaptan? Ben sadece sıradan bir askerim, hiçbir şey bilmiyorum.";
				link.l1 = "Her şeyi biliyorsun, Johan. Bu kadar mütevazı olma. Yüksek makamlardaki beyler sana rapor vermiyor olabilir, ama aralarındaki husumeti mutlaka duymuşsundur.";
				link.l1.go = "ClockTower_Johan_55";
				Notification_Skill(true, 80, SKILL_LEADERSHIP);
			}
			else
			{
				dialog.text = "Ben küçük bir adamım, ama doğrudan amirimden üstün birine gitmem. Özür dilerim, "+GetTitle(NPChar,true)+".";
				link.l1 = "Bu konuşmaya geri döneceğiz.";
				link.l1.go = "ClockTower_Johan_NightExit";
				Notification_Skill(false, 80, SKILL_LEADERSHIP);
			}
		break;
		
		case "ClockTower_Johan_55":
			Achievment_Set("ach_CL_197");
			dialog.text = "Bu doğru, "+GetTitle(NPChar,true)+". Mynheer direktör fazla kaldı. Bir fırtına yaklaşıyor.";
			link.l1 = "Tam olarak ne duydun?";
			link.l1.go = "ClockTower_Johan_56";
		break;
		
		case "ClockTower_Johan_56":
			dialog.text = "Herkes korkuyor ki, bugün değilse yarın, iktidarı ele geçirecek. Bizim bu küçük kasabamız için fazla büyük bir adam. Denetimleriyle herkesi boğuyor, her imzayı kendisinden geçirmek istiyor\nAçıkça söyleyeyim, sen de kendin gördün: Amsterdam limana her yanaştığında — hemen kötü bir gerginlik baş gösteriyor.";
			link.l1 = "Bunu çözebilirim, ama bunun için beni geçirmelisin.";
			link.l1.go = "ClockTower_Johan_57";
		break;

		case "ClockTower_Johan_57":
			dialog.text = "Devam et, "+GetTitle(NPChar,true)+". Yalnız senden bir ricam var, beni mahvetme: eğer bay müdür öğrenirse, başım gider, üstelik bakmam gereken bir ailem var.";
			link.l1 = "Elimden geleni yapacağım.";
			// if (sti(pchar.reputation.nobility) >= 71) link.l1.go = "ClockTower_Johan_58_hint";
			// else link.l1.go = "ClockTower_Johan_NightSuccess";
			link.l1.go = "ClockTower_Johan_58_hint";
		break;

		case "ClockTower_Johan_58_hint":
			ClockTower_AddBook();
			dialog.text = "Sen iyi bir adamsın, "+GetTitle(NPChar,true)+" . Belki sana yardımcı olabilirim: Müdür bey kitaplardan birinin içinde bir anahtar saklıyor. Ne işe yaradığını bilmiyorum ama belki işine yarar.";
			link.l1 = "Teşekkür ederim, Johan.";
			link.l1.go = "ClockTower_Johan_NightSuccess";
			// if (sti(pchar.reputation.nobility) >= 71) Notification_Reputation(true, 71, "low");
		break;
		
		case "ClockTower_Johan_NightSuccess":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_NightFree");
			NextDiag.CurrentNode = "ClockTower_Johan_51";
			// if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
		break;
		
		case "ClockTower_Peter_50":
			dialog.text = "Dur. Hollanda Batı Hindistan Şirketi arazisindesin. Deniz sicil dairesi ve arşiv. Giriş sadece randevu ile.";
			link.l1 = "Ben "+GetTitle(NPChar,false)+" "+pchar.name+".";
			link.l1.go = "ClockTower_Peter_51";
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_51":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "Randevunuz mu var? Devam edin.";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					
					ClockTower_RightDay();
				}
				else
				{
					dialog.text = "...";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "Randevunuz başka bir güne ayarlandı: "+pchar.quest.ClockTower.date+" "+month+".";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = "...";
				}
			}
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Peter_51";
		break;
		
		case "ClockTower_Visser_71":
			dialog.text = "Merhaba, "+GetTitle(NPChar,false)+" . Bir haber var mı?";
			link.l1 = "Evet. İşte sözleşme.";
			link.l1.go = "ClockTower_Visser_72";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_72":
			dialog.text = "İnanılmaz... Yedi yıl önce süresi dolmuş!";
			link.l1 = "Yani, ihtiyacın olan şey bu muydu?";
			link.l1.go = "ClockTower_Visser_73";
		break;

		case "ClockTower_Visser_73":
			dialog.text = "Aynen öyle! Bu belgeyle şirket onu yasal olarak geri çağırabilir. Hiçbir açık yok. Hiçbir bahane yok. Süresi doldu — nokta.";
			link.l1 = "Sırada ne var?";
			link.l1.go = "ClockTower_Visser_74";
		break;

		case "ClockTower_Visser_74":
			dialog.text = "Kontratı Amsterdam'a göndereceğim. On Yediler Konseyi karar verecek. Doorn'a geri dönmesi emredilecek. Reddetmeye cesaret edemeyecek.";
			link.l1 = "Ya reddederse ne olacak?";
			link.l1.go = "ClockTower_Visser_75";
		break;

		case "ClockTower_Visser_75":
			dialog.text = "O yapamaz. Karısı bir hissedarın, Büyük Pansiyoner'in kızı olabilir, ama onun babası bile Konsey'e karşı çıkmaz. Ve Catharina'nın kendisi... On yıldır bekliyor. Eğer onun dönebileceğini ama geri dönmeyi reddettiğini öğrenirse — bu onu mahveder.";
			link.l1 = "Zalim.";
			link.l1.go = "ClockTower_Visser_76";
		break;
		
		case "ClockTower_Visser_76":
			dialog.text = "Evet. Ama başka çare yok. Teşekkür ederim, kaptan. Önemli bir iş başardınız.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_77";
		break;
		
		case "ClockTower_Visser_77":
			if (CharacterIsAlive("ClockTower_Johan"))
			{
				dialog.text = "Ödülün — beş yüz dublon. Ve sana söz veriyorum: iki ya da üç ay içinde müdür koltuğuna oturduğumda, ofisin tüm hizmetlerine sınırsız erişimin olacak. Ne sıra bekleyeceksin, ne de randevu alacaksın. Ne zaman istersen.";
				AddItems(pchar, "gold_dublon", 500);
			}
			else
			{
				dialog.text = "Ve Johan'ı da öldürdün. Zaten hayranlık duyduğum ve her şeyimi borçlu olduğum birine ihanet ettim. Şimdi bir de bu oldu\n"+"Belki senin geminde insanlar birer odun parçası gibi görülebilir, ama şirket çalışanlarına değer verir. Ve cinayete ortak olmaktan tiksiniyorum\n"+"Altınlarınız Johan'ın ailesine gidecek, ama anlaşmanın ikinci kısmını ben yerine getireceğim\n"+"Sana söz veriyorum: İki ya da üç ay içinde, yönetmen koltuğuna oturduğumda, ofisin tüm hizmetlerine sınırsız erişim hakkı kazanacaksın.";
			}
			link.l1 = "Sözünüze güveniyorum. İyi günler.";
			link.l1.go = "ClockTower_Visser_78";
		break;
		
		case "ClockTower_Visser_78":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_WaitFewMonths");
		break;
		
		case "ClockTower_Visser_79":
			dialog.text = "Merhaba, "+GetTitle(NPChar,false)+" . Henüz bir haber yok. Merak etme, anlaşmamızı unutmadım.";
			link.l1 = "Umarım öyle.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_79";
		break;
		
		case "ClockTower_Visser_81":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+"! Gir, gir. Seni görmek güzel.";
			link.l1 = "Tebrikler, atanmanız hayırlı olsun.";
			link.l1.go = "ClockTower_Visser_82";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_82":
			dialog.text = "Teşekkür ederim. On Yediler Konseyi beklediğimden hızlı karar verdi. Sözleşme yeterli kanıt oldu. Mynheer van Doorn ofisi yönetmekten alındı.";
			link.l1 = "Bunu nasıl karşıladı?";
			link.l1.go = "ClockTower_Visser_83";
		break;

		case "ClockTower_Visser_83":
			dialog.text = "Kaybetmeyi biliyor. Ofisten kişisel eşyalarını topladı ve çıktı. Ama gerçekten kaybetti mi?\n"+"Amsterdam'ın komutasını ona verdiler. Bu konuda şirket kesinlikle hata yaptı. O gemiyi ona o zaman vermemeliydiler.\n"+"Onu hafife aldık. Umarım sonunda işler daha da kötüye gitmez\n"+"Ve bu hepsi değil.";
			link.l1 = "Daha kötü nasıl olabilirdi?";
			link.l1.go = "ClockTower_Visser_84";
		break;

		case "ClockTower_Visser_84":
			dialog.text = "Mynheer van Doorn, sözleşmenin ofisinden kim tarafından alındığını biliyor.";
			link.l1 = "Nasıl?!";
			link.l1.go = "ClockTower_Visser_85";
		break;

		case "ClockTower_Visser_85":
			dialog.text = "Bana öyle bakma! Ona hiçbir şey söylemedim. Kendi başına anladı.";
			link.l1 = "Şimdi ne olacak?";
			link.l1.go = "ClockTower_Visser_86";
		break;

		case "ClockTower_Visser_86":
			dialog.text = "Artık seni bir düşman olarak görüyor. Ama Yedi Birleşik Eyalet Cumhuriyeti'ne tehdit oluşturmadığın sürece — sana dokunmaz\n"+"Van Doorn her zaman kişisel olanla işi birbirinden ayırmayı bilirdi. Soru şu: Sen bunu başarabilir misin?";
			link.l1 = "Ya başaramazsam?";
			link.l1.go = "ClockTower_Visser_87";
		break;

		case "ClockTower_Visser_87":
			dialog.text = "O zaman seni bulur. Ve işini yapar. Ona bir sebep verme.";
			link.l1 = "Deneceğim.";
			link.l1.go = "ClockTower_Visser_88";
		break;

		case "ClockTower_Visser_88":
			dialog.text = "Size iyi günler, "+GetTitle(NPChar,false)+". Ofisimizin... yani benim ofisimin hizmetlerinden istediğiniz zaman yararlanabilirsiniz.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VillemstadStreet");
		break;
		
		case "ClockTower_Johan_61":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+", sizi bekliyorlar. Bay Visser, tüm müşterilerin serbestçe içeri alınmasını emretti. Eski kuralların fazla katı olduğunu söyledi.";
			link.l1 = "Teşekkür ederim, Johan.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_61":
			dialog.text = "İstediğin zaman, mesai saatleri içinde git. Randevu sistemi kaldırıldı.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Helena_1":
			dialog.text = "Bir dakikan var mı?";
			link.l1 = "Senin için — her zaman.";
			link.l1.go = "ClockTower_Helena_2";
		break;

		case "ClockTower_Helena_2":
			dialog.text = "Ah, keşke öyle olsa, kaptanım. Hayatta başka tutkuların var. Mesela şu anda, yakışıklı kafanı benden başka biri meşgul ediyor, değil mi?";
			link.l1 = "...";
			link.l1.go = "ClockTower_Helena_3";
		break;

		case "ClockTower_Helena_3":
			dialog.text = "Ben de öyle düşünmüştüm. Adamımı iyi tanırım. Bir denizcinin heyecanını ise daha da iyi bilirim. O yüzden açıkça söyle, canım\n"+"Saygın Hollanda Batı Hindistan Ticaret Şirketi'nin amiral gemisini ele geçirmek bize neye mal olacak?";
			link.l1 = "van Doorn'un bizzat peşimize düşmesi için, Willemstad'ın düşmanı olmam gerekecek.";
			link.l1.go = "ClockTower_Helena_4";
		break;

		case "ClockTower_Helena_4":
			dialog.text = "Ah, kaptanım... Demek böyle olacak. İlk defa değil, değil mi?";
			link.l1 = "Sanki onaylamıyormuşsun gibi.";
			link.l1.go = "ClockTower_Helena_5";
		break;

		case "ClockTower_Helena_5":
			dialog.text = "Ben sana olduğun gibi âşık oldum. Ve her zaman yanında olacağım. Sadece şunu unutma: Halkının önünde taşıdığın... yani, taşıdığımız sorumluluğun yükünü.";
			link.l1 = "Zaten bunun için Alonso'muz var. O sana hatırlatır.";
			link.l1.go = "ClockTower_Helena_6";
		break;

		case "ClockTower_Helena_6":
			dialog.text = "Yelken açar açmaz, kaptanım.";
			link.l1 = "O halde vakit kaybetmeyelim, sevgilim.";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Mary_1":
			dialog.text = "Charles? Bir şey sormak istiyorum.";
			link.l1 = "Elbette, Mary. Ne oldu?";
			link.l1.go = "ClockTower_Mary_2";
		break;

		case "ClockTower_Mary_2":
			dialog.text = "Ben... Senin için endişeleniyorum, tamam mı. O bakışı tanıyorum. Kafanda kötü bir şeyler var.";
			link.l1 = "Saçmalık. Az önce ne düşündüğümü bile hatırlamıyorum. Sen nereden bileceksin?";
			link.l1.go = "ClockTower_Mary_3";
		break;

		case "ClockTower_Mary_3":
			dialog.text = "Sadece biliyorum! O Amsterdam'ı gördüm, tamam mı. Güzel bir gemiydi. Hem de çok güzel. Ama\n"+"Her şeyi zaten sen kararlaştırdın... Tıpkı önceden olduğu gibi, değil mi?";
			link.l1 = "Van Doorn bizim için bizzat gelecek, ama bunun için Willemstad'ın düşmanı olmam gerekecek.";
			link.l1.go = "ClockTower_Mary_4";
		break;

		case "ClockTower_Mary_4":
			dialog.text = "Buna değer mi, Charles?";
			link.l1 = "Bilmiyorum, Mary.";
			link.l1.go = "ClockTower_Mary_5";
		break;

		case "ClockTower_Mary_5":
			dialog.text = "Mutlu olmanı istiyorum, tamam mı. Ama yine de Alonso'dan seninle konuşup vazgeçirmesini isteyeceğim, tamam mı!";
			link.l1 = "Tam da onun tarzı. Hadi gidelim, sevgilim.";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Girl_End":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Girl_DlgExit");
		break;
		
		case "ClockTower_Alonso_1":
			dialog.text = "Kaptan, konuşmamız lazım.";
			link.l1 = "Dinliyorum.";
			link.l1.go = "ClockTower_Alonso_2";
			link.l2 = "Şimdi değil, Alonso.";
			link.l2.go = "ClockTower_Alonso_2";
		break;

		case "ClockTower_Alonso_2":
			dialog.text = "Bak şimdi, kaptan, ama beni sonuna kadar dinlemen gerekecek. Bu, şey, nasıl desem\n"+"Acil bir mesele — işte bu!\n"+"Demek küçük bir kuş bana, şirketin yöneticilerinden birini bizzat rahat koltuğundan ettiğini söyledi, şimdi de o adam bize kin besliyor ve şık fırkateyniyle peşimize düşmüş.";
			link.l1 = "Bu tam bir abartı.";
			link.l1.go = "ClockTower_Alonso_3";
		break;

		case "ClockTower_Alonso_3":
			dialog.text = "İnsanların dedikodu yapmaya ne kadar meraklı olduğunu bilirsin, kaptan. Bir söylenti bir hafta dolansın — duymadığın kalmaz: van Doorn bir plantasyon sahibinin kızıyla baştan çıkarılmış, Amsterdam’ın tayfası yaşayan ölülerden oluşuyormuş, ambarında da bizzat Cortés’in hazinesi varmış\n"+"Ama ben gerçek durumla daha çok ilgileniyorum. Yani kaptan, kavga çıkacak mı çıkmayacak mı?";
			link.l1 = "...";
			if (CheckPassengerInCharacter(pchar, "Irons")) // Томми
			{
				link.l1.go = "ClockTower_Alonso_4_1";
			}
			else
			{
				link.l1.go = "ClockTower_Alonso_4_5";
			}
		break;
		
		case "ClockTower_Alonso_4_1":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin");
		break;
		
		case "ClockTower_Alonso_4_2":
			dialog.text = "Bu arada, bu acayip eğlenceli olurdu, inkâr etmiyorum! Hollanda amiral gemisi! Ha! O peynir sevenlerin suratlarını hayal edebiliyorum, biz...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_3";
		break;
		
		case "ClockTower_Alonso_4_3":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin_2");
		break;
		
		case "ClockTower_Alonso_4_4":
			dialog.text = "Tommy, kapa çeneni.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_5";
		break;
		
		case "ClockTower_Alonso_4_5":
			dialog.text = "...";
			link.l1 = "Eğer bir kavga çıkacaksa, bu hemen olmaz. Van Doorn intikam peşinde koşmaz, o tür bir adam değildir. Önce Hollandalıları gerçekten kızdırmamız gerekecek.";
			link.l1.go = "ClockTower_Alonso_4_6";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "ClockTower_Alonso_4_6":
			dialog.text = "Sağ ol, kaptan, bu tayfayı rahatlatır.";
			link.l1 = "Ya sen?";
			link.l1.go = "ClockTower_Alonso_5";
		break;
		
		case "ClockTower_Alonso_5":
			dialog.text = "Benim derdim mürettebatı korumak. Hem kendilerinden hem de... eğer elimden gelirse, senden. Zaten ne planladıysan onu yapacaksın.";
			if (CheckPassengerInCharacter(pchar, "Irons")) // Томми
			{
				link.l1 = "...";
				link.l1.go = "ClockTower_Alonso_5_add";
			}
			else
			{
				link.l1 = "Devam et, Alonso.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
			}
		break;
		
		case "ClockTower_Alonso_5_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_6", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;
		
		case "ClockTower_Alonso_6":
			dialog.text = "İspanyol katırı kadar inatçı!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_6_add";
		break;
		
		case "ClockTower_Alonso_6_add":
			StartInstantDialogTurnToNPC("ClockTower_Alonso", "ClockTower_Alonso_7", "Quest\ShipsPack\ClockTower_dialog.c", "Irons");
		break;
		
		case "ClockTower_Alonso_7":
			dialog.text = "Tanrım, neden ben.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_7_add";
		break;
		
		case "ClockTower_Alonso_7_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_8", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;

		case "ClockTower_Alonso_8":
			dialog.text = "Her şeyi gereğinden fazla karmaşıklaştırıyorsun! Kaptan güzel bir gemi istiyor — ona güzel bir gemi bulacağız! Biz tek bir ekibiz!";
			link.l1 = "Devam et, Alonso. Tommy, dışarı çık.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
		break;
		
		// Абордаж Амстердама, перед боем с Ван Дормом
		case "ClockTower_VanDoorn_21":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+GetFullName(pchar)+", "+NationName+". Gemin — '"+PChar.Ship.Name+"', "+shipType+". "+GetCannonQuantity(pchar)+" silahlar ve "+GetMaxCrewQuantity(pchar)+" mürettebat.";
			link.l1 = "Her zamanki gibi keskinsiniz, mynheer müdür.";
			link.l1.go = "ClockTower_VanDoorn_22";
		break;

		case "ClockTower_VanDoorn_22":
			dialog.text = "Artık o unvan bana ait değil — bunu senin çabalarına borçluyum. Ama sakın intikam almak için sana saldırdığımı düşünme. Ben sadece görevimi yapıyordum.\n"+"Ve belli ki bunda başarısız oldum. Zaten başaramazdım da: Sana bir keresinde senden çok daha iyi bir kaptan olduğunu söylemiştim.";
			link.l1 = "Bu yükü kendi başına üstlendin! Sözleşmen yedi yıl önce bitti. Seni eve dönmekten alıkoyan neydi?";
			link.l1.go = "ClockTower_VanDoorn_23";
		break;

		case "ClockTower_VanDoorn_23":
			dialog.text = "Seni aynı şeyi yapmaktan alıkoyan ne? Cevabını biliyorsun, kaptan. Bir hayalin var. Başka bir hayatın yok. Ve kontrolü bırakırsan — her şey çöker.\n"+"Bu bölgeye düzen getirebilirdim. Bitmek bilmeyen şiddet döngüsünü durdurabilirdim. Eğer kontrolümü gevşetmeseydim. Korkumu yenseydim ve çoktan yapmam gerekeni yapsaydım.\n"+"Ama yeterince dramatik olduk. Dövüşçülüğüm de kaptanlığım kadar zayıf, ama adamlarımı seçmeyi iyi bilirim. Kendini bana son görevim yaptın, kaptan. Bugün sicilde iki kaptan eksilecek!";
			if (CheckCharacterItem(PChar, "CatharinaLetter"))
			{
				link.l1 = "Korkudan bahsediyordun. O zaman şu mektubu oku."; // Доступно, если игрок принёс письмо
				link.l1.go = "ClockTower_VanDoorn_24";
			}
			link.l2 = "Sadece bir tane. Savaşa!"; // бой
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_24":
			dialog.text = "Catharina'dan mı?! Nasıl cüret edersin kişisel olanı işle karıştırmaya?!";
			link.l1 = "Gördüğün gibi, mektup hâlâ mühürlü. Bekliyorum.";
			link.l1.go = "ClockTower_VanDoorn_25";
			TakeItemFromCharacter(pchar, "CatharinaLetter");
			pchar.questTemp.ClockTower_GaveCatharinaLetter = true;
		break;

		case "ClockTower_VanDoorn_25":
			dialog.text = "...artık daha fazla bekleyemez... başkasına gidecek... ya dönmezsem?!";
			link.l1 = "Zaten makamını kaybettin. Mürettebatın şu anda ölüyor. Aileni de kaybetmeye hazır mısın?";
			link.l1.go = "ClockTower_VanDoorn_26";
		break;

		case "ClockTower_VanDoorn_26":
			dialog.text = "Böyle olmasın. Kaptan, teslim olmamı kabul ediyor musunuz?";
			link.l1 = "Evet. Defol gemimden."; // Отпускает, повышает честь
			link.l1.go = "ClockTower_VanDoorn_27";
			link.l2 = "Hayır. Bu, mahkuma yapılan son nezaketti. Savaşa!"; // бой
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_27":
			dialog.text = "O halde zaferiniz için tebrikler, Kaptan "+GetFullName(pchar)+" . Bugün kayıtlarda bir kaptan eksik olacak.";
			link.l1 = "...";
			link.l1.go = "ClockTower_cabinPeace";
			GiveItem2Character(PChar, "pistol15");
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE); // нужно два раза, чтобы сработало...
			TakeItemFromCharacter(npchar, "pistol15");
		break;
		
		// Финальный диалог с Маартеном
		case "ClockTower_Visser_101":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+GetFullName(pchar)+". Buraya gelmeye cesaret edeceğini beklemiyordum.";
			link.l1 = "Neden olmasın? Hâlâ senin müşterinim ve ofisin hizmetlerine ihtiyacım var.";
			link.l1.go = "ClockTower_Visser_102";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_102":
			dialog.text = "Hizmetler mi? HİZMETLER Mİ?! Yaptıklarından sonra mı? Sen saygın Hollanda Batı Hindistan Şirketi'nin düşmanısın! Başka bir kaptan senin müşteri yerini alacak!";
			link.l1 = "Pek sanmam. Van Doorn'un evraklarında ne bulduğuma bak.";
			link.l1.go = "ClockTower_Visser_103";
		break;
		
		case "ClockTower_Visser_103":
			dialog.text = "...";
			link.l1 = "Selefiniz, bu belgeyi kullanmayı kendine yediremedi — sandalyesi sallanmaya başladığında bile.";
			link.l1.go = "ClockTower_Visser_104";
			// отдаём Ключ к Маартену Виссеру
			TakeItemFromCharacter(pchar, "Visser_Key");
		break;
		
		case "ClockTower_Visser_104":
			dialog.text = "...";
			link.l1 = "Böyle bir üstün olduğu için şanslısın. Bu tür numaralar yüzünden en iyi ihtimalle yargılanırdın.";
			link.l1.go = "ClockTower_Visser_105";
		break;
		
		case "ClockTower_Visser_105":
			dialog.text = "...";
			link.l1 = "Sen bir iş adamısın. Nereye varmak istediğimi biliyorsun.";
			link.l1.go = "ClockTower_Visser_106";
		break;
		
		case "ClockTower_Visser_106":
			dialog.text = "Senin... Kayıtlardaki yerin geri verildi.";
			link.l1 = "Ah, Maarten. Müdürün yerine geçmek istedin, oysa sana her şeyi vermişti. Seni yargılanmaktan kurtardı ve sana haber vermeye bile gerek duymadı.";
			link.l1.go = "ClockTower_Visser_107";
		break;
		
		case "ClockTower_Visser_107":
			dialog.text = "...";
			link.l1 = "Bu küçük günah seni asla daha yükseğe çıkarmayacak ve seni sürekli bir korku içinde yaşamaya mahkûm edecek.";
			link.l1.go = "ClockTower_Visser_108";
		break;
		
		case "ClockTower_Visser_108":
			dialog.text = "...";
			link.l1 = "Şimdi bu yere zincirlenme sırası sende. Ama van Doorn'un sahip olduğu gibi bir yardımcın kesinlikle olmayacak.";
			link.l1.go = "ClockTower_Visser_109";
		break;
		
		case "ClockTower_Visser_109":
			dialog.text = "Yeter. Beni tamamen bitirmek mi istiyorsun?!";
			link.l1 = "Tam olarak değil. Yeni gemimi kayıtlara geçirmeni istiyorum. Herhangi bir yanlış anlaşılma olmasın.";
			link.l1.go = "ClockTower_Visser_110";
		break;
		
		case "ClockTower_Visser_110":
			dialog.text = "Geminizin adı '"+GetShipName("Amsterdam")+"'. DWIC amiral gemisi. Bu öylece... tekrar kaydedilemez.";
			link.l1 = "Neden olmasın? Kâğıt her şeyi kaldırır. Sistemin böyle işlemiyor mu?";
			link.l1.go = "ClockTower_Visser_111";
		break;
		
		case "ClockTower_Visser_111":
			dialog.text = "Aman Tanrım, ama her şeyin bir sınırı var!";
			link.l1 = "Bu yerin gücüne inanıyorum. Sen de inanmalısın.";
			link.l1.go = "ClockTower_Visser_112";
		break;
		
		case "ClockTower_Visser_112":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_113";
		break;
		
		case "ClockTower_Visser_113":
			dialog.text = "Tam adınız?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_114";
		break;
		
		case "ClockTower_Visser_114":
			dialog.text = "Vatandaşlık?";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_115";
		break;

		case "ClockTower_Visser_115":
			dialog.text = "Geminizin adı ne? ";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_116";
		break;

		case "ClockTower_Visser_116":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "Ne tür bir gemi?";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_117";
		break;

		case "ClockTower_Visser_117":
			dialog.text = "Top sayısı?";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_118";
		break;

		case "ClockTower_Visser_118":
			dialog.text = "Mürettebat sayısı?";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_119";
		break;

		case "ClockTower_Visser_119":
			dialog.text = "Güzel. Şuraya imza at. Buraya da. Bir de buraya.";
			link.l1 = "Hepsi bu mu?";
			link.l1.go = "ClockTower_Visser_120";
		break;
		
		case "ClockTower_Visser_120":
			dialog.text = "Hepsi bu.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Visser_pausa_1");
		break;
		
		case "ClockTower_Visser_121":
			dialog.text = "...";
			link.l1 = "Bir şeyi söylemeyi unuttun.";
			link.l1.go = "ClockTower_Visser_122";
		break;
		
		case "ClockTower_Visser_122":
			dialog.text = "\n"+"Hollanda Batı Hindistan Şirketi'nin saygın Denizcilik Siciline hoş geldiniz.";
			link.l1 = "Tekrar görüşene dek, mynheer direktör.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FINAL");
		break;
		

		//------------------Услуги конторы------------------//
		case "ClockTower_OfficeServices":
			if (npchar.id == "ClockTower_VanDoorn")
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.name+" . Bugün size ve ofisime nasıl yardımcı olabilirim?";
			}
			if (npchar.id == "ClockTower_Visser")
			{
				if (CharacterIsAlive("ClockTower_VanDoorn"))
				{
					dialog.text = "Seni görmek güzel, "+GetTitle(NPChar,false)+"Her zaman hizmetinizdeyim. Bugün sizi ne ilgilendiriyor?";
				}
				else
				{
					dialog.text = "Peki? Bugün ne ilgini çekiyor?";
				}
			}
			link.l1 = "Gemimi denetleyecek misin? Özelliklerini geliştirmek istiyorum.";
			link.l1.go = "ClockTower_OfficeServices_audit"; // Аудит
			link.l2 = "Gemimin uzmanlığından memnun değilim. Yeni belgeler temin edebilir misin?";
			link.l2.go = "ClockTower_OfficeServices_changeTrait"; // Смена документов
			link.l3 = "Gemi kaydımı şirket siciline ekleyecek misin? Korsanlar ve avcılar iki kez düşünsün.";
			link.l3.go = "ClockTower_OfficeServices_buffSpec"; // Занесение в реестр
			if (!CheckAttribute(pchar, "questTemp.ShipInsurance"))
			{
				link.l4 = "Liman deposunda bulunan gemilerimi sigortalamak istiyorum. Şu anki ve gelecektekileri.";
				link.l4.go = "ClockTower_OfficeServices_Insurance"; // Страховка (пропадает после оплаты)
			}
			if(!CheckAttributeEqualTo(npchar, "last_logbook_date", LastSpeakDate()) && ClockTower_JournalsQty() > 0)
			{
				link.l5 = "Korsan kaptanlarının gemi günlüklerini kabul ediyorsun, değil mi?";
				link.l5.go = "ClockTower_OfficeServices_logbook"; // Награда за пиратов (раз в сутки)
			}
			link.l6 = "Belki bugün değil. İyi günler.";
			link.l6.go = "ClockTower_OfficeServices_exit"; // Отказ
		break;

		// --> Аудит
		case "ClockTower_OfficeServices_audit":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "Maliyeti geminin büyüklüğüne bağlı. Hangi gemiden bahsediyoruz?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.Audit")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}
 
			if (n == 0)
			{
				dialog.text = "Ne yazık ki, denetim her bir gemi için yalnızca bir kez sunulan bir hizmettir. Başka bir isteğiniz var mı?";
				link.l1 = "Bunu başka bir zaman yapalım.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "Audit"))
			{
				n = GetAuditShipCost(sld);
				dialog.text = "Bakalım... Bunun bedeli  "+n+" dublon.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Devam et.";
					link.l1.go = "ClockTower_OfficeServices_audit_upgradeShip";
				}
				link.l2 = "Yine de... bunu başka bir zaman yapalım.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "Korkarım reddetmek zorundayım. Kayıtlara göre, geminiz yıllar önce deniz şeytanına gitti ve zamanın böyle bir hayaletini bir kalem darbesiyle geri getirmek mümkün değil. Birlikte çalışabilmemiz için önce onu eski haline getirmeniz gerekecek. Isla Tesoro’da bu işi üstlenecek bir usta olduğu söyleniyor.";
				link.l1 = "Pekala, teşekkürler.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$Gemi zaten yükseltildi";
				link.l1 = "Teşekkür ederim.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetAuditShipCost(sld));
			UpgradeShipAudit(sld);
			dialog.text = "Bitti.";
			link.l1 = "Teşekkür ederim.";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;
		// <-- Аудит

		// --> Улучшение специализации
		case "ClockTower_OfficeServices_buffSpec":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "Maliyeti geminin büyüklüğüne bağlı. Hangi gemiden bahsediyoruz?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.SpecialityUpgrade")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Ne yazık ki, kayıt işlemi her gemi için yalnızca bir kez yapılır. Başka bir isteğiniz var mı?";
				link.l1 = "Bunu başka bir zaman yapalım.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "SpecialityUpgrade"))
			{
				n = GetSpecialityUpgradeShipCost(sld);
				dialog.text = "Bakalım... Bunun maliyeti  "+n+" dublon.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Devam et.";
					link.l1.go = "ClockTower_OfficeServices_buffSpec_upgradeShip";
				}
				link.l2 = "Yine de... bunu başka bir zaman yapalım.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "Ne yazık ki reddetmek zorundayım. Sicile göre, geminiz yıllar önce deniz şeytanına gitti ve zamanın böyle bir hayaleti bir kalem darbesiyle geri alınamaz. Birlikte çalışmadan önce onu eski haline getirmeniz gerekecek. Isla Tesoro’da bu işi üstlenecek bir usta olduğu söyleniyor.";
				link.l1 = "Pekala, teşekkürler.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$Gemi zaten yükseltildi";
				link.l1 = "Teşekkür ederim.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetSpecialityUpgradeShipCost(sld));
			UpgradeShipSpeciality(sld);
			dialog.text = "Bitti.";
			link.l1 = "Teşekkür ederim.";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;
		// <-- Улучшение специализации

		// --> Смена трейта корабля
		case "ClockTower_OfficeServices_changeTrait":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "Maliyeti geminin büyüklüğüne bağlı. Hangi gemiden bahsediyoruz?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				sTemp = "";
				ShipTraitCanBeChanged(sld, &sTemp);
				if (sTemp == "EmptyShip" || sTemp == "QuestCompanion") continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Hm. Limanda hiçbir gemini göremiyorum.";
				link.l1 = "Bunu başka bir zaman yapalım.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_changeTrait_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";

			if (ShipTraitCanBeChanged(sld, &sTemp))
			{
				n = GetChangeShipTraitCost(sld);
				dialog.text = "Bakalım... Bunun bedeli "+n+" dublon.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Devam et.";
					link.l1.go = "ClockTower_OfficeServices_changeTrait_upgradeShip";
				}
				link.l2 = "Yine de... bunu başka bir zaman yapalım.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "QuestSP")
			{
				dialog.text = "Ne yazık ki, bu mümkün değil. Geminiz eşsiz bir parça, efsanelerle dolu. Böyle durumlarda bir kalem darbesi hiçbir işe yaramaz.";
				link.l1 = "Pekala, teşekkürler.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else
			{
				dialog.text = "Ne tür bir uzmanlıktan bahsediyorsun? Gemin her işe yarar, kendine has hiçbir özelliği yok.";
				link.l1 = "Bilmek güzel, teşekkürler.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			// тут можно обработать другие причины отказа, но на данный момент таковых не будет
		break;

		case "ClockTower_OfficeServices_changeTrait_upgradeShip":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
			DialogExit();
			LaunchChangeShipTraitScreen(sld);
		break;
		// <-- Смена трейта корабля

		// --> Страховка
		case "ClockTower_OfficeServices_Insurance":
			n = GetInsuranceCost();
			dialog.text = "Bakalım... Bunun bedeli  "+n+" dublon.";
			if (PCharDublonsTotal() > n)
			{
				link.l1 = "Devam et.";
				link.l1.go = "ClockTower_OfficeServices_Insurance_done";
			}
			link.l2 = "Yine de... bunu başka bir zaman yapalım.";
			link.l2.go = "ClockTower_OfficeServices_exit";
		break;

		case "ClockTower_OfficeServices_Insurance_done":
			pchar.questTemp.ShipInsurance = true;
			RemoveDublonsFromPCharTotal(GetInsuranceCost());
			dialog.text = "Bitti.";
			link.l1 = "Teşekkür ederim.";
			link.l1.go = "ClockTower_OfficeServices_exit";
			Achievment_Set("ach_CL_199");
		break;
		// <-- Страховка
		
		// Награда за пиратов (раз в сутки) -->
		case "ClockTower_OfficeServices_logbook":
			dialog.text = "Kesinlikle doğru. Ödül, günlüklerin sayısına ve sahiplerinin ne kadar tehlikeli olduğuna bağlı.\n"+"Kaç tane kütük getirdin?"link.l1 =""+ClockTower_JournalsQty();
			link.l1.go = "ClockTower_OfficeServices_logbook_1";
		break;
		
		case "ClockTower_OfficeServices_logbook_1":
			dialog.text = "Şirket, çalışmalarınız için size teşekkür ediyor. Size borçlu olduğumuz "+JournalsCost()+" dublon. Lütfen bunları alın ve buraya imza atın"link.l1 ="Teşekkür ederim.";
			link.l1.go = "ClockTower_OfficeServices_exit";
			npchar.last_logbook_date = LastSpeakDate();
			Achievment_Set("ach_CL_199");
		break;
		// <-- Награда за пиратов

		case "ClockTower_OfficeServices_exit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
		break;

		case "ClockTower_cabinFight":
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			ClockTower_CabinFight2();
		break;
		
		case "ClockTower_cabinPeace":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_cabinPeace");
		break;
	}
}

void ClockTower_NoShipInPort(ref link)
{
	dialog.text = "Liman’da gemini göremiyorum.";
	link.l1 = "Bunu başka bir zaman yapalım.";
	link.l1.go = "ClockTower_OfficeServices_exit";
}

int ClockTower_PlaySound_rh2(string name)
{
    float x = stf(loadedLocation.locators.reload.houseO2.x);
    float y = stf(loadedLocation.locators.reload.houseO2.y);
    float z = stf(loadedLocation.locators.reload.houseO2.z);
    return SendMessage(Sound, "lslfff", MSG_SOUND_EVENT_PLAY, name, 0, x, y, z);
}
