// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Perguntas, "+GetAddress_Form(NPChar)+"?","Como posso ajudar você, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Hm, qual é a sua, "+GetAddress_Form(NPChar)+"? ","De novo com essas perguntas estranhas? Vai tomar um rum, vai...")+"","Durante o dia de hoje, essa já é a terceira vez que você faz essa pergunta..."+GetSexPhrase(" Isso são sinais de afeto?","")+"","Mais perguntas, imagino eu. "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia","Não tenho nada para conversar no momento."),"Não, não, linda...","De jeito nenhum, querido(a)...","Não, que perguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_W")
            {
                link.l1 = "Escuta aqui, mulher, dizem que você era bem próxima do meu velho camarada Francois Gontier. Bem próxima mesmo...";
                link.l1.go = "Jamaica_ratW_1";
            }
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_WP")
            {
				if (CheckCharacterItem(pchar, "jewelry43"))
				{
					link.l1 = "Trouxe seu colar com as pedras preciosas. Aqui está. Que Deus me livre de mulheres gananciosas como você no futuro.";
					link.l1.go = "Jamaica_ratW_5";
				}
				else
				{
					link.l1 = "Nada por enquanto. Estou procurando seu colar.";
					link.l1.go = "exit";
				}
            }
			
		break;
		
		case "Jamaica_ratW_1":
            dialog.text = "Sim, nós estávamos. E daí? Não sou casada e passo meu tempo com quem eu quiser. O François é um marinheiro muito respeitável, diferente desses pescadores e fazendeiros daqui. Ele é tão... Ah! E ainda me deu presentes tão bonitos!";
            link.l1 = "Chega, já basta! Eu sei muito bem das qualidades do meu companheiro, não precisa ficar me lembrando. Não me importa o que aconteceu entre vocês dois. Podem até se casar, tanto faz pra mim. O que importa é que eu preciso encontrá-lo agora mesmo, entendeu? Sabe pra onde ele foi?";
            link.l1.go = "Jamaica_ratW_2";
        break;
		
		case "Jamaica_ratW_2":
            dialog.text = "Tee hee... Você é o camarada dele, e não sabe pra onde ele foi. Isso é engraçado!";
            link.l1 = "Não tem graça nenhuma, mulher. Tínhamos combinado de nos encontrar na Jamaica e depois tínhamos uma viagem juntos esperando por nós... se é que me entende. Não vou conseguir fazer isso sozinho e ele foi pra Deus sabe onde!";
            link.l1.go = "Jamaica_ratW_3";
        break;
		
		case "Jamaica_ratW_3":
            dialog.text = "Entendo. Bem, se uma viagem tão lucrativa está no seu horizonte, e considerando que você e o François são amigos... Eu te conto para onde ele foi, mas só por uma pequena recompensa.";
            link.l1 = "Tá, eu entendi o recado. Quanto você quer?";
            link.l1.go = "Jamaica_ratW_4";
        break;
		
		case "Jamaica_ratW_4":
            dialog.text = "Oh, que venal! Não preciso de dinheiro nenhum. Não, eu quero algo especial. O François prometeu me dar um colar lindo com pedras preciosas. Já até contei para as minhas amigas e ele sumiu... Traga o pingente para mim e eu te conto para onde ele foi, he-he!";
            link.l1 = "Sua atrevida! Vocês, holandesas, são gananciosas como ninguém! Tá bom, você vai receber seu colar.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_5");
			pchar.questTemp.Slavetrader = "FindRatJamaica_WP";
        break;
		
		case "Jamaica_ratW_5":
            dialog.text = "Ah, está lindo! Agora meus amigos vão morrer de inveja!";
            link.l1 = "Mande minhas condolências a eles. Agora comece a falar. Para onde o François foi?";
            link.l1.go = "Jamaica_ratW_6";
			RemoveItems(PChar, "jewelry43", 1);
        break;
		
		case "Jamaica_ratW_6":
            dialog.text = "Sim, claro, senhor. François partiu rumo a Cuba, para Havana.";
            link.l1 = "Obrigado pela dica cara, garota. Era só isso que eu queria.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_6");
			pchar.questTemp.Slavetrader = "FindRatHavana";
        break;
		
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
