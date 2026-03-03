// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Fale, estou ouvindo.";
			link.l1 = "Eu estava enganado. Adeus.";
			link.l1.go = "Exit";
			// --> Тичингиту
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "true")
            {
                link.l1 = "Há um índio preso. Ele foi capturado pelo Fadey, o Moscovita. Posso falar com ele?";
                link.l1.go = "Tichingitu";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "commandante")
            {
                link.l1 = "Me diga, você vai mesmo enforcar esse índio? Não acha que é um castigo pesado demais para um crime tão pequeno?";
                link.l1.go = "Tichingitu_3";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "pay")
            {
                link.l1 = "Sou eu de novo, comandante. Fadey, o Moscovita, escreveu este pedido para libertar o índio. Aqui está.";
                link.l1.go = "Tichingitu_6";
            }
			// <-- Тичингиту
			//Jason --> Бесчестный конкурент
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "Vim falar com você a pedido do dono da loja local, o nome dele é "+pchar.questTemp.Shadowtrader.Tradername+". Ele me pediu para entregar esta carta a você.";
				link.l1.go = "Shadowtrader_prison";
			}
			
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.SeekTrader") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "Sou eu de novo. Tenho provas substanciais de que "+pchar.questTemp.Shadowtrader.Tradername+" está certo.";
				link.l1.go = "Shadowtrader_prison2";
			}
			//Jason <-- Бесчестный конкурент
			//Sinistra --> Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTurma"))
            {
                link.l1 = "Estou procurando um homem chamado Longway. Ouvi dizer que você também está atrás dele, Monsieur Oficial. Teve alguma sorte em encontrá-lo, ou talvez alguma pista?";
                link.l1.go = "PZ_IshemLongway_1";
            }
			//Sinistra <-- Путеводная звезда
		break;
		
		// --> Тичингиту
		case "Tichingitu":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			dialog.text = "A-ah, Fadey lhe contou a história dele? Não tenho motivo para impedir que o veja, monsieur. Você não é o primeiro a vir ver aquele pele-vermelha. Bem, em dez dias qualquer cidadão poderá vê-lo quando o pendurarmos para secar ao sol...";
			link.l1 = "Então, posso entrar na prisão?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Como já te disse, 'não tenho motivo para te proibir disso.' Pode ir.";
			link.l1 = "Obrigado!";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "Tichingitu_3":
			DelLandQuestMark(npchar);
			dialog.text = "Você é novo aqui, não é, monsieur? Acabou de chegar da Europa? Você não entende a situação nas colônias. Esta execução vai servir de lição para aqueles malditos índios que ousam se meter nas propriedades dos colonos franceses. Além disso, o próprio Fadey faz questão disso, e ele é muito respeitado por aqui, além de ser um grande amigo do nosso governador.";
			link.l1 = "Existe alguma maneira de reduzir a punição? Ainda acho que foi severa demais...";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Ah, poupe-me da filosofia! Vá até Fadey e pergunte sobre esse índio se você realmente se importa com o destino dele. Se Fadey escrever um pedido de soltura, nós o concederemos.";
			link.l1 = "Entendido, oficial. Vou falar com Fadey.";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "fadey";
			AddLandQuestMark(characterFromId("fadey"), "questmarkmain");
			QuestPointerToLoc("BasTer_town", "reload", "houseSp1");
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			RemoveItems(pchar, "letter_1", 1);
			dialog.text = "(lendo) Hm... Esse Fadey é estranho... Exigiu uma execução pública, e agora está pedindo para soltar esse índio... Enfim, suponho que todos os amigos do governador sejam assim. Tá bom, pode ir e levar esse pele-vermelha.";
			link.l1 = "Meu agradecimento, oficial!";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			AddQuestRecord("Tichingitu", "3");
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_6";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- Тичингиту
		
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_prison":
			dialog.text = "De novo isso "+pchar.questTemp.Shadowtrader.Tradername+" com as reclamações dele! Tá bom, vamos ver o que é desta vez... (lê o papel)";
			link.l1 = "...";
			link.l1.go = "Shadowtrader_prison_1";
			RemoveItems(PChar, "letter_1", 1);
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Fort");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison_1":
			dialog.text = "De novo, só suposições absurdas e nenhuma prova concreta! Muito bem. Diga a ele que isso simplesmente não é suficiente para que eu alerte os guardas e mande vasculhar a cidade.";
			link.l1 = "Você quer que eu diga isso para ele?";
			link.l1.go = "Shadowtrader_prison_2";
		break;
		
		case "Shadowtrader_prison_2":
			dialog.text = "Exatamente – e, de preferência, palavra por palavra. Ele vai entender o que quero dizer. Não vou desperdiçar papel respondendo a esse sujeito irritante.";
			link.l1 = "Entendi. Então, até logo.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.Trouble = "true";
			NextDiag.TempNode = "First_officer";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
		
		case "Shadowtrader_prison2":
			dialog.text = "E que provas 'substanciais' são essas que você diz ter reunido?";
			link.l1 = "Fechei um acordo com os contrabandistas para comprar mercadorias pela loja não oficial deles. O agente deles vai vir hoje à noite ao escritório da capitania para me levar até essa tal 'loja'.";
			link.l1.go = "Shadowtrader_prison2_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			pchar.quest.ShadowtraderTimeSmugglers_Over.over = "yes";
			pchar.quest.Shadowtrader_SMG.over = "yes";//снять оба прерывания
			sld = characterFromID("ShadowAgent_1");
			sld.lifeday = 0;
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison2_1":
			dialog.text = "Hmm... Muito bem, capitão! Agora vamos avançar. Enviaremos nosso homem à reunião deles, localizaremos o esconderijo e prenderemos todos. Obrigado pela sua iniciativa!";
			link.l1 = "Sempre fico feliz em ajudar. Tenho certeza de que sua operação será um sucesso.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.End.Fort = "true";
			AddQuestRecord("Shadowtrader", "7");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			SetTimerFunction("ShadowTrader_questmark", 0, 0, 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			NextDiag.TempNode = "First_officer";
		break;
		// <-- мини-квест Бесчестный конкурент
		
		// Sinistra - Квест "Путеводная звезда" ==>
		case "PZ_IshemLongway_1":
			DelLandQuestMark(npchar);
			dialog.text = "Quem? Long... Way? Não me lembro de nenhum inglês na nossa cidade recentemente.";
			link.l1 = "Não, Longway é... chinês.";
			link.l1.go = "PZ_IshemLongway_2";
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTurma");
			DeleteQuestCondition("PZ_BasTerPeshera");
		break;
		
		case "PZ_IshemLongway_2":
			dialog.text = "Então, então. E por que está procurando esse tal de Longway, monsieur?";
			link.l1 = "Ele é meu amigo. Já fiquei sabendo do que aconteceu – foi um triste mal-entendido, eu lhe garanto.";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "Estou procurando por ele porque é um criminoso conhecido no Arquipélago.";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_IshemLongway_Zashita_1":
			dialog.text = "Ah, um mal-entendido. Não estávamos tentando dar um jeito nele ali mesmo, de forma alguma. Só queríamos conversar com ele... para começar. No entanto, esse seu homem amarelo agressivo não só derrubou vários guardas da cidade, como também massacrou as unidades enviadas para persegui-lo na selva.";
			link.l1 = "Você pretende enviar outra unidade? Eu poderia ir com seus homens, conversar com ele, acalmá-lo e evitar outro desastre. Bastaria se as mortes parassem e Longway deixasse a cidade de uma vez por todas?";
			link.l1.go = "PZ_IshemLongway_Zashita_2";
		break;
		
		case "PZ_IshemLongway_Zashita_2":
			dialog.text = "Em circunstâncias normais, talvez eu concordasse com você. Mas veja, um dos mortos era um oficial — um jovem tenente promissor, o favorito de Sua Graça. A cidade está de luto. Não tem como fingir que não aconteceu ou compensar isso. Você entende?";
			link.l1 = "Entendo perfeitamente. Peço desculpas pelas ações do meu amigo. Não vou incomodá-lo mais.";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
			link.l2 = "Sabe, só Deus sabe o que acontece na selva. Qualquer um poderia ter matado aqueles homens.";
			link.l2.go = "PZ_IshemLongway_Blef_1";
		break;
		
		case "PZ_IshemLongway_Blef_1":
			dialog.text = "E quem você acha que seria capaz de derrubar uma patrulha inteira comandada por um oficial?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(Confiável) Bandidos, quem mais? Tenho até vergonha de admitir, mas por pouco escapei de uma quadrilha enorme outro dia.";
				link.l1.go = "PZ_IshemLongway_Blef_2";
			}
			else
			{
				Notification_Perk(false, "Trustworthy");
				link.l1 = "Mas como eu saberia? Poderia ter sido qualquer um—bandidos, piratas, espiões...";
				link.l1.go = "PZ_IshemLongway_Blef_netVD_1";
			}
		break;
		
		case "PZ_IshemLongway_Blef_2":
			dialog.text = "Heh, não me surpreende – considerando o seu tamanho, Capitão. Sim, temos desses canalhas na ilha ultimamente...";
			link.l1 = "Exatamente! Então, eles poderiam ter massacrado a patrulha e o pobre tenente júnior.";
			link.l1.go = "PZ_IshemLongway_Blef_3";
		break;
		
		case "PZ_IshemLongway_Blef_3":
			dialog.text = "Infelizmente, isso é bem possível.";
			link.l1 = "Exatamente. Então, mais uma vez, peço que me deixe participar da próxima busca – Longway vai me ouvir, e assim podemos evitar mais mortes.";
			link.l1.go = "PZ_IshemLongway_Blef_4";
		break;
		
		case "PZ_IshemLongway_Blef_4":
			dialog.text = "Tudo bem. Mas ainda tem um 'porém', senhor.";
			link.l1 = "E o que é isso?";
			link.l1.go = "PZ_IshemLongway_Blef_5";
		break;
		
		case "PZ_IshemLongway_Blef_5":
			dialog.text = "Diferente do que aconteceu na selva, a culpa do seu amigo na cidade está clara e totalmente comprovada. Isso não ficará impune. Então, essas mortes precisam ser compensadas se você quiser que ele saia vivo da cidade.";
			link.l1 = "Justo. Quanto vai custar, Monsieur Oficial?";
			link.l1.go = "PZ_IshemLongway_Blef_6";
		break;
		
		case "PZ_IshemLongway_Blef_6":
			dialog.text = "Trezentas dobras. Esse dinheiro vai para a cidade, não para os briguentos da praça do mercado.";
			if (PCharDublonsTotal() >= 300)
			{
				link.l1 = "Claro. Trezentos doblões - aqui está.";
				link.l1.go = "PZ_IshemLongway_Blef_7";
			}
			link.l2 = "Não trouxe meus doblões para a cidade desta vez. Mas se me deixar buscá-los...";
			link.l2.go = "PZ_IshemLongway_NetDublonov_1";
		break;
		
		case "PZ_IshemLongway_Blef_7":
			dialog.text = "Excelente. Você provou ser responsável. Estamos apenas finalizando as instruções para o próximo grupo. Autorizo sua participação.";
			link.l1 = "Obrigado. Adeus, Monsieur Oficial.";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.PZ_DrugOtryad = true;
		break;
		
		case "PZ_IshemLongway_NetDublonov_1":
			dialog.text = "Eu não nasci ontem. Sei que você pretende fugir – não por causa dos dobrões, mas por causa do seu querido chinês.";
			link.l1 = "Dou minha palavra que não vou sair da cidade com Longway.";
			link.l1.go = "PZ_IshemLongway_NetDublonov_2";
		break;
		
		case "PZ_IshemLongway_NetDublonov_2":
			dialog.text = "Palavras, palavras... Estou cansado da sua conversa, Capitão. Você não vai a lugar nenhum até pegarmos esse maldito homem de pele amarela nós mesmos.";
			link.l1 = "Eu vou obedecer à sua ordem se você prometer não matar o Longway imediatamente, senhor oficial.";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "Mas fui eu que quebrei as leis da cidade hoje, pessoalmente?";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_1":
			dialog.text = "Então você não sabe. Vou confiar no meu instinto – o chinês precisa ser capturado, custe o que custar.";
			link.l1 = "Sua suspeita atual? Mas você não tem nenhuma prova de que Longway matou todo mundo na selva.";
			link.l1.go = "PZ_IshemLongway_Blef_netVD_2";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_2":
			dialog.text = "E você tem provas da inocência dele? Não? Então pare de fazer do seu homem de pele amarela um santo. Está me entendendo?";
			link.l1 = "Entendo perfeitamente. Peço desculpas pelas ações do meu amigo. Não vou incomodá-lo mais.";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
		break;
		
		case "PZ_IshemLongway_Uiti_1":
			dialog.text = "Receio que não posso deixar você sair ainda, Capitão.";
			link.l1 = "O que você quer dizer?";
			link.l1.go = "PZ_IshemLongway_Uiti_2";
		break;
		
		case "PZ_IshemLongway_Uiti_2":
			dialog.text = "O que quero dizer é que, já que esse Longway é seu amigo, não há garantia de que você não vá correr atrás dele e tentar fugir junto. Então, vou ter que te manter preso até pegarmos esse açougueiro de pele amarela nós mesmos.";
			link.l1 = "Eu vou obedecer à sua ordem se você prometer não matar o Longway aqui mesmo, senhor oficial.";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "Mas fui eu que quebrei as leis da cidade hoje, pessoalmente?";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Arest_1":
			dialog.text = "Não posso prometer nada. Vai saber o que seu amigo está planejando, ou se ele vai começar outro massacre quando nos vir. Enquanto isso, aproveite seu alojamento de luxo, Capitão.";
			link.l1 = "Hilário...";
			link.l1.go = "PZ_IshemLongway_Arest_2";
		break;
		
		case "PZ_IshemLongway_Arest_2":
			DialogExit();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto9", "PZ_SharliePlennik_BadFinal");
		break;
		
		case "PZ_IshemLongway_Pobeg_1":
			dialog.text = "Entenda, não tenho nada contra você pessoalmente. E você está certo – você não cometeu nenhum crime. Mas precisamos garantir que seu amigo de pele amarela não fuja da justiça.";
			link.l1 = "Então entenda que não vou permitir ser detido de maneira tão vergonhosa.";
			link.l1.go = "PZ_IshemLongway_Pobeg_2";
		break;
		
		case "PZ_IshemLongway_Pobeg_2":
			if (pchar.location.from_sea == "BasTer_Town")
			{
				dialog.text = "Nesse caso, teremos que fazer o senhor se calar.";
			}
			else
			{
				dialog.text = "Já cansei disso! Sargento, leve o pelotão até aquela maldita caverna e encontre o chinês! Com este aqui eu mesmo vou cuidar...";
			}
			link.l1 = "Nem pense nisso.";
			link.l1.go = "PZ_IshemLongway_Pobeg_3";
		break;
		
		case "PZ_IshemLongway_Pobeg_3":
			DialogExit();
			
			LAi_SetHuberType(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_MoveCharacter(NPChar, "FRANCE_CITIZENS");
			LAi_group_Attack(characterFromId("BasTer_Mayor"), Pchar);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			if (pchar.location.from_sea == "BasTer_Town")
			{
				PChar.quest.PZ_KorablPort_BadFinal.win_condition.l1 = "MapEnter";
				PChar.quest.PZ_KorablPort_BadFinal.win_condition = "PZ_KorablPort_BadFinal";
				AddQuestRecord("PZ", "10");
				LocatorReloadEnterDisable("BasTer_town", "gate_back", true);
				Island_SetReloadEnableGlobal("Guadeloupe", false);
			}
			else
			{
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition.l1 = "EnterToSea";
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition = "PZ_KorablBuhta_BadFinal";
				AddQuestRecord("PZ", "5");
				
				// Микро-диалог с Лонгвэем у пещеры, если мы побежали к пещере ему помочь после ссоры с комендантом
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1 = "location";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1.location = "Guadeloupe_CaveEntrance";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition = "PZ_IshemLongway_SorraKomendant";
				
				LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
				LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
				//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			}
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_1":
			dialog.text = "Caçador de recompensas, hein? Normalmente, não gosto de lidar com gente como você, mas neste caso, é do meu interesse que nossos objetivos coincidam. Pelo visto, esse de pele amarela é um assassino notório. Já matou muitos dos meus homens, tanto na cidade quanto na mata.";
			link.l1 = "Já faz um tempo que estou perseguindo ele pelo Arquipélago.";
			link.l1.go = "PZ_IshemLongway_OhotnikOtryad_2";
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_2":
			dialog.text = "Maldito canalha! Aqui está o que vamos fazer: vou reunir outro grupo, e você vai com eles. Desta vez, ele não tem para onde fugir, e com a sua ajuda, teremos mais chance de sucesso. Mas não espere recompensa de mim – você é um caçador de recompensas, então seu pagamento virá de quem te contratou. Devia agradecer por eu deixar você cooperar comigo, e só.";
			link.l1 = "É verdade. Até mais, oficial. Se algum dos seus homens sobreviver a outro encontro com nosso amigo chinês, eu te conto como foi.";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			pchar.questTemp.PZ_OhotnikOtryad = true;
		break;
		
		case "PZ_IshemLongway_BeryomOtryad":
			DialogExit();
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			DoQuestReloadToLocation("Guadeloupe_jungle_02", "goto", "goto1", "PZ_IshemLongway_Otryad");
		break;
		
		case "PZ_BasTer_ComendantDialog_1":
			dialog.text = "Você tem razão. Vocês dois se conhecem, não é? Qual é a relação entre vocês?";
			link.l1 = " Ele é oficial de navegação no meu navio, e...";
			link.l1.go = "PZ_BasTer_ComendantDialog_2";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "Estou procurando por ele porque é um criminoso conhecido no Arquipélago.";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_BasTer_ComendantDialog_2":
			dialog.text = "Ele é melhor com armas do que com mapas. Você faz ideia do que o seu mascote chinês aprontou?";
			link.l1 = "Para ser sincero, não, acabei de atracar e comecei a procurar. Tenho certeza de que foi tudo um mal-entendido.";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_1":
			dialog.text = "Exatamente. Quem é você para ele, se o quer tanto assim? Não importa – o que interessa é o motivo da sua visita à cidade.";
			link.l1 = "Nada ilegal, senhor. Mas o que quis dizer com “isso não importa mais”? Ele...";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_2";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_2":
			dialog.text = "Sim. Ele foi enterrado atrás de uma das colinas, um pouco afastado do cemitério. Os padres não permitiram um enterro cristão de verdade para um pagão.";
			link.l1 = "Como isso aconteceu, se não for segredo?";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_3";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_3":
			dialog.text = "Muito simples – ele chegou à cidade, bisbilhotando sem parar. Tentamos conversar com ele, descobrir o que fazia aqui, mas ele matou alguns homens e fugiu para a selva. Mandei várias equipes atrás dele, uma após a outra, mas ele acabou com todas! Tivemos que encurralá-lo numa caverna, e os atiradores fizeram o resto.";
			link.l1 = "E você não sabe o que ele estava procurando? Veja bem, ele nunca tinha feito nada assim antes – ele era navegador no meu navio. Mas aí me roubou e fugiu.";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_4";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_4":
			dialog.text = "Simplesmente me escapou da cabeça, é. Então, você também sofreu nas mãos dele? Isso vai te ensinar uma lição, Capitão. Da próxima vez, vai pensar duas vezes antes de confiar em alguém que não merece. Nunca confie em um homem de pele amarela – lembre-se do que estou dizendo!";
			link.l1 = "Entendi, vou lembrar disso. Descobriu algo sobre ele?";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_5";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_5":
			dialog.text = "Ah, você quer recuperar os bens roubados? Ele tinha um pouco de prata nos bolsos, então, se ele roubou de você, já gastou tudo. E havia uns papéis... do diário de bordo do seu navio? Não conseguimos entender nada – talvez algum tipo de código? Estava tudo coberto de sangue, então não deu pra identificar as partes que não estavam danificadas.";
			link.l1 = "Ah, sim. Obrigado. Sempre me preocupei com o que aconteceria se meus diários e anotações caíssem nas mãos de outra pessoa...";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_6";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_6":
			dialog.text = "E ter que inventar uma cifra complicada por causa disso? Não ficou com pena do seu tempo e esforço? Pronto, está aqui. E sobre a prata – não fique bravo, mas devolvemos para a cidade. Aquele chinês mandou muitos dos meus homens pro caixão naquele dia.";
			link.l1 = "Então não me atrevo a insistir. Adeus.";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_7";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_7":
			DialogExit();
			
			LAi_SetHuberType(npchar);
			AddQuestRecord("PZ", "9");
			CloseQuestHeader("PZ");
			bDisableLandEncounters = false;
		break;
		// <== Квест "Путеводная звезда" - Sinistra
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
