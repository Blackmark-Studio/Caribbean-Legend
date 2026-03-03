// Абрахам Норман
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
		case "First time":
			dialog.text = "Bir şeye mi ihtiyacınız var?";
			link.l1 = "Hayır, hiçbir şey.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "norman_us":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("Ne istiyorsun? Yoluna bak, işine gücüne bak. Yeter ki beni rahat bırak.","Hey, hey, dostum. Yürüyüşe mi çıktın? O zaman yürümeye devam et ve Bay Abraham'ı rahat bırak. O da yürüyüşe çıkıyor. Temiz deniz havası alıyor.","Merhaba, dostum. Sohbet etmek ister misin? Ama bir sorun var: konuşacak havamda değilim. Git, başkasını rahatsız et. Git meyhanede biraz dinlen. Biraz rom iç...");
				link.l1 = "Dinle Abraham, son zamanlarda Isla Tesoro'da Miguel Dichoso adında bir adamla karşılaştın mı? Buralarda epey tanınan biri kendisi.";
				link.l1.go = "tieyasal";
				break;
			}
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase("Ne istiyorsun? Yoluna bak, işine gücüne bak. Sadece beni rahat bırak.","Hey, hey, dostum. Yürüyüşe mi çıkıyorsun? O zaman yürü bakalım, Bay Abraham'ı da rahat bırak. O da yürüyüşe çıkıyor. Biraz deniz havası alacak.","Selam dostum. Sohbet etmek ister misin? Ama bir sorun var: Konuşacak havamda değilim. O yüzden başkasını rahatsız et. Git meyhanede takıl. Biraz rom iç..."),LinkRandPhrase("Hey, denizci. Ne o, kafan mı kalın? Sanırım gayet açık konuşmuştum.","Dostum, git biraz dinlen. Kulağın pek iyi duymuyor gibi.","Hey dostum, ne yani, aptal mısın sen? Sana zaten açık açık söyledim."),"Dostum, beni kızdırma. Hayatım boyunca o kadar çok karacıyı öldürdüm ki, bir eksik bir fazla hiç fark etmez.","Pekâlâ, beni sinirlendirdin. Şimdi ya o paslı kılıcını çek ya da alabildiğince hızlı kaç. Sana ikinci seçeneği tavsiye ederim...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Peki, dostum. Seni rahatsız etmeyeceğim.","Pekala, pekala. Anladım...","Vay canına, denizlerin yıldırımı gibi görünüyorsun! Tamam, ben kaçtım.","Ne?!",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "norman_us";
		break;
		
		case "norman_fes":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("Ne istiyorsun? Yoluna bak, kendi işine bak. Beni rahat bırak.","Hey, hey, dostum. Yürüyüşe mi çıkıyorsun? O zaman yürümeye devam et ve Bay Abraham'ı rahat bırak. O da yürüyüşe çıkıyor. Biraz deniz havası alacak.","Selam dostum. Sohbet etmek mi istiyorsun? Ama bir sorun var: konuşacak havamda değilim. O yüzden git başkasını rahatsız et. Git meyhanede takıl biraz. Biraz rom iç...");
				link.l1 = "Dinle Abraham, son zamanlarda Isla Tesoro'da Miguel Dichoso adında bir adamla karşılaştın mı? Buralarda epey tanınan birisidir.";
				link.l1.go = "tieyasal";
				break;
			}
			switch (hrand(5))
			{
				case 0:
					dialog.text = "Don! Bu adanın valisiyim. Ne, bana inanmıyor musun?!";
					link.l1 = "Elbette biliyorum! Isla Tesoro'nun valisini kim tanımaz ki...";
					link.l1.go = "norman_fes0_fight";
					link.l2 = "Ha, bir de amiral olduğunu söyle, ona da kesinlikle inanırım!";
					link.l2.go = "norman_fes0_peace";
				break;
				
				case 1:
					dialog.text = "Dikkat! Bakın - Amiral Barbarigo! Ünlü süvari kılıcımı tanımıyor musunuz?";
					link.l1 = "Özür dilerim, Amiralim! Bundan sonra daha dikkatli olacağım.";
					link.l1.go = "norman_fes1_peace";
					link.l2 = "Kılıcının ünü her yere yayılmış. Ne yazık ki bir aptalın elinde.";
					link.l2.go = "norman_fes1_fight";
				break;
				
				case 2:
					dialog.text = "Gördüğünüz gibi, burada sürgündeyim. General Monck'tan gelecek haberleri bekliyorum. Gizli kraliyet kimliğimi açıklamamanızı rica ediyorum. Cromwell'in casusları her şeyi duyar.";
					link.l1 = "Elbette, Majesteleri. Kimse Karl II'nin Batı Hint Adaları'nda saklandığını asla öğrenmeyecek.";
					link.l1.go = "norman_fes2_fight";
					link.l2 = "Pekâlâ, o zaman ben de Papa Innocentius X'im.";
					link.l2.go = "norman_fes2_peace";
				break;
				
				case 3:
					dialog.text = "Sana ne oldu Blaze? İki gündür seni arıyorum. Baban Nicolas'ı tamamen unuttun!";
					link.l1 = "Seninle uğraşacak vaktim yok, baba! Başım çok kalabalık.";
					link.l1.go = "norman_fes3_peace";
					link.l2 = "Yanılıyorsunuz, efendim. Benim adım "+GetFullName(pchar)+".";
					link.l2.go = "norman_fes3_fight";
				break;
				
				case 4:
					dialog.text = "Şşş... Ben Davy Jones. Söyle bakalım, ölümden korkar mısın?";
					link.l1 = "Elbette öyleyim, Bay Jones. Özellikle de akşamdan kalmayken.";
					link.l1.go = "norman_fes4_fight";
					link.l2 = "Bir ölüm bir trajedidir, bin ölüm ise sadece bir istatistiktir.";
					link.l2.go = "norman_fes4_peace";
				break;
				
				case 5:
					dialog.text = "Yeni oyunumun sonunu bir an önce bitirmem lazım. Bana 'Olmak ya da olmamak' cümlesini tamamlamamda yardım etmelisin?!";
					link.l1 = "İşte mesele bu! Hakarete katlanıp yolumuza devam mı edelim...";
					link.l1.go = "norman_fes5_fight";
					link.l2 = "Bir içki, elbette. Ama bir genelevde hastalık kaparsam hiç şaşırmam!";
					link.l2.go = "norman_fes5_peace";
				break;
			}
		break;
		
		case "norman_fes0_fight":
			dialog.text = "Ne saçmalıyorsun sen? 'Tesoro' mu dedin?! İstersen buraya Bermuda Adaları da de! Bu adanın adı Norman Adası, benim adımı taşıyor, bunu sakın unutma! Sana biraz coğrafya öğretmem gerekecek...";
			link.l1 = "Ha! Ne demek istiyorsun?!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes0_peace":
			dialog.text = "Haklısın, denizci. Aslında gerçekten Amiral Barbarigo'yum, ama bu aramızda kalsın. Hazırlan, yakında yola çıkıyoruz. Bu senin işine yarayacak.";
			link.l1 = "Gerçekten çok minnettarım!";
			link.l1.go = "norman_fes0_exit";
		break;
		
		case "norman_fes0_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 12)
			{
				GiveItem2Character(pchar, "pistol2");
				Log_Info("You've received a three-barreled shotgun");
			}
			else
			{
				if (GetDataDay() == 23 && GetDataMonth() == 2)
				{
					GiveItem2Character(pchar, "mushket1");
					Log_Info("You've received a match-lock musket");
				}
				else
				{
					GiveItem2Character(pchar, "cartridge");
					Log_Info("You've received a paper cartridge");
				}
			}
		break;
		
		case "norman_fes1_fight":
			dialog.text = "Şimdi kimin aptal olduğunu göreceğiz. Silahını çek!";
			link.l1 = "Ciddi misin?!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes1_peace":
			dialog.text = "Sana ne demiştim! Hadi, sağlığıma iç.";
			link.l1 = "Şerefe, Amiral!";
			link.l1.go = "norman_fes1_exit";
		break;
		
		case "norman_fes1_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 13)
			{
				GiveItem2Character(pchar, "gold_dublon");
				Log_Info("You've received a gold doubloon");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 4)
				{
					GiveItem2Character(pchar, "chest");
					Log_Info("You've received a chest of doubloons");
				}
				else
				{
					AddMoneyToCharacter(pchar, 5);
				}
			}
		break;
		
		case "norman_fes2_fight":
			dialog.text = "Adımı yaymamanı istemiştim! Şimdi seni tehlikeli bir tanık olarak ortadan kaldırmam gerekecek...";
			link.l1 = "Ah, bunu bekliyordum!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes2_peace":
			dialog.text = "Beni affedin, Ekselansları! Sizi bu kıyafetle tanıyamadım. Lütfen, gerçek bir Katolik'ten bu mütevazı hediyeyi kabul edin.";
			link.l1 = "Delilik sesini yükseltiyor...";
			link.l1.go = "norman_fes2_exit";
		break;
		
		case "norman_fes2_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 14)
			{
				GiveItem2Character(pchar, "amulet_10");
				Log_Info("You've received the Wonderworker Amulet");
			}
			else
			{
				if (GetDataDay() == 25 && GetDataMonth() == 12)
				{
					GiveItem2Character(pchar, "totem_04");
					Log_Info("You've received the Talisman of the Accomplice");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral3");
					Log_Info("You've received a wax candle");
				}
			}
		break;
		
		case "norman_fes3_fight":
			dialog.text = "Herkes peşimde! Oğluma tıpatıp benzeyen bir casus yakaladım! Eminim Thomas onu diğer gözümü de çıkarmak için gönderdi!";
			link.l1 = "Defol, seni aptal!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes3_peace":
			dialog.text = "Yorgunsun ve pek iyi görünmüyorsun, evlat. Hadi git, biraz tedavi ol.";
			link.l1 = "Teşekkürler!";
			link.l1.go = "norman_fes3_exit";
		break;
		
		case "norman_fes3_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 15)
			{
				GiveItem2Character(pchar, "potion4");
				Log_Info("You've received a potion");
			}
			else
			{
				if (GetDataDay() == 19 && GetDataMonth() == 6)
				{
					GiveItem2Character(pchar, "talisman8");
					Log_Info("You've received the Scorpion Amulet");
				}
				else
				{
					GiveItem2Character(pchar, "potion1");
					Log_Info("You've received remedial essence")
				}
			}
		break;
		
		case "norman_fes4_fight":
			dialog.text = "Korkma dostum. Bak, ölmek hiç de korkutucu değil...";
			link.l1 = "Şaka yapmıyormuşsun demek!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes4_peace":
			dialog.text = "Anlaşılan hiç korkmuyorsun. Biliyordum. İşte buna cesaret denir!";
			link.l1 = "Sen komik bir ihtiyarsın...";
			link.l1.go = "norman_fes4_exit";
		break;
		
		case "norman_fes4_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 17)
			{
				GiveItem2Character(pchar, "cirass6");
				Log_Info("You've received a fire-eater waistcoat");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 1)
				{
					GiveItem2Character(pchar, "cirass3");
					Log_Info("You've received a parade cuirass");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral18");
					Log_Info("You've received some tobacco");
				}
			}
		break;
		
		case "norman_fes5_fight":
			dialog.text = "Sen kötü bir şairsin, Denizci. Yoksa kılıcın dilinden daha mı çevik?";
			link.l1 = "Caramba! Senin o süvari kılıcın hiç de oyuncak değilmiş!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes5_peace":
			dialog.text = "Lanet olsun! İşlerin senin için gayet yolunda gitmiş! Hayal gücün için bundan iyisi olur mu!";
			link.l1 = "Yine beklerim.";
			link.l1.go = "norman_fes5_exit";
		break;
		
		case "norman_fes5_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 16)
			{
				GiveItem2Character(pchar, "potionrum");
				Log_Info("You've received a bottle of rum");
			}
			else
			{
				if (GetDataDay() == 28 && GetDataMonth() == 11)
				{
					GiveItem2Character(pchar, "totem_01");
					Log_Info("You've received a throat of cast iron");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral17");
					Log_Info("You've received a glass flask");
				}
			}
		break;
		
		case "norman_fight_again":
			dialog.text = "Aha, seni tanıyorum! Ha-ha!";
			link.l1 = "Yine...";
			link.l1.go = "fight";
		break;
		
		case "norman_fes_again":
			dialog.text = "Pekâlâ dostum, sohbetimizi yaptık. Şimdi yoluna devam et.";
			link.l1 = "Dediğiniz gibi...";
			link.l1.go = "exit";
			NextDiag.TempNode = "norman_fes_again";
		break;
		
		case "tieyasal":
			dialog.text = "Dichoso mu? Ona neden ihtiyacın var, ha?";
			link.l1 = "Yani, ona ihtiyacım var. Sadece ona ihtiyacım var. Peki, onu gördün mü?";
			link.l1.go = "tieyasal_1";
			link.l2 = "Ne demek, ona neden ihtiyacım var? Miguel eski bir dostumdur, hatta arkadaşım diyebilirsin. O şimdi...";
			link.l2.go = "tieyasal_2";
			link.l3 = "Benim için tıpkı bir zamanlar Shark Dodson’a yaptığı gibi yeni bir gemi getirmesini istiyorum.";
			link.l3.go = "tieyasal_3";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l4 = "Miguel Dichoso bir adam öldürdü. Bu yüzden onu arıyorum.";
				link.l4.go = "tieyasal_4";
			}
			npchar.quest.Tieyasal = "true";
		break;
		
		case "tieyasal_1":
			dialog.text = "Senin tek ihtiyacın olan o... Sadece ona ihtiyacın var! Tek ihtiyacın Miguel Dichoso! Hayır, onu görmedim. Uzun zamandır görmedim. Sana yardımcı olabileceğim bir şey yok, Denizci.";
			link.l1 = "Hm... Peki, hoşça kal.";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_2":
			dialog.text = "Bir arkadaş mı diyorsun... Görünen o ki, epeyce arkadaş edinmiş. Şimdi bir arkadaşı eksilecek...";
			link.l1 = "Hey, yaşlı adam. Sana ne oldu?";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "tieyasal_3":
			dialog.text = "Evet, Dichoso bu işlerin ustasıdır, hangi açıdan bakarsan bak. Ama nerede olduğunu bilmiyorum. Uğradı ama sonra yine gitti. O yüzden Alexus'a git, Denizci. Sana harika bir tekne ayarlayacaktır.";
			link.l1 = "Hm... İpucu için sağ ol, dostum.";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_4":
			dialog.text = "Peki, Dichoso kimi ortadan kaldırdı da sen onun peşine düştün, ha, dostum?";
			link.l1 = "Blaze Sharp";
			link.l1.go = "tieyasal_5_1";
			link.l2 = "Nicolas Sharp";
			link.l2.go = "tieyasal_5";
			link.l3 = "Alonso de Maldonado";
			link.l3.go = "tieyasal_5";
			link.l4 = "The Pope";
			link.l4.go = "tieyasal_5_bud_joke";
		break;

		case "tieyasal_5_1":
			dialog.text = "Şşşt... (etrafına bakar) Demek sen de Dichoso'nun Blaze Sharp'ı öldürdüğünü düşünüyorsun?";
			link.l1 = "Evet. Ve bu sadece bir his değil — elimde kanıt da var. Gemi günlüğündeki kayıtlar...";
			link.l1.go = "tieyasal_6"
		break;

		case "tieyasal_5_bud_joke":
			dialog.text = "Şimdi de şaka mı yapıyoruz? Hiç saygın yok! Hadi, yaklaş bakalım...";
			link.l1 = "İmkânsız.";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "tieyasal_5":
			dialog.text = "Ah... Şey. Onu öldürdü ve mesele bundan ibaret. Burada kaç tane katil dolaşıyor, biliyor musun? Her iki adamdan biri! Hayır, denizci. Dichoso'yu uzun zamandır görmedim. Sana hiçbir konuda yardımcı olamam.";
			link.l1 = "Ne yazık...";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_6":
			dialog.text = "Sessiz ol biraz. Senin adın neydi, ha? Aklımdan çıkıvermiş...";
			link.l1 = "Kaptan "+GetFullName(pchar)+".";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Dinle, "+pchar.name+". Dichoso zavallı Blaze'i öldürdü. Kendi gözlerimle gördüm, evet-evet. Ama bana inanmıyorlar. Görüyorsun ya, deli olduğumu düşünüyorlar. Onlardan biriyim ama deli. Oysa ben bir zamanlar bizzat Nicolas Sharp'ın tayfasındaki en iyi baskın subayıydım! Ne güzel günlerdi! Ama sonunda pençemi, toynaklarımı ve merceğimi kaybettim, karaya oturdum.\nNe? Ah, evet! Herkes Shark'ın suçlu olduğunu sandı, ama değildi. Hayır-hayır-hayır. Orada bir köpekbalığı dişi vardı, Dodson'ın tılsımı, ama onu oraya koyan Dichoso'ydu.\nMuhtemelen onu Shark'tan çalmıştır, birlikte Fortune adlı firkateynde yol alırlarken. O gün pek iyi uyuyamamıştım ve dışarı çıkıp biraz dolaştım. Dichoso'nun gizlice Sharp'ın konutuna girdiğini gördüm, birinin çığlık attığını, sonra da inlediğini duydum. Çok geçmeden Dichoso konuttan çıktı, elleri kan içindeydi.\nBana inanmadılar, hayır-hayır. Çünkü o gün adada Dichoso yokmuş, ama Shark varmış. Ve onun dişini bulmuşlar. Ama ben Dichoso'yu gördüm, bundan eminim. O gün orada olduğunu kimse bilmiyordu. 'Şanslı' çok kurnaz ve korkutucu bir adam...";
			link.l1 = "Dichoso'ya 'Şanslı' diyen ilk kişi sen değilsin. Neden böyle diyorlar? Bu onun lakabı mı?";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "İspanyolca bilmiyor musun, adamım? 'Dichoso' papazların dilinde 'şanslı' demek. Şanslı Miguel, Şanslı Miguel. Adı bu anlama geliyor.";
			link.l1 = "Şanslı Miguel mi?... Hm. Bu bana bir şeyi hatırlattı. Hm. Bu ifade bana çok tanıdık geliyor...";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Her ne kadar soyadı Dichoso olsa da, yine de İspanyol olduğunu sanmıyorum. Hayır, hayır. O İspanyol değil. Gerçi İspanyola benziyor.";
			link.l1 = "O halde ne olabilir? İngiliz mi, Fransız mı?";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "Ben bundan bahsetmiyorum, Denizci... Ah, affedersiniz, Kaptan. Evet, Dichoso Fransızca'yı harika konuşur, sizden aşağı kalmaz. İngilizce de öyle. Ama onun damarlarında Kızılderili kanı akıyor. Hayatımda böyle çok insan gördüm. Anlamak kolay değildir, ama o bir melez. Size garanti ediyorum.";
			link.l1 = "Yerli dili konuşabiliyor mu?";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			dialog.text = "Kim bilir, belki de biliyordur. Aslında, dur. Biliyor! Sürekli tuhaf bir dilde garip cümleler söylerdi, bunları söylerken de korkutucu bir bilge gibi yüzünü buruşturup yanaklarını şişirirdi. Mesela şöyle derdi: cogito ergo sum! Sonra gözlerini devirip denizcilerin tepkisini izlerdi. Ya da şöyle bağırırdı: aut Caesar, aut nihil! Daha başka bir sürü şey de geveliyordu. Hepsini hatırlamıyorum.";
			link.l1 = "Bu bir Kızılderili dili değil. Bu Latince. Latince... Latince mi?! Kahretsin!";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "Neden bu kadar tedirginsin, adamım? Neden bağırıyorsun? Yılan mı ısırdı seni yoksa? Nereye gitti?";
			link.l1 = "Neden en başından göremedim ki! Her şey gözümün önündeydi! Latince! Miguel... Şanslı Miguel!!!";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			dialog.text = "Hey, dostum. Artık bağırmayı keser misin? Herkes bize bakıyor. Neyin var senin, Denizci... pardon, Kaptan?";
			link.l1 = "Miguel Dichoso'nun gerçekte kim olduğunu biliyorum. O İspanyol değil. Fransız! Ah, nasıl da körmüşüm!";
			link.l1.go = "tieyasal_14";
		break;
		
		case "tieyasal_14":
			dialog.text = "Yok canım, aptal. O Fransız değil. Melez o. Beyaz babası, Karayiplerden bir Arawak ya da Miskito kızıyla, belki de bir Itza'yla birlikte olmuş, işte Kutsal Miguel Dichoso böyle gelmiş dünyaya. Sen fark etmiyorsun ama ben görüyorum. Gözlerinde yazılı...";
			link.l1 = "Onun nereden geldiğini bir kenara bırakalım şimdi. Nerede o, Abraham?! Burada mıydı?!";
			link.l1.go = "tieyasal_15";
		break;
		
		case "tieyasal_15":
			dialog.text = "Şşş... Evet, buradaydı. Ama gitti. Artık Isla Tesoro'da değil.";
			link.l1 = "Buraya neden geldi? Ne tür bir gemisi var?";
			link.l1.go = "tieyasal_16";
		break;
		
		case "tieyasal_16":
			dialog.text = "Gemi bir kalyon. Büyük bir savaş kalyonu. Buraya neden geldi... Şey, etrafta dolanıp sorular soruyordu. Ama konuşmalarını duydum, evet, evet! Bir Charles de Maure'u arıyordu. Evet, aynen öyle. Charles de Maure. Dur, bu sensin, Charles de Maure! Seni arıyordu, dostum.";
			link.l1 = "Ne için olduğunu biliyor musun?";
			link.l1.go = "tieyasal_17";
		break;
		
		case "tieyasal_17":
			dialog.text = "Yani, kesinlikle meyhaneye uğrayıp seninle rom içmek için gelmedi. Seni yakalamayı planlıyordu. Evet, evet! Seni yakalamak! Başın belada kaptan!";
			link.l1 = "Hiç şüphem yok...";
			link.l1.go = "tieyasal_18";
		break;
		
		case "tieyasal_18":
			dialog.text = "Ya sen? Onu neden arıyorsun? Ah, anladım, anladım: onu öldürmek için! Öldür onu, öldür o herifi! Blaze Sharp'ın intikamını al! Blaze harika bir adamdı. Onu hatırlıyorum, çocukken bile tıpkı Nicholas gibiydi.";
			link.l1 = "Dichoso nereye gitti?";
			link.l1.go = "tieyasal_19";
		break;
		
		case "tieyasal_19":
			dialog.text = "Blueweld'e gidiyordu. Charles de Maure'un Orman Şeytanı'nın himayesinde aranması gerektiğini söyledi. Ama adamlarını burada bıraktı... Dur. Sanırım çoktan fark edildin!";
			link.l1 = "Beni kim fark etti?";
			link.l1.go = "tieyasal_20";
		break;
		
		case "tieyasal_20":
			dialog.text = "Dichoso'nun adamları. Sana burada göz kulak olmalarını emretti. Ah, biliyorum, biliyorum! Dikkatli ol, kaptan: Isla Tesoro'nun kayalıkları gemilerle çevrili ve orada senin kafanı bekliyorlar. Kaptan tilki kadar kurnaz. Sakın kandırılma.";
			link.l1 = "Deneyeceğim...";
			link.l1.go = "tieyasal_21";
		break;
		
		case "tieyasal_21":
			dialog.text = "Ve bir şey daha: Al, süvarı kılıcımı sana veriyorum. Al, al. İhtiyacın olacak. Bu, Kaptan Barbarigo'nun kendi kılıcıdır. Mükemmel bir silahtır. Tüm takımadadaki en iyisi. Çekinme, al. Blaze Sharp'ın intikamı alınacak!";
			link.l1 = "Teşekkür ederim, Abraham.";
			link.l1.go = "tieyasal_22";
		break;
		
		case "tieyasal_22":
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveItems(npchar, "blade_29", 1);
			sTemp = GetBestGeneratedItem("blade_29");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			GiveItem2Character(npchar, "blade_19"); 
			EquipCharacterbyItem(npchar, "blade_19");
			Log_Info("You've received Barbarigo's sword");
			PlaySound("interface\important_item.wav");
			dialog.text = "Şimdi git. Git, izleniyorsun. Akıllıymış gibi davran. Ya da aptal. Fark etmez. Sadece dikkatli ol!";
			link.l1 = "Teşekkürler dostum. Bana ne kadar yardımcı olduğunu bile bilmiyorsun. İyi şanslar!";
			link.l1.go = "tieyasal_23";
		break;
		
		case "tieyasal_23":
			DialogExit();
			pchar.questTemp.Tieyasal.MigelKnow = "true";
			AddQuestRecord("Tieyasal", "4");
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
			pchar.questTemp.Tieyasal = "islatesoro";
		break;
		
		case "fight":
			iTemp = 20-sti(GetCharacterItem(npchar, "potion2"));
			TakeNItems(npchar, "potion2", iTemp);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
