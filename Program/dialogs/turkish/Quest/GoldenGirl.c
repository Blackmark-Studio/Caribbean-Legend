// диалоги персонажей по квесту Дороже золота
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
			link.l1 = "Gitmeliyim...";
			link.l1.go = "exit";
		break;
		
		// вестовой в Сен Пьере
		case "fraofficer":
			dialog.text = "Kaptan Charles de Maure! Sonunda! Ekselansları Jacques Dille de Parkuet sizi görmek istiyor! Bu çok acil!";
			link.l1 = "Neden şaşırmadım ki? Pekâlâ, lütfen Ekselanslarına yakında geleceğimi söyleyin.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", true);//закрыть выходы из города
			LAi_LocationDisableOfficersGen("FortFrance_townhall", true);//офицеров не пускать
			pchar.questTemp.GoldenGirl = "message";
			AddQuestRecord("GoldenGirl", "1");
		break;
		
		// маркиза Джулиана Бото
		case "Julianna":
			dialog.text = "Gözlerim beni yanıltıyor olmalı, karşımda bizzat Charles de Maure var! Böyle davetlere pek sık ev sahipliği yapmam, bu yüzden mütevazı manastırıma vakit ayırabildiğiniz için çok memnunum. Ne şanslıyım! Bu bir kadehi hak ediyor!";
			link.l1 = "Selamlar, hanımefendi. Davranışlarım sizi hayal kırıklığına uğratırsa affedin lütfen – böyle... etkinliklere en son katılmamın üzerinden epey zaman geçti. Bir gemide görgü kuralları ise itaat, temiz fularlar ve her sabah düzenli bir fincan taze kahveden ibaret.";
			link.l1.go = "Julianna_1";
		break;
		
		case "Julianna_1":
			dialog.text = "Ne kadar çekicisiniz, Kaptan, hâlâ üzerinizde Parisli zarafetiniz var. Bu tecrübeli ve tuzlu maskenin altında onun utangaç bir parıltısını görebiliyorum. Merak etmeyin, sizi nihayet gördüğüme o kadar memnunum ki, şimdilik size birçok şeyi affedebilirim. Şimdilik. İleride aramızda neler olacağını göreceğiz. Şarap ister misiniz? Kırmızı mı, beyaz mı?";
			link.l1 = "Rom şakası yapmak için harika bir an, ama ne yazık ki hiç havamda değilim. Üzgünüm. Güzel ellerinizin doldurduğu her şeyi memnuniyetle içerim.";
			link.l1.go = "Julianna_2";
		break;
		
		case "Julianna_2":
			dialog.text = "Güzel seçim. Ama ısrar ediyorum. Şarap zevki bir adam hakkında çok şey anlatır, bu gece senin hakkında her şeyi öğrenmek istiyorum. O yüzden tekrar soruyorum: kırmızı mı, beyaz mı?";
			link.l1 = "Sen bilirsin. Kırmızı şarap içiyorsun görüyorum. Ben de aynısından alayım – senin hakkında bir şeyler öğrenmek isterim.";
			link.l1.go = "Julianna_3";
			link.l2 = "O halde, ben beyazı alırım, ama seçimi sana bırakıyorum. Bu iş iki taraflı olmalı, sence de öyle değil mi?";
			link.l2.go = "Julianna_4";
		break;
		
		case "Julianna_3":
			pchar.questTemp.GoldenGirl.Vine = "red";
			dialog.text = "Harika, şimdi sıra bende mi? Bu, Burgundy Pinot Noir. Şarapçılar ona 'yaramaz kız' derler. Kolay idare edilen bir tür değildir ve ardındaki tat da oldukça yanıltıcı olabilir. Memnun kaldın mı?";
			link.l1 = "Pinot Noir, ha? Bana uyar. Güvenilmez ve gizemli, başta kasvetli bir tadı var ama biraz nefes almasına izin verirsen şaşırırsın. Tonların ve tatların hafif bir dansı, deneyimli bir zevk sahibinin tercihi. İlk izlenimler yanıltıcıdır, değil mi? Gözlerinize içiyorum, hanımefendi!";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_4":
			pchar.questTemp.GoldenGirl.Vine = "white";
			dialog.text = "Harika, şimdi sıra bende mi? Loire Vadisi’nden enfes bir Sauvignon Blanc’ım var. Oldukça vahşi, neredeyse dilinizde köpürdüğünü hissediyorsunuz. Ve en güzel yanı – barut notası. Sanırım ortak bir yanımız var.";
			link.l1 = "Daha iyisini beklerdim, belki bir Riesling gibi. Neyse, hadi şu yaz ve barut kokan kaba şarabı içelim. Bazı insanların bunu pipi de chat sanmasına ne dersin? Senin gülüşüne içiyorum, şu safirler kadar parlak!";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_5":
			dialog.text = "Remarkable, Charles! May I call you that? I wasn't wrong about you; on a different day, you'd be the star of my night. But alas, my Captain, today you have strong competition. It appears we are on the verge of a scandal over there, do you see?";
			link.l1 = "Öfkeli sesler duyuyorum. Kim bu tatsız monsieur ve sevgili valimizi neyle kızdırmış?";
			link.l1.go = "Julianna_6";
		break;
		
		case "Julianna_6":
			dialog.text = "This 'unpleasant' monsieur is Angerran de Chievous, an unrecognised bastard of Count de Levi Vantadur. You are entertaining their topic of argument. De Chievous has been trying to earn my favour for years, and he followed me here, thinking he can replace his father for me. Even though he is not a lawful son, he is rich and powerful. Stubbornness is another of his traits; for some people, it replaces wisdom. Just before your arrival, he and Jacques started arguing about the obvious subject. His Excellency always protects me in a very touching way, you should see! Come on, let's observe and see how it ends this time.";
			link.l1 = "Havada bir bela kokusu var... Neden böyle güzel bir gecede bile her zaman bir pürüz çıkıyor...";
			link.l1.go = "Julianna_7";
		break;
		
		case "Julianna_7":
			dialog.text = "Affedersin, Charles?";
			link.l1 = "Boşver. Lütfen ısrarcı arkadaşını bana tanıt, sonra bakarız...";
			link.l1.go = "Julianna_8";
		break;
		
		case "Julianna_8":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest1", "GoldenGirl_PartyTalk", -1);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Julianna_9":
			dialog.text = "Monsieur, size değerli misafirimizi takdim etmeme izin verin - bizzat kendisi Kaptan Charles de Maure, ziyaretiyle bizi onurlandırdı! Böylesine ünlü kişiler burada pek sık misafir olmaz.";
			link.l1 = "...";
			link.l1.go = "Julianna_10";
		break;
		
		case "Julianna_10":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "Julianna_11":
			dialog.text = "Charles, bu işin nereye varacağını hiç beğenmiyorum! Jacques söylediklerime kulak asmıyor, Angerran ise kesin bir şeyler çeviriyor. Bu kavganın bir amacı vardı ve senin yardımına ihtiyacım var!";
			link.l1 = "Sizi anlamadım... Burada ne yapabilirim ki? Zaten benimle düello etmeyi reddetti...";
			link.l1.go = "Julianna_12";
		break;
		
		case "Julianna_12":
			dialog.text = "Kaptan, lütfen beni hayal kırıklığına uğratma. Az önce sohbetin ustasıydın, şimdi ise dünyan kılıçla dürtebileceğin ve dürtemeyeceğin şeylere bölündü. Biraz farklı düşün! Angerran'ın oyununu bozalım. Zavallı Jacques'a tek başına meydan okumak istiyor ama bu çok sıkıcı! Bir turnuva düzenleyelim! Buradaki birkaç beyefendi ciddi bahisleri kaldırabilir, senin şansın ise zaten efsane olmuş durumda! Belki bu gece kartlar senden yana olur?";
			link.l1 = "de Chievous'un bizim sevimli valimizle savaşmasını nasıl engelleyeceğini tam olarak anlamasam da, ben varım hanımefendi. Yeter ki o küçük sırıtışını suratından silelim.";
			link.l1.go = "Julianna_13";
		break;
		
		case "Julianna_13":
			dialog.text = "Harika, şimdi masaya git ve bir şeyler ye, uzun bir gece olacak. Hazır olduğunda salonda buluşalım, bunun için daha fazla alana ihtiyacımız olacak. Bu arada, bir gösteri yapacağım; başkalarını bana gözlükler ve yüksek bahisli oyunlar vermeye ikna edeceğim. Hatta can sıkıntısından boğulan bir kadını fark etmeleri için onlara bağırabilirim bile. Lütfen karışma, bu gece aynı tarafta olduğumuzu kimse bilmemeli. Sonra görüşürüz, Kaptanım!";
			link.l1 = "Ne derseniz, hanımefendi, ne derseniz...";
			link.l1.go = "Julianna_14";
		break;
		
		case "Julianna_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "barmen", "stay", "GoldenGirl_JulianaPause", -1);
			AddQuestRecord("GoldenGirl", "4");
		break;
		
		case "Julianna_15":
			dialog.text = "Pekala, beni tebrik et, işe yaradı! Biraz gurur, biraz önyargı ve işte oldu! Sıkılmış bir yüz ifadesi takın, bizi izliyorlar. İçkiyle ilgilendiğini sansınlar, benimle değil\nBir turnuva başlamak üzere, bahisler yüksek, ikinci şans ya da rövanş yok. Nedense senin bu işlere alışık olduğunu hissediyorum. Bunun üstesinden gelirsin. Unutma, Angerran kesinlikle bir şeyler çeviriyor, dostumuz Jacques'a karşı bir hamle yapacak ama senin gelişini hesaba katmadı. Benim kozum ol, çünkü onun kendinden emin, ukala yüzünü görmek hiç iyiye işaret değildir. Sekiz oyuncumuz var ama finalden önce onunla karşılaşmayacağından emin oldum\nAh! İlk rakibin! Albay ve kalemizin Komutanı. Deniz karaya karşı – askeri tecrübesi olan misafirler için layık bir mücadele! Alkışlar!";
			link.l1 = "";
			link.l1.go = "Julianna_16";
		break;
		
		case "Julianna_16":
			DialogExit();
			DoQuestCheckDelay("GoldenGirl_CreateColonel", 0.5);
		break;
		
		case "Julianna_17":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "Harika iş çıkardın, Charles, gerçekten mükemmeldi. Angerran ve Jacques birazdan karşı karşıya gelecekler. Keşke dinleyip turnuvayı bir hafta ertelemeyi kabul etselerdi. O zaman Paris'e kadar konuşulacak, gerçekten muhteşem bir davetli topluluğu toplayabilirdim! Neyse, belki bir dahaki sefere. Görünen o ki, bir sonraki rakibin şansına layık birisi, gerçek bir deniz kurdu, Kaptan Moreno! Kaptanlar, lütfen!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Ne yazık ki şansınız yaver gitmedi, Kaptan. Üzgünüm ama oyun sizin için bitti. Angerran zaten Jacques'a karşı oynuyor, bu yüzden gitmeliyim. Hoşça kalın.";
				link.l1 = "Bir zevkti... hanımefendi.";
			}
			link.l1.go = "Julianna_18";
		break;
		
		case "Julianna_18":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) GoldenGirl_CreateCaptainMoreno();
			else GoldenGirl_CardsFail();
		break;
		
		case "Julianna_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "Zaferinizi hak ettiğiniz için sizi tebrik ederim, Kaptan! Finalde karşınıza kimin çıkacağı hâlâ belli değil... Biraz kenara çekilelim. Sesinizi alçaltın ve şu masayı gözlemleyin. Bakın, işte gidiyor! Angerran'ın ne peşinde olduğunu anlamaya başlıyorum! Şimdiden zavallı Jacques'ın tüm parasını aldı, ama onu masadan kalkmasına izin vermiyor. Yanından geçerken, zavallı adamın tüm yüküyle birlikte bir geminin belgelerini kumara sürdüğünü gördüm. Ne yazık ki, bu gece şans ondan yana değil. Ya da birisi ona öyle olmamasını söyledi.";
				link.l1 = "De Chievous'un hile yaptığını mı düşünüyorsun?";
				link.l1.go = "Julianna_21";
			}
			else
			{
				dialog.text = "Ne yazık ki, şansınız sizi terk etti, Kaptan. Üzgünüm, ama oyun sizin için bitti. Angerran zaten Jacques'e karşı oynuyor, bu yüzden gitmeliyim. Hoşça kalın.";
				link.l1 = "Bir zevkti... hanımefendi.";
				link.l1.go = "Julianna_20";
			}
		break;
		
		case "Julianna_20":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Julianna_21":
			dialog.text = "Eğer isteseydi kesinlikle yapabilirdi, ama elimde hiçbir kanıt yok. Sevgili valimiz kart oyunlarında iyidir, ama rakibi de öyle. Angerran fırkateynini ortaya koyarken gözünü bile kırpmadı, düşünsene. Bu düello Paris ya da Lyon'da olsaydı, efsane olurdu Charles! Yine de, belki de bu gece sadece şansı yaver gidiyor. Hadi yanlarına gidelim ve kendimiz görelim.";
			link.l1 = "...";
			link.l1.go = "Julianna_22";
		break;
		
		case "Julianna_22":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest3", "GoldenGirl_Talking", -1); 
			LAi_ActorFollow(npchar, pchar, "", 10.0);
		break;
		
		case "Julianna_23":
			dialog.text = "Charles, tut beni yoksa düşeceğim... Ya da düşmem, bu aptallar bayıldığımı bile fark etmezler. Bunu gördün mü? Jacques, kahretsin şu aptallığını! Çocuk gibi, Tanrım! Aptal bir çocuk!";
			link.l1 = "Markiz, sanırım sizi tam olarak anlayamadım.  Şu anda o masada neler oluyor? Ne üzerine kumar oynuyorlar?";
			link.l1.go = "Julianna_24";
		break;
		
		case "Julianna_24":
			dialog.text = "Bende, Charles. Bizim tatlı, saf Jacques bana güvendi. Angerran onun tek zayıf noktasını buldu ve tam zamanında vurdu.";
			link.l1 = "Kahretsin! Ama turnuvada sıradaki benim, o lanet gemisini geri kazanabilirim! Neden?";
			link.l1.go = "Julianna_25";
		break;
		
		case "Julianna_25":
			dialog.text = "Çünkü Angerran bunu çok düşündü ve her şeyi en ince ayrıntısına kadar planladı. Beni dinle, fazla vaktimiz yok. Sen de ona aynısını yapmalısın. Onu her şeyinden mahrum bırak, tüm parasını, tüm gemilerini al, onu kışkırt! Onu şöhret, onur, tutku, ne olursa olsun, aklını kaybetmeye zorla! Bu gece nasıl yapıldığını gördün. Onu köşeye sıkıştır ve bahis yapmaya mecbur bırak\nSana yalvarıyorum Charles! Her şeye hazırım ama ona gitmeyeceğim. Böyle değil! Kont Vantadur bile dürüst bir kart galibiyetine karşı duramaz, bana yardım etmek için parmağını bile kıpırdatmaz. Görüyorsun, kartlar soylular için lanet olası kutsal şeyler! Sen benim son ve tek umudumsun Charles!";
			link.l1 = "Valimizi hemen toprağa vermeyin, hanımefendi. Belki de gemisini geri kazanır? Şans Hanım dediğin, dengesiz bir... kadındır.";
			link.l1.go = "Julianna_26";
		break;
		
		case "Julianna_26":
			dialog.text = "Hâlâ anlamadın mı? O masada şansın yeri yok! Angerran de Chievous her şeye hükmediyor. Hem beni elde etmenin hem de babasını bu işin dışında tutmanın bir yolunu buldu. Bunu ne zamandır planladığını bilmiyorum ama artık neredeyse kazandı. Oyunu o yönetiyor ve bizim onu bozmak için tek bir şansımız var. Al, bunu al! Şimdi bir oyalama yapacağım, sana bir iki dakika kazandıracak. Akıllıca kullan.";
			link.l1 = "Markiz... Birisi, lütfen yardım edin! Madam kendini iyi hissetmiyor! Çabuk!";
			link.l1.go = "Julianna_27";
		break;
		
		case "Julianna_27":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			GiveItem2Character(pchar, "obereg_5");
			GiveItem2Character(pchar, "totem_13");
			Log_Info("You have received amulet 'Turtle'");
			Log_Info("You have received amulet 'Joker'");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Julianna_28":
			dialog.text = "Hayır, hayır, iyiyim... Burada biraz havasız oldu... Çok özür dilerim beyler. Biraz temiz hava almak için sizi bir anlığına bırakacağım. Bensiz devam edebilirsiniz.";
			link.l1 = "...";
			link.l1.go = "Julianna_29";
		break;
		
		case "Julianna_29":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto1", "", 10.0); // уходит
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromId("FortFrance_Mayor");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
		break;
		
		case "Julianna_30":
			dialog.text = "Şu anda ve St. Pierre'de değil, ama tanıdığım biri var. Sana söz veriyorum Angerran, bu tabloya değecek...";
			link.l1 = "...";
			link.l1.go = "Julianna_31";
		break;
		
		case "Julianna_31":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_32":
			dialog.text = "Angerran, sen gerçekten imkansızsın! Kaybetmeyi öğren artık! Bu sadece bir oyun ve her şeyi önceden bilemezsin. Şarabını bitir ve giyin - kurallar değişmedi - kaybeden bu keyifli buluşmadan ayrılır.";
			link.l1 = "Markiz, bekleyin...";
			link.l1.go = "Julianna_33";
		break;
		
		case "Julianna_33":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_34":
			dialog.text = "Bu iş fazla ileri gidiyor, beyler! Hemen durun! Hepimiz yorucu bir gecenin ardından çok yorgunuz ve ne yazık ki misafirlerimden veda etmelerini rica etmek zorundayım. Tartışmanıza, eğer fikrinizi değiştirmezseniz, yarın devam edebilirsiniz; onurlu adamlara yakışan da budur. Ama burada kimse silah çekmeyecek, anlaşıldı mı?";
			link.l1 = "...";
			link.l1.go = "Julianna_35";
		break;
		
		case "Julianna_35":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_36":
			dialog.text = "Charles, ne yazık ki senden de gitmeni istemek zorundayım. Yukarı çıkıp kendine bir oda tut. Her şeyi ben ayarlayacağım. Benim için yaptıkların için sana minnettarım, ama biraz yalnız kalmaya ihtiyacım var ve sen de muhtemelen çok yorgunsundur.";
			link.l1 = "O kadar da kötü değil, madam, ama bir yatağa hayır demem. Bu sıradan eğlence, bana devasa bir düşman donanmasından daha ağır geldi. Biliyorum, bütün bunlar sizin için de kolay olmadı, Markiz. Biraz dinlenin ve merak etmeyin, bana hiçbir borcunuz yok. Şu anda tek ihtiyacım biraz uyku.";
			link.l1.go = "Julianna_37";
		break;
		
		case "Julianna_37":
			dialog.text = "Seni öğlene kadar uyandıracaklarından emin olacağım. Zaten şafak söktü, bu yüzden artık sana iyi geceler diyemem. İyi uyu.";
			link.l1 = "Sen de, Markiz.";
			link.l1.go = "Julianna_38";
		break;
		
		case "Julianna_38":
			DialogExit();
			GoldenGirl_SleepInBrothel();
		break;
		
		case "Julianna_39":
			dialog.text = "İşte buradasın, Charles. Açıkçası hiç uyuyamadım, ama sen dinlenmiş görünüyorsun. Uykun nasıldı? Kahvaltı yolda.";
			link.l1 = "Misafirperverliğiniz dillere destan, hanımefendi, fakat ne yazık ki bundan keyif alacak vaktim yok. Ekselansları, de Chievous'un yardımcıları, kazandığım gemiler - hepsi beni bekliyor.";
			link.l1.go = "Julianna_40";
		break;
		
		case "Julianna_40":
			dialog.text = "Sadece gemileri kazanmadın. Sana başka bir şey daha sormak istiyordum, Charles...";
			link.l1 = "Ben ne Jacques ne de Angerran’ım, markiz. Kadınların gönlünü kazanmak için kumar oynamam. Bana hiçbir borcunuz yok.";
			link.l1.go = "Julianna_41";
			link.l2 = "Benim korumam altındasınız, Markiz. Ne Jacques ne de Angerran sizi bir daha rahatsız etmeyecek, bunu size garanti edebilirim.";
			link.l2.go = "Julianna_42";
		break;
		
		case "Julianna_41":
			pchar.questTemp.GoldenGirl.J1 = "true";
			dialog.text = "Ya olağanüstü derecede onurlusun ya da âşıksın, Charles. Hem de bana değil. Ama yine de, sana sonsuz minnettarım, tüm kalbimle. Eğer sana bir şekilde yardımcı olabilirim dersen - sadece söyle.";
			link.l1 = "Julianne, zaman daralıyor ve önümde en zorlu görev duruyor. De Chievous tam bir alçak ve dürüst bir düello bile dün gece izlediğimiz gibi bitebilir. Her şey tamamen bittiğinde sonra konuşalım. Sessizlik içinde uyuma fırsatı verdiğin için sana minnettarım ve seni tekrar görmeyi dört gözle bekliyorum.";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_42":
			pchar.questTemp.GoldenGirl.J2 = "true";
			dialog.text = "Tüm kalbimle sana minnettarım, Charles... İnan bana, senin ödülün olmak benim için de bir çeşit zafer. Bu sohbeti daha... özel bir ortamda sürdürsek mi?";
			link.l1 = "Julianne, zaman daralıyor ve önümde en zorlu görev duruyor. De Chievous tam bir alçak, üstelik dürüst bir düello bile dün gece gördüğümüz gibi bitebilir. Tüm bunlar nihayet sona erdiğinde konuşalım. Bana huzur içinde uyuma fırsatı verdiğin için teşekkür ederim, seni tekrar görmeyi dört gözle bekliyorum.";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_43":
			dialog.text = "Sizi daha fazla oyalamayacağım, Kaptanım. Ama unutmayın, Angerran tehlikeli biridir. Dövüş yeteneklerini tam olarak bilemem, fakat birkaç savaşa katılmış ve Rocroi’de çarpışmış. Ayrıca çoğunu tabancayla kazandığı birkaç düelloyu da duydum. En önemlisi, sizin de fark ettiğiniz gibi, oldukça kurnaz biridir. Lütfen dikkatli olun ve sonrasında mutlaka yanıma uğrayın!";
			link.l1 = "İlgi size gerçekten çok yakışıyor, Markiz. Bana inanın, de Chievous yoluma çıkan ilk alçak değil. Ben hallederim. Şimdi gerçekten Ekselansları ile düello meselesini konuşmak için gitmeliyim.";
			link.l1.go = "Julianna_44";
		break;
		
		case "Julianna_44":
			dialog.text = "Yolun açık olsun, Kaptanım! Ve Jacques’a söyle, evimin kapılarından olabildiğince uzak dursun.";
			link.l1 = "Söz veriyorum. Görüşürüz, Markiz!";
			link.l1.go = "Julianna_45";
		break;
		
		case "Julianna_45":
			DialogExit();
			GoldenGirl_ToGovernor();
		break;
		
		case "Julianna_46":
			dialog.text = "Kaptan, başardınız, ne büyük rahatlama! Nasıl geçti? Kanıyor musunuz?!";
			link.l1 = "Bu benim kanım değil... en azından hepsi değil. Markiz, de Chievous nerede?";
			link.l1.go = "Julianna_47";
		break;
		
		case "Julianna_47":
			dialog.text = "Ben de sana aynı şeyi soracaktım – onu indirmedin mi? Ne oldu? Neden kasabanın yarısı kadar muhafız dışarıda bekliyor?";
			link.l1 = "Valiye başının belada olabileceğini söyledim. De Chievous yaralandı ve kaçtı, adamlarını üstümüze saldı. Tam bir katliamdı. Gerçi, böyle hikayeler senin güzel kulaklarına göre değil. Bitti artık. Ondan da, bizim 'tatlı' Jacques'tan da kurtuldun.";
			link.l1.go = "Julianna_48";
		break;
		
		case "Julianna_48":
			dialog.text = "Bu çok kötü, Charles. Angerran de Chievous gibi düşmanlar, fırsatın varken tamamen ortadan kaldırılmalı. O adamı yıllardır tanırım – affedici biri değildir. Er ya da geç, intikamını almanın bir yolunu bulacaktır. Ama senin böyle kambur durmanı hiç beğenmedim, yaranla ilgilenildi mi?";
			link.l1 = "Sadece ufak bir sıyrık, çok daha kötülerini gördüm. Biraz acıyor, hepsi bu. Benimle ilgilendiğiniz için teşekkür ederim hanımefendi, ama artık gitmeliyim...";
			link.l1.go = "Julianna_49";
		break;
		
		case "Julianna_49":
			dialog.text = "Captain, you gambled for me, risking your ships and wealth; you fought for me in a deal, risking your life and career. The least I can do for you is tend to your wounds and give you a safe place to rest. No! I don't want to hear any more of this. Take my hand and follow me upstairs. Your room is waiting for you.";
			link.l1 = "Teklifinizi kabul ediyorum hanımefendi, teşekkür ederim. Ama sizi zahmete sokmak istemem. Yukarı kendim çıkarım.";
			link.l1.go = "Julianna_50";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.J2") && pchar.questTemp.GoldenGirl.Vine == "red")
			{
				link.l2 = "Markiz, benim koruyucu meleğimsiniz. Şimdi borçlu olan benim, korkarım.";
				link.l2.go = "Julianna_52";
			}
		break;
		
		case "Julianna_50":
			dialog.text = "Charles, sen tam bir şövalyelik örneğisin! Yemin ederim, böyle devam edersen aklımı kaybedeceğim! Peki, şövalyem, Denise'i sana göndereceğim, yaralarınla ilgilenecek, tıpkı iyi bir hekim gibi.";
			link.l1 = "Teşekkür ederim, markiz. Kalbim zaten başkasına ait olmasaydı, memnuniyetle oyuna katılırdım. Ama ne yazık ki! İyi geceler!";
			link.l1.go = "Julianna_51";
		break;
		
		case "Julianna_51":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_WithoutJulianna"); // найти нужные локаторы
		break;
		
		case "Julianna_52":
			dialog.text = "Bu durumda, hemen bana uyacaksın. Elimi tut ve dediklerimi yap. Denise! Yukarıya pamuk, sıcak şarap ve yiyecek bir şeyler getir! Hadi gidelim, Kaptanım. Ve unutma - bu sefer tartışmak yok!";
			link.l1 = "Dediğiniz gibi, Markiz, tamamen sizinim.";
			link.l1.go = "Julianna_53";
		break;
		
		case "Julianna_53":
			DialogExit();
			pchar.questTemp.GoldenGirl.JulianaSex = "true";
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_KissJulianna");
			sld = characterFromId("Julianna");
			ChangeCharacterAddressGroup(sld, "FortFrance_Brothel_room", "goto", "goto2");
		break;
		
		case "Julianna_54":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Günaydın, Charles. O 'çiziklerin' nasıl, iyi misin?";
				link.l1 = "Çabalarınız sayesinde kendimi yeniden doğmuş gibi hissediyorum. Lütfen en içten teşekkürlerimi kabul edin, Julianna.";
				link.l1.go = "Julianna_56";
			}
			else
			{
				dialog.text = "Günaydın, kahramanım. O 'çiziklerin' nasıl, bakalım?";
				link.l1 = "Endişeniz için teşekkür ederim hanımefendi, tamamen iyiyim. Denise'iniz gemimde doktorluk yapsa servet öderdim. Gerçekten bir mucize!";
				link.l1.go = "Julianna_55";
			}
		break;
		
		case "Julianna_55":
			dialog.text = "Bunu ayarlamak kolay olmayacak diye korkuyorum. Ama ciddi bir sebep olmadan sizi uyandırmaya asla cesaret edemezdim. İnanın bana, uykunuzu gözü pek bir şekilde korudum, fakat aşağıdaki adam çok ısrarcı. Kendi ekibinizden biri olduğunu ve bunun acil olduğunu söylüyor.";
			link.l1 = "Mürettebatım mı? Beni uyandırmakla doğru yaptınız, markiz! Hemen yola çıkacağım.";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_56":
			dialog.text = "Farklı koşullarda isterdim, kaptanım, ama bunu ertelememiz gerekecek. Aşağıda seni pek de eğitimli olmayan bir monsieur bekliyor. Kendisinin tayfanın bir üyesi olduğunu ve işinin acil olduğunu söylüyor.";
			link.l1 = "Bu konuya döneceğiz, Madam, döndüğümde. Umarım bu yine İspanyolların kuşatma başlatmasıyla ilgili değildir.";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_57":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload9_back", "GoldenGirl_BadNews");
		break;
		
		case "Julianna_58":
			dialog.text = "Charles, geri döndün! Adamın ne haber getirdi? Vedalaşmadan gittin!";
			link.l1 = "Özür dilerim, markiz. De Chievous yine kirli oynadı. Gemimi çaldı ve bu gece denize açıldı. O gemide güvendiğim subaylarımdan biri vardı ve onu o alçağın ellerine bırakamam.";
			link.l1.go = "Julianna_59";
		break;
		
		case "Julianna_59":
			dialog.text = "O mu? Geminde bir kadın subay mı var? Bu, denizcilikle ilgili bildiğim her şeye aykırı. Onun hâlâ hayatta olduğunu düşünmene sebep olan ne?";
			link.l1 = "Umarım. Julianna, şu ana kadar elimde sadece umut var. Angerran de Chievous hakkında daha fazla şey öğrenmeliyim. Mutlaka nereye gittiğini bulmalıyım! Onu geri getirmeliyim!";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) link.l1.go = "Julianna_62";
			else link.l1.go = "Julianna_60";
		break;
		
		case "Julianna_60":
			dialog.text = "Şimdi anlıyorum! Gerçekten de âşıksın, şövalyem! Böylesine sadakat ve bağlılık için, hiç düşünmeden ömrümün yarısını seve seve verirdim!";
			link.l1 = "Yemin etmedim, ama bu kadın benim için çok şey ifade ediyor, markiz.";
			link.l1.go = "Julianna_61";
		break;
		
		case "Julianna_61":
			dialog.text = "Bu kıskançlık dokunaklı. Duydun mu Charles, senin için kıskanacak kadar hazırım! Ama hangi kadın gerçek aşkın sesine kayıtsız kalabilir ki? Üstelik beni kurtardın, şövalyem, elbette sana yardım edeceğim. Sor bakalım.";
			link.l1 = "Teşekkür ederim. De Chievous'u uzun zamandır tanıyorsun. Bunca olaydan sonra babasının öfkesinden saklanmak için nereye gidebilir?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_62":
			dialog.text = "Sana güzel bir brunch teklif etsem ne dersin? İki gündür o... kızı düşünmedin, belki bir gün daha bekleyebilir?";
			link.l1 = "Markiz, gözünüzde nasıl görünebileceğimin farkındayım, ama olan oldu. Her ne kadar yemin etmemiş olsam da, kalbim ona ait. Lütfen beni anlamanızı ve bana yardım etmenizi rica ediyorum.";
			link.l1.go = "Julianna_63";
		break;
		
		case "Julianna_63":
			dialog.text = "Hadi ama Charles! Bir hayat kadınına aşk laflarıyla kendini savunmak mı? Uzun zamandır böyle gülmemiştim! Gerçekten inanılmazsın! Rahat ol, bu evde olan bu evde kalır. Sana olan borcumu unutmadım. Sor bakalım ne istiyorsun.";
			link.l1 = "Teşekkür ederim. De Chievous'u uzun zamandır tanıyorsun. Bunca tantanadan sonra babasının gazabından kaçmak için nereye gitmiş olabilir?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_64":
			dialog.text = "Doğrusunu söylemek gerekirse, Angerran de Chievous'u davet etmek belki de en keyifli iş olmayabilir, ama siyasi açıdan hâlâ çok faydalı. O, Fransa'nın müttefikleri de dahil olmak üzere her yerde hoş karşılanan bir misafirdir. Ama biliyorum ki, ona her zaman yardım edip sığınak sağlayacak tek bir adam var buralarda. Guadeloupe kolonimizin valisi Francois de Lyon. Kendisi Kont de Levi Vantadur'un eski bir dostudur ve bu piçe her zaman özel bir sempati duymuştur.";
			link.l1 = "Guadeloupe olsun! Umduğumdan daha iyi bir ipucu bu! Eğer bu akşam yelken açarsak, onlardan sadece bir gün geride olacağız.";
			link.l1.go = "Julianna_65";
		break;
		
		case "Julianna_65":
			dialog.text = "Bekle, Charles, başka bir şey daha var. Kısa süre önce sana bir mektup geldi. Önce düelloyla ilgili olduğunu sandım, ama artık pek emin değilim. Al, işte burada.";
			link.l1 = "Mühür yok, ama kağıdı pahalı. Bu hoşuma gitmedi...";
			link.l1.go = "Julianna_66";
		break;
		
		case "Julianna_66":
			DialogExit();
			AddQuestRecordInfo("GG_Letter_1", "1");
			chrDisableReloadToLocation = true;
			npchar.dialog.currentnode = "Julianna_67";
			LAi_SetStayType(npchar);
		break;
		
		case "Julianna_67":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Hadi Charles! Beni merakta bırakma, ondan mı geldi?";
			link.l1 = "Evet, ondan. O hayatta! Gemimi çalarken onu yakalamış. Şimdi ise medeni bir ortamda buluşup konuşmamızı öneriyor. Dediğin gibi, Guadeloupe, Basse-Terre.";
			link.l1.go = "Julianna_68";
		break;
		
		case "Julianna_68":
			dialog.text = "Monsieur de Lyons kesinlikle Leve Vantadur'un oğlunu senden önce seçecek. De Chievous sana yine tuzak kurabilir! Beni savunarak çok güçlü bir düşman edindin, Charles. Sana yardım edebilmeyi isterdim ama sanırım yapabileceğim tek şey dikkatli olmanı istemek.";
			link.l1 = "Julianne, Yeni Dünya’da her zaman doğrudan gitseydim asla başaramazdım. Karanlık işler benim uzmanlık alanım değil, ama oyuna nasıl dahil olacağımı bilirim.";
			link.l1.go = "Julianna_69";
		break;
		
		case "Julianna_69":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			chrDisableReloadToLocation = false;
			GoldenGirl_ToBaster();
		break;
		
		case "Julianna_70":
			dialog.text = "Bir haber var mı, kaptan?";
			link.l1 = "Ne yazık ki, hiçbir şey...";
			link.l1.go = "Julianna_71";
		break;
		
		case "Julianna_71":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
		break;
		
		case "Julianna_72":
			dialog.text = "Tekrar hoş geldin, Charles! Hayatta ve sapasağlam olmana sevindim. Ne haber?";
			link.l1 = "de Chievous'un yetenekleri hakkında bildiğimiz her şey büyük bir hafife alma oldu. O alçak benim... subayımı rehin tutuyor ve fidyeyi toplamak için sadece iki haftam var. Sizin yardımınız olmadan bunun mümkün olamayacağından korkuyorum.";
			link.l1.go = "Julianna_73";
		break;
		
		case "Julianna_73":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, aşkın gerçekten bir rüzgar çiçeği gibi, yine de sana çok şey borçluyum ve elimden gelenin en iyisini yapacağım. Sana nasıl yardımcı olabilirim?";
			}
			else
			{
				dialog.text = "Charles, sana yaptıklarını asla unutmayacağımı zaten söylemiştim. Borcumu ödemek için elimden geleni yapacağım. Hazırım, ama bu konuda sana nasıl yardımcı olabileceğimi tam olarak anlamıyorum.";
			}
			link.l1 = "Lütfen otur, Julianna. Bak, Angerran'ın fidyesi... sensin. Ve resmi bir koruma falan demiyorum, kastediyorum ki seni kargo ambarında zincirli bir esir olarak götürecek.";
			link.l1.go = "Julianna_74";
		break;
		
		case "Julianna_74":
			dialog.text = "Nutkum tutuldu... Ama yüzündeki ifadeden bunun bir şaka olmadığını anlıyorum. Aklını mı kaçırmış?";
			link.l1 = "Daha çok, yaptığımı düşündüğü için böyle. O kadar çaresiz ki, her türlü sınırı aşmaya hazır.";
			link.l1.go = "Julianna_75";
		break;
		
		case "Julianna_75":
			dialog.text = "Ve ne yani, bana mı soruyorsun? Kaçırılırken çığlık atmamamı mı istiyorsun? Kaptan, sence de bu biraz fazla bir istek değil mi? Sana çok şey borçluyum, ama başkasının aşkını kurtarmak için kendi hayatımı şerefsiz bir herifin ellerine bırakmak... Asil olan sensin burada, ben ise son derece gerçekçi ve maddiyatçı bir kadınım.";
			link.l1 = "Korkarım hanımefendi, tam olarak sizden bunu istiyorum. Eşyalarınızı toplayın, gidiyoruz. Bunun için gerçekten üzgünüm ama vaktimiz dar.";
			link.l1.go = "Julianna_76";
			link.l2 = "Markiz, bana güvenen kadınları kaçırmam. Ve bu bizim için bir fırsat olabilir.";
			link.l2.go = "Julianna_81";
		break;
		
		case "Julianna_76":
			dialog.text = "Sürekli şaşırtıyorsun beni, Charles. Duydun mu? Sana ayırdığım tüm hoşgörü buydu ve şimdi paramparça oldu. Sevgiymiş, değilmiş, fark etmez; seni beni kaçırmana asla izin vermem. Muhafızlar! Yardım edin!!! Kimse yok mu!!!!";
			link.l1 = "Ben de bizi arkadaş sanmıştım.";
			link.l1.go = "Julianna_77";
		break;
		
		case "Julianna_77":
			DialogExit();
			LAi_SetActorType(npchar);
			GoldenGirl_PatrolInBrothel();
		break;
		
		case "Julianna_78":
			dialog.text = "Bu bir rezalet! Salonumu ne hale getirdiniz?! Bu nasıl bir şeytani dehşet? Charles, kendine gel! Sen bir asilzadesin, lanet olası bir korsan değilsin!!";
			link.l1 = "Sana zaten özür diledim. İşleri daha da karmaşıklaştırmamanı istedim - dinlemedin. İnan bana, yaptıklarımdan hoşlanmıyorum ama başka çarem yok. O kadın için ne gerekiyorsa yapacağım.";
			link.l1.go = "Julianna_79";
		break;
		
		case "Julianna_79":
			dialog.text = "Böyle bir şövalyeyi kim ister ki? Ben kendim giderim, bana dokunma! Bir inek çalmıyorsun, biraz gururun olsun!";
			link.l1 = "Pekala. Benimle gelin, hanımefendi. Arkamda kalın ve başınızı eğik tutun - belki ateş etmeye başlarlar.";
			link.l1.go = "Julianna_80";
		break;
		
		case "Julianna_80":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.greeting = "Marquesa_again";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.goldengirl_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_alarm.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.goldengirl_alarm.function = "GoldenGirl_AlarmSP";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1.location = "Dominica";
			pchar.quest.goldengirl_dominica_alarm.function = "GoldenGirl_DominicaAlarm";
			ChangeCharacterComplexReputation(pchar, "nobility", -15);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			ChangeOfficersLoyality("bad_all", 5);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "14");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			pchar.questTemp.GoldenGirl = "dominica_alarm"; // флаг - силовое решение
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
		break;
		
		case "Julianna_81":
			dialog.text = "Bir an için seni hiç tanımadığımı sandım, Charles. O bakış... Peki şimdi ne yapacaksın? Hangi şanstan bahsettin?";
			link.l1 = "Neden o alçak sana ulaşmak için beni kullanıyor? Neden istediğini almak yerine o kart oyununu ayarladı? Neyden korkuyor?";
			link.l1.go = "Julianna_82";
		break;
		
		case "Julianna_82":
			dialog.text = "Hiçbir şey. Ne yazık ki, tüm bunların ardındaki nedenler sıkıcı ve basit. Kont Henri hâlâ bana karşı bir zaaf besliyor. Angerran bana istemediğim bir şey yaparsa çok büyük bir risk alır. Üzgünüm Charles, ama bu çıkmaz bir yol. O her şeyi inkâr edecek ve paçayı kurtaracak. Kimse senin, yani kaçıranın, sözlerine inanmaz; babası ise seni mahveder.";
			link.l1 = "Lanet olsun! Keşke bu noktaya gelmeseydik... Hazırlan, markiz, gitmemiz gerek. Ve evet, senden sessiz olmanı rica ediyorum.";
			link.l1.go = "Julianna_76";
			link.l2 = "Ama o herifin babasından başka zayıf noktaları da olmalı, değil mi? Mükemmel biri değil, tam aksine, mükemmelliğin tam tersi!";
			link.l2.go = "Julianna_83";
		break;
		
		case "Julianna_83":
			dialog.text = "Bunun bizim için faydalı olup olmayacağını bilmiyorum... Angerran'ın yerel korsan baronu ile bazı işleri vardı. Jacques Baraban?";
			link.l1 = "Barbazon, hanımefendi. İkisi de iyi insanlar! Ama İyi Yürekli Jacques bana hiç sıcak bakmaz, ayrıca Le Francois'ya saldırmak için kesin bir güvenceye ihtiyacım var.";
			link.l1.go = "Julianna_84";
		break;
		
		case "Julianna_84":
			if (CheckAttribute(pchar, "questTemp.Portugal.GG1"))
			{
				dialog.text = "Yine fazla açık sözlüsün, şövalyem. Kaptan Moreno'yu hatırlıyor musun? Senin ikinci kumar rakibin? Bahse girerim buraya Angerran yüzünden geldi. Bizim için değerli bir şey biliyor olmalı.";
				link.l1 = "Kaptan Moreno, hah! Evet, tabii. Hâlâ şehirde mi? Onu nerede bulabilirim?";
				link.l1.go = "Julianna_85";
			}
			else
			{
				dialog.text = "Yine fazla açık sözlüsün, şövalyem. Birileri her zaman bir şeyler bilir ve bazı durumlarda herkes ağzını tutamaz. Bu evde... öğrencilerim her şeyi duyar. Bana bir gün ver, daha fazlasını öğrenirim ya da sana yardımcı olabilecek birini bulurum.";
				link.l1 = "Markiz, endişelenmek size yakışıyordu, ama öfkelenmek size daha da çok yakışıyor. Teşekkür ederim, bana umut aşılıyorsunuz!";
				link.l1.go = "Julianna_86";
			}
		break;
		
		case "Julianna_85":
			pchar.questTemp.GoldenGirl.Portugal = "true";
			dialog.text = "Evet, hâlâ burada ve onu aramak için boşuna koşturmanı istemem. Yarın akşam buraya gel – Kaptan Moreno seni burada, bu odada bekliyor olacak. Keşke daha fazlasını yapabilsem, ama elimden bu kadar geliyor Charles.";
			link.l1 = "Bu zaten fazlasıyla yeterli, Markiz. Onun yanımda olmasıyla işler çok daha kolay olacak. Teşekkür ederim. Yarın akşam görüşürüz.";
			link.l1.go = "Julianna_87";
		break;
		
		
		case "Julianna_86":
			pchar.questTemp.GoldenGirl.Portugal = "false";
			dialog.text = "Keşke bunu senden başka bir durumda duysaydım, Charles. Yarın akşam yanıma gel. Umarım ihtiyacın olanı bulmuş olurum.";
			link.l1 = "Tekrar teşekkürler, Julianna! O zaman yarın akşam görüşürüz.";
			link.l1.go = "Julianna_87";
		break;
		
		case "Julianna_87":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			SetFunctionTimerCondition("GoldenGirl_JuliannaOneDay", 0, 0, 1, false); // таймер
		break;
		
		case "Julianna_88":
			pchar.quest.GoldenGirl_JuliannaOneDayFail.over = "yes"; //снять прерывание
			if (pchar.questTemp.GoldenGirl.Portugal == "true")
			{
				dialog.text = "İşte buradasın, dostum! Kaptan Moreno seni zaten bekliyor.";
				link.l1 = "...";
				link.l1.go = "Julianna_89";
			}
			else
			{
				dialog.text = "Charles, sanırım bir şey buldum. Kaptan Moreno'yu hatırlıyor musun? Hani o uğursuz gecede sana karşı oynayan?";
				link.l1 = "Evet, tam bir serseri.   Peki ya o?";
				link.l1.go = "Julianna_102";
			}
		break;
		
		case "Julianna_89":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			chrDisableReloadToLocation = true;
		break;
		
		case "Julianna_90":
			dialog.text = "Ben bunu her zaman biliyordum, Bartolomeo de la Cueva. Zaten bu yüzden ilk başta seni partime davet ettim. Yemeğe acı biber eklemek gibiydi. Senin ve adamlarının bu adada haftalardır dolaştığını biliyorum. Bunun bir şekilde Le Francois'nin korsan baronu ve Angerran de Chievous ile bağlantılı olduğuna eminim. Arkadaşıma her şeyi anlat, karşılığında efsanevi adını gizli tutarız. Aksi takdirde, kapıların arkasında bekleyen muhafızları çağırırım. Zaten gelişinle birlikte onları çağırmıştım.";
			link.l1 = "...";
			link.l1.go = "Julianna_91";
		break;
		
		case "Julianna_91":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_92":
			dialog.text = "Sadece onlar değil! Angerran bana bir kolye hediye etti, hem de ne güzel! Büyük, kusursuz incilerden yapılmış, tam ortasında güney gecesi kadar koyu bir tane var. Ama kolyeyi buradaki kuyumculardan sipariş etmiş!";
			link.l1 = "...";
			link.l1.go = "Julianna_93";
		break;
		
		case "Julianna_93":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_94":
			dialog.text = "Bence bunu sadece bana lüks bir hediye vererek gönlümü almak için yapmadı. Gerçi, o hediye nezaket sınırları içinde bana kendini sevdirmek için son çaresiydi. Angerran'ın ne unvanı ne de toprağı var, hatta sahip olduğu fırkateyn bile babasının kararına bağlı. Gücünü ve nüfuzunu kullanıyor ama kendi gelir kaynağı yok. Belki de babasının bağışlarını beklemekten sıkıldı ve mali durumunu düzeltmeye karar verdi?";
			link.l1 = "Bekleyin, hanımefendi! Kart oyunu! Eğer haklıysak ve de Chievous her şeyi önceden planladıysa, valimizi köşeye sıkıştırmak için büyük bir bahis parası bulması gerekirdi. Böyle bir parayı ailesinden istemesi, istemediği bir ilgiyi çekebilirdi. Korsanlardan çalınmış hazineleri tekrar çalmak ise, gerekli parayı sessiz ve güvenli bir şekilde elde etmenin yolu gibi görünüyor. Kimsenin haberi olmazdı!";
			link.l1.go = "Julianna_95";
		break;
		
		case "Julianna_95":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_96":
			dialog.text = "Bize, Charles! Angerran bu sefer yaptığıyla paçayı sıyıramaz. Bana karşı olan üstünlüğü artık fazla ileri gitti ve bu konuda sana yardımcı olmak isterim.";
			link.l1 = "";
			link.l1.go = "Julianna_97";
		break;
		
		case "Julianna_97":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_23";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_98":
			dialog.text = "Bir kaybeden korsan ve neredeyse âşık olmuş bir hayat kadını. Charles, kendine tam bir rüya takımı bulmuşsun!";
			link.l1 = "Yine de, ikinize de teşekkür ederim. Gerçekten! Şimdi biraz düşünmem ve bir plan yapmam gerekiyor.";
			link.l1.go = "Julianna_99";
		break;
		
		case "Julianna_99":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_25";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_100":
			dialog.text = "Bu evde misafirlerin aradığı her şey var. Gerekli hazırlıkları yapacağım. Hazır olduğunda bize katıl, Charles.";
			link.l1 = "Pekala, hanımefendi.";
			link.l1.go = "Julianna_101";
		break;
		
		case "Julianna_101":
			DialogExit(); // фин 3
			AddQuestRecord("GoldenGirl", "22");
			npchar.Dialog.currentnode = "Julianna_119";
			LAi_SetOwnerType(npchar);
		break;
		
		case "Julianna_102":
			dialog.text = "Hiçbir şey, ama kasabada birisi onu arıyor. O geceki diğer misafirlerle birlikte senin hakkında da sorup soruşturuyorlar. Şu anda tam olarak neler döndüğünü bilmiyorum, ama eminim düşündüğünden daha büyük bir işin içine bulaştın.";
			link.l1 = "Daha büyük bir şey mi? Ne demek istiyorsun, Julianne?";
			link.l1.go = "Julianna_103";
		break;
		
		case "Julianna_103": // запускаем Кортни
			chrDisableReloadToLocation = true;
			DialogExit();
			sld = characterFromId("Cortny");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_104":
			dialog.text = "Angerran... Yani, Monsieur de Chievous bana harika bir inci kolye hediye etti. İncilerden biri gece kadar siyahtı. Sadece arkasında güzel bir hikaye olan sahte bir şey sandım. Hiç takmadım, yanlış umutlar vermek istemedim, ama o kadar büyüleyici ki gözümü alamıyorum.";
			link.l1 = "";
			link.l1.go = "Julianna_105";
		break;
		
		case "Julianna_105":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_106":
			dialog.text = "Ne yapacaksın, Charles? Neler olup bittiğine dair bir fikrin var mı?";
			link.l1 = "Henüz değil, ama yapacağım. De Chievous ciddi bir işin içinde ve bu benim fırsatım. Kendi ülkesi ona dokunmaya cesaret edemez, ama İngiliz yetkilileri edebilir. Seni kaçırmak istemem, Julianne.";
			link.l1.go = "Julianna_107";
		break;
		
		case "Julianna_107":
			dialog.text = "Bu gerçekten çok nazikçe, Charles, ama pek komik değil.";
			link.l1 = "";
			link.l1.go = "Julianna_108";
		break;
		
		case "Julianna_108":
			DialogExit();
			chrDisableReloadToLocation = false;
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.hour  = 20.00;
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.function = "GoldenGirl_TimeCortny";
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.hour  = 23.00;
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.function = "GoldenGirl_TimeCortnyFail";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			AddQuestRecord("GoldenGirl", "17");
		break;
		
		case "Julianna_109":
			dialog.text = "Charles, bir şey öğrenebildin mi? Gergin görünüyorsun... Ne oldu?";
			link.l1 = "Kahretsin! Keşke işler farklı olsaydı... Eşyalarını topla, gitmeliyiz Markiz. Lütfen sorun çıkarma.";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_110":
			pchar.quest.goldengirl_time_cortny_fail.over = "yes"; //снять прерывание
			dialog.text = "Charles, içeri gel. Baronet zaten burada ve güzel bir sohbet ettik. Ona az önce devam eden olaylara olan ilginden bahsediyordum.";
			link.l1 = "Julianne, bunun akıllıca olduğundan pek emin değilim...";
			link.l1.go = "Julianna_111";
		break;
		
		case "Julianna_111":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_112":
			dialog.text = "Baronet, adamlarınız kapının arkasında bir şey düşürmüş gibi görünüyor! Onlara biraz daha dikkatli olmalarını söyler misiniz?";
			link.l1 = "";
			link.l1.go = "Julianna_113";
		break;
		
		case "Julianna_113":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_114":
			dialog.text = "Berbat! Şimdi ne yapacağız?!";
			link.l1 = "Lanet olsun! Keşke her şey farklı olsaydı... Eşyalarını topla, gitmeliyiz, Marquise. Lütfen sorun çıkarma.";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_115":
			dialog.text = "Tanrı aşkına! Oturma odamı ne hale getirdiniz beyler?! Burası Ortaçağ kabusu gibi görünüyor! Kim bu insanlar? Peki ya muhafızlar nerede?";
			link.l1 = "İyi misin, Julianne? Güzel. Eminim muhafızlar hak ettikleri rüşveti bir meyhanede harcıyordur. Baronet, tebriklerimi sunuyorum - Goodman Jack’i fena halde kızdırmayı başardın. Böyle dağınık ve kötü hazırlanmış bir suikast girişimi hiç onun tarzı değil.";
			link.l1.go = "Julianna_116";
		break;
		
		case "Julianna_116":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_21";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_117":
			dialog.text = "Heyecanlı sohbetinizi böldüğüm için özür dilerim, ama aranızda yaralı olan yoksa, hadi bir odaya geçelim. Böyle bir manzara bir hanımefendi için pek rahatlatıcı değil... Sadece tavan kan içinde değil!";
			link.l1 = "O zaman yukarı çıkın, Markiz. Biraz uzanıp bu kanlı ortamdan uzaklaşmanız iyi olur. Baronet Cortney ile ben her şeyi konuşacağız. Devam edelim mi?";
			link.l1.go = "Julianna_118";
		break;
		
		case "Julianna_118":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto2", "", 20.0);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_24";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_119":
			dialog.text = "Charles, planını bizimle paylaşmaya hazır mısın?";
			link.l1 = "Neredeyse. Söylesene, de Chievous titiz biri midir? Kayıtlarını ve defterlerini düzenli tutar mı?";
			link.l1.go = "Julianna_120";
		break;
		
		case "Julianna_120":
			dialog.text = "Angerran, iş finanslara gelince tam bir erteleme ustasıdır! Tanıdığım hiçbir bankacı onun kadar evrak imzalamaz. Sanırım çocukluğundan beri böyledir; babasının kim olduğunu bilmeden, yoksulluk içinde sokaklarda büyümüş.";
			link.l1 = "Harika! Şimdi, günlüğüne ve defterlerine ihtiyacımız var! Bunlar İngilizler için geçerli birer kanıt olacak. Onları nasıl ele geçireceğimizi bulmalıyız! Keşke gemisi elimdeyken bundan haberim olsaydı... ah.";
			link.l1.go = "Julianna_121";
		break;
		
		case "Julianna_121":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_27";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_122":
			dialog.text = "Bekle, Charles, bunca şeyden sonra kendimi de Chievous’a bir çiftlik keçisi gibi satmana izin vereceğimi gerçekten mi düşünüyorsun?";
			link.l1 = "Endişelenme Julianne, sadece birkaç gün sürecek. Sana Çin'den gelmiş paha biçilmez bir vazo gibi davranacaklarına söz veriyorum. Yanılıyorsam düzelt, ama de Chievous takas sırasında asla ortaya çıkmaz, değil mi?";
			link.l1.go = "Julianna_123";
		break;
		
		case "Julianna_123":
			dialog.text = "Bundan eminim. Angerran, François de Lyons'un koruması altında bekleyecek ve asla seninle açık denizde karşılaşmaya cesaret edemeyecek. Ama benim esir alınmam hakkında...";
			link.l1 = "";
			link.l1.go = "Julianna_124";
		break;
		
		case "Julianna_124":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_29";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_125":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, sözünü kesmek istemem ama, bütün bunlar hakkında benim fikrimi sormayı unuttuğunu fark etmedin mi? Haftalarca o gıcırdayan tabutların içinde... Benden ne istediğinin farkında mısın sen?! Belli ki o... kıza bağlandın, ama ben senin tayfalarından biri değilim! Kusura bakma ama bütün bunlar bana ciddi bir aşk hikâyesi gibi gelmiyor.";
				link.l1 = "Korkarım, Markiz, ısrar etmek zorundayım. Onu kaybetmeyi göze alamam.";
				link.l1.go = "Julianna_127";
				link.l2 = "Hepimiz hata yaparız, Julianna. Bunu en iyi sen bilirsin. Senden bana yardım etmeni istiyorum.";
				link.l2.go = "Julianna_126";
			}
			else
			{
				dialog.text = "Charles, sözünü kesmek istemem ama, bütün bunlar hakkında fikrimi sormayı unuttuğunu fark etmedin mi? Haftalarca o gıcırdayan tabutların içinde... Benden ne istediğinin farkında mısın?! Duyguların şövalyelikle ilgili klasik edebiyatlara layık, ama ben sadece sıradan bir saraylı kadınım. Sana hayranım ve sana yardım etmek istiyorum, ama her şeyin bir sınırı var!";
				link.l1 = "";
				link.l1.go = "Julianna_128";
			}
		break;
		
		case "Julianna_126":
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			if(sti(pchar.reputation.nobility) > 65)
			{
				pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
				dialog.text = "Anlıyorum, Charles. Gerçek ve kusursuz aşka inanmak istiyorum, ama sanırım bu dünyada öyle bir şey yok.";
				link.l1 = "Teşekkür ederim, markiz. Bu sefer her şeyi yoluna koyacağım. Bu yaşadıklarımdan çok şey öğrendim ve yaptıklarımın bedelini çok ağır ödememek için dua ediyorum.";
				link.l1.go = "Julianna_129";
			}
			else
			{
				dialog.text = "Kararını verdin, ben de başından beri yanında oldum, ama artık yeter. Zaten benim odamda terk ettiğin bir aşk uğruna her şeyi feda etmeye kalkışıyorsun. Bunların hepsi çok dokunaklı, Charles, ama ben artık o kadar genç ve saf değilim.";
				link.l1 = "Korkarım, Markiz, ısrar etmek zorundayım. Onu kaybetmeyi göze alamam.";
				link.l1.go = "Julianna_127";
			}
		break;
		
		case "Julianna_127":
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
			dialog.text = "Pekala, Kaptan, nasıl istersen öyle yap. Sana karşı koymayacağım, ama bunu istemeyerek yaptığımı bil.";
			link.l1 = "Beni nasıl istersen öyle düşün, Julianna, bunu hak ettim. Ama onu geri alacağım, ne pahasına olursa olsun\nJulianna, dinle, senden ne istediğimi biliyorum. Her şeyi geride bırakmanı ve başkalarının seni belirsiz bir oyuna sürüklemesine izin vermeni istiyorum. Ama şu anda, tek umudum sensin! Bu konuda yardımına ihtiyacım var ve ölünceye dek sana borçlu kalacağım!";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_128":
			pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
			dialog.text = "Pekala, Kaptan. Sonunda Angerran kesin olarak durdurulmalı. Sana yardım edeceğim, ama söyle bakalım, beni onun gemisinden nasıl kurtaracaksın?";
			link.l1 = "...";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_129":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_31";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_130":
			dialog.text = "Bekle. İncili kolyemi alabilirsin, İngilizler siyah incilerin peşinde, değil mi? Bu kolye onları seni dinlemeye zorlar. Peki ya sonra?";
			link.l1 = "Sıradaki adımda, müfettişi gemime alacağım ve Guadeloupe'a yelken açacağız. Seninle birlikte döndüğünde de Chievous'nun firkateyninde resmi bir arama yapacağız. Mercury meselesi, müttefikimizi ilgilendiren ciddi bir olaydı, bu yüzden De Lyon buna izin vermek zorunda kalacak!";
			link.l1.go = "Julianna_131";
		break;
		
		case "Julianna_131":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_33";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_132":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = " O,   beni esaretten   kendi adamlarının   kurtardığını   herkese   anlatacak.   Ve   bil,   Kaptan,   ben   onlara   ne   anlatacağımı   henüz   seçmedim. ";
				link.l1 = "Hiçbir şey söylememek gayet yeterli olurdu, markiz. İnan bana, seni buradan çıkaracağım ve Angerran her şeyin bedelini ödeyecek.";
			}
			else
			{
				dialog.text = "Onlara, evimden yabancılar tarafından kaçırılıp Angerran'ın gemisine götürüldüğümü söyleyeceğim. Sanki beni kaçırmaları için paralı askerler tutmuş gibi görünecek.";
				link.l1 = "Angerran'ın tabutuna bir çivi daha, markiz.";
			}
			link.l1.go = "Julianna_133";
		break;
		
		case "Julianna_133":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_35";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_134":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Bana sabaha kadar süre ver, yoksa beni bir çuvala koyup taşımak zorunda kalırsın. Yanıma birkaç adamını da gönder, sonuçta itibarlı bir kadın konforsuz seyahat edemez. Charles, beni kurtardın ve ben de sana yardım edeceğim, ayrıca lütfen bu paha biçilmez siyah inciyi kabul et, sana hediyem olsun. Eğer bu iş yolunda giderse, ödeşmiş oluruz.";
				link.l1 = "Dediğiniz gibi, Markiz. İkinize de yolunuz açık olsun! Her şey bittiğinde burada tekrar görüşürüz.";
			}
			else
			{
				dialog.text = "Gün doğarken hazır olacağım. Bir yük ambarında sürünmeye hiç niyetim yok, o yüzden bana düzgün bir oda ya da her ne diyorsanız hazırlayın. Charles, al bunu. Bu değerli bir siyah inci. Farkındayım, buradan daha değerli ama bazı şeyler altınla ölçülmez. Umarım işine yarar. Tanrı yardımcın olsun!";
				link.l1 = "Yolunuz açık olsun, ikiniz de! Her şey bittiğinde burada tekrar görüşürüz.";
			}
			link.l1.go = "Julianna_135";
		break;
		
		case "Julianna_135":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			sld = characterFromId("GG_Moreno");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "23");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			chrDisableReloadToLocation = false;
			pchar.questTemp.GoldenGirl = "antigua";
			// убрать фрегат Шиво
			pchar.quest.goldengirl_AngerranCap_AfterBattle.over = "yes";
			Group_DeleteGroup("GG_AngerranGroup");
			sld = characterFromId("GG_AngerranCap");
			sld.lifeday = 0;
			GiveItem2Character(pchar, "blackpearl"); // черная жемчужина 
		break;
		
		case "Julianna_136":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Tebrikler, Kaptan. Planınız işe yaradı. Ne büyük bir skandal yarattınız! İngilizler Angerran'ı ve gemisini içindeki her şeyle birlikte aldılar, bir tek ben hariç.";
				link.l1 = "Sir William vedalaşmaya bile gelmedi. Özür dileyeceğine söz vermişti.";
				link.l1.go = "Julianna_137";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
				else sld = characterFromId("Mary");
				dialog.text = "Charles, başardık! Seni her an serbest bırakacaklar! Ama adadan mümkün olduğunca çabuk ayrılmalıyız. Vali, Angerran'ın son tutuklanmasından dolayı çok öfkeli.";
				link.l1 = "Seni görmek güzel, Julianne. Nasılsın? Takas nasıl geçti? O iyi mi?";
				link.l1.go = "Julianna_140";
			}
		break;
		
		case "Julianna_137":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Sanırım bunun için fazla meşguldü. Şu anki valimiz gibi. O seni hatırlamadan kasabadan ayrılsan iyi edersin. Henri'nin oğlunu gerçekten severdi ama İngiliz belgeleri onu köşeye sıkıştırdı. Bütün öfkesini sana yöneltmeye karar vermesini beklemezdim.";
			link.l1 = "Adil bir cevap. Ayrıca, o beni Martinique'te bekliyor. Takas nasıl geçti? İyi mi, bir sorun yok mu?";
			link.l1.go = "Julianna_138";
		break;
		
		case "Julianna_138":
			dialog.text = "Beni affedin, ama bu konuda konuşmak istemiyorum. Onun yerine ona sorun. Hoşça kalın, Kaptan. Kendi başıma döneceğim. Denize biraz ara vermem gerekiyor – François, sıkıcı İngiliz memurları tarafından rahatsız edilmediğinde oldukça iyi bir ev sahibidir.";
			link.l1 = "Tüm bunlar için gerçekten üzgünüm, Madam. Her halükarda iş birliğiniz için teşekkür ederim. Yeni bir... arkadaş edindiğinizi duymak beni memnun etti.";
			link.l1.go = "Julianna_139";
		break;
		
		case "Julianna_139":
			dialog.text = "Sana da teşekkür ederim Charles, sözünü tuttuğun için. Bartholomew’u St. Pierre’deki evimde bulabilirsin. Hoşça kal. Yine görüşeceğiz.";
			link.l1 = "Elveda, Julianne. Yolun açık olsun.";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_140":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Onu görmedim, ama Bartholomew onu sağ salim götürdü. O İngiliz, de Chievous'u tutukladı ve malına el koydu, hem de yerel valinin burnunun dibinde – adam tek kelime etmedi! İnanılır gibi değil!";
			link.l1 = "Biliyor musun, bu tutuklamanın ardındaki geçmişi düşününce, her şey şaşırtıcı derecede sorunsuz geçti. Yine de, bunun ileride başıma iş açması kaçınılmaz. Neyse! Hemen Martinique'e gitmeliyim, onu bir an önce görmeliyim!";
			link.l1.go = "Julianna_141";
		break;
		
		case "Julianna_141":
			dialog.text = "Şüphesiz, ikinizin de birbirinize söyleyecek çok şeyi var. Ah Charles, keşke yanımda gözlerinde böyle bir ateş olan bir adam olsaydı. Hadi acele edelim, sıcak bir banyoyu ve temiz çarşafları gerçekten özledim. Bartholomew bizi St. Pierre'deki evimde bekliyor olacak.";
			link.l1 = "Evet, deniz yolculuklarının romantizmi abartılıyor. Kameramı size vereceğim, markiz, en azından bunu yapabilirim. Hadi.";
			link.l1.go = "Julianna_142";
		break;
		
		case "Julianna_142":
			dialog.text = "Benim için yapabileceğin her şeyi zaten yaptın, Charles. Senin sayende, umutsuz bir kadın yeniden inanmaya başladı.";
			link.l1 = "Ben de, Julianne. Ben de.";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_143":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "none", "", "", "GoldenGirl_BasterReloadJail", 7.0);
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterComplexReputation(pchar, "nobility", -10);
				ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterNationReputation(pchar, ENGLAND, 20);
			}
		break;
		
		case "Julianna_144":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, geldiğine çok sevindim! O hanımefendi nasıl? İyi mi?";
				link.l1 = "Her şey yolunda, senin sayende Julianne. Bunu sana bir kez daha söylemek istedim. Sen harika bir kadınsın ve tüm cesaretinle zekân için sana sonsuza dek minnettar kalacağım.";
				link.l1.go = "Julianna_145";
			}
			else
			{
				dialog.text = "Charles, geldiğine çok sevindim! O hanımefendi nasıl? İyi mi?";
				link.l1 = "Her şey yolunda, senin sayende Julianne. Bunu sana bir kez daha söylemek istedim. Sen harika bir kadınsın ve cesaretinle, zekânla bana kattıkların için sana sonsuza dek minnettar kalacağım.";
				link.l1.go = "Julianna_148";
			}
		break;
		
		case "Julianna_145":
			dialog.text = "Belki de sana borçlu olan benim. Sonuçta beni iki fazlasıyla baş belası müşteriden kurtardın. Hâlâ sana borçlu olduğumu düşünüyorum. Ne istersen söyle, Charles.";
			link.l1 = "Bu durumda, küçük bir ricam olacak, hanımefendi. Bize eşitlik kazandıracak bir şey yapabilirsiniz.";
			link.l1.go = "Julianna_146";
		break;
		
		case "Julianna_146":
			dialog.text = "Sizi dinliyorum, Kaptan. Nedir mesele?";
			link.l1 = "İnsanlar hata yapar, ama bu dünyayı kötü yapmaz. Bunu unutma ve mutlu ol, Julianne. Mutlu olmayı hak ediyorsun.";
			link.l1.go = "Julianna_147";
		break;
		
		case "Julianna_147":
			dialog.text = "Ben... Ben deneyeceğim, Charles. Teşekkür ederim. Beni arada bir ziyarete gelir misin... bir arkadaş olarak? Evim sana her zaman açık olacak!";
			link.l1 = "Teşekkür ederim, markiz. Hoşça kal, ve bana verdiğin sözü unutma.";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_148":
			dialog.text = "Yet apparently not marvellous enough... but I am glad that it ended well for you. You owe me nothing; after what you did, I can't thank you enough! Come see me whenever you are ashore. You will always be welcome at my place, as a friend!";
			link.l1 = "Teşekkür ederim, Markiz. Size her şeyin en iyisini dilerim. Elveda!";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_149":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_150";
		break;
		
		case "Julianna_150":
			dialog.text = "Charles, dostum, ne kadar kabasın – beni ne kadar da seyrek ziyaret ediyorsun! Seni özledim, biliyor musun? Biraz şarap ister misin? Heyecanlı hikayeleri birinci elden duymak için can atıyorum! Ve ünlü şansını denemek için de!";
			link.l1 = "Markiz, sadece merhaba demek ve iyi olduğunuzdan emin olmak istedim.";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Julianna_";
		break;
		
		// Жак Дьель дю Парке
		case "governor":
			dialog.text = "Ve işte buradasın, dostum! Seni tekrar görmek güzel!";
			link.l1 = "...";
			link.l1.go = "governor_1";
		break;
		
		case "governor_1":
			DialogExit();
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "governor_2":
			dialog.text = "Arkadaşımı böyle davranarak bana başka seçenek bırakmıyorsunuz, monsieur. Meydan okumanızı kabul ediyorum. Nerede ve ne zaman?";
			link.l1 = "Şimdi ve burada. Hizmetkârları çağır, onlara mum getirmelerini söyle, böyle loş bir ortam olmaz. Burası gündüz gibi aydınlık olmalı!";
			link.l1.go = "governor_3";
		break;
		
		case "governor_3":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_4";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
		break;
		
		case "governor_4":
			dialog.text = "Arkadaşım, lütfen bunu kişisel alma. Angerran gerçekten kötü biri, doğru, ama ona sataşmamalısın. Bunu bana bırak.";
			link.l1 = "Emin misiniz, Ekselansları? Karadaki bir haftadan sonra kamarotum kadar sarhoş, ama kılıcını nasıl kullanacağını kesinlikle biliyor. Böyle şeyleri hemen anlarım.";
			link.l1.go = "governor_5";
		break;
		
		case "governor_5":
			dialog.text = "Tanrı korusun Charles! Onunla düello yapmayacağım. Kumar oynayacağız, kartlar medeni insanların silahıdır. Onu soyup soğana çevireceğim ve sana, Quebec'e sağ salim dönebilmek için borç dilenirken göndereceğim.";
			link.l1 = "Bana sorarsan, bu sağlam bir plan. Ama ben olsam, o alçağın yoksul değil, ölü olmasını isterdim. Yolunuz açık olsun, Ekselansları!";
			link.l1.go = "governor_6";
		break;
		
		case "governor_6":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_11";
			sld.greeting = "Marquesa_needhelp";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_7":
			dialog.text = "Lanet olsun Angerran, orada on olamaz! İmkânsız!";
			link.l1 = "Bu bir suçlama mıydı? Anlaşma senindi, monsieur.";
			link.l1.go = "governor_8";
		break;
		
		case "governor_8":
			dialog.text = "Değildi. Sadece... biraz fazla heyecanlandım, özür dilerim. Bu bir kazaydı ve rövanş hakkı istiyorum! Bu gemi, ben... onu geri almalıyım! Ya da oyunu boşver, bana onu kaça satmaya razı olduğunu söyle! Fiyatını söyle, yarın öğlene kadar ödeyeceğim!";
			link.l1 = "Ne yazık ki, bütün kalbimle inanıyorum ki, kumarda kaybedilen ganimetler parayla geri alınamaz. Sadece tekrar kazanılabilirler. Flüt artık benim ve satmaya hiç niyetim yok. Tutkunuzun sizi böyle bir duruma düşürmesine üzgünüm, bazen yeteneklerimiz konusunda daha gerçekçi olmalıyız... Belki başka gemi belgeleriniz vardır?";
			link.l1.go = "governor_9";
		break;
		
		case "governor_9":
			dialog.text = "Sen bir pisliksin, Angerran, ve beni köşeye sıkıştırdın. Sana kabul edeceğin bir teklif sunabileceğime inanıyorum.";
			link.l1 = "...";
			link.l1.go = "governor_10";
		break;
		
		case "governor_10":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_23";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_11":
			dialog.text = "Charles, benim tek umudum sensin, sana yalvarıyorum, bana yardım et! O flüt ve onun... yükü çoktan Hollanda Şirketi'ne satıldı. Yarın tüm belgeleri onlara teslim etmem gerekiyor. Bütün gece burada kalırım diye düşündüm, o yüzden belgeleri yanıma aldım. Eğer anlaşma bozulursa başım büyük belaya girecek!";
			link.l1 = "Ama 'tatlı Jacques', senin gözdesi olan kadının şimdi çok daha kötü bir durumda olduğunu kabul etmiyor musun? Ben de kumar oynadım, bir gemiyi ortaya koymanın ne demek olduğunu bilirim, hele ki o gemi senin olmasa bile. Ama bir kadın için kumar oynamak mı?! Gerçekten beni şaşırttın! Ve şimdi tek derdin anlaşmanın akıbeti mi?";
			link.l1.go = "governor_12";
		break;
		
		case "governor_12":
			dialog.text = "Beni yargılama, Charles. Güçlü bir kontun eski sevgilisine ilgi göstermek ve hatta bir süre ona aşık olmak, Peter Stuyvesant’a bir milyon peso borçlu olmaktan hiçbir şey sayılır. Bunu onun temsilcisine nasıl açıklayacağım? İtibarımın göreceği zararı bir düşün!";
			link.l1 = "Daha önce de benzer bir borcum vardı, ama elimde hiçbir şey yoktu ve yine de başımın çaresine baktım. Sen de başaracaksın. Görüşürüz, Jacques. Hiçbir söz vermiyorum, ve bir milyon değerinde neyin kargosu olur da onu flütte saklarsın, onu da sormayacağım.";
			link.l1.go = "governor_13";
		break;
		
		case "governor_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto5", "", 10.0); // уходит
			LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload3", false); // открыть доступ в малую комнату
		break;
		
		case "governor_14":
			dialog.text = "İşte buradasın, Charles. Az kalsın seni çağıracaktım. De Chievous düelloda ısrar ediyor ve uzlaşma ihtimalini tamamen reddetti. Kartlarda iyi iş çıkardın, ama bunu yapmaya devam etmek istediğine emin misin?";
			link.l1 = "İçimde bir huzursuzluk var, Ekselansları, sanki en başından beri tam da bunu istiyordunuz. O yüzden evet diyorum. Bu iş artık kesin olarak çözüme kavuşmalı. Düellonun şartları ne olacak?";
			link.l1.go = "governor_15";
		break;
		
		case "governor_15":
			dialog.text = "Çok fazla kendi kafanda yaşıyorsun, dostum. Dünyamızın bazı yerleri hâlâ senin etrafında dönmüyor. İnan bana, dün gece olanlardan dolayı gerçekten çok hayal kırıklığına uğradım. Hem de fazlasıyla. Ama önce, senin... kazançlarının akıbetini konuşalım.";
			link.l1 = "Peki. Flütünü nasıl geri alacağını mı, yoksa Madame Julianne’in nasıl olduğunu mu öğrenmek istiyorsun?";
			link.l1.go = "governor_16";
		break;
		
		case "governor_16":
			dialog.text = "Alaylarını kiniyle mi değiştirdin? Charles, aynı taraftayız, bunu unutma.";
			link.l1 = "Tartışmalı bir iddia, Ekselansları. Hafifçe söylemek gerekirse. Şimdi, nereden başlayalım: gemiden mi yoksa hanımefendiden mi?";
			link.l1.go = "governor_17";
		break;
		
		case "governor_17":
			dialog.text = "Tabii ki Stuyvesant anlaşması – adamı bütün sabah beni bekledi ve artık bahane bulamıyorum. Flüt belgelerine ihtiyacım var, Charles.";
			link.l1 = "Pekala. O artık senin. De Chievous'un dürüst oynadığına inanmıyorum, bu yüzden malını yarı fiyatına geri alabilirsin. 150 000.";
			link.l1.go = "governor_18";
			link.l2 = "Memnuniyetle yardımcı olurum. Geminin fiyatı neydi, demiştiniz? 500.000 mi? Bana uyar.";
			link.l2.go = "governor_19";
		break;
		
		case "governor_18":
			AddMoneyToCharacter(pchar, 135000);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "Şimdi, vergiler dahil dört yüz altmış bin peso olacak. Anlaştık. 135.000.";
			link.l1 = "Dinle... Tartışmaktan yoruldum artık. O yüzden paramı ver, belgelerini al ve işini bitir.";
			link.l1.go = "governor_20";
		break;
		
		case "governor_19":
			AddMoneyToCharacter(pchar, 300000);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			dialog.text = "Eski dostlara acımazsın, değil mi Charles? Şimdi, tüm vergiler dahil...";
			link.l1 = "Kart borçlarıyla dostluğun hiçbir ilgisi yok, Ekselansları. Vergileri alıcı olarak siz ödeyeceksiniz, yoksa gemiyi Le Francois'da satarım. Unutmayın, henüz konumunuzdan yararlanmıyorum... henüz.";
			link.l1.go = "governor_20";
		break;
		
		case "governor_20":
			dialog.text = "Pekâlâ, öyle olsun. Şimdi, düello. Count de Levi Vantadur ile başımın belaya girmesini istemem, bu yüzden her şey mümkün olduğunca yasal olmalı. Beni duydun mu, Charles? Kanuna göre! Seni iki subayımla birlikte göndereceğim – ikisi de soylu ve saygıdeğer adamlardır. Onlar, her zamanki... arkadaşların yerine senin şahitlerin olacaklar. Mesele çözülene kadar her şeyin apaçık olmasını istiyorum!";
			link.l1 = "Ne kadar naziksin. Peki ya bizim iyi dostumuz kirli oyunlar oynamaya kalkarsa? Sırtımı, böyle durumlarda ne yapacağını bilen ve dostum dediğim insanlara yaslamayı, doğru ailede doğmuş olanlara tercih ederim.";
			link.l1.go = "governor_21";
		break;
		
		case "governor_21":
			dialog.text = "Charles, bu düelloyu sanki sadece seninle benim aramdaymış gibi davranmayı bırak. Bu ciddi bir mesele. De Chievous öyle kolayca öldürüp sıyrılabileceğin biri değil. Sonuç ne olursa olsun, soruşturmalar olacak, belki de mahkemeye çıkacaksın. Güvenilir tanıklara ihtiyacımız olacak. Bak, aslında seni korumaya çalışıyorum! Ama en önemlisi, onu öldürmemelisin. Biliyorum, Angerran kararlı ve muhtemelen iyi bir dövüşçü, ama Charles, onu öldürmemelisin! Yarala, hatta küçük düşür, ama orada dur. Eğer onu öldürürsen, sonuçları ağır olur ve ikimiz de bundan kaçamayız ya da kurtulamayız. Kont de Levi Vantadur gayrimeşru oğlunu resmen tanımamış olsa da başka oğlu yok. Öfkesi sonsuz olacak.";
			link.l1 = "Harika, yani öfkeli kont seni valilik koltuğundan atmasın diye kendimi öldürtmeme izin mi vermeliyim?";
			link.l1.go = "governor_22";
		break;
		
		case "governor_22":
			dialog.text = "Korkarım ki eğer beni dinlemezsen, Angerran de Chievous'tan çok daha uzun yaşamayacağız. Bunu aklında tut ve dikkatli ol. Düello bu gece saat onda, kasaba kapılarının dışında olacak. Subaylarım orada seni bekleyecek. Şimdi, son meseleye geçelim: Madame Julianne Botot - durumu nasıl?";
			link.l1 = "Ödülümden faydalanıp faydalanmadığımı mı öğrenmek istiyorsunuz? Hayır, Ekselansları, henüz değil ya da belki hiç - bunun bir önemi yok. Önemli olan, artık markizin evinden temelli olarak çıkmış olmanız. O bu konuda son derece netti. Onu bunun için yargılayamam. Julianne bundan sonra kimin koruyucusu olacağına kendisi karar verecek.";
			link.l1.go = "governor_23";
		break;
		
		case "governor_23":
			dialog.text = "Gerçekten şaşırtmayı biliyorsun, Charles. Neyse, benim Şirketin temsilcisiyle sıkıcı bir toplantım var. Sen de git, hazırlan ve sana ne konuda uyardığımı unutma.";
			link.l1 = "Elbette deneyeceğim, Ekselansları. Ama bu bir dövüş, o yüzden söz veremem. Yardımınız için teşekkür ederim.";
			link.l1.go = "governor_24";
		break;
		
		case "governor_24":
			DialogExit();
			GoldenGirl_GovernorOut();
		break;
		
		case "governor_25":
			dialog.text = "Yaşıyorsun, Charles! Oh, ne büyük rahatlama, nasıl kurtuldun? Bu kan mı?! De Chievous hayatta mı?";
			link.l1 = "Ne yazık ki, evet. Yaralı, ama ciddi değil. Kaçmak zorunda kaldı, ama adamlarını da üstümüze saldı. Kısacası, bu kanın bir kısmı bana ait değil.";
			link.l1.go = "governor_26";
		break;
		
		case "governor_26":
			dialog.text = "Alçak herif! Peki ya adamlarım? Olanları anlatacak kadar hayatta kaldılar mı?";
			if (sti(pchar.questTemp.GoldenGirl.Officer) > 1)
			{
				link.l1 = "Hepsi iyi, Ekselansları. Biraz hırpalanmışlar, ama yaşayacaklar.";
				link.l1.go = "governor_27_1";
			}
			else
			{
				if (sti(pchar.questTemp.GoldenGirl.Officer) == 1)
				{
					link.l1 = "Hepsini değil, Ekselansları. Bir beyefendi başaramadı - de Chievous yanında tüfekli askerler getirme zahmetine girmiş. Elimden bir şey gelmedi.";
					link.l1.go = "governor_27_2";
				}
				else 
				{
					link.l1 = "Orası tam bir cehennemdi, Ekselansları. İki cesur beyefendi de çatışmada hayatını kaybetti. Onlar olmasaydı, benim için işler çok kötüye giderdi. De Chievous tam anlamıyla kanlı bir pusu kurmuş.";
					link.l1.go = "governor_27_3";
				}
			}
		break;
		
		case "governor_27_1":
			dialog.text = "Harika! Güvenilir tanıkların huzurunda yazılı ifadelerini alacağım. De Chievous bunun bedelini ödeyecek!";
			link.l1 = "Onun adını en ufak şekilde bile lekeleyebileceğimizi sanmıyorum. Uyarılarına rağmen, onu bulup işi kendim bitirmeyi tercih ederim. Böyle bir korkak yaşamayı hak etmiyor.";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			ChangeCharacterComplexReputation(pchar, "authority", 6);
			ChangeCharacterComplexReputation(pchar, "fame", 6);
		break;
		
		case "governor_27_2":
			dialog.text = "Berbat. Ama en az bir tanıktan yazılı ifade alacağız. De Chievous bunun bedelini ödeyecek!";
			link.l1 = "Onun adını en ufak şekilde bile lekeleyebileceğimizi sanmıyorum. Tüm uyarılarına rağmen onu bulup işi kendim bitirmeyi tercih ederim. Böyle bir korkak yaşamayı hak etmiyor.";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "governor_27_3":
			dialog.text = "Kahretsin ona! Onlar iyi adamlardı, Charles! Yemin ederim, o alçak bunun bedelini ödeyecek!";
			link.l1 = "Onun adını en ufak şekilde bile lekeleyebileceğimizi sanmıyorum. Uyarılarına rağmen onu bulup işi kendim bitirmeyi tercih ederim. Böyle bir korkak yaşamayı hak etmiyor.";
			link.l1.go = "governor_28";
		break;
		
		case "governor_28":
			dialog.text = "Boşver, Charles. O herif zaten gereken bütün zararı kendi başına verdi. Bahse girerim şimdi kaçıyor, zavallı bir koloninin pisliğinde saklanıyordur. Artık sana bir tehdit oluşturması pek mümkün değil. Bu alçaklık, kaçan bir yılanın son ısırığıydı. Sen de yaralanmış gibisin, bir doktora ihtiyacın var mı?";
			link.l1 = "Endişeniz için teşekkür ederim Ekselansları, ama iyiyim.";
			link.l1.go = "governor_29";
		break;
		
		case "governor_29":
			dialog.text = "Bunu bilmek güzel. Artık rahatça nefes alabilirsin, bu hikaye sona erdi. Rahatla ve işine geri dön. Bu arada, hazır lafı açılmışken... Son kazançların hakkında konuşmamızı yarım bırakmıştık. Onunla ne yapacağına karar verdin mi?";
			link.l1 = "Seni tam olarak anlamıyorum, Jacques. Nedir bu? Markizi mi kastediyorsun? Kahretsin! Madam Botot! De Chievous kaçıyor, artık bana tehdit değil, ama çaresiz ve her şeyi yapabilir! Gitmeliyim! Muhafızları markizin evine gönder! Hemen!";
			link.l1.go = "governor_30";
		break;
		
		case "governor_30":
			DialogExit();
			GoldenGirl_ToJulianna();
		break;
		
		case "governor_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "governor_";
		break;
		
		case "Angerran":
			if (pchar.questTemp.Sharlie == "escape")
			{
				dialog.text = "Ünlü bir Kaptan, öyle mi? Şu küçük kasabayı neredeyse küle çeviren İspanyol saldırısını püskürten kişi? Anladım. Ne içersiniz?";
			}
			else
			{
				dialog.text = "Ünlü bir Kaptan mı dedin? Hiç adını duymadım... Ne içersin?";
			}
			link.l1 = "...";
			if (pchar.questTemp.GoldenGirl.Vine == "red") link.l1.go = "Angerran_1";
			else link.l1.go = "Angerran_2";
		break;
		
		case "Angerran_1":
			dialog.text = "Pinot Noir, tıpkı güzel ev sahibemiz gibi mi? Bunca deniz tuzundan sonra gerçekten bir şeyin tadını alabileceğine emin misin? Genelde senin gibi insanlar, eski bir çizmeyi bile eritecek içkileri tercih eder.";
			link.l1 = "If this is a suggestion to walk past the gates together, then I am in. I don't like you either, and I am glad the feeling is mutual. Let's cut the talking; you're not good at it anyway. I leave the choice of terms and arms to you.";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_2":
			dialog.text = "Bir demet toprak ve kedi çişi mi? Ne hoş! Bu ekşi zıkkımı fıçılarda bile bekletmiyorlar, çünkü zaten asla şarap olmayacak. Söylesene, deniz tuzu tadı bu kadar mı bastırıyor?";
			link.l1 = "If this is a suggestion to walk past the gates together, then I am in. I don't like you either, and I am glad the feeling is mutual. Let's cut the talking; you are not good at it anyway. I leave the choice of terms and arms to you.";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_3":
			dialog.text = "Ha, such a brave boy! Now calm your temper and keep your distance. We are not in a tavern and I am not a drinking companion of yours. You are far beneath my station; we shouldn't even be speaking, but the lady requested it. Now, Jacques and I have unfinished business...";
			link.l1 = "";
			link.l1.go = "Angerran_4";
		break;
		
		case "Angerran_4": // перекидываем pchar на Ангеррана и говорим с губером
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Angerran"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "Angerran_5":
			dialog.text = "Julianne, iyi misin? Su getirin, aptallar! Su getirin!";
			link.l1 = "...";
			link.l1.go = "Angerran_6";
		break;
		
		case "Angerran_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_28";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Angerran_7":
			dialog.text = "Kesinlikle haklısın, burası çok bunaltıcı. Şimdiye kadar oldukça eğlenceli bir oyun oldu, ama finalden önce kısa bir mola verelim. Hoşça kal Jacques - turnuvamızın şartlarını unutma, olur mu?\nVe işte burada Charles de Maure, değil mi? Şarap zevki pek iyi olmayan bir kaptan, seni hatırlıyorum. Merak etme, işim bittiğinde sadece su içeceksin. O yüzden acele etme, anın tadını çıkar, bir yudum al. Hazır olduğunda, bu küçük odada bana katıl. Gecenin sonunu daha rahat bir ortamda getireceğiz...";
			link.l1 = "Dört gözle bekliyorum, 'monsieur'.";
			link.l1.go = "Angerran_8";
		break;
		
		case "Angerran_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto6", "GoldenGirl_AngerranCards", 10.0); // уходит
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Angerran_9":
			dialog.text = "İşte geldin sonunda. Paranı vermeye hazır mısın?";
			link.l1 = "Sana ait olanı da onlara eklemeyi tercih ederim. Lütfen!";
			link.l1.go = "Angerran_10";
		break;
		
		case "Angerran_10":
			dialog.text = "Güzel söylediniz, ne yazık ki sevgili valimiz utanç verici yenilgisinden hemen önce kuralları değiştirmekte ısrar etti. Artık ortaya sadece para koymak yetmiyor. Bahisler her iki tarafça da eşit olarak kabul edilmeli. Benim bahsim, gümüş işlemeli flüt.";
			link.l1 = "Hadi ama, bu çok sıkıcı – birkaç haftalık yağmada bundan beş tane altınla alabilirim. Bana daha büyük bir şey ver.";
			link.l1.go = "Angerran_11";
		break;
		
		case "Angerran_11":
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "Evet, gemini gördüm, kabul etmeliyim ki gerçekten görülmeye değer. O halde bahsi yükseltelim – iki gemi bire karşı. Benim fırkatem ve flütümdeki gümüşe karşı senin gemin?";
				link.l1 = "Harika bir oyun! Madame Botot yanılmış - BU düello efsane olarak anılacak. Anlaştık!";
			}
			else
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
				{
					dialog.text = "Bak hele, kaptanımız yaramaz bir çocukmuş! Ama korsanlık kutsaldır. Peki ya bir savaş gemisi? Bir fırkateyn, 48 toplu. Birçok korvetten daha hızlı – kraliyet tersanelerinin ürünü, dünyanın en iyi gemi ustaları tarafından daha da geliştirilmiş. Taşıdığı kalverin topları mükemmel menzile ve isabetliliğe sahip. Ne dersin?";
					link.l1 = "Çok daha iyi, varım! Hadi gidelim!";
				}
				else
				{
					dialog.text = "Buraya demir attığını duydum, Kaptan. Eski tekneni teminat olarak kabul etmeyi kabul ettiğim için minnettar olmalısın. Hadi bakalım, yoksa vaz mı geçiyorsun?";
					link.l1 = "Pekâlâ, haklısın. Hadi gidelim.";
				}
			}
			link.l1.go = "Angerran_12";
		break;
		
		case "Angerran_12":
			DialogExit();
			npchar.money = 200000;
			pchar.questTemp.GoldenGirl.Game.G3 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_13":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
				{
					dialog.text = "Oyun bitti, Kaptan, istediğini aldın. İstersen zaferini kutla. Fırkateynimin devriyle ilgili şartları yarın öğlen konuşmamızı öneririm.";
					link.l1 = "Hepsi bu mu? Ben de senin gibi, kumarda kaybedilenin parayla geri alınamayacağına, sadece yeniden kazanılabileceğine inanıyorum. Ya da onu buradaki balıkçılara kereste diye satar, onlara da senin cömert bağışından uzun uzun bahsederim.";
					link.l1.go = "Angerran_15";
				}
				else
				{
					if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
					{
						dialog.text = "Demek ki kader kararını verdi. Bu iş gerçekten ilginç bir hal aldı. Tebrikler, Kaptan de Maure. Firkateynimin devriyle ilgili şartları yarın öğlen konuşmamızı öneririm.";
						link.l1 = "Bu kadar çabuk mu? Diğer misafirlerimizi hayal kırıklığına uğratıyoruz, monsieur. Yanılmıyorsam, hâlâ bir geminiz daha var. Kaybedilenin kumarda satın alınamayacağına, sadece geri kazanılabileceğine sizin gibi ben de yürekten inanıyorum.";
						link.l1.go = "Angerran_16";
					}
					else
					{
						dialog.text = "So Fortune has spoken. This turned out most curiously. Congratulations, Captain de Maure. You've earned yourself a decent drink, try Sangiovese. I assume Jacques will pay you well for this tub; it seems he has feelings for it, feelings much stronger than for certain other things. That should be enough to buy a good wine.";
						link.l1 = "Şimdiden pes mi ediyorsunuz? Diğer misafirleri hayal kırıklığına uğratıyoruz, monsieur. Yanılmıyorsam, hâlâ bir geminiz daha var. Kendi gemimi fazla mütevazı bulduğunuz için, sizin fırkateyninizi gümüş işlemeli flütümle oynuyorum.";
						link.l1.go = "Angerran_17";
					}
				}
			}
			else
			{
				dialog.text = "Şanssızlık, Kaptan. Yine de cesaretini takdir ediyorum ve bugün keyfim yerinde. Altınını alacağım, ama gemin sende kalsın. Şimdi gözümün önünden kaybol ve lütfen bir daha kumar oynamaktan uzak dur. Bir gün başına bela olacak.";
				link.l1 = "Bunu senden beklemezdim, çok asilce davrandın. Elveda, Monsieur de Chievous.";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_14":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Angerran_15":
			dialog.text = "Yenilmiş rakibinle alay etmekle övünmek arasında önemli bir fark var, Monsieur de Maure.";
			link.l1 = "Şimdiden kendini yenilmiş mi sayıyorsun? Oysa her şey ne güzel başlamıştı... ah! Madame Botot, sanırım salonunuza sözlerle eylemler arasındaki farkı anlatan yeni bir hikaye daha eklendi!";
			link.l1.go = "Angerran_15_1";
		break;
		
		case "Angerran_15_1":
			dialog.text = "Daha ne istiyorsun? Kolumda başka gemi kalmadı, cebimde ise bir gemiyi bile karşılayacak para yok. Dublon için kumar oynamak ciddi bir iş değil, hele bu gece yaşadıklarımızdan sonra.";
			link.l1 = "Sen bizim tatlı Jacques Dille du Parkuet’den daha mı beceriksizsin? Sana, aşkın her zaman satılık olmadığını kanıtlama fırsatını veriyorum. Şans da lütfunu satmaz. Gümüş gemi ve senin fırkateynin, altından daha çok değer verdiğin şey uğruna.";
			link.l1.go = "Angerran_15_2";
		break;
		
		case "Angerran_15_2":
			dialog.text = "Kaptan, bu artık komik bile değil. Hadi bunu bitirelim – şafak yaklaşıyor. Fırkateynimin satın alınmasını yarın konuşuruz.";
			link.l1 = "Pekâlâ, işte sana üç gemi! Üstelik biri gerçek bir savaş gemisi, Yeni Dünya'nın en... yani, en pahalı hanımefendisine karşı. Böyle bir teklifi reddedebilir misin?";
			link.l1.go = "Angerran_15_3";
		break;
		
		case "Angerran_15_3":
			dialog.text = "Bu delilik olurdu. Gerçi, bu zaten delilik, monsieur de Maure. Lütfen. Ama unutmayın, bu sizin fikrinizdi.";
			link.l1 = "Bu, kapalı kapılar ardında bir yıl boyunca dillerden düşmeyecek bir efsane olacak! Hey sen, biraz daha şarap ve mum getir! Oyun devam etmeli!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_16":
			dialog.text = "Daha dün bu flütü gemilerimize karşı değersiz bir bahis olarak görüyordun. Ne değişti?";
			link.l1 = "Sıkıldım. Gel düellomuza biraz heyecan katalım - senin fırkateynin ve benim gemim karşı...";
			link.l1.go = "Angerran_16_1";
		break;
		
		case "Angerran_16_1":
			dialog.text = "Şu hiç değer vermediğin flüt mü? Ateşin mi var yoksa? Pek iyi görünmüyorsun.";
			link.l1 = "Ben gayet iyiyim, teşekkür ederim. Dinlemedin. İkiye bir oran pek de etkileyici sayılmaz, doğru, o halde şartları eşitleyelim! Tüm değerli şeyler altınla ölçülemez, sence de öyle değil mi? Yoksa, işler planladığın gibi gitmezse rüzgara karşı durmak yerine rotanı mı değiştiriyorsun? O zaman ne yazık, demek ki senin hakkında yanılmışım. Madam Botot, sanırım salonunuza sözlerle eylemler arasındaki farkı anlatan bir hikaye daha eklendi...";
			link.l1.go = "Angerran_16_2";
		break;
		
		case "Angerran_16_2":
			dialog.text = "Beni sinirlendirmeye çalışma, Monsieur de Maure, bu iş için fazlasıyla saf kalırsın.";
			link.l1 = "Gerçekten de. İrade eksikliği bir günah değildir... tabii asker değilseniz. Ya da soylu biri — aile onuru bazen ne büyük bir yük, bilirsiniz. Gerçi sizin böyle ikilemlerle karşılaşmış olmanız pek olası değil, öyle değil mi.";
			link.l1.go = "Angerran_16_3";
		break;
		
		case "Angerran_16_3":
			dialog.text = "Bir düello başlatmaya mı çalışıyorsun, yoksa oyuna devam mı etmek istiyorsun?";
			link.l1 = "İkisi de olur. Sen kendine gelene kadar ben Markiz’in şarap koleksiyonuna hakkını teslim edeceğim.";
			link.l1.go = "Angerran_16_4";
		break;
		
		case "Angerran_16_4":
			dialog.text = "O halde öyle olsun. Bu gece layıkıyla son bulmalı. İki muhteşem gemi, gümüşle dolu eski bir döküntüye ve Yeni Fransa'nın en güzel kadınına karşı! Derin bir nefes alın, monsieur de Maure, bu iddia yüksek sosyetenin dedikodularında efsane olacak.";
			link.l1 = "Yenilginiz gerçekten de efsane olacak, monsieur de Chievous. Bize daha fazla şarap ve mum getirin! Hadi başlayalım!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_17":
			dialog.text = "You've lost your head over luck, monsieur de Maure. You're taking a risk here; fortune's favour is fleeting.";
			link.l1 = "A brief favour is a path to true love. The same could be said of bought loyalty; it leads only to contempt or boredom.";
			link.l1.go = "Angerran_17_1";
		break;
		
		case "Angerran_17_1":
			dialog.text = "Sinirlerimi bozma çabaların beni eğlendiriyor. İyisi mi, Madam Juliana'ya sor bu iyilik, aşk ve parayla alınıp alınamayacak diğer şeyleri. Ama acele et – yarın şehirden ayrılıyor.";
			link.l1 = "En azından konuya dair bilgin tek taraflı. Burada kazanarak ya da ödeyerek Şans Tanrıçası'nın gönlünü kazanamazsın, dolayısıyla onun sevgisini de bilemezsin. Cesaret ve sarsılmaz bir irade gerekir, monsieur, risk almak için. Kaldı ki... dünyevi hanımlar da bu özelliklere değer verir. Ben iki gemimi senin bir gemine karşı koyuyorum, var mısın?";
			link.l1.go = "Angerran_17_2";
		break;
		
		case "Angerran_17_2":
			dialog.text = "Bunu bu kadar hevesle sürdürmek mi istiyorsun? Peki, neyse. Ama en azından biraz dram katalım buna, monsieur de Maure. Aşktan ve bedellerden bahsediyordun galiba? O halde teklif ediyorum: senin o teknen ve gümüş flütün, benim fırkatayım ve Yeni Fransa'nın en güzel kadınına karşı. Şimdi ne diyorsun?";
			link.l1 = "Şunu söylemeliyim ki, gerçekten şık bir şekilde kumar oynamayı biliyorsunuz, monsieur! Daha fazla şarap ve mum getirilsin! Haydi gidelim!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_18":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game"); // fix 22-03-20
			npchar.money = 70000; // на 2 кона
			pchar.questTemp.GoldenGirl.Game.G4 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "İnanılmaz, Monsieur de Maure, bu gerçekten inanılmaz!";
				link.l1 = "Evet, gerçekten de Avrupa, Rocroi Muharebesi'nden beri böyle bir yenilgi görmedi, monsieur de Chievous. İçimdeki sanatçı, böylesine tarihi bir anı ölümsüzleştirme arzusuyla titriyor. Ne yazık ki artık gençliğimdeki gibi çizemiyorum. Ama belki de madam Julianne'ın yakınında yetenekli bir ressam vardır, öyle değil mi?";
				link.l1.go = "Angerran_20";
			}
			else
			{
				dialog.text = "Kötü şans, Kaptan. Yine de cesaretini takdir ediyorum ve bugün keyfim yerinde. Altınını alacağım, ama gemini yanında tutabilirsin. Şimdi gözümden kaybol, ve lütfen bir daha kumar oynamamaya çalış. Bir gün bu seni mahvedecek.";
				link.l1 = "Çok asilce davrandınız, bunu beklemiyordum. Elveda, Monsieur de Chievous.";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_30";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_21":
			dialog.text = "Hayır, anlamıyorsun. Bu o kadar inanılmaz ki, gerçekten olamaz!";
			link.l1 = "Hepimiz kartları gördük, Monsieur de Chievous - Şans asla yalan söylemez.";
			link.l1.go = "Angerran_22";
		break;
		
		case "Angerran_22":
			dialog.text = "Kader değil, ama siz, Mösyö de Maure, kesinlikle etkiliyorsunuz! Bana öyle geliyor ki, küstahlığınızın ardında sadece tutku değil, bir plan da vardı. Siz bir yalancı ve sahtekârsınız – bunu tüm misafirlerin önünde kanıtlamaya hazırım.";
			link.l1 = "...";
			link.l1.go = "Angerran_23";
		break;
		
		case "Angerran_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_32";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_24":
			dialog.text = "";
			link.l1 = "Monsieur de Chievous, doğru mu duydum? Şüphelerinizi sadece sözlerle değil, başka bir şekilde de savunmaya hazır mısınız? Görüyorum ki hakaretleriniz artık haddini aştı, ve ben, sizden farklı olarak, ailemin onuruna değer veririm.";
			link.l1.go = "Angerran_25";
		break;
		
		case "Angerran_25":
			dialog.text = "Bir dolandırıcı ve düzenbaz olan ikinci oğul bana aile onuru hakkında ders veremez! Sessiz ol Julianne, seninle sonra konuşacağım! Charles de Maure, derhal bana hesap vermeni istiyorum! Kılıç mı, tabanca mı?";
			link.l1 = "İkisi de. Açıkçası, fikrini değiştirmene sevindim. Hatırlıyor musun, kapıların önünde yürüyüş yapmayı önermiştim? Benim değersiz sınıfım hakkında ne demiştin? Belki de kart oyunu sana biraz cesaret kazandırmıştır, ne dersin?";
			link.l1.go = "Angerran_26";
		break;
		
		case "Angerran_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_34";
			sld.greeting = "Marquesa_vecherkonchen";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_27":
			dialog.text = "Büyük bir onur, ama markizin söylediklerine katılıyorum. Sana bir asilzade gibi son vereceğim, de Maure, bunu hak etmesen de. Yarın öğlen, Ekselansları Vali aracılığıyla seni düelloya davet ediyorum. İstersen bizzat gel, istersen şartları görüşmek için adamlarını gönder. O zamana kadar. Hanımefendi, saygılarımı sunarım.";
			link.l1 = "...";
			link.l1.go = "Angerran_28";
		break;
		
		case "Angerran_28":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0); // уходит
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_36";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_29":
			dialog.text = "Ve işte buradasın, talihin gözdesi. İşlerini hallettin umarım? Günahlarını itiraf etmeyi unutmadın mı? Derler ki, cehennem itiraftan yoksun olunca pek rahat olmazmış.";
			link.l1 = " Laf lafla olmaz, monsieur. Kart oynamayı beceremiyorsun, o zaman bakalım kılıçta ne yapacaksın... Hadi bakalım!";
			link.l1.go = "Angerran_30";
		break;
		
		case "Angerran_30":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ExitTown")], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantGG_"+i);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocator(sld, "goto", "goto1"+(7+i), "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			LAi_group_Delete("EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "GoldenGirl_Duel"); 
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Angerran_31":
			dialog.text = "Güzel... vuruş, kahretsin seni. Ama hâlâ yaşıyorum!";
			link.l1 = "Your wound doesn't look good, but you should see a doctor nevertheless. Clearly, you can't go on like this; you will die if you do. It looks like we are done here. I won, and I didn't cheat. I will return your ship to you, and you will leave St. Pierre. We will never see each other again.";
			link.l1.go = "Angerran_32";
		break;
		
		case "Angerran_32":
			dialog.text = "Ne büyük bir şövalyelik! Bakın, monsieur de Maure, doğuştan bir kılıç ustası olabilirsiniz ama kesinlikle kartta hile yaptınız. Deste ile üç kez oynadım. Üç kez, lanet olsun! Dünyada hiçbir mucize sizi kurtaramazdı ama yine de kazandınız! Nasıl yaptığınızı keşke bilseydim... Neyse, yakında şeytana her şeyi anlatırsınız. Vurun, çocuklar!";
			link.l1 = "Seni alçak! Sana merhamet gösterdim, sen ise bana böyle mi karşılık veriyorsun?! Beyler, silah başına!";
			link.l1.go = "Angerran_33";
		break;
		
		case "Angerran_33":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 20.0);
			LAi_RemoveCheckMinHP(npchar); 
            LAi_SetCurHPMax(npchar);
			GoldenGirl_DuelNext();
		break;
		
		case "Angerran_34":
			dialog.text = "Kabul etmeliyim ki, Monsieur de Maure, sizi burada görmek beni biraz şaşırttı. Demek ki sizinle ilgili yanılmamışım ve o asi kız gerçekten sizin için bir anlam ifade ediyor?";
			link.l1 = "Acaba senin iyi dostun de Lyons, donanmamızın saygıdeğer kaptanlarının subaylarını kaçırmak hakkında ne düşünüyor? Belki onu da çağırıp her şeyi baştan sona anlatmamız gerekir?";
			link.l1.go = "Angerran_35";
		break;
		
		case "Angerran_35":
			dialog.text = "Bu sana hiç yardımcı olmayacak, inan bana. Ayrıca, senin kadınına bir esir generaldan daha iyi davrandım. Şimdilik. Ama her şey değişebilir, bu tamamen sana bağlı, Charles.";
			link.l1 = "Seninle bir sevgilinin kadehini paylaştığımızı hatırlamıyorum. Bana 'Charles' deme, Monsieur de Chievous. Lafı dolandırma ve benden ne istediğini açıkça söyle.";
			link.l1.go = "Angerran_36";
		break;
		
		case "Angerran_36":
			dialog.text = "Senden mi? Aman Tanrım, asla! Seninle ben sadece talihsiz bir kavganın ardından, rezil bir kart oyunundan sonra, birkaç kadeh içtik ve bu odadan eski dostlar olarak ayrıldık.";
			link.l1 = "Angerran, son yaranına rağmen iyi görünüyorsun, ama bu boş muhabbetin her dakikası o yarayı tazelemek isteğimi artırıyor. Hatta Francois de Lyons'un şu güzelim halılarını kirletme fikri bile bana gitgide daha cazip gelmeye başladı.";
			link.l1.go = "Angerran_37";
		break;
		
		case "Angerran_37":
			dialog.text = "Ama iyi yürekli François bu halılara bayılır, Charles. Herkesin sevdiği bir şey vardır. Madem buradasın, demek ki silah arkadaşını, o küçük sevgilini seviyorsun. Onu sana geri vermeye hazırım, tabii ki malımı geri alırsam. Oyunu berbat ettin ve normalde böyle şeyleri affetmem, ama senin için bir istisna yapabilirim. Benim arzuladığım ödülü bana vereceksin, ben de sana seninkini. Sonra güzelce yollarımızı ayırırız. Aşk dediğin de bu kadar işte.";
			link.l1 = "Marquise'i çantamda değerli bir mücevher gibi taşıdığımı mı sanıyorsun? Saçmalık! Onu sana nasıl teslim edebilirim ki?!";
			link.l1.go = "Angerran_38";
		break;
		
		case "Angerran_38":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Umurumda bile değil, Charles. Bunu halletmen için iki haftan var. Ve evet, bu ödülün sessizce alınmasını istiyorum. Diyelim ki, aşırı pahalı bir fahişeyi kazanan bir kaptan, yine de onun gönlünü kazanamayınca, aptalca bir şey yapabilir, değil mi? Zaten yeterince çaresiz olduğunu mu düşünüyorsun, Charles?";
			link.l1 = "Önce subayımı görmek istiyorum, hâlâ hayatta olduğundan emin olmak için.";
			link.l1.go = "Angerran_39";
		break;
		
		case "Angerran_39":
			dialog.text = "Söz konusu bile olamaz. Sözüme güvenmek zorundasın. O, güvenli bir yerde ve ödülümü alana kadar da orada kalacak. Ama onu önceden görmekte ısrar edersen, sana bir iyilik yapıp ondan bir parça göndermekten memnuniyet duyarım. Hangisini tercih edersin? Bir kulak, bir burun, yoksa birkaç parmak mı?";
			link.l1 = "Bir daha ona dokunursan, seni ellerimle boğarım, Allah şahidim olsun! Sakın beni sınamaya kalkma!";
			link.l1.go = "Angerran_40";
		break;
		
		case "Angerran_40":
			dialog.text = "Calm down. Everything that is about to happen is entirely your doing. I don't like violence; I use it only when I must. Don't make me. Just hand over my prize at Cape Scott Head on Dominica in less than two weeks and you will get what is yours. I don't care how you do it. If you want to steal - steal, you are a pirate after all, just better dressed.";
			link.l1 = "Sen tam anlamıyla delirmişsin, bir korsanla lanet bir köle taciri arasında büyük bir fark var...";
			link.l1.go = "Angerran_41";
		break;
		
		case "Angerran_41":
			dialog.text = "Daha derin nefes al, şimdi eski François'nın önünde şık bir giriş yapacağız. Artık arkadaşız, hatırlıyor musun? Gülümse, Charles, hadi! Yollarımızı ayıralım. Cape Scott Head, Dominika, iki hafta sonra. Sakın geç kalma.";
			link.l1 = "Orada görüşürüz.";
			link.l1.go = "Angerran_42";
		break;
		
		case "Angerran_42":
			DialogExit();
			DoQuestReloadToLocation("Baster_townhall", "goto", "goto1", "GoldenGirl_AfterBaster");
		break;
		
		case "Cortny":
			PlaySound("VOICE\English\LE\Cortny\Cortny_01.wav");
			dialog.text = "İyi akşamlar, Madame Botot, Kaptan de Maure. Sakin kalmanızı rica ediyorum.";
			link.l1 = "Markiz, arkamda dur, hemen! Mösyö, bunun anlamı ne?!";
			link.l1.go = "Cortny_1";
		break;
		
		case "Cortny_1":
			PlaySound("VOICE\English\LE\Cortny\Cortny_02.wav");
			dialog.text = "Kapının arkasında bir düzine adamım ve devletiniz tarafından bana verilen olağanüstü yetkilerim var. Muhafızlar size yardım etmeyecek. Bu yüzden, lütfen kılıcınızı indirin, efendim. Sadece konuşmak istiyorum. Şimdilik.";
			link.l1 = "Beyefendi, siz kimsiniz ve buraya nasıl geldiniz?! Kendinizi açıklamalısınız!";
			link.l1.go = "Cortny_2";
		break;
		
		case "Cortny_2":
			dialog.text = "Kendimi tanıtmama izin verin - Sir William Cortney, Baronet Cortney. Şimdi hepimiz sakinleşelim ve konuşalım.";
			link.l1 = "Pekala, Mösyö Cortney, hepimiz sizi dinliyoruz.";
			link.l1.go = "Cortny_3";
		break;
		
		case "Cortny_3":
			dialog.text = "Lütfen beni dinlediğim için mazur görün, fakat şu anki koşullar bana başka bir seçenek bırakmıyor. St. Pierre'de kimliğimi gizli tutuyor olsam da, İngiltere Kraliyeti adına son derece önemli bir soruşturma yürütüyorum. Denizde kaybolan bir kurye gemisiyle ilgili. Hiç Regina adında bir brigantin duydunuz mu? ";
			link.l1 = "Hayır, ve sizin bu belirsiz imalarınızı da anlamıyorum, Mösyö. Ben dürüst bir kaptanım...";
			link.l1.go = "Cortny_4";
		break;
		
		case "Cortny_4":
			dialog.text = "Sizin o karanlık işlerinize en ufak bir alakam yok, efendim. Hakkınızda biraz araştırma yaptım ve açıkçası, Regina kaybolduktan hemen sonra Martinique'e gittiğinizi duyunca sizi ilk şüphelim olarak düşündüm. Ama aptal değilsiniz ve adamlarınız burada incilerle oyalanmadı. Bu yüzden, şimdilik şüphelerimden çıktınız.";
			link.l1 = "İnci mi? Hangi incilerden bahsediyorsun sen?";
			link.l1.go = "Cortny_5";
		break;
		
		case "Cortny_5":
			dialog.text = "İspanyol Batı Ana'nın işletmelerinden özenle seçilmiş, iri taneli inciler. Üstelik inciler siyah, yani son derece nadir bulunur. Böyle bir şey duymuş muydun hiç?";
			link.l1 = "Bilmiyorum, ama hep bunun da denizcilerin uydurduğu hikayelerden biri olduğunu düşünürdüm. Tıpkı Uçan Hollandalı hakkındaki masallar gibi. Julianne, neyin var?";
			link.l1.go = "Cortny_6";
		break;
		
		case "Cortny_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_104";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_7":
			dialog.text = "Bunu burada sunmanızı rica ediyorum, hanımefendi. Bu son derece önemli bir mesele. Bu arada, siz de bana Kaptan Moreno hakkında her şeyi anlatmalısınız, efendim. O ipucunu size onun verdiğinden şüpheleniyorum. Bu işteki rolünü öğrenmek için çok merak ediyorum.";
			if (CheckAttribute(pchar, "questTemp.Portugal"))
			{
				link.l1 = "Moreno onun gerçek adı değil, Monsieur Cortney. Asıl adı Hernando Vasquez, namıdiğer Kanlı Don; eskiden Albatross'un çeyrekbaşıydı – bu gemi de meşhur Portekizli Bartholomew'ya aitti.";
				link.l1.go = "Cortny_8";
			}
			else
			{
				link.l1 = "Sadece birkaç kelime konuştuk. Anlatacak pek bir şeyim yok. Gerçek bir deniz kurdu gibiydi.";
				link.l1.go = "Cortny_9";
			}
		break;
		
		case "Cortny_8":
			dialog.text = "Vay canına. Peki, bunu nasıl bildiğini sorabilir miyim?";
			link.l1 = "Onun kaptanını eskiden tanırdım. Aslında onu yakalayıp Hollandalılara teslim eden bendim. Uzun bir hikaye. Keşke o zamanlar Vasquez'in kendisini de ele geçirseydim...";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_9":
			dialog.text = "Sen de tam bir deniz kurdusun, efendim. Daha fazlasını fark etmediğine inanmıyorum.";
			link.l1 = "Sadece hafif bir aksanı vardı, görünüşü ve tavırları da öyleydi. Bahse girerim İspanyol, Monsieur Cortney.";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_10":
			dialog.text = "Bu gerçekten her şeyi değiştirir, efendim. Ve bu hiç iyi değil. Hanımefendi, kolyeyi buldunuz mu? İzin verin bir bakayım\nEvet, gerçekten de bu İspanyol siyah incilerinden biri. Bakın, bu denizcinin anlattıkları büyük ölçüde doğruymuş. Şimdi geriye sadece şu de Chievous'un bunlardan birini nasıl ele geçirdiğini öğrenmek kaldı. Bu arada, kendisi Duke de Levy Vantadur'un piçi değil miydi?";
			link.l1 = "Evet, o. Bildiğimiz kadarıyla Le Francois'daki yerel korsan baronuyla ilişkileri vardı. Belki de bu inciyi ondan satın aldı?";
			link.l1.go = "Cortny_11";
		break;
		
		case "Cortny_11":
			dialog.text = "Belki de öyle. Ama bu işteki İspanyol izinden hiç hoşlanmıyorum. Yine de, işbirliğiniz için teşekkür ederim. Korkarım yarın günün aynı saatinde sizi tekrar ziyaret etmem gerekecek. Kaptan de Maure'un da orada olmasını rica ediyorum. Belki size daha fazla sorum olur. Şimdi Le François'ya gitmeliyim.";
			link.l1 = "Monsieur Cortney, bekleyin. Belki size katılabilirim? Jacques Barbazon bu lakabı sevgi dolu ve nazik biri olduğu için almadı, ayrıca bu mesele beni de ilgilendiriyor.";
			link.l1.go = "Cortny_12";
		break;
		
		case "Cortny_12":
			dialog.text = "Kaptan, ilginiz beni duygulandırdı ama cevabım hayır. Bu bir devlet meselesi. O alçak haddini bilir ve tacın elçisine el sürmeye cesaret edemez, yoksa zavallı köyü yerle bir olur! Yine rahatsız ettiğim için özür dilerim hanımefendi. İyi akşamlar.";
			link.l1 = "Yarın akşam görüşürüz, Baronet.";
			link.l1.go = "Cortny_13";
		break;
		
		case "Cortny_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_106";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_14":
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Ona kızmayın, Kaptan. Ben oldukça ikna edici olabilirim. Hikayeniz gerçekten etkileyici. Sanırım size bir işim düşebilir.";
			link.l1 = "Keyifli görünüyorsun. Le Francois'da nasıl geçti?";
			link.l1.go = "Cortny_15";
		break;
		
		case "Cortny_15":
			dialog.text = "Beklediğim gibi, o baronun kuzu gibi uysaldı. Bilmek istediğim her şeyi anlattı. Dediğim gibi, gerektiğinde son derece ikna edici olabilirim.";
			link.l1 = "";
			link.l1.go = "Cortny_16";
		break;
		
		case "Cortny_16":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_112";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_17":
			dialog.text = "Bugün buraya tek başıma geldim, o kapının ardında adamlarım yok. Ne oluyor böyle?!";
			link.l1 = "İçimde kötü bir his var. Julianne, hemen arkamda dur! Baronet, Taç'ın elçileri konuştuğu kadar iyi dövüşebiliyor mu bakalım?";
			link.l1.go = "Cortny_18";
		break;
		
		case "Cortny_18":
			DialogExit();
			GoldenGirl_CortnyBandosFight();
		break;
		
		case "Cortny_19":
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Kılıcı nasıl kullanacağını iyi biliyorsun, Kaptan! Açıkçası, bu hiç de kolay olmadı. Kimdi o herifler, Allah aşkına?!";
			link.l1 = "Arkadaşlarına da sormalıyız - daha fazla ayak sesi duyuyorum. Keşke muhafızlar olsaydı...";
			link.l1.go = "Cortny_20";
		break;
		
		case "Cortny_20":
			DialogExit();
			GoldenGirl_CortnyMercenFight();
		break;
		
		case "Cortny_21":
			dialog.text = "İnanılır gibi değil! O alçağın bütün bunları yapmaya cüret ettiğini mi düşünüyorsun?! Bedelini ödeyecek, yemin ederim!";
			link.l1 = "Nefes al. Barbazon her türlü suçlamadan sıyrılmayı becerir. Sana bunun zengin bir eve yapılan sıradan bir hırsızlık baskını olduğunu söyleyecek. Üstelik, kendisi lanet bir korsan, otoriteleri neden umursasın ki! Yine de, artık senin gerçekten değerli bir şey öğrendiğinden eminim. Bu bilgiyi benimle paylaşmanı rica ediyorum.";
			link.l1.go = "Cortny_22";
		break;
		
		case "Cortny_22":
			dialog.text = "Hayır diyemem, değil mi? Yoksa bir dahaki sefer gerçekten olur mu? Peki, sesindeki tehdidi duymamış gibi yapacağım. Diyelim ki bir iyiliği geri ödüyorum. İyi Yürekli Jacques, o soylu piçe inci satmadı. O satın alıyordu. Hepsi bu.";
			link.l1 = "Demek Regina'yı ele geçiren de Chievous'muş? O tam bir alçak, ama sıradan korsanlığa tenezzül edeceğine inanmak zor.";
			link.l1.go = "Cortny_23";
		break;
		
		case "Cortny_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_117";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_24":
			dialog.text = "Regina'yı tipik bir korsan ganimeti olarak adlandırmak zor, Kaptan. Gemide en az yarım düzine siyah inci olduğunu tahmin ediyoruz. Tek bir siyah inci bile paha biçilemez. O Sir de Chievous ile ne pahasına olursa olsun mutlaka tanışmalıyım.";
			link.l1 = "Burada size biraz yardımcı olabilirim, Mösyö. Ama önce bir şeyi netleştirelim. Madame Botot'nun kolyesiyle ilgilendiğimi sanmıyorum, demek ki inciler burada olmanızın sebebi değil. Regina'nın başka neyi vardı gemide?";
			link.l1.go = "Cortny_25";
		break;
		
		case "Cortny_25":
			dialog.text = "Very well, I suppose I'll have to tell you more, given the circumstances. You see, the cargo is not as important as the ship herself. The courier brigantine Regina had been assigned to the port of San Jose, Trinidad. Her captain used to gather intel and run some... errands for us.\nHis last errand was to transport spoils our capers managed to extract from the Spanish pearl operations. It took three years of our efforts to get that lead. Black pearls are certainly significant, but losing the Regina is disastrous. It wasn't an accident; someone who knew about her pearls must also have known about the rest.";
			link.l1 = "Harika, demek ki işin içinde istihbarat servisleri var! Kurduğun bütün casus ağı tehlikede diye mi korkuyorsun? Şimdi sıkıntılarının boyutunu tam olarak görebiliyorum.";
			link.l1.go = "Cortny_26";
		break;
		
		case "Cortny_26":
			dialog.text = "John Thurloe'yu duydun mu hiç? O, Kraliyet istihbaratının başında. Bir gün Londra'da olacağım ve Regina'nın akıbetini bizzat ona rapor edeceğim. Sızıntının nereden geldiğini bulmalı ve... kaynağıyla ilgilenmeliyim. Üstelik, şu gizemli kaptan Moreno da var. Eğer İspanyollar sömürgeci casus ağımızın izini sürerse, yıllar süren zorlu ve yorucu emek boşa gidecek!";
			link.l1 = "Biliyor musun, bütün bunlar daha geniş açıdan bakınca anlam kazanmaya başlıyor. Sanırım İspanyol aksanlı biri de Chievous'a Regina'yı ve siyah incileri anlatmış.";
			link.l1.go = "Cortny_27";
		break;
		
		case "Cortny_27":
			dialog.text = "We think alike. There is no better way to exploit an exposed spy network. A diplomatic incident with a man of such high standing involved... Such an incident could seriously damage relations between Britain and France; all you need is to feed the right leads and just wait for an international scandal. Perhaps even that lead about black pearls was deliberately fed to us as well.";
			link.l1 = "Şu lanet Kastilyalılar, değil mi? Peki, de Chievous hakkında ne yapacağız?";
			link.l1.go = "Cortny_28";
		break;
		
		case "Cortny_28":
			dialog.text = "Dürüst olmak gerekirse, hiçbir fikrim yok. Eğer bu bir İspanyol provokasyonuysa, en iyisi onu görmezden gelmek olurdu. Ama Regina'yı nasıl öğrendiğini ve bunun İspanyol kolonilerindeki ağımız için ne kadar kötü göründüğünü bilmem gerek. Ayrıca, sana hayatımı borçluyum ve bu borcumu ödemeye niyetliyim.";
			link.l1 = "Dürüstlük karşılığında dürüstlük, Baronet. Elimden gelen her türlü yardıma ihtiyacım var. Markizi kaçırmayı bile düşünecek kadar çaresizim artık.";
			link.l1.go = "Cortny_29";
		break;
		
		case "Cortny_29":
			dialog.text = "Bunun de Chievous'un izlerini nasıl kaybettirdiğinin farkındasın, değil mi? Tüm bu karmaşayı, Regina'nın kayboluşu da dahil, senin üzerine yıkmak onun için çocuk oyuncağı olur. Bu yüzden sana şunu öneriyorum. Marquise Botot bana de Chievous'un takasa katılmayacağını ve Basse-Terre'de güvende kalacağını söyledi. Ya başını ne kadar derde soktuğunu anladı ya da bir şeylerden şüphelenmeye başladı. Mutfak faresinden farksız, son derece temkinli olacak. Bu yüzden Dominika'ya seninle birlikte gideceğim.";
			link.l1 = "Ama onun tutsağı benim önceliğim, onun hayatını riske atamam! O, takas için bekletilen bir rehine!";
			link.l1.go = "Cortny_30";
		break;
		
		case "Cortny_30":
			dialog.text = "Merak etme - Jacques Dille de Parkuet'i sıkıştıracağım ve de Chievous'un gemisi için bir tutuklama emri alacağım. Adamlarının içinde bulundukları durumun tamamen farkında olduklarını sanmıyorum, yoksa o inciler konusunda daha dikkatli olurlardı. Onlara bir sandalla gideceğiz ve emri doğrudan kendilerine sunacağız.";
			link.l1 = "Evet, zorla ikna yeteneğinizi hatırlıyorum, Mösyö, ama bu bir risk. Hem de büyük bir risk.";
			link.l1.go = "Cortny_31";
		break;
		
		case "Cortny_31":
			dialog.text = "Tamamen haklısın, ama yardımımı istiyorsan bunu kabul etmelisin. Dominika'daki işimiz bittiğinde, Basse-Terre'e gidip Vali de Lyon'dan düşmanını teslim etmesini isteyeceğim. Yetkim buna yeter. De Chievous'un kaçmasına izin veremeyiz.";
			link.l1 = "Buna gerçekten hazır mısınız, Mösyö? Bu bir savaşı başlatabilir, değil mi?";
			link.l1.go = "Cortny_32";
		break;
		
		case "Cortny_32":
			dialog.text = "Eminim buna asla izin vermeyecekler. Gerçeği zaten bildiğimiz için bu kesinlikle imkânsız. Siyaset bir fahişe, Kaptan. Sana söz veriyorum, de Chievous'u bizzat senin için İngiliz zindanlarıyla tanıştıracağım. Bu, babasının bile makul bir bedel olarak göreceği sessiz bir çözüm gibi geliyor.";
			link.l1 = "Planını beğendiğimi söyleyemem, ama başka bir yol göremiyorum.";
			link.l1.go = "Cortny_33";
		break;
		
		case "Cortny_33":
			dialog.text = "Sana söz veriyorum, başaracağız. Şimdi valiyi görmeye ve adamlarıma emir vermeye gitmeliyim. Markizi görürsen, ona soruşturmaya yardım ettiği için inciyi bir teşekkür nişanesi olarak yanında tutabileceğini söyle.";
			link.l1 = "Teşekkürler, Baronet. Gemimde görüşürüz, yakında yelken açacağız.";
			link.l1.go = "Cortny_34";
		break;
		
		case "Cortny_34":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "GoldenGirl_CortnyPassenger", 15.0);
		break;
		
		case "Cortny_35":
			PlaySound("VOICE\English\LE\Cortny\Cortny_02.wav");
			dialog.text = "William Cortney, Baronet Cortney, at your service. By the power vested in me by the British Empire, with the full support of her trusted ally France, your vessel is hereby under arrest. Here are the papers; please make sure to read them and tell your men to keep their hands away from their weapons. You are detained, but not yet arrested. If you don't do anything foolish, you will be released at the first port.";
			link.l1 = "Baronet, subayımı... subayımı geri almak zorundayım!";
			link.l1.go = "Cortny_36";
		break;
		
		case "Cortny_36":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "Endişelenmeyin Kaptan, onu geminize götüreceğim. Sizden ricam, şimdi sandalınıza dönmeniz. Bu geminin komutasını alıp Basse-Terre'e yelken açacağım. Eğer baş düşmanınızı şahsen alaya almak gibi bir niyetiniz yoksa, bizi burada bırakmakta özgürsünüz. Sadece, Guadeloupe'a ulaşmamıza yardımcı olması için birkaç adamınızı bana vermenizi istiyorum.";
			link.l1 = "Pekâlâ, Mösyö. Hiç istemem. Ona en kötü dileklerimi iletin. Hoşça kalın ve tekrar teşekkürler!";
			link.l1.go = "Cortny_37";
		break;
		
		case "Cortny_37":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaCortnyFinal");
		break;
		
		case "Cortny_38":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "Charles, seni görmekten mutluyum. Dönmeni ummuştum ama bunun gerçekten olacağına asla inanmamıştım.";
			link.l1 = "Aynı şekilde, Baronet. Markiz'i ziyarete mi geldiniz? Bu arada, kendisi nerede?";
			link.l1.go = "Cortny_39";
		break;
		
		case "Cortny_39":
			dialog.text = "Hâlâ anlamıyorsun, değil mi? O kaçtı. Ayrıca, Angerran de Chievous sana içten özürlerini iletiyor. Onu, senin hiçbir zaman oyunun bir parçası olmadığın, sadece bir başka kurban olduğun konusunda ikna etmeyi başardım. Tıpkı onun gibi. İyi adam yazmaya zahmet etmedi ama işlerin bu hale gelmesinden dolayı gerçekten çok üzgün.";
			link.l1 = "Çok mu üzgünmüş, öyle mi?! Ne diyorsun sen, Mösyö?";
			link.l1.go = "Cortny_40";
		break;
		
		case "Cortny_40":
			dialog.text = "Seninle ben, asıl meseleyi gözden kaçırdık. O incilerden nasıl haberdar oldu? O İspanyol kaptanı bu eve kim davet etti? Kim o alçağı böyle bir hazineye peşine düşmeye itmiş olabilir?";
			link.l1 = "Ciddi misin? Bu olamaz...";
			link.l1.go = "Cortny_41";
		break;
		
		case "Cortny_41":
			dialog.text = "Kesinlikle olabilir. Markiz rolünü mükemmel oynadı, neredeyse her şeyi başarıyla tamamlıyordu. Fakat, yaptığımız soruşturma sayesinde, de Chievous'a bir hırsız ve korsan olarak değil, aslında kandırılmış bir kurban olarak yaklaştım. Onun içine sürüklendiği durumu oldukça çabuk fark etti, fakat elinde hiçbir kanıt yoktu ve kendi başına harekete geçmeye karar verdi. Sonrasında ne olduğunu biliyorsun.";
			link.l1 = "Tüm bunların arkasında Markiz mi varmış? De Chievous buna saf bir çocuk gibi kandı!";
			link.l1.go = "Cortny_42";
		break;
		
		case "Cortny_42":
			dialog.text = "Kesinlikle. Tutku çok tehlikeli bir şeydir, Charles! Bu evde kumar oynadığın o geceyi hatırlıyor musun? Angerran, markizin üzerinde nüfuz kazanarak ondan ihtiyacı olan kanıtı elde etmeye çalışıyordu. Evet, hile yaptı, ama yıllarca süren umutsuz bir tutkunun en yıkıcı ihanetle sona ermesinden sonra çaresizdi! Ama sen araya girdin, kendini onun koruyucusu ilan ettin ve bu rolde başarılı oldun. De Chievous, senin ve onun aynı düşüncede olduğunuzu sandı. Sana kaybettiği bir gemiyi, onun seyir defterlerini ele geçirmemen için çaldı. Subayını kullanarak, seni ve onu - kendi inancına göre ölümcül düşmanlarını - birbirine düşürmeye çalıştı.";
			link.l1 = "Söyleyecek söz bulamıyorum!";
			link.l1.go = "Cortny_43";
		break;
		
		case "Cortny_43":
			dialog.text = "Artık nasıl olduğunu biliyorsun Charles! Markiz hem zeki, hem nefes kesici güzellikte, hem de bir o kadar tehlikeli. Yeni Fransa'nın en seçkin insanlarını ne kadar süreyle parmağında oynattı, bilmiyorum. Yıllarca, diyebilirim. Neyse, artık seni ilgilendirmiyor. Seni tekrar görmek güzeldi, ama daha altüst etmem gereken odalar var, ev büyük. Muhtemelen hiçbir şey bulamayacağız, ama en azından denemek zorundayız.\nYollarımız ayrılmadan önce bir şey daha. Al, bunu da yanında götür. Hatıra olarak sakla. Belki hazır olduğunda onu hanımefendine verirsin. Çok şanslısın, biliyor musun? Özellikle de zavallı de Chievous'la karşılaştırınca!";
			link.l1 = "Haklısınız, öyleyim. Elveda, ve arayışınızda Tanrı yardımcınız olsun, Baronet!";
			link.l1.go = "Cortny_44";
		break;
		
		case "Cortny_44":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Town", "reload", "reload9", "GoldenGirl_SPFinal");
		break;
		
		case "Cortny_45": // фин 3
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Bugün ne güzel bir gün, değil mi Kaptan? Yaptıklarınızı duydum, ama sizi sıradan bir korsan olarak hiç hayal etmemiştim. Ne cüret – yaptıklarınızdan sonra St. Jones'a gelmek!";
			link.l1 = "Belki korsanım, bu doğru efendim, ama ben aptal mı görünüyorum? Neden durup dururken Mercury'yi yağmalayıp İspanyol incilerini aldıktan sonra buraya geleyim ki?";
			link.l1.go = "Cortny_46";
		break;
		
		case "Cortny_46":
			dialog.text = "Kabul ediyorum, şu anda bu konuşmayı yapıyor olmanın tek nedeni, bir ilmekten sallanıyor olmaman. Bak, bu işte gizlediğimiz küçük bir ayrıntı var. Üzerinde bulduğumuz inciyi kastetmiyorum. Sözünü ettiğim, brigantine'in adı.";
			link.l1 = "Ne demek?";
			link.l1.go = "Cortny_47";
		break;
		
		case "Cortny_47":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "Regina adında bir kurye brigantini, son iki yıldır San Jose limanına atanmıştı. Kaptanı bizim için istihbarat toplar, ayrıca her türlü... işi de hallederdi. Resmi olarak, taşıdığı kayıp diplomatik postayı bahane ederek onu arıyoruz. Pek inandırıcı bir bahane değil, kabul ediyorum. Yine de, kaptanın kamarasını iyice araştırmadan geminin gerçek adını öğrenemezdin.";
			link.l1 = "Eskiden kördüm, ama şimdi her şeyi görüyorum. Lütfen beni dinleyin efendim, açıklayacağım!";
			link.l1.go = "Cortny_48";
		break;
		
		case "Cortny_48":
			dialog.text = "Pekâlâ, daha çok çabala kaptan. Hayatın pamuk ipliğine bağlı.";
			link.l1 = "Bu casusluk hikayesiyle hiçbir alakam yok! İspanyolların da yok. Ağınız güvende, merak etmeyin. Ama bir yerde sızıntı olmuş ve biri bundan faydalanmış. Sonra da, ben bu kişiyle tartışmaya girdim. Onun Mercury işine karıştığına dair kanıt buldum ve bunu ona karşı kullanmak istedim.";
			link.l1.go = "Cortny_48_1";
		break;
		
		case "Cortny_48_1":
			dialog.text = "";
			link.l1 = "Tanrı şahidim olsun, bu işi sıradan bir korsanlık vakası sanmıştım, Kraliyet’in istihbaratının bununla ilgisi olabileceğini aklımın ucundan bile geçirmemiştim! Elimde sadece bu inci var, ama daha fazlasını ne zaman ve nerede bulabileceğini çok iyi biliyorum.";
			link.l1.go = "Cortny_49";
		break;
		
		case "Cortny_49":
			dialog.text = "John Thurloe'yu duydun mu? O, Kraliyet istihbaratının başı. Bir gün Londra'da olacağım ve Mercury'nin akıbetini bizzat ona rapor edeceğim. Bu yüzden, bana o zavallı düşmanının adını ver.";
			link.l1 = "Angerran de Chievous, Kont de Levy Vantadur'un piçi. Sanırım Mercury'yi sadece korsanların ganimetini taşıyan bir gemi olarak görüyordu. İncilerden haberi olabilir, ama İngiliz istihbaratıyla olan bağlantıdan haberi yoktu.";
			link.l1.go = "Cortny_50";
		break;
		
		case "Cortny_50":
			dialog.text = "Hayal kırıklığına uğratmıyorsun, Kaptan, bunu kabul etmeliyim! Ne eğlence, ne düşmanlar seçmişsin! Peki. İnciden başka hangi kanıtların var?";
			link.l1 = "De Chievous has a frigate. I used to own it... for one night only, yet I managed to learn something. He is an extremely pedantic man; you will learn all about his attack on the Mercury from his log. I am quite sure that he still possesses a portion of the prize too. Maybe even more black pearls if there was more than one.";
			link.l1.go = "Cortny_51";
		break;
		
		case "Cortny_51":
			dialog.text = "Birden fazla, buna güvenebilirsin. Regina'yı sıradan inciler uğruna asla riske atmayız. Umarım Monsieur de Chievous ile mutlaka konuşmam gerektiğini anlıyorsundur. İnciler umurumda değil, ama sızıntı hakkında daha fazlasını öğrenmeliyim. Üstlerim, onlara tam bir tablo sunmazsam beni yerin dibine sokar.";
			link.l1 = "Sizin için bir buluşma ayarlamaktan memnuniyet duyarım, fakat acele etmeliyiz! Şu anda de Chievous'nun fırkateyni Guadeloupe'a doğru yol alıyor, sahibi ise şu an orada, yerel valinin koruması altında. Eminim yaptıklarının farkında ve en kısa sürede Yeni Dünya'dan kaçacaktır.";
			link.l1.go = "Cortny_52";
		break;
		
		case "Cortny_52":
			dialog.text = "Bunlar çok ciddi ithamlar, hem de çok önemli insanlar hakkında, Kaptan. Sonrasında ne tür bir... fırtınanın kopabileceğinin farkında mısınız? Bir haydutun, müttefik bir ülkenin bayrağını taşıyan bir gemiye saldırması mı? Bu, iki büyük ülke arasındaki ilişkileri gerçekten karmaşık hale getirebilir. Sizi bu kadar büyük bir riski göze almaya itecek kadar onun size nasıl dokunduğunu hayal etmekte zorlanıyorum.";
			link.l1 = "Benden bir şey aldı, efendim. En çok değer verdiğim şeyi. Hayatımdan bile daha kıymetli. Bunu düzeltmeliyim. Bu savaş çıkmasına yol açarsa, bayrağımın altında ülkeme hizmet etmiş olurum. Yine de, de Chievous hak ettiğini bulacak ve suçlu sadece o olacak!";
			link.l1.go = "Cortny_53";
		break;
		
		case "Cortny_53":
			dialog.text = "Sana hiç kimse büyük tehlike taşıyan bir adam olduğunu söyledi mi, Kaptan? Amacına ulaşmak için dünyanın yarısını savaşa sürüklemeye hazır mısın? Pekala, senin istediğin gibi olsun. Seninle birlikte Basse-Terre'e gideceğim. Böyle bir izden vazgeçemem. Kanıtlarını yazması için bir katip göndereceğim, ben de gemimi hazırlayacağım.";
			link.l1 = "Teşekkür ederim, efendim. Ama burada oyalanacak vaktimiz yok, sizi uyarıyorum!";
			link.l1.go = "Cortny_54";
		break;
		
		case "Cortny_54":
			dialog.text = "Kaptan de Maure, zamanında yetişeceğiz, senden hiç şüphem yok. Ama bu macera yolunda gitmezse... beni anlıyorsun, değil mi? Sana düzgün bir mezar bile vaat edemem.	";
			link.l1 = "Evet, efendim. Sizi tamamen anlıyorum.";
			link.l1.go = "Cortny_55";
		break;
		
		case "Cortny_55":
			DialogExit();
			npchar.dialog.currentnode = "Cortny_56";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "Baster_Townhall", "goto", "goto4", "GoldenGirl_ReloadToBaster", 10.0);
		break;
		
		case "Cortny_56":
			dialog.text = "Zar atıldı, Kaptan. Angerran de Chievous ile bir görüşme talep ettim. Fırkateyni limana varır varmaz derhal aranacak. Francois de Lyon'un bazı şüpheleri var, ama belgelerimdeki mühürler şimdilik onu durduruyor. Durum netleşene kadar şehirde kalmanı rica ediyorum.";
			link.l1 = "Elbette, efendim, anlıyorum.";
			link.l1.go = "Cortny_57";
		break;
		
		case "Cortny_57":
			dialog.text = "O halde bunu da anlayışla karşılayacağını umuyorum. Şu beyefendilere kılıcını ver ve onlarla git, böylece sözünü tutacağına emin olabilirim.";
			link.l1 = "İnanılmaz... Lordum Cortney, ciddi misiniz?!";
			link.l1.go = "Cortny_58";
		break;
		
		case "Cortny_58":
			dialog.text = "Tam anlamıyla ciddiyim. Hâlâ başlıca şüphelilerimden birisin ve seni bu şartlar altında serbest bırakmak büyük bir aptallık olurdu. Eğer söylediklerin doğru çıkarsa, uygun gördüğüm şekilde senden özür dileyeceğim.";
			link.l1 = "";
			link.l1.go = "Cortny_59";
		break;
		
		case "Cortny_59":
			DialogExit();
			GoldenGirl_BasterArest();
		break;
		
		case "comendant":
			dialog.text = "Selamlar, Mösyö de Maure. Başlayalım mı?";
			link.l1 = "Memnuniyetle, kurallar nedir? Açıkçası, yemekle fazla meşguldüm ve muhtemelen şartları yanlış duydum.";
			link.l1.go = "comendant_1";
		break;
		
		case "comendant_1":
			dialog.text = "Kurallar basit. Kart başına 10.000 peso, biri pes edene kadar oynarız. Makbuz ve borç kabul edilmez.";
			link.l1 = "Bana uyar. Hadi yapalım, Albay.";
			link.l1.go = "comendant_2";
		break;
		
		case "comendant_2":
			DialogExit();
			npchar.money = 70000;
			pchar.questTemp.GoldenGirl.Game.G1 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "comendant_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Lanet olsun! Bir daha asla! Peki öyle olsun, monsieur de Maure, bir sonraki turda bol şans.";
				link.l1 = "Zevkle, Albay. Hoşça kalın.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "İyi savaştınız, ama Talih Hanım'ın kendi planları vardı. Elveda, monsieur de Maure. Oyun için teşekkür ederim.";
					link.l1 = "Evet, sanırım bu işte kendimi fazla abarttım. Elveda, Albay.";
				}
				else
				{
					dialog.text = " Oyunu bırakmaya karar verdiniz ve böylece yenilgiyi kabul ettiniz! Cesurca savaştınız, ama talih başka türlü hükmetti. Hoşça kalın, monsieur de Maure, ve oyun için teşekkürler.";
					link.l1 = "Evet, sanırım bu konuda kendimi fazla abarttım. Elveda, Albay.";
				}
			}
			link.l1.go = "comendant_4";
		break;
		
		case "comendant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// Португалец или Васкез
		case "moreno":
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "Kaptan Charles de Maure, ne büyük sürpriz!";
					link.l1 = "Kaptan. Moreno muymuş! Seni buraya ne getirdi?!";
					link.l1.go = "moreno_1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						pchar.questTemp.GoldenGirl.Vaskez = "true";
						dialog.text = "Kaptan Charles de Maure, memnun oldum.";
						link.l1 = "Daha önce tanışmış mıydık, monsieur... Moreno?";
						link.l1.go = "moreno_5";
					}
					else // васкез нейтральный
					{
						dialog.text = "Kaptan Charles de Maure, memnun oldum.";
						link.l1 = "Daha önce tanışmış mıydık, Mösyö... Moreno?";
						link.l1.go = "moreno_4";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "Captain Charles de Maure, memnun oldum.";
				link.l1 = "Daha önce tanışmış mıydık, Mösyö... Moreno?";
				link.l1.go = "moreno_4";
			}
		break;
		
		case "moreno_1":
			dialog.text = "Uzun bir hikaye. Her zamanki gibi, kaptan. Gözlerinden soruların olduğunu görebiliyorum. Sadece sessiz ol ve sıradan bir denizciyle alay ediyormuş gibi davran.";
			link.l1 = "Evet, bu şık takım sana çok yakışmış, sade dostum. Bence onu nasıl giyeceğini biliyorsun.";
			link.l1.go = "moreno_3";
		break;
		
		case "moreno_3":
			dialog.text = "Sadece nadir zamanlarda, şans eseri. Bugün o gün. Hadi kumar oynayalım, Kaptan. İnsanlar izliyor, onları bekletmek ayıp olur.";
			link.l1 = "Pekala, sonra konuşuruz. Anlaştık... Kaptan Moreno, lütfen.";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_4":
			dialog.text = "Seni biraz tanıyorum, ama bunun bir önemi yok. Kartları dağıt, Kaptan de Maure, insanlar bir gösteri istiyor.";
			link.l1 = "İlginç. Özellikle İspanyol aksanınız ve Madam Botot'nun övgüleriyle birlikte. Pekâlâ. Deniz denize karşı, hadi yapalım!";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_5":
			dialog.text = "Seni gayet iyi hatırlıyorum. Sen ve eski kaptanım Le Francois'da adamlarımı doğradınız. O alçak da hak ettiğini buldu zaten, senin yardımın olmadan olmazdı, yanlış mı hatırlıyorum? Ama benden teşekkür bekleme, Franz Garke'yi öldürdün ve bunu asla affetmeyeceğim.";
			link.l1 = "Portekizli çeyrekbaşı mı? Kanlı Don, değil mi? Bu gece gittikçe güzelleşiyor. Hadi yapalım!";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_6":
			DialogExit();
			npchar.money = 110000;
			pchar.questTemp.GoldenGirl.Game.G2 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "moreno_7":
			if (!CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win") && !CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
			{
				dialog.text = "Oynamaya devam etmeyi reddettin ve böylece yenilgiyi kabul ettin! Demek ki Şans Tanrıçası kararını verdi. Hoşça kal, Kaptan.";
				link.l1 = "Aynı şekilde, Mösyö Moreno. Oyun için teşekkür ederim.";
				link.l1.go = "moreno_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "Sanırım Şans Tanrıçası sözünü söyledi. Elveda, Kaptan, belki tekrar karşılaşırız.";
					link.l1 = "Aynı şekilde, Mösyö Moreno. Oyun için teşekkürler.";
					link.l1.go = "moreno_8";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						dialog.text = "Anlaşılan Şans Tanrıçası kararını verdi. Hoşça kal, Kaptan, belki bir gün başka koşullarda tekrar karşılaşırız, he-he.";
						link.l1 = "Dört gözle bekliyorum, Mösyö Moreno.";
						link.l1.go = "moreno_8";
					}
					else // васкез нейтральный
					{
						dialog.text = "Hepsi bu. Kader kararını verdi, Kaptan. Elveda.";
						link.l1 = "Hoşça kal, Mösyö Moreno.";
						link.l1.go = "moreno_8";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "İşte bu kadar. Kader kararını verdi, Kaptan. Elveda.";
				link.l1 = "Hoşça kal, Mösyö Moreno.";
				link.l1.go = "moreno_8";
			}
		break;
		
		case "moreno_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "moreno_9":
			dialog.text = "Sizi görmek ne güzel, Monsieur Kaptan de Maure! Açıkçası, her şeyi bekliyordum, tam bir muhafız birliği dahil, ama sizi değil.";
			link.l1 = "Señor Moreno, yerel yetkililerle bir sorun mu yaşıyorsunuz? Bu arada, sizi görmek de güzel, ha-ha!";
			link.l1.go = "moreno_10";
		break;
		
		case "moreno_10":
			dialog.text = "Şunu söyleyeyim, ev sahibimizin davetini kimse geri çeviremez. En azından, böyle bir daveti. Hadi ama Charles, bırak şu komediyi. Markiz, gerçek kimliğimi bildiğini bana açıkça belli etti.";
			link.l1 = "...";
			link.l1.go = "moreno_11";
		break;
		
		case "moreno_11":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_90";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_12":
			dialog.text = "Hanımefendi, çok zarifsiniz! Bu yeni dostunuz beni daha önce bir kere ele vermeye kalktı. Gerçi pek başarılı olamadı, hatta öyle çok kez paçamı kurtardı ki artık sayısını unuttum. Her neyse, şimdi ona bir borcum var, o yüzden tehditlere gerek yok, hiç merak etmeyin.";
			link.l1 = "Teşekkür ederim, Bartholomew. Angerran de Chievous beni son derece zor bir duruma soktu ve onu mutlaka alt etmem gerekiyor. Çok değer verdiğim birinin hayatı buna bağlı. Bana güven, bu sefer hiçbir şey beni durduramayacak.";
			link.l1.go = "moreno_13";
		break;
		
		case "moreno_13":
			dialog.text = "Yeter, Kaptan, biz dost değil miyiz? Tüm Takımadalar boyunca yaptığımız o yarışı hatırlıyor musun? O benim için çok şey ifade ediyordu. Sana yardım etmek için elimden geleni yapacağım. Mercury'yi hiç duydun mu?";
			link.l1 = "Şimdi, o da ne? Bir gemi mi?";
			link.l1.go = "moreno_14";
		break;
		
		case "moreno_14":
			dialog.text = "Tam olarak bir İngiliz brigantini. Görevi, Albay D'Oyley'in özel korsanlarının Batı Ana'daki İspanyol inci madenlerini yağmaladıktan sonra elde ettikleri ganimetleri taşımaktı. Bazen efsanevi siyah incileri avlayanlar var ya, duydun mu hiç? Kaynağım doğruysa, o incilerden birkaçı Mercury'de saklanmış. Bir ay önce Martinik ile Guadeloupe arasında pusu kurdum, o beyefendileri bekledim. Ama nafile! Bir hafta boyunca denizde kaldık, sonunda başarısızlığı kabul etmek zorunda kaldık.";
			link.l1 = "Demek ki kaynağın güvenilir değilmiş ve eline hiçbir ödül geçmedi. Peki, de Chievous'un bütün bunlarla ne ilgisi var?";
			link.l1.go = "moreno_15";
		break;
		
		case "moreno_15":
			dialog.text = "Ben de aynı şeyleri düşünüyordum, ta ki Mercury'nin Antigua'da hiç görünmediğini öğrenene kadar. Curaçao yakınlarında görüldüğünde ise şaşkınlığımı tahmin edersin, çünkü Martinique civarında benden gizlice geçmesi imkânsızdı. İngilizler öfkeden deliye döndü! Böyle bir ganimeti kaçırmak kolay hazmedilecek iş değil! Her neyse, ben de meraklandım ve araştırmaya başladım, herkesin keyfini kaçıran o özel kişi hakkında. Böyle bir ganimet hemen elden çıkarılamaz, bu yüzden Le François'ya gidip o herifi bulmaya ve bana olan borcunu almaya karar verdim.";
			link.l1 = "Hikayen bana tanıdık geliyor. 'Karma' kelimesini duydun mu hiç? Başına bela açmayı iyi biliyorsun. Ama hâlâ bunun bana nasıl bir faydası olacağını anlamış değilim?";
			link.l1.go = "moreno_16";
		break;
		
		case "moreno_16":
			dialog.text = "Acele etme Kaptan, hikayemin en güzel kısmını şimdi anlatacağım. O yıkanmamış ama şık dostun var ya – adamlarının yerel dükkânlarda bıraktığı iz, göz alıcı incilerle doluydu. Bir yığın İspanyol incisi, bol bol savrulmuş.";
			link.l1 = "...";
			link.l1.go = "moreno_17";
		break;
		
		case "moreno_17":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_92";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_18":
			dialog.text = "Düydün mu, Kaptan?";
			link.l1 = "Sence de Chievous, Jacques the Kind ve adamlarından çalınmış incileri satın almış olabilir mi? Korkarım bu... yeterli değil.";
			link.l1.go = "moreno_19";
		break;
		
		case "moreno_19":
			dialog.text = "Öyle, kaptan. O satın almadı, satıyordu! Bu konuda Barbazon'la konuştum ve bana, ortağından hatırı sayılır miktarda kusursuz inci aldığını doğruladı. Sonra da bunları Avrupa'ya göndermiş. Ayrıca kolyedeki o siyah inci ve de Chievous'un gemisinin tamirden geçtiği gerçeği var. İşçiler bana onun fırkateyninde on iki librelik toplardan açılmış delikler olduğunu söyledi. Akıllı bir insan, kim böyle toplarla bir fırkateyne saldırır ki?";
			link.l1 = "Bizim brigantin gibi görünüyor! Ayrıca, de Chievous'un fırkateyninin ne kadar hızlı olduğuyla övündüğünü hatırlıyorum. Ama bu delilik neden? Britanya ile barış içindeyiz, neden bu kadar riske girsinler ve ne için? Siyah inciler çok nadir bulunur, evet, ama imkânsız değiller.";
			link.l1.go = "moreno_20";
		break;
		
		case "moreno_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_94";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_21":
			dialog.text = "Ve işte tam orada hata yaptı! İngilizler, Mercury'nin kayboluşuyla ilgili resmi bir soruşturma başlattı bile, gerçi ona önemli belgeler taşıyan kayıp bir kurye gemisi diyorlar. Her türlü ipucu cömertçe ödüllendirilecek, sorumlular ise ağır şekilde cezalandırılacak. En güzeli de, Antigua'ya özel bir soylu yetkili göndermişler, şimdi davayı durmaksızın kurcalıyor. Adını hatırlamıyorum—kendi kadar gösterişli bir isimdi—ama beni aramıyor olmasına seviniyorum!";
			link.l1 = "Bu gerçekten ilginç! Görünüşe göre o siyah incileri çok istiyorlar. Mercury'de kaç tane vardı acaba, ve bütün bu bilgiler bana nasıl fayda sağlayabilir?";
			link.l1.go = "moreno_22";
		break;
		
		case "moreno_22":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_96";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_23":
			dialog.text = "Neden, o pislik seni de mi kızdırdı, Markiz? Alçak herif! Bu konuda da seninleyim, Kaptan de Maure! Hiç kimse Bartolomeo Portekizli'den ganimet çalmaya cesaret edemez!";
			link.l1 = "";
			link.l1.go = "moreno_24";
		break;
		
		case "moreno_24":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_98";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_25":
			dialog.text = "Bunca laftan sonra şöyle güzel bir içki lazım bana. Markiz, artık dost olduğumuza göre...";
			link.l1 = "Sanmıyorum ki bu evde rom olsun, Bartholomew.";
			link.l1.go = "moreno_26";
		break;
		
		case "moreno_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_100";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_27":
			dialog.text = "Evet tabii, o İngiliz müfettişinin dikkatini doğrudan fırkateynine çekelim! Eğer planımız buysa, o zaman bizim eski iyi Kaptan de Maure'u tanıyamıyorum!";
			link.l1 = "Komik gelecek ama plan bu. İkinizin de yardımına ihtiyacım olacak. Hanımefendi - tuttuğum korsanın esiri olacaksınız - Bartholomew, bu da senin görevin.";
			link.l1.go = "moreno_28";
		break;
		
		case "moreno_28":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_122";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_29":
			dialog.text = "Ve şu benim alçaklığım hakkında da! Portekizli Bartolomeo asla bir kadını kaçırmadı!";
			link.l1 = "Ve etmeyecek, ama de Chievous'nun adamlarına öyle görünecek. Ayrıca, onlara adını söylemene gerek yok. Hanımefendimizi gemiye al ve Angerran'ın fırkateyniyle Cape Scott Head yakınlarında buluş. Julianna'yı subayımla takas et ve Martinique'e dön. Sonra markizle beni bekle.";
			link.l1.go = "moreno_30";
		break;
		
		case "moreno_30":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_125";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_31":
			dialog.text = "Bunların hepsi gerçekten çok ilginçti, Charles, sen tam bir doğuştan şövalyesin. Ama takastan sonra onu nasıl geri götüreceğiz, Allah aşkına?";
			link.l1 = "Ben hallederim. Fazla vaktimiz yok, bu yüzden ayrılalım. Sen ve markiz Dominika'ya gidin, ben de hızla St. John's'a gideceğim. Albay D'Oyley'i ya da o İngiliz araştırmacıyı bulup Mercury'nin kaybolmasından kimin sorumlu olduğunu söyleyeceğim.";
			link.l1.go = "moreno_32";
		break;
		
		case "moreno_32":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_130";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_33":
			dialog.text = "Böyle bir olaydan sonra kopacak fırtınayı hiç düşündünüz mü, Kaptan? Şu anda Antigua tam bir arı kovanı ve siz bana ona taş atmamı söylüyorsunuz. Daha azı yüzünden savaşların çıktığını hatırlıyorum!";
			link.l1 = "Her şeyin sırası var... Onu ne pahasına olursa olsun geri getireceğim! Eğer dedikleri kadar güçlüyse, bırak de Levy Vantadur bütün bu karmaşayı kendi başına çözsün! Ayrıca, de Chievous'un Madame Botot'nun nasıl olup da gemisine bindiğini açıklaması hiç de kolay olmayacak.";
			link.l1.go = "moreno_34";
		break;
		
		case "moreno_34":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_132";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_35":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Hazır mısın? Bir duayla! Markiz, kaçırılmaya hazır mısın?";
			}
			else
			{
				dialog.text = "Hazır mısın? Tanrıya dua ederek! Markiz, toparlanman ne kadar sürecek?";
			}
			link.l1 = "";
			link.l1.go = "moreno_36";
		break;
		
		case "moreno_36":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_134";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "secundant": // fix 22-03-20
			dialog.text = TimeGreeting()+", Mösyö de Maure. Benim adım "+GetFullName(npchar)+", ve bu da "+GetFullName(characterFromId("GG_SecundantGG_2"))+" Ekselansları, Monsieur de Chievous ile düellonuza şahitlik etmemizi istedi.";
			link.l1 = "İyi akşamlar, beyler. Umarım her şey yolunda gider ve bu gece kimse ölmez. Ama her ihtimale karşı hazırlıklı olun. Bu 'beyefendi' hayal kırıklığı yaratabilir.";
			link.l1.go = "secundant_1";
		break;
		
		case "secundant_1":
			dialog.text = "Endişeniz yersiz. Bu düellonun önceden belirlenmiş kurallarına göre, hiçbir koşulda yardımcılar müdahale edemez. Yine de bizi uyardığınız için teşekkürler. Rakibiniz geldi. Yolunuz açık olsun, Kaptan. Ekselansları size, sağduyunuz için dua edeceğini iletmemi istedi.";
			link.l1 = "Eminim bana oldukça yardımcı olacak. Neyse, başlayalım.";
			link.l1.go = "secundant_2";
		break;
		
		case "secundant_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto8", "", 5); 
			sld = characterFromId("Angerran");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			for (i=1; i<=2; i++)
			{
				ref chr = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(chr);
				LAi_ActorFollow(chr, sld, "", 10.0);
			}
		break;
		
		case "sailor":
			dialog.text = "Kaptan, bir sorunumuz var. Gemimiz... şey, yok oldu.";
			link.l1 = "Ne, ne dedin?! Nasıl, kim? Başında tam bir nöbetçi birliği olmalıydı, ne saçmalıyorsun sen?!";
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Hayır, Kaptan, gemi değil. O pırıl pırıl. Dün kazandığın fırkateyn, artık o da bizim, değil mi? Oraya sadece on iki kişilik bir ödül mürettebatı gönderdik. Onun yeterli olacağını söyledi.";
			link.l1 = "Lanet olsun, dur ve bana en başından tam olarak ne olduğunu anlat!";
			link.l1.go = "sailor_2";
		break;
		
		case "sailor_2":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Hiçbir fikrim yok, Kaptan. Fırkateyn sabah sisiyle birlikte denize açıldı. Gözcüler, sis dağıldıktan birkaç saat sonra onun yokluğunu fark etti.";
			link.l1 = "Bu olamaz! Bana asla bunu yapmazdı! Gerçi... lanet olsun, daha yeni kavga etmiştik. Yoksa o mu...";
			link.l1.go = "sailor_3";
		break;
		
		case "sailor_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Durum daha da kötü, Kaptan. Balıkçılar bu sabah erken saatlerde ödül mürettebatımızdan iki adamımızı buldu. İkisi de ölüydü, boğazları kesilmişti.";
			link.l1 = "Lanet olsun! De Chievous! Marquise ile meşgulken gemisini çaldı! Umarım kadın hayattadır... Saçının teline bile zarar gelirse, ben...";
			link.l1.go = "sailor_4";
		break;
		
		case "sailor_4":
			dialog.text = "Will you give the orders to the boys to get ready, Cap? We can set sail in two hours' time, everybody's been on edge all morning, your second-in-command especially; we barely managed to stop him from sailing after them.";
			link.l1 = "Bunun için henüz erken. Önce... bunu iyice düşünmeliyim ve biriyle konuşmalıyım. Evet! Gemiyi hazırlayın! Herkes hazır olsun, döner dönmez yelken açacağız.";
			link.l1.go = "sailor_5";
		break;
		
		case "sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			GoldenGirl_GirlPrisoner();
		break;
		
		case "off_brothel":
			dialog.text = "Kaptan de Maure, neler oluyor? Hanımefendiye biri mi saldırdı?";
			link.l1 = "Buraya gelmemeliydin. Tanrı şahidimdir ki, bunu istememiştim.";
			link.l1.go = "off_brothel_1";
		break;
		
		case "off_brothel_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("GG_PatrolBrl_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GoldenGirl_BrothelAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Cap_Nayad":
			dialog.text = "Monsieur, sizi burada göreceğimizden neredeyse umudu kesmiştik. Uzun sandalınızda Marquise Botot'yu görüyorum. Nasıl olduğunu sormayacağım bile. Yol arkadaşınız sizi bekliyor. O güvende ve sağ salim, onu alın ve hemen buradan defolup gidin.";
			link.l1 = "Eğer ona dokunduysan, o eski tekneni paramparça ederim!";
			link.l1.go = "Cap_Nayad_1";
		break;
		
		case "Cap_Nayad_1":
			dialog.text = "Ne beklenmedik bir ilgi gösterisi. Merak etme, o adeta bir mahkum kraliçe gibi korundu. Tehditlerin beni ilgilendirmiyor. Bu arada, Chevalier de Chievous selamlarını iletti.";
			link.l1 = "Onun selamı da kendisi de umurumda değil. Benim... subayım nerede? Takasa başlayalım.";
			link.l1.go = "Cap_Nayad_2";
		break;
		
		case "Cap_Nayad_2":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaAlarmFinal");
		break;
		
		case "Cap_Nayad_3":
			dialog.text = "Monsieur, neredeyse sizi burada göreceğimizden umudu kesmiştik. Yoldaşınız sizi bekliyor. O güvende ve sağ salim... bir dakika, bu da kim? Markiz nerede?";
			link.l1 = "";
			link.l1.go = "Cap_Nayad_4";
		break;
		
		case "Cap_Nayad_4":
			DialogExit();
			LAi_SetActorType(npchar);
			chrDisableReloadToLocation = true;
			GoldenGirl_CortnySetOnDeck();
		break;
		
		case "antigua_officer":
			dialog.text = "Kılıcınızı verin, efendim. Ve sakın numara yapmaya kalkmayın, adamlarım bu aralar biraz gergin. Kurşun yemek istemezsiniz, değil mi?";
			link.l1 = "Ciddi misin? Peki, al ama dikkatli ol, bu senin kışlandan daha pahalı. Ekselansları, Baronet Cortney ile görüşme talep ediyorum!";
			link.l1.go = "antigua_officer_1";
		break;
		
		case "antigua_officer_1":
			dialog.text = "Merak etme, eminim sana uğramak için vakit bulacaktır.";
			link.l1 = "Birine yardım etmeye çalıştığında...";
			link.l1.go = "antigua_officer_2";
		break;
		
		case "antigua_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("SentJons_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 1, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_45"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_CortnyInJail", 10.0);
			bDisableCharacterMenu = true;//лочим F2
		break;
		
		case "baster_officer":
			dialog.text = "Ben de bundan hoşlanmıyorum, Mösyö. Ne yazık ki, bu küstah İngiliz öyle bir otoriteye sahip ki, Mösyö de Lyon bile pek bir şey yapamıyor. Özür dilerim Kaptan, lütfen kılıcınızı teslim edin.";
			link.l1 = "Umarım Monsieur de Chievous benimle aynı hücreyi paylaşmaz. Hadi gidelim beyler, ölü gibi yorgunum. Sonunda biraz uyuyacağım.";
			link.l1.go = "baster_officer_1";
		break;
		
		case "baster_officer_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("Baster_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			sld = characterFromId("Cortny");
			sld.lifeday = 0; // Captain Beltrop, убираем Кортни
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_136"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "Baster_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_JuliannaInJail", 7.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "24");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
		break;
		
		case "statist_1":
			dialog.text = "Nezaketsizlik etmek istemem, monsieur, ama şu anda konuşacak vaktim yok, gördüğünüz gibi burada neler oluyor. Hiçbir şeyi kaçırmak istemem!";
			link.l1 = "Dediğiniz gibi, monsieur.";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1_1":
			dialog.text = "Bu akşam tarihe geçecek, hissediyorum! İnsanlar buradan Versailles'a kadar bunu konuşacak! Marianne'im çok sevinecek ve tüm ayrıntıları öğrenmek isteyecek. Lütfen, monsieur, kenara çekilin, görüşümü engelliyorsunuz.";
			link.l1 = "Ben zaten gidiyorum, monsieur, gösterinin tadını çıkarın ve unutulmaz Marianne'e selam söyleyin... her kimse artık.";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1a":
			DialogExit();
			npchar.dialog.currentnode = "statist_1_1"; 
		break;
		
		case "statist_2":
			dialog.text = "Hah! Demek, Monsieur de Maure burada! Affınıza sığınırım... Kaptan Charles de Maure! Buyurun, lütfen, burada Eski Dünya'nın en seçkin şaraplarından bir koleksiyon var. Akşamı nasıl başlatmak istersiniz: bir yenilikle mi - sevgili Gironde kıyılarımızdan Cabernet Sauvignon ile mi, yoksa zamansız bir klasikle mi - İtalyan Sangiovese?";
			link.l1 = "Teşekkür ederim, monsieur, seninle içeceğim, ama biraz sonra.";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2_1":
			dialog.text = "Oh, Kaptan de Maure! Biraz daha şarap ister misiniz... hık? Bakın bize ne getirdiler - 1643 yılından, Rhône Vadisi'nin kuzey tepelerinden bir Syrah. Bu, kahretsin, gerçek bir mücevher! Ve o yıl her açıdan harikaydı, size söylüyorum... Sadece Gat Burnu'nda İspanyolların yenilgisi bile yeter! Bu arada... herkes neden bu kadar telaşlı, biliyor musunuz? Biri kendini kötü mü hissediyor? Neyse - sağlığınıza...";
			link.l1 = "Pekala, en azından birileri ikramlara değer veriyor. Au revoir, Monsieur.";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2a":
			DialogExit();
			npchar.dialog.currentnode = "statist_2_1"; 
		break;
		
		case "statist_3":
			dialog.text = "Oh, Kaptan Charles de Maure, senin hakkında bu şehirdeki herkes gibi ben de duydum! İzin ver kendimi tanıtayım - "+GetFullName(npchar)+", sizinle tanışmak büyük bir onur, inanın bana! Gerçekten valimizle aranız iyi mi? Bizi tanıştırabilir misiniz? Ona en derin saygılarımı sunmak isterim ve...";
			link.l1 = "Belki sonra. İyi akşamlar, monsieur.";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3_1":
			dialog.text = "Monsieur de Maure, bunu gördünüz mü?! Saygıdeğer valimiz ve bizzat Monsieur de Chievous - neredeyse birbirlerini burada öldüreceklerdi! Muhteşemdi! Marquise Botot bugün kendini aştı - her şey inanılmaz heyecanlı! Devamını sabırsızlıkla bekliyorum. Bu arada, belki de şimdi tam zamanı? Beni tanıştıracağına söz vermiştin... ";
			link.l1 = "Hiçbir şey vaat ettiğimi hatırlamıyorum. Üzgünüm, ama gitmem gerek.";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3a":
			DialogExit();
			npchar.dialog.currentnode = "statist_3_1"; 
		break;
		
		case "statist_4":
			dialog.text = "Monsieur de Maure, sonunda dâhi Madame Botot'nun salonuna teşrif ettiniz! Kendisi sizi görmek istediğinden birkaç kez bahsetmişti. Onun 'öğrencilerini' değerlendirme fırsatınız oldu mu? Evet, markiz gibi yıldızlar, sizin ve benim gibi ölümlülere göre değil. Ama bana inanın: bu hanımefendiler gerçek birer sanat eseri. Belki Michelangelo ya da örneğin Titian kadar şaşırtıcı değiller, ama yine de öyleler.";
			link.l1 = "İlginç bir karşılaştırma, monsieur. Neyse, sizi geceyle baş başa bırakıyorum....";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4_1":
			dialog.text = "Hayır, burası her zaman hareketlidir, ama şimdi havada büyük bir skandalın kokusu var, hissediyor musun? Lady Jacqueline beni yukarıda bekliyor, ama hâlâ oyun masalarından ayrılamıyorum! Lord Hazretleri ve Monsieur de Chievous gerçekten dişli rakipler ve son derece kararlılar. Görünen o ki, bu geceki bahisler sadece yıldızlara ulaşmakla kalmayacak, gök kubbeyi delip şeytanlara kadar gidecek!";
			link.l1 = "Şeytanlar aşağıda, monsieur. Cennetin kubbesinin ardında mutlaka melekler vardır.";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4a":
			DialogExit();
			npchar.dialog.currentnode = "statist_4_1"; 
		break;
		
		case "statist_5":
			dialog.text = "Eh, en azından hoş bir karşılaşma! Zaten tanışmıştık, Kaptan de Maure, ama muhtemelen hatırlamıyorsunuzdur. "+GetFullName(npchar)+" - Garnizonun altıncı piyade birliğinin kaptanıydım, İspanyollara karşı sokaklarımızda seninle birlikte savaştım. Doğrusunu söylemek gerekirse, dizimden vuruldum ve savaşın çoğunu tam da bu genelevin yanışını izleyerek, bir hendekte yatarak geçirdim. Ve işte şimdi buradayım – bir başka iç savaş, ve yine hayranlıkla bakıyorum, ama bu kez içeriden.";
			link.l1 = "Sizi tanıdığıma memnun oldum, monsieur. O gün gerçekten çok sıcaktı, ama itiraf etmeliyim ki, o zamandan beri burası çok daha güzel oldu!";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5_1":
			dialog.text = "Buradaki havayı nasıl buldunuz, kaptan? Görünen o ki, bu dünyevi budalalar ortalığı kana bulamaya karar vermiş! Merak ediyorum, valinin koltuğu da kart oyununda bahse konulabilir mi? Unutmayın sözümü – bu iş çelikle bitecek. Yazık, dizim yüzünden artık böyle eğlenceler bana göre değil. Yine de, Jacqueline'i bir yerde gördüm – onun beyi, olan bitene fena halde kapılmış durumda... Sanırım ben de gidip şansımı deneyeyim, burası hâlâ sakinken.";
			link.l1 = "İyi bir karar, size başarılar dilerim, monsieur. Ve şimdi benim... duvarlara dönmem gerek.";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5a":
			DialogExit();
			npchar.dialog.currentnode = "statist_5_1"; 
		break;
	}
} 
