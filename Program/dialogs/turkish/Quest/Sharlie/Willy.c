// Вильям Патерсон
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
			link.l1 = "Hayır, hiçbir şey.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "catoche":
			dialog.text = "Merhaba, Mösyö. Kahretsin, demek buralarda bütün bu askeri kargaşayı çıkaran sensin?!";
			link.l1 = TimeGreeting()+", efendim. Evet, karaya çıkan gemi benimkiydi. Ne oldu ki? Siz kimsiniz? Sanırım İngilizsiniz?";
			link.l1.go = "catoche_1";
		break;
		
		case "catoche_1":
			dialog.text = "Bir İskoç'um, Mösyö. İngiliz Donanması'nın kaptanı William Paterson, bu da sağ kolum ve birinci subayım Archibald Calhoun. Mesele şu ki, ormanda bir İspanyol kalesi var. Görevim, o lanet olası herifleri, İngiliz topraklarına tehlikeli derecede yakın inşa ettikleri kaleden kovmak.\nGeçenlerde kaleye saldırmayı denedik ama herifler kayıplarına rağmen direnebildiler. Ben de takviye almak için ayrıldım ve...";
			link.l1 = "No need for that now. I've completed your unfinished business; the jungle fort is empty. The Spanish commander, Diego de Montoya, is dead, and his squadron has been wiped out as well.";
			link.l1.go = "catoche_2";
		break;
		
		case "catoche_2":
			dialog.text = "Bu nasıl bir kendi adaletini sağlama girişimi? İngiliz topraklarında böyle bir askeri hareketliliğe sebep olmanın motivasyonu ne?";
			link.l1 = "Sana hatırlatmaya cüret ediyorum Kaptan Paterson, burası Belize değil. Hangi İngiliz toprağı? Bütün bu tantana Don Diego de Montoya'nın bana ve gemilerime saldırma konusundaki pervasız kararı yüzünden başladı.";
			link.l1.go = "catoche_3";
		break;
		
		case "catoche_3":
			dialog.text = "Ehem... Don Diego'nun sana saldırmak için ne sebebi vardı, ha kaptan?";
			link.l1 = "O ve benim aramda uzun süredir süren bir husumet var... Onun komutasındaki filonun St. Pierre'e saldırdığı ve kısa süre sonra benim de doğrudan müdahalemle yok edildiği günden beri.";
			link.l1.go = "catoche_4";
		break;
		
		case "catoche_4":
			dialog.text = "Kahretsin! O yaşlı caballero'ya canlı ihtiyacım vardı! Onu ormanda neden askeri üs kurduğunu sorgulayacaktım. Bunu durduk yere yapmış olamazdı...";
			link.l1 = "Üzgünüm, ama şu anda size bir şey söyleyemez. Yine de, kalede garnizondan yaralı askerler olabilir. Onların konuşma ihtimali var mı?";
			link.l1.go = "catoche_5";
		break;
		
		case "catoche_5":
			dialog.text = "Askerler... Ah, şu inatçı budalalardan ne hayır gelir ki!... Don Diego'nun cesedi nerede? Üzerinde önemli belgeler olabilirdi!";
			link.l1 = "Don Diego'yu zırhhanenin kalesinin avlusunda bıraktım. Ona bu kadar ihtiyacın varsa, orada bulabilirsin. Kaçabileceğini sanmıyorum.";
			link.l1.go = "catoche_6";
		break;
		
		case "catoche_6":
			dialog.text = "Eh... ve sana kim başkasının işine burnunu sokmanı söyledi... Zaten başıma yeterince dert açtın...";
			link.l1 = "Kaptan, neden beni azarladığınızı anlamıyorum. Sizin işinizi yaptım, kendi adamlarımı savaşa soktum, kendi hayatımı riske attım, ama yine de memnun değilsiniz. Şimdi yapmanız gereken tek şey Port Royal'e görevinizdeki başarınızı ve tüm işlerinizi bildirmek. Söz veriyorum, şanınızdan pay istemeyeceğim.";
			link.l1.go = "catoche_7";
		break;
		
		case "catoche_7":
			dialog.text = "Övgüyü sahiplenmek mi? Şan derken neyi kastediyorsun?! Hiçbir şey anlamıyorsun... Eh, peki. Elveda, beyefendi.";
			link.l1 = "Sana da en iyi dileklerimi sunarım!";
			link.l1.go = "catoche_8";
		break;
		
		case "catoche_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "GuardOT_OpenCatocheDoor", 10.0);
			sld = CharacterFromID("Archy");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 7.0);
			AddQuestRecord("Guardoftruth", "57");
		break;
		
		case "isladevieques":
			PlaySound("Voice\English\sharlie\Willie Paterson.wav");
			dialog.text = "Adamım, dedikoducular senin kedi gibi dokuz canlı olduğunu söylerken hiç de abartmamışlar! "+TimeGreeting()+", Monsieur de Maure. Pek iyi görünmüyorsunuz...";
			link.l1 = TimeGreeting()+", Bay Paterson. Şunu söylemeliyim ki, siz ve arkadaşınız Archibald rolünüzü çok iyi oynadınız ve beni fena halde kandırdınız. Hepinizin canı cehenneme! Hiçbir şeyin farkında bile değildim...";
			link.l1.go = "isladevieques_1";
		break;
		
		case "isladevieques_1":
			dialog.text = "Hey, don't swear before the gates of the Holy Land. You didn't see it coming? I am flattered: I have fooled one of the most famous intriguers of the archipelago. The diary idea was brilliant, don't you think?\nI had to lure you to some obscure place; killing you in the open would be a scandal, you are a close friend of Philippe de Poincy, am I correct? Now you are going to disappear without a trace and no one will ever know how.";
			link.l1 = "Yani, Calhoun'un bana anlattığı her şey... yalan mıydı?";
			link.l1.go = "isladevieques_2";
		break;
		
		case "isladevieques_2":
			dialog.text = "Not at all. I really did find poor Archibald at this place. He didn't write any memoirs, though; the diary you found in his room was written at my request, especially for you, Monsieur de Maure.\nI have been keeping an eye on you since we met at Cape Catoche. It was you who took the map of Two Appearances from Don Diego's corpse, wasn't it? Don't deny it, I know it was you.";
			link.l1 = "Sen de Gerçeğin Muhafızı'nı biliyor musun?";
			link.l1.go = "isladevieques_3";
		break;
		
		case "isladevieques_3":
			dialog.text = "Bu çok saçma bir soru. Tabii ki biliyorum. Ve şefin Pençesi'nin de sende olduğunu biliyorum. Yakında, sana ait olmayan o eşyaları geri vereceksin.";
			link.l1 = "Don Diego gibi sende sallanmadığın için memnunum. Dürüstlüğü ve açık sözlülüğü takdir ederim. Anladığım kadarıyla, pusula yani Yolun Oku sende, doğru mu?";
			link.l1.go = "isladevieques_4";
		break;
		
		case "isladevieques_4":
			dialog.text = "Hah-ha! Pekâlâ, dürüst olalım, sonuna kadar... Gerçekten inanıyor musunuz, efendim, ben de siz ve Don Diego gibi bir aptalım da, böyle değerli bir eşyayı yanımda taşırım? Pusula Jamaika’da, hem de Port Royal’da bile değil, kimsenin aklına gelmeyecek bir yerde ve sağlam bir kilit altında. Ama bu bilgiye ihtiyacınız olmayacak.";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.OfficerKill"))
			{
				link.l1 = "Anladığım kadarıyla, beni çoktan toprağa verdiniz, Bay Paterson? İddia ediyorum ki, kedinin hâlâ bir canı kaldı!.. Subaylarım nerede?";
				link.l1.go = "isladevieques_5_1";
			}
			else
			{
				link.l1 = "Anladığım kadarıyla beni çoktan toprağa verdiniz, Bay Paterson? İddia ediyorum ki, kedinin hâlâ bir canı kaldı!..";
				link.l1.go = "isladevieques_5_2";
			}
		break;
		
		case "isladevieques_5_1":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.GirlKill"))
			{
				dialog.text = "Hanımefendiniz için endişelendiniz mi, kaptan? Kadınınız orada çalılıkların arasında, alnında bir delikle yatıyor. Size yolu açtı, yakında siz de ona katılacaksınız. Şunu da söylemeliyim, güzel bir kızdı! Umarım onu bir kereden fazla yatağınıza aldınız?";
				link.l1 = "O bir orospu çocuğu! Bunun bedelini ödeyeceksin, seni alçak?!";
				link.l1.go = "isladevieques_6";
			}
			else
			{
				dialog.text = "Adamlarınız sizin için yolu açtı, Mösyö de Maure. Şurada çalılıkların arasında yatıyorlar. Yakında siz de onlara katılacaksınız.";
				link.l1 = "Bunu göreceğiz!";
				link.l1.go = "isladevieques_6";
			}
		break;
		
		case "isladevieques_5_2":
			dialog.text = "Gerçekten de sonuncusu olduğundan emin olacağız.";
			link.l1 = "Bunu göreceğiz!";
			link.l1.go = "isladevieques_6";
		break;
		
		case "isladevieques_6":
			dialog.text = "Beni güldürüyorsun. Tek başına bütün birliğe karşı! Neyse, yeterince konuştuk... Tüfeklerinizi doğrultun! Ateş!";
			link.l1 = "...";
			link.l1.go = "isladevieques_7";
		break;
		
		case "isladevieques_7":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться patch-8
			LAi_ActorRunToLocation(npchar, "quest", "teleport", "IslaDeVieques_HouseEntrance", "quest", "mushketer", "GuardOT_WillyGetReady", 10.0);
			for(i=1; i<=5; i++)
			{
				sld = CharacterFromID("GuardOT_willymushketer_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_WillyMushketerDie");
			DoQuestFunctionDelay("Terrapin_SetMusic", 0.2);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
