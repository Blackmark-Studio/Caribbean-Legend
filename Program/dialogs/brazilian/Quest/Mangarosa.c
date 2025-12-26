// диалоги персонажей по квесту Мангароса
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "O que você quer?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		// Амелия - знахарка-цыганка
		case "amelia":
			dialog.text = "O que você quer na minha casa?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "Seu nome é Amelia, certo? Vim te perguntar sobre uma planta. Manga Rosa.";
				link.l1.go = "amelia_1";
			}
			else
			{
				link.l1 = "Não tenho nada para te contar ainda. Mas um dia eu volto...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "amelia";
		break;
		
		case "amelia_1":
			dialog.text = "Interessante! E quem foi que te falou sobre mim, jovem corajoso?";
			link.l1 = "Uma das suas pessoas. Ela disse que você conhece os segredos desta planta e que pode me ensinar a fazer poções especiais com ela...";
			link.l1.go = "amelia_2";
		break;
		
		case "amelia_2":
			dialog.text = "Primeiro, me mostre a planta de que está falando. Talvez você não saiba nada sobre ela e só esteja perdendo meu tempo. Onde está sua Manga Rosa?";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "Aqui, dá uma olhada.";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "Hm...";
				link.l1.go = "amelia_exit";
			}
		break;
		
		case "amelia_exit":
			dialog.text = "E o que você ia me mostrar? Você não tem Manga Rosa. Então cai fora, camarada, antes que eu perca a paciência. Essa conversa acabou.";
			link.l1 = "Mas...";
			link.l1.go = "exit";
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_wait":
			dialog.text = "Você de novo? Não arrume confusão, garoto...";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "Calma, Amelia. Devo ter deixado cair em algum lugar da última vez. Aqui, trouxe uma Manga Rosa para você. Dá uma olhada.";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "amelia_exit";
			}
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_3":
			dialog.text = "Vamos ver... Parece que você sabe alguma coisa sobre isso. E quer que eu te conte os segredos das minhas poções?";
			link.l1 = "Exatamente. E pelo que entendi, não de graça...";
			link.l1.go = "amelia_4";
		break;
		
		case "amelia_4":
			dialog.text = "Você entendeu direitinho, rapaz! Não parece ser um completo idiota. Pois bem, posso ensinar a um homem que busca conhecimento e que não desperdiça essa planta rara com besteiras de fumo inúteis...";
			link.l1 = "Amelia, antes de começarmos a negociar... você poderia me contar um pouco do básico sobre as poções que posso fazer com Manga Rosa?";
			link.l1.go = "amelia_5";
		break;
		
		case "amelia_5":
			dialog.text = "Sem negociação, camarada. Eu vou te dizer o preço e cabe a você decidir se vai pagar ou não. Não conte com pechinchas ou descontos, aqui não é mercado. E sobre sua pergunta... Você pode preparar poções especiais de Manga Rosa que vão fortalecer suas habilidades físicas. Elas podem te deixar mais forte, mais resistente ou mais rápido, ou podem transformar completamente seu corpo, te tornando mais forte em todos os aspectos, mas uma poção dessas teria um efeito mais fraco do que as duas anteriores.";
			link.l1 = "Muito interessante. Diga seu preço.";
			link.l1.go = "amelia_6";
		break;
		
		case "amelia_6":
			dialog.text = "Posso te ensinar três receitas. Para cada receita, peço uma planta e quinhentas moedas de ouro.";
			link.l1 = "Me conte mais sobre essas poções. O que cada uma delas faz?";
			link.l1.go = "amelia_7";
		break;
		
		case "amelia_7":
			dialog.text = "You must be a master of the art of alchemy if you wish to brew even a single potion. Each potion lasts for two days or less, depending on when you drink it; if you take it at midnight, it will last nearly two full days\nThe first potion increases your strength and endurance. You will fight better, take less damage, and carry more weight\nThe second potion will make you swifter, more agile, tireless, and it will also improve your aim\nThe third potion has effects half as strong as both previous potions. But it also grants you charm, self-confidence, and luck as well\nAll Manga Rosa-based potions have a positive effect on your health. You must drink only one potion at a time; never mix them, otherwise they will do you no good—on the contrary, you will suffer severe poisoning\nSo, handsome, are you ready to pay for the knowledge right now, or do you need time to think?";
			if (CheckCharacterItem(pchar, "cannabis7") && PCharDublonsTotal() >= 500)
			{
				link.l1 = "Sim, estou pronto.";
				link.l1.go = "amelia_8";
			}
			link.l2 = "Preciso pensar um pouco. É uma decisão importante a tomar.";
			link.l2.go = "exit";
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_next":
			if (!CheckAttribute(npchar, "quest.ChickenGod") && CheckCharacterItem(pchar, "talisman11")) {
				if (CheckAttribute(npchar, "quest.recipe_power") || CheckAttribute(npchar, "quest.recipe_fast") || CheckAttribute(npchar, "quest.recipe_total")) {
					link.chickengod = "Amelia, you seem to have a knack for such things. Can you tell me if there is a demand for such stones among your people? I find them everywhere - it's like everyone is obsessed with them!";
					link.chickengod.go = "chickengod";
				}
			}
			
			if (CheckAttribute(npchar, "quest.ChickenGod") && !CheckAttribute(npchar, "quest.ChickenGod.Complete") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.chickengod = "Here you go, Amelia. Just as you ordered: one hundred and thirteen adder stones.";
				link.chickengod.go = "chickengod_collected";
			}
		
			if (CheckAttribute(npchar, "quest.recipe_all"))
			{
				dialog.text = "Ah, é você, rapaz! Então, minhas poções te ajudaram?";
				link.l1 = "Eles realmente fizeram isso, Amelia. Obrigado!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ah, é você, rapaz! Quer comprar algumas receitas?";
				if (CheckCharacterItem(pchar, "cannabis7") && PCharDublonsTotal() >= 500)
				{
					link.l1 = "Exatamente. É por isso que estou aqui.";
					link.l1.go = "amelia_8";
				}
				
				link.l2 = "Ainda não, Amelia. Só vim te fazer uma visita.";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_8":
			dialog.text = "Muito bem. Que tipo de receita você gostaria de comprar?";
			if (!CheckAttribute(npchar, "quest.recipe_power"))
			{
				link.l1 = "A receita de uma poção de força e resistência.";
				link.l1.go = "power";
			}
			if (!CheckAttribute(npchar, "quest.recipe_fast"))
			{
				link.l2 = "A receita da poção de agilidade e incansável disposição.";
				link.l2.go = "fast";
			}
			if (!CheckAttribute(npchar, "quest.recipe_total"))
			{
				link.l3 = "A receita de uma poção complexa.";
				link.l3.go = "total";
			}
		break;
		
		case "power":
			dialog.text = "Certo. Eu a chamei de 'Onda Gigante'. Aqui, pegue as instruções. Leia com atenção. E não se esqueça de usá-la do jeito certo!";
			link.l1 = "Obrigada, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosapower");
			SetAlchemyRecipeKnown("mangarosapower");
			npchar.quest.recipe_power = true;
		break;
		
		case "fast":
			dialog.text = "Certo. Eu a chamei de 'Tempestade'. Aqui, pegue as instruções. Leia com atenção. E não se esqueça de usá-la do jeito certo!";
			link.l1 = "Obrigada, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosafast");
			SetAlchemyRecipeKnown("mangarosafast");
			npchar.quest.recipe_fast = true;
		break;
		
		case "total":
			dialog.text = "Certo. Eu chamei de 'Abraço do Mar'. Aqui, pegue estas instruções. Leia com atenção. E não se esqueça de usar direito!";
			link.l1 = "Obrigada, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosatotal");
			SetAlchemyRecipeKnown("mangarosatotal");
			npchar.quest.recipe_total = true;
		break;
		
		case "recipe_exit":
			DialogExit();
			NextDiag.CurrentNode = "amelia_next";
			RemoveDublonsFromPCharTotal(500);
			RemoveItems(pchar, "cannabis7", 1);
			Log_Info("You have given 500 doubloons and one Manga Rosa");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.recipe_power") && CheckAttribute(npchar, "quest.recipe_fast") && CheckAttribute(npchar, "quest.recipe_total"))
			{
				npchar.quest.recipe_all = true;
				CloseQuestHeader("mangarosa");
			}
		break;
		
		case "chickengod":
			dialog.text = "Bax de adder, de fato! Não vale muito, mas pode ser útil para quem sabe usar. Traga-me cento e treze deles, e eu abrirei um dos meus baús para você.";
			link.l1 = "Isso é um monte de pedras! Por que você não me diz primeiro pra que precisa delas?";
			link.l1.go = "chickengod_1";
		break;
		
		case "chickengod_1":
			dialog.text = "Não, querido, se você precisa perguntar, então esse conhecimento ainda não serve para você.";
			link.l1 = "E o que tem dentro do baú que você prometeu abrir com tanta generosidade?";
			link.l1.go = "chickengod_2";
		break;
		
		case "chickengod_2":
			dialog.text = "Muitas coisas úteis para capitães que não desprezam trabalho manual. Não me faça perder tempo, querido, você não vai conseguir juntar tantas pedrinhas assim mesmo.";
			link.l1 = "Vamos ver sobre isso!";
			link.l1.go = "exit";
			
			npchar.quest.ChickenGod = true;
		break;
		
		case "chickengod_collected":
			dialog.text = "Ha-ha-ha! Era só uma brincadeira, querida!";
			link.l1 = "A piada vai ser pra você quando te queimarem, bruxa, na sua própria cabana!";
			link.l1.go = "chickengod_collected_1";
		break;
		
		case "chickengod_collected_1":
			dialog.text = "Esse não é o meu destino, querido... Você deixou esta cigana orgulhosa! Aqui, este baú é seu para saquear.";
			link.l1 = "Obrigada, Amelia. Mas espero mesmo que tenha algo útil aí além das suas roupas de baixo velhas...";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			npchar.quest.ChickenGod.Complete = true;
			AddDialogExitQuestFunction("ChickenGod_AmeliaOpenChest");
		break;
	}
} 
