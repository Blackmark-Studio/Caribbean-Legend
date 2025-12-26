// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Size nasıl yardımcı olabilirim?","Sana nasıl yardımcı olabilirim?"),"Söyle bana, seni ne rahatsız ediyor, "+GetAddress_Form(NPChar)+"?","Üçüncü kez, "+GetAddress_Form(NPChar)+", ne istiyorsun?","Senden bıktım. Defol!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim, kusura bakmayın.","Bir şey değil, affedersiniz."),"Beni affedin, önemli bir şey değil.","Haklısınız, bu zaten üçüncü sefer oldu. Affedin beni...","Özür dilerim.",npchar,Dialog.CurrentNode);		
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Dinle, burada Havana'da ya da civarında Joachim Merriman adında bir adam gördün ya da tanıdın mı? Orta yaşlı, Portekizli bir señor; bıyıklı, keçi sakallı ve delici bakışlı biri. Belki bir koyda ya da ormanda karşılaşmışsındır? Onu arıyorum.";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "H-hayır, denizci, e-elbette hayır. Buraya nadiren ziyaretçi gelir, anlıyor musun, ıı... ve ben... b-ben tarif ettiğin gibi birini görmedim, yani...";
			link.l1 = "Gerçekten mi? O zaman neden kekeliyor ve gözlerini kaçırıyorsun? Bana şimdi yalan söyleme, gerçeği biliyorsun. En iyisi bana tekrar söyle - o adamı gördün mü?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "B-Ben size söylüyorum, Señor, h-hiç kimseyi görmedim! B-ben çocukluğumdan beri k-kekeliyorum...";
			link.l1 = "Yalan, hepsi yalan. Gözlerinde görüyorum. Nerede o, nerede Merriman?! Söyle bana, HEMEN!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Ben Merriman diye birini tanımıyorum! Bu ismi de daha önce hiç duymadım! Bana zarar vermeye kalkma, yoksa Komutan seni kalede astırır! O yüzden dikkatli ol, delikanlı!";
			link.l1 = "Öyle mi düşünüyorsun? Peki. Şimdi beni çok dikkatli dinle: Joachim Merriman bir büyücü. Kutsal Engizisyon onu arıyor. Yıllar önce Avrupa'da, mezar kazmak, ölülere saygısızlık yapmak ve büyücülükten dolayı kazığa bağlanıp yakılmaya mahkûm edildi. Ve şimdi kesin olarak biliyorum ki, burada, Havana'nın dış mahallelerinde bir yerde saklanıyor...";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "...";
			link.l1 = "...yakın zamanda civardaki mağarayı zombilerden temizledim ve kimin sorumlu olduğunu biliyorum! Elbette, Merriman başka nereye giderdi ki, mezarlıktan başka! Onun nerede olduğunu biliyorsun. Ama sen bilirsin, sana dokunmayacağım, fakat Santiago'daki Engizisyoncuları ziyaret edeceğim. Peder Vincento, Joachim Merriman'ın Havana mezarlığında yerel bekçiyle birlikte saklandığını çok ilginç bulacaktır...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "...";
			link.l1 = "...Yüzünün rengi şimdiden soldu mu? Sana bir soylunun sözünü veriyorum: bulgularımı bildirdikten bir gün sonra, bütün ada İspanyol askerleriyle dolup taşacak. Ve sen işkence tezgahına gerilecek, o büyücünün nerede saklandığını söyleyene kadar yalvarıp ağlayacaksın. Ondan sonra da, ben auto-da-fé’yi izlerken, onun suç ortağı olarak kazığa bağlanıp yakılacaksın. Bu hoşuna gider mi?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Lütfen, señor! Yemin ederim, bu işlerin hiçbirine karışmadım! Ben... ben hiçbir şey yapamadım... Ona nasıl karşı koyabilirdim ki?! O korkunç bir adam, yapabileceklerini... siz onun neler yapabileceğini hayal bile edemezsiniz! Merhamet edin, yalvarırım!";
			link.l1 = "Bana güven, neler yapabileceğini biliyorum. Kendi gözlerimle gördüm. Ee? Nerede o? Söyle bana, söz veriyorum seni bu işe karıştırmayacağım.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "O... O mezarlığın altındaki bir mağarada saklanıyor. Oraya sadece şapelin kapısından geçerek ulaşabilirsin. O dışarı çıktığında, ben evime saklanıyorum ve orada kalıyorum. O dehşetten kurtulmak için ne kadar çok istediğimi hayal bile edemezsin!\nAma yaklaşmaya bile cesaret edemem. O... Onu taze bir mezar kazarken gördüm, sonra... sonra ölü adam kalktı ve ay ışığında mezarlıkta dolaşmaya başladı! O an neredeyse aklımı kaybediyordum! Ama Merriman gitmeme izin vermedi. Eğer izni olmadan, yarım günlüğüne bile evimden çıkarsam, beni bulup o iğrenç şeye... yürüyen bir iskelete dönüştüreceğini söyledi!";
			link.l1 = "Mağarasından ne kadar sık çıkar?";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Şey, ona kasabadan yiyecek ve şifa iksirleri getiriyorum, bir de... ne isterse artık. Ay dolunay olduğunda, ayda bir ya da iki kez gider... Kapıya bir not bırakır, neye ihtiyacı varsa yazar... Ben de alıp kapıya bırakırım, o da döndüğünde alır.";
			link.l1 = "Anladım. O inine giden kapı - herhangi bir şekilde kilitli mi?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			dialog.text = "Evet, öyle. Her zaman kilitli olur. Kapı çok sağlam, kilidi ise kocaman ve karmaşık.";
			link.l1 = "Hm... Merriman aptal değil, kesinlikle Avrupa'daki evi gibi ininden başka bir çıkışı vardır. Eğer kapıyı zorla açarsak, kaybolur gider, bir daha asla bulunmaz. Hmmm...";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Senyor, beni Engizisyona teslim etmeyeceğine yemin eder misin?";
			link.l1 = "Sana söz verdim ve bir asilzadenin sözü kutsaldır. Yemin ederim ki seni ele vermeyeceğim.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Tanrı sizi korusun, Señor! Mağaraya nasıl gidileceğini biliyorum. Bir anahtar var, ikinci bir anahtar... O bende. Merriman o kilidin iki anahtarı olduğunu bilmiyor. Ben asla girmeye cesaret edemezdim, ama siz...";
			link.l1 = "Anahtarı bana ver, seni bu kâbustan kurtarayım.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_crypt");
			dialog.text = "Buyurun, Señor. Gerçekten onun inine mi gidiyorsunuz?";
			link.l1 = "Benim. Evine kapan ve ben içeri girerken orada bekle. Eğer dönmezsem, her şeyi bırak ve olabildiğince hızlı kaç.";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "Ama dikkatli olun, Señor. Mağarasından korkutucu sesler geldiği duyuldu ve orada kimin yaşadığını düşünmek bile beni korkutuyor. Ama Merriman kesinlikle orada yalnız değil.";
			link.l1 = "Elimden gelen her önlemi alacağım. Hoşça kal.";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			DialogExit();
			AddQuestRecord("Caleuche", "30");
			pchar.questTemp.Caleuche = "merriman";
			pchar.quest.caleuche_merriman_cave.win_condition.l1 = "locator";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.location = "Havana_CryptBig2";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator_group = "reload";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator = "reload2";
			pchar.quest.caleuche_merriman_cave.function = "Caleuche_OpenMerrimanCave";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1 = "location";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1.location = "Havana_CryptDungeon";
			pchar.quest.caleuche_merriman_cave1.function = "Caleuche_InMerrimanCave";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Caleuche_MerrimanCaveOver", 0, 0, 3, false); // таймер
			npchar.quest.caleuche = "true";
			// логово Мерримана
			int n = Findlocation("Havana_CryptDungeon");
			locations[n].id.label = "Merrimancave";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
