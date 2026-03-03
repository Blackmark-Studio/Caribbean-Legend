// диалоги НПС по квесту Коварный остров Ксочитэм
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;

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
		
		// капитан-нежить Санта-Квитерии
		case "SQC_skeletcap":
			PlaySound("Types\skel.wav");
			dialog.text = "Sen... yine de... ölmek... zorundasın. O gelecek... ve seni öldürecek... tıpkı hepimizi öldürdüğü gibi... tıpkı burada herkesi öldürdüğü gibi...";
			link.l1 = "Ne? Sen kimsin? Kimden bahsediyorsun?";
			link.l1.go = "SQC_skeletcap_1";
		break;
		
		case "SQC_skeletcap_1":
			PlaySound("Types\skel.wav");
			dialog.text = "O çok büyük... o yenilmez... öldürüyor... seni de öldürecek. Seni öldürmeliyim... eğer seni öldürürsem, bizim gibi olmazsın... anlamıyorsun... onun kılıcıyla öleceksin... bizim gibi birine dönüşeceksin... Santa Quiteria'daki herkes gibi...";
			link.l1 = "Olmaz!";
			link.l1.go = "SQC_skeletcap_2";
		break;
		
		case "SQC_skeletcap_2":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=2; i<=3; i++)
			{
				sld = characterFromId("SQI_skelet_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_SQCskeletcapdie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Страж маски Кукулькана
		case "guardmask":
			PlaySound("Voice\English\sharlie\Hranitel Maski Kukulkana.wav");
			dialog.text = "Seni ne zamandır bekliyorum!..";
			link.l1 = "Şey!.. İnanılmaz!... Bu gerçekten dehşet bir iskelet!";
			link.l1.go = "guardmask_1";
		break;
		
		case "guardmask_1":
			dialog.text = "Görüyorum... Hissediyorum... Bana... özgürlüğümü getirdin...";
			link.l1 = "Ne diyorsun? Sen nesin?!";
			link.l1.go = "guardmask_2";
		break;
		
		case "guardmask_2":
			dialog.text = "Ben Ksocheatem’in Muhafızıyım, Kukulcan’ın maskesinin bekçisiyim... ve senin yaklaşan ölümünüm!..";
			link.l1 = "...";
			link.l1.go = "guardmask_3";
		break;
		
		case "guardmask_3":
			PlaySound("Ambient\Teno_inside\big_ring.wav");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "KSOCHITAM_MONSTERS");
			LAi_group_FightGroups("KSOCHITAM_MONSTERS", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("Terrapin_SetMusic", 1.2);
			n = Findlocation("Shore_mask");
			locations[n].type = "seashore";
			pchar.questTemp.Ksochitam.GuardMaskFight = "true";
			for (i=1; i<=4; i++)
			{
				CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas"+i, 1, 0, 0, "fortfire");
				CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas"+i, 2.5, 0, 0, "fortfire");
			}
		break;
		
		case "guardmask_4":
			PlaySound("Voice\English\sharlie\Hranitel Maski Kukulkana.wav");
			dialog.text = "Dur...";
			link.l1 = "Ve bunu neden yapacakmışım, ha? Nefesin mi kesildi, kemik torbası?";
			link.l1.go = "guardmask_5";
		break;
		
		case "guardmask_5":
			dialog.text = "Hayır. Beni asla öldüremeyeceksin. O sihirli hançerle bile. Düellomuz çok, çok uzun sürebilir, ta ki tamamen tükenip ölene kadar.";
			link.l1 = "Öyle mi? Peki neden bana vuramıyorsun?";
			link.l1.go = "guardmask_6";
		break;
		
		case "guardmask_6":
			dialog.text = "Sen cesur, güçlü bir savaşçısın ve Şefin Pençesi'ni taşıyorsun. Bu hançeri elinde tutan, bana karşı savaşmaya cesaret eden kim olursa olsun, aradığı şeyi alır; bu yüzden seni yaşatmak zorundayım.";
			link.l1 = "Sen kimsin? Gerçekten kimsin, Muhafız?";
			link.l1.go = "guardmask_7";
		break;
		
		case "guardmask_7":
			dialog.text = "Eskiden bana Alberto Casco derlerdi. Alonso de Maldonado'nun birliğinde bir askerdim. Kadim Tayasal'ı bulduk, ama bizi yakaladılar ve kurban ettiler. Boyum ve gücüm yüzünden, pagan Kanek beni Ksocheatem'in Muhafızı, Kukulcan'ın maskesinin bekçisi yaptı. Ksocheatem'e ayak basan herkes beni buldu, elimde can verdi ve sonra bir ölümsüze dönüştü.\nReis'in Pençesi hançeriyle, bu yerin haritası etime kazındı. Maskenin güvenliğini sonsuza dek koruyacağım ve hançeri ellerimde tutana dek huzur bulamayacağım.";
			link.l1 = "Şefin Pençesine ihtiyacın var mı?";
			link.l1.go = "guardmask_8";
		break;
		
		case "guardmask_8":
			dialog.text = "Evet. Maskeye ihtiyacın olduğuna göre, hançeri bana ver. Ben uzun zamandır beklediğim huzura kavuşacağım, sen de maskeyi alacaksın. Sana yemin ederim, maskeyi alıp Ksocheatem'den sağ çıkabileceksin.";
			link.l1 = "Teklifini kabul ediyorum, Muhafız. Vaftiz çeşmesinin arkasındaki kaidedeki maskeyi gördüm. O mu?";
			link.l1.go = "guardmask_9";
		break;
		
		case "guardmask_9":
			dialog.text = "Evet, öyle. Bu, bizzat Uçan Yılan Kukulcan'ın kudretli eseri. Konuşmamız bittiğinde, oraya gidip onu alabilirsin.";
			link.l1 = "Umarım sözünü tutarsın, Muhafız...";
			link.l1.go = "guardmask_10";
		break;
		
		case "guardmask_10":
			dialog.text = "And içtenlikle yemin ettim... ";
			link.l1 = "O halde Şef'in Pençesi'ni al. Umarım ruhuna huzur getirir.";
			link.l1.go = "guardmask_11";
		break;
		
		case "guardmask_11":
			RemoveItems(pchar, "knife_01", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the Chief's Claw");
			RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			dialog.text = "Ah, bu anı ne zamandır bekliyordum! Artık sonunda gidebilirim... Ama veda hediyesi olarak, gücümden bir parça sana bırakmak istiyorum. Alberto Casco'nun vereceği son hediye bu olacak.";
			link.l1 = "...";
			link.l1.go = "guardmask_12";
		break;
		
		case "guardmask_12":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Ksochitam_GuardMaskGift", 1.5);
		break;
		
		case "guardmask_13":
			dialog.text = "Now it's time for me to leave. Don't waste any time; without its Guardian and the Kukulcan mask, the island will soon disappear forever.";
			link.l1 = "Bunda pişman olacak bir şey yok. Dünyada bir bataklık eksildi... Ama dur, Koruyucu! Tayasal'a gittin! Lütfen, bana orası nasıl bir yer anlat.";
			link.l1.go = "guardmask_14";
		break;
		
		case "guardmask_14":
			dialog.text = "Orası eski bir Maya şehri. İnsanların hâlâ orada yaşadığı zamanki haliyle korunmuş. Görkemli tapınaklar, yükselen piramitler... Şimdi ise orada, kendilerini Mayaların doğrudan torunları olarak gören Itza kabilesi yaşıyor. Her konuda onlara öykünüyorlar: dinlerinde, kültürlerinde ve yaşam tarzlarında.";
			link.l1 = "Oraya nasıl gidebilirim?";
			link.l1.go = "guardmask_15";
		break;
		
		case "guardmask_15":
			dialog.text = "Komutanımız yolu biliyordu, Alonso de Maldonado. Biz sadece onun peşinden ormanda ilerledik. Sadece şunu hatırlıyorum: Mosquito Körfezi'nde, Perlas Burnu'nun kuzeyinde karaya çıktık ve batıya, ormanın derinliklerine doğru ilerledik.";
			link.l1 = "Tayasal'da dikkate değer ne var?";
			link.l1.go = "guardmask_16";
		break;
		
		case "guardmask_16":
			dialog.text = "Orada her şey dikkat çekici. Gerçekten her şey. Ama bizim ilgimizi çeken tek şey Maya hazineleriydi. Ve onları bulduk. Ve bunun bedelini ağır ödedik, özellikle de ben. Ama şimdi, sonunda özgürüm!";
			link.l1 = "Tayasal'a gitmeden önce bilmem gerekenler neler?";
			link.l1.go = "guardmask_17";
		break;
		
		case "guardmask_17":
			dialog.text = "Itza halkı büyük bir güç ve zekâya sahiptir. Beyazlardan, milliyetleri ne olursa olsun, nefret ederler ve topraklarına giren her yabancıyı yok ederler. Sıradan Itza savaşçıları asla iletişime geçmez, ama Kanek ya da oğlu Urakan maskeyi görürse... belki konuşurlar. Tayasal'a sağ ulaşmayı başarırsan, kendin göreceksin. Ama oradan ayrılabilecek misin...";
			link.l1 = "Kanek, Tayasal'a gelen tüm beyazları kurban olarak sunuyor mu?";
			link.l1.go = "guardmask_18";
		break;
		
		case "guardmask_18":
			dialog.text = "Sanırım öyle. Ama bu, Kukulcan maskesini takan adamı kapsamayabilir.";
			link.l1 = "Pekâlâ. Buna güveneceğim.";
			link.l1.go = "guardmask_19";
		break;
		
		case "guardmask_19":
			dialog.text = "Elveda, asker. Maskenin gücünü doğru amaç için kullanmanı umuyorum.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Ksochitam_GuardMaskGoAway");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
