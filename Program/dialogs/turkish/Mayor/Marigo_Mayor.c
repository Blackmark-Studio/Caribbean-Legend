// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne istiyorsunuz? Sorunuzu sorun.","Dinliyorum, sorunuz nedir?"),"Bu, ikinci kez sormaya çalıştığınız oldu...","Bu üçüncü kez sormaya çalışıyorsun...","Bu ne zaman bitecek?! Ben meşgul bir adamım, koloni işleriyle uğraşıyorum, sen ise hâlâ beni rahatsız ediyorsun!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şimdi değil. Yeri ve zamanı değil."),"Doğru... Ama sonra, şimdi değil...","Soracağım... Ama biraz sonra...","Üzgünüm, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToGovernor")
			{
				link.l1 = "Majesteleri, size son derece önemli ve harika bir haberim var! Portekizli Bartolomeo'yu yakaladım, o alçak şu anda gözetim altında ve adil bir yargılamayı bekliyor! Ve Şirket'ten mütevazı bir minnettarlık umuyorum...";
				link.l1.go = "Portugal";
			}
			//Португалец
			
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "governor")
			{
				link.l1 = "Beni görmekte ısrar ettiniz, Sayın Vali...";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_battle_complete")
			{
				link.l1 = "İngiliz casusları meselesiyle ilgili olarak buradayım, Sayın Vali...";
				link.l1.go = "FMQN_7";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Zaten her şeyi aldınız. Daha ne istiyorsunuz?","Henüz el koymadığın bir şey kaldı mı?");
            link.l1 = RandPhraseSimple("Sadece etrafa bakıyorum...","Sadece kontrol ediyorum, bir şeyi almayı unutabilirim...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//Jason, Португалец
		case "Portugal":
			dialog.text = "Bartolomeo... Bart Portekizli benim şehrimde mi?! Hayatta mı?!!";
			link.l1 = "Evet, Ekselansları, ve güvenilir bir muhafızın gözetiminde. Bart'ın başı için Şirket tarafından vaat edilen ödülü aldıktan sonra onu size teslim edeceğim. Altın doblonlar da olur...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Bill, dublonlar mı? Aklını mı kaçırdın?! Bu canavarı kasabama getirmeyi nasıl düşündün?! Eğer o buradaysa, onun fırkateyni de adadan çok uzakta değildir ve mürettebatı şu anda kasabanın içinde olabilir!";
			link.l1 = "Onunla birlikte olanları öldürdüm, diğerleri hakkında bir fikrim yok, ama sanırım bunun pek bir önemi yok çünkü Bartolomeo...";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Evet, öyle! Gerçekten ne yaptığının farkında değil misin?! 'Albatros' adanın yakınında ve sen, kendi kana susamış tayfasını bile korkutan korsanı yakaladın! Buradan git! Adadan uzaklaş! Ve bu canavarı da yanında götür!";
			link.l1 = "Ama dinleyin, ya vaat edilen ödül ve...";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "Şehrimin senin açgözlülüğün ve Şirket’in intikam hırsı yüzünden yanmasını istemiyorum! Kaledeki askerlerimin hepsi yeni, yarısı da ravelinlere kim ve neden saldırıyor öğrenince hemen kaçacak! Sonra da katliam başlayacak... Bunu göze alamam, anladın mı?! Defol git ve eğer Şirket onun başını bu kadar çok istiyorsa, kendin götür onu Curaçao’ya!\nHemen yap bunu, çok geç olmadan! Onunla ne yapmak istiyorsan yapabilirsin, ister geminin güvertesinden at, ama sakın bunu şehrimde yapma!\nHans! Hans, neredesin, tembel aptal! Bana bir kediotu iksiri falan getir, ve Tanrı aşkına, biri şu maceraperesti konutumdan atsın artık!";
			link.l1 = "Ama Majesteleri...";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Marigo_town", "reload", "reload3_back", "PortugalOutResidence");
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Pekâlâ! Söyleyin bana kaptan, adamız yaklaşırken herhangi bir İngiliz askeri ya da ticaret gemisiyle karşılaştınız mı?";
			link.l1 = "Hayır, Efendim. Sularınızda İngiliz bayrağı taşıyan ne askeri ne de ticari gemi gördüm.";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Anlıyorum. Burada ne kadar kalmayı düşünüyorsunuz?";
			link.l1 = "Üç gün kadar...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "In that case, I have an offer for you. According to our intelligence, there is a risk of English spies here. I will give ten thousand pesos as a reward for any information regarding suspicious vessels or people on the island, in the town, its vicinity, on the shores, etc. The reward will be significantly increased if you assist the authorities in detaining or eliminating an enemy.\nEvery civilian captain is welcome to take part in the investigation and to patrol the local shores and jungle in search of spies.\nIt's possible that you'll encounter our military corvette, the Zeepard; don't be alarmed, it is on patrol. You are free to approach its captain if you find any Brits.";
			link.l1 = "Ne yazık ki, Ekselansları, buraya yalnızca barışçıl ticaret niyetiyle geldim. Erzakımı tazeleyip işlerimi bitirir bitirmez bu adadan ayrılmak zorundayım.";
			link.l1.go = "FMQN_3";
			link.l2 = "Cazip bir teklif! Sanırım katılıp adanızın sularını ve kıyılarını yağmalayacağım. Belki burada bir süre kalırım bile.";
			link.l2.go = "FMQN_5";
		break;
		
		case "FMQN_3":
			dialog.text = "Bu sadece bir bilgi, kaptan. Hiçbir baskı yok. Şüpheli bir şey görürseniz, kime başvuracağınızı biliyorsunuz.";
			link.l1 = "Pekâlâ, Efendim, anladım. Elveda!";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			DialogExit();
			pchar.questTemp.FMQN = "way_eng_1";
			AddQuestRecord("FMQ_Nevis", "8");
			chrDisableReloadToLocation = false;
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_5":
			dialog.text = "Harika, kaptan! Madem bu kadar ciddisiniz, komutanımızla da mutlaka konuşun. Casusları yakalamaktan sorumlu ve size ek bilgiler verebilir.";
			link.l1 = "Pekâlâ, Mösyö. Onu görmeye gideceğim.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			DialogExit();
			pchar.questTemp.FMQN = "way_div";
			AddQuestRecord("FMQ_Nevis", "9");
			chrDisableReloadToLocation = false;
			AddLandQuestMarkToPhantom("marigo_prison", "marigoJailOff");
		break;
		
		case "FMQN_7":
			DelLandQuestMark(npchar);
			dialog.text = "Sizi bekliyorduk, Bayım "+GetFullName(pchar)+". Allow me to express our gratitude for your actions in eliminating the dangerous English raiding party. Please accept these ten thousand pesos. In addition: 200 ship's silk will be loaded into your hold, and a very special reward — a three-year license from the Dutch West India Trading Company. This is an extremely valuable document; I trust you know that?";
			link.l1 = "Elbette! Üç yıllık bir ruhsat - bu gerçekten büyük bir şey.";
			link.l1.go = "FMQN_8";
		break;
		
		case "FMQN_8":
			dialog.text = "Lütfen, ödülünüzü alın. Ayrıca, tüm Hollanda vatandaşlarının ve yetkililerinin minnettarlığına güvenebilirsiniz. Philipsburg'da bir sansasyon oldunuz, sizi tekrar görmekten memnuniyet duyarız.";
			link.l1 = "Böylesine içten sözler duymak, ruhsattan daha değerli. Teşekkür ederim, bu bir zevkti. Şimdi ise yoluma devam etmeliyim. Hoşça kalın!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandBattleComplete");
		break;
		
		// Jason НСО
		case "tomas":
			dialog.text = "Teslim oluyoruz! Kutsal olan her şey adına yalvarıyorum, lütfen Philipsburg'u ve vatandaşlarını yağmalamayın! Taleplerinizi dinlemeye hazırım!";
			link.l1 = "Vatandaşlar için endişelenmeyin, Efendim. Fransız Tacı'nın tebaası Fransız askerlerinden korkmamalı.";
			link.l1.go = "tomas_1";
		break;
		
		case "tomas_1":
			dialog.text = "Fransız Kraliyeti mi?";
			link.l1 = "Kesinlikle. Bu ada Fransa'ya aittir ve siz burada sadece kiracısınız. Kendisini bu adanın sahibi sanan küstah kiracılar. Bugünden itibaren, Saint Maarten'daki Hollanda otoritesi sona ermiştir. Anlaşıldı mı?";
			link.l1.go = "tomas_2";
		break;
		
		case "tomas_2":
			dialog.text = "Ama... Ama bize, sana teslim olan Hollandalı askerlere ve yaralılara ne olacak? Ya sonra...";
			link.l1 = "Bu tamamen size bağlı olacak, Bay Thomas. Eğer bana bir iyilik yaparsanız, teslim olanların hepsinin yaralılarını alıp buradan limanda bulacağımız bir ya da birkaç gemiyle Curaçao'ya, Bay Stuyvesant'a gitmelerine izin vereceğim.";
			link.l1.go = "tomas_2_1";
		break;
		
		case "tomas_2_1":
			dialog.text = "";
			link.l1 = "Aksi takdirde, gemilerimin ambarlarında ve Saint Kitts'in zindanlarında tutulacaksınız. Ayrıca, Stuyvesant'ın kolonilerimizi fethetme hevesini kaybetmesini sağlamak için bazı önemli Hollandalı yetkililerin de asılması gerekecek...";
			link.l1.go = "tomas_3";
		break;
		
		case "tomas_3":
			dialog.text = "(kekelemeyerek) N-n-ne... Ne... ne t-tür b-bir i-iyilik... t-tale... p ediyorsunuz?";
			link.l1 = "Adanın derinliklerinde bir anlaşmazlık kaynağı yatıyor - bir tuz madeni. Orada sadece madenciler ve köleler değil, aynı zamanda tepeden tırnağa silahlı Hollandalı askerler de olduğunu biliyorum. Bunlar Şirket Muhafızlarından olmalı, değil mi, Mynheer? Onlara teslim olma şansı sunacağım, reddederlerse zor kullanacağım. Madene giden yolu bana gösterebilecek bir rehbere ihtiyacım var. Bana böyle bir rehber bul.";
			link.l1.go = "tomas_4";
		break;
		
		case "tomas_4":
			dialog.text = "T-Tuz... m-madeni mi?";
			link.l1 = "Exactly. Don't be afraid, Mynheer Thomas, if the guards of the mine are wise enough to give up their arms, I will give them an opportunity to leave the island. I don't need unnecessary bloodshed. Don't worry, your conscience will be clear: even if you don't tell me where the mine is, the island of Saint Maarten is small enough that I can find the mine without your help; I just don't want to waste my time rambling through thickets and marshes. So this deal is more profitable to you than it is to me.";
			link.l1.go = "tomas_5";
		break;
		
		case "tomas_5":
			dialog.text = "Ta-tamam... Madene nasıl gideceğinizi söyleyeceğim, a-ama bana söz verin ki... hepimiz bu adadan ayrılacağız!";
			link.l1 = "Bir subay ve asilzade olarak size söz veriyorum.";
			link.l1.go = "tomas_6";
		break;
		
		case "tomas_6":
			dialog.text = "Grand Case koyunda... en uçta, suyun hemen yanında... taşlar var. Orada... orada, onların arkasında, kıyı boyunca, suyun kenarından bir geçit var, orada... orası sığ, bel hizasında ya da daha az. Kayayı dolaşman gerekiyor ve büyük bir kumsala ulaşacaksın, orada... orada gemini yanaştıramazsın çünkü etrafı resiflerle çevrili. Bu kumsaldan doğrudan... madene... giden bir patika var.";
			link.l1 = "Mükemmel. Ben yola çıkıyorum. Ve siz, Mösyö, ben dönene kadar askerlerimin dikkatli gözetimi altında burada kalacaksınız.";
			link.l1.go = "tomas_7";
		break;
		
		case "tomas_7":
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			LAi_SetActorType(npchar);
			pchar.quest.Patria_BastionGate.win_condition.l1 = "location";
			pchar.quest.Patria_BastionGate.win_condition.l1.location = "Shore40";
			pchar.quest.Patria_BastionGate.function = "Patria_BastionShore";
			AfterTownBattle();
			AddQuestRecord("Patria", "50_1");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
