// Диего де Монтойя
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
		
		case "patrol":
			dialog.text = TimeGreeting()+", "+GetFullName(npchar)+", San Jose devriyesinin şefiyim. Bu kasabanın dışında şüpheli davranışlarla ilgili bir mesaj aldık. Bize kim olduğunuzu ve ne yaptığınızı açıklama nezaketini gösterir misiniz?";
			link.l1 = "Kaptan "+GetFullName(pchar)+", señor subay. Burada Engizisyoncu Baba Vincento'nun yetkisi ve doğrudan talimatlarıyla bulunuyorum. İşte yetkimi doğrulayan bir belge.";
			link.l1.go = "patrol_1";
		break;
		
		case "patrol_1":
			dialog.text = "Pekâlâ... Her şey yolunda görünüyor. Belgeler düzgünce doldurulmuş, sorgucunun imzası da var. Şüphelerim için özür dilerim. Fenerde ne işiniz var?";
			link.l1 = "I'm not authorised to answer such questions. If you are genuinely interested in the purpose of my work for the inquisitor, I would recommend referring directly to him in Santiago for clarification. You are an officer; surely you have knowledge of military and service secrets. The only thing I can tell you is that I am investigating the circumstances of a wrecked Spanish ship.";
			link.l1.go = "patrol_2";
		break;
		
		case "patrol_2":
			dialog.text = "Tekrar özür dilerim, Mösyö. Sizi daha fazla oyalamaya cesaret edemem... ah, bir dakika! Az önce soğuk çeliğin parıltısını mı gördüm, yoksa bana mı öyle geldi? Ne ilginç bir hançeriniz var! Bana gösterebilir misiniz?";
			link.l1 = "Bunu geri vermeyi unutmadığından emin ol. Benim için çok önemli.";
			link.l1.go = "patrol_3";
		break;
		
		case "patrol_3":
			dialog.text = "Dios mio! Bu hançeri tanıyorum, kütüphanedeki kitaplardan birinde resmini görmüştüm! Bu, bizzat Cortés’in hançeri! İşte burada damgası var... Mösyö, lütfen reddetmeyin. Bu hançeri bana verin! Antika ve kişiselleştirilmiş silahlar topluyorum ve bu gerçekten inanılmaz bir parça. Karşılığını fazlasıyla öderim.";
			link.l1 = "Señor, bu hançer satılık değil. Onu bir hediye olarak aldım ve kimseye satmaya niyetim yok. Lütfen geri verin.";
			link.l1.go = "patrol_4";
		break;
		
		case "patrol_4":
			dialog.text = "Beş yüz altın doblonla bile yetinmez miydin? Bu bir servet. O parayla bir gemi alabilirsin!";
			link.l1 = "Hayır. Zaten bir gemim var, ve bu hançer eşsiz. Onu satmam.";
			link.l1.go = "patrol_5";
		break;
		
		case "patrol_5":
			dialog.text = "Eh, ne yazık... Peki, al eşyalarını. Seni daha fazla rahatsız etmeyeceğim. İyi şanslar!";
			link.l1 = "Bol şanslar, subay bey.";
			link.l1.go = "patrol_6";
		break;
		
		case "patrol_6":
			DialogExit();
			AddQuestRecord("Guardoftruth", "42");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "GuardOT_ClearMayakPatrol", 12.0);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("GOT_spamayaksold_"+i);
				sld.lifeday = 0;
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 10.0);
			}
		break;
		
		case "shore":
			PlaySound("Voice\English\Sharlie\Diego De Montoya.wav");
			dialog.text = "Yeter! Onunla konuşmak istiyorum...";
			link.l1 = "Demek Diego de Montoya bizzat karşımda... Ama affedersiniz, señor. Daha önce tanışmıştık, değil mi? Evet, doğru. Trinidad'da, deniz fenerinde. Ama orada kendinizi başka bir isimle tanıtmıştınız, eminim...";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			dialog.text = "Hafızanız sizi yanıltmıyor, efendim. Sahnelerin arkasında entrika çevirmek ve savaş başlatmak konusunda yalnız olmadığınızı bilmelisiniz. Sizi görmek için yanıp tutuştuğumun da farkındasınız. Eh, dileğiniz gerçek oldu gibi görünüyor.";
			link.l1 = "Bu tam olarak umduğum türden bir karşılaşma değildi, señor.";
			link.l1.go = "shore_2";
		break;
		
		case "shore_2":
			dialog.text = "Pekâlâ, olan oldu. Ama eğer hançerini bana verirsen, buradan sağ çıkman için sana bir şans vereceğim.";
			link.l1 = "Nadirleri toplama tutkun seni gerçekten bu kadar aşağıya mı sürükledi, caballero, bana böyle ince düşünülmüş bir tuzak hazırlayacak kadar?  Ah, sanmıyorum. Hakikatin Muhafızı seni tetikte mi tutuyor, yoksa tamamen yanılıyor muyum?";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "Ne hakkında konuştuğun hakkında hiçbir fikrim yok. Hançer ait olduğu yere dönmeli ve bilmen gereken tek şey bu. Altın için vermedin, şimdi ise kendi hayatın için vereceksin.";
			link.l1 = "Gerçekten mi sanıyorsunuz, señor, bana şimdi anlattıklarınıza inanacağım? Zaten bu körfezden ayrılmama izin vermeyeceğinize karar verdiniz, değil mi?";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			dialog.text = "Ya sana söz verirsem?";
			link.l1 = " 'Kurbağa yiyen' için kullanılan kelime mi? Hm...";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "Monsieur, I'm giving you one last chance. Either you hand over the dagger I'm interested in, or I'll be looting your dead body in a few minutes. Resistance is futile; we've got an overwhelming advantage in numbers.";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio")) link.l1 = "Beni gerçekten şaşırttınız, señor, orası kesin. Gerçekten de beni öyle inatçı bir ahmak mı sanıyorsunuz ki, zıpkınımı almadan kafamı köpekbalığının ağzına sokayım? Çocuklar, öldürün onları!";
			else link.l1 = "Gerçek güç sayılarda değil, yetenekte yatar, señor!";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto5", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio"))
			{
				PlaySound("interface\abordage_wining.wav");
				PlaySound("interface\abordage_wining.wav");
				for(i=1; i<=10; i++)
				{
					sld = characterFromId("GuardOT_Oursoldier_"+i);
					LAi_SetWarriorType(sld);
					ChangeCharacterAddressGroup(sld, "Shore15", "reload", "reload1_back");
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			sld = CharacterFromID("spa_baseprisoner");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=1; i<=13; i++)
			{
				sld = characterFromId("GOT_spashore_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_DiegoShoreGuardDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
