// Якоб ван Берг - злодей и пират, капитан Миража
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobInRoom")
			{
				dialog.text = "Argh! Hık... Sen de kimsin? Çinli nerede? Sana söylüyorum, sağır mısın? Hık!";
				link.l1 = "Seni gayet iyi duyuyorum, bağırmana gerek yok. Hiçbir Çinli gelmeyecek. Onun yerine ben geldim.";
				link.l1.go = "HollJacob_inRoom";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Bir hata var. Geliştiricilere söyle.";
			link.l1 = "Eğer öyle diyorsan...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "HollJacob_inRoom":
			dialog.text = "Ne? Sen kimsin? Ne halt ediyorsun burada? Sana bir soru sordum, pislik!";
			link.l1 = "Bunu bilmen gerekmiyor. Gemine ihtiyacım var.";
			link.l1.go = "HollJacob_inRoom_1";			
		break;
		
		case "HollJacob_inRoom_1":
			dialog.text = "Ah... Ne?! Sen ciddi misin... bekle! Sen lanet olası bir İngiliz köpeğisin! Kahretsin! Sonunda beni buldular... Buraya kadarmış! Teslim olmayacağım!";
			link.l1 = "Pekala, teslim olmanı istemiyorum...";
			link.l1.go = "HollJacob_inRoom_fight";			
		break;
		
		case "HollJacob_inRoom_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern_upstairs")], false);
			pchar.quest.JacobOnMainOver.over = "yes";//снять таймер
			chrDisableReloadToLocation = true;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "HollJacob_dead");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "JacobBerg_abordage":
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = "Kahretsin! Lanet olsun! Ne rezalet! Tüccar değilsin, değil mi?";
				link.l1 = "Ne akıllı bir çocuksun. Mürettebatım seçkin İngiliz denizcilerinden oluşuyor, yani baştan kaybetmiştin. Richard Fleetwood'la birlikte tüccar hikayesini biz uydurduk ve işte buradasın. Maceraların bitti, piç!";
				link.l1.go = "JacobBerg_abordage_1";
			}
			else
			{
				dialog.text = "Sonunda karşılaştık, kaptan. Zekâlı bir adamsınız... Uzun zamandır bu kadar dişli bir rakiple karşılaşmamıştım.";
				link.l1 = "Ve ben senin son rakibinim, Jacob. Buradan sağ çıkamayacaksın.";
				link.l1.go = "JacobBerg_abordage_3";
			}
		break;
		
		case "JacobBerg_abordage_1":
			dialog.text = "Öyle görünüyor. Mürettebatın gemiyi ele geçirdi ve sağ kalacağımı sanmıyorum. Ama onlar yardıma gelmeden önce seni cehenneme göndereceğim! Van Berg canını ucuza satmayacak!";
			link.l1 = "Bu sadece senin fikrin. Bence hayatın bir kuruş bile etmez. Yeter artık, hazırlan!";
			link.l1.go = "JacobBerg_abordage_2";			
		break;
		
		case "JacobBerg_abordage_2":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "JacobBerg_abordage_3":
			dialog.text = "Gerçekten mi? Kaçamayacağından emin oldum. Cephanelikte fitili ateşledim. Birazdan gemilerimiz paramparça olacak.";
			link.l1 = "Bence patlayacak tek şey sen ve şu eski teknen. Seni doğrayacağım, gemimi geri alacağım ve uzaklaşırken havai fişekleri izleyeceğim.";
			link.l1.go = "JacobBerg_abordage_4";			
		break;
		
		case "JacobBerg_abordage_4":
			dialog.text = "Önce seni öldürüp, pencereden atlayıp, kıyıya yüzüp, havai fişekleri kendim izlersem olmaz!";
			link.l1 = "Bahis?";
			link.l1.go = "JacobBerg_abordage_5";			
		break;
		
		case "JacobBerg_abordage_5":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom2"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
}
}
