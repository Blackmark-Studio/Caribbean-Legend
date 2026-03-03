void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "exit";
		break;
		
		// Родриго Хименес
		case "Himenes_exit":
			dialog.text = "Başka bir şey var mı, Kaptan?";
			link.l1 = "Şimdilik bir şey yok...";
			link.l1.go = "Himenes_exit_1";
		break;
		
		case "Himenes_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
		break;
		
		case "Himenes":
			dialog.text = "Ha-ha-ha! Señor Jesucristo! Koruyucu Santiago'ya şan olsun! Meryem Ana'ya şan olsun! Kurtulduk! Ha-ha-ha!";
			link.l1 = "İspanyollar! Silah başına!";
			link.l1.go = "Himenes_1_1";
			link.l2 = "Merhaba.   Bir sorun yaşadığınızı duydum?   Siz kimsiniz?";
			link.l2.go = "Himenes_2";
		break;
		
		case "Himenes_1_1":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "Ha-ha-ha-ha-ha-ha-ha-ha!";
			link.l1 = "Pekâlâ, tamam, sakin ol. Sadece bir alışkanlık.";
			link.l1.go = "Himenes_2";
		break;
		
		case "Himenes_2":
			dialog.text = "Ha-ha! Señor, benim adım Rodrigo Jimenez. Ben bir haritacıyım ve kaderin cilvesiyle, bu talihsiz insanların el jefe'siyim.";
			link.l1.go = "Himenes_3";
		break;
		
		case "Himenes_3":
			dialog.text = "Biz... buraya bırakıldık. Ama, señor, biz suçlu değiliz! Ha-ha-ha-ha!";
			link.l1 = "Ne var gülünecek?";
			link.l1.go = "Himenes_4";
		break;
		
		case "Himenes_4":
			dialog.text = "Ah... Özür dilerim, señor! Bu benim derdim, çocukluğumdan beri çok heyecanlandığımda gülmeye başlarım. Ha.";
			link.l1 = "Ve lider olarak seni mi seçtiler?.. Peki. İnsanlar durduk yere ıssız adalara ayak basmaz, señor. Açıklamak ister misin? Sana sadece bir şans veriyorum.";
			link.l1.go = "Himenes_5";
		break;
		
		case "Himenes_5":
			string nationManName[4];
			nationManName[0] = "English";
			nationManName[1] = "French";
			nationManName[2] = "If you are seeing this, it's a bug";
			nationManName[3] = "Spaniard";
			dialog.text = "Affedersiniz, adınızı duyamadım efendim. İngiliz misiniz?";
			link.l1 = nationManName[sti(pchar.BaseNation)]+" . Bu o kadar mı önemli? Şimdilik adımı boşverelim.";
			link.l1.go = "Himenes_6";
		break;
		
		case "Himenes_6":
			dialog.text = "Gerçekten de, Katolik İspanyol Kilisesi tarafından sapkın ilan edildiğimiz için, Kutsal Engizisyon'un adaletli mahkemesi önünde hesap vermek zorundayız. İşte bu yüzden milliyetiniz bizim için bu kadar önemli. Bir İspanyol kaptan bizi yerel makamlara teslim etmek zorunda kalırdı. Bir daha böyle bir şeyi atlatamayız! Ha-ha!";
			if (sti(pchar.BaseNation) == SPAIN) dialog.text = "Ha-ha-ha-ha-ha-ha! Şansımız bu kadar işte, zaten kaybedecek bir şeyimiz yok. "+dialog.text;
			link.l1 = "Pekâlâ, neyse ki Engizisyon'un işleri beni ilgilendirmiyor. Ee, ne olmuş? Siz putperest misiniz?";
			link.l1.go = "Himenes_7";
		break;
		
		case "Himenes_7":
			dialog.text = "Hayır, sana yemin ederim! Topluluğumuz elli yıl boyunca görkemli Cadiz şehrinde zanaat ve ticaretle uğraşıyordu. Her şey yolunda gidiyordu, hatta bir gemi ve İmparatorluğumuzun kolonileriyle ticaret yapmak için bir lisans bile aldık. Şimdi anlıyorum ki o zamanlar bir sınırı aştık ve yeni rakiplerimize... ve onların yöntemlerine karşı tamamen hazırlıksızdık.";
			link.l1 = "Avrupa’da biriyle ticaret yapmadın ve bunun sonucunda bütün topluluk Karayipler’de ıssız bir adada mahsur kaldı mı? Ben de kendimi dertli sanıyordum...";
			link.l1.go = "Himenes_8";
		break;
		
		case "Himenes_8":
			dialog.text = "Ne yazık ki, durum böyle. Topluluğumuz, yeni dine geçen ve İspanya'ya geri dönme hakkı verilen Yahudiler tarafından kuruldu. Bu eski hikaye bile suçlamalar ve resmi inceleme için yeterli oldu.";
			link.l1 = "Ve böylece kaçtın...";
			link.l1.go = "Himenes_9";
		break;
		
		case "Himenes_9":
			dialog.text = "Evet! Ha-ha-ha! Kendi gemimizde! Yeni bir yuva ve yeni bir iş kurmak için Curaçao'ya gidiyorduk. Ama Engizisyon'un inatçılığını hafife aldık ve bunun bedelini ağır ödedik. Onların habercisi, buradan çok uzakta olmayan bir yerde bizi yakaladı ve kaptana bizi eve geri götürmesini emretti...";
			link.l1 = "Lanet olsun!";
			link.l1.go = "Himenes_10";
		break;
		
		case "Himenes_10":
			dialog.text = "Daha bitmedi! Ha! Kaptanımız bizi Atlantik'i tekrar geçip geri götürmek ya da en yakın limanda sorumluluğundan kurtulmak istemedi. Ve gerçekten Süleymanvari bir kararla, bize yiyecek verdi, burada karaya çıkardı ve mesele kapandı.";
			link.l1 = "Gerçekten de trajik bir hikaye, bunda hiç şüphe yok. Şöyle özetleyelim: Eve dönemezsin, dost koloniler seni ihbar eder, yabancı limanlar da seni kabul etmez - bu bölgede savaşın sonu yok. Peki, ne yapmayı düşünüyorsun?";
			link.l1.go = "Himenes_11";
		break;
		
		case "Himenes_11":
			dialog.text = "Öyle karamsar bir tablo çizdiniz ki, efendim, ne diyeceğimi bilemiyorum. Sanki bu adadan daha iyi bir yer yokmuş gibi.";
			link.l1 = "Bence öyle değil, daha iyi bir ada var.";
			link.l1.go = "Himenes_12";
		break;
		
		case "Himenes_12":
			dialog.text = "Gerçekten mi? İspanyolca mı?";
			link.l1 = "Bu benim. Kaderin bir cilvesiyle, ıssız bir adada eski bir korsan sığınağı miras kaldı bana. Şimdi orası benim üssüm; burayı büyütmek, adayı keşfetmek ve mümkünse orada bir fabrika kurmak istiyorum.";
			link.l1.go = "Himenes_13";
		break;
		
		case "Himenes_13":
			dialog.text = "Sen korsan mısın?";
			link.l1 = "Evet.";
			link.l1.go = "Himenes_14_1";
			link.l2 = "Hayır.";
			link.l2.go = "Himenes_14_2";
		break;
		
		case "Himenes_14_1":
			dialog.text = "Yeni Dünya! Gerçekten de buradayız. Memlekette korsanların gerçek birer şeytan, insan bile olmadıkları söylenir. Çocukları yerler, kadınlara tecavüz ederler, iyi Katolikleri diri diri yüzerlermiş. Bu doğru mu?";
			link.l1 = "Haftanın gününe bağlı. Bunu başka bir zaman konuşalım. İnsanlar arıyorum. Uzaklarda, medeniyetten uzakta yıllarca yaşamaya istekli, çalışkan ve yetenekli kişiler. Böyle bir şeye ilgin olur mu?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_14_2":
			dialog.text = "Ne yazık ki, zaten bir suçlu olduğuma göre, en azından bir korsan görmeyi isterdim.";
			link.l1 = "Belki böyle bir fırsat yeniden karşına çıkar. Bunu başka bir zaman konuşalım. Birkaç yıl boyunca medeniyetten uzak yaşamaya istekli, çalışkan ve becerikli insanlar arıyorum. Böyle bir şeye ilgin olur mu?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_15":
			dialog.text = "Başka bir çıkış yolumuz yok. Ama aslında bu o kadar da kötü bir seçenek değil. Eğer huzur içinde yaşamamıza ve çalışmamıza izin verirseniz, kabul ederiz. Ve bir gün bizi memleketimize göndereceğinize söz verin! Bize söz verin, efendim, ve adınızı söyleyin...";
			link.l1 = "Ben, Kaptan "+GetFullName(pchar)+", sana söz veriyorum. ?";
			link.l1.go = "Himenes_16";
		break;
		
		case "Himenes_16":
			dialog.text = "Ha-ha! Kurtulduk! Öyle olsun! Biz birkaç aileyiz, yaklaşık 30 kişiyiz. Hepimiz okur yazarız, zanaat ve ticarette ustayız.";
			link.l1 = "Kader kararını verdi... Lütfen gemiye buyurun!";
			link.l1.go = "Himenes_17";
		break;
		
		case "Himenes_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto1", "none", "", "", "", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			IslaMona_TerksHimenesOnBoard();
		break;
		
		case "Himenes_18":
			dialog.text = "Sizinle tanıştığıma memnun oldum, Señor Rodgar. Görünen o ki, bir süre birlikte yaşayıp çalışmak zorunda kalacağız... Aman Tanrım, bu sıcağa nasıl dayanıyorsunuz?";
			link.l1 = "";
			link.l1.go = "Himenes_19";
		break;
		
		case "Himenes_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_14";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_20":
			dialog.text = "Eğer izin verirseniz, ben devreye gireyim: Kaptan, bize yerleşmek ve envanteriyle araziyi hızlıca gözden geçirmek için bir gün verin. Eminim Señor Rodgar'ın bu toprak parçasıyla ilgili birçok fikri vardır. Sanırım iyi bir ekip olacağız.";
			link.l1 = "Gerçekten başka bir seçeneğin yok, Hymenese. Ha-ha!";
			link.l1.go = "Himenes_21";
		break;
		
		case "Himenes_21":
			dialog.text = "Ha-ha-ha-ha-ha-ha!";
			link.l1 = "";
			link.l1.go = "Himenes_22";
		break;
		
		case "Himenes_22":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_23":
			dialog.text = "Evet, Kaptan?";
			link.l1 = "Hymenese, benim için iyi bir haber var mı?";
			link.l1.go = "Himenes_24";
		break;
		
		case "Himenes_24":
			dialog.text = "Kaptan, bu tam bir kabus. Eviniz fena değil tabii ki. Ama onun dışında... Bu kulübelerde, etrafı ot bürümüş halde yaşamak imkansız, bir de Señor Rodgar adanın öbür ucunda ne olup bittiğinden bile habersiz!! İnanılır gibi değil! Ha-ha!";
			link.l1 = "Gerçekten gergin misin, yoksa şu anda buna gülüyor musun?";
			link.l1.go = "Himenes_25";
		break;
		
		case "Himenes_25":
			dialog.text = "Elbette, bu komik! Bunca yıl ne yaptılar ki? Öncelikle birkaç evin inşaatını bitirmemiz ve şu kulübeleri yaşanabilir bir hale getirmemiz gerekiyor. İnsanların düzgün yaşaması lazım ki işlerine dört elle sarılsınlar. Ayrıca korsanlardan adanın tam bir keşfini yapmalarını isteyeceğim. Belki de bu yer sadece taş ve kumdan ibaret değildir. Her şey tamamlandığında, bu toprakla tam olarak ne yapman gerektiğini sana söyleyebilirim.";
			link.l1 = "Harika! Benden ne isteniyor?";
			link.l1.go = "Himenes_26";
		break;
		
		case "Himenes_26":
			AddQuestRecordInfo("IslaMonaData", "1");
			dialog.text = "Evler, mobilyalar ve geçici barınaklar için malzemeler. Her şeyi hesapladım. Al, işte liste.";
			link.l1 = "Etkileyici...";
			link.l1.go = "Himenes_27";
		break;
		
		case "Himenes_27":
			dialog.text = "Gerçekten mi? Efendim, biz katedraller inşa ettik! Asıl bu etkileyici...";
			link.l1 = "Sana inanmak istiyorum! Yeter ki buraya yanlışlıkla bir katedral dikme. Her seferinde buraya bir sürü malzeme taşımam gerekecek mi?";
			link.l1.go = "Himenes_28";
		break;
		
		case "Himenes_28":
			dialog.text = "Hayır, bu malzemeler bir süre idare eder ama yine de ileride bazı şeyleri getirmemiz gerekecek. Gelecekte böyle sıkıntılardan kaçınmak istiyorsan, iki katı malzeme getir.";
			link.l1 = "Pekala, beni ikna ettin. Ne yapabileceğime bakacağım. Bir son tarih var mı?";
			link.l1.go = "Himenes_29";
		break;
		
		case "Himenes_29":
			dialog.text = "Hayır, efendim. Ama sizi gecikmemeniz için nazikçe uyarıyorum - bu, işleri ilerletmek için yapılması gereken bir iş. İnsanların da yaşayacak bir yere ihtiyacı var. Malzemeleri depoya yükleyin ve her şey hazır olduğunda bana mutlaka haber verin. Ah, neredeyse unutuyordum! Adayı keşfetmek için Bay Rodgar'la konuşun.";
			link.l1 = "Kabul!";
			link.l1.go = "Himenes_30";
		break;
		
		case "Himenes_30":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			pchar.questTemp.IslaMona = "stalk";
			AddQuestRecord("IslaMona", "6");
		break;
		
		case "Himenes_31":
			dialog.text = "Kaptan, ne oldu?";
			if (IslaMona_CheckBuild()) // привез товары на стройку
			{
				link.l1 = "Merhaba, Jiménez. Depoyu kontrol et.";
				link.l1.go = "Himenes_32_1";
			}
			else // не привез товары на стройку
			{
				link.l1 = "Merhaba, Jiménez. Adamlarım tüm adayı didik didik aradı. Ne diyorsun?";
				if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_32_2"; // привез еду и лекарства
				else link.l1.go = "Himenes_32_3";
			}
		break;
		
		case "Himenes_32_1":
			IslaMona_RemoveBuild(); // сразу удаляем товары со склада
			dialog.text = "Bu sorumluluğun üstesinden başarıyla geldin! Bir gün Cadiz'e yolun düşerse, gel benim için depo sorumlusu olarak çalış!";
			link.l1 = "Yoldayım! Söylesene dostum, şimdi ne yapacaksın?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_34_1"; // привез еду и лекарства
			else link.l1.go = "Himenes_34_2";
		break;
		
		case "Himenes_32_2":
			dialog.text = "Señor Kaptan, önce barınma ve erzak işini halledelim. Sonra planlarımızı yaparız. Listenizdeki malları depoda bekliyorum.";
			link.l1 = "Pekala, anladım. Önce evler inşa etmemiz ve burayı toparlamamız gerekiyor. Mallar yakında gelecek.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_32_3":
			dialog.text = "Kaptan, önce barınma ve erzak işini halledelim. Planları sonra yaparız. Listenizdeki malları depoda bekliyorum. Korsan arkadaşınız da erzak ve ilaç bekliyor.";
			link.l1 = "Pekala, anladım. Önce evler inşa etmemiz ve burayı toparlamamız gerekiyor. Mallar yakında gelecek. Korsan dostum için de öyle.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_33":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_31";
		break;
		
		case "Himenes_34_1":
			dialog.text = "Bize altı ay verin, Kaptan, burayı tanıyamayacaksınız.";
			link.l1 = "Altı ay sonra burada ne sen, ne yerleşim, ne de malzemeler kalacak mı diyorsun? Görüşürüz!";
			link.l1.go = "Himenes_37"; // все выполнил
		break;
		
		case "Himenes_34_2":
			dialog.text = "Bu haydutla işini hallettikten sonra çalışmaya başlayacağız. Senden erzak ve ilaç istedi, ben de ona katılıyorum – bu makul bir talep.";
			link.l1 = "Sözlerinizi ona ileteceğim.";
			link.l1.go = "Himenes_35";
			AddQuestRecord("IslaMona", "11");
		break;
		
		case "Himenes_35":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_36";
		break;
		
		case "Himenes_36":
			dialog.text = "Peki, Kaptan? Korsanının istediği her şeyi yaptın mı?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food"))
			{
				link.l1 = "Tüm sorunları Rodgar ile çözdüm. Ada keşfi başladı, erzak ve ilaçlar depoda. Şimdi sıra sende.";
				link.l1.go = "Himenes_34_1";
			}
			else
			{
				link.l1 = "Endişelenme, bir yolunu buluruz. Ben hallederim.";
				link.l1.go = "Himenes_35";
			}
		break;
		
		case "Himenes_37":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			DeleteAttribute(pchar, "questTemp.IslaMona.Food");
			pchar.questTemp.IslaMona = "build";
			AddQuestRecord("IslaMona", "12");
			SetFunctionTimerCondition("IslaMona_BuildDone", 0, 0, 180, false);
		break;
		
		case "Himenes_38":
			dialog.text = "Señor Kaptan! Ne düşünüyorsun? Ha-ha-ha?";
			link.l1 = "Çok daha iyi. Rapor ver, Jiménez!";
			link.l1.go = "Himenes_39";
		break;
		
		case "Himenes_39":
			dialog.text = "Artık burada gerçekten yaşayabilirsin! Tüm evleri temizleyip yeniden yaptık, tabii seninkini saymazsak. Çok lüks değil ama Belize’deki evlerimizden de kötü sayılmaz.";
			link.l1 = "Belize uzun zamandır İngiltere'ye ait, Jiménez.";
			link.l1.go = "Himenes_40";
		break;
		
		case "Himenes_40":
			dialog.text = "Bilmiyorum, evler bundan haberdar mı Kaptan, ha ha!";
			link.l1 = "Artık kalacak bir yerin var ve yerleşim yeri de oldukça medeni görünüyor. Sırada ne var?";
			link.l1.go = "Himenes_41";
		break;
		
		case "Himenes_41":
			dialog.text = "Etrafa bak, Señor Janssen ile konuş ve sonra bana geri dön. Adadaki keşif sonuçlarını ve planlarımızı konuşacağız.";
			link.l1 = "Rodgar'a ne zamandır böyle hitap ediyorsun? Hani sürekli didişiyordunuz?";
			link.l1.go = "Himenes_42";
		break;
		
		case "Himenes_42":
			dialog.text = "Ve hâlâ onlara sahibiz. Ama bir şekilde sağlam ilişkiler kurmamız gerekiyor.";
			link.l1 = "Teşekkür ederim, Rodrigo. Yakında döneceğim.";
			link.l1.go = "Himenes_43";
		break;
		
		case "Himenes_43":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload6", "none", "", "", "", 10.0); // возможно будет иной локатор в новой локации
			pchar.questTemp.IslaMona = "village";
		break;
		
		case "Himenes_44":
			dialog.text = "Kaptan. Señor Janssen.";
			link.l1 = "Hadi, ada keşfinin sonuçlarını anlat bana.";
			link.l1.go = "Himenes_45";
		break;
		
		case "Himenes_45":
			dialog.text = "Evet, Kaptan. Bizzat ben ve araştırmacımız bazı yerleri inceledik. Ne diyebilirim ki... Isla Mona fakir, küçük ve oldukça önemsiz bir ada. İnşaat için çok az alan var, arazi engebeli ve zor, neredeyse hiç verimli toprak yok. Üç plaj, bir su basmış mağara, sık çalılıklar, birkaç papağan, bir keçi sürüsü ve biz...";
			link.l1 = "Ciddi misin? Bu adadaki en değerli şeyin bir keçi sürüsü olduğunu mu söylüyorsun?";
			link.l1.go = "Himenes_46";
		break;
		
		case "Himenes_46":
			dialog.text = "Ha-ha-ha-ha! Sorarım tabii, Señor! Ha-ha! Bitirmeme izin vermedin!";
			link.l1 = "";
			link.l1.go = "Himenes_47";
		break;
		
		case "Himenes_47":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_38";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_48":
			dialog.text = "";
			link.l1 = "Pekala, tamam, sakin ol ve işine devam et. Biliyor musun, buraya çok emek verdim.";
			link.l1.go = "Himenes_49";
		break;
		
		case "Himenes_49":
			dialog.text = "Ve bu boşuna değil! Mağarada yeterince tatlı su var, meyve veren ağaçlar yetiştirmek için uygun toprak da mevcut, ayrıca keçi de beslenebilir. Balıkçılık ve yoldaşlarının çabalarıyla yiyecek meselesi çok kısa sürede çözülecek.";
			link.l1 = "Yani, buraya daha fazla yiyecek getirmen gerekmeyecek mi? Fena değil. Umarım burası benim sürekli ilgim olmadan da ayakta kalabilir. Devam edelim.";
			link.l1.go = "Himenes_50";
		break;
		
		case "Himenes_50":
			dialog.text = "Her konuda haklısınız, Señor. Ama haberler bununla bitmiyor! Öncelikle, Señor Rodgar bir meyhane inşa etme fikriyle geldi. Size ne getirecek bilmiyorum ama bu herif kesin bir şeyler çeviriyor.";
			link.l1 = "Sarhoş olmak istiyor, hepsi bu!";
			link.l1.go = "Himenes_51";
		break;
		
		case "Himenes_51":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_40";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_52":
			dialog.text = "İkinci olarak, Valinin Körfezi başta düşündüğümüzden çok daha derin çıktı. Tam teşekküllü bir iskele inşa edebiliriz.";
			link.l1 = "Bunun bana nasıl bir fayda sağlayacağını tam olarak anlamadım ama bu bile güzel bir haber. Hepsi bu kadar değil, değil mi?";
			link.l1.go = "Himenes_53";
		break;
		
		case "Himenes_53":
			dialog.text = "Bocote ağaçlarından oluşan bir koru bulduk. Fabrika için ideal bir yer.";
			link.l1 = "Beni çok mutlu ediyorsun, Rodrigo! Gerçekten harika bir haber bu!";
			link.l1.go = "Himenes_54";
		break;
		
		case "Himenes_54":
			dialog.text = "Şimdilik bu kadar, señor. İleride başka fikirlerimiz de olabilir. Bilirsiniz, en iyi fikirler çalışırken gelir! Ne hakkında bir şey sormak istersiniz?";
			link.l1 = "Bacote'den bahset bana. Kulağa umut verici geliyor.";
			link.l1.go = "Himenes_55";
		break;
		
		case "Himenes_55":
			dialog.text = "Benim tahminime göre, küçük bir fabrika bu değerli ağacı birkaç yıl boyunca çıkarabilir. Rezervler az, ama kaynak stratejik öneme sahip. Adanın ortasında bir alan temizleyip oraya bir depo ile birlikte bir ev inşa edebiliriz. Bu bir başlangıç olur. İnşaat malzemelerine ek olarak, yaklaşık 15 çift kelepçe ve tüfek de gerekecek.";
			link.l1 = "Peki, kelepçelere neden ihtiyacımız var? Ve neden tam olarak on beş tane?";
			link.l1.go = "Himenes_56";
		break;
		
		case "Himenes_56":
			dialog.text = "Zor bir iş bu, señor. Hatta köle işi bile diyebilirim.";
			link.l1 = "Anladım. Heh-heh...";
			link.l1.go = "Himenes_57_1";
			link.l2 = "Aklını mı kaçırdın? Köle sahibi olmam asla!";
			link.l2.go = "Himenes_57_2";
		break;
		
		case "Himenes_57_1":
			dialog.text = "";
			link.l1 = "Peki neden bir tüfeğe ihtiyacımız var? Hem neden sadece bir tane?";
			link.l1.go = "Himenes_59";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Himenes_57_2":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_42";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Himenes_58":
			dialog.text = "Ben korsana katılıyorum, señor. Sizi anlamıyorum, kaptan. Bu bölgenin bütün ekonomisi köle emeğine dayanıyor ve daha uzun yıllar böyle devam edecek. Bizim onlardan ne farkımız var?";
			link.l1 = "Bir karar vereceğim. Bu arada, neden bir tüfeğe ihtiyacın var? Ve neden tam olarak bir tane?";
			link.l1.go = "Himenes_59";
		break;
		
		case "Himenes_59":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_60":
			dialog.text = "Elbette, fabrikanın bakıma ihtiyacı olacak. İnşaatı tamamlandığında, bu ada senin ana ticaret ortağın olduğun bir ekonomiye sahip olacak. Kölelerin yiyeceğini biz sağlayacağız, ama güvenlik ve üretim masrafları sana ait olacak. Yerleşimciler her parti için 20 dublon ve beş şişe şarap alacak. Güvenlik işleri için Señor Janssen ile pazarlık et.";
			link.l1 = "";
			link.l1.go = "Himenes_61";
		break;
		
		case "Himenes_61":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_46";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_62":
			dialog.text = "her ay kırk ölçek. Ve altın geleceğimiz için. Bir gün bizi buradan götüreceksin, sözünü unutma? Yapılan her işin bir karşılığı olmalı, senin doblonlarınla yerleşkedeki avcılara ve zanaatkârlara emeklerinin karşılığını ödeyeceğiz. Böylece ticaretimiz olacak, ticaretle birlikte de – medeniyet!";
			link.l1 = "İşte böyle! Pekâlâ! Şimdilik her şey yeterince inandırıcı görünüyor...";
			link.l1.go = "Himenes_63";
		break;
		
		case "Himenes_63":
			dialog.text = "Başka neyle ilgileniyorsun?";
			link.l1 = "Peki, meyhanenin hikayesi ne? Neden bir tiyatro inşa etmiyorsun?";
			link.l1.go = "Himenes_64";
		break;
		
		case "Himenes_64":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_65":
			dialog.text = "Kaptan, ona ev fikrini beğenmeyeceğinizi söylemiştim. Ama başka çaremiz yok. Şehirdeki en büyük ev sizde... öhöm, giriş katını salona dönüştüreceğiz, masalar ve bir mutfak kuracağız. İçecekleri ve yiyecekleri evin altındaki mahzenlerde saklayacağız. Yemek yapacak ve müzik çalacak insanlar da var. İkinci kat yine size ait olacak, oraya dokunmayacağız. Giriş kattaki tüm eşyalarınızı da kendimiz yukarı taşıyacağız.";
			link.l1 = "Peki. Peki, meyhane bize tam olarak ne sunacak?";
			link.l1.go = "Himenes_66";
		break;
		
		case "Himenes_66":
			dialog.text = "Biraz kültür canlandıracağız ve Karayipler'in tam kalbinde yaklaşık üç yüz kişiyi yedekte tutma şansın olacak.";
			link.l1 = "İlginç... Bunu düşüneceğim.";
			link.l1.go = "Himenes_67";
		break;
		
		case "Himenes_67":
			dialog.text = "Başka ne ilgini çekiyor?";
			link.l1 = "Peki, iskeleye ne dersin?";
			link.l1.go = "Himenes_68";
		break;
		
		case "Himenes_68":
			dialog.text = "Basit. Vali Koyu'ndaki resifleri temizleyeceğiz, işaret lambaları kuracağız ve bir iskele inşa edeceğiz. Señor Janssen, koyda üç gemiyi ya da bir birinci sınıf gemiyi barındırabileceğini söylüyor. Ayrıca, her seferinde sandalını sahilde sürüklemek yerine buraya dönmek senin için çok daha keyifli olacak.";
			link.l1 = "Bu güzel olurdu.";
			link.l1.go = "Himenes_69";
		break;
		
		case "Himenes_69":
			dialog.text = "Ne bilmek istersiniz?";
			link.l1 = "Şimdilik bu kadar. Ne inşa edeceğime karar verdiğimde geri döneceğim.";
			link.l1.go = "Himenes_70";
		break;
		
		case "Himenes_70":
			dialog.text = "Señor Kaptan, bu belgeyi alın. Tüm ayrıntıları defalarca tekrarlamamak için yazma cesaretini gösterdim. İnceleyin, malzemeleri getirin ve görevi başlatın.";
			link.l1 = "Teşekkür ederim, Rodrigo.";
			link.l1.go = "Himenes_71";
		break;
		
		case "Himenes_71":
			DialogExit();
			IslaMona_HouseDialogFin();
		break;
		
		case "Himenes_72": // нода Хименеса строителя и управляющего факторией
			if (CheckAttribute(pchar, "questTemp.IslaMona.RecordPart")) // после защиты Исла Моны - нужно ещё 10 рабов
			{
				dialog.text = "Señor Kaptan, fabrikada çalışacak 10 köleye ihtiyacımız var - söylemiştim, unutmamışsınız değil mi?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 10)
				{
					link.l1 = "Zaten teslim edildi. Onları boşaltın ve üretime başlayın.";
					link.l1.go = "Himenes_plantation_12";
				}
				else
				{
					link.l1 = "Hafızam yerinde. Onları yakında getireceğim.";
					link.l1.go = "Himenes_plantation_14";
				}
				break;
			}
			dialog.text = "Peki, Señor Kaptan, ne dersiniz?";
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Harbour"))
			{
				link.l1 = "Temiz bir koy ve güvenli bir iskele istiyorum. Filom için burası üs olacak.";
				link.l1.go = "Himenes_harbour";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Tavern"))
			{
				link.l2 = "Devam et ve meyhaneyi inşa et. Herkes bunu takdir edecek, ben de burada bir yedek tutabileceğim.";
				link.l2.go = "Himenes_tavern";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Plantation"))
			{
				link.l3 = "Plantasyonu kurmaya başla. Yatırımı geri alma zamanı geldi.";
				link.l3.go = "Himenes_plantation";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation.Slave") && IslaMona_CheckSlave())
			{
				link.l4 = "Rodrigo, en değerli uzmanlar ve ekipman fabrikaya teslim edildi. Artık çalışmaya başlayabilirsin.";
				link.l4.go = "Himenes_plantation_7";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Factory.Part") && sti(pchar.questTemp.IslaMona.Factory.Part) > 0)
			{
				link.l4 = "Rodrigo, demir ağacımı almaya geldim.";
				link.l4.go = "Himenes_bacaut";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Tavern") && pchar.questTemp.IslaMona.Tavern == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Factory") && !CheckAttribute(pchar, "questTemp.IslaMona.Church"))
			{
				link.l5 = "Rodrigo, büyük inşaatımızı bitirdik mi?";
				link.l5.go = "Himenes_church";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "start" && IslaMona_CheckChurch())
			{
				link.l5 = "Rodrigo, kiliseni inşa edelim.";
				link.l5.go = "Himenes_church_10";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "Wait_candles" && IslaMona_CheckCandles())
			{
				link.l5 = "Rodrigo, kilise eşyalarını getirdim.";
				link.l5.go = "Himenes_church_10_3";
			}
			link.l10 = "Şimdilik bir şey yok...";
			link.l10.go = "Himenes_73";
		break;
		
		case "Himenes_harbour":
			if (IslaMona_CheckHarbour())
			{
				dialog.text = "Malzemeler hazır, her şey tamam. İnşaat 4 ay sürecek.";
				link.l1 = "Acelen yok, değil mi! Neyse, bol şans, Rodrigo.";
				link.l1.go = "Himenes_harbour_1";
			}
			else
			{
				dialog.text = "Maalesef depoda yeterli malzeme yok. Lütfen listeyi tekrar kontrol edin.";
				link.l1 = "Ben hallederim.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_tavern":
			if (IslaMona_CheckTavern())
			{
				dialog.text = "Malzemeler hazır, her şey tamam. İnşaat 3 ay sürecek.";
				link.l1 = "Acelen yok, değil mi! Neyse, bol şans, Rodrigo.";
				link.l1.go = "Himenes_tavern_1";
			}
			else
			{
				dialog.text = "Maalesef depoda yeterli malzeme yok. Lütfen listeyi tekrar kontrol edin.";
				link.l1 = "Ben hallederim.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_plantation":
			if (IslaMona_CheckPlantation())
			{
				dialog.text = "Malzemeler hazır, her şey tamam. İnşaat 6 ay sürecek.";
				link.l1 = "Acelen yok, değil mi! İyi şanslar, Rodrigo.";
				link.l1.go = "Himenes_plantation_1";
			}
			else
			{
				dialog.text = "Maalesef depoda yeterli malzeme yok. Lütfen listeyi tekrar kontrol edin.";
				link.l1 = "Ben hallederim.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_73":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_harbour_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveHarbour();
			pchar.questTemp.IslaMona.Harbour = "true";
			SetFunctionTimerCondition("IslaMona_BuildHarbour", 0, 0, 120, false);
		break;
		
		case "Himenes_harbour_2":
			dialog.text = "Hoş geldiniz, Kaptan. Yeni limanınızı nasıl buldunuz?";
			if (stf(environment.time) > 22.0 || stf(environment.time) < 5.0)
			{
				link.l1 = "Karanlık olmuş Rodrigo! Az kalsın övgüyle bahsettiğin iskelenize çarpıyorduk! Bari ışıklandırmışsın, aferin!";
				link.l1.go = "Himenes_harbour_3";
			}
			else
			{
				link.l1 = "Fena değil, Rodrigo! Küçük bir şey gibi görünebilir ama bu tahtaların üzerinden kıyıya yürümek güzel. Ayrıca koyda dolaşmak da kolaylaştı. Demek şimdi bu küçük koya daha fazla gemi sığdırabilirim, öyle mi?";
				link.l1.go = "Himenes_harbour_4";
			}
		break;
		
		case "Himenes_harbour_3":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_51";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_harbour_4":
			sld = characterFromId("Islamona_carpenter");
			sld.portman.info = "true"; // если вдруг до сих пор не говорил об условиях стоянки
			pchar.questTemp.IslaMona.Harbour = "done"; // флаг - пристань построена и сдана
			dialog.text = "Evet, Kaptan. Şunu söylemeliyim ki, bunda bir gurur var. Büyük inşaat projemizle ilgili nasıl ilerlemek istediğinizi bana bildirmekten çekinmeyin.";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && pchar.questTemp.IslaMona.Plantation == "complete") // если пересеклось со сдачей фактории
			{
				link.l1 = "İnşaattan söz açılmışken, benim fabrikam da şimdiye kadar bitmiş olmalı. Doğru mu, Rodrigo?";
				link.l1.go = "Himenes_plantation_2";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Himenes_harbour_5";
			}
		break;
		
		case "Himenes_harbour_5":
			DialogExit();
			IslaMona_HarbourClear();
		break;
		
		case "Himenes_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveTavern();
			pchar.questTemp.IslaMona.Tavern = "true";
			SetFunctionTimerCondition("IslaMona_BuildTavern", 0, 0, 90, false);
		break;
		
		case "Himenes_tavern_2":
			dialog.text = "H-hıçk! Kaptan! Burada kutlama yapıyoruz!";
			link.l1 = "Rodgar. Rodrigo. Ah, kahretsin!";
			link.l1.go = "Himenes_tavern_3";
		break;
		
		case "Himenes_tavern_3":
			dialog.text = "Ne oldu, k-k-kaptan? Duvarların rengini beğenmediniz mi?";
			link.l1 = "Şimdi fark ediyorum ki, ikinizin de adı aynı! Ha-ha-ha! Bir İspanyol ve bir korsan, aynı isme sahip, ıssız bir adada bir meyhane kurmuş ve birlikte içiyorlar; sanki Hint tanrıları herkesi yutacak ve güneş doğana kadar dünya sona erecek! Ha-ha! Ben de sizinleyim!";
			link.l1.go = "Himenes_tavern_4";
		break;
		
		case "Himenes_tavern_4":
			dialog.text = "Ha-ha-ha! Çok doğru! Tam isabet!";
			link.l1 = "Başardım!";
			link.l1.go = "Himenes_tavern_5";
		break;
		
		case "Himenes_tavern_5":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_ReloadTavern();
		break;
		
		case "Himenes_plantation_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemovePlantation();
			pchar.questTemp.IslaMona.Plantation = "true";
			SetFunctionTimerCondition("IslaMona_BuildPlantation", 0, 0, 180, false);
		break;
		
		case "Himenes_plantation_2":
			dialog.text = "Her şey hazır. Gidelim mi? Fabrikanızı size göstereyim.";
			link.l1 = "Önden buyur.";
			link.l1.go = "Himenes_plantation_3";
		break;
		
		case "Himenes_plantation_3":
			DialogExit();
			pchar.questTemp.IslaMona.Plantation.Harbour = "true"; // наложилась сдача пристани и фактории
			IslaMona_PlantationGo();
		break;
		
		case "Himenes_plantation_4":
			dialog.text = "Kaptan, operasyonlara başlamak için neredeyse her şey hazır. İşçiler için konutlar, hammadde deposu, işleme alanı – layıkıyla bir fabrika kuruldu. Ormanda kesim için en umut vadeden ağaçları zaten işaretledik. On beş işçi ve kararlaştırılan malzemeleri – 15 pranga ve tüfek – getirin, işe başlayalım.";
			link.l1 = "Biz mi? Köleleri mi kastediyorsun?";
			link.l1.go = "Himenes_plantation_5";
		break;
		
		case "Himenes_plantation_5":
			dialog.text = "Ha! Köleler kesecek, yerleşimciler işleyecek, korsanlar ise koruyacak. Herkesin işi olacak – ciddi bir işe kalkıştın, Kaptan.";
			link.l1 = "Neredeyse vaat edilmiş topraklar gibi, değil mi. Malları bekle, avlanma vakti benim için geldi.";
			link.l1.go = "Himenes_plantation_6";
		break;
		
		case "Himenes_plantation_6":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Plantation.Slave = "true"; // привезти рабов, кандалы и мушкет для запуска фактории
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "IslaMona_factoria_residence", "sit", "sit1", "IslaMona_PlantationHouse", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5);
			pchar.questTemp.IslaMona.Plantation = "done"; // флаг - фактория построена и сдана
		break;
		
		case "Himenes_plantation_7":
			dialog.text = "Ne yazık... Buradan asla ayrılamayacaklar.";
			link.l1 = "Rodgar... Yani, Rodrigo! Öncelikle, gidebilirler. İkincisi ise, eğer Turks'te başka biriyle karşılaşsaydın, kaderin hiç de daha iyi olmazdı.";
			link.l1.go = "Himenes_plantation_8";
		break;
		
		case "Himenes_plantation_8":
			dialog.text = "Bunu çok iyi biliyorum, Kaptan. Ve bunu unutmadım. Size fabrikanın işleyişinden bahsedeyim. Gelecek aydan itibaren, her ayın on beşinci günü, kırk işlenmiş bacout kütüğü teslim edeceğiz. Elbette, her teslimat için her ay gelmek zorunda değilsiniz - tüm partiler burada, fabrikada sizin için saklanacak ve sizi bekliyor olacak.";
			link.l1 = "Yani, aynı anda birkaç partiyi birden alabiliyor muyum?";
			link.l1.go = "Himenes_plantation_9";
		break;
		
		case "Himenes_plantation_9":
			dialog.text = "Tabii ki makul ölçüde - çok uzun süre ortadan kaybolma. İnsanlar yıllarca ödeme almadan, tek müşterilerinin hayatta olup olmadığını bilmeden çalışmaz. Sanırım altı parti teslimat yaptıktan sonra işleri askıya alacağız.";
			link.l1 = "Hepsini bir seferde mi toplamam gerekiyor? Peki ya fiyatı, bana tekrar hatırlatır mısın?";
			link.l1.go = "Himenes_plantation_10";
		break;
		
		case "Himenes_plantation_10":
			dialog.text = "Evet, hepsi birden. Standart bir bacout kütüğünün fiyatı on dublondur. Ayrıca, her parti için beşer şişe iyi rom ve aynı sayıda şarap şişesi vermeniz gerekecek. Rodgar, böyle fiyatları dünyanın başka hiçbir yerinde bulamayacağınızı söylüyor.";
			link.l1 = "Kesinlikle, katılıyorum! Teşekkürler, Rodrigo. Hadi işe koyulalım!";
			link.l1.go = "Himenes_plantation_11";
		break;
		
		case "Himenes_plantation_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			DeleteAttribute(pchar, "questTemp.IslaMona.Plantation.Slave");
			AddQuestRecordInfo("Unique_Goods", "5");
			IslaMona_RemoveSlave();
		break;
		
		case "Himenes_plantation_12":
			dialog.text = "Harika! Şimdi işimize geri döneceğiz!";
			link.l1 = "İyi.";
			link.l1.go = "Himenes_plantation_13";
		break;
		
		case "Himenes_plantation_13":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_FactoryReActivar(); // запустить факторию
		break;
		
		case "Himenes_plantation_14":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_bacaut":
			dialog.text = "Elbette, kaptan, buyurun. Bir sonraki sevkiyat için şu partiler hazır: "+sti(pchar.questTemp.IslaMona.Factory.Part)+", bu "+sti(pchar.questTemp.IslaMona.Factory.Goods)+" kütükler. Bu yüzden bize borçlusun "+sti(pchar.questTemp.IslaMona.Factory.Dublon)+" dublon, "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" şişe rom, ve "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" şişe şarap, hepsi var mı?";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.IslaMona.Factory.Dublon) && PCharItemsTotal("potionrum") >= sti(pchar.questTemp.IslaMona.Factory.Bottle) && PCharItemsTotal("potionwine") >= sti(pchar.questTemp.IslaMona.Factory.Bottle))
			{
				link.l1 = "Elbette. İşte ödemeniz.";
				link.l1.go = "Himenes_bacaut_1";
			}
			else
			{
				link.l1 = "Görünüşe göre her şey elimde değil. Hemen getireceğim.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_1":
			if (IslaMona_CheckBacautSpace())
			{
				dialog.text = "Mükemmel. Bacout'u fabrikadan deponuza taşıyacağız, oradan dilediğiniz zaman alabilirsiniz.";
				link.l1 = "Harika. Sonraki partiyi hazırla.";
				link.l1.go = "Himenes_bacaut_2";
			}
			else
			{
				dialog.text = "Dur bir dakika, kaptan! Ambarın dolu - hasat edilen tüm bacout'u oraya yükleyemeyeceğiz. Ambarında biraz yer aç, sonra tekrar yanıma gel.";
				link.l1 = "Pekala, onunla ben ilgileneceğim.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_2":
			dialog.text = "Elbette, kaptan!";
			link.l1 = "...";
			link.l1.go = "Himenes_73";
			IslaMona_FactoryTrade();
		break;
		
		case "Himenes_church":
			dialog.text = "Ha! Kaptan, başka bir şey inşa etmek gereksiz bir çılgınlık ve savurganlık olurdu. Yalnızca...";
			link.l1 = "Ne dışında?";
			link.l1.go = "Himenes_church_1";
		break;
		
		case "Himenes_church_1":
			dialog.text = "Kaptan, bunu sormak benim için biraz garip... Zaten buraya hatırı sayılır bir miktar yatırım yaptınız!";
			link.l1 = "Bir genelev mi?";
			link.l1.go = "Himenes_church_2_1";
			link.l2 = "Bir kilise mi?";
			link.l2.go = "Himenes_church_2_2";
		break;
		
		case "Himenes_church_2_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Aziz Santiago adına yemin ederim, fena olmazdı! Ama ilk gecede kadınlarımız orayı yakar, bizi de beraberinde. Hayır kaptan, ben bir kiliseden bahsediyorum. Evet, düzgün evlerimiz ve maaşımız var, deniz ve eğlence, ailelerimiz ve dostlarımız var. Ama yine de bir şey eksik, anlıyor musun?";
			link.l1 = "Hayal edebiliyorum.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_2_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			AddCharacterExpToSkill(pchar, "Defence", 500);
			dialog.text = "Beni hemen anladınız, kaptan. Evet, düzgün bir barınağımız ve maaşımız var, deniz ve eğlence, ailelerimiz ve dostlarımız da yanımızda. Ama yine de bir şeyler eksik, anlıyor musunuz?";
			link.l1 = "Hayal edebiliyorum.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_3":
			dialog.text = "Aynen öyle. Senin yardımın olmadan Tanrı'nın Evini inşa edemeyiz. Böyle bir yer özel olmalı, bu dünyadan farklı olmalı. Bu yüzden de pahalı olmalı. Mumlara, altın külçelere, kehribara ve tabii ki inşaat malzemelerine ihtiyacımız olacak, hem de ucuzlarından değil. Sana hiçbir kazanç getirmeyecek, bu yüzden istemeye bile cesaret edemiyorum.";
			link.l1 = "Yani, buraya bir rahip getirmen mi gerekiyor?";
			link.l1.go = "Himenes_church_4";
		break;
		
		case "Himenes_church_4":
			dialog.text = "Hayır.";
			link.l1 = "Aranızda zaten bir rahip var mı?";
			link.l1.go = "Himenes_church_5";
		break;
		
		case "Himenes_church_5":
			dialog.text = "Hayır, kaptan. Ve sanırım zaten her şeyi anladınız.";
			link.l1 = "Peki, Engizisyon'un kutsal babalarının sizi cezalandırmak için bir sebebi var mıydı? Siz sapkın mısınız?";
			link.l1.go = "Himenes_church_6";
		break;
		
		case "Himenes_church_6":
			dialog.text = "Kanonik hukuka göre, biz en kötü sapkınlarız. Tanrı'yla iletişim kurmak için bu dünyadan bir aracıya ihtiyaç olduğuna inanmıyoruz.";
			link.l1 = "Bu dünyadan mı?";
			link.l1.go = "Himenes_church_7";
		break;
		
		case "Himenes_church_7":
			dialog.text = "Kaptan, biz Satanist değiliz ve topluluğumuz bir tarikat değil. Biz de sizin gibi Hristiyanız, fakat olaylara çok daha geniş bir açıdan bakıyoruz. Bazı çok eğitimli ve saygın insanlara göre, fazlasıyla geniş bir açıdan. Eğer bir gün kalbinizde açıklığa ve anlayışa yer bulursanız, size daha fazlasını anlatırım. Ama şimdilik, sadece bu listeyi alın. Ne olur ne olmaz.";
			link.l1 = "Bunu bana daha önce söylemeliydin, Rodrigo. Bir gün geri dönüp topraklarımda bir cadı ayini ya da yeni bir inancın doğuşunu görmek istemem! Beklerken - kararımı vereceğim.";
			link.l1.go = "Himenes_church_8_1";
			link.l2 = "Etkileyici bir liste. Kutsal babaların neden bu kadar çok paraya ihtiyacı olduğunu anlamaya başlıyorum! Teklifini düşüneceğim, Rodrigo, ve bir karar vereceğim.";
			link.l2.go = "Himenes_church_8_2";
		break;
		
		case "Himenes_church_8_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "";
			link.l1 = "Eğer sonuç olumlu olursa, listedeki tüm malları depoya getiririm ve hazineleri senin için masanın üstüne sererim.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_8_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			dialog.text = "";
			link.l1 = "Eğer sonuç olumlu olursa, listedeki tüm malları depoya getireceğim ve hazineleri senin için masanın üstüne dizeceğim.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_9":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "start";
			AddQuestRecord("IslaMona", "14");
			AddQuestRecordInfo("IslaMonaData", "3");
		break;
		
		case "Himenes_church_10":
			dialog.text = "Tüm topluluğumuz adına size teşekkür ediyorum, kaptan. Buna pişman olmayacaksınız, yemin ederim!";
			link.l1 = "Sadece tamamen berbat bir şey yaparsan pişman olurum.";
			link.l1.go = "Himenes_church_10_1";
		break;
		
		case "Himenes_church_10_1":
			dialog.text = "Kaptan, tüm inşaat malzemeleri stokta! Listede belirtilen lüks eşyaları getirdiğinizde inşaata başlayacağız. Onlar mücevher ve ritüel aletler için kullanılacak. Tekrar çok teşekkür ederiz, Kaptan! Muchas gracias!";
			link.l1 = "Rica ederim!";
			link.l1.go = "Himenes_church_10_2";
		break;
		
		case "Himenes_church_10_2":
			DialogExit();
			IslaMona_RemoveChurch();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "Wait_candles";
			pchar.questTemp.IslamonaChurch.GoldNugget = 50;
			pchar.questTemp.IslamonaChurch.Candle = 100;
			pchar.questTemp.IslamonaChurch.Amber = 30;
			pchar.questTemp.IslamonaChurch.BlueAmber = 1;
		break;
		
		case "Himenes_church_10_3":
			IslaMona_RemoveCandles();
			string sAdd = "";
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Candle"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Candle)+ " candles,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Amber"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Amber)+ " amber,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.GoldNugget"))
			{
				sAdd += " "+ sti(pchar.questTemp.IslamonaChurch.GoldNugget) + " ingots,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.BlueAmber"))
			{
				sAdd += " and one blue amber"
			}
			if(sAdd == "")
			{
				dialog.text = "Çok teşekkür ederim, kaptan! Her şey hazır, inşaata başlıyoruz. İlk hizmet için birkaç aya tekrar gelin. Ah, bir de, üzümler olgunlaştı! Ev yapımı şarap yapacağız, sizin şerefinize bir kutlama ve şölen düzenleyeceğiz!";
				link.l1 = "Bence hepimiz bir kutlamayı hak ediyoruz. İki ay sonra döneceğim.";
				link.l1.go = "Himenes_church_12";
			}
			else
			{
				dialog.text = "Kaptan, hâlâ var "+sAdd+" kaldı.";
				link.l1 = "Tabii, lütfen bana biraz daha zaman ver. Açıkçası, şu mumlar olmasa, hazine gömeceğini sanardım.";
				link.l1.go = "Himenes_church_11";
			}
		break;
		
		case "Himenes_church_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_church_12":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "build";
			AddQuestRecord("IslaMona", "15");
			//IslaMona_RemoveChurch();
			SetFunctionTimerCondition("IslaMona_ChurchComplete", 0, 0, 60, false);
		break;
		
		case "Himenes_church_13":
			dialog.text = "Ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-ha!";
			link.l1 = "Ve ben de o aptalca alışkanlıktan kurtulduğunu sanmıştım.";
			link.l1.go = "Himenes_church_14";
		break;
		
		case "Himenes_church_14":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "that we won't have to sit here for weeks waiting for events to unfold.";
			else sTemp = "that not everyone will have to participate in the battle.";
			dialog.text = "Ha-ha-ha-ha-ha... ha. Ben de öyle düşünmüştüm, kaptan! Rodgar haklı, varlığınız zaten demek oluyor ki, "+sTemp+"";
			link.l1 = "Ne olduğunu zaten biliyorum. Yaralanan var mı?";
			if (GetCharacterIndex("Mirabella") != -1) link.l1.go = "Himenes_church_15";
			else link.l1.go = "Himenes_church_16";
		break;
		
		case "Himenes_church_15":
			DialogExit();
			sld = characterFromId("Mirabella"); 
			sld.dialog.currentnode = "mirabelle_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_16":
			dialog.text = "Bu kadar endişelenme, Rodgar. Bu senin suçun değil, tüfekçiler çok hızlı geldiler. Zaten onları hatlarımızın gerisinde tutamazdık ve hepsini kılıçtan geçirecek zaman da yoktu.";
			link.l1 = "İspanyollar ne olacak?";
			link.l1.go = "Himenes_church_17";
		break;
		
		case "Himenes_church_17":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) // решил проблему самостоятельно
			{
				dialog.text = "Yalnızca üçü bize ulaşabildi, onlardan da sadece biri hayatta kaldı. Kaptanın ta kendisi! Görünüşe bakılırsa, oldukça üst rütbeli bir deniz subayıymış. Ama henüz bize yardımcı olamaz - en az birkaç gün daha yatakta kalması gerekecek. Bu arada kaptan, silah sesleri duyduk ve görünüşüne bakılırsa sen de duymuşsun.";
				link.l1 = "Öyle denebilir. Davetsiz misafirler, böyle beklenmedik bir ziyareti hiç beklemiyorlardı ve kendilerini yeniden denizin içinde buldular.";
				link.l1.go = "Himenes_church_20";
			}
			else
			{
				dialog.text = "Sadece üçü bize ulaşabildi, onlardan da yalnızca biri hayatta kaldı. Kaptanın ta kendisi! Görünüşe göre oldukça ciddi bir deniz subayı. Ama henüz bize yardımcı olamaz - en az birkaç gün daha yatakta kalmak zorunda.";
				if (i >= 50) 
				{
					link.l1 = "Geçen sefer burada nöbette epey adamımı bırakmıştım, yani sizden çok daha fazla olmaları gerekiyordu. Neden hepsini birden denize atıvermediniz?";
					link.l1.go = "Himenes_church_17_1";
				}
				else 
				{
					link.l1 = "Pekâlâ, bu işi çözelim. Plan şöyle: Onları açık bir saldırıya çekip hemen şimdi harekete geçeceğiz. Ertelemenin anlamı yok. Hazırlanın, saçmalı tüfekleri ve misket tüfeklerini alın, korsanlar kapıda olsun, geri kalanlar evde kalsın ve sakince beklesin.";
					link.l1.go = "Himenes_church_18";
				}
			}
		break;
		
		case "Himenes_church_17_1":
			dialog.text = "Başkan, hepsi profesyonel askerler, başlarında da bir komutan var. Bizde ise doğru düzgün silah bile yok. Evet, tabii ki sayı üstünlüğüyle üstesinden gelebilirdik, ama en az iki kat fazla adam kaybederdik, oysa burada her bir kişi değerli ve gerekli.";
			link.l1 = "Pekâlâ, bu işi çözelim. Plan şöyle: Onları açık bir saldırıya çekip hemen şimdi harekete geçeceğim. Ertelemeye gerek yok. Saçmalı tüfekleri ve misketleri hazırlayın, korsanlar kapıda, geri kalan herkes evde kalsın – ve sakın kıpırdamayın.";
			link.l1.go = "Himenes_church_18";
		break;
		
		case "Himenes_church_18":
			dialog.text = "Kaptan, savaşmaya hazırız!";
			link.l1 = "Biliyorum, Rodrigo. Ama bitirmeme izin vermedin: Eğer tek bir düşman bile kapılardan geçmeyi başarırsa, hepiniz her taraftan ona saldırmalısınız. Ve savaş sırasında, bir kurşun ya da bir parça isabet etme ihtimaliniz azalır. Başka sorusu olan var mı?";
			link.l1.go = "Himenes_church_19";
		break;
		
		case "Himenes_church_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_68";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_20":
			dialog.text = "Aferin! Elbette, yurttaşlarının başına böyle bir talihsizlik gelmesi üzücü. Ama bir kez daha bizim tarafımızı tuttuğun için minnettarım.";
			link.l1 = "Kolay olmadı, Rodrigo. Sıradan insanlar bunu ihanet olarak görürdü ve haklı olurlardı.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "Burası benim toprağım, Rodrigo. Kimden olursa olsun, her zaman savunulmalı.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20a":
			dialog.text = "Evet, yaşlı Rodrigo, Cadiz'den ayrılırken Yeni Dünya'da böyle maceralarla karşılaşacağını hiç beklemiyordu.";
			link.l1 = "Bana anlatma. Bazen hâlâ tam olarak aynı şeyleri düşünüyorum.";
			link.l1.go = "Himenes_church_20b";
		break;
		
		case "Himenes_church_20b":
			dialog.text = "Elbette, böyle bir kaderin yoldaşlarınızı bulması talihsiz bir durum. Ama bir kez daha bizim tarafımızı tuttuğunuz için minnettarım.";
			link.l1 = "Kolay olmadı, Rodrigo. Sıradan insanlar bunu ihanet olarak görürdü ve haklı olurlardı.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "Burası benim toprağım, Rodrigo. Kimden olursa olsun, her zaman savunulmalı.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "Anlıyorum, kaptan. O halde, izninizle yokluğunuzda yerleşkemizdeki durum hakkında size kısa bir özet sunayım.";
			link.l1 = "Gerçekten mi? Dur bir dakika... Kaptan?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_20_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			dialog.text = "Anladım, kaptan. O halde, izninizle yokluğunuzda yerleşkemizdeki duruma dair size kısa bir özet sunayım.";
			link.l1 = "Gerçekten mi? Dur bir dakika... Kaptan?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_21":
			dialog.text = "Alınmanı istemedim. Sadece Rodgar o kelimeyi öyle güzel söylüyor ki ben de denemek istedim. Çok... korsanca.";
			link.l1 = " Sorun değil, sadece şaşırdım. Peki burada ne oldu? ";
			link.l1.go = "Himenes_church_22";
		break;
		
		case "Himenes_church_22":
			dialog.text = "Önce kiliseyi inşa ettik. Biraz bekle, içeri gel. Göreceğin bir şey var. Büyük bir iyilik yaptın, kaptan. Sana öyle gelmeyebilir ama Tanrı'yla iletişim kurabilmek bizim için gerçekten çok, çok önemli. Bugünden itibaren Isla Mona'ya yuvamız diyoruz.";
			link.l1 = "Evim, güzel evim mi? Kesinlikle bir göz atacağım. Bunca mumu boşuna mı taşıdım?";
			link.l1.go = "Himenes_church_23";
		break;
		
		case "Himenes_church_23":
			dialog.text = "Boşuna değil! İkincisi, fabrika mahvoldu – tüm iş gücümüzü kaybettik. Yeni bir grup köle getirmen gerekecek. Neyse ki, işin verimliliğini yeniden değerlendirdikten sonra, on kölenin fazlasıyla yeterli olacağına karar verdik. Yani, senin için daha az uğraş olacak.";
			link.l1 = "Peki. Başka bir şey var mı?";
			link.l1.go = "Himenes_church_24";
		break;
		
		case "Himenes_church_24":
			dialog.text = "Kutlama için her şey hazır. Yani, neredeyse: Burayı biraz toparlamamız, o talihsizlerin cesetlerini gömmemiz gerekiyor... Yarın kiliseye gel, başlarız.";
			link.l1 = "Kiliseye mi? Partiye başlamak için tuhaf bir yer. Evlenme teklif etmeyi mi düşünüyorsun, Rodrigo?";
			link.l1.go = "Himenes_church_25";
		break;
		
		case "Himenes_church_25":
			dialog.text = "Ha-ha! Hayır, kaptan, ama bazı kızlarımız buna karşı çıkmazdı. Yapsanız da bize fark etmez.";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && IsOfficer(characterFromId("Mary")))
			{
				link.l1 = "";
				link.l1.go = "Himenes_church_25_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && IsOfficer(characterFromId("Helena")))
				{
					link.l1 = "";
					link.l1.go = "Himenes_church_25_2";
				}
				else
				{
					link.l1 = "Kabul, yarın kiliseye geleceğiz. Tabii ki dua etmek için.";
					if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common") || CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) link.l1.go = "Himenes_church_28";
					else link.l1.go = "Himenes_church_26";
				}
			}
		break;
		
		case "Himenes_church_25_1":
			DialogExit();
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_25_2":
			DialogExit();
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_26":
			dialog.text = "Bir de bir şey daha, kaptan. Kutlamadan önce git ve önce esirle ilgilen. Kararın verilmesi gerekiyor, ve biliyorum ki hangi yolu seçersen de hoşuna gitmeyecek.";
			link.l1 = "Pekala. Hemen şimdi gideceğim.";
			link.l1.go = "Himenes_church_27";
		break;
		
		case "Himenes_church_27":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_factoria", "reload", "reload1", "IslaMona_DefFraPrisoner"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_28":
			DialogExit();
			WaitDate("", 0, 0, 0, 3, 5); //крутим время
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			IslaMona_DefBattleLightClear();
			DoQuestReloadToLocation("IslaMona_town", "quest", "detector1", "");
		break;
		
		case "Himenes_church_29":
			dialog.text = "Herkes burada! Señor, buraya ilk başta ne için geldiğinizi ya da şimdi burayı kendiniz için nasıl gördüğünüzü bilmiyoruz. Bizim için burası önce zorunlu bir sığınaktı, şimdi ise gerçek bir yuvaya dönüştü. Burada sizin denizcileriniz, korsanlarınız ve kaçak İspanyol sapkınlarınız yaşıyor. Dünyanın başka bir yerinde olsak, şimdiye kadar birbirimizin boğazını çoktan keserdik. Ama burada dostuz, birlikte çalışıyor ve hayatın tadını çıkarıyoruz. Isla Mona, hiçbirimiz için bu dünyanın haritasındaki son durak değil, ama belki de hayatımızın en mutlu ve en verimli yıllarını burada geçireceğiz. Ve bu, sizin başarınız, sizin toprağınız ve sizin insanınız. Muchas gracias, "+pchar.name+"!";
			link.l1 = "";
			link.l1.go = "Himenes_church_30";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_30":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_86";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		case "Himenes_church_31":
			dialog.text = "Pekala, pekala. Kaptan, senin için hediyeler topladık – işe yarar ve sadece hoş olan birçok şey. Bazılarını yanımızda getirdik, bazılarını ise kendimiz yaptık. Bu hediyeyi gönül rahatlığıyla kabul et, kalanını ise emeğimizle sana sunacağız.";
			link.l1 = "Teşekkür ederim... Bunu beklemiyordum. Bu yolculuğumda parlak anlar ve insanlığa dair küçük iyilikler öylesine az ki... Bu benim için çok şey ifade ediyor, inan bana.";
			link.l1.go = "Himenes_church_32";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_32":
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "GunEchin", 10);
			TakeNItems(pchar, "slave_01", 10);
			TakeNItems(pchar, "grenade", 10);
			TakeNItems(pchar, "obereg_7", 1);
			TakeNItems(pchar, "purse3", 1);
			TakeNItems(pchar, "jewelry47", 1);
			TakeNItems(pchar, "jewelry52", 1);
			TakeNItems(pchar, "berserker_potion", 1);
			TakeNItems(pchar, "potion5", 10);
			TakeNItems(pchar, "cannabis7", 1);
			dialog.text = "Ve şimdi - işe geri dönelim!";
			link.l1 = "Hayır, şimdi—mehaneye! Rodrigo, hadi gidelim!";
			link.l1.go = "Himenes_church_33_1";
			link.l2 = "Evet, bu harika anın tadını biraz daha çıkaralım.";
			link.l2.go = "Himenes_church_33_2";
		break;
		
		case "Himenes_church_33_1":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_Town", "sit", "sit_base2", "IslaMona_ChurchToTavern"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_33_2":
			DialogExit();
			LAi_SetActorType(pchar);
			ChangeShowIntarface();
			ResetSound();
			SetMusic("music_terrain");
			InterfaceStates.Buttons.Save.enable = false;
			bDisableCharacterMenu = true;
			pchar.GenQuest.FrameLockEsc = true;
			locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 10000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("IslaMona_ChurchTavernExit", 45.0);
		break;
		
		case "Himenes_74":
			dialog.text = "Ha-ha! Hıçk!";
			link.l1 = "Bu arada, artık her şeye ve hiçbir şeye öyle çılgınca gülmeyi neredeyse bıraktığını fark ettim. Karayiplerin temiz havası mı iyi geldi?";
			link.l1.go = "Himenes_75";
		break;
		
		case "Himenes_75":
			dialog.text = "Daha çok Rodgar'ın yozlaştırıcı etkisi diyebilirim. Onu izlerken, her şeyi cehenneme yollamayı öğrendim.";
			link.l1 = "";
			link.l1.go = "Himenes_76";
		break;
		
		case "Himenes_76":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_90";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_77":
			dialog.text = "Oradan birçok saygın insan tanıyorum.";
			link.l1 = "";
			link.l1.go = "Himenes_78";
		break;
		
		case "Himenes_78":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_93";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_79":
			dialog.text = "Hayır, rom içmeye devam edip sana ters ters bakmayı tercih ederim.";
			link.l1 = "";
			link.l1.go = "Himenes_80";
		break;
		
		case "Himenes_80":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_96";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_81":
			dialog.text = "Kaptan! Hık!";
			link.l1 = "Sana da merhaba, Rodrigo. Görüyorum ki hareketli bir akşam geçirmişsin?";
			link.l1.go = "Himenes_82";
		break;
		
		case "Himenes_82":
			dialog.text = "Daha iyi... sorma. Bir ay... içmeyeceğim. Ah. Bir haberim var! Kaptan... aklını başına topladı.";
			link.l1 = "Hayatta kalan tek İspanyol sen misin?";
			link.l1.go = "Himenes_83";
		break;
		
		case "Himenes_83":
			dialog.text = "Hik! Ah! Evet, onu factoría'ya koydular, gözetim altında bir eve.";
			link.l1 = "Peki. Ona gideceğim. Kendini fazla yorma.";
			link.l1.go = "Himenes_84";
		break;
		
		case "Himenes_84":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10); /// ОН ИДЕТ НА ВЫХОД, ПОСТАВИТЬ ПРАВИЛЬНЫЙ ЛОКАТОР
			IslaMona_ChurchSetHispanos();
		break;
		
		case "Himenes_85":
			dialog.text = "Bir güzel yüzdüm, şimdi her şey eskisi gibi iyi! Yaşayacağız ve çalışacağız. Faktoryayı elimden geldiğince ayakta tutmaya çalışacağım. Biraz tamirat, ufak tefek inşaat işleri de yaparım. Belki çocuk sahibi olma meselesini de eşimle konuşuruz.";
			link.l1 = "Hepiniz adına çok mutluyum! Bu çok heyecanlı, pahalı... ve harika bir maceraydı, ve bizim için iyi sonuçlandığına sevindim. Herkese bol şans, ve yelken açanlarımıza daha da fazla şans!";
			link.l1.go = "Himenes_86";
		break;
		
		case "Himenes_86":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_Final", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// солдат в бухте
		case "Capral":
			dialog.text = "Dur! Onbaşı "+GetFullName(npchar)+". Bir çatışma bölgesine indiniz! Hemen kendinizi tanıtın ve burada bulunma amacınızı açıklayın!";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "Onbaşı, geri çekil! "+GetFullName(pchar)+", Fransız Donanması'nın kaptanıyım. Sizi komutanınıza götürmenizi emrediyorum. Emri yerine getirin!";
				link.l1.go = "Capral_1";
			}
			else
			{
				link.l1 = ""+GetFullName(pchar)+",   ' adlı geminin kaptanı "+pchar.ship.name+"Tamamen tesadüfen bu adaya vardım – belki gemiyi onarmak ve tatlı su stoklarını yenilemek için.";
				link.l1.go = "Capral_3";
			}
		break;
		
		case "Capral_1":
			if(IsUniformEquip())
			{
				dialog.text = "Evet, efendim, Kaptan! Lütfen beni takip edin. Sadece rica ediyorum, dikkatli olun! Bu ada haydutlarla dolu.";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Affedersiniz Kaptan. Üniformanız yok, bu yüzden subaylık belgenizi kontrol etmek zorundayım.";
				link.l1 = "Gördün mü? Tatmin oldun mu? Şimdi - acele et ve emri yerine getir, onbaşı!";
			}
			link.l1.go = "Capral_2";
		break;
		
		case "Capral_2":
			DialogExit();
			AddQuestRecord("IslaMona", "16");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 20.0);
		break;
		
		case "Capral_3":
			dialog.text = "Benimle gelmek zorundasınız, Kaptan. Üst subayımız sizinle konuşacak. Bu andan itibaren geminiz Fransız Donanması'nın ihtiyaçları için geçici olarak el konulmuş sayılıyor. Şu anki nöbetçiyi derhal bilgilendirin ve beni takip edin.";
			link.l1 = "Charles Prince gemisini el koymak mı? Sanmıyorum!";
			link.l1.go = "Capral_5";
			link.l2 = "Görünüşe bakılırsa başka seçeneğim yok. Dediğini yapacağım.";
			link.l2.go = "Capral_4";
		break;
		
		case "Capral_4":
			DialogExit();
			AddQuestRecord("IslaMona", "18");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 5.0);
		break;
		
		case "Capral_5":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_DefKillCapral", 1.0);
		break;
		
		case "Capral_6":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Kaptan, düşman kampına giden yol sağımızda. Size eşlik edeceğim.";
				link.l1 = "Çekil kenara, Onbaşı. Yalnız gitmeyi tercih ederim.";
			}
			else
			{
				dialog.text = "Kaptan, düşman kampına giden yol sağımızda. Kaybolmazsınız.";
				link.l1 = "İlginiz için teşekkür ederim.";
			}
			link.l1.go = "Capral_7";
		break;
		
		case "Capral_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			IslaMona_DefGotoMarch();
			pchar.quest.islamona_def_killslaves.win_condition.l1 = "location";
			pchar.quest.islamona_def_killslaves.win_condition.l1.location = "IslaMona_town";
			pchar.quest.islamona_def_killslaves.function = "IslaMona_DefKillSlaves";
		break;
		
		case "FraOfficer":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Kaptan "+GetFullName(pchar)+"! Tanrıya şükür! Kendimi tanıtmama izin verin - Teğmen "+GetFullName(npchar)+" . Sizin büyük bir hayranınızım! Bu sefil toprak parçasında ne işiniz var bilmiyorum ama tam zamanında geldiniz!\nŞunu söylemeliyim ki, Kaptan, subaylarımız arasında oldukça popüler oldunuz. Hizmetinizin... 'kendine has' tarzı birçoklarını rahatsız etse de, herkes sizin katılımınızın filomuzu güçlendirdiği konusunda hemfikir. Şu anda tam anlamıyla bir çıkmazdayız, bu yüzden sizin gibi birinin yardımı paha biçilemez!";
				link.l1 = "Ne yapabilirim? Burada neler oluyor?";
				link.l1.go = "FraOfficer_1";
			}
			else
			{
				dialog.text = "Kaptan "+GetFullName(pchar)+"Adınız filo raporlarında birkaç kez geçti. Hem de pek de olumlu olmayan bir şekilde. Ancak şimdi, bu pek onurlu olmayan gidişatı tersine çevirip anavatanınıza hizmet etme şansınız var.";
				link.l1 = "Ne yapabilirim?   Burada neler oluyor?";
				link.l1.go = "FraOfficer_8";
			}
		break;
		
		case "FraOfficer_1":
			dialog.text = "Biz 'Warrior'daydık, sıradan bir görevdi - özellikle cüretkâr İspanyol akıncılarını avlıyorduk. İş genelde çok basit: casus hedefin yerini ve bilgilerini verir, sen de ufkun ötesinden yakalarsın. Anlatacak pek bir şey yok, ama her şey çok kötü bitti: İspanyollar bizi önce buldu ve saldırdılar, üstelik kendileri de bir korvetteydi. Eğer elimizde daha ciddi bir şey olsaydı, onlarla birlikte dibe gitmezdik... ama en azından tüm gövdelerini havaya uçurmayı başardık. Sadece benim timim hayatta kaldı. Kastilyalıların da birkaç kurtulanı oldu. Ama uzun sürmedi, haha!";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "'Warrior' firkateyni mi? Kaptan Shocke öldü mü?";
				link.l1.go = "FraOfficer_1_1";
			}
			else
			{
				link.l1 = "";
				link.l1.go = "FraOfficer_2";
			}
		break;
		
		case "FraOfficer_1_1":
			dialog.text = "I am not surprised that you asked about him, Captain. I heard about your involvement in intercepting the 'Alcantara'. A great feat; even then, you laid the foundation for your patent! Commander Shocke didn't die—quite the opposite! He was promoted and, at his request, sent to serve in the Mediterranean. We can only envy him, given our situation now. So, actually, about our situation...";
			link.l1 = "";
			link.l1.go = "FraOfficer_2";
		break;
		
		case "FraOfficer_2":
			dialog.text = "Adada bir yerleşim bulduk – oldukça kalabalık bir haydut yuvası, hem de – dinle şimdi – korsanlar ve İspanyollar bir arada. İnanılır gibi değil! Bilirsin, normalde bu alçaklar birbirlerini doğrar ya da asarlar, ama burada – bak hele: takımadaların tam ortasında, aile gibi çalışıp korsan kerestesi çıkarıyorlar. Kendilerine yaptıkları iskeleyi gördün mü? Misafirler bunlara sandal ile gelmiyor. Görevimiz gayet açık: senin yardımınla yerleşimi ele geçiriyoruz, korsan kerestesini ve esirleri alıyoruz, sonra da herkesi Capsterburg’a götürüyorsun. Bu arada yetkililer kendi işlerini halleder... Onlar hallederken de biz korsan kerestesiyle ilgileniriz ve memleketten filomun diğer subaylarıyla güzelce kutlama yaparız!";
			link.l1 = "Seni şimdiye kadar yerleşimi kendin almaktan alıkoyan ne oldu?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_3":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "There are probably many more bandits than us - we saw tents on the shore. And besides tents, they also have a wall, gates, cannon!";
			else sTemp = "There are probably not so many bandits, otherwise they would have kicked us out of here already, but they still have a wall, gates, cannon and plenty of time!";
			dialog.text = "Bizi ne durdurdu sanıyorsun?! Sadece on iki tüfekçimiz ve yedi denizcimiz var. Hepsi yorgun ve bitkin. Sadece beş misket tüfeğini kurtarabildik, her birinde en fazla bir fişek var! "+sTemp+"";
			link.l1 = "Ama bir planın var mı?";
			link.l1.go = "FraOfficer_4";
		break;
		
		case "FraOfficer_4":
			dialog.text = "Dinle, hiç vakit kaybetmedik. Öncelikle bu fabrikayı ele geçirdik, biraz yiyecek ve suya el koyduk, en önemlisi de korsanlara ait bir depo dolusu kereste ve bir düzineden fazla köle aldık! Zaten köleleri koruyamazdık, bu yüzden hemen güç kullanarak keşif yaptık; onları tüfeklerimizin koruması altında eski efendilerine saldırmaya gönderdik. Böylece haydutların silah stokladığını öğrendik.";
			link.l1 = "Şimdi beni ve adamlarımı köleler yerine bu silahla ilgilenmeye göndermek istediğini doğru mu anlıyorum?";
			link.l1.go = "FraOfficer_5";
		break;
		
		case "FraOfficer_5":
			dialog.text = "Hayır, ama barış bayrağı altında haydutların yanına gidebilirsin. Senin gelişin onların ininin açığa çıktığı anlamına geliyor ve şimdi kralın askerlerinin bir gemisi ve takviyesi var. Onlar durumu anlamaya çalışırken ve seni dikkatle dinlerken, topa olabildiğince yaklaş, altına bir el bombası at ve bizim adamlarımızla seninkiler gelene kadar hayatta kalmaya bak. Bunu başarabileceğinden emin değilsen, yerine adamlarından birini göndermeyi dene.";
			link.l1 = "Önce onlara bombayla gitmeden bir teslim olma şansı sunayım. Etrafı kolaçan eder, ruh hallerini ve güçlerini tartarım, kalplerine şüphe tohumları ekerim. Teslim olmazlarsa, bu sefer bombayla tekrar giderim.";
			if (CheckCharacterItem(pchar, "patent_fra")) link.l1.go = "FraOfficer_6";
			else link.l1.go = "FraOfficer_6_1";
		break;
		
		case "FraOfficer_6":
			GiveItem2Character(pchar, "grenade");
			//Log_Info("Вы получили гранату");
			PlaySound("interface\important_item.wav");
			dialog.text = "... ve o zamana kadar sana alışmış olacaklar, böylece sabotajı gerçekleştirmek daha kolay olacak! Akıllıca! Senden daha azını beklemezdim, Kaptan. Hazır olduğunda devam et. Ama yine de, al... İşine yarayabilir.";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_6_1":
			dialog.text = "... o zamana kadar sana alışmış olacaklar, böylece sabotajı gerçekleştirmek daha kolay olacak. Böyle yapacağız. Devam et!";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_7":
			DialogExit();
			AddQuestRecord("IslaMona", "19");
			chrDisableReloadToLocation = false;
			pchar.quest.islamona_def_goout.win_condition.l1 = "location";
			pchar.quest.islamona_def_goout.win_condition.l1.location = "IslaMona_Jungle_01";
			pchar.quest.islamona_def_goout.function = "IslaMona_DefCapralTalk";
		break;
		
		case "FraOfficer_8":
			dialog.text = "Bu bölgede İspanyollarla uzun süren bir çatışma yaşandı. Her iki gemi de battı ve sağ kalanlar buraya sığındı. Çoğunluğu Fransız’dı, ama düşmanlarımızdan bazıları da kurtulmayı başardı. Ve daha fazlasını bilmenize gerek yok, üzgünüm Kaptan. Gizli bilgi, anlıyorsunuz.";
			link.l1 = "Anlaşıldı.";
			link.l1.go = "FraOfficer_9";
		break;
		
		case "FraOfficer_9":
			dialog.text = "Adada bir yerleşim bulduk - oldukça kalabalık bir haydut yuvası, hem de - dinle şimdi - korsanlar ve İspanyollar bir arada. İnanılır gibi değil! Bilirsin, normalde bu alçaklar birbirlerini doğrar ya da asarlar, ama burada - bak hele: takımadaların tam ortasında, aile gibi çalışıp korsan kerestesi çıkarıyorlar. Kendilerine yaptıkları iskeleyi gördün mü? Buradakilere misafirler kayıkla gelmez. Görevimiz gayet net: senin yardımınla yerleşimi ele geçiriyoruz, korsan kerestesini ve esirleri alıyoruz, sonra da herkesi Capsterburg'a götürüyorsun. Bu arada yetkililer kendi işlerini halleder... Ve onlar işlerini hallederken, belki de sana ihtiyacın için değerli keresteden biraz alma fırsatı bile verebilirim.";
			link.l1 = "Şimdiye kadar yerleşimi kendi başına ele geçirmene ne engel oldu?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_10":
			dialog.text = "İşte buradasın! Bir haber var mı?";
			link.l1 = "Bu bir onur muhafızı mı?";
			link.l1.go = "FraOfficer_11";
		break;
		
		case "FraOfficer_11":
			dialog.text = "Elbette, yakında bir karar verilecek ve ne yapacağımıza karar vereceğiz. Yeni emirler vermek için adamlarımı adanın dört bir yanında aramak zorunda kalmak istemem.";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "Mükemmel bir girişim! Emirlerinizi alacaksınız. Keşif yaptım: düşman zayıf, topun da cephanesi bitmiş. Hemen haydutların inine saldırmanızı emrediyorum, Teğmen. Ellerinizle oynamayı bırakın. Filoda sıradan bir gün daha. Harekete geçin!";
				link.l1.go = "FraOfficer_12";
			}
			else
			{
				link.l1 = "Bence onları 'köle' keşfinden hemen sonra zorla alabilirdin. Savunmaları gülünç, sadece birkaç dişe dokunur dövüşçüleri var. Fazla düşünmeye gerek yoktu – şimdiye kadar ganimet şarabını yudumlayıp demir ağacından bir dağın üstünde oturuyor olabilirdik.";
				link.l1.go = "FraOfficer_14";
			}
		break;
		
		case "FraOfficer_12":
			dialog.text = "Emredersiniz, Kaptan!";
			link.l1 = "...";
			link.l1.go = "FraOfficer_13";
		break;
		
		case "FraOfficer_13":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -25);
			AddQuestRecord("IslaMona", "22");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_14":
			dialog.text = "Ve bunlar senin keşif sonuçların mı? Asker olmayan birinden fazlasını beklemenin garip olabileceğini anlıyorum, ama bana gerçekler lazım! Gerçekler, Kaptan, senin fikrin değil!";
			link.l1 = "Beni kırdınız, Teğmen. Rapor veriyorum!";
			link.l1.go = "FraOfficer_15";
		break;
		
		case "FraOfficer_15":
			dialog.text = "";
			link.l1 = "Şu anda, senin batırdığın İspanyol gemisinden sağ kalan bir kaptan burada bizimle. Tecrübeli bir komutan, yakında toparlanacak. Eğer gecikirsek, iyileşecek ve savunmayı askeri bilime uygun şekilde organize edecek, o zaman işimiz çok zorlaşır. Acele etmeliyiz – tekrar ediyorum, şu an zayıf ve moralsizler.";
			link.l1.go = "FraOfficer_15_1";
			link.l2 = "Takviye kuvvetler yakında geliyor – korsanın kerestesini ele geçirmek için. Bunun bir blöf olduğunu sanmıyorum: sen de kendin gördün iskeleleri ve fabrikanın deposunda teslimata hazır yığılı malları. Acele etmeliyiz – tekrar ediyorum, onlar zayıf ve moralsizler. Gecikirsen, bir korsan gemisinin gelişini beklemek zorunda kalırsın.";
			link.l2.go = "FraOfficer_15_2";
			link.l3 = "Bu bataklığın neredeyse yarısı kadınlardan oluşuyor. Aslında milislerle bile savaşmadın: tüm bu süre boyunca sana karşı çıkan savaşçıların sayısı ondan fazla değildi. Hepsi zayıf ve moralsiz.";
			link.l3.go = "FraOfficer_15_3";
			link.l4 = "The cannon is out of ammunition. I've seen enough guns in my lifetime and can tell when a crew is ready to fire and when it's not. Without their artillery, they're nothing but poor warriors; they are weak and demoralized.";
			link.l4.go = "FraOfficer_15_4";
			link.l5 = "Zaferleri ve şanı düşün, Teğmen! Bir İspanyol akıncısına karşı tek başına kazanılan zafer, bir haydut yuvasının ele geçirilmesi ve korsanlara özgü bir kereste kaynağı – tüm bunlar kendi gemini komuta etmene layık! Tekrar ediyorum, onlar zayıf ve moralsiz, şimdi onları ezmenin tam zamanı!";
			link.l5.go = "FraOfficer_15_5";
		break;
		
		case "FraOfficer_15_1":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				Notification_Skill(true, 80, SKILL_LEADERSHIP);
				dialog.text = "Teşekkür ederim, Kaptan. Bu çok değerli bir bilgi ve haklıydınız, burada oyalanmamıza gerek yok. Adamlarım burada, güçlüyüz, eğitimliyiz ve hazırız. Her şey yarım saat içinde bitecek. Kaptan, lütfen geminizde insanları, esirleri ve yükü almaya hazırlanın. Burada fazla oyalanmayacağız.";
				link.l1 = "Her şey hazır, Teğmen. Sadece sizi bekliyorduk. Sonra görüşürüz!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				Notification_Skill(false, 80, SKILL_LEADERSHIP);
				dialog.text = "Teşekkürler, Kaptan. Bu gerçekten değerli bir bilgi. O halde, iskeleye gidip biniş ekibini hazırla. Haydutların inine birlikte ve hemen baskın yapacağız. En iyi adamlarım ve seninkiler önde olacak – kapıları ele geçirecekler. Güçlerimizi birlikte gözden geçirdikten sonra gerisini konuşuruz. Beni ya da ülkeni hayal kırıklığına uğratma, "+GetFullName(pchar)+".";
				link.l1 = "...Öyle olsun. Sonra görüşürüz, Teğmen.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_2":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				Notification_Reputation(true, 42, "low");
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
				dialog.text = "Teşekkür ederim, Kaptan. Bu çok değerli bir bilgi ve haklıydınız, burada oyalanmamıza gerek yok. Adamlarım burada, güçlüyüz, eğitimliyiz ve hazırız. Her şey yarım saat içinde bitecek. Kaptan, lütfen geminizde insanları, esirleri ve yükü almaya hazırlanın. Burada fazla oyalanmayacağız.";
				link.l1 = "Her şey hazır, Teğmen. Sadece sizi bekliyorduk. Sonra görüşürüz!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				Notification_Reputation(false, 42, "low");
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				dialog.text = "Teşekkür ederim, Kaptan. Bu çok değerli bir bilgi. O halde, iskeleye gidip biniş ekibini hazırla. Haydutların inine birlikte ve hemen saldıracağız. Benim en iyi adamlarım ve seninkiler öncü olacak – kapıları ele geçirecekler. Güçlerimizi birlikte gözden geçirdikten sonra gerisini konuşuruz. Beni ve ülkeni mahcup etme, "+GetFullName(pchar)+".";
				link.l1 = "...Öyle olsun. Sonra görüşürüz, Teğmen.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 70 && sti(pchar.reputation.nobility) > 41)
			{
				Notification_Reputation(true, 42, "low");
				Notification_Skill(true, 70, SKILL_LEADERSHIP);
				dialog.text = "Teşekkür ederim, Kaptan. Bu değerli bir bilgi ve haklısınız, burada oyalanmamıza gerek yok. Adamlarım burada, güçlüyüz, iyi eğitimliyiz ve hazırız. Her şey yarım saat içinde bitecek. Kaptan, lütfen geminizde insanları, esirleri ve yükü almaya hazırlanın. Burada fazla oyalanmayacağız.";
				link.l1 = "Her şey hazır, Teğmen. Sadece sizi bekliyorduk. Sonra görüşürüz!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				Notification_Reputation(false, 42, "low");
				Notification_Skill(false, 70, SKILL_LEADERSHIP);
				dialog.text = "Teşekkür ederim, Kaptan. Bu çok değerli bir bilgi. O halde, iskeleye gidip biniş ekibini hazırla. Haydutların inine birlikte ve hemen baskın yapacağız. Benim en iyi adamlarım ve seninkiler öncü olacaklar – kapıları ele geçirecek olanlar onlar olacak. Kuvvetlerimizi birlikte gözden geçirdikten sonra gerisini konuşuruz. Beni ya da ülkeni hayal kırıklığına uğratma, "+GetFullName(pchar)+".";
				link.l1 = "...Öyle olsun. Görüşürüz, Teğmen.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_4":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				Notification_Reputation(true, 42, "low");
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
				dialog.text = "Teşekkür ederim, Kaptan. Bu değerli bir bilgi ve haklıydınız, burada oyalanmaya gerek yok. Adamlarımın hepsi burada, güçlüyüz, iyi eğitimliyiz ve hazırız. Her şey yarım saat içinde bitecek. Kaptan, lütfen geminizde insanları, esirleri ve yükü almaya hazırlanın. Burada fazla oyalanmayacağız.";
				link.l1 = "Her şey hazır, Teğmen. Sadece sizi bekliyorduk. Sonra görüşürüz!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				Notification_Reputation(false, 42, "low");
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				dialog.text = "Teşekkür ederim, Kaptan. Bu çok değerli bir bilgi. O halde, iskeleye gidip biniş ekibini hazırla. Haydutların inine birlikte ve hemen baskın yapacağız. En iyi adamlarım ve seninkiler önden gidecek – kapıları ele geçirecek olanlar onlar olacak. Kuvvetlerimizi birlikte gözden geçirdikten sonra kalanları konuşuruz. Beni ya da ülkeni hayal kırıklığına uğratma, "+GetFullName(pchar)+".";
				link.l1 = "...Öyle olsun. Sonra görüşürüz, Teğmen.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_5":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 90)
			{
				Notification_Skill(true, 90, SKILL_LEADERSHIP);
				dialog.text = "Teşekkür ederim, Kaptan. Bu gerçekten değerli bir bilgi ve haklıydınız, burada oyalanmamıza gerek yok. Adamlarım burada, güçlüyüz, eğitimliyiz ve hazırız. Her şey yarım saat içinde bitecek. Kaptan, lütfen geminizde insanları, mahkumları ve yükü almaya hazırlanın. Burada fazla oyalanmayacağız.";
				link.l1 = "Her şey hazır, Teğmen. Sadece sizi bekliyorduk. Sonra görüşürüz!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				Notification_Skill(false, 90, SKILL_LEADERSHIP);
				dialog.text = "Teşekkür ederim, Kaptan. Bu gerçekten değerli bir bilgi. O halde, iskeleye gidip biniş ekibini hazırla. Haydutların inine birlikte ve hemen saldıracağız. En iyi adamlarım ve seninkiler önden gidecek – kapıları ele geçirecekler. Kalanı, kuvvetlerimizi birlikte gözden geçirdikten sonra konuşuruz. Beni ya da ülkeni hayal kırıklığına uğratma, "+GetFullName(pchar)+".";
				link.l1 = "...Öyle olsun. Sonra görüşürüz, Teğmen.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_16": // французы атакуют сами
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			AddQuestRecord("IslaMona", "24");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_17": // совместная атака
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -7);
			AddQuestRecord("IslaMona", "23");
			IslaMona_DefAttackCommon();
		break;
		
		case "FraOfficer_18":
			if (CheckCharacterItem(pchar, "patent_fra")) dialog.text = "Ve ben, ne aptalmışım ki sana hayranlık duydum! A-ah! Fransa'nın gururu, Kaptan "+GetFullName(pchar)+"!! Sen bu ayrıcalığı hak etmiyorsun!!!";
			else dialog.text = ""+GetFullName(pchar)+", alçak, hain ve lanetli korsan! Bu sefil inin senin pis yuva olduğunu tahmin etmeliydim! Fransa senin gibi adamları ne unutur ne de affeder!";
			link.l1 = "";
			link.l1.go = "FraOfficer_19";
		break;
		
		case "FraOfficer_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_75";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FraOfficer_20":
			dialog.text = "Hazır mısınız, Kaptan? Mürettebatınız gerçekten güven veriyor!";
			link.l1 = "Teşekkür ederim, Teğmen. Başlayalım mı?";
			link.l1.go = "FraOfficer_21";
		break;
		
		case "FraOfficer_21":
			dialog.text = "Evet, hemen devam edelim!";
			link.l1 = "...";
			link.l1.go = "FraOfficer_22";
		break;
		
		case "FraOfficer_22":
			DialogExit();
			IslaMona_DefAttackCommonRun();
		break;
		
		// обиженный пират
		case "Pirate":
			dialog.text = "Ha! "+GetFullName(pchar)+"! Ne karşılaşma ama. Hey, yakalayın onu! Bu herif burada her şeyin sahibi! Burası onun adası!";
			link.l1 = "Ne gün ama bu...";
			link.l1.go = "Pirate_1";
		break;
		
		case "Pirate_1":
			DialogExit();
			IslaMona_DefCheckJungleFight();
		break;
		
		// Алонсо
		case "Alonso":
			dialog.text = "Kaptan, emirler nedir? Hazır bekleyip çıkarma ekibini göndermemiz için işaret geldi.";
			link.l1 = "Emir değişmedi. Çocuklar, peşimden gelin, evimizi istenmeyen misafirlerden temizlememiz lazım. Ödül benim, tüm ganimetler sizin!";
			link.l1.go = "Alonso_1";
		break;
		
		case "Alonso_1":
			dialog.text = "Yaşasın!";
			link.l1 = "Savaşa!";
			link.l1.go = "Alonso_2";
		break;
		
		case "Alonso_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_our_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common"))
			{
				pchar.quest.islamona_attack_common1.win_condition.l1 = "location";
				pchar.quest.islamona_attack_common1.win_condition.l1.location = "IslaMona_Jungle_01";
				pchar.quest.islamona_attack_common1.function = "IslaMona_DefAttackCommonPrepare";
			}
			else
			{
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload3_back", true);
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload1_back", true);
				pchar.quest.islamona_attack_force.win_condition.l1 = "location";
				pchar.quest.islamona_attack_force.win_condition.l1.location = "IslaMona_factoria";
				pchar.quest.islamona_attack_force.function = "IslaMona_DefAttackForce";
			}
		break;
		
		// испанский офицер
		case "SpaOfficer":
			dialog.text = "Selamlar, señor. Bu toprağın sahibi siz misiniz? Kendimi tanıtmama izin verin, Ben Grand Francisco de Alba, 'Perro Marino' korvetinin eski kaptanıyım.";
			link.l1 = "Evet, burası benim toprağım. Ben "+GetFullName(pchar)+",   ' gemisinin kaptanı "+pchar.ship.name+"'. Görkemli mi? Burada daha önce hiç bu kadar seçkin misafirimiz olmamıştı.";
			link.l1.go = "SpaOfficer_1";
		break;
		
		case "SpaOfficer_1":
			dialog.text = "Ah, Mösyö "+GetFullName(pchar)+"! Adın oldukça iyi biliniyor. Son zamanlarda Casa de Contratación raporlarında adın o kadar sık geçiyor ki, sana karşı bir şeyler yapmam için emir gelmesini ciddi ciddi bekliyordum.";
			link.l1 = "Benimle mi uğraşıyorsun?";
			link.l1.go = "SpaOfficer_2";
		break;
		
		case "SpaOfficer_2":
			dialog.text = "Bence artık rol yapmanın anlamı yok. Benim görevim, dünyanın tüm denizlerinde İspanya'nın ve Kral Philip'in düşmanlarını bulup yok etmek.";
			link.l1 = "Böyle emirlerin henüz gelmemiş olması şansımıza. Belli ki çok yetenekli bir deniz subayısınız.";
			link.l1.go = "SpaOfficer_3";
		break;
		
		case "SpaOfficer_3":
			dialog.text = "Şu anda korsanlarla dolup taşan küçücük bir adada yarı ölü bir esir olmam ve hemşehrilerimin kaçak durumda olması, vardığınız sonucu doğruluyor, ha-ha! Çok tehlikeli bir işti ama emir, emirdir. Az kalsın başarıyorduk! Adamlarım için çok üzgünüm - hepsini ismiyle tanırdım, yıllarca birlikte hizmet ettik. Ama ülkem, imparatorluk statüsünü korumak için daha çok evladının kanını dökmek zorunda kalacak. Bizim ailemiz bunu herkesten iyi bilir.";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "";
				link.l1.go = "SpaOfficer_4";
			}
			else
			{
				link.l1 = "Şimdilik daha acil meselelere dönelim. Seninle ne yapacağım, Grand?";
				link.l1.go = "SpaOfficer_5";
			}
		break;
		
		case "SpaOfficer_4":
			dialog.text = "Bu arada, Monsieur de Mor, 'Savaşçı' - o küçük gemi sana tanıdık geldi, değil mi? Porto Bello’daki o cüretkâr operasyonun gözden kaçmadı. Cesurcaydı, hatta intihara yakındı. Paraya fena halde ihtiyacın vardı, değil mi? Ha!";
			link.l1 = "Benim hakkımda çok şey biliyorsun, Grand. Ama şimdi senin kaderine geçelim.";
			link.l1.go = "SpaOfficer_5";
		break;
		
		case "SpaOfficer_5":
			dialog.text = "Düşünecek ne var ki? Her iyi hikâyede olduğu gibi, üç seçeneğin var: Beni öldür, burada bırak ya da beni serbest bırak. Eğer beni serbest bırakırsan, de Alba ailesinin sözüyle temin ederim ki, bu yerden ya da başıma gelenlerden kimseye bahsetmeyeceğim. Üstelik sana borçlu olacağım ve bu borcumu ödeyene kadar sana asla karşı gelmeyeceğim.";
			link.l1 = "Bunu riske atamam, Büyükbaba.";
			link.l1.go = "SpaOfficer_6";
			link.l2 = "Bir süre burada kalacaksın. Kendi yurttaşlarınla eşit şartlarda yaşayacak ve çalışacaksın.";
			link.l2.go = "SpaOfficer_7";
			link.l3 = "Gemime hoş geldin, Grand. Zamanı gelince seni Santiago deniz fenerinde karaya çıkaracağım. Umarım sözünü tutarsın.";
			link.l3.go = "SpaOfficer_8";
		break;
		
		case "SpaOfficer_6":
			dialog.text = "Anlıyorum, señor. Her halükarda, o savaşta adamlarımla birlikte ben de zaten öldüm. Bu iyi bir son.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_6_1";
		break;
		
		case "SpaOfficer_6_1":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_KillSpanish", 1.0);
		break;
		
		case "SpaOfficer_7":
			dialog.text = "Kabul ediyorum, yarım yamalak işlerden hoşlanmam. Ama esir olmakta bir utanç yok, bu yüzden bana bahşettiğin hayatı kabul ediyorum ve bu iyi kalpli, belli ki çok mutlu insanlarla huzur içinde yaşayacağım. Yine de, buradan bir gün ayrılırsam, sana hiçbir borcum olmayacak.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_7_1";
		break;
		
		case "SpaOfficer_7_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			AddQuestRecord("IslaMona", "27");
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_8":
			dialog.text = "Sana kendi sözümü, bir de Alba ailesinin sözünü veriyorum! Gemide görüşürüz!";
			link.l1 = "";
			link.l1.go = "SpaOfficer_8_1";
		break;
		
		case "SpaOfficer_8_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("IslaMona", "28");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			pchar.quest.islamona_final_mayak.win_condition.l1 = "location";
			pchar.quest.islamona_final_mayak.win_condition.l1.location = "Mayak9";
			pchar.quest.islamona_final_mayak.function = "IslaMona_FinalMayakSpanish";
			pchar.questTemp.IslaMona.Mayak = "true";
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_9":
			dialog.text = "Kaptan "+GetFullName(pchar)+"! You saved my life and brought me back to my own. I understand how difficult it was to take such a risk - I would never have dared to do such a thing. I owe you, senor. I give you my word that I will never tell anyone about the circumstances of that ill-fated battle. When you return to the Old World, be sure to find me; you will always be welcome at our family estate in Madrid. For now, take this...";
			link.l1 = "Bir harita parçası mı?";
			link.l1.go = "SpaOfficer_10";
		break;
		
		case "SpaOfficer_10":
			AddMapPart();
			dialog.text = "Yanımda değerli olan tek şey buydu. Diğer parçayı kolayca bulacağından hiç şüphem yok. Elveda! Ve sana bol şans, dostum.";
			link.l1 = "Elveda, Grand. Sözünü unutma, sana bol şans!";
			link.l1.go = "SpaOfficer_11";
		break;
		
		case "SpaOfficer_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.IslaMona.Mayak = "done";
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			AddQuestRecord("IslaMona", "29");
			CloseQuestHeader("IslaMona");
		break;
		
		// Диалоги обитателей Исламоны
		// мужское население
		case "island_man":
			dialog.text = LinkRandPhrase("Selamlar! Nasılsınız, Kaptan? Bizim için işler yolunda gidiyor.","Toplum için çalışmak en büyük mutluluk!","Adanız harika, Kaptan, ve refahı için elimizden gelen her şeyi yapacağız.");
			link.l1 = LinkRandPhrase("Bunu duymak güzel.","Her şeyin yolunda olmasına sevindim.","Coşkunuzu takdir ediyorum, amigo.");
			link.l1.go = "island_man_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Küstahlık olarak algılamayın, señor, ama burada yaşamak imkânsız.","Engizisyon'un hücrelerinde oturmaktan iyisi yok..."),RandPhraseSimple("Bizi kurtardığınız için teşekkür ederiz, Kaptan.","Bunlar... korsanlar senin arkadaşların mı?"));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 1:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Burada fena değil! Sadece biraz sıkıcı.","Kaptan, sizi görmek güzel. Bir ara uğrayın!"),RandPhraseSimple("Birisi sahilde kafatasları bulmuş ve sabah toplantısına getirmiş. Burada hep böyle mi oluyor?","Sana bir sır vereyim, Señor Jiménez belli ki buranın temiz havası ve güvenliğinden faydalanıyor."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 2:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Burada fena değil! Sadece biraz sıkıcı.","Kaptan, sizi görmek güzel. Bir ara uğrayın!"),RandPhraseSimple("Birisi sahilde kafatasları bulmuş ve sabah toplantısına getirmiş. Burada hep böyle mi oluyor?","Sana bir sır vereyim, Señor Jimenez bu yerin temiz havası ve güvenliğinden açıkça faydalanıyor."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 3:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Tanrı seni korusun, Kaptan!","Haftada bir kez, sahilde ve meyhanede gösteriler yapıyoruz. Bir ara uğra."),RandPhraseSimple("Denizcileriniz sürekli olarak bize taze yiyecek karşılığında her türlü ıvır zıvır getiriyor. Bunu teşvik ettiğiniz için teşekkür ederim.","Bu yerin hâlâ keşfedilmemiş olması inanılmaz. Umarım hep böyle kalır."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
				}
			}
		break;
		
		case "island_man_1":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
		break;
		
		case "island_man_2":
			dialog.text = "Teşekkür ederim, señor. Sayende gerçek Yeni Dünya'yı gördük. Tanrı seni korusun!";
			link.l1 = "";
			link.l1.go = "island_man_3";
			locCameraFromToPos(1.64, 1.58, -5.11, false, 2.66, 0.20, -5.74);
		break;
		
		case "island_man_3":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
			sld = characterFromId("Himenes_companion_12");
			sld.dialog.currentnode = "island_woman_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// женское население
		case "island_woman":
			dialog.text = LinkRandPhrase("Güvenlik ve huzur - işte bu yeri sevmemin nedeni bu!","Harika bir cennet! Yani, neredeyse...","Onca zorluktan sonra burada yeni bir yuva bulduğumuz için mutluyuz.");
			link.l1 = LinkRandPhrase("Sizin ve topluluğunuz adına mutluyum.","Evet, ben de bu küçük adayı seviyorum.","Memnun kalmana sevindim.");
			link.l1.go = "island_woman_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = LinkRandPhrase("Ah... Merhaba.","Efendim, o silahlı... kaba adamlar kimler?","Bizi kurtardığınız için teşekkür ederiz, Kaptan.");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 1:
						dialog.text = LinkRandPhrase("Adamlarımız harika iş çıkardı - evler mükemmel. Ama biz de çok çalıştık!","Señor Kaptan, merak etmeyin: küçük klanımızın kadınları zorluklardan ve geçici rahatsızlıklardan korkmaz.","Buradaki hava ne güzel! Bir de deniz! Kendini Tanrı'ya daha yakın hissediyorsun!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 2:
						dialog.text = LinkRandPhrase("Adamlarımız harika iş çıkardı - evler mükemmel. Ama biz de çok çalıştık!","Señor Kaptan, endişelenmeyin: küçük klanımızın kadınları zorluklardan ya da geçici rahatsızlıklardan korkmaz.","Buradaki hava ne güzel! Ve deniz! Kendini Tanrı'ya daha yakın hissediyorsun!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 3:
						dialog.text = LinkRandPhrase("Daha sık uğra, Señor Kaptan. Seni görmek beni her zaman mutlu ediyor.","Señor Rodgar harika bir hikaye anlatıcısı. Onu saatlerce dinleyebilirsin!","Hehe. Bizim gruptan birinin ailesine yeni bir üye katılacakmış diyorlar. Hayat Isla Mona'da bile devam ediyor!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
				}
			}
		break;
		
		case "island_woman_1":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
		break;
		
		case "island_woman_2":
			dialog.text = "Sen çok teşekkür ederim, señor! Daha sık uğra...";
			link.l1 = "";
			link.l1.go = "island_woman_3";
			locCameraFromToPos(-1.86, 1.18, 4.51, true, -1.49, 0.20, 6.13);
		break;
		
		case "island_woman_3":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// пираты Родгара
		case "fort_pirate":
			if(npchar.location == "islamona_factoria")
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("Her şey yolunda, Kaptan!","Köleler kontrol altında, merak etme."),RandPhraseSimple("Endişelenmene gerek yok, isyan söz konusu bile olamaz.","Rom için teşekkürler! Hemen işe koyuluyoruz!"));
			}
			else
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("İspanyollar mı? Bunu senden beklemezdik.","Şimdi huzur içinde uyuyabilmek için tüm yolu sahile kadar yürümek zorundayız!"),RandPhraseSimple("Neden bütün bunlara karar verdin, ha Kaptan?","Patron sana o zaman güvendi - ve yanılmadı. Şimdi yine sana inanacağız."));
			}
			link.l1 = "...";
			link.l1.go = "fort_pirate_1";
		break;
		
		case "fort_pirate_1":
			DialogExit();
			npchar.dialog.currentnode = "fort_pirate";
		break;
		
		// посетители таверны
		case "citizen_tavern":
			dialog.text = LinkRandPhrase("Belini kıracak kadar çalıştıktan sonra, bir iki kadeh içmek günah sayılmaz...","I'm almost done and heading home; the wife must be waiting...","Ah, it's nice to relax in our tavern after work! We're all grateful to you, captain!");
			link.l1 = LinkRandPhrase("İçkini keyifle yudumla, dostum, ha-ha!","Sakin ol dostum, ama fazla abartma, yoksa karın sana kızar, ha-ha!","Sakin ol dostum, hayat sadece çalışmaktan ibaret değil!");
			link.l1.go = "citizen_tavern_1";
		break;
		
		case "citizen_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "citizen_tavern";
		break;
		
		case "sailor_tavern":
			if (GetCharacterIndex("Mirabella") != -1) sTemp = "Who's that pretty mulatto woman living here?";
				else sTemp = "Captain, nice place you got here!";
			dialog.text = RandPhraseSimple(RandPhraseSimple("Kaptan, burası gerçekten güzelmiş!","Birdenbire romsuz kalsak ne olurdu, bir düşünsene. Elbette daha fazlasını bulurdun, değil mi?"),RandPhraseSimple("Böyle bir tatili uzun zamandır hayal ediyordum. Yine de bir genelev olsa fena olmazdı... sadece çılgınca bir düşünce, Kaptan.",sTemp));
			link.l1 = "...";
			link.l1.go = "sailor_tavern_1";
		break;
		
		case "sailor_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_tavern";
		break;
		
		case "sailor_town":
			dialog.text = RandPhraseSimple(RandPhraseSimple("İzin verdiğiniz için teşekkür ederim, Kaptan.","Burada güzel bir yer kurmuşsunuz - işleri düzenli tutmakta gerçekten ustasınız, Kaptan."),RandPhraseSimple("Taze yiyecek, içki, ayaklarımın altında sağlam toprak. Bu bir rüya.","Biraz daha burada kalmak istiyorum."));
			link.l1 = "...";
			link.l1.go = "sailor_town_1";
		break;
		
		case "sailor_town_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_town";
		break;
		
		// рабы
		case "slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("O kadar yorgunum ki - ayakta zor duruyorum.","Böyle yaşamak için artık gücüm kalmadı!"),RandPhraseSimple("Bu iş bana fazla ağır geliyor.","Gözetmenler derimi canlı bırakmadı!"));				
			link.l1 = "";
			link.l1.go = "slave_1";
		break;
		
		case "slave_1":
			DialogExit();
			npchar.dialog.currentnode = "slave";
		break;
		
		// энкауниеры в домах
		case "HouseMan":
			dialog.text = LinkRandPhrase("Size nasıl yardımcı olabilirim, kaptan?","İçeri gel, biraz yerel paella al. Ama Allah aşkına, neyle yapıldığını sakın sorma!","Hoş geldiniz, kaptan. Burayı nasıl buldunuz?");
			link.l1 = "...";
			link.l1.go = "HouseMan_1";
		break;
		
		case "HouseMan_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseMan";
		break;
		
		case "HouseWoman":
			dialog.text = LinkRandPhrase("Señor, hoş geldiniz!","Merhaba, kaptan. Kalacak mısınız?","Benim için mi geldiniz? Lütfen, içeri buyurun, dağınıklığı görmezden gelin, señor.");
			link.l1 = "...";
			link.l1.go = "HouseWoman_1";
		break;
		case "HouseWoman_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseWoman";
		break;
	}
}