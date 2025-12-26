// колдун ривадос - Чимисет
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bir şey mi istiyorsun?";
			link.l1 = "Hayır, boşver.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//-------------------------------------в тюрьме на Тартарусе-----------------------------
		// вариант R
		case "KillChad":
			dialog.text = "Dur, bekle! Ne olur, beni dinle, korkunç bir hata yapmadan önce.";
			link.l1 = "Dinliyorum...";
			link.l1.go = "KillChad_1";
			LAi_RemoveCheckMinHP(npchar); //убираем проверяльщик, если ещё есть
		break;
		
		case "KillChad_1":
			dialog.text = "Beni öldürmen söylendi, değil mi? Yukarıda Chad'le konuştuğunu duydum. Sana kızmıyorum – sana başka seçenek bırakmadı – ama ben öldükten sonra Chad'in seni bırakacağını düşünmekle yanılıyorsun.";
			link.l1 = "Hm... peki neden yapmasın? Bildiğim tek şey, seni öldürmezsem geleceğim karanlık.";
			link.l1.go = "KillChad_2";
		break;
		
		case "KillChad_2":
			dialog.text = "Beni öldürürsen hiçbir geleceğin olmayacak. Bak, Narvaller ve Chad benim yok olmamı istiyor, ama bunu kendi elleriyle yapmaya korkuyorlar - beni öldüren sonsuza dek lanetlenecek. O yüzden başkasının bunu yapmasını istiyorlar.\nChad senin Rivados olmadığını biliyor. Seni oyuna getiriyor. Beni öldürdüğünde, aynısını sana da yapacaklar ve cesedini Shark'ı kandırmak için kullanacaklar.";
			link.l1 = "Köpekbalığı mı?! Köpekbalığı Dodson? O burada mı? Ve Tanrı aşkına, söyle bana, kim bu Rivados denen herifler?";
			link.l1.go = "KillChad_3";
		break;
		
		case "KillChad_3":
			dialog.text = "Yalan söylemiyordun... gerçekten yenisin burada... hmm... Ama şimdi açıklama zamanı değil! Kaçmamız gerekiyor. Bir planım var, dinler misin?";
			link.l1 = "Hayır. Biliyor musun, büyücü? Az önce mistik bir portaldan geçip sağ çıktım, bu yüzden lanetlerin beni korkutmuyor. Üzgünüm - bunu acısız yapmaya çalışacağım.";
			link.l1.go = "KillChad_fightfail";
			link.l2 = "Pekala, dinleyeceğim. Planın nedir?";
			link.l2.go = "KillChad_4";
		break;
		
		case "KillChad_fightfail":
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "afraid", "", -1);
			LAi_SetImmortal(npchar, false);
			pchar.quest.LSC_fightfail.win_condition.l1 = "NPC_Death";
			pchar.quest.LSC_fightfail.win_condition.l1.character = "Chimiset";
			pchar.quest.LSC_fightfail.function = "LSC_Fightfail_Final";
		break;
		
		case "KillChad_4":
			dialog.text = "There is a chest over there. It contains decent weapons and potions. It is locked, but the lock is old and damaged, so find a crowbar and break it.\nTake everything from the chest, arm yourself, and go to the stairs. It is a good defensive position; they will be forced to fight you one at a time - just watch out for the musketeers.\nI hope that you are good with a blade, I am too old to help you fight. If you manage to kill them all and survive, I guarantee you the protection of the Rivados - my family.";
			link.l1 = "Very well... pray to your gods for me; this fight will not be easy. Those lads upstairs don't look soft.";
			link.l1.go = "KillChad_5";
		break;
		
		case "KillChad_5":
			DialogExit();
			pchar.quest.LSC_fightfail.over = "yes"; //снять прерывание
			LAi_SetImmortal(npchar, true);
			ref location = &Locations[FindLocation(pchar.location)];
			location.private1.key = "crowbar";
			location.private1.key.delItem = true;
			NextDiag.CurrentNode = "KillChad_6";
		break;
		
		case "KillChad_6":
			dialog.text = "Vakit kaybetme! Kilidi zorla, çabuk!";
			link.l1 = "Evet, evet, yapıyorum!";
			link.l1.go = "exit";
			NextDiag.TempNode = "KillChad_6";
		break;
		
		case "Chad_die":
			dialog.text = "Aferin! Gerçekten usta bir savaşçısın. Hayatım sana borçlu, yabancı. Söylesene, adın ne?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+". Peki ya seninki?";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "Ben Chimiset, Rivados'un şamanı ve reisi Kara Eddie'nin danışmanıyım. Beni kurtarıp hayatımı bağışladığını öğrenince Eddie çok sevinecek. Artık hem benim, hem Kara Eddie'nin, hem de tüm Rivados'un dostusun. Bundan böyle Koruyucu'da her zaman hoş karşılanacaksın...";
			link.l1 = "Bekle... Chimiset, hâlâ anlamadıysan söyleyeyim, buraya geleli sadece birkaç saat oldu! Bana nerede olduğumu, şu Rivados'un kimler olduğunu ve Köpekbalığı Dodson'u nerede bulabileceğimi anlatır mısın?";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "This place is called the City of Abandoned Ships - though that name is a mockery; it is not much of a city.\nThis place is an island formed out of hundreds of dead ships. The central wrecks form our dwelling space. The island's inhabitants are people who survived the shipwrecks caused by the storms and currents that circle the island.\nMy Rivados are a clan, a group of free blacks who have been living together for a long time. There are three other groups who live here: the Narwhal clan, descended from the men who brought our African ancestors here; Shark Dodson's pirates; and the commoners, who keep to themselves.\nShark may be considered chief of the island, calls himself 'Admiral.' He arrived quite recently and seized power violently. He captured the San Augustine, where the island stores its provisions. Now, we have to buy our own food back at the prices named by Shark. Based on what I overheard between you and Chad, it seems that you have already been in the pirate warehouse.\nChad Kapper was Shark's boatswain and prison warden. Together with Layton Dexter, Shark's first mate, these men and their pirates formed one of the three controlling powers on the island, together with my Rivados and the Narwhals.";
			link.l1 = "Chad Kapper neden seni öldürmemi istedi?";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "Chad struck a bargain with the Narwhals, the sworn enemies of the Rivados. With their help, he was going to kill Shark and take his place.\nThe Narwhals hold a grudge against the Admiral for the murder of their leader, Alan Milrow. They believe that Shark is responsible, but they are wrong. Chad murdered Alan; I am the sole witness to this crime.\nThat is why Chad wished me dead, yet he feared to do it himself. Pirates are fearless in battle, but they respect big magic. So he tried to use you.\nChad and the Narwhals would have killed Shark and blamed the Rivados.";
			link.l1 = "Neden seni suçlayayım?";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = ""+pchar.name+", sonra konuşalım. Acele etmeliyiz, Köpekbalığı'nın korsanları gelmeden önce. Chad'in cesedini ara ve anahtarlarını al. Masasını da kontrol et, önemli belgeler olabilir.\nKöpekbalığı Dodson'a git, onu adanın kuzey ucundaki büyük gemi San Augustine'de bulacaksın. Oradan Pluto'ya uzanan bir halat köprüsü var. Ona Chad'in ona ihanet etmeyi planladığını, tüm bunların arkasında Narvallerin olduğunu, bizim, Rivadosların, bununla hiçbir ilgisi olmadığını söyle.\nBeni Protector'da görmeye geldiğinde sana istediğin her şeyi memnuniyetle anlatırım. Hadi gidelim!";
			link.l1 = "Pekala, Chimiset. Seni sonra... Koruyucu'da bulacağım. Hadi gidelim!";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "Son bir şey daha: gemilerimiz, Protector dahil, yabancılara yasaktır. İçeri girmek için Rivados olmalı ya da şifremizi bilmelisin. Söylemek isterdim ama şifre her hafta değişiyor ve ben burada fazla kaldım, şu anki şifreyi bilmiyorum.\nÖnce San Augustine'e git. Sen Shark'la konuşurken ben de bizimkilere kim olduğunu anlatırım. Seni bekleyeceğiz. Shark'la konuşmadan Protector'dan uzak dur!";
			link.l1 = "Anladım. San Augustine'e gideceğim. Yakında görüşürüz!";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.LSC_LetterChad.win_condition.l1 = "item";
			pchar.quest.LSC_LetterChad.win_condition.l1.item = "letter_chad";
			pchar.quest.LSC_LetterChad.function = "LSC_LetterChad_Find";
			sld = characterFromId("SharkMush_17");
			sld.lifeday = 0;
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("SharkSold_1"+(i+3));
				sld.lifeday = 0;
			}
			AddSimpleRumourCityTip("They say that you are a friend of clan Rivados. Interesting... congratulations.", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that you saved the Rivados wizard Chimiset from Tartarus. Now, you are a welcome guest on their ships.", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("So, it was you who set Chimiset free! Interesting. Now you are a friend of Rivados but an enemy of Narwhals. I'm not sure whether to congratulate or pity you...", "LostShipsCity", 5, 1, "LSC", "");
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "Benden ne istiyorsun, yabancı?";
			link.l1 = "Adın Chimiset, değil mi?";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "Evet, öyle. Benimle bir işin mi var?";
			link.l1 = "Evet, öyle. Amiral, Köpekbalığı Dodson’dan geliyorum. Sizi serbest bırakmamı emretti, ama bir şartla: Sorularıma cevap vermelisiniz.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "Dodson beni serbest bırakmaya karar verdi mi? Bunu duymak güzel – tabii bir oyun değilse.";
			link.l1 = "Bu bir oyun değil, ama yardımına ihtiyacım var. Söyle bana, Chimiset, bu adada gündüz taş olup gece yarısı altına dönüşen bir Kızılderili putu var mı? Beni deli sanma...";
			link.l1.go = "Friend_2";
		break;
		
		case "prisoner_3":
			dialog.text = "Başka sorunuz var mı?";
			link.l1 = "Evet. 'Beyaz Oğlan' adında birini tanıyor musun?";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "Beyaz Oğlan mı? Tabii, onu tanırım. O, Ole Christiansen. Artık büyüdü, çocuk gibi görünmüyor ama aklı hâlâ bir çocuğunki gibi.";
			link.l1 = "Öyle mi? Söylesene, onu nerede bulabilirim?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "Onu genellikle Axel Yost'un dükkanında, Carpentero'nun meyhanesinde ya da sokaklarda dolaşırken bulabilirsin. Solgun tenli, beyaz saçlı ve sade bir tavrı var. Onu hemen tanırsın.";
			link.l1 = "Mükemmel! Bir soru daha: burada Nathaniel Hawk adında bir adamla karşılaştın mı? Bir süre önce burada ortaya çıkmış olmalı ve ciddi şekilde hasta olabilir.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			dialog.text = "Bu isimde bir adamı tanımıyorum. Sana temin ederim ki Rivados'un gemilerinde öyle biri yok, ortak alanlarda da hiç görmedim.\nNarvaların bölgeleri hakkında ise bir şey diyemem. Rivadoslar oraya gitmez.";
			link.l1 = "Anladım. Yine de yardımın için teşekkürler, Chimiset!";
			link.l1.go = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "Ve şimdi Köpekbalığı beni özgür bırakacak mı?";
			link.l1 = "Evet. Sana başka sorum yok. Chad Kapper seni serbest bırakacak. Neyse, gitmem gerek...";
			link.l1.go = "prisoner_8";
		break;
		
		case "prisoner_8":
			dialog.text = "Dur! Geri gel.";
			link.l1 = "Evet? Başka bir şey mi düşündün?";
			link.l1.go = "prisoner_9";
		break;
		
		case "prisoner_9":
			dialog.text = "Tam olarak değil... (sesini alçaltarak) Senin Kapper'ın adamlarından olmadığını görüyorum. Ona güvenme. O bir katil.\nKısa bir süre önce, Alan Milrow'u silahsızken, soğukkanlılıkla öldürdü. O, Narval klanının lideriydi. Bunu hücremden gördüm: Chad içeri girdi ve onu bıçakladı.\Bir söylenti duydum; Amiralin kendi adamlarından bazıları onu öldürmeyi planlıyorlarmış. Köpekbalığı'na söyle - ve ona de ki, yüz yüze konuştuğumuzda daha fazlasını anlatacağım.";
			link.l1 = "Hm. Peki, bunu Dodson'a anlatacağım. Görüşürüz!";
			link.l1.go = "prisoner_10";
		break;
		
		case "prisoner_10":
			DialogExit();
			sld = characterFromId("Capper");
			sld.quest.chimiset_talk = "true"; // разговор с Чимисетом состоялся
			if (!CheckAttribute(npchar, "quest.capper_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_10"; // ноду Акуле
			LSC_SetWhiteBoy(); // поставим белого мальчика
			NextDiag.CurrentNode = "prisoner_11";
			AddQuestRecord("SharkHunt", "20");
		break;
		
		case "prisoner_11":
			dialog.text = "Köpekbalığı'na git ve sana anlattığım her şeyi ona da anlat. Umarım beni bu kafesten yakında çıkarırlar...";
			link.l1 = "Yoldayım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_11";
		break;
		
		//------------------------беседа на Протекторе, если был старт через Тартарус-----------------
		case "Friend":
			dialog.text = "İşte buradasın, dostum! Beni kurtardığın ve Kapper yerine bana güvendiğin için tekrar teşekkür ederim.\nBu tılsımları, çabalarının karşılığı olarak al. Eminim işine yarayacaklardır.";
			link.l1 = "Teşekkür ederim! Bunu hiç beklemiyordum...";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			GiveItem2Character(pchar, "indian_1");
			GiveItem2Character(pchar, "indian_11");
			GiveItem2Character(pchar, "amulet_1");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ve şimdi konuşabiliriz. Sanırım bana soruların vardı?";
			link.l1 = "Pekala. Yardımına ihtiyacım var. Chimiset, deli olduğumu düşünme... ama bu adada, gündüzleri taş olup, gece yarısı altına dönüşen bir Hint putu var mı?";
			link.l1.go = "Friend_2";
		break;
		
		// нода пересечения
		case "Friend_2":
			dialog.text = "I do not think you mad; there was such an idol.\nThough, it turns to gold under the morning sun's rays, and remains stone the rest of the day and night...\nMany times we brought wicked Narwhals to the idol, and it devoured each and every one. But no longer.";
			link.l1 = "Artık değil mi... Yani put artık yok mu diyorsun?";
			link.l1.go = "Friend_3";
		break;
		
		case "Friend_3":
			dialog.text = "Put bir zamanlar San Geronimo gemisindeydi. O gemi birkaç yıl önce battı ve put da onunla birlikte denizin dibini boyladı.";
			link.l1 = "Kahretsin! Bu putu kullanarak bu adadan gitmeyi umuyordum... Peki o gemi neredeydi?";
			link.l1.go = "Friend_4";
		break;
		
		case "Friend_4":
			dialog.text = "Narval bölgesinden çok uzakta değil, Phoenix enkazının yakınında. Havanın açık olduğu bir günde San Geronimo'yu deniz dibinde görebilirsin.";
			link.l1 = "Ah! Yani sığlıkta mı duruyor? O zaman yüzerek gidebilirim--";
			link.l1.go = "Friend_5";
		break;
		
		case "Friend_5":
			dialog.text = "Yapamazsın dostum. Birincisi, orası çok derin. İkincisi, orada dev yengeçler var. San Geronimo'ya varmadan seni paramparça ederler.";
			link.l1 = "Ah... peki, bunu biraz düşünmem gerekecek. En azından heykelin var olduğunu ve nerede olduğunu biliyorum.";
			if (CheckAttribute(npchar, "quest.chimiset_die")) link.l1.go = "prisoner_3";
			else
			{	
				if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_1";
				else link.l1.go = "Friend_6";
			}
			AddQuestRecord("LSC", "4");
		break;
		// нода пересечения
		
		case "Friend_6":
			dialog.text = "Bakıyorum, daha fazla sorunuz var. Sorun, dostum.";
			link.l1 = "Shark Dodson benden Chad’in suç ortaklarını bulmamı istedi. Chad’in sandığında bir mektup buldum. Bir keskin nişancıdan ve bir tüfekten bahsediyor. Görünüşe göre Shark’ı uzaktan öldürmek istiyorlar. Ne düşünüyorsun, Chimiset?";
			link.l1.go = "Friend_7";
		break;
		
		case "Friend_7":
			dialog.text = "They are going to shoot the Admiral? Hmm, let me think... Thing is, the Admiral almost never leaves his residence, and when he does, he is protected by half a dozen pirates.\nBut... he likes to walk around the stern gallery late in the evening; it's his habit.\nThere are two places that provide an angle on the Admiral's residence: the bow of the Santa Florentina and the mast of the Fury. Even so, no marksman I know of could make such a shot.\nHe would have to be eagle-eyed indeed, and he would need an excellent rifle. You should ask around the island for people who have access to such firearms.";
			link.l1 = "Mektupta bir... bir stutzen'dan bahsediliyordu. Böyle bir silahı olan birini gördün mü?";
			link.l1.go = "Friend_8";
		break;
		
		case "Friend_8":
			dialog.text = "Hayır. Böyle bir silahı hiç duymadım. Başkalarına sor - belki de bizim bilmediğimiz bir şey bilen vardır.";
			link.l1 = "Pekâlâ. Verdiğiniz bilgiler çok değerliydi, teşekkür ederim. Ah, son bir soru... 'Beyaz Oğlan' adında birini tanıyor musunuz?";
			link.l1.go = "Friend_9";
		break;
		
		case "Friend_9":
			dialog.text = "Beyaz Oğlan mı? Evet, bu Ole Christiansen'in lakabı. Artık yetişkin biri ama artık bir çocuk gibi görünmüyor, gerçi aklı hâlâ bir çocuğunki gibi.";
			link.l1 = "Yani, o bir aptal mı? Söylesene, onu nerede bulabilirim?";
			link.l1.go = "Friend_10";
		break;
		
		case "Friend_10":
			dialog.text = "Onu genellikle Axel Yost'un dükkanında, Carpentero'nun meyhanesinde ya da sokaklarda yürürken bulabilirsin. Solgun tenli, beyaz saçlı ve sade bir tavrı var. Onu hemen tanırsın.";
			link.l1 = "Harika. Teşekkürler Chimiset, gerçekten çok yardımcı oldun!";
			link.l1.go = "Friend_11";
		break;
		
		case "Friend_11":
			dialog.text = "Rivados'un bir dostuna yardım etmekten her zaman memnuniyet duyarım. Daha fazla sorunuz olursa, mutlaka yanıma gelin.";
			link.l1 = "Şimdilik gideceğim, şimdi gitmem gerek. Hoşça kal!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_2";
			else link.l1.go = "Friend_12";
		break;
		
		case "Friend_12":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
			pchar.questTemp.Saga.SharkHunt = "search_mush_1"; // флаг на магазин - поиск мушкета
			AddQuestRecord("SharkHunt", "11");
		break;
		
		case "freedom":
			dialog.text = "Ve işte özgürlüğümü ve hayatımı borçlu olduğum kişi burada. Kardeşlerimin beni o katil Kapper'dan kurtarmasına yardım ettiğin için teşekkür ederim.\nÇabalarının karşılığı olarak bu tılsımları al. Eminim işine yarayacaklardır.";
			link.l1 = "Teşekkür ederim! Bunu beklemiyordum...";
			link.l1.go = "Friend_1";
		break;
		
		case "freedom_1":
			dialog.text = "Bugün senin için başka ne yapabilirim?";
			link.l1 = "Bana söyle, Chimiset, 'Beyaz Oğlan' adında birini tanıyor musun?";
			link.l1.go = "Friend_9";
		break;
		
		case "freedom_2":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
		break;
		
		//--> информационный блок
		case "Chimiset_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Oh! Dostum "+pchar.name+"! Sana boğulduğunu söylemişlerdi! Görünen o ki loa'lar senden hoşlanmış...";
				link.l1 = "Sağımda ve sağlıklıyım, Chimiset. Endişen için teşekkür ederim. Loaların konusunda ise, haklı olabilirsin – Kukulcan'dan geçerken gerçekten de bana göz kulak oldular...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "Buraya ne getirdi seni, dostum?";
			/*if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l1 = "Bana Narvalların liderinin nasıl öldüğünü anlat. Bunu gören tek kişi sendin.";
				link.l1.go = "story";
			}*/
			if (!CheckAttribute(npchar, "quest.crab"))
			{
				link.l2 = "San Geronimo'nun yakınındaki dipte yengeçlerden bahsettin. Onlar nedir?";
				link.l2.go = "crab";
			}
			link.l9 = "Hiçbir şey, Chimiset. Sadece seni görmek istedim, dostum.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "story":
			dialog.text = "Her şeyi gördüğüm gibi yazacağım.";
			link.l1 = "Teşekkür ederim.";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "crab":
			dialog.text = "No one knows where they came from, or why they have reached such gigantic size. In fact we know little about these beasts.\nGroups of them can be found among the shipwrecks, living in shallow water, but most of them stalk the bottom of the sea, eating fish and any garbage we toss overboard.\nThey are a menace; their pincers can sever limbs and their jaws contain a dangerous poison, similar to that which saturates the bodies of barracuda. If left untreated, crab bites are lethal. Fortunately, the toxin can be counteracted by any common antidote or mixture.\nThere once was a crab hunter among us - a brave man who dove to the bottom to kill crabs in their own domain. He used to bring us their meat, which makes a delicious dish. He also brought me their poison, which formed a key ingredient in some of my potions.\nIt's a great pity he went to his creator - he was loved and envied by all.";
			link.l1 = "Nasıl öldü?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "Avladığı yengeçler tarafından yenip gitti. Uyarıyorum: o yaratıklara karşı dikkatli ol.";
			link.l1 = "Yapacağım.";
			link.l1.go = "exit";
			npchar.quest.crab = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		//<-- информационный блок
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
