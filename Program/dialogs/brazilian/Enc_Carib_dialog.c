void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iGun, iMush, qty;
	string sGroup, sLink, sText;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Carib" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "First time":
			dialog.text = "Parabéns! Isso é um bug. Entre em contato com o Jason e conte como e onde você encontrou isso. Valeu!";
			link.l1 = "Vou fazer isso imediatamente!";
			link.l1.go = "exit";
			Diag.TempNode = "First time";
		break;

		case "exit_fight":
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_CaribAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_peace":
			DialogExit();
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_SetImmortal(sld, false);
				LAi_CharacterDisableDialog(sld);
			}	
			ChangeIndianRelation(1.00);
		break;
		
		// военные индеи - карибы
		case "war_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				dialog.text = LinkRandPhrase("Saudações, filho do mar! Já ouvi falar de você. Pode andar livremente por nossas terras.",""+npchar.name+" saúda você, irmão de rosto pálido. Ficamos felizes em tê-lo como nosso convidado.","Saúdo você, bravo guerreiro de rosto pálido! "+npchar.name+" está feliz em conhecer um amigo dos índios. Vá em paz!");
				link.l1 = RandPhraseSimple("E saudações para você, irmão de pele vermelha! Que tenha uma boa caçada!","Saudações, bravo guerreiro! Que os deuses abençoem você e sua família!");
				link.l1.go = "exit_peace";
				if (CheckCaribGuns())
				{
					npchar.quest.count = 0;
					link.l2 = RandPhraseSimple("Tenho algo que pode te interessar, irmão de pele vermelha. Quer negociar?","Posso te oferecer algo interessante para comprar, bravo guerreiro. Quer negociar?");
					link.l2.go = "war_indian_trade";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Pare, cara-pálida! Com que direito você pisa na minha terra?","Pare, homem branco! Você está na terra dos meus antepassados e na minha terra!","Pare, cara-pálida! Você não pertence à minha terra");
				link.l1 = RandPhraseSimple("Terra sua? Cai fora, seu desgraçado de cara vermelha!","Olha pra ele – um macaco falante! Cai fora, vai!");
				link.l1.go = "war_indian_1";
				link.l2 = RandPhraseSimple("Vim em paz, guerreiro de pele vermelha. Não devemos lutar à toa.","Não sou inimigo seu nem da sua terra, guerreiro. Vim em paz.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/3)) > hrand(80)) link.l2.go = "war_indian_2_1";
				else link.l2.go = "war_indian_2_2";
				link.l3 = RandPhraseSimple("Vim negociar com você, não lutar.","Eu não luto com índios. Eu faço comércio com eles.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/6)+makeint(GetSummonSkillFromName(pchar, SKILL_FORTUNE)/6)) > hrand(90)) link.l3.go = "war_indian_3_1";
				else link.l3.go = "war_indian_3_2";
			}
		break;
		
		case "war_indian_1":
			dialog.text = RandPhraseSimple("Você vai se arrepender do dia em que nasceu, cachorro de cara pálida... Vou arrancar seu coração e assá-lo na fogueira!","Vou te fazer comer pedras, cachorro de cara pálida! Vamos rir enquanto você implora pela morte de joelhos, vira-lata branco!");
			link.l1 = RandPhraseSimple("Você ainda não consegue calar essa boca imunda, seu espantalho enfeitado? Vou te mandar de volta pra selva de onde você rastejou!","Você ousa me ameaçar, seu verme?! Pois agora vai voltar correndo pro buraco de onde saiu!");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_2_1":
			dialog.text = RandPhraseSimple("Ouço que sua voz fala a verdade. Não vamos erguer nossos machados contra você hoje. Vá em paz, cara-pálida.","Rosto pálido raramente traz paz, mas vejo nos seus olhos que fala a verdade. Vá agora.");
			link.l1 = RandPhraseSimple("Uma decisão sábia, guerreiro. Boa sorte pra você.","Fico feliz que tenhamos chegado a um entendimento, guerreiro.");
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_2_2":
			dialog.text = RandPhraseSimple("Mentiroso, cachorro de cara pálida! Você veio aqui para matar índios! Pronto para a luta, cara pálida?!","Você mata índios. Língua branca é língua mentirosa. Eu corto ela fora e frito na fogueira!");
			link.l1 = RandPhraseSimple("Bem, camarada, então não me culpe. Deus sabe que eu tentei evitar isso...","Bem, você que pediu, guerreiro.");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_3_1":
			if (CheckCaribGuns())
			{
				npchar.quest.count = 0;
				dialog.text = "Troca? Precisamos da arma do homem branco. Aquela arma de fogo de uma mão só dos rostos-pálidos! Por isso, trocaremos nossas mercadorias! Você tem uma arma de fogo para trocar?";
				link.l1 = "Hmm. Eu tenho. E o que você vai me dar em troca?";
				link.l1.go = "war_indian_trade";
				link.l2 = "Seu canalha! E depois vai atirar nos colonos com as minhas pistolas? Não, isso não vai acontecer! Quanto a vocês, chacais, vou acabar com todos agora...";
				link.l2.go = "exit_fight";
			}
			else
			{
				dialog.text = "Você não tem o que queremos, cara-pálida... Você será nosso troféu de guerra!";
				link.l1 = "Tente se tiver coragem, espantalho...";
				link.l1.go = "exit_fight";
			}
		break;
		
		case "war_indian_3_2":
			dialog.text = RandPhraseSimple("Não negociamos com cães de cara-pálida. Matamos e tomamos!","Não somos imundos Miskitos ou Arawaks, não negociamos com caras-pálidas! Nós os matamos e pegamos seus troféus de guerra!");
			link.l1 = RandPhraseSimple("Então tente me roubar, canalha!","Primeiro, você vai ter que tirar meu sabre de mim, seu verme!");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_trade":
			iGun = 1;
			dialog.text = "Você mostra o que tem, e a gente diz o que oferece por isso.";
			for (i=6; i>=1; i--)
			{
				if (GetCharacterFreeItem(pchar, "pistol"+i) > 0)
				{
					sLink = "l"+iGun;
					link.(sLink) = "Offer "+XI_ConvertString("pistol"+i)+".";
					link.(sLink).go = "gun_"+i;
					iGun++;				
				}
			}
		break;
		
		case "gun_1":
			npchar.quest.gun = "pistol1";
			if (hrand(1) == 0)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(1)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(9)+14);
				iTotalTemp = hrand(2)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "Ei, ei! Nós vamos te pagar por isso "+sText+".";
			link.l1 = "Fechado!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Não. De jeito nenhum.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_2":
			npchar.quest.gun = "pistol2";
			if (hrand(3) < 2)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(3)+1);
				iTotalTemp = hrand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "Ei, que arma astuta... Vamos te dar algo por ela "+sText+".";
			link.l1 = "Fechado!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Não. De jeito nenhum.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_3":
			npchar.quest.gun = "pistol3";
			if (hrand(5) < 3)
			{
				qty = rand(1)+2;
				npchar.quest.item = "jewelry5"+qty;
				iTotalTemp = hrand(6)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful pearl";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(2)+2);
				iTotalTemp = hrand(2)+5;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  this beautiful stone";
			}
			dialog.text = "Ei-ho! Arma poderosa! Mata muitos, muitos inimigos! A gente te dá por ela "+sText+".";
			link.l1 = "Fechado!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Não. De jeito nenhum.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_4":
			npchar.quest.gun = "pistol4";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(10)+qty*30;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "obereg_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Ei! Uma arma assustadora... Vamos te dar isto em troca "+sText+".";
			link.l1 = "Fechado!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Não. De jeito nenhum.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_5":
			npchar.quest.gun = "pistol5";
			if (hrand(7) < 7)
			{
				if (hrand(10) < 8)
				{
					npchar.quest.item = "jewelry7";
					iTotalTemp = 2+hrand(1);
				}
				else
				{
					npchar.quest.item = "jewelry8";
					iTotalTemp = hrand(4)+10;
				}
				qty = hrand(1)+1;
				npchar.quest.item = "jewelry"+(qty+6);
				if (qty == 1) iTotalTemp = 2;
				else iTotalTemp = hrand(5)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful and precious petrified tar";
			}
			else
			{
				npchar.quest.item = "indian_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Ei! Que arma linda e poderosa! Já matou muitos, muitos inimigos! Nós te damos por ela "+sText+".";
			link.l1 = "Fechado!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Não. De jeito nenhum.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_6":
			npchar.quest.gun = "pistol6";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(8)+qty*20;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "amulet_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Ei, bela arma... Podemos te dar algo por ela "+sText+".";
			link.l1 = "Fechado!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Não. De jeito nenhum.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "war_indian_trade_agree":
			ChangeIndianRelation(1.00);
			npchar.quest.count = sti(npchar.quest.count)+1;
			TakeNItems(pchar, npchar.quest.item, iTotalTemp);
			RemoveItems(pchar, npchar.quest.gun, 1);
			Log_Info("You have given "+XI_ConvertString(npchar.quest.gun)+"");
			Log_Info("You have received "+XI_ConvertString(npchar.quest.item)+" in amount of "+FindRussianQtyString(iTotalTemp)+"");
			PlaySound("interface\important_item.wav");
			if (sti(npchar.quest.count) > 3+hrand(2));
			{
				dialog.text = "Ótimo. Aqui estão suas mercadorias. Não vamos negociar mais. Volte depois. Pagamos mais por uma arma de fogo melhor. Agora vá!";
				link.l1 = "Até logo, guerreiro de pele vermelha.";
				link.l1.go = "exit_peace";
			}
			else
			{
				dialog.text = "Certo. Aqui estão suas mercadorias. Tem mais armas de fogo para trocar?";
				if (CheckCaribGuns())
				{
					link.l1 = "Tenho sim. Vai querer comprar?";
					link.l1.go = "war_indian_trade";
				}
				link.l2 = "Não. Da próxima vez eu trago mais.";
				link.l2.go = "war_indian_trade_exit";
			}
		break;
		
		case "war_indian_trade_exit":
			dialog.text = "Traga. Traga uma arma de fogo melhor e nós pagaremos mais por ela. Agora vá!";
			link.l1 = "Até logo, guerreiro...";
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_trade_bad":
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				DialogExit();
				sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
				for(i = 0; i < iTemp; i++)
				{
					sld = CharacterFromID(sTemp + i);
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sGroup);
					LAi_SetImmortal(sld, false);
					LAi_CharacterDisableDialog(sld);
				}	
			}
			else
			{
				dialog.text = "Então a gente pega tudo de graça, cara-pálida!";
				link.l1 = "Pode tentar...";
				link.l1.go = "exit_fight";
			}
		break;
		
		// мирные индеи - мискито
		case "peace_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase("Saudações, homem branco. O que você procura em nossa selva?","A nossa selva é muito perigosa. O que você está fazendo aqui?","O que traz você aqui, bravo rosto-pálido?");
			link.l1 = RandPhraseSimple("Eu só estava de passagem, meu amigo de pele vermelha. Acho que tem espaço suficiente nesse caminho para nós dois?","Saudações, filho da selva! Estou aqui a negócios, e não luto contra índios.");
			link.l1.go = "peace_indian_1";
			link.l2 = RandPhraseSimple("E por que você precisa saber? Cuide da sua vida e não se meta em encrenca!","Siga seu caminho, pele-vermelha. Não tenho tempo para conversar com você.");
			link.l2.go = "peace_indian_2";
		break;
		
		case "peace_indian_1":
			dialog.text = RandPhraseSimple("Somos um povo pacífico. Não somos inimigos dos homens brancos. Vá, mas tenha cuidado em nossa terra!","Fico feliz em conhecer o amigo de rosto pálido dos índios. Vá em paz, filho do mar!");
			link.l1 = RandPhraseSimple("Boa sorte pra você também, filho da selva...","Adeus, amigo de pele vermelha.");
			link.l1.go = "exit_peace";
		break;
		
		case "peace_indian_2":
			dialog.text = RandPhraseSimple("Somos caçadores pacíficos. Mas não vamos tolerar rostos-pálidos falando assim em nossas terras!","Não lutamos contra homens brancos, mas se homens brancos nos ofendem, respondemos como nossos antepassados nos ensinaram!");
			link.l1 = RandPhraseSimple("Você ainda não consegue calar essa boca imunda, seu espantalho pintado? Vou te mandar de volta pra selva de onde você rastejou!","Você ousa me ameaçar, seu verme?! Agora vai subir de volta na árvore de onde acabou de descer!");
			link.l1.go = "exit_fight";
		break;
	}
}
