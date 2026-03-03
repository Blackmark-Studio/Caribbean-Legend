// Оле Кристиансен - Белый Мальчик
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Hiçbir şey.";
			NextDiag.TempNode = "First time";
		break;
		
		// в магазине - первая встреча
		case "store":
			dialog.text = "Ah... Merhaba, amca. Beyaz boncun var mı? Beyaz boncuğu ver bana...";
			link.l1 = "Hm. İyi günler. Sen... Beyaz Çocuk musun?";
			link.l1.go = "store_1";
		break;
		
		case "store_1":
			dialog.text = "Boncuk! Beyaz çocuk için beyaz boncuk! Beyaz boncuğun var mı, amca?";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Hm, boncuklarım yok ama sana bu inciyi verebilirim. Beyaz ve boncuk gibi. Senin için uygun mu?";
				link.l1.go = "store_2";
			}
			link.l2 = "Hayır, boncuğum yok, ne beyaz ne de kırmızı. Boncuk takacak ne bir kızım ne de bir Kızılderiliyim. Söyle bakalım...";
			link.l2.go = "pearl";
			sld = characterFromId("Axel");
			sld.quest.ole_pearl = "true";
		break;
		
		case "pearl":
			dialog.text = "Boncuk! Beyaz boncuk! Boncuk yoksa, konuşmak yok. Kötü amca... Bana bir boncuk ver!";
			link.l1 = "Lanet olsun! Ne manyak adam! Snake Eye ve Chimiset haklıydı – aklı başında değil... Ne tür bir boncuk istiyor ki?";
			link.l1.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "pearl_repeat":
			dialog.text = "Bana bir boncuk ver, amca. İyi amca... Beyaz bir boncuk!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Al, boncuğunu al. Bunu mu istiyorsun?";
				link.l1.go = "store_2";
			}
			link.l2 = "Ah, kahretsin...";
			link.l2.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "store_2":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Evet, evet! Bu o! Amca bana bir boncuk verdi! Teşekkür ederim, iyi adam! Şimdi Ole'nin bir boncuğu daha var. Yakında annemi göreceğim...";
			link.l1 = "Senin adına sevindim. Peki, şimdi konuşabilir miyiz?";
			link.l1.go = "store_3";
			sld = characterFromId("Axel");
			DeleteAttribute(sld, "quest.ole_pearl");
		break;
		
		case "store_3":
			dialog.text = "Tabii, iyi adam. Sen iyi bir adam mısın, amca? Arkadaş olacağız. Ole seninle konuşmaktan memnun olur. Adın ne?";
			link.l1 = "Benim adım "+pchar.name+". Ole, bir zamanlar bana senden bahsetmişti biri, ama artık burada değil. Sana yardım ettiğini ve bana da yardım edebileceğini söylemişti.";
			link.l1.go = "store_4";
		break;
		
		case "store_4":
			dialog.text = "Amca Ole'ye bir boncuk verdi - iyi bir amca o. Ole iyi insanlara yardım etmeyi sever. Çok fazla iyi insan yok - kötü amcalar her yerde. Sana kesinlikle yardım edeceğim. Yardım etmeyi severim.";
			link.l1 = "Güzel! Artık arkadaşız demek. Söylesene, kırmızı tenli ve şahane tüylü bir şapkası olan bir adamı hatırlıyor musun? Bana, onu yıllar önce senin kurtardığını söylemişti.";
			link.l1.go = "store_5";
		break;
		
		case "store_5":
			dialog.text = "O amcayı hatırlıyorum. O iyi bir adam. Onu ben kurtardım. Heykele ben getirdim. Yakın zamanda da ambarın içinden, yiyeceklerle birlikte başka iyi bir adamı kurtardım. Onu kötü amiralin amcalarından kurtardım. Onlar onu öldürecekti. Onu da heykele götürmek istedim ama kesinlikle reddetti.";
			link.l1 = "Ambar kısmından mı? Heh, sanırım kimi kastettiğini anladım... Ve bu amcayı tanıyorum. Söylesene Ole, kurtardığın adam kim?";
			link.l1.go = "store_6";
		break;
		
		case "store_6":
			dialog.text = "Adı Nathan Amca. Çok hasta, hem de çok çok hasta. Ole onu bulduğunda neredeyse yürüyemiyordu.";
			link.l1 = "Elbette... Bunu nasıl başarabildiği gerçekten tuhaf.";
			link.l1.go = "store_7";
		break;
		
		case "store_7":
			dialog.text = "Hayır, tuhaf değil. Onu buldum ve ona biraz ateş romu verdim. Gemide yiyecek olduğu için deliğe yüzerek girdim. Kötü adamlar kapıyı kilitliyor, ama ben her zaman açarım. He-he-he... Aptal kötü adamlar. Yengeçleri tuzağa düşürüyorlar, biliyorum bunu. Oraya vardım, kötü adamlar vardı ve Nathan'ı buldum. İyi hissetmiyordu. Ateş romum vardı - ona içirdim, böylece kendine geldi. Sonra ona tentür verdim, her zaman yanımda bulundururum, olur da korkunç bir yengeç Ole'yi ısırır diye. İyi amca Chimiset bana böyle yapmamı söyledi...";
			link.l1 = "Ona panzehiri ve romu verdin mi? Heh, herkesin sandığı kadar aptal değilsin demek. Aferin, Ole.";
			link.l1.go = "store_8";
		break;
		
		case "store_8":
			dialog.text = "Kötü amcalar Ole'yi aptal sanıyor ve onunla dalga geçiyorlar: Aptal Ole... Ole aptal değil, sadece bütün beyaz boncukları toplaması gerekiyor yoksa annesi onu gönderecek. Sonra bana bir boncuk daha verir misin?";
			link.l1 = "Hm... Tabii Ole, biz arkadaşız. Söylesene, Hawk'ı... Nathan Amca'yı heykele nasıl gönderecektin? Chimiset Amca bana heykelin gemiyle birlikte battığını söylemişti...";
			link.l1.go = "store_9";
		break;
		
		case "store_9":
			dialog.text = "Heykel aşağıda. Ole biliyor. Ama derin değil, iyi amca Henrik amca Nathan'ı oraya gönderebilir. Amca Henrik suyun altında yürümeyi bilir. Ama orada çok korkunç yengeçler var. Ole onlardan korkuyor. Acı acı ısırıyorlar.";
			link.l1 = "Amca Henrik mi? O da kim?";
			link.l1.go = "store_10";
		break;
		
		case "store_10":
			dialog.text = "Uncle Henrik lives among the wicked Narwhal uncles. Everybody knows him. He can walk underwater, and he teaches the Narwhal uncles how to dive there. Uncle Henrik is kind; he gave a white bead to Ole.";
			link.l1 = "Narvallar seni nasıl içeri alıyor? Yoksa onların bölgesi sana açık mı?";
			link.l1.go = "store_11";
		break;
		
		case "store_11":
			dialog.text = "Hihi... Kötü amcalar Ole'nin içeri girmesine izin vermez, ama Ole geceleri onların gemilerindeki her odaya girebilir. Onlar büyük ve gürültülü, ama Ole sessiz ve dikkatli. Bir de amca Henrik'le, amca Henrik'in dalış yaptığı geminin etrafında yüzerken tanıştım. Amca Henrik Ole'ye beyaz bir boncuk verdi ve artık arkadaşız.";
			link.l1 = "İlginç... Ben de Henrik amcayla arkadaş olmak istiyorum.";
			link.l1.go = "store_12";
		break;
		
		case "store_12":
			dialog.text = "Heykele dalmak mı istiyorsun? Orada, eski geminin enkazında. Bir sürü büyük ve korkutucu yengeç var. Onlardan korkmuyor musun? Isırabilirler.";
			link.l1 = "Hayır, onlardan korkmuyorum. Zaten birini öldürdüm, bu yüzden benden korkmaları daha iyi olur.";
			link.l1.go = "store_13";
		break;
		
		case "store_13":
			dialog.text = "Oh, "+pchar.name+" Çok cesursun! O zaman Amca Henrik'e gitmelisin, sana denizin dibinde nasıl yürüyeceğini öğretecek ve oradaki tüm yengeçleri öldüreceksin. Orada Ole için bir tane daha büyük boncuk da bulacaksın. Değil mi?";
			link.l1 = "Tabii, yapacağım. Ama önce Amca Henrik'i bulmam gerek.";
			link.l1.go = "store_14";
		break;
		
		case "store_14":
			dialog.text = "Onu neden bulmak istiyorsun? 'San Gabriel' adlı gemide, atölyede yaşıyor. Ama o kötü Narval amcaları seni pek hoş karşılamayabilir.";
			link.l1 = "Kötü amcalarla kendim ilgileneceğim. Ve son bir soru, Nathan Amca şimdi nerede? Onu arıyordum, buraya gelmemin sebebi de o.";
			link.l1.go = "store_15";
		break;
		
		case "store_15":
			dialog.text = "Amca Nathan’ı 'Fernanda'daki sığınağıma sakladım. Orası çok uzakta ve kimse yaşamıyor. Herkes yakında batacağını sanıyor ama Ole öyle olmadığını biliyor. Amca Nathan’ı kurtardım ve oraya götürdüm\nHâlâ çok hasta ve sürekli ateş romu içiyor. Zar zor yürüyebiliyor ve beş kilodan ağır bir şeyi kaldıramıyor. Ona çok üzülüyorum, amca Nathan’a sandıklardan ateş romu ve amiralin kötü adamlarının ambarından yiyecek getiriyorum. Bir de yakaladığım fareleri pişirip ona veriyorum. Çok lezzetli fareler!";
			link.l1 = "Lezzetli fareler mi? Anladım. Peki, Nathan şu gemide mi... ne demiştin - 'Fernanda' mıydı? Onu tanımıyorum...";
			link.l1.go = "store_16";
		break;
		
		case "store_16":
			dialog.text = "Amca "+pchar.name+", Sana az önce buradan çok uzak olmadığını söyledim. Ona ulaşmak için yüzmen gerekiyor. Arkasında bir kapı var, ama Nathan amca onu açmaz. Ole ona açmamasını söyledi. Ama sen Nathan amcanın dostuysan, sana nasıl açılacağını söyleyeyim. Kapıyı şöyle çal: tak-tak... tak-tak. O zaman açar.";
			link.l1 = "Bunu unutmayacağım. Teşekkür ederim, Ole! Gerçekten bana çok yardımcı oldun! Sana nasıl teşekkür edeceğimi bilemiyorum.";
			link.l1.go = "store_17";
		break;
		
		case "store_17":
			dialog.text = "Bana bir beyaz boncuk daha getir. Tabii bulabilirsen.";
			link.l1 = "Ah, evet! Beyaz boncuklar! Güzel. Görüşürüz, Ole!";
			link.l1.go = "store_18";
		break;
		
		case "store_18":
			DialogExit();
			LAi_SetLoginTime(npchar, 12.0, 21.99);
			LAi_SetCitizenType(npchar);
			LAi_group_MoveCharacter(npchar, "LSC_CITIZEN");
			sld = characterFromId("Nathaniel");
			sld.dialog.currentnode = "diffindoor";
			sld.greeting = "Nathaniel_ill"; // ноду и вякалку Натану
			pchar.questTemp.LSC.DiffIndoor = "true"; //атрибут прохода к Натану
			pchar.questTemp.LSC = "mechanic"; // флаг на разговор с Механиком
			NextDiag.CurrentNode = "ole";
			AddQuestRecord("LSC", "6");
		break;
		
		case "ole":
			dialog.text = "Ah, amca "+pchar.name+"!  Seni görmek ne güzel! Nasılsın?";
			link.l1 = "Teşekkürler Ole, iyiyim. Seni de gördüğüme sevindim.";
			link.l1.go = "exit";
			link.l2 = "Dinle Ole, amiralin korsanlarının ambarın kapısını kapattığını ve senin de her seferinde açtığını söyledin... Oradaki sandıkların hepsi kilitli, ama amca Nathan için onlardan rom aldığını da söyledin. Bunu nasıl başarıyorsun?";
			link.l2.go = "lock";
			NextDiag.TempNode = "ole";
		break;
		
		case "lock":
			dialog.text = "Ole'nin güzel anahtarları var. Onlarla her kapı ya da sandık açılır. Yani, hepsi değil. Bazıları açılmaz ama çoğu açılır. Ole onları kötü amca Jurgen'in kamarasında buldu. Jurgen her gün ocağının yanında çekiciyle çalışır. Kilitler ve anahtarlar yapar. Bir de kötü Narvaller için kocaman, korkunç tüfekler yapar.";
			link.l1 = "Anladım. Ole, bana o anahtarları satabilir misin? Onlar için ödeme yapabilirim...";
			link.l1.go = "lock_1";
		break;
		
		case "lock_1":
			dialog.text = "Peki, amca "+pchar.name+",  anahtarları sana satacağım. Sadece bir tanesini kendime saklayacağım. O, amiralin odasını açıyor. Nathan Amca için bolca yiyecek ve rom var. Sandıklarda zaten artık boncuk ya da rom kalmadı.";
			link.l1 = "Onlar için ne kadar istiyorsun?";
			link.l1.go = "lock_2";
		break;
		
		case "lock_2":
			dialog.text = "Önce bana söyle, amca "+pchar.name+", büyük bir gemin var mı?";
			link.l1 = "Evet, gördüm. Ama o burada değil, dış halkada. Fakat yakında adadan ayrılacağım ve Amca Nathan için büyük gemimle buraya geri döneceğim.";
			link.l1.go = "lock_3";
		break;
		
		case "lock_3":
			dialog.text = " Nathan amca için mi? Ah, bu harika! Bak, bana söz ver, beni buradan büyük geminle götüreceksin ve ne kadar istersem seninle denize açılmama izin vereceksin. Faydalı olabilirim. Fare yakalar, pişiririm... Bir de, bana beş beyaz boncuk ver. O zaman anahtarları sana veririm.";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "Tabii! İşte boncukların. Al onları.";
				link.l1.go = "lock_4";
			}
			link.l2 = "Fareleri yakalayıp pişirmek mi? Heh! İlginç bir yetenek. Tamam Ole, anlaştık. Sana beş boncuk ve sözümü getireceğim.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_1";
		break;
		
		case "ole_1":
			dialog.text = "Ah, amca "+pchar.name+"! Seni görmek ne güzel! Nasılsın?";
			link.l1 = "Teşekkürler Ole, iyiyim. Seni de görmek güzel.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "Sana anahtarların için beş beyaz boncuk getirdim.";
				link.l2.go = "lock_4";
			}
			NextDiag.TempNode = "ole_1";
		break;
		
		case "lock_4":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			dialog.text = "Boncuklar! Beyaz boncuklar! Amca "+pchar.name+"  Ole'ye boncuklar verdi! Yakında seni göreceğim, anne!... Amca "+pchar.name+", geri döndüğünde beni buradan götüreceğine söz veriyor musun?";
			link.l1 = "Yaparım, Ole. Henüz fare yemedim. Seni de yanıma alacağım.";
			link.l1.go = "lock_5";
		break;
		
		case "lock_5":
			GiveItem2Character(pchar, "keys_skel");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			dialog.text = "Teşekkür ederim, teşekkür ederim, sevgili amca "+pchar.name+" Anahtarlarını al. Kullanması kolay, her birini sırayla dene. İhtiyacın olan kilidi eninde sonunda biri açacaktır. Açmazsa, demek ki kilit çok karmaşık ve özel bir anahtara ihtiyacın olacak.";
			link.l1 = "Anladım. Sanırım bununla ben ilgileneceğim.";
			link.l1.go = "lock_6";
		break;
		
		case "lock_6":
			dialog.text = "Bekle, amca "+pchar.name+"! Bir anahtarım daha var. Oldukça güzel ve akıllıca yapılmış. Kötü amca Jurgen böyle anahtarlar yapmaz. Ne açtığını bilmiyorum ama belki sen öğrenirsin. Bak, gerçekten çok güzel bir anahtar, eminim daha önce böyle bir şey görmemişsindir.";
			link.l1 = "Bana göster... Evet, anahtar gerçekten ilginç. Ama ne işe yarar ki, neyi açtığını bilmiyorsan?";
			link.l1.go = "lock_7";
		break;
		
		case "lock_7":
			dialog.text = "Amca "+pchar.name+", , sen gerçekten tuhafsın. Ne işe yarar ki? Bir anahtar varsa, bir yerde bir kilit de vardır. Bir kilit varsa, bir yerde bir madeni para da vardır. Anahtarı adada buldum. Bu da demek oluyor ki kilit de burada. Hiç şüphem yok. Bu akıllıca bir anahtar, ve ancak çok değerli eşyalar böyle bir anahtarla kilitlenir. Ole bilir.";
			link.l1 = "Doğrusunu söylemek gerekirse, komiksin Ole. Peki, alıyorum. Buna karşılık boncuk ister misin?";
			link.l1.go = "lock_8";
		break;
		
		case "lock_8":
			dialog.text = "Evet, Ole beş boncuk istiyor. Verecek misin, amca "+pchar.name+"?";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "Al, boncuklarını geri veriyorum.";
				link.l1.go = "key";
			}
			link.l2 = "Onlar bende yok, ama sana mutlaka boncuk getireceğim.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_2";
		break;
		
		case "key":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "sant_anna_key");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Boncuklar! Beyaz oğlan için beyaz boncuklar! Annesi için! Al, amca "+pchar.name+", al anahtarı. Ve kilidi bulacaksın, Ole bilir. Cesursun, vahşi yengeçlerden bile korkmuyorsun.";
			link.l1 = "Ah, güldürme beni Ole! Anahtar için sağ ol. Görüşürüz!";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "ole_2":
			dialog.text = "Ah, amca "+pchar.name+"! Seni gördüğüme sevindim! Nasılsın?";
			link.l1 = "Teşekkürler Ole, iyiyim. Seni de görmek güzel.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "Sana anahtarın için beş beyaz boncuk getirdim.";
				link.l2.go = "key";
			}
			NextDiag.TempNode = "ole_2";
		break;
		
		case "ole_3":
			dialog.text = "Ah, amca "+pchar.name+"! Seni gördüğüme sevindim! Nasılsın?";
			link.l1 = "Teşekkürler Ole, iyiyim. Seni de gördüğüme sevindim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "return":
			dialog.text = "Ah, amca "+pchar.name+", geri geldin! Büyük gemiye geri döndün! Beni buradan götürecek misin? Amca "+pchar.name+", bana söz vermiştin, hatırlıyor musun?";
			link.l1 = "Elbette, biliyorum Ole. Hoş geldin aramıza! Sanırım fareler başı dertte, ha-ha!";
			link.l1.go = "return_1";
			link.l2 = "Gerçekten mi? Ve sana ne zaman söz verdim? Böyle bir söz verdiğimi hiç hatırlamıyorum...";
			link.l2.go = "return_3";
		break;
		
		case "return_1":
			dialog.text = "Teşekkürler, amca! Ole işe yarayacak, göreceksin! Ah, belki annemi de görürüm? Şimdi hemen gidiyorum!";
			link.l1 = "Böyle acele etme, Ole. Eşyalarını toplayabilirsin. Hemen yelken açmayacağım.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LSC_SetOlePassenger", 10.0);
		break;
		
		case "return_3":
			dialog.text = "Bana söz verdin, verdin! Ole'yi buradan götüreceğine söz verdin! Kötü amca! Ole'yi kandırdın! Kötü amca!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload45", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", -3);
			if (GetCharacterIndex("Mary") != -1) // Мэри
			{
				sld = characterFromId("Mary");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else // иначе завершение
			{
				chrDisableReloadToLocation = false;
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			}
		break;
		
		// Блудный сын
		case "givemepearl":
			dialog.text = "Amca, amca... Bir beyaz boncuğa daha ihtiyacım var. Lütfen, Ole'ye bir beyaz boncuk ver!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Bunu isteyeceğini biliyordum. Al, boncuğunu. Memnun musun?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "Ah, ne büyük dertmiş bu... Boncuğum kalmadı Ole, hiç kalmadı!";
			link.l2.go = "givemepearl_no";
			DeleteAttribute(npchar, "pearl_date");
		break;
		
		case "givemepearl_yes":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			dialog.text = "Teşekkür ederim! İyi, iyi amca "+pchar.name+"! Ole'nin bir boncuğu daha var ve boncuklar neredeyse bitti! Ve ben anneme gideceğim...";
			link.l1 = "Ah, peki neden bu kadar garipsin...";
			link.l1.go = "givemepearl_yes_1";
		break;
		
		case "givemepearl_yes_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			SaveCurrentNpcQuestDateParam(npchar, "pearl_date");
			npchar.quest.pearlqty = sti(npchar.quest.pearlqty)+1;
			NextDiag.CurrentNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_repeat":
			dialog.text = "Boncuk için teşekkür ederim, iyi amca "+pchar.name+"!";
			link.l1 = "Hoş geldin...";
			link.l1.go = "exit";
			NextDiag.TempNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_no":
			dialog.text = "Boncuk yok mu? Ama bu nasıl olur, amca "+pchar.name+"?! Sadece birkaç boncuk daha kaldı... Onları toplamam gerek. O halde, karaya çıkacağım. Boncuk arayacağım...";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Peki, nereye gideceksin? Tek başına ne yapacaksın? Hayır, kaderinden ben sorumlu olmak istemem. Bekle, ceplerime bakayım... Al! Boncuğunu al ve benimle kal. Oldu mu?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "Hakkındır, Ole. Eğer benimle denizlere açılmaktan sıkıldıysan, seni tutmam. Anlaşmamız vardı. Ama şu zamana kadar işleri gayet iyi götürdün...";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "givemepearl_no_1":
			dialog.text = "Elveda, amca "+pchar.name+" Ole'nin beyaz boncuklara ihtiyacı var, yoksa asla annesine dönemez...";
			link.l1 = "Ah, senin adına gerçekten üzgünüm, ama elimden ne gelir? Git, Ole. Bol şans.";
			link.l1.go = "givemepearl_exit";
		break;
		
		case "givemepearl_exit": // Оле уходит - квест не довели до конца
			DialogExit();
			RemovePassenger(Pchar, npchar);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(pchar, "GenQuest.Ole");
		break;
		
		case "mother":
			dialog.text = "Amca "+pchar.name+"! Bir beyaz boncuğa daha ihtiyacım var. Sonuncusu. Lütfen, onu Ole'ye ver!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Bunu isteyeceğini biliyordum. Al, boncuğunu al. Memnun musun?";
				link.l1.go = "mother_1";
			}
			link.l2 = "Ah, ne büyük dert başıma... Boncuğum kalmadı Ole, vallahi kalmadı!";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "mother_1":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Teşekkür ederim, teşekkür ederim, sevgili amca "+pchar.name+"! Şimdi Ole'nin bütün boncukları var. Evet, hepsi tek tek! Şimdi Ole onları annesine götürebilir ve annesi Ole'yi göndermeyecek...";
			link.l1 = "Dinle, sürekli bahsettiğin o anne kim? Ve sonunda, neden o incilere... beyaz boncuklara ihtiyacın olduğunu bana açıkla. Ve bu ne demek oluyor – hepsi sende mi?";
			link.l1.go = "mother_2";
		break;
		
		case "mother_2":
			dialog.text = "İyi amca "+pchar.name+" Ole'nin annesi için boncuk toplamasına yardım etti... Ole küçüktü, annesinin beyaz boncuklu kolyesini kopardı. Bütün boncuklar suya düştü. Annesi Ole'ye çok kızdı ve Ole, kaybolan tüm boncukları toplayana kadar eve dönemedi\nKaç tane olduklarını hatırlıyorum. Beş kere on boncuk. Şimdi Ole hepsini topladı. Amca "+pchar.name+", lütfen, beni eve götür! Annemi mutlu etmek, boncukları geri vermek istiyorum. Beni eve götür!";
			link.l1 = "Tanrım, ne inanılmaz bir hikaye... Çocukken Adalet Adası'na gelmişsin. Annenin inci kolyesini kırdığın için mi evinden kovuldun? Tüyler ürpertici...";
			link.l1.go = "mother_3";
		break;
		
		case "mother_3":
			dialog.text = "Beni anneme götür, iyi amca "+pchar.name+" . Onu görmek istiyorum. Boncukları görünce sevinecek.";
			link.l1 = "İsterdim, ama sen evinin nerede olduğunu biliyor musun? Annen nerede yaşıyor?";
			link.l1.go = "mother_4";
		break;
		
		case "mother_4":
			dialog.text = "Adada yaşıyor, kırmızı çatılı evde.";
			link.l1 = "Gerçekten mi! Burada kaç ada olduğunu ve kaç evin kırmızı çatısı olduğunu biliyor musun? O adanın adı ne? Detayları anlat...";
			link.l1.go = "mother_5";
		break;
		
		case "mother_5":
			dialog.text = "Adını bilmiyorum. Bir adadaydık, annem babama adada olduğumuzu söylüyordu! Kırmızı çatılı bir evde yaşıyorduk. Güzel bir evdi, hem de büyük. Beni anneme götür, amca "+pchar.name+". Lütfen...";
			link.l1 = "Peki, tamam. O zaman her adada böyle bir ev arayacağız ve anneni soracağız. Adı ne?";
			link.l1.go = "mother_6";
		break;
		
		case "mother_6":
			dialog.text = "Adı mı? Çok garipsin, amca "+pchar.name+" . Annemin adı Anne. Senin annenin adı farklı mı?";
			link.l1 = "Tanrım, lütfen bana biraz sabır ver... Peki, Ole. Evini bulmaya çalışacağız. Şimdi gemiye git.";
			link.l1.go = "mother_7";
		break;
		
		case "mother_7":
			dialog.text = "Teşekkür ederim, amca "+pchar.name+" . Çok, çok nazik ve iyi bir insansınız! Yakında Ole annesini görecek!";
			link.l1 = "Ah...";
			link.l1.go = "mother_8";
		break;
		
		case "mother_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(npchar, "pearl_date");
			// ставим Агнес Кристиансен и открываем ее дом в Мариго
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", false);
			sld = GetCharacter(NPC_GenerateCharacter("Agnes", "women_18", "woman", "towngirl", 10, HOLLAND, -1, true, "quest"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Agnes";
			sld.lastname = "Christiansen";
			sld.dialog.FileName = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "agnes";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Marigo_houseSp2", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		break;
		
		case "home":
			dialog.text = "Anne... Anne, anneciğim! Geri döndüm!";
			link.l1 = "Oğlum...";
			link.l1.go = "home_1";
		break;
		
		case "home_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestFunctionDelay("LSC_OleReturnHome", 18.0);
		break;
		
		case "home_2":
			dialog.text = "Anneciğim, sana beyaz boncuklar getirdim! Hepsini topladım! Yine bir kolyen olacak. Hâlâ bana kızgın mısın?";
			link.l1 = "Tanrım... (ağlayarak) Ole! Oğlum, neden? Neden gittin? O inciler umurumda bile değil!";
			link.l1.go = "home_3";
		break;
		
		case "home_3":
			sld = characterFromId("Blaze");
			dialog.text = "Anne, al... bunları al. Uzun zamandır biriktiriyorum. İyi amcalar bana yardım etti, özellikle de amca "+sld.name+". Beni büyük gemisine aldı, boncuk toplamama yardım etti ve beni eve getirdi...";
			link.l1 = "Ole... Gerçekten büyümüşsün, ama hâlâ bir çocuksun... Gel, sana sarılayım, oğlum! Özür dilerim, o lanet kolye için beni affet! Seni asla yalnız bırakmayacağım, asla! Birlikte yaşayacağız ve sana gözüm gibi bakacağım... Hatalarımı telafi edeceğim, söz veriyorum!...";
			link.l1.go = "home_4";
		break;
		
		case "home_4":
			dialog.text = "Anne, seni çok özledim... Seninle kalmak istiyorum. Hâlâ bana kızgın mısın? Neden ağlıyorsun?";
			link.l1 = "(ağlayarak) Hayır, hayır... Çok üzgünüm, lütfen beni affet, oğlum!...";
			link.l1.go = "home_5";
		break;
		
		case "home_5": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Agnes");
			sld.dialog.currentnode = "agnes_11";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "final":
			dialog.text = "Amca "+pchar.name+"! Geldiğine çok sevindim! Beni anneme getirdiğin için teşekkür ederim. Onunla burada olmak harika... Eve dönmek güzel değil mi, amca? "+pchar.name+"?";
			link.l1 = "Evet. Evet. Öyle. Senin mutlu olmana sevindim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "final";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Dinle, silahını indirsen iyi olur. Beni tedirgin ediyorsun.","Biliyor musun, burada elinde bıçakla dolaşmana izin verilmez. Onu yerine koy.","Dinle, elinde kılıçla etrafta dolaşan bir ortaçağ şövalyesi gibi davranma. Onu yerine koy, sana yakışmıyor...");
			link.l1 = LinkRandPhrase("Pekâlâ.","Pekala.","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dinle, ben bu şehrin bir vatandaşıyım ve senden kılıcını indirmeni rica ediyorum.","Dinle, ben bu şehrin bir vatandaşıyım ve senden kılıcını indirmeni rica ediyorum.");
				link.l1 = LinkRandPhrase("Pekâlâ.","Pekala.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dikkatli ol dostum, elinde silahla dolaşıyorsun. Gerilebilirim...","Silahları çekilmiş adamların önümden geçmesini sevmem. Bu beni korkutuyor...");
				link.l1 = RandPhraseSimple("Anladım.","Bunu alıyorum.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
