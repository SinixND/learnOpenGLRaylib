#include <iostream>

enum class State
{
    regen,
    idle,
    busy,
    end_turn,
};

enum class Action
{
    none,
    mov,
    mov_active,
    atk,
    reg,
};

struct Hero
{
    int energy{10};
    int maxEnergy{10};
    int move{};
};

struct Enemies
{
    int energies[5]{0, 0, 2, 2, 4};
    int maxEnergies[5]{10, 10, 10, 10, 10};
    int attacks[5]{};
};

int main()
{
    Hero hero{};
    Enemies enemies{};

    State state{State::regen};

    int frame{32};
    while (--frame)
    {
        std::cout << "Frame [" << 32 - frame << "]: ";
        switch (state)
        {
        default:
        case State::regen:
        {
            std::cout << "Regen...\n";
            //* Regen system
            hero.energy += 1;
            if (!(hero.energy < hero.maxEnergy))
            {
                std::cout << "Hero rdy\n";
                state = State::idle;
            }

            for (auto i{0}; i < 5; ++i)
            {
                enemies.energies[i] += 1;
                if (!(enemies.energies[i] < enemies.maxEnergies[i]))
                {
                    std::cout << "Enemy " << i << " rdy\n";
                    state = State::idle;
                }
            }
            break;
        }
        case State::idle:
        {
            //* Action system
            if (!(hero.energy < hero.maxEnergy))
            {
                std::cout << "Add/Set hero mov action\n";
                hero.energy = 0;
                hero.move = 3;
                state = State::busy;
            }

            for (auto i{0}; i < 5; ++i)
            {
                if (!(enemies.energies[i] < enemies.maxEnergies[i]))
                {
                    std::cout << "Add/Set enemy atk action\n";
                    enemies.energies[i] = 0;
                    enemies.attacks[i] = 2;
                    state = State::busy;
                }
            }
            break;
        }
        case State::busy:
        {
            //* Execute instant actions
            //* Attack
            for (auto i{0}; i < 5; ++i)
            {
                if (enemies.attacks[i])
                {
                    std::cout << "Execute enemy attack action and cleanup action\n";
                    enemies.attacks[i] = 0;
                    state = State::end_turn;
                }
            }

            //* Execute multiframe actions
            state = State::end_turn;
            //* Move
            if (hero.move)
            {
                std::cout << "Execute hero move action\n";
                hero.move -= 1;

                if (hero.move)
                {
                    std::cout << "Hero move action ongoing\n";
                    state = State::busy;
                }
                else
                {
                    std::cout << "Hero move action done: Cleanup action\n";
                }
            }
            break;
        }
        case State::end_turn:
        {
            std::cout << "No actions left for this turn\n";
            state = State::regen;
            break;
        }
        }
    }
}
