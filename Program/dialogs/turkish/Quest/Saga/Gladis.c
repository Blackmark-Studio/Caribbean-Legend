// Глэдис МакАртур - приемная мать Элен
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if(pchar.questTemp.Saga == "helena1")
			{
				dialog.text = "Ah, Kaptan! Biliyor musun, Helen'e her şeyi anlattım. Üzerimden nasıl bir yük kalktı, tahmin bile edemezsin!";
				link.l1 = "Her şeyi doğru yaptınız, Bayan McArthur. Kız gerçeği bilmeli. Ve ben de onun için buradayım.";
				link.l1.go = "Helena_hire";
			}
			else
			{
				dialog.text = "Selamlar, "+pchar.name+"! Seni gördüğüme sevindim! Biraz rom ister misin?";
				link.l1 = "Teşekkür ederim, Bayan McArthur, ama şu anda çok meşgulüm.";
				link.l1.go = "exit";			
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "FindHelena":
			dialog.text = "Ne istiyorsunuz, efendim?";
			link.l1 = "Sen Gladys McArthur mısın?";
			link.l1.go = "FindHelena_1";
		break;
		
		case "FindHelena_1":
			dialog.text = "Benim. Seni hatırlamıyorum, delikanlı. O halde, benden ne istediğini açıklar mısın?";
			link.l1 = "Kızınızın kayboluşunun hikayesiyle ilgileniyorum Bayan McArthur. Onun kaybolduğunu düşünmenize ne sebep oldu? Helen’in çok yetenekli bir mürettebatı olduğunu duydum...";
			link.l1.go = "FindHelena_2";
		break;
		
		case "FindHelena_2":
			dialog.text = "Ah, I am absolutely certain! Look, my late husband's death anniversary was five days ago. Helen loved her father and she would never miss this date. She had only left for a few days to receive a shipment of redwood from the friendly Miskito people.\nThe Indians respect and fear our patron Jan Svenson; they would never harm her. Señor Svenson has already spoken to them. The wood was loaded on the same day. No one has seen Helen since.";
			link.l1 = "Belki korsanlar ona saldırmıştır?";
			link.l1.go = "FindHelena_3";
		break;
		
		case "FindHelena_3":
			dialog.text = "Saçmalık! Bay Svenson'un beş korsan baronundan biri ve Kıyı Kardeşliği Konseyi'nin bir üyesi olduğunu zaten biliyor olmalısınız. Onun izni olmadan burada hiçbir korsana avlanmak yasaktır. Yine de yeni biri olabilir...";
			link.l1 = "Peki ya İspanyollar? Bir İspanyol devriyesine rastlamış olabilir mi?";
			link.l1.go = "FindHelena_4";
		break;
		
		case "FindHelena_4":
			dialog.text = "Siyasetten pek anlamam, ama burada altın ve gümüş madenlerinin tamamen tükendiğini, soylu hidalgoların hayatlarını tehlikeye atacak pek bir hazine kalmadığını söylüyorlar. O yüzden buralarda pek görünmezler. Ayrıca, yerliler de onlara pek sıcak bakmıyor.\nHelen için rastgele bir İspanyol devriyesiyle karşılaşmak kötü sonuçlanamazdı, onların gözünde yasa dışı hiçbir şey yapmamıştı. 'Rainbow' Hollanda bayrağı çekmişti ve Helen’in tüm evrakları, ticaret ruhsatı da dahil, eksiksizdi.";
			link.l1 = "Son yolculuğundan önce olağan dışı bir şey oldu mu? Belki gözünüzden kaçan tuhaf bir olay?";
			link.l1.go = "FindHelena_5";
		break;
		
		case "FindHelena_5":
			dialog.text = "Ah, hayır! Tanrıya şükür, burada huzurlu bir hayat sürüyoruz. Yine de, birkaç hafta önce Helen başka bir istenmeyen hayranından buluşma için yalvaran bir mektup aldı. Güzel bir kız, ama zengin değil.\nBu yüzden çok sayıda hayranı var, ama hiçbirini beğenmiyor ve evlenmek istemiyor. Bu şekilde zaten birçok kişiyi kandırdı. Çok hafifmeşrep, tıpkı annesi gibi!";
			link.l1 = "Sen o tür bir kadın gibi görünmüyorsun, Bayan McArthur...";
			link.l1.go = "FindHelena_6";
		break;
		
		case "FindHelena_6":
			dialog.text = "Ne? Ah, neyse, kalbim kırık. Ne diyordum? Ha, evet, mektup. Her neyse, o mektubu Jimmy Higgins yazdı. Jackman'ın adamlarından biri ve Maroon Town'da yaşıyor. Kasabamıza sık sık gelir. Jackman da bir korsan baronu ama Bay Svenson ondan pek hoşlanmaz, nedenini bilmiyorum.";
			link.l1 = "Ya Helen?";
			link.l1.go = "FindHelena_7";
		break;
		
		case "FindHelena_7":
			dialog.text = "Ah, yüksek sesle gülüyordu. Bir gün önce İngiliz bir korvet kaptanından evlenme teklifi almış ve onu bile reddetmişti. Şimdi ise bir korsan teknesinin sıradan bir lostromosu... Hiç şansı yok, Sean McArthur'un kızı daha görkemli bir koca ister!";
			link.l1 = "O İngiliz kaptanın adı neydi?";
			link.l1.go = "FindHelena_8";
		break;
		
		case "FindHelena_8":
			dialog.text = "Ah, ben nereden bileyim? Gerçek centilmenler burada nadiren uğrar. Kusura bakmayın, sizi kırmak istemedim. Şu Higgins'e sorun. O kesin adını hatırlıyordur. Jimmy, Helen yüzünden o kaptanla düello etmeye kalkmıştı. Arkadaşları zorla vazgeçirdi. Ama ikisi de, Helen denize açılmadan birkaç gün önce Blueweld'den ayrıldılar.";
			link.l1 = "Pekala, hikayeniz için teşekkür ederim. Sevdiğinizi bulmaya çalışacağım. Bir şey öğrenirsem size ya da Bay Svenson'a haber vereceğim. Umarım kızınızı sağ ve sapasağlam bulurum.";
			link.l1.go = "FindHelena_9";
		break;
		
		case "FindHelena_9":
			dialog.text = "Onu aramaya mı gidiyorsunuz? Tanrı yardımcınız olsun, yolunuzu aydınlatsın ve elinizi güçlendirsin! Sizin için dua edeceğim! İsminizi söyler misiniz, saygıdeğer beyefendi?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+". Yakında iyi haberlerle döneceğimi umuyorum, Bayan McArthur. Hoşça kalın!";
			link.l1.go = "FindHelena_10";
		break;
		
		case "FindHelena_10":
			DialogExit();
			NextDiag.CurrentNode = "FindHelena_wait";
			AddQuestRecord("Saga", "1");
			pchar.questTemp.Saga = "maruntown";//идем к Джекману
			SetFunctionTimerCondition("Gladis_SetHome", 0, 0, 1, false);
			int iTime = 25-MOD_SKILL_ENEMY_RATE;
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime*2, false);
			}
			else SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime, false);
		break;
		
		case "FindHelena_wait":
			dialog.text = "Kızım hakkında yeni bir bilgin var mı, "+pchar.name+"?";
			link.l1 = "Üzgünüm, Bayan McArthur, size henüz yeni bir haberim yok, ama umudunuzu kaybetmeyin. Aramaya devam edeceğim. Kötü bir haberin olmaması da başlı başına iyi bir haber.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FindHelena_wait";
		break;
		
		case "Helena_die":
			dialog.text = "Çok geç kaldınız, Kaptan. Zavallı kızımın cesedi Antigua kıyılarında bulundu. Tanrım, ölümünden önce ona ne işkenceler etmişler! Güzel kızımı koruyamadım...";
			link.l1 = "Üzgünüm. Yapabileceğim hiçbir şey yoktu...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_exit":
			dialog.text = "Ah, delikanlı, lütfen, acımla baş başa kalmama izin ver...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_regard":
			dialog.text = "Kaptan, kızımı kurtardığınız için size nasıl teşekkür edeceğimi bile bilmiyorum. Bana her şeyi anlattı ve cesaretinizle onurunuza hayran kaldım. Alın, bu altın doblonları kabul edin. Çok fazla değil, ama hepsini içtenlikle sunuyorum. Sakın reddetmeyi düşünmeyin!";
			link.l1 = "Pekala, Gladys, yapmayacağım. Ama kızını parayla kurtarmadım, umarım bunu biliyorsun.";
			link.l1.go = "Gladis_regard_1";
			link.l2 = "Bu parayı kendine sakla, Gladys. Buna benden çok senin ihtiyacın var.";
			link.l2.go = "Gladis_regard_2";
			sld = characterFromId("Helena");
			LAi_SetStayType(sld);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			// открыть город
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);
		break;
		
		case "Gladis_regard_1":
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Sana olan borcumu bir şekilde ödeyebildiğim için mutluyum. Evimin kapıları sana her zaman açık. Helen ve ben seni her zaman görmekten memnuniyet duyarız.";
			link.l1 = "Teşekkür ederim, Bayan McArthur. Fırsat bulduğumda sizi ve Helen'i ziyaret edeceğim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_regard_2":
			dialog.text = "Ah, lütfen... Sadece onurlu davranışınız için size karşılık vermek istedim. Bilin ki evimin kapıları size her zaman açık. Helen ve ben sizi her zaman görmekten memnuniyet duyarız.";
			link.l1 = "Teşekkür ederim, Bayan McArthur. Fırsat bulduğumda sizi ve Helen'i ziyaret edeceğim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
			pchar.questTemp.Saga.Helena_friend = "true";//атрибут поведения Элен в будущем
		break;
		
		case "Gladis_wait":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys")) {
				dialog.text = "Kaptan, evimizde her zaman hoş geldiniz! Helen için mi geldiniz? Ne yazık ki kendini odasına kapattı - son birkaç günün ardından çok yorulmuş olmalı. Merak etmeyin, bazen böyle olur.";
				link.l1 = "Gerçekten mi? Emin misin, iyi olduğundan?";
				link.l1.go = "after_drinking";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys");
				break;
			}
		
			dialog.text = "Ah, Monsieur de Maure! Kızımın kurtarıcısını evimde görmek her zaman beni mutlu ediyor. Helen'le mi görüşmek istiyorsunuz? O, yukarıda odasında. 'Rainbow'u kaybettikten ve o inanılmaz kurtarılışından sonra, dışarı çıkmaktan kaçınıyor. Onu ilk kez böyle bir şaşkınlık içinde görüyorum...";
			link.l1 = "Teşekkür ederim, Bayan McArthur.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_history":
			dialog.text = "Ah, Monsieur de Maure! Kızımın hayatını kurtaran adamı evimde görmek her zaman beni mutlu eder. Helen'i görmek mi istiyorsunuz?";
			link.l1 = "Hayır. Sana birkaç soru sormak istiyorum ve dürüstlüğüne gerçekten ihtiyacım var. Helen'in güvenliği buna bağlı. Bu yüzük sana tanıdık geliyor mu?";
			link.l1.go = "Gladis_history_1";
		break;
		
		case "Gladis_history_1":
			RemoveItems(pchar, "bucher_ring", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Aman Tanrım! Bu... babasının yüzüğü!";
			link.l1 = "Bay McArthur'ın mı?";
			link.l1.go = "Gladis_history_2";
		break;
		
		case "Gladis_history_2":
			dialog.text = "Hayır. Helen üvey kızımız, ama bunun farkında değil. Anne babası öldü, ben de onu kendi çocuğum gibi yanıma aldım. Sean da onu evlat edindi, ama o bile Helen’in benim öz kızım olmadığını bilmiyordu.";
			link.l1 = "Peki, onun gerçek anne babası kim?";
			link.l1.go = "Gladis_history_3";
		break;
		
		case "Gladis_history_3":
			dialog.text = "Babası 'Neptune' firkateyninde 'Kasap' lakaplı bir korsanmış, bunu biliyorum. Onu sadece iki kez gördüm. Annesi ise genç, güzel, kızıl saçlı bir kadındı, erkek kıyafetleri giyerdi. Onun hakkında anlatabileceğim neredeyse her şey bu, bir de kötü bir anneydi.\nBen asla öyle bir bebeği yabancıların eline bırakmazdım. İkisi de trajik şekilde öldü. Ve vaat edilen kurye yirmi yıl sonra ortaya çıktı, meğerse o da sensin. Seni Butcher mı gönderdi? O hayatta mı?";
			link.l1 = "Sakin olun, Bayan Gladys! Kasabın geri döndüğünden şüphelenmek için bir sebep yok, gerçi bu fikre kapılan ikinci kişisiniz. Kısa süre önce size bu yüzüğü göstermesi gereken bir adamla karşılaştım...";
			link.l1.go = "Gladis_history_4";
		break;
		
		case "Gladis_history_4":
			dialog.text = "...";
			link.l1 = "Basit bir olay onun zamanında bunu yapmasını engelledi ve kaptanının son emrini yerine getirememenin acısını hayatı boyunca çekti. Kısa süre önce öldü ve... neyse, yeter bu kadar hüzün. Söylesene Gladys, Helen’in annesi çocuğuna hatıra olarak bir şey bırakmış mı? Belki küçük bir eşya, bir hatıra?";
			link.l1.go = "Gladis_history_5";
		break;
		
		case "Gladis_history_5":
			dialog.text = "Bana eski bir haritanın garip bir parçasını bıraktı. Şaka yollu, bunun onun mirası olduğunu söyledi. O kâğıt parçası ne işe yarayabilir ki? Bence bundan fazlası olmayan kötü bir şakaydı. Fazlasıyla heyecanlıydı ve biraz da aklı başında değildi. Ama bu 'hediyeyi' sakladım.\nKim bilir... İstersen, bir gün bana her şeyi anlatacağına söz verirsen sana verebilirim.";
			link.l1 = "Elbette, Bayan McArthur. Bu kağıt parçasını bir süreliğine yanıma alacağım. Bay Svenson'la konuşmam gerek.";
			link.l1.go = "Gladis_history_6";
		break;
		
		case "Gladis_history_6":
			GiveItem2Character(pchar, "map_half_beatriss"); //половинка карты
			PlaySound("interface\important_item.wav");
			dialog.text = "Bize yine yardım ettiniz, Monsieur de Maure! Size nasıl teşekkür edeceğimi bilemiyorum. Lütfen, en azından eşimin tabancasını alın. O her zaman onunla gurur duyardı ve çok nadir olduğunu söylerdi. Uzun zamandır burada öylece duruyor. Size hizmet etsin! Lütfen alın, alın!";
			link.l1 = "Teşekkür ederim, Gladys. Bu tabanca gerçekten harika. Sağ ol, hoşça kal.";
			link.l1.go = "Gladis_history_7";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l2 = "Bu tabanca Helen'e hizmet etsin. Benim zaten yeterince silahım var.";
				link.l2.go = "Gladis_history_8_1";
			}
		break;
		
		case "Gladis_history_7":
			DialogExit();
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol5");
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			AddQuestRecord("Saga", "22");
			AddCharacterExpToSkill(pchar, "Leadership", 50);
		break;
		
		case "Gladis_history_8_1":
			dialog.text = "Ama neden hediyelerimi almaktan hep kaçınıyorsun? Beni üzüyorsun...";
			link.l1 = "Şimdi seni mutlu edebileceğime inanıyorum. Kaptan Butcher'ın kızını güvende tutman için sana teslim edilmesi gereken altını geri vereceğim. Elbette bu doblonlar, tüm sevgini ve sadakatini karşılamaz, ama onlar senin hakkın. Onlarla ne istersen yapabilirsin.";
			link.l1.go = "Gladis_history_8";
		break;
		
		case "Gladis_history_8":
			dialog.text = "Ah, Kaptan! Ne diyeceğimi bilemiyorum... Böyle... onurlu insanların var olabileceğini hayal bile edemezdim! Kızıma git ve ona bu güzel haberi ver!";
			link.l1 = "Yoldayım, Bayan McArthur.";
			link.l1.go = "Gladis_history_9";
		break;
		
		case "Gladis_history_9":
			DialogExit();
			RemoveItems(pchar, "chest", 1);
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Saga", "22");
			sld = characterFromId("Helena");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterbyItem(sld, "pistol5");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
		break;
		
		case "Helena_hire":
			dialog.text = "Ciddi misin? Ne demek istiyorsun?";
			link.l1 = "Bay Svenson'un isteği üzerine, Helen'i gemimde subay olarak görevlendireceğim. Büyük bir tehlike içinde. Jan ile ben bu meseleyle ilgilenirken, Helen'in sağlam bir korumaya ihtiyacı olacak. Umarım bu korumayı sağlayabilirim.";
			link.l1.go = "Helena_hire_1";
		break;
		
		case "Helena_hire_1":
			dialog.text = "Ah, bu harika! Bunu senden istemeye cesaret edemezdim. Kızım için en iyi koruma bu olacak. Helen tekrar denize açılacağı için çok sevinecek!";
			link.l1 = "İltifatınız için teşekkür ederim, Bayan McArthur. Ve şimdi... üvey kızınızı görmem gerek.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "Helena_hire";
			pchar.questTemp.Saga = "helena2";
		break;
		
		case "saw_sex":
			dialog.text = "Aman Tanrım! Küçük kızım!";
			link.l1 = "Gladys, kapıyı çalmayı bilmiyor musun?!";
			link.l1.go = "saw_sex_1";
		break;
		
		case "saw_sex_1":
			dialog.text = "Ah, affedersiniz gençler! Ben gidiyorum! Helen, sana söylediklerimi unutma!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysTalk");
		break;
		
		case "after_drinking":
			dialog.text = "Bence bu sefer kendini fazla yordu. Her şeyi anlattı bana, Kaptan! Dün ona yeni bir gemi seçmesinde yardımcı olduğunuz için teşekkür ederim!";
			link.l1 = "Ha? Hm, rica ederim. Hoşça kalın, Bayan MacArthur.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
