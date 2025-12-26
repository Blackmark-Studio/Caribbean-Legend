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
			dialog.text = "Não quero conversar.";
			link.l1 = "Hum, entendi.";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "zpq_sld2":
			dialog.text = "Só um minuto, senhor, você está "+GetFullName(pchar)+"?";
			link.l1 = "Sim... Como posso te ajudar?";
			link.l1.go = "zpq_sld2_1";
		break;
		case "zpq_sld2_1":
			dialog.text = "Precisamos de você. Ou melhor, do seu dinheiro. E nem pense em fazer birra, porque hoje não estou com paciência. Posso me irritar.";
			link.l1 = "Ah, por favor, que dinheiro é esse de que você está falando? Você acha mesmo que eu andaria por aí carregando o tesouro comigo?";
			link.l1.go = "zpq_sld2_2";
		break;
		case "zpq_sld2_2":
			dialog.text = "Não tente me enganar. Apenas me dê o dinheiro - "+FindRussianMoneyString(sti(pchar.questTemp.zpq.sum))+" e você pode seguir seu caminho. Ou vamos tomar à força.";
			if (pchar.questTemp.zpq == "failed")
			{
				link.l1 = "Você não trabalha para aquele rato do forte? Pois tenho boas notícias pra você: mandei ele direto pro inferno.";
				link.l1.go = "zpq_sld2_3_1";
			}
			else
			{
				link.l1 = "Você não trabalha para aquele rato do forte? Diga a ele que o dinheiro foi entregue a mãos confiáveis, então ele pode esquecer isso.";
			link.l1.go = "zpq_sld2_3";
			}
			if(makeint(Pchar.money) >= sti(pchar.questTemp.zpq.sum))
			{
				link.l2 = "Tá bom, pega seu dinheiro sujo, desgraçado!";
				link.l2.go = "zpq_sld2_6";
			}
			else
			{
				link.l2 = "Eu não tenho eles...";
				link.l2.go = "zpq_sld2_3";
			}
		break;
		case "zpq_sld2_3":
			dialog.text = "Então esse é o seu destino – morrer jovem por causa da sua ganância. É perigoso demais deixar você vivo.";
			link.l1 = "Tanta autoconfiança.";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_3_1":
			dialog.text = "Heh, então o seu destino é morrer por causa da sua ganância. Funciona pra gente, não queremos dividir.";
			link.l1 = "É a sua ganância que vai te matar...";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_4":
			dialog.text = "Ei, pessoal! Coloquem um saco na cabeça dele!";
			link.l1 = "Bem, foi a sua escolha...";
			link.l1.go = "zpq_sld2_5";
		break;
		case "zpq_sld2_5":
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(PChar, true);

			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("zpq", "7");

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = "Cumana";
			pchar.quest.zpq_seaBattle.function = "zpq_seaBattle";
		break;
		case "zpq_sld2_6":
			dialog.text = "Ótimo. Entregue isso e suma daqui, capitão!";
			link.l1 = "...";
			link.l1.go = "zpq_sld2_7";
			AddMoneyToCharacter(Pchar, -makeint(pchar.questTemp.zpq.sum));
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddQuestRecord("zpq", "8");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
		break;
		case "zpq_sld2_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			for(int i = 1; i <= 3; i++)

			{

				sld = CharacterFromID("qp2_" +i);
				LAi_SetImmortal(sld, true);
				LAi_type_actor_Reset(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 6.0);
			}
		break;
	}
}
