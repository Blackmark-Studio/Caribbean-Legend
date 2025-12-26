
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		////// Леа Карно //////
		
		case "Exit":
			DialogExit();
		break;
		
		case "First Time":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"! Affedersiniz, siz bir denizci misiniz"+GetSexPhrase("veya","oress")+"?";
			link.l1 = "Ben Kaptanım "+GetFullName(pchar)+", hizmetinizdeyim.";
			link.l1.go = "Lea First Talk";
			DelLandQuestMark(npchar);
		break;

		case "Lea First Talk":
			dialog.text = "Ben Lea. Lea Carno... "+GetSexPhrase("Monsieur","Mademoiselle")+" Kaptan, yakın zamanda mı geldiniz? Denizde 'Cormorant' adında bir balıkçı teknesi görmediniz, değil mi? Bakın, kocam... kocam Pierre... iki gün önce denize açıldı ve hâlâ dönmedi.";
			link.l1 = "'Cormorant' mı? Hayır, öyle bir gemiyle hiç karşılaşmadım. O ismi mutlaka hatırlardım. Üzgünüm, Madam. Umarım eşiniz iyidir ve sadece yolunda biraz gecikmiştir.";
			link.l1.go = "Lea First Talk Rep Plus";
			link.l2 = "'Cormorant' mı? Ha! Bu geminin adı mı, yoksa sahibinin lakabı mı? Her halükarda, ikisini de görmedim.";
			link.l2.go = "Lea First Talk Rep Minus";
		break;

		case "Lea First Talk Rep Plus":
			dialog.text = "Ne düşüneceğimi bilmiyorum... Hiç bu kadar uzun süre ortadan kaybolmamıştı. Her zaman öğlene kadar mutlaka dönerdi. Şimdi ise... bir şey oldu. Hissediyorum.";
			link.l1 = "Yetkililere git. Sahil sularını taramaları için devriye gemisi gönderebilirler.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
		break;

		case "Lea First Talk Rep Minus":
			dialog.text = "Ne düşüneceğimi bilmiyorum... Bu kadar uzun süre hiç gitmemişti. Her zaman öğlene kadar mutlaka dönerdi. Şimdi... bir şey oldu. Hissediyorum.";
			link.l1 = "Yetkililere git. Sahil sularını taramak için bir devriye gemisi gönderebilirler.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
		break;

		case "Lea First Talk1":
			dialog.text = "Oh, "+GetSexPhrase("Monsieur","Mademoiselle")+" Kaptan, elbette komutanla zaten konuştum. Ama ne faydası oldu? Sadece omuz silkti... Kocamı aramak için boşta gemisi olmadığını söyledi.\nPeki ya ben? Yapabildiğim tek şey burada durup ufka bakmak, beklemek... ve umut etmek.";
			link.l1 = "Şimdi, şimdi, Madame Lea. Hemen umutsuzluğa kapılma. Sana yardım etmek için bir günümü ayırabilirim sanırım.";
			link.l1.go = "Agree To Help";
			link.l2 = "Neden bu kadar endişeleniyorsun? Belki de sabah meltemi onu hoş bir hanımefendinin kollarına sürüklemiştir. Biraz dolaşır, temiz havayı içine çeker ve geri döner.";
			link.l2.go = "bad joke";
			link.l3 = "Bir tavsiye ister misin? Gözlerini ufka dikmekten vazgeç. Le François’daki meyhaneye git ve kocanı orada ara. Alınma ama büyük ihtimalle sadece evdeki dertlerden biraz uzaklaşmak istemiştir, sen ise bunu bir trajediye çeviriyorsun. Bol şans.";
			link.l3.go = "Rejection";
		break;

		case "Agree To Help":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Kaptan, ben... Size nasıl teşekkür edeceğimi bile bilmiyorum... Siz... bunun benim için ne anlama geldiğini tahmin bile edemezsiniz! Herkes omuz silkip geçiyor... Ama siz... yardım etmeye gönüllüsünüz. Teşekkür ederim!";
			link.l1 = "Daha teşekkür etmene gerek yok. Söylesene—kocan genelde nerede balık tutardı? Sabit bir yeri var mıydı, yoksa dolaşmayı mı severdi?";
			link.l1.go = "Go To Help";
		break;
		
		case "bad joke":
			dialog.text = "Cazibeli bir hanımefendi mi?! Şaka yapmak için gerçekten doğru zaman olduğunu mu düşünüyorsun? Onun başının dertte olduğunu biliyorum... ve sen benim acıma gülüyorsun! (ağlar) Şu anda dünyadaki her şey bana karşı. Kimse yardım etmek istemiyor... Kimse kalbimin ne kadar ağır olduğunu anlamıyor.";
			link.l1 = "Madame Lea, Allah aşkına, düşüncesizliğimi bağışlayın. Kötü bir niyetim yoktu! Yemin ederim, kocanızı bulmak için elimden geleni yapacağım. Sadece nereden başlamam gerektiğini söyleyin.";
			link.l1.go = "bad joke1";
		break;

		case "bad joke1":
			dialog.text = "Sen...? Gerçekten bana yardım etmek mi istiyorsun?";
			link.l1 = "Elbette. Affedilmez ve zamansız şakamı telafi etmek için yapabileceğimin en azı bu.";
			link.l1.go = "bad joke2";
		break;

		case "bad joke2":
			dialog.text = "Teşekkür ederim, "+GetSexPhrase("Monsieur","Mademoiselle")+" Kaptan. Teşekkür ederim... Gerçekten, beni hazırlıksız yakaladınız—ne diyeceğimi bilemiyorum...";
			link.l1 = "Daha teşekkür etmene gerek yok. Onun yerine bana söyle—kocan genelde nerede balık tutar? Sabit bir yeri mi var, yoksa sürekli yer mi değiştirir?";
			link.l1.go = "Go To Help";
		break;

		case "Go To Help":
			dialog.text = "Pekâlâ... Pierre... Bana nadiren tam olarak nerede balık tuttuğunu söylerdi. 'Onun sırrı' derdi. Ama onu bulmana yardımcı olacaksa... Belki... Bilmiyorum... Gerçekten yardım etmek istiyorsun, değil mi, "+GetSexPhrase("Monsieur","Mademoiselle")+" Kaptan mı? Gerçekten mi?";
			link.l1 = "Kocanızın gizli balık avı yerini paylaşmayı düşünüyor musunuz? Ailenizin sırrı bende kalacak—bir kaptan olarak söz veriyorum. Aramaya başlamak için yeri bilmem gerek.";
			link.l1.go = "Go To Help1";
		break;

		case "Go To Help1":
			dialog.text = "Haklısın, "+GetSexPhrase("Monsieur","Mademoiselle")+" Kaptan... Beni affedin. Orası Pierre için çok şey ifade ediyordu. Her zaman oranın onun tek gerçek sırrı, küçük hazinesi olduğunu söylerdi.\nAma nerede olduğunu biliyorum. Eğer onu eve getirmeye yardımcı olacaksa... Le Marin Körfezi yakınlarında balık tutardı. Güney kıyısında, kasabaya çok uzak değil. Lütfen, yalvarıyorum—onu bulun!";
			link.l1 = "Endişelenme, Lea. Elimden gelen her şeyi yapacağım. Düşmanı var mıydı? Son zamanlarda onu tehdit eden biri oldu mu?";
			link.l1.go = "Go To Help2";
		break;

		case "Go To Help2":
			dialog.text = "Düşmanlar mı? Pierre mi? O, yaşayan en iyi kalpli insan! Bir sineğe bile zarar vermez... Sadece sıradan bir balıkçı. Kime ne yapmış olabilir ki? Ne olmuş olabileceğini hiç anlamıyorum... Her şey o kadar garip ki... ve korkutucu...";
			link.l1 = "Korkmayın, Madame Lea. Hemen yola çıkacağım. Eminim kocanız güvendedir. Onu sevgi dolu kollarınıza geri getireceğim. Güçlü kalın.";
			link.l1.go = "Return Lea Exit";
		break;

		case "Return back to Lea":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Kaptan, lütfen—herhangi bir haber var mı? Bir şey öğrendiniz mi? Hiçbir şey, en ufak bir şey bile?";
			link.l1 = "Henüz değil, korkarım. Ama hâlâ arıyorum, Lea!";
			link.l1.go = "Exit";
		break;
		
		case "Return Lea Exit":
			DialogExit();
			npchar.dialog.currentnode = "Return back to Lea";
			AddQuestRecord("VPVL", "2"); 
			DoQuestCheckDelay("VPVL_Start", 0.1);
			LocatorReloadEnterDisable("FortFrance_Town", "gate_back", true);
		break;
		
		case "Rejection":
			DialogExit();
			npchar.dialog.currentnode = "Rejection1";
			SetTimerCondition("VPVL_ClearLea", 0, 0, 2, false);  // Удаляем Леа через 2 дня
			CloseQuestHeader("VPVL");
		break;
		
		case "Rejection1":
			dialog.text = "Daha ne istiyorsun? Zavallı bir kadınla dalga geçmekten yeterince eğlenmedin mi?";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

		case "Lea second talk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Kaptan! Pierre! Seni gördüğüme ne kadar sevindim bilemezsin! Onu bulmuşsun!";
			link.l1 = "Madame Lea, size Pierre Carno'yu, bizzat kendisini takdim edeyim. Kolay atlatmadı diyemem, ama eminim ki sizin ilginizle kısa sürede toparlanacaktır.";
			link.l1.go = "Lea second talk1";
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
		break;

		case "Lea second talk1":
			dialog.text = "Pierre! Kutsal Meryem Ana! Senin için endişeden hasta oldum! Neredeydin? Yüzünde hiç renk yok... çok solgunsun... Ah! Bu da ne?! Bu korkunç yaralar?! Kesikler... ve yanıklar...";
			link.l1 = "Sakin ol şimdi, kalbimin hazinesi. Bunlar sadece birkaç çizik, zamanla geçer. Yüzünü tekrar görmek... tek istediğim buydu. Kaptan olmasaydı... borçluyum "+GetSexPhrase("onu","onu")+" hayatımın ta kendisi. ";
			link.l1.go = "Lea second talk2";
			CharacterTurnByChr(npchar, CharacterFromID("VPVL_Pier_carno"));
			sld = CharacterFromID("VPVL_Pier_carno");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_Lea_girl"));
			locCameraFromToPos(-7.62, 3.1, 83.26, false, 30, -15, 0);
		break;

		case "Lea second talk2":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Kaptan... Ben... Size nasıl teşekkür edeceğimi bile bilmiyorum... Onu buldunuz! Pierre’imi kurtardınız! Teşekkür ederim... her şey için teşekkür ederim! Tanrı sizi korusun, "+GetSexPhrase("Monsieur","Mademoiselle")+" Kaptan!";
			link.l1 = "Şimdi, şimdi, bu kadarı yeter. Pierre’in gerçekten ihtiyacı olan şey sıcak bir yemek ve doğru düzgün bir dinlenme.";
			link.l1.go = "Exit";
			CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
			AddDialogExitQuest("VPVL_PierTalkOnThePirs");
		break;
		
		//////   Контры   //////
		
		case "Kontr Le Maren":
			dialog.text = "Kahretsin! Sonunda ortaya çıktın, "+GetSexPhrase("sen pis köpek","sen zavallı kadın")+"! Şeytanın dibi, neredeydin sen? Üç gündür bu lanet sahilde kavrulup duruyoruz! Yükümüz nerede?!";
			link.l1 = "Eğlence benim olmadan başlayamıyor galiba, değil mi beyler? Eh, biraz gecikmiş olabilirim—ama hiç gelmemektense gelmek daha iyidir!";
			link.l1.go = "Exit_Sneak";
			link.l2 = "Bana mı hitap ediyorsun? Sorularını lağım faresine benzer bir şekilde sormadan önce biraz görgü öğren istersen!";
			link.l2.go = "Exit_Lucky";
			//locCameraFromToPos(-3.35, 2.23, 6.93, false, 20, -1, 10);
			locCameraFromToPos(-3.53, 2.35, 6.35, true, 1.93, -0.60, 11.17);
			DeleteAttribute(pchar, "questTemp.VPVL_Contr_V_Lemaren");
		break;
		
		case "Exit_Sneak":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			notification("Experience gained", SKILL_SNEAK);
		break;
		
		case "Exit_Lucky":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			notification("Experience gained", SKILL_FORTUNE);
		break;

		case "Kontr Le Maren0":
			sld = CharacterFromID("VPVL_contr_2");
			dialog.text = ""+sld.name+", sen şaşkın herif! Gözlerini aç, aptal—bu bizim adamımız değil!";
			link.l1 = "Ah... Yine valinin köpeklerinden biri! Kesin bilgi, tıpkı gelgit gibi! Çünkü "+GetSexPhrase("bu alçak","bu aptal kız")+" sürüklendi "+GetSexPhrase("kendisi","kendisi")+" burada, hadi çekelim "+GetSexPhrase("onu","onu")+" diğer fareyle mağaraya. Göreceğiz "+GetSexPhrase("onu","onu")+" sırları nasıl ortaya çıkarırız—yeterince hızlı olursa, efendilerinin kurduğu her pis planı bir bir anlatırlar!";
			link.l1.go = "Kontr Le Maren1";
			locCameraFromToPos(-3.53, 2.35, 6.35, false, -0.03, 0.40, 7.77);
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_1"));
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_2"));
			
			sld = CharacterFromID("VPVL_contr_1");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_2"));
		break;
		
		case "Kontr Le Maren1":
			sld = CharacterFromID("VPVL_contr_2");
			dialog.text = "Kafanda ne tür pis hayaller dönüyor, tuzlu suya bulanmış yaratık? Salyanı akıtmayı kes! En iyisi onu... sen de biliyorsun kime satalım. Böyle güzel bir kız için bir sandık altın verir, biz de haftalarca içip eğleniriz!";
			if (pchar.sex == "man")
			{
				dialog.text = "Bizim hücrede başka bir pisliği neden tutalım ki? Arkadaşına daha sert davran—güneş doğarken martı gibi ötecek. Şuna gelince, burada ve şimdi işini bitirelim, suratını daha fazla görmek zorunda kalmayalım!";
			}
			link.l1 = "Bin aç köpekbalığı bağırsaklarını kemirsin, "+sld.name+" ! Sen bütün takımadadaki en kurnaz kaçakçısın!";
			link.l1.go = "Kontr Le Maren2";
		break;

		case "Kontr Le Maren2":
			dialog.text = "...";
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) >= 20)
			{
				if(GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE) == "") {
					notification("No pistol equipped", "NONE");
					link.l2 = "Eğer o midye beyinliden daha zekisi yoksa, diğerlerinin kafasında ne tür saçmalıklar döndüğünü düşünmek bile istemem!";
					link.l2.go = "Kontr Le Maren3";
					CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
					locCameraFromToPos(-3.73, 2.45, 5.75, false, -0.53, -0.0, 9.17);
					sld = CharacterFromID("VPVL_contr_1");
					CharacterTurnByChr(sld, CharacterFromID("Blaze"));
					CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
				}
				else
				{
					link.l1 = "(Kendi kendime)(Tabancalar) Bu deniz fareleri boş laflarla oyalanırken, ben de açık gökyüzünden çakan bir şimşek gibi hızlı ve kesin vurma fırsatını buldum.";
					link.l1.go = "murder";
					notification("Check passed", SKILL_PISTOL);
					locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
				}
			}
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) < 20)
			{
				notification("Skill too low (20)", SKILL_PISTOL);
				CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
				sld = CharacterFromID("VPVL_contr_2");
				CharacterTurnByChr(sld, CharacterFromID("Blaze"));
				locCameraFromToPos(-3.73, 2.45, 5.75, false, -0.53, -0.0, 9.17);
				CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
			}
			link.l2 = "Eğer o midye beyinliden daha zekisi yoksa, kalanların kafasında ne tür saçmalıklar döndüğünü düşünmek bile istemem!";
			link.l2.go = "Kontr Le Maren3";
		break;
		
		case "Kontr Le Maren3":
			dialog.text = "O geveze dilini kafandan koparırım, seni arsız köpek"+GetSexPhrase("","—pislik orospunun teki")+", ve onu martılara yediririm, bir daha tek kelime edemezsin!";
			link.l1 = "Çekil aradan, olur mu? Hadi bakalım, şeytana meydan okumaya cesaretin varsa gel.";
			link.l1.go = "Kontr Le Maren Fight";
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
		break;
		
		case "Kontr Le Maren Fight":
			DialogExit();
			AddDialogExitQuest("VPVL_EveryoneFight");
			LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], false);
			EndQuestMovie();
		break;
		
		case "murder":
			DialogExit();
			AddDialogExitQuest("VPVL_Pistol_Murder");
			//locCameraFromToPos(-5.04, 2.62, 8.65, false, 20, -6, -15);
		break;
		
		/////////////   Пьер Карно   /////////////
		
		case "PierFirstTalk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"... Affedersiniz... Aklım dağılmış... Onların başlattığını bitirmeye mi geldiniz?";
			link.l1 = "Sen Pierre Carno musun?";
			link.l1.go = "Pier_1";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.VPVL_SetFlagLeMaren");
		break;

		case "Pier_1":
			dialog.text = "Ayou, bu benim. Adımı biliyor musun?";
			link.l1 = "Elbette. Yoksa burada ne işim olurdu?";
			link.l1.go = "Pier_2";
		break;

		case "Pier_2":
			dialog.text = "Beni affedin, hiçbir şey anlamıyorum... Acı ve açlık aklımı başımdan aldı... Neden geldiniz?";
			link.l1 = "Çok basit. Sen kaybolduğundan beri sadık eşin iskelede nöbet tutuyor, gözleri hep Karabatak’ın yelkenini arıyor. Onun kederi beni öyle derinden etkiledi ki, kayıtsızca geçip gidemedim—seni aramaya karar verdim.";
			link.l1.go = "Pier_3";
		break;

		case "Pier_3":
			dialog.text = "Karım... sevgili Léa'm... Onu bir daha asla göremeyeceğimden emindim...";
			link.l1 = "O fırsat geçti. Seni iskelede bekliyor, hâlâ umutla tutunuyor. Hadi buradan gidelim. Koluma gir.";
			link.l1.go = "Pier_4";
		break;

		case "Pier_4":
			dialog.text = "Merhamet... "+GetSexPhrase("Monsieur","Mademoiselle")+"... Biraz zamana ihtiyacım var... bacaklarım sanki kütük gibi... Gerçekten teşekkür ederim. Sen olmasaydın... sanki Yüce Allah seni bana gönderdi... Adını söylemedin. Kurtarıcımı nasıl hitap etmeliyim?";
			link.l1 = "Kaptan "+GetFullName(pchar)+" . Gücünü toplarken, bana buraya nasıl düştüğünü anlat. Bu... adamlarla iş mi yapıyordun?";
			link.l1.go = "Pier_5";
			LAi_Fade("VPVL_PierStay", "");
		break;

		case "Pier_5":
			dialog.text = "Yok kaptan, asla. Ben sadece mütevazı bir balıkçıyım. Gün çok güzel başlamıştı. Batı kıyısında balık tutuyordum—av harikaydı.\nBalıkları fıçıya doldurup ağlarımı tekrar atmak için sabırsızlanıyordum, ama akıntının kayığımı resife doğru sürüklediğini fark etmedim. Gövde yumurta kabuğu kadar inceydi—tek bir darbe denizin içeri girmesine yetti. Sabah avıyla dolu Karabatak hızla battı.";
			link.l1 = "Sonra karaya çıktın, ama kaçakçılar seni valinin casuslarından biri sandı, öyle mi?";
			link.l1.go = "Pier_6";
		break;

		case "Pier_6":
			dialog.text = "Kesinlikle. Lanetli dalgalarla boğuşarak zar zor kıyıya ulaştım. Sadece biraz kurulanıp dinlenmem gerekiyordu, sonra kasabaya gidecektim. O anda, o şeytanlar birden ortaya çıktı.\nBana bir bakıp casus olduğuma karar verdiler. Daha tek kelime edemeden beni bağlayıp buraya sürüklediler. İki gün boyunca aç bırakıp işkence ettiler, bilmediğim şeyleri itiraf etmemi istediler—ajanlar, planlar... ama hiçbir şey bilmiyordum!";
			link.l1 = "O grupta akıl pek yoktu—şimdi yengeçlere yem olmalarının sebebi de bu. Ama artık bunların hepsi geride kaldı. Artık özgürsün. Karına kavuşma vakti—eminim o da perişan halde seni bekliyordur.";
			link.l1.go = "Pier_7";
		break;

		case "Pier_7":
			dialog.text = "Tek istediğim onu tekrar kollarıma almak. Sanırım... Sanırım artık yürüyebilirim.";
			link.l1 = "O halde bir an daha kaybetmeyelim.";
			link.l1.go = "exit_grot";
		break;
		
		case "exit_grot":
			DialogExit();  
			AddQuestRecord("VPVL", "4");
			AddDialogExitQuest("VPVL_PierFollow");
		break;
		
		case "PierInThePirs":
			dialog.text = "Kaptan, yalvarırım—yarın akşam altı çan vurduğunda meyhaneye gelin. Size gerektiği gibi teşekkür etmezsem vicdanım asla rahat etmez. Şu anda... kalbimde olanları ifade edecek kelimeleri bulamıyorum. Lütfen, gelin. Bu benim için çok şey ifade ederdi.";
			link.l1 = "Pekâlâ, Pierre. Endişelenme—orada olacağım.";
			link.l1.go = "GoHome";
			locCameraFromToPos(-8.28, 3.1, 82.93, false, 40, -15, 0);
		break;

		case "GoHome":
			DialogExit();
			AddQuestRecord("VPVL", "5");
			AddDialogExitQuest("VPVL_KarnoGoHome");
		break;

		case "PierTalkTavern":
			dialog.text = "Kaptan! Geldiniz! Lütfen, bana katılın!";
			link.l1 = "Memnuniyetle!";
			link.l1.go = "PierTalkTavern1";
			LAi_Fade("VPVL_SitOnTheTable", "");
			FreeSitLocator("FortFrance_Tavern", "sit6");  // Just in case
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			pchar.questTemp.VPVL_DontSpawnSmugglersShipPier = true;
			DelLandQuestMark(npchar);
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
		break;

		case "PierTalkTavern1":
			dialog.text = "Şansınızın ve sağlığınızın daim olması için kadehlerimizi kaldıralım!";
			link.l1 = "Sadece benim için değil, Pierre—senin için de. O lanet mağarada seni bulduğum zamankinden çok daha iyi görünüyorsun şimdi. Şerefe!";
			link.l1.go = "PierTalkTavern2";
		break;

		case "PierTalkTavern2":
			dialog.text = "Kapitan, sonsuz minnettarlığımı nasıl ifade edeceğimi bilemiyorum! Beni görmezden gelmediniz, sırtınızı dönmediniz—tamamen yabancı, sıradan bir balıkçıya yardım ettiniz. Böyle bir asalet, layıkıyla ödüllendirilmeli; elimde ne varsa size vermek istiyorum.\nBuyurun—yirmi parça altın sarısı kehribar ve beş nadir mavi taş; batık bir gemiden çıkardım. Artık sizinler.\nAyrıca, seyir aletlerimi ve oltalarımı da size vermek isterim. Artık gemim yok, bana bir faydaları kalmadı.";
			link.l1 = "Teşekkür ederim, Pierre. Bunlar kesinlikle işe yarayacak. Ama en önemlisi, artık evindesin—ve eşin de artık korku içinde yaşamak zorunda değil. İkiniz için de her şey düzelecek.";
			link.l1.go = "PierTakeGift";
			link.l2 = "Pierre, jestini takdir ediyorum ama onları kendine saklamalısın. Tekneni onarmak, olta, ağ, varil almak için her kuruşa ihtiyacın olacak... Teşekkürün ve seni eşinle yeniden bir arada görmek benim için yeterli bir ödül. Birbirinize iyi bakın.";
			link.l2.go = "PierWontGift1";
		break;
		
		case "PierTakeGift":
			dialog.text = "Bütün bunların gerçekten yaşandığına hâlâ inanamıyorum... Ailemin hayatında yeni bir sayfa açılmasına ve senin asil yüreğine içelim, Kaptan!";
			link.l1 = "Ve iyi şanslar Pierre. Hepimizin birazına ihtiyacı var!";
			link.l1.go = "ZastavkaVPVL";
			AddItems(PChar, "jewelry8", 20);
			AddItems(PChar, "jewelry7", 5);
			AddItems(PChar, "A_map_martiniqua", 1);
			AddItems(PChar, "spyglass3", 1);
			AddItems(PChar, "obereg_7", 1);
		break;

		case "PierWontGift1":
			dialog.text = "Kapitan, bu işin böyle kalmasına izin veremem... Hayatımı kurtardınız, size her şeyimi borçluyum. Kehribar ve diğer hediyeleri kabul etmediğiniz için, en azından tayfanıza sığ sularda balık tutmayı öğreteyim. Böylece karınları doyar, erzak masraflarınız da azalır. Ne dersiniz?";
			link.l1 = "Bu harika bir fikir! Eski bir söz vardır—birine ağ atmayı öğretirsen, bir daha asla aç kalmaz.";
			link.l1.go = "PierWontGift2";
			pchar.questTemp.VPVL_Food = true;
		break;

		case "PierWontGift2":
			dialog.text = "Ağzınızdan bal damlıyor, Kaptan! Yardımcı olabildiğime sevindim. Şimdi—bir bardak daha paylaşalım mı?";
			link.l1 = "Sağlığına ve refahına, Pierre!";
			link.l1.go = "ZastavkaVPVL";
		break;
		
		case "ZastavkaVPVL":
			DialogExit();
			SetLaunchFrameFormParam("Four hours have passed...", "VPVL_SitOnTheTable", 2, 2);
			LaunchFrameForm();
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
			sld = CharacterFromID("VPVL_Pier_carno");
			sld.dialog.currentnode = "PierTalkTavern3";
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, sld, "", -1, 0);
		break;
		
		case "PierTalkTavern3":
			if(CheckAttribute(pchar, "questTemp.VPVL_Food"))
			{
			int foodDays = CalculateShipFood(&pchar);
			dialog.text = "Neptün'ün sakalı adına! Bu içki ne kadar da sertmiş! Bir yudum daha alırsam... hık... krakeni uyandıracak bir şarkı patlatırım! Buradan limana kadar herkes sesimi duyar!";
			link.l1 = "Şarkını daha sakin sulara sakla, Pierre. Sesini... hık... bir sonraki limanımıza sakla. Eğer şimdi bağırmaya başlarsan, yakında ben de koroya katılırım. Ve benim... şey... ilgilenmem gereken acil işlerim var. Gelgit kimseyi beklemez... hık... hele kafası güzel olanları hiç! Kendine iyi bak... hık... o iyi kadına da selam söyle!";
			link.l1.go = "PierTalkTavern4";
			WaitDate("", 0, 0, 0, 4, 10);
			LAi_AlcoholSetDrunk(pchar, 71, 5600);
			notification("Ship's provisions consumption reduced by 15%", "None");
			}
			else
			{
			dialog.text = "Neptün'ün sakalı adına! Bu ne kuvvetli içkiymiş! Bir yudum daha alırsam... hık... öyle bir şarkı patlatırım ki krakeni bile uyandırır! Buradan limana kadar herkes benim sesimi duyar!";
			link.l1 = "Şu şarkını sakin sulara sakla, Pierre. Sesini... hık... bir sonraki limanımıza bırak. Eğer şimdi bağırıp çağırmaya başlarsan, yakında ben de sana katılırım. Ve benim... şey... ilgilenmem gereken acil işlerim var. Gelgit kimseyi beklemez... hık... kadehi elinde olanları bile! Kendine iyi bak... hık... ve o iyi kadınına da!";
			link.l1.go = "PierTalkTavern4";
			WaitDate("", 0, 0, 0, 4, 10);
			LAi_AlcoholSetDrunk(pchar, 71, 5600);
			}
		break;

		case "PierTalkTavern4":
			dialog.text = "Ah, Kaptan... sen gerçekten... hık... gerçek bir denizcinin yüreğine sahipsin! Sana olan borcumu asla ödeyemem, anlıyor musun? Eğer bir gün demirini limanımıza atarsan... ocağımız... ocağımız senin olur, sanki aynı... aynı anneden doğmuşuz gibi! Ruhum ve şerefim üzerine yemin ederim! Fortuna seni bu kıyılara geri getirdiğinde yine birlikte kadeh kaldıracağız!";
			link.l1 = "Dümeni sabit tut, Pierre! En iyisi... hık... demir alayım, yoksa denizci bacaklarım jöleye döner ve kendimi bu meyhanenin zemininde sürüklenirken bulurum! Rüzgarın hep arkanda olsun!";
			npchar.dialog.currentnode = "RepeatTavern";
			link.l1.go = "Exit2";
		break;

		case "Exit2":
			DialogExit();
			LAi_Fade("VPVL_ExitFromTableVPVL", "VPVL_PierLivingTavern");
			DeleteAttribute(pchar, "questTemp.VPVL_Delete_Ship_RemoveFlag");
		break;

		case "RepeatTavern":
			dialog.text = "De-niz-le-rin derin mavisiii, ticaret rüzgarları essin... hık... balık avına ilk ışıkta açılıyoruz!.. Kahrolası rom kafamı bulandırdı! Dizeler aklımdan uçup gidiyor! Kaptan!.. Hâlâ burada demirli misin? Meyhaneci! Getir bakalım... hık... mahzenindeki en iyi Batı Hint romunu!";
			link.l1 = "Ben gidiyorum, Pierre! Hık... hâlâ gemime geri dönecek kadar ayıktayken, sığlıklarda karaya oturmadan bu tehlikeli yolu aşabilirim!";
			link.l1.go = "Exit";
		break;

		case "MeetingInTneCity":
			dialog.text = ""+pchar.name+" !   Tuzla kaplanmış gözlerime bir ziyafet! Karayipler'in en iyi içkisinden bir kadehe ne dersin? Hayatın engin okyanusunda yollarımızın kesişmesini kutlamak için!";
			link.l1 = "Senin yıpranmış yüzünü görmek de kalbimi neşeyle dolduruyor, Pierre. Ne yazık ki, bugün görevim ayık kalmamı gerektiriyor. Rotamı, berrak bir zihin ve sağlam bir el isteyen tehlikeli sulardan geçirdim. Belki yıldızlarımız bir sonraki sefere yeniden kesiştiğinde?";
			link.l1.go = "MeetingInTneCity1";
		break;

		case "MeetingInTneCity1":
			dialog.text = "Ayou, ayou, Kaptan! Bir gemi limana yanaşmadan önce mutlaka denize açılmalı. Tüccarların dediği gibi, önce hesap kitap, sonra keyif. Ama Şans çarkını tekrar bize çevirdiğinde, eski Karasakal’ı bile gururlandıracak bir kadeh kaldıracağız!";
			link.l1 = "Bunu geminin günlüğüne yaz, Pierre. Ta ki gelgitler bizi tekrar bir araya getirene kadar!";
			link.l1.go = "Exit";
			npchar.dialog.currentnode = "ExitRepeat";
		break;

		case "ExitRepeat":
			dialog.text = "Kaptan! Geminiz, yükümlülükler fırtınasından güvenli bir liman bulabildi mi?";
			link.l1 = "Ticaretin akıntısı hâlâ demirimi çekiyor, Pierre. Görevlerim beni bir süre daha dümenin başında tutacak.";
			link.l1.go = "Exit";
		break;
	}
}   