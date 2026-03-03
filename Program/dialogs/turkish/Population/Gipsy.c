//Jason общий диалог цыганок
// ugeen <-- добавил продажу мышьяка из под полы
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int poison_price;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ah, merhaba, canım. Ne istiyorsun?";
			link.l1 = "Sanırım hiçbir şey.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("Sana bir sorum var.","Bilgiye ihtiyacım var.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Sevgilim, biraz altın paylaşır mısın? Sana geleceğini söyleyeceğim.","Hey, denizci, öyle aceleyle gitme! Geleceğini öğrenmek ister misin?","Bana biraz tütün ve birkaç gümüş ver, cesur delikanlı. Geleceğine bir göz atayım. (göz kırpar) Gizli çingene büyüsünden biraz duymak ister misin?");
				link.l1 = "Üzgünüm, ama gitmem gerekiyor.";
				link.l1.go = "exit";
				// --> мангароса
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Dinle, tamirci hanım, senin halkının iksirler ve zehirler konusunda uzman olduğunu biliyorum. Bu bitkiyle ilgilenebileceğini söylediler. Bir bak bakalım. Ne düşünüyorsun?";
					link.l5.go = "mangarosa";
				}
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy_trade" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Hey, kara gözlüm, sana bir şeyim var... Bu mangarosa. Almak ister misin?";
					link.l5.go = "mangarosa_trade1";
				}
				// <-- мангароса
				link.l2 = "Falımı bakabilir misin?";
				link.l2.go = "guess";
				link.l3 = RandPhraseSimple("Sana bir sorum var.","Bilgiye ihtiyacım var.");
				link.l3.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
			}
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_Start") && !CheckAttribute(pchar, "questTemp.DWH_gipsy") && npchar.city == "SentJons")
			{
				link.l6 = "Hastalara bakan bir çingene kadın arıyorum. O siz misiniz?";
				link.l6.go = "dwh_ne_ta";
			}
			// <-- Тёмные воды исцеления

			if (!CheckAttribute(npchar, "quest.poison_price") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && rand(2) == 0)
			{
				link.l4 = "Hey, kara gözlüm, fareler için zehrin var mı? Gemimde başıma bela oldular.";
				link.l4.go = "get_poison_1";
			}
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------------гадание-------------------------------------------------
		case "guess":
			dialog.text = "Elbette, yakışıklı. Bana biraz para ver ve sağ elini göster. Sana geleceğini anlatayım, felaketten nasıl kaçınacağını söyleyeyim. Asla hile yapmam! Memnun kalmazsan paranı geri alırsın!";
			link.l1 = "Sanırım tam da burada yoldaşın cebimi boşaltacak... Fikrimi değiştirdim. Keyfim yok.";
			link.l1.go = "exit";
			link.l2 = "Ne kadar para istiyorsun?";
			link.l2.go = "guess_1";
		break;
		
		case "guess_1":
			dialog.text = "Ah canım, keseniz ne kadar elverirse ve gönlünüz ne kadar isterse. Sekizlikleriniz ne kadar çok olursa, geleceği o kadar ileriden görebilirim!";
			link.l1 = "100 peso";
			link.l1.go = "guess_rate_1";
			link.l2 = "500 peso";
			link.l2.go = "guess_rate_2";
			link.l3 = "1000 peso";
			link.l3.go = "guess_rate_3";
			link.l4 = "5000 peso";
			link.l4.go = "guess_rate_4";
		break;
		
		sTemp = GuessText();
		case "guess_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Ah, cömertliğin için teşekkür ederim, yakışıklı genç şahinim! Şimdi dinle:  "+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! Bu gerçekten ilginç. Bunu düşüneceğim...","Gerçekten mi? Bunu düşüneceğim...","Gerçekten mi? Ciddi misin? Bunu aklımda tutacağım...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Seni bekleyen en çirkin ve kaçınılmaz talihsizliktir. Alay edeni lanetle! Üstünde kara bulutlar toplansın ve cezan seni bulsun!";
				link.l1 = "Ha-ha! Gerçekten sana para vereceğimi mi sandın, seni çingene cadısı? Çekil önümden! Engizisyon'un seni yakalamasını dilerim!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_2"://немного в везение или скрытность
			if (sti(pchar.money) >= 500)
			{
				AddMoneyToCharacter(pchar, -500);
				dialog.text = "Ah, teşekkür ederim, yakışıklı genç şahinim! Şimdi dinle:"+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! Bu çok ilginç. Bunu aklımda tutacağım...","Gerçekten mi? Bunu düşüneceğim...","Gerçekten mi? Ciddi misin? Peki, bunu aklımda tutacağım...","Hey, kendimi şimdiden daha iyi hissediyorum!");
				link.l1.go = "exit";
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 30+rand(10));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 30+rand(10));//скрытность
			}
			else
			{
				dialog.text = "Seni bekleyen en çirkin ve kaçınılmaz talihsizliktir. Alay edeni lanetle! Kara bulutlar üstünde toplansın, cezan seni bulsun!";
				link.l1 = "Ha-ha! Gerçekten sana para vereceğimi mi sandın, seni çingene cadısı? Çekil önümden! Engizisyonun seni almasını dilerim!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_3"://здоровье + везение или скрытность, харизма
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "Ah, gümüşlerin için teşekkür ederim, yakışıklı genç şahinim! Şimdi dinle:"+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! Bu gerçekten ilginç. Bunu bir düşüneceğim...","Gerçekten mi? Bunu düşüneceğim...","Gerçekten mi? Ciddi misin? Bunu aklımda tutacağım...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 1);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 50+rand(20));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 50+rand(20));//скрытность
			}
			else
			{
				dialog.text = "Seni bekleyen en çirkin ve kaçınılmaz talihsizliktir. Alay edeni lanetle! Üstünde kara bulutlar toplansın, cezan seni bulsun!";
				link.l1 = "Ha-ha! Gerçekten sana para vereceğimi mi sandın, seni çingene cadısı? Çekil önümden! Engizisyonun seni yakalamasını dilerim!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_4"://умения в оружие, везение+скрытность, здоровье, харизма
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "Oh la la! Cömertliğin için teşekkür ederim, yakışıklı genç şahinim! Şimdi dinle:"+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! Bu oldukça ilginç. Bunu bir düşüneceğim...","Gerçekten mi? Bunu düşüneceğim...","Gerçekten mi? Ciddi misin? Bunu aklımda tutacağım...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 2);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCharacterExpToSkill(pchar, "Fortune", 50+rand(100));//везение
				AddCharacterExpToSkill(pchar, "Sneak", 50+rand(50));//скрытность
				AddComplexSelfExpToScill(20, 20, 20, 20);
			}
			else
			{
				dialog.text = "En çirkin ve kaçınılmaz talihsizlik seni bekliyor. Alay edene lanet olsun! Kara bulutlar tepende toplansın ve ceza seni bulsun!";
				link.l1 = "Ha-ha! Gerçekten sana para vereceğimi mi sandın, seni çingene cadısı? Çekil önümden! Engizisyon'un seni almasını dilerim!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_exit":
			DialogExit();
			AddCharacterHealth(pchar, -10);
			LAi_CharacterDisableDialog(npchar);
		break;
//<-- гадание

// --> продажа мышьяка
		case "get_poison_1" :
			npchar.quest.poison_price = (hrand(3) + 1) * 10;
			if(hrand(10) == 3 || IsCharacterPerkOn(pchar, "Trustworthy"))
			{				
				dialog.text = LinkRandPhrase("Ah, emin değilim, yakışıklı! Kısa bir süre önce biri fareleri öldürmek için yardım istiyordu, sonra da birisi kalede askerleri zehirledi. Muhafızlar katili bulana kadar iki hafta boyunca bizi sorgularken, adadaki bizimkiler için işler epey karıştı. Katil bir düşman casusuydu.","Peki, niyetinden nasıl emin olabilirim? Belki de sadece bir soyluyu, onurlu bir düelloda karşısına çıkmaya cesaret edemediğin için zehirlemek istiyorsun?","Birinin handa bir tüccarı zehirleyip bütün eşyalarını çaldığını duydum. Adam ölmeden önce uzun süre acı çekmiş. Ağzından köpükler çıkmış, patlıcan gibi mosmor olmuş... Bunun sorumlusu sen misin, sevgilim?");
				link.l1 = "Siz çingene kadınları gerçekten de fikirlerinizi paylaşmayı seviyorsunuz! Merak etme kızım, kimseyi zehirleyecek değilim. O, kadınların öldürme yöntemi, bana göre değil. Erkekler için kılıcım var, ama şu lanet olası farelerle baş edemiyorum.";
				link.l1.go = "get_poison_2";
				if (IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(true, "Trustworthy");
			}
			else
			{
				dialog.text = "Beni tuzağa düşürmeye çalışıyorsunuz! Hayır efendim, zehirim yok. Bitkilerim ve iksirlerim var, ama zehirim yok.";
				link.l1 = "Peki o zaman. Bana nazar değmesin.";
				link.l1.go = "exit";
				Notification_Perk(false, "Trustworthy");
			}	
		break;
		
		case "get_poison_2" :
			dialog.text = "Ah, ne kadar yakışıklı ve cesur bir adamsınız! (fısıldayarak) Bana ödeme yapın "+sti(npchar.quest.poison_price)+" dublon.";
			if (PCharDublonsTotal() >= sti(npchar.quest.poison_price))
			{				
				link.l1 = "Pahalı... Umarım bu işe yarar.";
				link.l1.go = "get_poison_4";
			}
			else
			{
				link.l1 = "Olmaz! Ben aynısını memlekette beş pistoleye aldım! O paraya bütün fareleri kendim yakalarım!";
				link.l1.go = "get_poison_3";
			}
		break;
		
		case "get_poison_3" :
			dialog.text = "O zaman kendin yakala onları ve beni rahatsız etme. Bir dahaki sefere muhafızı çağıracağım.";
			link.l1 = " Muhafızlara gerek yok, cadı, gidiyorum. ";
			link.l1.go = "exit";
		break;
		
		case "get_poison_4" :
			PlaySound("interface\important_item.wav");
			RemoveDublonsFromPCharTotal(sti(npchar.quest.poison_price));
			TakeNItems(pchar, "rat_poison", 1);
			DialogExit();
		break;
// <-- продажа мышьяка

	// --> Мангароса
		case "mangarosa":
			dialog.text = LinkRandPhrase("Bitkiyi göster bana, sevgili... Hm... Sanırım bunu senden satın alabilirim. Üç yüz sekizlik, anlaştık mı?","Bana orayı göster, yakışıklı... Heh... Pekâlâ, bunun için iki yüz elli ödeyebilirim.","Bakalım... Ah! İlginç bir örnek! İki yüz peso! Anlaştık mı?")"";
			link.l1 = LinkRandPhrase("Aman Tanrım... kara gözlüm, ben köyden gelmiş biri değilim. Bu bitkiyi tanıyorum. Bu mangarosa...","Gerçekten mi?! Bu mangarosa'nın kusursuz bir örneği. Beni kandırmaya çalışma, çingene.","Aha, ve sen bu mangarosayı bu kadar az bir paraya vereceğimi mi sanıyorsun.");
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			dialog.text = "Pekala, pekala, yakışıklı. Bu bitki hakkında bir şeyler bildiğini görüyorum. Elli doblon. Ver onu bana.";
			link.l1 = "Dur hele! Bunun nasıl kullanılabileceğini ve ne işe yaradığını öğrenmek istiyorum. Bana bundan bahsedebilir misin? Sizin halkınız bu küçücük çalı için bir yığın altın ödemeye razı!";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			// тут работает харизма
			if (sti(pchar.questTemp.Mangarosa.g_count) == 5 || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 10+hrand(25)+hrand(30, "1"))
			{
				dialog.text = "Hm... Sanırım sana biraz anlatmamda bir sakınca yok. Bu bitkiyle özel yeteneklerin olmadan hiçbir şey yapamazsın.";
				link.l1 = "Dinliyorum.";
				link.l1.go = "mangarosa_3";
			}
			else
			{
				dialog.text = LinkRandPhrase("Benim halkım çok altın ödeyebilir, ama asla sırlarını açığa çıkarmazlar.","Altın altındır, sırlar da sırdır, delikanlı... ","Evet, ödemeye razıyız, ama anlatmaya değil.")+"Yani bana mangarosanı satacak mısın? Elli doblon bizim bunun için verdiğimiz fiyattır, kimse sana daha fazlasını ödemez.";
				link.l1 = "Ah, peki... Bana uyar nasılsa. Elli doblon. Al bakalım";
				link.l1.go = "mangarosa_trade";
				link.l2 = "Beni anla, onu satmak istemiyorum. Neden ihtiyacın olduğunu bilmek istiyorum. Bilgini benimle paylaş, sana bedava vereyim.";
				link.l2.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_trade":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Al paralarını al, genç şahin. Bir de, bu bitkilerden bize daha fazla getir. Ama biz onları sadece birer birer alabiliriz, çünkü yanımızda büyük paralar taşımıyoruz. Muhafızlar bizim gibileri pek sevmez, fırsat buldukça da başımıza bela olurlar...";
			link.l1 = "Pekala. Daha fazlasını bulursam, getiririm.";
			link.l1.go = "mangarosa_trade_exit";
		break;
		
		case "mangarosa_trade_exit":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "gipsy_trade";
			AddQuestRecord("Mangarosa", "3");
		break;
		
		case "mangarosa_exit":
			dialog.text = LinkRandPhrase("Olmaz! Satmak istemiyorsan, satma. Sana hiçbir şey söylemem.","Sırlarımızı bir yabancıya açıklamam! (tükürür) Satmak istemiyor musun? Cehenneme git o zaman.","Dostum, bu senin kulağına göre değil. Elli dublona satmak istemiyor musun? Git, ticaret kızına iki yüz pesoya sat.");
			link.l1 = LinkRandPhrase("O zaman senin için kötü oldu! Zaten tayfanın başka biri bana anlatacak bunu. Ve o kişi de bu bitkiyi hediye olarak alacak. Görüşürüz!","Neden bu kadar inatçısın? Eğer bana söylemezsen, o zaman diğeri anlatır. Ve bu mangarosayı hediye olarak o alır. Hoşça kal.","Nefesin sarımsak kokuyor. Sonunda istediğimi alacağım. Senin gibilerden biri daha konuşkan olur ve bitkiyi bedavaya alır. Görüşürüz.");
			link.l1.go = "exit";
			npchar.quest.mangarosa = "true";
			pchar.questTemp.Mangarosa.g_count = sti(pchar.questTemp.Mangarosa.g_count)+1;
		break;
		
		case "mangarosa_trade1":
			dialog.text = "Ve neden soruyorsun, şahin?! Elbette! Ver onu bana.";
			link.l1 = "Bana elli dublon ver.";
			link.l1.go = "mangarosa_trade1_1";
			link.l2 = "Ah! Sanırım onu kaybettim ya da gemimde unuttum. Ne yazık. Hoşça kal...";
			link.l2.go = "exit";
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_trade1_1":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Merak etme, seni kandırmayacağım. Al paralarını.";
			link.l1 = "Mangarosanı al. Eğer bulursam, daha fazlasını getiririm.";
			link.l1.go = "exit";
		break;
		
		case "mangarosa_3":
			dialog.text = "Tomurcukları özel bir şekilde öğütür, sonra kuruturuz, tohumlarını ve saplarını ayıklarız, ardından tütünle karıştırır, pipolarımıza basar ve karışımı içeriz. Sonra da... unutulmaz bir etki yaşarız. Alkol sarhoşluğuna benzer, ama ertesi gün baş ağrısı olmadan. Bir bitki, yirmi kadar pipo doldurmaya yeter.";
			link.l1 = "Şimdi anladım! Bana bu gizli tekniği öğretebilir misin? Sana iyi bir ödeme yapabilirim...";
			link.l1.go = "mangarosa_4";
		break;
		
		case "mangarosa_4":
			dialog.text = "Genç şahin, bana güven, buna ihtiyacın yok. Bulaşma, o bitki seni mahveder. Zihni köreltir, insanı tembelleştirir. Bana bile sorma. Ama... karşımda cesur bir adam görüyorum, kılıcıyla, denizin adamı... belki de bir kaptan?";
			link.l1 = "Haklısın.";
			link.l1.go = "mangarosa_5";
		break;
		
		case "mangarosa_5":
			dialog.text = "O halde dinle. Mangarosa çok daha asil amaçlar için kullanılabilir ve senin de işine yarayabilir. Şifacılarımızdan biri onun tüm sırlarını biliyor. İhtiyacın olan kişi o.\nBitkiyi bana ver, sana adını ve nerede bulacağını söyleyeyim. Sırlarını seninle paylaşmaya ikna etmek ise senin sorunun olacak.";
			link.l1 = "Pekala. Bitkiyi al ve bana çingene büyücünü nasıl bulacağımı söyle.";
			link.l1.go = "mangarosa_6";
		break;
		
		case "mangarosa_6":
			RemoveItems(pchar, "cannabis7", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Adı Amelia. Akıllı insanların dediğine göre, İspanyol Ana Karası'nın güneybatı kıyısında, denize pek de uzak olmayan kumullar arasında küçük bir evde tek başına yaşıyor.";
			link.l1 = "Aman Tanrım, lütfen biraz daha açık olabilir misin?";
			link.l1.go = "mangarosa_7";
		break;
		
		case "mangarosa_7":
			dialog.text = "Sen bir denizcisin, cesur bir şahinsin, ben ise değilim. Sana söylediğim yerde onu ara. Onun evi deniz kıyısına çok yakın. İspanyol Sahili'nin güneybatısındaki bir koyun yakınında – denizciler orayı bilir.";
			link.l1 = "Pekala, bulmaya çalışacağım...";
			link.l1.go = "mangarosa_8";
		break;
		
		case "mangarosa_8":
			dialog.text = "Ona bir Mangarosa götür yoksa seninle konuşmaz bile. Yanında mutlaka birkaç doblon da bulunsun, sakın bedavaya sana bir şey öğreteceğini sanma!";
			link.l1 = "Böylesine açgözlülük. Bunu düşüneceğim. Hikayeni paylaştığın için teşekkürler!";
			link.l1.go = "mangarosa_9";
		break;
		
		case "mangarosa_9":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "amelia";
			pchar.questTemp.Mangarosa.Tell = "true"; // калеуче
			AddQuestRecord("Mangarosa", "4");
			// создаем и ставим Амелию
			sld = GetCharacter(NPC_GenerateCharacter("Amelia", "gipsy_3", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Amelia";
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Mangarosa.c";
			sld.dialog.currentnode = "amelia";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Amelia_house", "barmen", "stay");
		break;
		
		// --> Тёмные воды исцеления
		case "dwh_ne_ta":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "Hayır, "+GetSexPhrase("sevgili","güzellik")+", aradığın kişi ben değilim, o "+sld.name+"Şu anda şehirde. Onu yakın zamanda gördüm.";
			link.l1 = "Teşekkür ederim.";
			link.l1.go = "exit";
		break;
		// <-- Тёмные воды исцеления
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Beni dinle, cesur şahin, ben bir çingene olabilirim ama biz bile açık şiddeti kınarız. Lütfen kılıcını kınına koy.","Beni dinle, cesur şahin, bu kasabanın bir vatandaşı olarak senden kılıcını kınına koymanı istiyorum.");
			link.l1 = LinkRandPhrase("Pekâlâ.","Nasıl isterseniz.","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string GuessText()
{
	string sText;
	switch (hrand(19))
	{
		case 0: sText = "you will have luck, brave young falcon, tomorrow you'll be lucky with cards!" break;
		case 1: sText = "the fortune will be kind with you in your mercantile business, captain!" break;
		case 2: sText = "there is a misfortune awaiting you in the open sea, it's waiting just for you, wait for three days!" break;
		case 3: sText = "I see that you need to seek help from your closest ones, you won't make it alone in your next fight!" break;
		case 4: sText = "go and light a candle in a church, you have been cursed by your enemy. You won't make it without God's help!" break;
		case 5: sText = "you are going to lose a lot soon, my falcon, but don't despair and hope for yourself, seek help from you friends..." break;
		case 6: sText = "a heavy loss is waiting for you in the sea, but I see, that you, captain, will be able to ride it out even if you don't get what you want." break;
		case 7: sText = "you have entered the aim of misfortune, captain! Visit a brothel and have some rest." break;
		case 8: sText = "you will get what you want, captain, but don't expect anything good from it. All what you've wanted so passionately, captain, will bring only bad things so you'd better change your plans away." break;
		case 9: sText = "I see that there is a sign on that face of yours, the sign of ultimate luck. You will get more than you're expecting to get, young man!" break;
		case 10: sText = "you need to evaluate your wish once again and decide. Do you really need it? Your fate is giving you a chance to rethink." break;
		case 11: sText = "it's rare luck, not everyday we've getting a chance to rethink. Take a rest for a few days, bright-eyed, think about things. Don't hurry to your death!" break;
		case 12: sText = "though all of your efforts won't give you the expected result, don't despair, young falcon, great luck is waiting for you in the most unexpected day, don't lose it!" break;
		case 13: sText = "your problem won't be solved in a positive way but you are a stubborn one and you'll get what you want but, perhaps, not from the place you've expected." break;
		case 14: sText = "you'd better forget about the business you are up to. You will never be lucky in this and if you'll be continuing in it than, perhaps, your closest people will be hurt or killed." break;
		case 15: sText = "there is an event which is waiting for you, captain, and it will completely change your life. Your recent concerns will lose all of their meaning to you after that." break;
		case 16: sText = "there is danger on your way to your dream, captain, and you must be really lucky if you will be able to get what you want without heavy losses. It's better to turn away and forget your unachievable dream. Or perhaps, this fate could be tricked if you lose in cards or dice right now..." break;
		case 17: sText = "I see a strong power in you like a rock and a light as bright as the north star which leads people. Good news is waiting for you!" break;
		case 18: sText = "a bad sign is rising on your way, fear the evil eye and keep loyal men close to you." break;
		case 19: sText = "a lucky event is rising on your way right behind your own back. Look for the good which is coming right to your hands and don't chase the unachievable." break;
	}
	return sText;
}
