// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("O que deseja? Pode perguntar.","Estou ouvindo você, qual é a sua pergunta?"),"É a segunda vez que você tenta perguntar...","É a terceira vez que você tenta perguntar de novo...","Quando isso vai acabar?! Sou um homem ocupado, cuidando dos assuntos da colônia, e você ainda insiste em perguntar algo!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Agora não. Lugar e hora errados."),"É verdade... Mas depois, não agora...","Vou perguntar... Mas um pouco mais tarde...","Me desculpe, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Fechei um negócio lucrativo na Martinica e agora pretendo navegar para Blueweld. Quero comprar pau-brasil e café na sua colônia. Além disso, meu brigue não comporta toda a carga que desejo adquirir, então preciso comprar um fluyt aqui no seu estaleiro. Poderia me ajudar com essas questões?";
                link.l1.go = "MayorDone";
            }
		break;
		
		case "MayorDone":
			dialog.text = "Minha ajuda? Nosso comerciante é um homem muito honesto, então duvido que ele tentaria enganá-lo. Fale com o mestre do porto sobre a flauta, ele vai ajudá-lo com esse assunto. E se tiver qualquer problema, venha falar comigo. Tenho interesse em fortalecer as relações comerciais da nossa colônia e lhe darei todo o meu apoio. Além disso, estou organizando um banquete esta noite, e todos os notáveis de Bridgetown estarão presentes. Você também deveria vir, capitão.";
			link.l1 = "Obrigado pelo convite, mas infelizmente estou muito ocupado. Adeus, e agradeço pela sua ajuda!";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-8");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
			pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
			DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
				//if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
				//else AddDialogExitQuestFunction("CreateVanBergInWorld");
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
