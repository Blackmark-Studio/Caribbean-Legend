void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
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
		
		case "dwh_gypsy_0":
			dialog.text = "...";
			link.l1 = "Dinle, kara kaşlı, insanların hastalıklarını, hatta ağır hastalıkları bile iyileştirdiğini duydum. Doğru mu bu?";
			link.l1.go = "dwh_gypsy_1";
			DelLandQuestMark(npchar);
		break;
		
		case "dwh_gypsy_1":
			dialog.text = "Doğru, "+GetSexPhrase("sevgilim","güzellik")+"Her hastalığın üstesinden gelmek için kendi yöntemlerim var. Sıradan insanlara, tüccarlara, hatta zenginlere bile yeniden ayağa kalkmalarında yardımcı oldum. Hatta vali bile, kimse fayda edemediğinde benim iksirlerime başvurdu. Hastalık altından korkmaz, ama benim ilaçlarıma karşı koyamaz.";
			link.l1 = "O halde neden ağır hasta olan Thomas Morrison'ın kızını tedavi etmeyi reddediyorsun?";
			link.l1.go = "dwh_gypsy_2";
			pchar.questTemp.DWH_gipsy = true;
		break;
		
		case "dwh_gypsy_2":
			dialog.text = "Bunu sana kim saçmaladı, "+GetSexPhrase("falconet","dovey")+"? Yardım etmeyi reddetmedim ki. Beni evden kovan onun babasıydı. Kızını tedavi edeceğim konusunda anlaşmıştık, ama birden fikrini değiştirdi. Beni yeminli bir düşman gibi kapı dışarı etti.";
			link.l1 = "Yani, kızını kendi elleriyle acı çekmeye mi mahkûm etti?";
			link.l1.go = "dwh_gypsy_2_1";
		break;
		
		case "dwh_gypsy_2_1":
			dialog.text = "Hayır, hayır, o çok ilgili bir baba. Neden böyle davrandığını anlamak zor.";
			link.l1 = "Onunla tekrar konuşmayı denedin mi?";
			link.l1.go = "dwh_gypsy_3";
		break;
		
		case "dwh_gypsy_3":
			dialog.text = "Evin yanına bile yaklaşmama izin vermiyor. Dinle, "+GetSexPhrase("sevgilim","güzellik")+" , madem yoksul bir kızın kaderiyle ilgileniyorsun, belki neler olup bittiğini öğrenmeye çalışabilirsin? Thomas'la konuş, çocuğu acıdan kurtarmama yardım et.";
			link.l1 = "Elbette yardım edeceğim. Thomas'ı nerede bulabilirim?";
			link.l1.go = "dwh_gypsy_4";
			link.l2 = "Hayır, kara kaşlı. Her ne olursa olsun, eminim babasının senin yardımını reddetmek için kendi sebepleri vardır. Ben karışmam. Karar onun—kız onun kızı.";
			link.l2.go = "dwh_gypsy_otkaz";
		break;
		
		case "dwh_gypsy_otkaz":
			DialogExit();
			CloseQuestHeader("DWH");
		break;
		
		case "dwh_gypsy_4":
			dialog.text = "Eviniz surun yanında, kasabanın kuzey kısmında, sütunlu büyük bir malikanenin hemen yanında. Hadi, "+GetSexPhrase("falconet","dovey")+", onunla konuş ve bana geri dön.";
			link.l1 = "Yakında döneceğim.";
			link.l1.go = "dwh_gypsy_5";
		break;
		
		case "dwh_gypsy_5":
			DialogExit();
			AddDialogExitQuestFunction("DWH_gypsy_5");
		break;

		case "dwh_gypsy_repeat":
			dialog.text = "Pekala, "+GetSexPhrase("sevgilim","tatlım")+", Thomas ile konuştun mu?";
			link.l1 = "Henüz değil.";
			link.l1.go = "dwh_exit";
		break;

		case "dwh_exit":
			DialogExit();
			NextDiag.TempNode = "dwh_gypsy_repeat";
		break;
		
		case "Tomas":
			dialog.text = ""+TimeGreeting()+"! Ne işiniz var evimde?";
			link.l1 = "Benim adım Kaptan "+GetFullName(pchar)+". Çingene kadının isteği üzerine buradayım. Neden yardımını reddettiğini öğrenmek istiyor. Kızını iyileştirmek için, ne kadar küçük olursa olsun, herhangi bir şansı gerçekten geri çevirecek durumda mısın?";
			link.l1.go = "Tomas_1";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_1":
			dialog.text = "Ah, Kaptan... Lütfen anlayın, reddetmek zorunda kaldım ama bu benim isteğimle olmadı. İnanın bana, Esther'in iyileşmesi için her şeyimi verirdim.";
			link.l1 = "Sana bu kadar çok ihtiyaç duyduğun yardımı reddettiren ne olabilir?";
			link.l1.go = "Tomas_2";
		break;

		case "Tomas_2":
			dialog.text = "Bakın, ailemiz her zaman dindar olmuştur. Eşim Olivia'nın ölümünden sonra, sadece inancımla ayakta kaldım. Çingene yardım teklif edince kabul ettim – kızımı kurtarmak için her şeyi yapardım. Ama... rahibimiz bunu öğrendi.";
			link.l1 = "Dur tahmin edeyim: böyle hizmetlere karşı mı?";
			link.l1.go = "Tomas_3";
		break;

		case "Tomas_3":
			dialog.text = "Aynen öyle. Beni, kızımı ancak dua ve Tanrı'nın iradesinin iyileştirebileceğine inandırdı. Ve eğer bu yoldan sapar, bir 'cadı'nın yardımına başvurursam, beni kiliseden aforoz etmekle tehdit etti. Anlıyor musunuz? Aforoz!";
			link.l1 = "Yani Esther’in sağlığı tamamen rahibin sözüne mi bağlı?";
			link.l1.go = "Tomas_4";
		break;

		case "Tomas_4":
			dialog.text = "Kızım ve ben kilisenin yanında yaşıyoruz. İnanç bizim için her şey demek. Eğer çingene başarısız olursa, sadece kızımı değil, bu dünyadaki yerimden geriye kalan her şeyi de kaybedeceğim. İnsanlar bizden yüz çevirecek, kilise bizi reddedecek. Esther ve ben tamamen yalnız kalacağız.";
			link.l1 = "Ve eğer rahip izin verirse? O zaman çingenenin denemesine izin verir miydin?";
			link.l1.go = "Tomas_5";
		break;

		case "Tomas_5":
			dialog.text = "Evet. Eğer kilise onun yaptıklarını kutsadıysa... O zaman ona güvenirim. Yardımcı olabilecek her şeyi denemeye hazırım.";
			link.l1 = "Anladım. Peki Thomas, sana yardım edeceğim. Papazınla konuşacağım. Belki onu ikna edebilirim.";
			link.l1.go = "Tomas_6";
		break;

		case "Tomas_6":
			dialog.text = "Sen... gerçekten bize yardım etmeye istekli misin? Kaptan, başarın için dua edeceğim. Ama unutma... rahibimiz inatçı ve prensip sahibidir, onu ikna etmek kolay olmayacak.";
			link.l1 = "İkna edici argümanlarla prensipler aşılabilir. Beni bekle, yakında döneceğim.";
			link.l1.go = "Tomas_7";
		break;

		case "Tomas_7":
			DialogExit();
			AddDialogExitQuestFunction("DWH_Tomas_7");
		break;
		
		case "Tomas_11":
			dialog.text = "...";
			link.l1 = "Thomas, rahibi ikna etmeyi başardım.";
			link.l1.go = "Tomas_12";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_12":
			dialog.text = "Gerçekten mi? İnanılmaz! O halde çingeneyi bir an önce davet edelim.";
			link.l1 = "Elbette yapacağız, ama küçük bir detay var. Rahip, bunun inancınızı sarsmayacağını umuyor ve içten bir pişmanlık ile iyi işler bekliyor. Mesela, cemaat için yeni bir çan almak böyle bir iyilik olabilir.";
			link.l1.go = "Tomas_13";
		break;

		case "Tomas_13":
			dialog.text = "Oh, Kaptan... Bir çan iyi bir paraya mal oluyor. Merhum eşimin takılarından bir şeyle vedalaşmam gerekebilir. Ama Esther için, sahip olduğum her şeyi—ve daha fazlasını—vermeye hazırım. Elbette, Tanrı’dan af dileyeceğim. Demirciye gidip siparişi vereceğim ve çingeneyi bulacağım.\nLütfen rahibe söyleyin, çan yakında hazır olacak. Gerekirse yerin dibinden bile çıkarıp getireceğim.";
			link.l1 = "Pekala, Thomas.";
			link.l1.go = "Tomas_14";
		break;
		
		case "Tomas_14":
			DialogExit();
			AddDialogExitQuestFunction("DWH_Tomas_14");
		break;
		
		case "Tomas_15":
			dialog.text = "...";
			link.l1 = "Senin söylediklerini rahibe anlattım. Artık önünde durmayacak, başlayabilirsin.";
			link.l1.go = "Tomas_16";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_16":
			dialog.text = "Teşekkür ederim Kaptan, ilginiz için! Lütfen bu elli dublonu kabul edin. Sizin için yapabileceğim en azı bu, ve şu anda elimde olan tek şey...";
			link.l1 = "Saçmalık! Sana para için yardım etmedim. Yani, her şey hazır mı... hmm... tedavi için?";
			link.l1.go = "Tomas_16_1";
			link.l2 = "Peki, madem ısrar ediyorsunuz... Başka yapabileceğim bir şey var mı?";
			link.l2.go = "Tomas_16_2";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
		break;

		case "Tomas_16_1":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.questTemp.DWH_GoodChoice = true;
		break;
		
		case "Tomas_16_2":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			AddItems(pchar, "gold_dublon", 50);
		break;
		
		case "gypsy_1":
			dialog.text = "Kızın sağlığını geri kazandıracak ilacı hazırlamak için mangarosa'ya ihtiyacım var - insan elinin nadiren değdiği yerlerde yetişen nadir bir bitki. Kasabanın dışında bir mağara biliyorum, oraya sık sık... serseriler uğrar. Mangarosayı içmek için yakıyorlar, gücünden habersizler. Bana yardım et, "+GetSexPhrase("falconet","dovey")+", bana biraz mangarosa getir, onsuz hiçbir şey işe yaramaz.";
			if (CheckAttribute(pchar, "questTemp.Mangarosa"))
			{
				link.l1 = "Mangarosa mı? O bitkiyi biliyorum.";
				link.l1.go = "gypsy_VD_manga_1";
			}
			else
			{
				link.l1 = "Nasıl görünüyor?";
				link.l1.go = "gypsy_VD_no_manga";
			}
		break;

		case "gypsy_VD_no_manga":
			dialog.text = "Oldukça uzun boylu, yaprakları bölünmüş ve hoş, baş döndürücü bir kokusu olan bir bitki. Onu başka bir şeyle karıştırmazsın.";
			link.l1 = "Pekala, bu mangarosayı bulacağım.";
			link.l1.go = "gypsy_2";
		break;

		case "gypsy_VD_manga_1":
			dialog.text = "Sen de tütününe mi karıştırıyorsun?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "Hayır, hiç de değil! Amelia adında bir şifacı var. Zihinlerini gerçekten altüst edebilecek iksirler yapmak için bunu kullanıyor.";
				link.l1.go = "gypsy_VD_manga_1_2";
			}
			else
			{
				link.l1 = "Hayır, ama mangarosayla birkaç kez ilgilendim.";
				link.l1.go = "gypsy_VD_manga_2";
			}
		break;

		case "gypsy_VD_manga_1_2":
			dialog.text = "Amelia'yı tanıyor musun? Peki, "+GetSexPhrase("falconet","dovey")+", yakında bana gerçekten rakip olacaksın. Ama şimdi bunun zamanı değil. Git mangarosayı getir, ben de her şeyi hazırlayacağım.";
			link.l1 = "Yoldayım.";
			link.l1.go = "gypsy_2";
			AddCharacterExpToSkill(pchar, "Fortune", 200);
		break;

		case "gypsy_VD_manga_2":
			dialog.text = "Anladım, sen sıradan biri değilsin, "+GetSexPhrase("falconet","dovey")+"Bilginiz engin, zekânız bir kılıç kadar keskin! Bilinmeyene adım atmaktan korkmaz, başkalarının uzak durduğu şeyleri öğrenmeye heveslisiniz. Thomas sizin yardımınıza sahip olduğu için şanslı. Şimdi git, bana mangarosayı getir, kızı iyileştireceğim.";
			link.l1 = "...";
			link.l1.go = "gypsy_2";
		break;
		
		case "gypsy_2":
			DialogExit();
			AddDialogExitQuestFunction("DWH_gypsy_22");
		break;
		
		case "Bandit_1":
			dialog.text = "Ha-ha. Sana söylüyorum Mark, o tam bir aptal. Evini bile kilitlemiyor.";
			link.l1 = " Emin misin, onun tavuğu evde oturmayacak mı? ";
			link.l1.go = "Bandit_2";
			
			locCameraSleep(true);
			sld = CharacterFromID("DWH_Bandit_1");
			CharacterTurnToLoc(sld, "goto", "ass4");
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "ass2");
		break;
		
		case "Bandit_2":
			DialogExit();
			AddDialogExitQuestFunction("DWH_Bandit_2");
		break;
		
		case "Bandit_3":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "Pekâlâ, pekâlâ, taze balık ağımıza takıldı! Hadi, öylece durma. Ceplerini boşalt, çabuk ol, keyfimiz kaçmadan.";
			link.l1 = "Sakin olun, haydutlar. Buraya iş için geldim. "+sld.name+" beni gönderdi. Mangarosa'ya ihtiyacım var.";
			link.l1.go = "Bandit_4";

			locCameraSleep(false);
			locCameraFromToPos(3.39, 1.16, -1.80, true, 3.62, -0.50, 3.63);
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "goto2");
		break;

		case "Bandit_4":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "Sen diyorsun ki "+sld.name+" seni mi gönderdi? Tamam, mangarosa var. Bize on altın ver, senin olsun.";
			if (PCharDublonsTotal() >= 10)
			{
				link.l1 = "Buyurun.";
				link.l1.go = "Bandit_5";
			}
			link.l2 = "Para mı? Ne için? Sadaka dağıtmam. Ama sana iki kilo çelik verebilirim!";
			link.l2.go = "Bandit_7";
		break;

		case "Bandit_5":
			dialog.text = "Pekâlâ, işte mangarosan. Ve unutma, bizi asla görmedin.";
			link.l1 = "Heh. Uyarıya gerek yoktu.";
			link.l1.go = "Bandit_6";
			GiveItem2Character(PChar, "cannabis7");
			RemoveDublonsFromPCharTotal(10);
		break;
		
		case "Bandit_6":
			DialogExit();
			AddDialogExitQuestFunction("DWH_Bandit_6");
		break;
		
		case "Bandit_7":
			DialogExit();
			AddDialogExitQuestFunction("DWH_Bandit_7");
		break;
		
		case "gypsy_3":
			if (CheckCharacterItem(PChar, "cannabis7"))
			{
				dialog.text = "...";
				link.l1 = "Bir bak, "+npchar.name+" , bu ihtiyacın olan bitki mi?";
				link.l1.go = "gypsy_4";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "İstediğim şeyi getirdin mi?";
				link.l1 = "Henüz değil, üzerinde çalışıyorum.";
				link.l1.go = "exit";
				NextDiag.TempNode = "gypsy_3";
			}
		break;

		case "gypsy_4":
			dialog.text = "Evet, işte bu. Artık ihtiyacım olan her şeye sahibim ve başlayabilirim.";
			link.l1 = "...";
			link.l1.go = "gypsy_5";
			TakeItemFromCharacter(pchar, "cannabis7");
		break;

		case "gypsy_5":
			StartInstantDialog("DWH_Tomas", "Tomas_17", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
		break;

		case "Tomas_17":
			dialog.text = "Hadi hızlıca gidelim, hiç vakit kaybetmemeliyiz.";
			link.l1 = "...";
			link.l1.go = "Tomas_18";
			CharacterTurnByChr(npchar, CharacterFromID("DWH_gypsy"));
		break;

		case "Tomas_18":
			dialog.text = "Kaptan, izin verirseniz, sonra konuşalım. Şimdi en önemli kısmı yaşıyoruz... tedavi.";
			link.l1 = "Elbette, Thomas. Umarım kızın yakında iyileşir.";
			link.l1.go = "Tomas_19";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tomas_19":
			DialogExit();
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "gypsy_6":	// если не прошли проверку ВД у священника
			dialog.text = "...";
			link.l1 = ""+npchar.name+" , Thomas seni kendi isteğiyle geri çevirmedi. Rahip, yardımını kabul ederse onu aforoz etmekle tehdit etti.";
			link.l1.go = "gypsy_7";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_7":
			dialog.text = "Hemen anladım, "+GetSexPhrase("sevgilim","güzellik")+",   bana o reddi ağır bir kalple verdiğini.";
			link.l1 = "Kilise alınmadan ona yardım etmenin bir yolu var mı?";
			link.l1.go = "gypsy_8";
		break;

		case "gypsy_8":
			dialog.text = "Oh, "+GetSexPhrase("sevgilim","güzellik")+", bu öyle kolay bir iş değil, ama yolları biliyorum, ne yapmam gerektiğini de biliyorum. Yalnız, senin yardımın olmadan başaramam, anlıyorsun değil mi.";
			link.l1 = "Elbette, bana güvenebilirsin.";
			link.l1.go = "gypsy_10";
			link.l2 = "Üzgünüm, kara kaşlı, ama bunun için gerçekten hiç vaktim yok. Elimden gelen her şeyi yaptım. Şimdi kendi işlerime bakmam gerek.";
			link.l2.go = "gypsy_9";
		break;
		
		case "gypsy_9":
			DialogExit();
			CloseQuestHeader("DWH");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			
			sld = CharacterFromID("DWH_Tomas");
			sld.lifeday = 0;
		break;
		
		case "gypsy_10":
			dialog.text = "O halde bana şunları getir: kıza ait bir eşya, iki dal datura, bir dal ipekakuan ve bir dal verbena. Bunların hepsini getirirsen, onun için iyileştirici bir iksir hazırlayabilirim.";
			link.l1 = "Pekâlâ, gereken her şeyi alacağım.";
			link.l1.go = "gypsy_11";
		break;

		
		case "gypsy_11":
			DialogExit();
			AddQuestRecord("DWH", "7");
			
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_21":
			dialog.text = "...";
			link.l1 = "Thomas, ne yazık ki rahip sözlerime kulak asmadı. Ama çingene ile ben sana yardımcı olabiliriz. Benim ihtiyacım olan...";
			link.l1.go = "Tomas_22";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_22":
			dialog.text = "Kilisenin karşısına mı çıkmamı öneriyorsun?";
			link.l1 = "Her şeyi sessizce halledeceğiz, kimsenin haberi olmayacak. Kızınız yakında yeniden hayatın tadını çıkaracak ve genç bir hanıma yakışır şekilde şehirde özgürce dolaşabilecek.";
			link.l1.go = "Tomas_23";
			link.l2 = "Lanet olsun, Thomas Morrison, kızının iyileşmesini gerçekten istiyor musun, yoksa sadece güzel sözlerin arkasına mı saklanıyorsun?";
			link.l2.go = "Tomas_24";
		break;

		case "Tomas_23":
			dialog.text = "Pekâlâ, kabul ediyorum. Ama lütfen, dikkatli davran. Gereksiz dedikodular ve sorunlar istemiyorum.";
			link.l1 = "Elbette. Şimdi, kızınızın değer verdiği kişisel bir eşyasına ihtiyacım var.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Sneak", 200);
		break;

		case "Tomas_24":
			dialog.text = "Pekala, kabul ediyorum. Ama lütfen, dikkatli davran. Gereksiz dedikodular ve sorunlar istemiyorum.";
			link.l1 = "Elbette. Kızınızın kişisel bir eşyasına ihtiyacım var. Ona bağlı olduğu bir şey olmalı.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Tomas_25":
			dialog.text = "Hmm... Evet! Ne işe yarayacağını biliyorum. Burada bekle, hemen döneceğim.";
			link.l1 = "Bekleyeceğim...";
			link.l1.go = "Tomas_26";
		break;

		case "Tomas_26":
			DialogExit();
			SetLaunchFrameFormParam("A few minutes later...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("DWH_TomasGovotitAgain", 0.0);
			LaunchFrameForm();
		break;
		
		case "Tomas_27":
			dialog.text = "Al, bunlar yeşim boncuklar. Esther onları asla çıkarmazdı, ona çok kıymetliler.";
			link.l1 = "Mükemmel. Şimdi tek yapman gereken beklemek. Yakında görüşürüz, Thomas.";
			link.l1.go = "Tomas_28";
			GiveItem2Character(PChar, "jewelry49");
		break;

		case "Tomas_28":
			DialogExit();
			AddQuestRecord("DWH", "8");

			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest/MiniEvents/DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "gypsy_21":
			dialog.text = "Her şeyi almayı başardın mı?";
			if (GetCharacterItem(pchar, "cannabis1") >= 2 && GetCharacterItem(pchar, "cannabis4") >= 1 && GetCharacterItem(pchar, "cannabis3") >= 1)
			{
				link.l1 = "İhtiyacım olan her şeyi toplamayı başardım.";
				link.l1.go = "gypsy_22";
			}
			link.l2 = "Bana ne getirmem gerektiğini tekrar hatırlat.";
			link.l2.go = "gypsy_napomni";
		break;

		case "gypsy_napomni":
			dialog.text = "O zaman ihtiyacım olanlar şunlar: kıza ait bir eşya, iki dal datura, iki dal ipekakuana ve bir dal verbena. Bunların hepsini getirirsen, onun için bitkisel bir karışım hazırlayabilirim.";
			link.l1 = "Pekâlâ, gereken her şeyi halledeceğim.";
			link.l1.go = "gypsy_napomni_2";
		break;

		case "gypsy_napomni_2":
			DialogExit();
			NextDiag.TempNode = "gypsy_21";
		break;

		case "gypsy_22":
			dialog.text = "Mükemmel. Şimdi kız için iyileştirici bir iksir hazırlayabilirim. Yarın sabahdan önce hazır olmaz. Beni her zamanki gibi kasabanın sokaklarında bulabilirsin.";
			link.l1 = "Pekâlâ, o zaman görüşürüz.";
			link.l1.go = "gypsy_23";
			DelLandQuestMark(npchar);
			RemoveItems(pchar, "cannabis1", 2);
			RemoveItems(pchar, "cannabis4", 1);
			RemoveItems(pchar, "cannabis3", 1);
			RemoveItems(pchar, "jewelry49", 1);
		break;
		
		case "gypsy_23":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("DWH", "11");
			SetTimerFunction("DWH_GypsyPrigotovilaZelie", 0, 0, 1);
		break;
		
		case "gypsy_31":
			dialog.text = "...";
			link.l1 = "Pekala, "+npchar.name+", iksiriniz hazır mı?";
			link.l1.go = "gypsy_32";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_32":
			dialog.text = "İşte orada, "+GetSexPhrase("sevgilim","güzellik")+". Kız bu boncukları taksın ve şişedeki sıvıyı son damlasına kadar içsin. En fazla bir ay içinde tamamen iyileşecek.";
			link.l1 = "Bunu hemen Thomas'a götüreceğim. Hoşça kal, kara kaşlı.";
			link.l1.go = "gypsy_33";
			GiveItem2Character(PChar, "quest_potion");
			GiveItem2Character(PChar, "jewelry49");
		break;

		case "gypsy_33":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);

			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest/MiniEvents/DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "Tomas_31":
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				dialog.text = "...";
				link.l1 = "Thomas, her şey hazır. Esther bu boncukları takmalı ve iksirin şişesini tek seferde bitirmeli.";
				link.l1.go = "Tomas_32";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Tomas_31";
			}
		break;

		case "Tomas_32":
			dialog.text = "Teşekkür ederim, "+pchar.name+"! Lütfen beni affedin, bir dakikamı bile boşa harcamak istemiyorum...";
			link.l1 = "Elbette, elbette.";
			link.l1.go = "Tomas_33";
			TakeItemFromCharacter(pchar, "quest_potion");
		break;
		
		case "Tomas_33":
			DialogExit();
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "Tomas_41":
			dialog.text = "Selamlar, "+pchar.name+"! Esther'im iyileşti! Tamamen sağlıklı ve şimdi kilisede, seni ve çingeneyi bize gönderdiği için Rabbimize şükrediyor!";
			link.l1 = "Thomas, her şeyin yoluna girmesine çok sevindim! Kıza iyi bak, artık önünde uzun ve mutlu bir hayat var.";
			link.l1.go = "Tomas_42";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_42":
			dialog.text = "Şu üç yüz doblonu alın. Ne yazık ki, daha fazlasını veremem, çünkü bu parayı toplamak için borca girmek zorunda kaldım. Ama bilin ki, size olan minnettarlığımı ne sözler ne de altın anlatabilir, Kaptan. Sadece onun hayatı için duyduğum korkudan beni kurtarmakla kalmadınız, ailemize de gelecek için umut verdiniz. Size daima borçlu kalacağım!";
			link.l1 = "Teşekkür ederim! Üç yüz doblon oldukça cömert bir ödül, için rahat olsun – bana fazlasıyla teşekkür etmiş oldun!";
			link.l1.go = "Tomas_43";
			link.l2 = "Paranı almam, Thomas. Israr etmeyi bile düşünme! O parayla genç Esther’e güzel bir elbise al, o bunu hak ediyor.";
			link.l2.go = "Tomas_46";
		break;

		case "Tomas_43":
			dialog.text = ""+pchar.name+", istediğin zaman bizi ziyaret et. Evimizde her zaman hoş karşılanırsın. Ayrıca, çingene kadınla da konuş, seninle görüşmek istedi.";
			link.l1 = "Bunu bir onur sayarım! Şimdi müsaadenizi isteyeyim - gelgitler hiçbir kaptanı beklemez.";
			link.l1.go = "Tomas_44";
			AddItems(pchar, "gold_dublon", 300);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;

		case "Tomas_44":
			dialog.text = "Elbette, elbette. Tanrı yardımcın olsun, "+GetFullName(pchar)+"!";
			link.l1 = "Hoşça kal.";
			link.l1.go = "Tomas_45";
		break;
		
		case "Tomas_45":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_41";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_46":
			dialog.text = "Gerçekten asil bir insansınız, "+GetFullName(pchar)+"! Meryem Ana seninle olsun! Bizi ziyaret et, evimizde her zaman hoş karşılanan bir misafirsin. Ve ayrıca, "+pchar.name+", çingeneyle konuş, seni görmek istemişti.";
			link.l1 = "Elbette! Şimdi gitmeliyim - deniz beni çağırıyor.";
			link.l1.go = "Tomas_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Tomas_47":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_44";
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.DWH_QuestCompleted = true;
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1;
			
			AddSimpleRumourCity("Have you heard? "+GetFullName(pchar)+" procured a remedy for Thomas Morrison's daughter that miraculously restored the poor girl's health!", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Thomas Morrison lights a candle in the parish daily for the health of "+GetFullName(pchar)+". They say thanks to his (her) efforts, Thomas's daughter was freed from a prolonged illness.", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Esther Morrison has blossomed before our eyes. As if she had never been ill. No one can really explain what made the illness retreat.", "SentJons", 10, 1, "");
		break;
		
		case "gypsy_41":
			dialog.text = "Ve işte buradasın, "+GetSexPhrase("falconet","dovey")+"!   Döneceğini biliyordum. Sayende kız kendine geldi ve şimdi bir güvercin gibi dolaşıyor. Bütün kasaba onun hakkında hayranlıkla konuşuyor.";
			link.l1 = "Pekâlâ, kara kaşlı, bu sadece benim başarım değildi – bana fazla pay biçme. Onun sağlığını yerine getiren senin hazırladığın iksirdi, bu yüzden kendi katkını küçümseme.";
			link.l1.go = "gypsy_42";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_42":
			dialog.text = "Senin kalbin çok iyi, "+GetSexPhrase("falconet","dovey")+", ve keskin bir zekâ! Senin için büyük işler yazılmış – bu benim kehanetim.";
			link.l1 = "Heh... şey, teşekkür ederim, "+npchar.name+".";
			link.l1.go = "gypsy_43";
		break;
		
		case "gypsy_43": // плохой вариант
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "9");
			CloseQuestHeader("DWH");
		break;
		
		case "gypsy_44":
			dialog.text = "Ve işte oradasın, "+GetSexPhrase("falconet","dovey")+"!   Burada tekrar görüneceğini biliyordum.   Sayende kız kendine geldi, şimdi güvercin gibi kanat çırpıyor.   Bütün kasaba ona hayran.";
			link.l1 = "Dur bakalım, kızı sen kurtardın, şimdi de bütün övgüyü bana mı bırakmak istiyorsun? Olmaz öyle şey! İksiri sen hazırladın, onu ayağa kaldıran da sendin, onur da sana ait olmalı.";
			link.l1.go = "gypsy_45";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_45":
			dialog.text = "Senin kalbin çok iyi, "+GetSexPhrase("falconet","dovey")+", ve asil bir ruhsun. Sana bir hediye getirdim – her kaptanın takdir edeceği bir şey. Al bakalım. Artık gemindeki farelerin ne huzuru ne de mutluluğu kalacak!";
			link.l1 = "Benim için bir hediye mi? Yıldızlar adına, hiç beklemezdim!";
			link.l1.go = "gypsy_46";
			GiveItem2Character(PChar, "rat_poison");
		break;

		case "gypsy_46":
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				dialog.text = "Ruhun temiz, anlık zevk uğruna mangarosayı yakmayacağını görüyorum. Ona acil ihtiyacın olursa, bana gel, "+GetSexPhrase("falconet","dovey")+" . Üç dalı sana üç yüz elli doblona mal olur\nBu ot nazlıdır, herkes bulamaz. O yüzden acele etme – benden ayda birden fazla isteme, zaten bulamam.";
			}
			else
			{
				dialog.text = "Ruhun parlak, görüyorum ki akılsız değilsin, otları bazı şifacılardan aşağı kalmaz şekilde anlıyorsun. Pek çok şeyi bulabilirsin, ama şans her zaman yanında olmaz. Herkesin bulamayacağı nadir bir bitki var. Adı mangarosa. Bir gün ihtiyacın olursa, bana gel, "+GetSexPhrase("falconet","dovey")+". Üç kök bulurum, ama bedavaya vermem – üç yüz elli doblon isterim\nAma bu ot inatçıdır, aceleye getirme. Ayda birden fazla sorma – kaderin tüm kartlarını önüme sersen de, daha önce bulamam.";
			}
			link.l1 = "Pekala, teşekkür ederim, "+npchar.name+".";
			link.l1.go = "gypsy_47";
		break;
		
		case "gypsy_47": // хороший вариант
			DialogExit();
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "10");
			CloseQuestHeader("DWH");
			AddQuestRecordInfo("Useful_Acquaintances", "1");
			
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
		
		case "Tomas_51":
			dialog.text = "Kaptan, sürekli düşünüyorum – seni tam zamanında buraya yönlendiren bizzat Tanrı'nın kendisi olmalı! Kızımı kurtardın, bunu asla unutmayacağım.";
			link.l1 = "Belki de, Thomas. Tanrı'nın yolları anlaşılmazdır.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tomas_52";
			SetTimerFunction("DWH_Tomas_HelloAgain", 0, 0, 1);
		break;

		case "Tomas_52":
			dialog.text = "Biraz şarap ister misiniz, Kaptan? Değerli misafirler için özel bir şeyim var.";
			link.l1 = "Teşekkür ederim, Thomas, ama ne yazık ki gitmem gerek.";
			link.l1.go = "exit";
		break;

		case "gypsy_Mangarosa":
			dialog.text = "Ne istiyorsun, benim şah kartalım?";
			if (CheckAttribute(pchar, "questTemp.DWH_Mangarosa"))
			{
				link.l1 = "Söyle bakalım, kara kaşlı, bana mangarosa verir misin?";
				link.l1.go = "gypsy_Mangarosa_1";
			}
			link.l2 = "Sadece uğrayıp merhaba demek istedim. Artık gitme vakti!";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;
		
		case "gypsy_Mangarosa_1":
			dialog.text = "Benden başka kim, "+GetSexPhrase("sevgilim","güzellik")+", böyle bir nadirliği sana kim getirir? Üç yüz elli doblon – ve senin olur, üç dal, ne eksik ne fazla.";
			if (PCharDublonsTotal() >= 350)
			{
				link.l1 = "Fiyatın makul. Altın senin.";
				link.l1.go = "gypsy_Mangarosa_2";
			}
			link.l2 = "Kahretsin! Kesem yine çok hafif. Şans bana güldüğünde geri döneceğim.";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;

		case "gypsy_Mangarosa_2":
			dialog.text = "Bu daha iyi. Al bunu. Ama dikkatli ol, boş yere harcama – mangarosa sıradan bir ot değildir, içinde herkesin başa çıkamayacağı bir güç saklıdır.";
			link.l1 = "Endişelenme, kara kaşlı, onun gücüne layık bir kullanım bulacağım.";
			link.l1.go = "gypsy_Mangarosa_3";
			AddItems(pchar, "cannabis7", 3);
			RemoveDublonsFromPCharTotal(350);
		break;
		
		case "gypsy_Mangarosa_3":
			DialogExit();
			
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			DeleteAttribute(pchar, "questTemp.DWH_Mangarosa");
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
	}
}